%{     /* pars1.y    Pascal Parser      Gordon S. Novak Jr.  ; 10 Jan 24   */

/* Copyright (c) 2023 Gordon S. Novak Jr. and
   The University of Texas at Austin. */

/* 14 Feb 01; 01 Oct 04; 02 Mar 07; 27 Feb 08; 24 Jul 09; 02 Aug 12;
   30 Jul 13; 25 Jul 19 ; 28 Feb 22; 08 Jul 22; 13 Nov 23 */

/*
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.
 
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.

; You should have received a copy of the GNU General Public License
; along with this program; if not, see <http://www.gnu.org/licenses/>.
  */


/* NOTE:   Copy your lexan.l lexical analyzer to this directory.      */

       /* To use:
                     make pars1y              has 1 shift/reduce conflict
                     pars1y                   execute the parser
                     i:=j .
                     ^D                       control-D to end input

                     pars1y                   execute the parser
                     begin i:=j; if i+j then x:=a+b*c else x:=a*b+c; k:=i end.
                     ^D

                     pars1y                   execute the parser
                     if x+y then if y+z then i:=j else k:=2.
                     ^D

           You may copy pars1.y to be parse.y and extend it for your
           assignment.  Then use   make parser   as above.
        */

        /* Yacc reports 1 shift/reduce conflict, due to the ELSE part of
           the IF statement, but Yacc's default resolves it in the right way.*/

#include "codegen.h"
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "lexan.h"
#include "symtab.h"
#include "pprint.h"
#include "parse.h"
#include "token.h"

        /* define the type of the Yacc stack element to be TOKEN */

#define YYSTYPE TOKEN

TOKEN parseresult;

%}

/* Order of tokens corresponds to tokendefs.c; do not change */

%token IDENTIFIER STRING NUMBER   /* token types */

%token PLUS MINUS TIMES DIVIDE    /* Operators */
%token ASSIGN EQ NE LT LE GE GT POINT DOT AND OR NOT DIV MOD IN

%token COMMA                      /* Delimiters */
%token SEMICOLON COLON LPAREN RPAREN LBRACKET RBRACKET DOTDOT

%token ARRAY BEGINBEGIN           /* Lex uses BEGIN */
%token CASE CONST DO DOWNTO ELSE END FILEFILE FOR FUNCTION GOTO IF LABEL NIL
%token OF PACKED PROCEDURE PROGRAM RECORD REPEAT SET THEN TO TYPE UNTIL
%token VAR WHILE WITH

%right thenthen ELSE // Same precedence, but "shift" wins.

%%
  program   : PROGRAM IDENTIFIER LPAREN idlist RPAREN SEMICOLON vblock DOT { parseresult = makeprogram($2, $4, $7); } ;
            ;
  
  idlist   :  IDENTIFIER COMMA idlist
                          { $$ = cons($1, $3); }
           |  IDENTIFIER  { $$ = cons($1, NULL); }
           ;
  vblock   :  VAR varspecs block       { $$ = $3; }
           |  block
           ;
  varspecs :  vargroup SEMICOLON varspecs
           |  vargroup SEMICOLON
           ;
  vargroup :  idlist COLON type
                      { instvars($1, $3); }
           ;
  type     :  simpletype
           ;
  simpletype :  IDENTIFIER   { $$ = findtype($1); }
          ;  /* $1->symtype returns type */

  block    : BEGINBEGIN statement endpart
              { $$ = makeprogn($1,cons($2, $3)); }
  
  statement  :  BEGINBEGIN statement endpart
                                       { $$ = makeprogn($1,cons($2, $3)); }
             |  IF expr THEN statement endif   { $$ = makeif($1, $2, $4, $5); }
             |  assignment
             |  functionCall
             |  FOR assignment TO expr DO statement { $$ = makefor(1, $1, $2,
             $3, $4, $5, $6); }
             | REPEAT repeat_body UNTIL expr { $$ = makerepeat($1, $2, $3, $4); }
             ;

  repeat_body : statement SEMICOLON repeat_body { $$ = cons($1, $3); }
              | statement { $$ = cons($1, NULL); }
              ;
  
  expressionList : expr COMMA expressionList { $$ = cons($1, $3); }
             |  expr
             ;
  functionCall : IDENTIFIER LPAREN expressionList RPAREN { $$ = makefuncall($2, $1, $3); }
             ;
  endpart    :  SEMICOLON statement endpart    { $$ = cons($2, $3); }
             |  END                            { $$ = NULL; }
             ;
  endif      :  ELSE statement                 { $$ = $2; }
             |  /* empty */                    { $$ = NULL; }  %prec thenthen
             ;
  assignment :  variable ASSIGN expr           { $$ = binop($2, $1, $3); }
             ;

  expr       :  basicExpr equivalenceOp basicExpr                 { $$ = binop($2, $1, $3); }
             |  basicExpr                          { $$ = $1;} 
             ;

  equivalenceOp: EQ
               | NE
               | LT
               | LE
               | GT
               | GE
               | IN
               ;

  scalarOp : TIMES 
            | DIVIDE 
            | MOD 
            | DIV 
            | AND 
            | OR
             ;
             
  term       :  factor scalarOp factor              { $$ = binop($2, $1, $3); }
             |  factor
             ;
             
  basicExpr  :  sign PLUS term              { $$ = binop($2, $1, $3); }
             |  sign MINUS term             { $$ = binop($2, $1, $3); }
             |  sign OR term                { $$ = binop($2, $1, $3); }
             |  sign
             ;
             
  sign       : PLUS term							{ $$ = unaryop($1, $2); }
             | MINUS term						{ $$ = unaryop($1, $2); }
             | term								{ $$ = $1; }
             ;

  factor     :  LPAREN expr RPAREN             { $$ = $2; }
             |  variable
             |  NUMBER
             |  STRING
             |  NIL 
             |  funcall
             |  NOT factor                    { $$ = unaryop($1, $2); }
             ;

  variable   : IDENTIFIER
             ;
%%

/* You should add your own debugging flags below, and add debugging
   printouts to your programs.

   You will want to change DEBUG to turn off printouts once things
   are working.

   To add more flags, use the next power of 2: the next one would be 32.
   To turn on all flags, set DEBUG to the next power of 2, minus 1.
  */

#define DEBUG        0            /* set bits here for debugging, 0 = off  */
#define DB_CONS       1             /* bit to trace cons */
#define DB_BINOP      1             /* bit to trace binop */
#define DB_MAKEIF     1             /* bit to trace makeif */
#define DB_MAKEPROGN  1             /* bit to trace makeprogn */
#define DB_PARSERES  1             /* bit to trace parseresult */
#define DB_MAKEPROGRAM 1           /* bit to trace makeprogram */
#define DB_MAKENUMTOK     1
#define DB_MAKEOPTOK     1
#define DB_MAKECOPY     1
#define DB_MAKEFOR      1
#define DB_MAKEFUNCALL  1
#define DB_MAKEREPEAT   1

 int labelnumber = 0;  /* sequential counter for internal label numbers */

   /*  Note: you should add to the above values and insert debugging
       printouts in your routines similar to those that are shown here.     */

TOKEN cons(TOKEN item, TOKEN list)           /* add item to front of list */
  { item->link = list;
    if (DEBUG & DB_CONS)
       { printf("cons\n");
         dbugprinttok(item);
         dbugprinttok(list);
       };
    return item;
  }


TOKEN makeFloatToken(TOKEN tok){
  if (tok->tokentype == NUMBERTOK){
    tok->datatype = REAL;
    tok->realval = (double) tok->intval;
    return tok;
  }
  else{
    TOKEN floatToken = makeOperatorTok(FLOATOP);
    floatToken->operands = tok;
    return floatToken;
  }
}

TOKEN unaryop(TOKEN op, TOKEN lhs){
  op->operands = lhs;
  lhs->link = NULL;
  if (DEBUG & DB_BINOP)
       { printf("unaryop\n");
         dbugprinttok(op);
         dbugprinttok(lhs);
       };
  return op;

}


TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs)        /* reduce binary operator */
  { op->operands = lhs;          /* link operands to operator       */
    lhs->link = rhs;             /* link second operand to first    */
    rhs->link = NULL;            /* terminate operand list          */

    int lhType;
    int rhType;

    if (lhs->datatype == INTEGER) {
      lhType = 1;
    } else {
      //REAL
      lhType = 0;
    }
    if (rhs->datatype == INTEGER) {
      rhType = 1;
    } else {
      //REAL
      rhType = 0;
    }

    if (lhType == 1 && rhType == 0) {

      TOKEN temptoken = talloc();
      if (op->whichval == ASSIGNOP){
        op->datatype = INTEGER;
        TOKEN temptoken = talloc();
        if (rhs->tokentype == NUMBERTOK) {
          temptoken->intval = (int) rhs->realval;
          temptoken->datatype = INTEGER;
        }
        else{
          temptoken = makeOperatorTok(FIXOP);
          temptoken->operands = rhs;
        }
        lhs->link = temptoken;
      }
      else{
        op->datatype = REAL;
        TOKEN temptoken = makeFloatToken(lhs);
        temptoken->link = rhs;
      }
    }


    else if (lhType == 0 && rhType == 0) {
      op->datatype = REAL;
    }

    else if (lhType == 0 && rhType == 1) {
      op->datatype = REAL;
      TOKEN floatToken = makeFloatToken(rhs);
      lhs->link = floatToken;
    }

    //deciding what to set op datatype to
    if (DEBUG & DB_BINOP)
       { printf("binop\n");
         dbugprinttok(op);
         dbugprinttok(lhs);
         dbugprinttok(rhs);
       };
    
    return op;

    
  }

//method to duplicate an input token
TOKEN copytok(TOKEN origtok) {
  TOKEN copy = talloc();
  copy->tokentype = origtok->tokentype;
  copy->basicdt = origtok->basicdt;
  copy->symtype = origtok->symtype;
  copy->symentry = origtok->symentry;
  copy->link = origtok->link;
  copy->whichval = origtok->whichval;
  copy->intval = origtok->intval;
  copy->realval = origtok->realval;
  if (DEBUG & DB_MAKECOPY) {
    printf("copytok\n");
    dbugprinttok(copy);
  }
  return copy;
}

//helper to create an operator token of specific op type
TOKEN makeOperatorTok(int op){
    TOKEN tok = talloc();
    tok->whichval = op;
    tok->tokentype = OPERATOR;
    if (DEBUG & DB_MAKEOPTOK) {
      printf("makeoperatortok\n");
      dbugprinttok(tok);
    }
    return tok;
}

//helper method to create a number token
TOKEN makeNumTok(int num) {
  TOKEN tok = talloc();
  tok->intval = num;
  tok->tokentype = NUMBERTOK;
  tok->basicdt = INTEGER;
  if (DEBUG & DB_MAKENUMTOK) {
      printf("makeNumTok\n");
      dbugprinttok(tok);
  }
  return tok;
}


//method for handling for loop logic
TOKEN makefor(int sign, TOKEN tok, TOKEN assign, TOKEN tokb, TOKEN expr, TOKEN tokc, TOKEN statements) {
    // Initial assignment and progn creation for the loop
    tok = makeprogn(tok, assign);

    // Setting up the loop label for iteration control
    TOKEN loopLabel = talloc();
    loopLabel->operands = makeNumTok(labelnumber++);
    loopLabel->tokentype = OPERATOR;
    loopLabel->whichval = LABELOP;

    // Linking the loop initialization to the label
    assign->link = loopLabel;

    // Preparing the loop body
    TOKEN loopBody = talloc();
    loopBody = makeprogn(loopBody, statements);

    // Creating the conditional check for the loop
    TOKEN leOperator = makeOperatorTok(LEOP);
    TOKEN conditional = talloc();
    conditional = makeif(conditional, leOperator, loopBody, NULL);

    // Handling the loop variable and its increment
    TOKEN varCopy = copytok(assign->operands);
    varCopy->link = expr;
    leOperator->operands = varCopy;

    TOKEN incrementStep = copytok(varCopy);
    TOKEN incrementVar = copytok(varCopy);

    TOKEN incrementOp = makeOperatorTok(PLUSOP);
    TOKEN incrementAssign = makeOperatorTok(ASSIGNOP);

    incrementOp->operands = incrementStep;
    incrementVar->link = incrementOp;
    incrementStep->link = makeNumTok(1);
    incrementAssign->operands = incrementVar;

    // Setting up the goto operation for loop continuation
    TOKEN gotoOperation = talloc();
    gotoOperation->operands = makeNumTok(labelnumber - 1);
    gotoOperation->whichval = GOTOOP;
    gotoOperation->tokentype = OPERATOR;

    // Linking the increment operation and the goto for the loop's next iteration
    statements->link = incrementAssign;
    incrementAssign->link = gotoOperation;

    // Final assembly of the loop's conditional and body components
    loopLabel->link = conditional;
    leOperator->link = loopBody;
    conditional->operands = leOperator;

    // Debugging output, if enabled
    if (DEBUG && DB_MAKEFOR) {
        printf("Refactored makefor\n");
        dbugprinttok(tok);
    }

    return tok;
}

//method to create a function call token
TOKEN makefuncall(TOKEN tok, TOKEN fn, TOKEN args)
  {  
     fn->link = args;
     tok->tokentype = OPERATOR;  
     tok->whichval = FUNCALLOP;
     tok->operands = fn;
     if (DEBUG & DB_MAKEFUNCALL)
        { 
          printf("makefuncall\n");
          dbugprinttok(tok);
          dbugprinttok(fn);
          dbugprinttok(args);
        };
     return tok;
   }

//method to create an if token
TOKEN makeif(TOKEN tok, TOKEN exp, TOKEN thenpart, TOKEN elsepart)
  {  tok->tokentype = OPERATOR;  
     tok->whichval = IFOP;
     tok->operands = exp;
     thenpart->link = elsepart;
     if (elsepart != NULL) {
      elsepart->link = NULL;
     }
     exp->link = thenpart;
     if (DEBUG & DB_MAKEIF)
        { printf("makeif\n");
          dbugprinttok(tok);
          dbugprinttok(exp);
          dbugprinttok(thenpart);
          dbugprinttok(elsepart);
        };
     return tok;
   }

//method to create a progn token
TOKEN makeprogn(TOKEN tok, TOKEN statements)
  {  tok->tokentype = OPERATOR;
     tok->whichval = PROGNOP;
     tok->operands = statements;
     if (DEBUG & DB_MAKEPROGN)
       { printf("makeprogn\n");
         dbugprinttok(tok);
         dbugprinttok(statements);
       };
     return tok;
   }

//method to create a program token
TOKEN makeprogram(TOKEN name, TOKEN args, TOKEN statements)
  {
    TOKEN tok = talloc();
    tok->tokentype = OPERATOR;
    tok->whichval = PROGRAMOP;
    tok->operands = name;
    TOKEN nameArgs = talloc();
    nameArgs = makeprogn(nameArgs, args);
    name->link = nameArgs;
    nameArgs->link = statements;

    if(DEBUG & DB_MAKEPROGRAM){
      printf("makeprogram\n");
      dbugprinttok(tok);
      dbugprinttok(args);
    }
    return tok;
  }


TOKEN makerepeat(TOKEN tok, TOKEN statements, TOKEN tokb, TOKEN expr){

  TOKEN repeatStart = talloc();
  repeatStart->tokentype = OPERATOR;
  repeatStart->whichval = LABELOP;
  repeatStart->operands = makeNumTok(labelnumber++);

  tok = makeprogn(tok, repeatStart);

  TOKEN shellBody = makeprogn(tokb,statements );
  repeatStart->link = shellBody;

  TOKEN repeatStartGoTo = talloc();
  repeatStartGoTo->tokentype = OPERATOR;
  repeatStartGoTo->whichval = GOTOOP;
  repeatStartGoTo->operands = makeNumTok(labelnumber - 1);

  TOKEN repeatConditional = makeif(talloc(), expr, repeatStartGoTo, NULL);

  while(statements->link != NULL){
    statements = statements->link;
  }
  statements->link = repeatConditional;


  if (DEBUG && DB_MAKEREPEAT) { 
        printf("make repeat\n");
        dbugprinttok(tok);
  }

    return tok;


  return tok;
}


//method to find the symbol entry of specified toke
TOKEN findid(TOKEN tok) { /* the ID token */
  SYMBOL sym = searchst(tok->stringval);
  tok->symentry = sym;
  SYMBOL typ = sym->datatype;
  tok->symtype = typ;
  if ( typ->kind == BASICTYPE ||
      typ->kind == POINTERSYM)
      tok->basicdt = typ->basicdt;
  return tok; 
}

//method to find the type of a token in symbol table
TOKEN findtype(TOKEN tok){
  SYMBOL sym = searchst(tok->stringval);
  tok->symentry = sym;
  tok->symtype = sym;
  return tok;
}

//method to insert symbols into symbol table
void instvars(TOKEN idlist, TOKEN typetok)
  {  
    SYMBOL sym, typesym; int align;
    typesym = typetok->symtype;
    align = alignsize(typesym);
    while ( idlist != NULL )   /* for each id */
      {  sym = insertsym(idlist->stringval);
        sym->kind = VARSYM;
        sym->offset =     /* "next" */
            wordaddress(blockoffs[blocknumber],
                        align);
        sym->size = typesym->size;
        blockoffs[blocknumber] =   /* "next" */
                        sym->offset + sym->size;
        sym->datatype = typesym;
        sym->basicdt = typesym->basicdt;
        idlist = idlist->link;
      };
  }


int wordaddress(int n, int wordsize)
  { return ((n + wordsize - 1) / wordsize) * wordsize; }
 
void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}

int main(void)          /*  */
  { int res;
    initsyms();
    res = yyparse();
    printf("yyparse result = %8d\n", res);

    printstlevel(1);    /* to see level 0 too, change to:   printst();  */

    if (DEBUG & DB_PARSERES){ 

      dbugprinttok(parseresult);
    }

    ppexpr(parseresult);           /* Pretty-print the result tree */

    /* uncomment following to call code generator. */
     
    // gencode(parseresult, blockoffs[blocknumber], labelnumber);
 
  }
