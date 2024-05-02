/* codgen.c       Generate Assembly Code for x86         07 May 18   */

/* Copyright (c) 2018 Gordon S. Novak Jr. and The University of Texas at Austin
    */

/* Starter file for CS 375 Code Generation assignment.           */
/* Written by Gordon S. Novak Jr.                  */

/* This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License (file gpl.text) for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "symtab.h"
#include "lexan.h"
#include "genasm.h"
#include "codegen.h"
#include "pprint.h"
#include <float.h>
 
/* Set DEBUGGEN to 1 for debug printouts of code generation */
#define DEBUGGEN 0

int nextlabel;    /* Next available label number */
int stkframesize;   /* total stack frame size */

TOKEN inline_funcall = NULL;        /* to handle function calls in the RHS of an ASSIGNOP statement */
int num_funcalls_in_curr_tree;
int num_inlines_processed;
int saved_inline_reg;
int saved_inline_regs[10];

int saved_label_num = -1;           /* saves the label number of the top-level label; used to handle repeat statements */

bool new_funcall_flag = false;   /* if a FUNCALLOP is for new(), set to true */

double saved_float_reg = -DBL_MAX;  /* in an ASSIGNOP, holds the value of the float being assigned */

bool nil_flag = false;           /* if assigning a NUMBERTOK with whichval == 0 to a ptr, set to true */

TOKEN saved_rhs_reg = NULL;         /* in an ASSIGNOP, save the TOKEN representing the RHS (value to be assigned) */
int saved_rhs_reg_num = -1;         /* in an ASSIGNOP, save the register location of saved_rhs_reg */

bool nested_refs = false;        /* used in POINTEROP in genop(). probably can be deprecated but have not checked */
TOKEN first_op_genarith = NULL;     /* used to signal if multiple pointer dereferences are made in a single statement */
TOKEN nested_ref_stop_at = NULL;    /* in an AREFOP in genop(), and if multiple ptr dereferences are made in a single statement,
                                       signals the second-to-last pointer dereference */

TOKEN last_ptr = NULL;              /* the last pointer to be referenced in any single statement */
int last_ptr_reg_num;               /* the register number last_ptr */
int last_ptr_deref_offs;            /* the offset of the field being dereferenced by the statement in which last_ptr is set */

int last_id_reg_num;                /* the register number location of the last identifier referenced in a statement (EXCEPT pointers) */

                     /* integer regs */
int used_regs[32] = { 0, 0, 0, 0, 0, 0, 0, 0,
                     /* FP regs; r8d to r15d */
                      0, 0, 0, 0, 0, 0, 0, 0,
                     /* xmm0 to xmm15 */
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                    };

#define NUM_INT_REGS    8
#define NUM_FP_REGS     24
#define NUM_REGS        32

/*  Top-level entry for code generator.
    pcode    = pointer to code:  (program foo (output) (progn ...))
    varsize  = size of local storage in bytes
    maxlabel = maximum label number used so far

    Add this line to the end of your main program:
        gencode(parseresult, blockoffs[blocknumber], labelnumber);
    The generated code is printed out; use a text editor to extract it for
    your .s file.
*/

//good as is
void gencode(TOKEN pcode, int varsize, int maxlabel)
  {  TOKEN name, code;
     name = pcode->operands;
     code = name->link->link;
     nextlabel = maxlabel + 1;
     stkframesize = asmentry(name->stringval,varsize);
     genc(code);
     asmexit(name->stringval);
  }


/* Trivial version: always returns RBASE + 0 */
/* Get a register.   */
/* Need a type parameter or two versions for INTEGER or REAL */
//good
int getreg(int kind) {
    int start, stop;

    // Set the range based on the type of register
    if (kind == INTEGER || kind == POINTER) {
        start = 0;
        stop = NUM_INT_REGS;
    } else {
        start = 16;
        stop = NUM_REGS;
    }

    // Search for an unused register within the specified range
    for (int i = start; i < stop; i++) {
        if (used_regs[i] == 0) {
            used_regs[i] = 1;
            return i;
        }
    }
    // If no register is found, return the base register
    return RBASE;
}


/* Trivial version */
/* Generate code for arithmetic expression, return a register number */
int genarith(TOKEN code) {

    int num, reg_num, lhs_reg, rhs_reg;
    SYMBOL sym;

    switch (code->tokentype) {
        case NUMBERTOK:
            reg_num = getreg(code->basicdt);

            if (code->basicdt == INTEGER) {
                num = code->intval;

                if (num >= MINIMMEDIATE && num <= MAXIMMEDIATE && !nested_refs) {
                    if (last_ptr && last_ptr_reg_num > -1) {
                        asmimmed(MOVQ, num, reg_num);
                    } else {
                        asmimmed(nil_flag ? MOVQ : MOVL, num, reg_num);
                    }
                }
            } 
            else {
                makeflit(code->realval, nextlabel);
                asmldflit(MOVSD, nextlabel++, reg_num);
            }

            break;

        case IDENTIFIERTOK:
            sym = searchst(code->stringval);
            num = sym->offset;

            if (sym->kind == FUNCTIONSYM) {
                reg_num = getreg(sym->datatype->basicdt);
                inline_funcall = code;
                genc(code->link);
            } 
            
            else {
                int bdt = code->basicdt;
                reg_num = getreg(bdt);

                if (code->basicdt != POINTER && NUM_INT_REGS > reg_num) {
                    SYMBOL symEnt = searchst(code->stringval);

                    if (symEnt->datatype->kind != ARRAYSYM) {
                        asmld(MOVL, sym->offset - stkframesize, reg_num, code->stringval);
                        last_id_reg_num = reg_num;
                    }
                } 


                else {
                    if (bdt != POINTER) {
                        asmld(MOVSD, sym->offset - stkframesize, reg_num, code->stringval);
                        last_id_reg_num = reg_num;

                    }

                    else {
 
                        if ((last_ptr != NULL && strcmp(last_ptr->stringval, code->stringval)) || last_ptr == NULL) {
                            asmld(MOVQ, sym->offset - stkframesize, reg_num, code->stringval);
                            last_ptr_reg_num = reg_num;
                            last_ptr = code;

                        }
                    }
                }
            }
            break;


        case OPERATOR:
            if (first_op_genarith != NULL) {
                nested_refs = true;
            } 
            else {
                first_op_genarith = code;
            }

            lhs_reg = genarith(code->operands);
            rhs_reg = 0;

            if (code->operands->link != NULL) {
                rhs_reg = genarith(code->operands->link);

            } 

            bool same_reg_assn = lhs_reg == rhs_reg;
            if (same_reg_assn) {
                
                lhs_reg = getreg(INTEGER);
                if (rhs_reg > 15) {
                    lhs_reg = getreg(REAL);
                }
            }

            lhs_reg = genop(code, rhs_reg, lhs_reg);
            free_reg(rhs_reg);

            if (same_reg_assn) {
                
                free_reg(lhs_reg);
                int temp = getreg(INTEGER);
                if (lhs_reg > 15) {
                    temp = getreg(REAL);
                }
                lhs_reg = temp;
            }

            reg_num = lhs_reg;

            break;

    }

    first_op_genarith = NULL;

    return reg_num;
}





int genop(TOKEN code, int rhs_reg, int lhs_reg) {
    if (DEBUGGEN) {
        printf(" OPERATOR detected, from genarith().\n");
        printf(" %d %d %d\n", code->whichval, rhs_reg, lhs_reg);
    }

    int out;
    

    switch (code->whichval) {
        case PLUSOP:
            if (at_least_one_float(lhs_reg, rhs_reg)) {
                asmrr(ADDSD, rhs_reg, lhs_reg);
            } else {
                asmrr(ADDL, rhs_reg, lhs_reg);
            }
            out = lhs_reg;
            break;
        case MINUSOP:
            if (lhs_reg > 15 && lhs_reg < NUM_REGS && rhs_reg == 0) {
                asmfneg(lhs_reg, getreg(REAL));
                rhs_reg = lhs_reg;
            } else if (at_least_one_float(lhs_reg, rhs_reg)) {
                asmrr(SUBSD, rhs_reg, lhs_reg);
            } else {
                asmrr(SUBL, rhs_reg, lhs_reg);
            }
            out = lhs_reg;
            break;
        case TIMESOP:
            if (at_least_one_float(lhs_reg, rhs_reg)) {
                asmrr(MULSD, rhs_reg, lhs_reg);
            } else {
                asmrr(IMULL, rhs_reg, lhs_reg);
            }
            out = lhs_reg;
            break;
        case DIVIDEOP:
            if (at_least_one_float(lhs_reg, rhs_reg)) {
                asmrr(DIVSD, rhs_reg, lhs_reg);
            } else {
                asmrr(DIVL, rhs_reg, lhs_reg);
            }
            out = lhs_reg;
            break;
        case EQOP:
            out = nextlabel++;
            asmrr(CMPL, rhs_reg, lhs_reg);
            asmjump(JE, out);
            break;
        case NEOP:
            out = nextlabel++;
            asmrr(CMPQ, rhs_reg, lhs_reg);
            asmjump(JNE, out);
            break;
        case LTOP:
            out = nextlabel++;
            asmrr(CMPL, rhs_reg, lhs_reg);
            asmjump(JL, out);
            break;
        case LEOP:
            out = nextlabel++;
            asmrr(CMPL, rhs_reg, lhs_reg);
            asmjump(JLE, out);
            break;
        case GEOP:
            out = nextlabel++;
            asmrr(CMPL, rhs_reg, lhs_reg);
            asmjump(JGE, out);
            break;
        case GTOP:
            out = nextlabel++;
            asmrr(CMPL, rhs_reg, lhs_reg);
            asmjump(JG, out);
            break;
        case POINTEROP:
            last_ptr_deref_offs = code->link->intval;

            if (nested_ref_stop_at && nested_refs && is_equal(nested_ref_stop_at, code)) {
                asmstr(MOVSD, saved_rhs_reg_num, code->link->intval, lhs_reg, "^. ");
            }

            if (!nested_refs) {
                saved_rhs_reg = code->operands;
            } else {
                saved_rhs_reg = code->link;
            }

            out = lhs_reg;
            break;
        case FUNCALLOP:
            if (inline_funcall) {
                if (num_funcalls_in_curr_tree > 1) {
                    saved_inline_regs[num_inlines_processed] = lhs_reg;
                    num_inlines_processed++;
                    if (num_inlines_processed == 1) {
                        asmcall(inline_funcall->stringval);
                        asmsttemp(lhs_reg);
                    } else if (num_inlines_processed > 0 && num_inlines_processed < num_funcalls_in_curr_tree) {
                        // load and then store?
                    } else {
                        asmcall(inline_funcall->stringval);
                        asmldtemp(lhs_reg);
                    }
                } else if (strcmp(inline_funcall->stringval, "new") == 0) {
                    asmrr(MOVL, rhs_reg, EDI);
                    asmcall(inline_funcall->stringval);
                } else {
                    asmcall(inline_funcall->stringval);
                }

                inline_funcall = NULL;
            } else {
                // ?????????????????????????????
            }

            out = lhs_reg;
            break;

        case AREFOP:
            // printf("AREFOP\n");
            if (saved_float_reg != -DBL_MAX) {
                /* Use MOVSD because saved_float_reg implies floating-point data. */
                asmldr(MOVQ, code->operands->link->intval, lhs_reg, rhs_reg, "^.");
            } else {
                if (last_id_reg_num > -1) {
                    SYMBOL sym;
                    int reg_num, offs;
                    TOKEN lhs = code->operands;

                    if (sym && sym->datatype->kind == ARRAYSYM) {
                        SYMBOL arraysym = sym->datatype;
                        while (arraysym->kind == ARRAYSYM) {
                            arraysym = arraysym->datatype;
                        }
                        if (arraysym->kind == RECORDSYM) {
                            // handle array of records
                        printf("array of records\n");

                            asmimmed(MOVL, code->operands->link->intval, EAX);
                            asmop(CLTQ);
                            offs = sym->offset - stkframesize;
                            if (reg_num >= 0 && reg_num < 16) {
                                asmldr(MOVL, offs, EAX, reg_num, sym->namestring);
                            } else {
                                asmldr(MOVSD, offs, EAX, reg_num, sym->namestring);
                            }
                        }
                    }

                    int temp = rhs_reg;
                    if (last_id_reg_num > -1 && last_id_reg_num < 16) {
                        if (last_id_reg_num == rhs_reg) {
                            rhs_reg = getreg(INTEGER);
                            free_reg(temp);
                        }

                        if (last_ptr && last_ptr_reg_num > -1) {
                            bool found = false;
                            SYMBOL temp0, temp1, temp2, temp3, typsym;
                            temp0 = searchst(last_ptr->stringval);
                            if (!temp0) {
                                return symbol_is_null_int(code->stringval);
                            }

                            temp1 = searchst(temp0->link->namestring);
                            if (!temp1) {
                                return symbol_is_null_int(code->stringval);
                            }

                            if (temp1->datatype->kind == ARRAYSYM) {
                                typsym = temp1->datatype;
                                while (typsym && typsym->kind == ARRAYSYM) {
                                    typsym = typsym->datatype;
                                }
                                if (!typsym) {
                                    return symbol_is_null_int(code->stringval);
                                }

                                temp2 = typsym->datatype;
                                if (temp2 && temp2->kind == RECORDSYM) {
                                    temp3 = temp2->datatype;
                                    while (temp3 && !found) {
                                        if (temp3->offset == last_ptr_deref_offs) {
                                            found = true;
                                            if (temp3->size > basicsizes[INTEGER]) {
                                                /* Use MOVQ for pointer or larger than integer size data */
                                                asmldr(MOVQ, code->operands->link->intval, lhs_reg, rhs_reg, "^.");
                                            } else {
                                                /* Use MOVL for data fitting in an integer */
                                                asmldr(MOVSD, code->operands->link->intval, lhs_reg, rhs_reg, "^.");
                                            }
                                        }
                                        temp3 = temp3->link;
                                    }
                                }
                            }

                            if (!found) {
                                /* Default to MOVQ to handle potentially larger data
                                safely */
                                // printf("code->basicdt: %d\n", code->basicdt);
                                if (code->basicdt == POINTER){
                                    asmldr(MOVQ, code->operands->link->intval, lhs_reg, rhs_reg, "^.");

                                }
                                else{
                                    asmldr(MOVL, code->operands->link->intval, lhs_reg, rhs_reg, "^.");

                                }
                            }

                            last_ptr_reg_num = -1;
                        } else {
                            /* Use MOVL as this seems to handle standard integer data */
                            asmldr(MOVSD, code->operands->link->intval, lhs_reg, rhs_reg, "^.");                        
                        }
                    } else {
                        if (last_id_reg_num == rhs_reg) {
                            rhs_reg = getreg(REAL);
                            free_reg(temp);
                        }
                        /* Use MOVSD for floating-point data */
                        asmldr(MOVSD, code->operands->link->intval, lhs_reg, rhs_reg, "^.");
                    }
                } else {
                    
                    // printf("code->basicdt: %d\n", code->basicdt);
                    if(code->basicdt == 4){
                        asmldr(MOVQ, code->operands->link->intval, lhs_reg, rhs_reg, "^.");

                    }

                    else if (code->basicdt == 1){
                        free_reg(rhs_reg);
                        rhs_reg = getreg(REAL);
                        asmldr(MOVSD, code->operands->link->intval, lhs_reg, rhs_reg, "^.");
                    }
                    else{
                        //its this one

                        asmldr(MOVL, code->operands->link->intval, lhs_reg, rhs_reg, "^.");

                    }

                    
                }
            }

            last_ptr_reg_num = rhs_reg;
            out = rhs_reg;
            break;

    case FLOATOP:
        {
            int freg = getreg(REAL);
            asmfloat(rhs_reg, freg);
            free_reg(lhs_reg);
            free_reg(rhs_reg);
            out = freg;
            break;
        }

    case FIXOP:
        {
            int dreg = getreg(INTEGER);
            asmfix(rhs_reg, dreg);
            free_reg(lhs_reg);
            free_reg(rhs_reg);
            out = dreg;
            break;
        }

    }

    if (inline_funcall != NULL && num_funcalls_in_tree > 0) {
        saved_inline_reg = rhs_reg;
    }

    return out;
}

/* Generate code for a Statement from an intermediate-code form */
void genc(TOKEN code) {

    if (code->tokentype != OPERATOR) {
        if (code->tokentype == NUMBERTOK && code->basicdt == INTEGER && new_funcall_flag) {
            reset_regs();
            new_funcall_flag = false;
            return;
        }
    }

    SYMBOL sym;
    TOKEN tok, lhs, rhs;
    int num, reg_num, offs, which_val;

    reset_regs();
    which_val = code->whichval;

    switch (which_val) {
        case PROGNOP:

            last_ptr = NULL;
            last_ptr_reg_num = -1;
            last_ptr_deref_offs = -1;

            nested_ref_stop_at = NULL;

            int i;
            for (i = 0; i < 10; i++) {
                saved_inline_regs[i] = -1;
            }
            num_inlines_processed = 0;

            last_id_reg_num = -1;

            tok = code->operands;
            while (tok) {
                num_funcalls_in_curr_tree = num_funcalls_in_tree(tok->operands, 0);
                saved_inline_reg = 0;

                if (tok->whichval == LABELOP) {
                    saved_label_num = tok->operands->intval;
                }

                if (search_tree_str(tok, "new")) {
                    new_funcall_flag = true;
                }

                genc(tok);
                tok = tok->link;
            }
            break;

        case ASSIGNOP:
            {
            TOKEN last_operand = NULL;
            TOKEN currentToken = code->operands;
            while (currentToken) {
                TOKEN nextLink = currentToken->link;
                if (!nextLink) {
                    last_operand = currentToken;
                    break;
                }
                currentToken = nextLink;
            }
            last_operand = currentToken;
            TOKEN outer_link = code->operands->link;
            if (last_operand) {
                if (last_operand->basicdt == POINTER && outer_link->tokentype == NUMBERTOK &&
                    outer_link->basicdt == INTEGER && outer_link->intval == 0) {
                    nil_flag = true;
                }
            }

            lhs = code->operands;
            rhs = lhs->link;

            if (code->operands->operands != NULL) {
                nested_ref_stop_at = code->operands->operands;
            }

            reg_num = genarith(rhs);
            saved_rhs_reg = rhs;
            saved_rhs_reg_num = reg_num;

            sym = searchst(lhs->stringval);
            SYMBOL arraysym;
            if (sym && sym->datatype->kind == ARRAYSYM) {
                arraysym = sym->datatype;
                while (arraysym->kind == ARRAYSYM) {
                    arraysym = arraysym->datatype;
                }
                if (arraysym->kind == RECORDSYM) {
                    

                    TOKEN lastLink = lhs->operands;
                    TOKEN currentToken = lhs->operands;
                    while (currentToken) {
                        lastLink = currentToken;
                        currentToken = currentToken->link;
                    }
                    TOKEN last_link = lastLink;
                    
                    if (last_link && last_link->tokentype == NUMBERTOK) {
                        asmimmed(MOVL, last_link->intval, EAX);
                        asmop(CLTQ);
                        if (reg_num >= 0 && reg_num < 16) {
                            asmstrr(MOVL, reg_num, offs, EAX, lhs->stringval);
                        } else {
                            asmstrr(MOVSD, reg_num, offs, EAX, lhs->stringval);
                        }
                    }
                }
            }

            int datatype = code->basicdt;

            if (sym) {
                offs = sym->offset - stkframesize;

                if (reg_num >= 0 && reg_num < 16) {
                    if (lhs->basicdt == 4) {
                        asmst(MOVQ, reg_num, offs, lhs->stringval);
                    } else {
                        asmst(MOVL, reg_num, offs, lhs->stringval);
                    }
                } else {
                    asmst(MOVSD, reg_num, offs, lhs->stringval);
                }
            } else {
                sym = searchst(lhs->operands->stringval);

                if (!sym) {
                    sym = searchst(lhs->operands->operands->stringval);
                    if (sym) {
                        offs = sym->offset - stkframesize;
                        int temp = getreg(INTEGER);

                        last_ptr = lhs->operands->operands;

                        asmld(MOVQ, offs, temp, sym->namestring);
                        offs = lhs->operands->link->intval;

                        if (basicsizes[rhs->basicdt] > basicsizes[INTEGER]) {
                            if (saved_float_reg != -DBL_MAX) {
                                asmstr(MOVSD, reg_num, offs, temp, "^. ");
                            } else {
                                asmstr(MOVQ, reg_num, offs, temp, "^. ");
                            }
                        } else {
                            if (!nil_flag) {
                                asmstr(MOVL, reg_num, offs, temp, "^. ");
                            } else {
                                asmstr(MOVQ, reg_num, offs, temp, "^. ");
                            }
                        }
                    }
                } else {
                    offs = sym->offset - stkframesize;

                    TOKEN lastLink = lhs->operands;
                    TOKEN currentToken = lhs->operands;
                    while (currentToken) {
                        lastLink = currentToken;
                        currentToken = currentToken->link;
                    }
                    TOKEN last_link = lastLink;

                    if (last_link) {
                        if (last_link->tokentype == NUMBERTOK && last_link->basicdt == INTEGER) {
                            asmimmed(MOVL, last_link->intval, EAX);
                            asmop(CLTQ);

                            if (reg_num >= 0 && reg_num < 16) {
                                asmstrr(MOVL, reg_num, offs, EAX, sym->namestring);
                            } else {
                                asmstrr(MOVSD, reg_num, offs, EAX, sym->namestring);
                            }
                        } else if (last_link->tokentype == OPERATOR && last_link->whichval == PLUSOP) {
                            TOKEN plus_operand = last_link->operands;
                            TOKEN mul_operand = plus_operand->link->operands;
                            TOKEN last_operand = mul_operand->link;

                            mark_reg_unused(EAX);
                            mark_reg_used(last_ptr_reg_num);

                            int move_plus_to = getreg(INTEGER);
                            int move_mul_to = getreg(INTEGER);
                            int move_last_to;

                            asmimmed(MOVL, plus_operand->intval, move_plus_to);
                            asmimmed(MOVL, mul_operand->intval, move_mul_to);

                            if (last_operand->tokentype == NUMBERTOK) {
                                move_last_to = getreg(INTEGER);
                                asmimmed(MOVL, last_operand->intval, move_last_to);
                            } else {
                                sym = searchst(last_operand->stringval);
                                offs = sym->offset - stkframesize;
                                asmld(MOVL, offs, EBX, sym->namestring);
                                asmrr(IMULL, EBX, move_mul_to);
                                asmrr(ADDL, move_mul_to, move_plus_to);
                                asmop(CLTQ);
                                sym = searchst(lhs->operands->stringval);
                            offs = sym->offset - stkframesize;
                            asmstrr(MOVL, last_ptr_reg_num, offs, 0, lhs->operands->stringval);
                        }
                    } 
                } else {
                    if (reg_num >= 0 && reg_num < 16) {
                        asmstrr(MOVL, reg_num, offs, getreg(INTEGER), sym->namestring);
                    } 
                    else {
                        asmstrr(MOVSD, reg_num, offs, getreg(INTEGER), sym->namestring);
                    }
                }
            }
        }

        if (lhs->operands) {
            reg_num = genarith(lhs->operands);
        }

        nil_flag = false;
        saved_float_reg = -DBL_MAX;
        saved_rhs_reg = NULL;
        saved_rhs_reg_num = -1;
        nested_refs = false;

        last_ptr = NULL;
        last_ptr_reg_num = -1;

        nested_ref_stop_at = NULL;
        break;
            }
    case GOTOOP:

        lhs = code->operands;
        asmjump(JMP, lhs->intval);
        break;

    case LABELOP:


        lhs = code->operands;
        asmlabel(lhs->intval);
        break;

    case IFOP:

        lhs = code->operands;
        rhs = code->operands->link;
        int if_label_num = genarith(lhs);
        if (rhs->whichval == PROGNOP) {
            if (rhs->link != NULL) {
                asmjump(JMP, saved_label_num);
            }
        }
        asmjump(JMP, nextlabel);
        int else_label_num = nextlabel++;
        asmlabel(if_label_num);
        genc(rhs);
        asmlabel(else_label_num);
        genc(lhs);
        break;

    case FUNCALLOP:

        lhs = code->operands;
        rhs = NULL;

        if (code->operands->link) {
            rhs = code->operands->link;
        }

        SYMBOL argsym;

        if (strstr(lhs->stringval, "write")) {
            sym = searchst(lhs->stringval);

            if (rhs->tokentype == STRINGTOK) {
                asmlitarg(nextlabel, EDI);
                asmcall(lhs->stringval);
                makeblit(rhs->stringval, nextlabel++);
            } else if (rhs->tokentype == OPERATOR) {
                if (rhs->whichval == AREFOP) {
                    sym = searchst(rhs->operands->stringval);
                    if (!sym) {
                        sym = searchst(rhs->operands->operands->stringval);
                        if (sym) {
                            reg_num = getreg(INTEGER);
                            offs = sym->offset - stkframesize;
                            asmld(MOVQ, offs, reg_num, sym->namestring);

                            offs = rhs->operands->link->intval;
                            int temp = getreg(REAL);
                            asmldr(MOVSD, offs, reg_num, temp, "^.");

                            asmcall(lhs->stringval);
                        }
                    }
                } 
            } else if (sym != NULL && (sym->datatype->basicdt == INTEGER || sym->datatype->basicdt == REAL)) {
                SYMBOL argsym;

                if (rhs->tokentype == IDENTIFIERTOK) {
                    argsym = searchst(rhs->stringval);
                    if (!argsym) {
                        return;
                    }

                    if (argsym->basicdt == INTEGER) {
                        reg_num = getreg(INTEGER);
                        offs = argsym->offset - stkframesize;

                        asmld(MOVL, offs, reg_num, argsym->namestring);
                        asmrr(MOVL, reg_num, EDI);
                        asmcall(lhs->stringval);
                    } else if (argsym->basicdt == REAL) {
                        reg_num = getreg(REAL);
                        offs = argsym->offset - stkframesize;
                        asmld(MOVSD, offs, reg_num, argsym->namestring);
                        asmrr(MOVSD, reg_num, EDI);
                        asmcall(lhs->stringval);
                    }
                }
            }
        } else if (strcmp(lhs->stringval, "new") == 0) {
            new_funcall_flag = true;
            num = lhs->intval;
            reg_num = getreg(INTEGER);
            sym = lhs->symentry;
            offs = sym->offset - stkframesize;

            if (num >= MINIMMEDIATE && num <= MAXIMMEDIATE) {
                asmimmed(MOVL, num, reg_num);
            }

            asmrr(MOVL, reg_num, EDI);
        } 
        break;

}
}

void reset_regs() {
    memset(used_regs, 0, sizeof(used_regs));
}

void free_reg(int reg_num) {
    if (reg_num >= 0 && reg_num < NUM_REGS) {
        used_regs[reg_num] = 0;
    }
}

bool at_least_one_float(int lhs_reg, int rhs_reg) {
    return (lhs_reg >= NUM_INT_REGS && lhs_reg < NUM_REGS) ||
           (rhs_reg >= NUM_INT_REGS && rhs_reg < NUM_REGS);
}

void mark_reg_unused(int reg) {
    if (reg >= 0 && reg < NUM_REGS) {
        used_regs[reg] = 0;
    }
}

void mark_reg_used(int reg) {
    if (reg >= 0 && reg < NUM_REGS) {
        used_regs[reg] = 1;
    }
}

int num_funcalls_in_tree(TOKEN tok, int num) {
    if (!tok) {
        return num;
    }
    if (tok->whichval == FUNCALLOP) {
        num++;
    }
    num = num_funcalls_in_tree(tok->link, num);
    num = num_funcalls_in_tree(tok->operands, num);
    return num;
}

bool search_tree_str(TOKEN tok, char str[]) {
    if (!tok) {
        return false;
    }
    if (!strcmp(tok->stringval, str)) {
        return true;
    }
    return search_tree_str(tok->link, str) || search_tree_str(tok->operands, str);
}


int symbol_is_null_int(char *stringValue) {
    if (stringValue) {
        printf("Str not null\n");
    }
    return 0;
}

bool is_equal(TOKEN firstToken, TOKEN secondToken) {
    return firstToken == secondToken;
}