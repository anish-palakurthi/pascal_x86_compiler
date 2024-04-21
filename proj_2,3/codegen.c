/* codgen.c       Generate Assembly Code for x86         15 May 13   */

/* Copyright (c) 2013 Gordon S. Novak Jr. and The University of Texas at Austin
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

/*
 * Last modified: 0242 14-08-14
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include "token.h"
#include "symtab.h"
#include "genasm.h"
#include "codegen.h"
 


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
int saved_float_reg_num = -1;       /* the register where the float in saved_float_reg is stored */

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

void print_used_regs();
int symbol_is_null_int(char *str);

/*  Top-level entry for code generator.
    pcode    = pointer to code:  (program foo (output) (progn ...))
    varsize  = size of local storage in bytes
    maxlabel = maximum label number used so far

    Add this line to the end of your main program:
        gencode(parseresult, blockoffs[blocknumber], labelnumber);
    The generated code is printed out; use a text editor to extract it for
    your .s file.
*/

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
int getreg(int kind) {


    int i = 0;
    int stop = NUM_INT_REGS;
    if (kind !=  INTEGER && kind != POINTER) {

        i = 16;
        stop = NUM_REGS;
    }

    for (; i < stop; i++) {
        if (used_regs[i] == 0) {
            used_regs[i] = 1;
            return i;
        }
    }

    return RBASE;
}

/* Generate code for a function call */
int genfun(TOKEN code) {
    TOKEN tok = code->operands; //FUNCTION
    TOKEN lhs = tok->link;  //FIRST ARGUMENT
    int count = 0;
    while (lhs) {
      genarith(lhs);        
      lhs = lhs->link;
      count ++;
    }

    asmcall(tok->stringval);  
    SYMBOL sym = searchst(tok->stringval);

    if (DEBUGGEN) {
      printf("genfunc\n");
      printf("no of arguments: %d", count);
      dbugprinttok(code);
    }
    if (sym->datatype->basicdt == REAL) {
      return XMM0;
    } else if (sym->datatype->basicdt == INTEGER) {
      return EAX;
    } else {
      return RAX;
    }
}


/* Trivial version */
/* Generate code for arithmetic expression, return a register number */
int genarith(TOKEN code) {

    if (DEBUGGEN) {
        printf("\nIn genarith()\n");
//        dbugprinttok(code);
        ppexpr(code);
        printf("\n");
    }

    int num, reg_num, lhs_reg, rhs_reg;
    SYMBOL sym;

    if (code->tokentype == NUMBERTOK) {
        if (code->basicdt == INTEGER) {
            num = code->intval;
            reg_num = getreg(INTEGER);

            if (num >= MINIMMEDIATE && num <= MAXIMMEDIATE && !nested_refs) {
                if (last_ptr && last_ptr_reg_num > -1) {

                    // asmimmed(MOVQ, num, last_ptr_reg_num);
                    asmimmed(MOVQ, num, reg_num);
                    last_ptr_reg_num = -1;
                }
                else if (!nil_flag) {
                    asmimmed(MOVL, num, reg_num);
                }
                else {
                    asmimmed(MOVQ, num, reg_num);
                }

            }
            else {
                // ?????????????????????????????????????????????????????????????????
            }

        }
        else {
            /* Generate literal for the value of the constant, then
               load the literal into a register. */

            reg_num = getreg(REAL);
            saved_float_reg = code->realval;
            saved_float_reg_num = reg_num;

            makeflit(code->realval, nextlabel);
            asmldflit(MOVSD, nextlabel++, reg_num);
        }
    }
    
    else if (code->tokentype == IDENTIFIERTOK) {

        sym = searchst(code->stringval);
        if (!sym) {
            return symbol_is_null_int(code->stringval);
        }

        if (DEBUGGEN) {
            printf(" IDENTIFIERTOK detected; symbol table entry:\n");
            ppexpr(code);
            dbprsymbol(sym);
            printf(" offset: %d\n", sym->offset);
            printf("\n");
        }

        num = sym->offset;

        if (sym->kind == FUNCTIONSYM) {
            reg_num = getreg(sym->datatype->basicdt);
            inline_funcall = code;
            genc(code->link);
        }

        else {

            reg_num = getreg(code->basicdt);
            if (reg_num < NUM_INT_REGS && code->basicdt != POINTER) {

                SYMBOL temp = searchst(code->stringval);
                if (!temp) {
                    return symbol_is_null_int(code->stringval);
                }

                SYMBOL next = temp->datatype;

                if (!next) {
                    return symbol_is_null_int(NULL);
                }

                if (next->kind != ARRAYSYM) {
                    last_id_reg_num = reg_num;
                    asmld(MOVL, sym->offset - stkframesize, reg_num, code->stringval);
                }

            }
            else {
                if (code->basicdt == POINTER) {

                    if (last_ptr == NULL) {
                        last_ptr = code;
                        last_ptr_reg_num = reg_num;
                        asmld(MOVQ, sym->offset - stkframesize, reg_num, code->stringval);
                    }

                    else if (last_ptr != NULL && strcmp(last_ptr->stringval, code->stringval) != 0) {
                        last_ptr = code;
                        last_ptr_reg_num = reg_num;
                        asmld(MOVQ, sym->offset - stkframesize, reg_num, code->stringval);
                    }
                }

                else {
                    last_id_reg_num = reg_num;
                    asmld(MOVSD, sym->offset - stkframesize, reg_num, code->stringval);
                }
            }       
        }

    }
    else if (code->tokentype == OPERATOR) {
        // ppexpr(code);
        // printf("\n");
        // printf("code->stringval: %s\n", code->stringval);
        // printf("code->operands->stringval: %s\n", code->operands->stringval);
        if (code->whichval == FUNCALLOP && strcmp(code->operands->stringval, "new") != 0) {
            free_reg(lhs_reg);

            return genfun(code);
        }
        if (first_op_genarith == NULL) {
            first_op_genarith = code;
        }
        else {
            nested_refs = true;
        }

        lhs_reg = genarith(code->operands);

        if (code->operands->link) {
            rhs_reg = genarith(code->operands->link);
        }
        else {
            // FLOATOP (and possibly FIXOP?)
            rhs_reg = 0;
        }

        if (code->operands->whichval == FUNCALLOP) {

            free_reg(lhs_reg);
            lhs_reg = saved_inline_regs[num_inlines_processed - 1];
            mark_reg_used(lhs_reg);
        }
        if (code->operands->link) {
            if (code->operands->link->whichval == FUNCALLOP) {

                free_reg(rhs_reg);
                rhs_reg = saved_inline_regs[num_inlines_processed - 2];
                mark_reg_used(rhs_reg);
            }
        }

        bool same_reg_assn = false;
        if (lhs_reg == rhs_reg) {
            same_reg_assn = true;
            if (rhs_reg > 15) {
                lhs_reg = getreg(REAL);
            }
            else {
                lhs_reg = getreg(INTEGER);
            }
        }

        lhs_reg = genop(code, rhs_reg, lhs_reg);
        free_reg(rhs_reg);

        if (same_reg_assn) {
            int temp;
            if (lhs_reg > 15) {
                free_reg(lhs_reg);
                temp = getreg(REAL);
            }
            else {
                free_reg(lhs_reg);
                temp = getreg(INTEGER);
            }
            lhs_reg = temp;
        }

        reg_num = lhs_reg;
    }
    else { 
        return symbol_is_null_int(NULL);
    }

    first_op_genarith = NULL;

    return reg_num;
}

/* Gets and returns the last TOKEN (in)directly
   connected via ->link to TOKEN tok. Mostly used 
   to handle elimination of nested progns. */
TOKEN get_last_link(TOKEN tok) {
	if (!tok) {
		return NULL;
	}

	TOKEN curr = tok;
	TOKEN curr_link = curr->link;
	while (curr_link) {
		curr = curr_link;
		curr_link = curr_link->link;
	}

	return curr;
}

/* Gets and returns the last TOKEN (in)directly
   connected via ->operands to TOKEN tok. */
TOKEN get_last_operand(TOKEN tok) {
	if (!tok) {
		return NULL;
	}

	TOKEN curr = tok;
	TOKEN curr_operand = curr->operands;
	while (curr_operand) {
		curr = curr_operand;
		curr_operand = curr_operand->operands;
	}

	return curr;	
}
int genop(TOKEN code, int rhs_reg, int lhs_reg) {

    if (DEBUGGEN) {
        printf(" OPERATOR detected, from genarith().\n");
//        printf(" %s\n", opprint[which_val]);
        printf(" %d %d %d\n", code->whichval, rhs_reg, lhs_reg);
    }

    int out = 0;
    int which_val = code->whichval;

    if (which_val == PLUSOP) {
        if (at_least_one_float(lhs_reg, rhs_reg)) {
            asmrr(ADDSD, rhs_reg, lhs_reg);
        }
        else {
            asmrr(ADDL, rhs_reg, lhs_reg);
        }
        out = lhs_reg;
    }
    else if (which_val == MINUSOP) {
        // printf("MINUSOP\n");
        
        //left hand is a float register? maybe when minusop is used a negative sign
        if (lhs_reg > 15 && lhs_reg < NUM_REGS && rhs_reg == 0) {
            // printf("NEGATE\n");

            asmfneg(lhs_reg, getreg(REAL));
            rhs_reg = lhs_reg;
        }
        else if (at_least_one_float(lhs_reg, rhs_reg)) {
            // printf("SUBSD\n");
            asmrr(SUBSD, rhs_reg, lhs_reg);
        }
        else {
            // printf("SUBL\n");

            asmrr(SUBL, rhs_reg, lhs_reg);
        }
        out = lhs_reg;
    }
    else if (which_val == TIMESOP) {
        if (at_least_one_float(lhs_reg, rhs_reg)) {
            asmrr(MULSD, rhs_reg, lhs_reg);
        }
        else {
            asmrr(IMULL, rhs_reg, lhs_reg);
        }
        out = lhs_reg;
    }
    else if (which_val == DIVIDEOP) {
        if (at_least_one_float(lhs_reg, rhs_reg)) {
            asmrr(DIVSD, rhs_reg, lhs_reg);
        }
        else {
            asmrr(DIVL, rhs_reg, lhs_reg);
        }
        out = lhs_reg;
    }
    else if (which_val == EQOP) {
        out = nextlabel++;
        asmrr(CMPL, rhs_reg, lhs_reg);
        asmjump(JE, out);
    }
    else if (which_val == NEOP) {
        out = nextlabel++;
        asmrr(CMPQ, rhs_reg, lhs_reg);
        asmjump(JNE, out);
    }
    else if (which_val == LTOP) {
        out = nextlabel++;
        asmrr(CMPL, rhs_reg, lhs_reg);
        asmjump(JL, out);
    }
    else if (which_val == LEOP) {
        out = nextlabel++;
        asmrr(CMPL, rhs_reg, lhs_reg);
        asmjump(JLE, out);
    }
    else if (which_val == GEOP) {
        out = nextlabel++;
        asmrr(CMPL, rhs_reg, lhs_reg);
        asmjump(JGE, out);
    }
    else if (which_val == GTOP) {
        out = nextlabel++;
        asmrr(CMPL, rhs_reg, lhs_reg);
        asmjump(JG, out);
    }
    else if (which_val == POINTEROP) {
        last_ptr_deref_offs = code->link->intval;

        if (nested_ref_stop_at && nested_refs && is_equal(nested_ref_stop_at, code)) {
            asmstr(MOVSD, saved_rhs_reg_num, code->link->intval, lhs_reg, "^. ");
        }

        if (!nested_refs) {
            saved_rhs_reg = code->operands;
        }
        else {
            saved_rhs_reg = code->link;
        }

        out = lhs_reg;
    }
    else if (which_val == FUNCALLOP) {
        if (inline_funcall) {

            if (num_funcalls_in_curr_tree > 1) {
                saved_inline_regs[num_inlines_processed] = saved_inline_reg;
                num_inlines_processed++;
                if (num_inlines_processed == 1) {
                    asmcall(inline_funcall->stringval);
                    asmsttemp(saved_inline_reg);
                }
                else if (num_inlines_processed > 0 && num_inlines_processed < num_funcalls_in_curr_tree) {
                    // load and then store?
                }
                else {
                    asmcall(inline_funcall->stringval);
                    asmldtemp(saved_inline_reg);
                }               
            }
            else if (strcmp(inline_funcall->stringval, "new") == 0) {
                asmrr(MOVL, rhs_reg, EDI);
                asmcall(inline_funcall->stringval);
            }
            else {
                asmcall(inline_funcall->stringval);
            }

            inline_funcall = NULL;
        }
        else {
            // ?????????????????????????????
        }

        out = lhs_reg;
    }
else if (which_val == AREFOP) {
    if (saved_float_reg != -DBL_MAX) {
        /* Use MOVSD because saved_float_reg implies floating-point data. */
        asmldr(MOVQ, code->operands->link->intval, lhs_reg, rhs_reg, "^.");
    } else {
        if (last_id_reg_num > -1) {
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
                        if (code->basicdt == 4){
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
            // free_reg(rhs_reg);
            // rhs_reg = getreg(REAL);
            /* Use MOVSD as a default when no information about the data type is available */
            //asmldr(MOVSD, code->operands->link->intval, lhs_reg, rhs_reg,
            //"^.");
            
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
}

    else if (which_val == FLOATOP) {
        int freg = getreg(REAL);
        asmfloat(rhs_reg, freg);
        free_reg(lhs_reg);
        free_reg(rhs_reg);
        out = freg;
    }
    else if (which_val == FIXOP) {
        int dreg = getreg(INTEGER);
        asmfix(lhs_reg, dreg);
        free_reg(lhs_reg);
        free_reg(rhs_reg);
        out = dreg;
    }

    if (inline_funcall != NULL && num_funcalls_in_tree > 0) {
        saved_inline_reg = rhs_reg;
    }

    return out;
}

/* Generate code for a Statement from an intermediate-code form */
void genc(TOKEN code) {

    if (DEBUGGEN) {
        printf("\nIn genc()\n");
        ppexpr(code);
//        dbugprinttok(code);
        printf("\n");
    }
    if (code->tokentype != OPERATOR) {
        if (code->tokentype == NUMBERTOK && code->basicdt == INTEGER && new_funcall_flag) {
            reset_regs();
            new_funcall_flag = false;
            return;
        }
        printf("\tError: bad code token! (genc())\n");
        dbugprinttok(code);
        printf("\n");
    }

    SYMBOL sym;
    TOKEN tok, lhs, rhs;
    int num, reg_num, offs, which_val;

    reset_regs();
    which_val = code->whichval;

    if (which_val == PROGNOP) {

        if (DEBUGGEN) {
            printf(" PROGNOP detected.\n");
            ppexpr(code->operands);
            printf("\n");
        }

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
            saved_inline_reg = 0;       // may need to set to -1 as sentinel value

            if (tok->whichval == LABELOP) {
                saved_label_num = tok->operands->intval;
            }

            if (search_tree_str(tok, "new")) {
                new_funcall_flag = true;
            }

            genc(tok);
            tok = tok->link;
        }
    }
    else if (which_val == ASSIGNOP) {
        /* Generate the RHS into a register using genarith().
           Then store the register into the location specified
           by the LHS. */

        if (DEBUGGEN) {
            printf("\n ASSIGNOP detected.\n");
            ppexpr(code);
            printf("#####\n");
            ppexpr(code->operands);
            printf("\n");
        }

        TOKEN last_operand = get_last_operand(code);
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

        reg_num = genarith(rhs);                        /* generate rhs into a register */
        saved_rhs_reg = rhs;
        saved_rhs_reg_num = reg_num;

        sym = searchst(lhs->stringval);

        int datatype = code->basicdt;                  /* store value into lhs  */

        if (sym) {

            offs = sym->offset - stkframesize;          /* net offset of the var   */

            if (reg_num >= 0 && reg_num < 16) {
                if (lhs->basicdt == 4) { 
                    asmst(MOVQ, reg_num, offs, lhs->stringval);
                }
                else {
                    asmst(MOVL, reg_num, offs, lhs->stringval);
                }
            }
            else {
                asmst(MOVSD, reg_num, offs, lhs->stringval);
            }
        }
        else {

            sym = searchst(lhs->operands->stringval);

            if (!sym) {
                sym = searchst(lhs->operands->operands->stringval);
                if (sym) {

                    offs = sym->offset - stkframesize;
                    int temp = getreg(INTEGER);

                    last_ptr = lhs->operands->operands; // ??????????????????????????????????????????????????????????????????

                    asmld(MOVQ, offs, temp, sym->namestring);
                    offs = lhs->operands->link->intval;

                    if (basicsizes[rhs->basicdt] > basicsizes[INTEGER]) {
                        // see third line in L1 for pasrec
                        if (saved_float_reg != -DBL_MAX) {
                            asmstr(MOVSD, reg_num, offs, temp, "^. ");
                            // saved_float_reg = -DBL_MAX;
                        }
                        else {
                           asmstr(MOVQ, reg_num, offs, temp, "^. ");
                        }
                    }
                    else {
                        if (!nil_flag) {     //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                            asmstr(MOVL, reg_num, offs, temp, "^. ");
                        }
                        else {
                            asmstr(MOVQ, reg_num, offs, temp, "^. ");
                            // nil_flag = false;
                        }
                    }

                }
                else {
                    // printf("\nEMPTY ELSE\n");
                }
            }
            else {

                offs = sym->offset - stkframesize;

                TOKEN last_link = get_last_link(lhs->operands);
                // printf("not not executing yet\n");

                if (last_link) {
                    // printf("Not executing yet\n");
                    if (last_link->tokentype == NUMBERTOK && last_link->basicdt == INTEGER) {
                        // printf("executing array reference\n");
                        asmimmed(MOVL, last_link->intval, EAX);
                        asmop(CLTQ);

                        if (reg_num >= 0 && reg_num < 16) {
                            asmstrr(MOVL, reg_num, offs, EAX, sym->namestring);
                        }
                        else {
                            asmstrr(MOVSD, reg_num, offs, EAX, sym->namestring);
                        }

                    }
                    else if (last_link->tokentype == OPERATOR && last_link->whichval == PLUSOP) {
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
                        }
                        else {
                            sym = searchst(last_operand->stringval);
                            offs = sym->offset - stkframesize;          // NOT NULL CHECKED !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                            asmld(MOVL, offs, EBX, sym->namestring);    // CONTENTS AREN'T ACTUALLY IN CALLEE-SAVE REG EBX (SEE last_ptr_reg_num)
                            asmrr(IMULL, EBX, move_mul_to);
                            asmrr(ADDL, move_mul_to, move_plus_to);
                            asmop(CLTQ);

                            sym = searchst(lhs->operands->stringval);
                            offs = sym->offset - stkframesize;          // NOT NULL CHECKED !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                            asmstrr(MOVL, last_ptr_reg_num, offs, 0, lhs->operands->stringval);
                        }
                    }
                    else {
                        // ?????????????????????????????????????????????????????????????????????????????
                    }
                }
                else {
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

    }
    else if (which_val == GOTOOP) {
        /* Generate a branch to the label number (see genasm.c). */

        if (DEBUGGEN) {
            printf(" GOTOOP detected.\n");
            ppexpr(code->operands);
            printf("\n");
        }

        lhs = code->operands;
        asmjump(JMP, lhs->intval);

    }
    else if (which_val == LABELOP) {
        /* Generate a label with the label number (see genasm.c). */

        if (DEBUGGEN) {
            printf(" LABELOP detected.\n");
            ppexpr(code->operands);
            printf("\n");
        }

        lhs = code->operands;
        asmlabel(lhs->intval);

    }
    else if (which_val == IFOP) {
        /* See S207. */

        if (DEBUGGEN) {
            printf(" IFOP detected.\n");
            ppexpr(code->operands);
            printf("\n");
        }

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
        // genc() for else crap?

    }
    else {  // which_val == FUNCALLOP
        /* Compile short intrinsic functions inline.
           For others, generate subroutine calls. */

        if (DEBUGGEN) {
            printf(" FUNCALLOP detected.\n");
            ppexpr(code);
            ppexpr(code->operands);
            ppexpr(code->operands->link);
            printf("\n");
        }

        lhs = code->operands;
        rhs = code->operands->link;
        SYMBOL argsym;

        if (strstr(lhs->stringval, "write")) {      // != NULL
            sym = searchst(lhs->stringval);

            if (rhs->tokentype == STRINGTOK) {
                asmlitarg(nextlabel, EDI);
                asmcall(lhs->stringval);
                makeblit(rhs->stringval, nextlabel++);
            }

            else if (rhs->tokentype == OPERATOR) {
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

                else if (rhs->whichval == POINTEROP) {
                    printf("\nPTROP UNFINISHED\n");
                }
            }

            else if (sym != NULL && (sym->datatype->basicdt == INTEGER ||
                sym->datatype->basicdt == REAL)) {
                
                SYMBOL argsym;

                if (rhs->tokentype == NUMBERTOK) {
                    printf("\nNUMBERTOK UNFINISHED\n");
                }             

                else if (rhs->tokentype == IDENTIFIERTOK) {
                    argsym = searchst(rhs->stringval);
                    if (!argsym) {
                        printf("Error: no symbol table entry for var \"%s\"", rhs->stringval);
                        return;
                    }

                    if (argsym->basicdt == INTEGER) {
                        reg_num = getreg(INTEGER);
                        offs = argsym->offset - stkframesize;

                        asmld(MOVL, offs, reg_num, argsym->namestring);
                        asmrr(MOVL, reg_num, EDI);
                        asmcall(lhs->stringval);
                    }

                    else if (argsym->basicdt == REAL) {
                        reg_num = getreg(REAL);
                        offs = argsym->offset - stkframesize;
                        asmld(MOVSD, offs, reg_num, argsym->namestring);
                        asmrr(MOVSD, reg_num, EDI);
                        asmcall(lhs->stringval);
                    }
                }
            }
        }

        else if (strcmp(lhs->stringval, "new") == 0) {
            new_funcall_flag = true;
            num = lhs->intval;
            reg_num = getreg(INTEGER);  // ???
            sym = lhs->symentry;
            offs = sym->offset - stkframesize;

            if (num >= MINIMMEDIATE && num <= MAXIMMEDIATE) {
                asmimmed(MOVL, num, reg_num);
            }

            asmrr(MOVL, reg_num, EDI);
               
        }
        else {
            
        }
        // else ALL OTHERS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    }

}   // genc() end
















/* ##################################################################################################################################### */

void reset_regs() {
    int i;
    for (i = 0; i < NUM_REGS; i++) {
        used_regs[i] = 0;
    }
}

void free_reg(int reg_num) {
    if (reg_num < 0 || reg_num >= NUM_REGS) {
        // printf("Error: cannot free register number %d\n", reg_num);
        return;
    }
    used_regs[reg_num] = 0;
}

bool at_least_one_float(int lhs_reg, int rhs_reg) {
    if ((lhs_reg >= NUM_INT_REGS && lhs_reg < NUM_REGS) || 
        (rhs_reg >= NUM_INT_REGS && rhs_reg < NUM_REGS)) {
        return true;
    }
    return false;
}

bool both_float(int lhs_reg, int rhs_reg) {
    if ((lhs_reg >= NUM_INT_REGS && lhs_reg < NUM_REGS) &&
        (rhs_reg >= NUM_INT_REGS && rhs_reg < NUM_REGS)) {
        return true;
    }
    return false;
}

void mark_reg_unused(int reg_num) {
    if (reg_num < 0 || reg_num >= NUM_REGS) {
        printf("Error: register %d out of bounds\n", reg_num);
        return;
    }
    used_regs[reg_num] = 0;
}

void mark_reg_used(int reg_num) {
    if (reg_num < 0 || reg_num >= NUM_REGS) {
        printf("Error: register %d out of bounds\n", reg_num);
        return;
    }
    used_regs[reg_num] = 1;    
}

/* test if there is a function call within code: 1 if true, else 0 */
bool funcallin(TOKEN code) {
    int num = num_funcalls_in_tree(code, 0);
    if (num > 0) {
        return true;
    }
    return false;
}

int num_funcalls_in_tree(TOKEN tok, int num) {
    if (tok == NULL) {
        return num;
    }

    if (tok->whichval == FUNCALLOP) {
//        ppexpr(tok);
        num++;
    }
    if (tok->link != NULL) {
        num = num_funcalls_in_tree(tok->link, num);
    }
    if (tok->operands != NULL) {
        num = num_funcalls_in_tree(tok->operands, num);
    }

    return num;
}

bool search_tree_str(TOKEN tok, char str[]) {
    if (tok == NULL) {
        return false;
    }

//    dbugprinttok(tok);

    bool found = false;

    if (strcmp(tok->stringval, str) == 0) {
        return true;
    }
    if (tok->link != NULL) {
        found = search_tree_str(tok->link, str);
    }
    if (tok->operands != NULL) {
        found = search_tree_str(tok->operands, str);
    }

    return found;
}

void print_used_regs() {
    printf("\nUsed registers: %d", used_regs[0]);
    
    int i;
    for (i = 1; i < NUM_REGS; i++) {
        printf(" %d", used_regs[i]);
    }
    printf("\n\n");
}

int symbol_is_null_int(char *str) {
    if (str) {
        printf("Error: NULL symbol (\"%s\")\n", str);
    }
    return 0;
}

bool is_equal(TOKEN a, TOKEN b) {
    if (!a || !b) {
        return false;
    }

    if ((long) a == (long) b) {
        return true;
    }
    return false;
}

bool is_gen_purpose_reg(int reg_num) {
    if (reg_num < 0 || reg_num >= NUM_INT_REGS) {
        return false;
    }
    return true;
}

bool is_fp_reg(int reg_num) {
    if (reg_num < NUM_INT_REGS || reg_num >= NUM_REGS) {
        return false;
    }
    return true;
}