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

#define I_REGS 8
#define TOT_REGS 32
#define NUM_REGS        32

// Register array initialization for integer and floating-point registers
int registers[TOT_REGS] = {0};

// Token for function calls, specifically in right-hand side of ASSIGNOP
TOKEN inline_call = NULL;

// Flags to indicate specific conditions during operations
bool funcFlag = false;         // Indicates if FUNCALLOP is for "new"
bool nilFlag = false;          // Indicates NUMBERTOK assignment of zero to a pointer
bool nestRefs = false;         // Legacy flag, usage under review

// Handling of labels and function calls within tree structures
int numTreeCalls;              // Counts function calls within a tree
int numLinesProcs;             // Processes lines within structured blocks
int savedLineReg;              // Temporary storage for current line's register
int savedLineRegs[10];         // Array to save registers across multiple lines
int labelNum = -1;             // Top-level label number for control structures

// Assignments and operations involving pointers and identifiers
TOKEN rhsReg = NULL;           // TOKEN for the right-hand side in ASSIGNOP
int rhsReg_num = -1;           // Register number for rhsReg
double floatReg = -DBL_MAX;    // Floating-point register for ASSIGNOP

// Pointer dereferencing within operations
TOKEN opGenarith = NULL;       // Indicates multiple pointer dereferences
TOKEN stopRef = NULL;          // Marks the penultimate pointer dereference in AREFOP
TOKEN finalPtr = NULL;         // Last pointer referenced in any statement
int finalPtr_reg_num;          // Register number for finalPtr
int finalPtr_deref_offs;       // Offset for field dereferenced by finalPtr

// Register tracking for the last non-pointer identifier referenced
int lastIdReg;                 // Register number of the last identifier referenced (excluding pointers)



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
        stop = I_REGS;
    } else {
        start = 16;
        stop = TOT_REGS;
    }

    // Search for an unused register within the specified range
    for (int i = start; i < stop; i++) {
        if (registers[i] == 0) {
            registers[i] = 1;
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

                if (num >= MINIMMEDIATE && num <= MAXIMMEDIATE && !nestRefs) {
                    if (finalPtr && finalPtr_reg_num > -1) {
                        asmimmed(MOVQ, num, reg_num);
                    } else {
                        asmimmed(nilFlag ? MOVQ : MOVL, num, reg_num);
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
                inline_call = code;
                genc(code->link);
            } 
            
            else {
                int bdt = code->basicdt;
                reg_num = getreg(bdt);

                if (code->basicdt != POINTER && I_REGS > reg_num) {
                    SYMBOL symEnt = searchst(code->stringval);

                    if (symEnt->datatype->kind != ARRAYSYM) {
                        asmld(MOVL, sym->offset - stkframesize, reg_num, code->stringval);
                        lastIdReg = reg_num;
                    }
                } 


                else {
                    if (bdt != POINTER) {
                        asmld(MOVSD, sym->offset - stkframesize, reg_num, code->stringval);
                        finalPtr_reg_num = reg_num;

                    }

                    else {
 
                        if ((finalPtr != NULL && strcmp(finalPtr->stringval, code->stringval)) || finalPtr == NULL) {
                            asmld(MOVQ, sym->offset - stkframesize, reg_num, code->stringval);
                            finalPtr_reg_num = reg_num;
                            finalPtr = code;

                        }
                    }
                }
            }
            break;


        case OPERATOR:
            if (opGenarith != NULL) {
                nestRefs = true;
            } 
            else {
                opGenarith = code;
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

    opGenarith = NULL;

    return reg_num;
}




int genop(TOKEN code, int rhs_reg, int lhs_reg) {

    int out;
    
    switch (code->whichval) {
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
        case PLUSOP:
            if (at_least_one_float(lhs_reg, rhs_reg)) {
                asmrr(ADDSD, rhs_reg, lhs_reg);
            } else {
                asmrr(ADDL, rhs_reg, lhs_reg);
            }
            out = lhs_reg;
            break;
        case MINUSOP:
            if (lhs_reg > 15 && lhs_reg < TOT_REGS && rhs_reg == 0) {
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
        case POINTEROP:
            finalPtr_deref_offs = code->link->intval;

            if (stopRef && nestRefs && is_equal(stopRef, code)) {
                asmstr(MOVSD, rhsReg_num, code->link->intval, lhs_reg, "^. ");
            }

            if (!nestRefs) {
                rhsReg = code->operands;
            } else {
                rhsReg = code->link;
            }

            out = lhs_reg;
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

        case FUNCALLOP:
            if (inline_call) {
                if (numTreeCalls > 1) {
                    savedLineRegs[numLinesProcs] = lhs_reg;
                    numLinesProcs++;
                    if (numLinesProcs == 1) {
                        asmcall(inline_call->stringval);
                        asmsttemp(lhs_reg);
                    } 
                     else {
                        asmcall(inline_call->stringval);
                        asmldtemp(lhs_reg);
                    }
                } else if (strcmp(inline_call->stringval, "new") == 0) {
                    asmrr(MOVL, rhs_reg, EDI);
                    asmcall(inline_call->stringval);
                } else {
                    asmcall(inline_call->stringval);
                }

                inline_call = NULL;
            }

            out = lhs_reg;
            break;

        case AREFOP:
            if (floatReg != -DBL_MAX) {
                /* Use MOVSD because floatReg implies floating-point data. */
                asmldr(MOVQ, code->operands->link->intval, lhs_reg, rhs_reg, "^.");
            } else {
                if (lastIdReg > -1) {
                    SYMBOL sym;
                    int reg_num, offs;
                    TOKEN lhs = code->operands;

                    if (sym && sym->datatype->kind == ARRAYSYM) {
                        SYMBOL arraysym = sym->datatype;
                        while (arraysym->kind == ARRAYSYM) {
                            arraysym = arraysym->datatype;
                        }
                        if (arraysym->kind == RECORDSYM) {

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
                    if (lastIdReg > -1 && lastIdReg < 16) {
                        if (lastIdReg == rhs_reg) {
                            rhs_reg = getreg(INTEGER);
                            free_reg(temp);
                        }

                        if (finalPtr && finalPtr_reg_num > -1) {
                            bool found = false;
                            SYMBOL temp0, temp1, temp2, temp3, typsym;
                            temp0 = searchst(finalPtr->stringval);


                            temp1 = searchst(temp0->link->namestring);


                            if (temp1->datatype->kind == ARRAYSYM) {
                                typsym = temp1->datatype;
                                while (typsym && typsym->kind == ARRAYSYM) {
                                    typsym = typsym->datatype;
                                }


                                temp2 = typsym->datatype;
                                if (temp2 && temp2->kind == RECORDSYM) {
                                    temp3 = temp2->datatype;
                                    while (temp3 && !found) {
                                        if (temp3->offset == finalPtr_deref_offs) {
                                            found = true;
                                            if (temp3->size > basicsizes[INTEGER]) {
                                                /* Use MOVQ for pointer or larger than integer size data */
                                                asmldr(MOVQ, code->operands->link->intval, lhs_reg, rhs_reg, "^.");
                                            } 
                                            else {
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
                                if (code->basicdt == POINTER){
                                    asmldr(MOVQ, code->operands->link->intval, lhs_reg, rhs_reg, "^.");
                                }
                                else{
                                    asmldr(MOVL, code->operands->link->intval, lhs_reg, rhs_reg, "^.");
                                }
                            }

                            finalPtr_reg_num = -1;
                        } 

                        else {
                            /* Use MOVL as this seems to handle standard integer data */
                            asmldr(MOVSD, code->operands->link->intval, lhs_reg, rhs_reg, "^.");                        
                        }
                    } 
                    
                    else {
                        if (lastIdReg == rhs_reg) {
                            rhs_reg = getreg(REAL);
                            free_reg(temp);
                        }
                        /* Use MOVSD for floating-point data */
                        asmldr(MOVSD, code->operands->link->intval, lhs_reg, rhs_reg, "^.");
                    }
                } else {
                    
                    if(code->basicdt == POINTER){
                        asmldr(MOVQ, code->operands->link->intval, lhs_reg, rhs_reg, "^.");
                    }

                    else if (code->basicdt == REAL){
                        free_reg(rhs_reg);
                        rhs_reg = getreg(REAL);
                        asmldr(MOVSD, code->operands->link->intval, lhs_reg, rhs_reg, "^.");
                    }
                    else{
                        asmldr(MOVL, code->operands->link->intval, lhs_reg, rhs_reg, "^.");
                    }
                    
                }
            }

            finalPtr_reg_num = rhs_reg;
            out = rhs_reg;
            break;



    }

    return out;
}

/* Generate code for a Statement from an intermediate-code form */
void genc(TOKEN code) {

    if (code->tokentype != OPERATOR && (funcFlag && code->tokentype == NUMBERTOK && code->basicdt == INTEGER )) {
            reset_regs();
            return;
        }
    

    SYMBOL sym;
    TOKEN tok, lhs, rhs;
    int num, reg_num, offs;

    reset_regs();


    switch (code->whichval) {
        case GOTOOP:

            lhs = code->operands;
            asmjump(JMP, lhs->intval);
            break;

        case LABELOP:


            lhs = code->operands;
            asmlabel(lhs->intval);
            break;

        case IFOP:
{
            TOKEN lhs = code->operands;
            TOKEN rhs = code->operands->link;

            // Generate code for the left-hand side expression, which typically is the condition.
            int ifNum = genarith(lhs);

            // Check if the right-hand side is a PROGNOP, which might indicate a structured block of statements.
            if (rhs->link != NULL && rhs->whichval == PROGNOP) {
                // Jump to a saved label if the right side is PROGNOP and has a continuation.
                asmjump(JMP, labelNum);
            }

            // Generate a jump to the else label which will be defined next.
            asmjump(JMP, nextlabel);
            

            // Label the start of the 'if' block code
            asmlabel(ifNum);

            // Generate code for the right-hand side statement (consequent)
            genc(rhs);

            // Label the start of the 'else' block code
            asmlabel(nextlabel++);

            // Generate code for the left-hand side again, typically this might be redundant unless `lhs` has side effects.
            genc(lhs);

            break;
}
            
        case PROGNOP:

            // Reset tracking variables to initial values
            finalPtr_reg_num = -1;
            lastIdReg = -1;

            // Initialize saved inline registers to -1
            for (int i = 0; i < 10; i++) {
                savedLineRegs[i] = -1;
            }

            // Iterate over each token in the operands of the code
            TOKEN tok = code->operands;
            while (tok) {
                // Initialize count of function calls within this token's operands
                int numTreeCalls = 0;
                for (TOKEN temp_tok = tok->operands; temp_tok; temp_tok = temp_tok->link) {
                    if (temp_tok->whichval == FUNCALLOP) {
                        numTreeCalls++;
                    }
                }
                
                // Only search for "new" if it's necessary based on the context or previous results
                funcFlag = false;  // Reset flag for each token processed
                if (numTreeCalls > 0) {  // Only check for "new" if there are function calls
                    for (TOKEN search_tok = tok; search_tok; search_tok = search_tok->link) {
                        if (search_tree_str(search_tok, "new")) {  // Ensure to pass search_tok instead of tok
                            funcFlag = true;
                            break;  // Exit the loop early once "new" is found
                        }
                    }
                }

                // Handle specific label operations
                if (tok->whichval == LABELOP && tok->operands) {
                    labelNum = tok->operands->intval;
                }

                genc(tok);  // Generate code for the current token
                tok = tok->link;  // Proceed to the next token in the list
            }


            break;


            
        case FUNCALLOP:

            lhs = code->operands;
            rhs = NULL;

            if (code->operands->link) {
                rhs = code->operands->link;
            }

            SYMBOL argsym;
            if (strcmp(lhs->stringval, "new") == 0) {
                funcFlag = true;  // Flag indicating 'new' function call

                // Obtain and initialize the required register and offset for the operation
                int reg_num = getreg(INTEGER);
                int offset = lhs->symentry->offset - stkframesize;
                int immediate_value = lhs->intval;

                // If the immediate value is within a valid range, move it to the register
                if (immediate_value >= MINIMMEDIATE && immediate_value <= MAXIMMEDIATE) {
                    asmimmed(MOVL, immediate_value, reg_num);
                }

                // Always move the value in the register to EDI
                asmrr(MOVL, reg_num, EDI);
            }


            else if (strstr(lhs->stringval, "write")) {
                sym = searchst(lhs->stringval);
                if (rhs->tokentype == OPERATOR && rhs->whichval == AREFOP) {
                        sym = searchst(rhs->operands->stringval);
                        if (!sym) {
                            sym = searchst(rhs->operands->operands->stringval);
                            if (sym) {
                                asmld(MOVQ, sym->offset - stkframesize, getreg(INTEGER), sym->namestring);
                                asmldr(MOVSD, rhs->operands->link->intval, getreg(INTEGER),  getreg(REAL), "^.");
                                asmcall(lhs->stringval);
                            }
                        }
                    
                } 
                
                else if (rhs->tokentype == STRINGTOK) {
                    asmlitarg(nextlabel, EDI);
                    asmcall(lhs->stringval);
                    makeblit(rhs->stringval, nextlabel++);
                } 
                
                else if (sym->datatype->basicdt == INTEGER || sym->datatype->basicdt == REAL) {
                    SYMBOL argsym;

                    if (rhs->tokentype == IDENTIFIERTOK) {
                        argsym = searchst(rhs->stringval);

                        reg_num = getreg(argsym->basicdt);
                        asmld(argsym->basicdt, argsym->offset - stkframesize, reg_num, argsym->namestring);
                        asmrr(argsym->basicdt, reg_num, EDI);
                        asmcall(lhs->stringval);

                    }
                }
            } 

            break;


        case ASSIGNOP:
            {
            TOKEN currentToken = code->operands;
            while (currentToken) {
                TOKEN nextLink = currentToken->link;
                if (!nextLink) {
                    break;
                }
                currentToken = nextLink;
            }
            
            
            if (currentToken && (code->operands->link->tokentype == NUMBERTOK && currentToken->basicdt == POINTER && code->operands->link->basicdt == INTEGER && code->operands->link->intval == 0)) {
                nilFlag = true;
            }
            

            lhs = code->operands;
            rhs = lhs->link;

            if (code->operands->operands) {
                stopRef = code->operands->operands;
            }

            reg_num = genarith(lhs->link);
            rhsReg = rhs;
            rhsReg_num = reg_num;

            sym = searchst(lhs->stringval);
            if (sym && sym->datatype->kind == ARRAYSYM) {
                
                SYMBOL arrSym = sym->datatype;
                while (arrSym->kind == ARRAYSYM) {
                    arrSym = arrSym->datatype;
                }

                if (arrSym->kind == RECORDSYM) {
                    
                    TOKEN prev = lhs->operands;
                    TOKEN currentToken = lhs->operands;
                    while (currentToken) {
                        prev = currentToken;
                        currentToken = currentToken->link;
                    }

                    
                    if (prev && prev->tokentype == NUMBERTOK) {
                        asmimmed(MOVL, prev->intval, EAX);
                        asmop(CLTQ);
                        if (reg_num >= 0 && reg_num < 16) {
                            asmstrr(MOVL, reg_num, offs, EAX, lhs->stringval);
                        } 
                        else {
                            asmstrr(MOVSD, reg_num, offs, EAX, lhs->stringval);
                        }
                    }
                }
            }


            if (sym) {
                offs = sym->offset - stkframesize;

                if (reg_num >= 0 && reg_num < 16) {
                    if (lhs->basicdt != POINTER) {
                        asmst(MOVL, reg_num, offs, lhs->stringval);
                    } 
                    else {
                        asmst(MOVQ, reg_num, offs, lhs->stringval);
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
                        
                        int temp = getreg(INTEGER);

                        finalPtr = lhs->operands->operands;

                        asmld(MOVQ, sym->offset - stkframesize, temp, sym->namestring);

                        offs = lhs->operands->link->intval;

                        if (basicsizes[rhs->basicdt] <= basicsizes[INTEGER]) {
                            if (nilFlag) {
                                asmstr(MOVQ, reg_num, offs, temp, "^. ");
                            } 
                            else {
                                asmstr(MOVL, reg_num, offs, temp, "^. ");
                            }
                            
                        } 
                        else {
                            if (floatReg == -DBL_MAX) {
                                asmstr(MOVQ, reg_num, offs, temp, "^. ");
                            }
                            else {
                                asmstr(MOVSD, reg_num, offs, temp, "^. ");
                            }
                        }
                    }
                } 
                
                else {

                    TOKEN prev = lhs->operands;
                    TOKEN curTok = lhs->operands;
                    while (curTok) {
                        prev = curTok;
                        curTok = curTok->link;
                    }
                    

                    if (prev) {
                        if (prev->tokentype == NUMBERTOK && prev->basicdt == INTEGER) {
                            asmimmed(MOVL, prev->intval, EAX);
                            asmop(CLTQ);

                            if (reg_num >= 0 && reg_num < 16) {
                                asmstrr(MOVL, reg_num, sym->offset - stkframesize, EAX, sym->namestring);
                            } else {
                                asmstrr(MOVSD, reg_num, sym->offset - stkframesize, EAX, sym->namestring);
                            }
                        } 
                    } 
            }
        }

        if (lhs->operands) {
            reg_num = genarith(lhs->operands);
        }

        finalPtr = NULL;

        stopRef = NULL;
        break;
        }

    }
}







void reset_regs() {
    int i;
    for (i = 0; i < NUM_REGS; i++) {
        registers[i] = 0;
    }}

void free_reg(int reg_num) {
    registers[reg_num] = 0;
    
}

bool at_least_one_float(int lhs_reg, int rhs_reg) {
    return (lhs_reg >= I_REGS && lhs_reg < TOT_REGS) ||
           (rhs_reg >= I_REGS && rhs_reg < TOT_REGS);
}

void mark_reg_unused(int reg) {
    registers[reg] = 0;
    
}

void mark_reg_used(int reg) {
    registers[reg] = 1;
    
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

bool is_equal(TOKEN firstToken, TOKEN secondToken) {
    return firstToken == secondToken;
}