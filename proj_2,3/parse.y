%{     /* pars1.y    Pascal Parser      Gordon S. Novak Jr.  ; 30 Jul 13   */

/* Copyright (c) 2013 Gordon S. Novak Jr. and
   The University of Texas at Austin. */


/* 14 Feb 01; 01 Oct 04; 02 Mar 07; 27 Feb 08; 24 Jul 09; 02 Aug 12 */

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

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "token.h"
#include "lexan.h"
#include "symtab.h"
#include "parse.h"

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


%%

  program    : PROGRAM IDENTIFIER LPAREN idlist RPAREN SEMICOLON lblock DOT { parseresult = makeprogram($2, $4, $7); } ;
             ;

  idlist     :  IDENTIFIER COMMA idlist { $$ = cons($1, $3); }
             |  IDENTIFIER    { $$ = cons($1, NULL); }
             ;

  cdef       :  IDENTIFIER EQ constant { instconst($1, $3); }
             ;
  clist      :  cdef SEMICOLON clist    
             |  cdef SEMICOLON          
             ;  
  constant   :  sign IDENTIFIER     { $$ = unaryop($1, $2); }
             |  IDENTIFIER
             |  sign NUMBER         { $$ = unaryop($1, $2); }
             |  NUMBER
             |  STRING
             ;
  tdef       :  IDENTIFIER EQ type     { insttype($1, $3); }
             ;
  tlist      :  tdef SEMICOLON tlist
             |  tdef SEMICOLON
             ;
  statementList     :  statement SEMICOLON statementList      { $$ = cons($1, $3); }
             |  statement                  { $$ = cons($1, NULL); }
             ;
  fieldsList     :  idlist COLON type             { $$ = instfields($1, $3); }
             ;
  multiFieldsList :  fieldsList SEMICOLON multiFieldsList   { $$ = nconc($1, $3); }
             |  fieldsList
             ;
  label      :  NUMBER COLON statement          { $$ = dolabel($1, $2, $3); }
             ;  
  labelsList    :  NUMBER COMMA labelsList  { instlabel($1); }
             |  NUMBER                { instlabel($1); }
             ;
  lblock     :  LABEL labelsList SEMICOLON cblock  { $$ = $4; }
             |  cblock
             ;
  cblock     :  CONST clist tblock              { $$ = $3; }
             |  tblock
             ;
  tblock     :  TYPE tlist vblock       { $$ = $3; }
             |  vblock
             ;
  vblock     :  VAR varspecs block       { $$ = $3; }
             |  block
             ;
  varspecs   :  vargroup SEMICOLON varspecs   
             |  vargroup SEMICOLON            
             ;
  vargroup   :  idlist COLON type { instvars($1, $3); }
             ;
  type       :  basicType
             |  POINT IDENTIFIER                              { $$ = instpoint($1, $2); }
             |  ARRAY LBRACKET basicList RBRACKET OF type   { $$ = instarray($3, $6); }
             |  RECORD multiFieldsList END                          { $$ = instrec($1, $2); }
             ;

  basicList :  basicType COMMA basicList  { $$ = cons($1, $3); }
             |  basicType                { $$ = cons($1, NULL); }
             ;
  basicType :  IDENTIFIER   { $$ = findtype($1); }
             |  constant DOTDOT constant     { $$ = instdotdot($1, $2, $3); }
             |  LPAREN idlist RPAREN         { $$ = instenum($2); }
             ;

  block      :  BEGINBEGIN statement endpart   { $$ = makeprogn($1, cons($2, $3)); }  
             ;
  statement  :  block
            |  IF expr THEN statement endif   { $$ = makeif($1, $2, $4, $5); }
            |  assignment
            |  functionCall
            |  FOR assignment TO expr DO statement   { $$ = makefor(1, $1, $2, $3, $4, $5, $6); }
            |  REPEAT statementList UNTIL expr              { $$ =
            makerepeat($1, $2, $3, $4); }
            |  GOTO NUMBER                  { $$ = dogoto($1, $2); }
            |  WHILE expr DO statement       { $$ = makewhile($1, $2, $3, $4); }
            |  label
            ;
  functionCall    :  IDENTIFIER LPAREN expressionList RPAREN    { $$ = makefuncall($2, $1, $3); }
             ;
  endpart    :  SEMICOLON statement endpart    { $$ = cons($2, $3); }
             |  END                            { $$ = NULL; }
             ;
  endif      :  ELSE statement                 { $$ = $2; }
             |  /* empty */                    { $$ = NULL; }
             ;
  assignment :  variable ASSIGN expr         { $$ = binop($2, $1, $3); }
             ;

  variable   :  IDENTIFIER                            { $$ = findid($1); }
             |  variable LBRACKET expressionList RBRACKET   { $$ = arrayref($1, $2,
             $3, $4); }
             |  variable POINT                         { $$ = dopoint($1, $2); }
             |  variable DOT IDENTIFIER                { $$ = reducedot($1, $2, $3); }
             ;

  signedExpression     :  signedTerm
             |  signedExpression PLUS term                 { $$ = binop($2, $1, $3); }
             |  signedExpression MINUS term                 { $$ = binop($2, $1, $3); }
             |  signedExpression OR term                 { $$ = binop($2, $1, $3); }
             ;
  
  signedTerm :  sign term           { $$ = unaryop($1, $2); }
             |  term
             ;

  sign       :  PLUS 
             |  MINUS
             ;

  expr       :  expr EQ signedExpression              { $$ = binop($2, $1, $3); }
             |  expr LT signedExpression              { $$ = binop($2, $1, $3); }
             |  expr GT signedExpression              { $$ = binop($2, $1, $3); }
             |  expr NE signedExpression              { $$ = binop($2, $1, $3); }
             |  expr LE signedExpression              { $$ = binop($2, $1, $3); }
             |  expr GE signedExpression              { $$ = binop($2, $1, $3); }
             |  expr IN signedExpression              { $$ = binop($2, $1, $3); }
             |  signedExpression 
             ;

  expressionList  :  expr COMMA expressionList           { $$ = cons($1, $3); }
             |  expr                        { $$ = cons($1, NULL); }
             ;

  term       :  term TIMES factor              { $$ = binop($2, $1, $3); }
             |  term DIVIDE factor              { $$ = binop($2, $1, $3); }
             |  term AND factor              { $$ = binop($2, $1, $3); }
             |  term DIV factor              { $$ = binop($2, $1, $3); }
             |  term MOD factor              { $$ = binop($2, $1, $3); }
             |  factor
             ;
  factor     :   variable
             |  STRING
             | NUMBER
             |  NIL 
             |  functionCall
             |  LPAREN expr RPAREN             { $$ = $2; }       
             |  NOT factor          { $$ = unaryop($1, $2); }
%%

/* You should add your own debugging flags below, and add debugging
   printouts to your programs.

   You will want to change DEBUG to turn off printouts once things
   are working.
  */

#define DEBUG           0             /* set bits here for debugging, 0 = off  */
#define DB_CONS         0             /* bit to trace cons */
#define DB_BINOP        0             /* bit to trace binop */
#define DB_MAKEIF       0             /* bit to trace makeif */
#define DB_MAKEPROGN    0             /* bit to trace makeprogn */
#define DB_PARSERES     0             /* bit to trace parseresult */
#define DB_MAKEPROGRAM  0
#define DB_MAKEINTC     0
#define DB_MAKELABEL    0
#define DB_MAKEOP       0
#define DB_MAKECOPY     0
#define DB_MAKEGOTO     0
#define DB_MAKEFOR      0
#define DB_MAKEWHILE    0
#define DB_MAKEFUNCALL  0
#define DB_UNOP         0
#define DB_FINDID       0  
#define DB_INSTCONST    0  
#define DB_INSTLABEL    0   
#define DB_FINDLABEL    0 
#define DB_FINDTYPE     0 
#define DB_REDUCEDOT    1
#define DB_ARRAYREF     1
#define DB_MAKEREPEAT   0
#define DB_MAKESUB      0
#define DB_MAKEAREF     1
#define DB_DOLABEL      0
#define DB_DOGOTO       0
#define DB_DOPOINT      0
#define DB_INSTTYPE     0
#define DB_INSTENUM     0
#define DB_INSTDOTDOT   0
#define DB_INSTARRAY    0
#define DB_INSTFIELD    0
#define DB_NCONC        0
#define DB_INSTREC      0
#define DB_INSTPOINT    0

 int labelnumber = 0; 
 int labels[50];

   /*  Note: you should add to the above values and insert debugging
       printouts in your routines similar to those that are shown here.     */

TOKEN cons(TOKEN item, TOKEN list)            /* add item to front of list */
  { item->link = list;
    if (DEBUG & DB_CONS)
       { printf("cons\n");
         dbugprinttok(item);
         dbugprinttok(list);
       };
    return item;
  }


/* nconc concatenates two token lists, destructively, by making the last link
   of lista point to listb.
   (nconc '(a b) '(c d e))  =  (a b c d e)  */
/* nconc is useful for putting together two fieldlist groups to
   make them into a single list in a record declaration. */
TOKEN nconc(TOKEN lista, TOKEN listb) {
  TOKEN temp = lista;
  while(temp->link) {
    temp = temp->link;
  }
  temp->link = listb;
  if (DEBUG & DB_NCONC) {
   printf("nconc\n");
   dbugprinttok(temp);
  };
  return temp;
}

int  checkReal(TOKEN tok) {
  return (tok->basicdt == REAL);

}

int checkInt(TOKEN tok) {
  return (tok->basicdt == INTEGER);

}


/* unaryop links a unary operator op to one operand, lhs */
TOKEN unaryop(TOKEN op, TOKEN lhs) {
  op->operands = lhs;
  lhs->link = NULL;
  if (DEBUG & DB_UNOP)
     { printf("unaryop\n");
       dbugprinttok(op);
       dbugprinttok(lhs);
     };
  return op;  
}



/* binop links a binary operator op to two operands, lhs and rhs. */
TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs){ 
    printf("lhs\n");
    ppexpr(lhs);
    printf("\n");
    printf("lhs->basicdt: %d\n", lhs->basicdt);

    printf("\nop\n");;
    ppexpr(op);
    printf("\nrhs\n");
    ppexpr(rhs);
    printf("\n");
    
    if (lhs->tokentype == NUMBERTOK){

    lhs->link = rhs;             
    rhs->link = NULL;           
    op->operands = lhs; 

    //handles type casting
    int lhType;
    int rhType;

    //define our variables for specifying type
    if (lhs->basicdt == INTEGER) {
      lhType = 1;
    } else {
      //REAL
      lhType = 0;
    }
    if (rhs->basicdt == INTEGER) {
      rhType = 1;
    } else {
      //REAL
      rhType = 0;
    }

    //left hand = integer; right hand = float
    if (lhType == 1 && rhType == 0) {


      TOKEN temptoken = talloc();

      // computation operation
      if (op->whichval != ASSIGNOP){

        op->basicdt = REAL;
        TOKEN temptoken = makefloat(lhs);
        temptoken->link = rhs;
      }

      // assignment operation
      else{
        op->basicdt = INTEGER;
        TOKEN temptoken = makefix(rhs);
        lhs->link = temptoken;
      }
    }

    //both real
    else if (lhType == 0 && rhType == 0) {
      op->basicdt = REAL;
    }

    //left hand = int; right hand = real
    else if (lhType == 0 && rhType == 1) {
      TOKEN floatToken = makefloat(rhs);
      lhs->link = floatToken;
      op->basicdt = REAL;

    }

    //nothing needed for both int

    //deciding what to set op datatype to
    if (DEBUG & DB_BINOP)
       { printf("binop\n");
         dbugprinttok(op);
         dbugprinttok(lhs);
         dbugprinttok(rhs);
       };
    
    return op;
    }
      if (rhs->whichval == (NIL - RESERVED_BIAS)) {
        rhs = makeintc(0);
    }

    op->operands = lhs; // Link operands to operator.
    lhs->link = rhs; // Link second operand to first.
    rhs->link = NULL; // Terminate operand list.



      // Existing logic
      if (checkReal(lhs) && checkReal(rhs)) {
          op->basicdt = REAL;
      } else if (checkReal(lhs) && checkInt(rhs)) {
          op->basicdt = REAL;
          TOKEN ftok = makefloat(rhs);
          lhs->link = ftok;
      } else if (checkInt(lhs) && checkReal(rhs)) {
          if (op->whichval == ASSIGNOP) {
              op->basicdt = INTEGER;
          } else {
              op->basicdt = REAL;
          }
      }
    

    if (DEBUG & DB_BINOP) {
        printf("binop - final type handling\n");
        dbugprinttok(op);
    }

    return op;
    }


/* makefloat forces the item tok to be floating, by floating a constant
   or by inserting a FLOATOP operator */
TOKEN makefloat(TOKEN tok) {
  if(tok->tokentype == NUMBERTOK) {
    tok->basicdt = REAL;
    tok->realval = (double) tok->intval;
    return tok;
  } else {
    TOKEN floatop = makeop(FLOATOP);
    floatop->operands = tok;
    return floatop;
  }
  
}


/* makefix forces the item tok to be integer, by truncating a constant
   or by inserting a FIXOP operator */
TOKEN makefix(TOKEN tok) {
  if(tok->tokentype == NUMBERTOK) {
    tok->basicdt = INTEGER;
    tok->intval = (int) tok->realval;
    // printf("was numbertoken so truncated\n");
    return tok;
  } else { 
    TOKEN fixop = makeop(FIXOP);
    fixop->operands = tok;
    return fixop;
  }
}



/* makeop makes a new operator token with operator number opnum.
   Example:  makeop(FLOATOP)  */
TOKEN makeop(int op){
    TOKEN tok = talloc();
    tok->tokentype = OPERATOR;
    tok->whichval = op;
    if (DEBUG & DB_MAKEOP) {
      printf("makeop\n");
      dbugprinttok(tok);
    }
    return tok;
}

/* copytok makes a new token that is a copy of origtok */
TOKEN copytok(TOKEN target) {
  TOKEN copy = talloc();
  copy->tokentype = target->tokentype;
  copy->basicdt = target->basicdt;
  copy->symtype = target->symtype;
  copy->symentry = target->symentry;
  copy->link = target->link;
  for (int i = 0; i < 16; i++){
    copy->stringval[i] = target->stringval[i];
  }
  
  if (DEBUG & DB_MAKECOPY) {
    printf("copytok\n");
    dbugprinttok(copy);
  }
  return copy;
}

TOKEN makeif(TOKEN tok, TOKEN exp, TOKEN thenpart, TOKEN elsepart)
  {  tok->tokentype = OPERATOR;  /* Make it look like an operator   */
     tok->whichval = IFOP;
     if (elsepart != NULL) elsepart->link = NULL;
     thenpart->link = elsepart;
     exp->link = thenpart;
     tok->operands = exp;
     if (DEBUG & DB_MAKEIF)
        { printf("makeif\n");
          dbugprinttok(tok);
          dbugprinttok(exp);
          dbugprinttok(thenpart);
          dbugprinttok(elsepart);
        };
     return tok;
   }

/* makeintc makes a new token with num as its value */
TOKEN makeintc(int number) {
  TOKEN tok = talloc();
  tok->tokentype = NUMBERTOK;
  tok->basicdt = INTEGER;
  tok->intval = number;
  if (DEBUG & DB_MAKEINTC) {
      printf("makeintc\n");
      dbugprinttok(tok);
  }
  return tok;
}

/* makelabel makes a new label, using labelnumber++ */
TOKEN makelabel() {
  TOKEN tok = talloc();
  tok->tokentype = OPERATOR;
  tok->whichval = LABELOP;
  tok->operands = makeintc(labelnumber++);
  if (DEBUG & DB_MAKELABEL) {
      printf("makelabel\n");
      dbugprinttok(tok);
  }
  return tok;
}

/* makegoto makes a GOTO operator to go to the specified label.
   The label number is put into a number token. */
TOKEN makegoto(int num){
  TOKEN tok = talloc();
  tok->tokentype = OPERATOR;
  tok->whichval = GOTOOP;
  tok->operands = makeintc(num);
  if (DEBUG && DB_MAKEGOTO) {
      printf("makegoto\n");
      dbugprinttok(tok);
  }
  return tok;
}


TOKEN makearef(TOKEN var, TOKEN off, TOKEN tok){
  
  TOKEN finalOffset = off; // Start with the assumption we'll use the provided offset

  if (var->link){
    
    if (var->link->tokentype == NUMBERTOK){
    finalOffset->intval = var->link->intval + off->intval;
    }
    else if(var->link->tokentype == IDENTIFIERTOK){
      TOKEN plusop = makeop(PLUSOP);
      plusop->operands = var->link;
      plusop->link = off;
      finalOffset = plusop;
      finalOffset->tokentype = IDENTIFIERTOK;
    }
    
  }

  if (var->whichval == AREFOP && off->basicdt == INTEGER) {
    
    TOKEN off1 = var->operands->link;
    if (off1->tokentype == NUMBERTOK) { // Assuming off1 is the offset in the nested AREF
      // Directly sum the integer values of the offsets
      int sumOffsets = off1->intval + off->intval;
      finalOffset = makeintc(sumOffsets); // Use this new offset for the final AREF
    }
  }

  // Now, we create the AREF operation using the possibly updated finalOffset
  TOKEN areftok = makeop(AREFOP);
  if (var->whichval == AREFOP) { // If nesting was detected, link directly to the array part of the nested AREF
    if(var->link == NULL || var->link->tokentype != IDENTIFIERTOK){
      var = var->operands;

    }
  }

  if (finalOffset != 0){
    var->link = finalOffset; // Link the final offset

  }

  if (var->link->tokentype == IDENTIFIERTOK){
    return var;
  }
  else{
    areftok->operands = var;
  }
  
  areftok->symtype = var->symtype;
  
  if (var->symtype && var->symtype->datatype) {
    areftok->basicdt = var->symtype->datatype->basicdt;
  }

  if (DEBUG && DB_MAKEAREF) {
      printf("makearef - possibly merged\n");
      dbugprinttok(areftok);
  }

  return areftok;
}



/* makefor makes structures for a for statement.
   sign is 1 for normal loop, -1 for downto.
   asg is an assignment statement, e.g. (:= i 1)
   endexpr is the end expression
   tok, tokb and tokc are (now) unused tokens that are recycled. */
TOKEN makefor(int sign, TOKEN tok, TOKEN assign, TOKEN tokb, TOKEN expr, TOKEN tokc, TOKEN statements) {
    // Initial assignment
    tok = makeprogn(tok, assign);

    // Setting up the loop label token
    TOKEN loopLabel = makelabel();


    // Linking the loop initialization to the label
    assign->link = loopLabel;

    // build loop body's statements tree
    TOKEN loopBody = talloc();
    loopBody = makeprogn(loopBody, statements);

    // Creating the conditional check for the loop
    TOKEN leOperator = makeop(LEOP);
    TOKEN conditional = talloc();
    conditional = makeif(conditional, leOperator, loopBody, NULL);

    // Handling the loop variable and its increment
    TOKEN varCopy = copytok(assign->operands);
    varCopy->link = expr;
    leOperator->operands = varCopy;

    TOKEN incrementStep = copytok(varCopy);
    TOKEN incrementVar = copytok(varCopy);

    TOKEN incrementOp = makeplus(NULL, NULL, NULL);
    TOKEN incrementAssign = makeop(ASSIGNOP);

    incrementOp->operands = incrementStep;
    incrementVar->link = incrementOp;
    incrementStep->link = makeintc(1);
    incrementAssign->operands = incrementVar;

    // Setting up the goto operation for loop continuation
    TOKEN gotoOperation = makegoto(labelnumber - 1);

    // Linking the increment operation and the goto for the loop's next iteration
    statements->link = incrementAssign;
    incrementAssign->link = gotoOperation;

    // Final assembly of the loop's conditional and body components
    loopLabel->link = conditional;
    leOperator->link = loopBody;
    conditional->operands = leOperator;

    // Debugging output, if enabled
    if (DEBUG && DB_MAKEFOR) {
        dbugprinttok(tok);
    }

    return tok;
}
/* makeplus makes a + operator.
  tok (if not NULL) is a (now) unused token that is recycled. */
TOKEN makeplus(TOKEN lhs, TOKEN rhs, TOKEN tok) {

	TOKEN ret = makeop(PLUSOP);

  ret->operands = lhs;
  lhs->link = rhs;
  rhs->link = NULL;


	return ret;
}

/* makewhile makes structures for a while statement.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN makewhile(TOKEN tok, TOKEN expr, TOKEN tokb, TOKEN statement) {
  
  TOKEN loopLabel = makelabel();
  tok = makeprogn(tok, loopLabel);

  TOKEN body = makeprogn(tokb, statement);

  TOKEN ifTok = talloc();
  ifTok = makeif(ifTok, expr, body, NULL);
  loopLabel->link = ifTok;

  statement->link = makegoto(labelnumber - 1);


  return tok;
  
}

/* makefuncall makes a FUNCALL operator and links it to the fn and args.
   tok is a (now) unused token that is recycled. */
TOKEN makefuncall(TOKEN tok, TOKEN fn, TOKEN args) {

  
  fn->link = args;
  tok->tokentype = OPERATOR;  
  tok->operands = fn;
  tok->whichval = FUNCALLOP;
  tok->basicdt = args->basicdt;

  if (strcmp(fn->stringval, "writeln") == 0) {
    int argType = args->basicdt;


    int typeIndex = 7; 
    switch (argType) {
        case REAL:
            if (strcmp(fn->stringval, "writeln") == 0) {
                fn->stringval[typeIndex] = 'f';
                fn->stringval[typeIndex + 1] = '\0';
            }
            break;
        case INTEGER:
            if (strcmp(fn->stringval, "writeln") == 0) {
                fn->stringval[typeIndex] = 'i';
                fn->stringval[typeIndex + 1] = '\0';
            }
            break;
        default:
            break;
    }
  }

  else if (strcmp(fn->stringval, "new") == 0) {
    tok = makeop(ASSIGNOP);
    tok->operands = args;

    TOKEN funcOp = makeop(FUNCALLOP);
    fn->link = makeintc(args->symtype->datatype->size);
    funcOp->operands = fn;
    funcOp->basicdt = args->symtype->datatype->basicdt;
    args->link = funcOp;

    return tok;
  } 


     if (DEBUG & DB_MAKEFUNCALL)
        { 
          printf("makefuncall\n");
          dbugprinttok(tok);
          dbugprinttok(fn);
          dbugprinttok(args);
        };
    
    
  return tok;
}

/* makerepeat makes structures for a repeat statement.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN makerepeat(TOKEN tok, TOKEN statements, TOKEN tokb, TOKEN expr) {

  //set label token for the start
  TOKEN repeatStart = makelabel();
   
   
   tok = makeprogn(tok, repeatStart);

   //set up the repeat body token
   TOKEN shellBody = makeprogn(tokb, statements);
   repeatStart->link = shellBody;

   //set up the go to token for looping
   TOKEN repeatStartGoTo = makegoto(labelnumber - 1);
   TOKEN filler = makeprogn(talloc(), NULL);
   filler->link = repeatStartGoTo;

   //conditional token
   TOKEN ifs = makeif(talloc(), expr, filler, repeatStartGoTo);
   shellBody->link = ifs;


   return tok;  
}

/* makesubrange makes a SUBRANGE symbol table entry, puts the pointer to it
   into tok, and returns tok. */
TOKEN makesubrange(TOKEN tok, int low, int high) {

  SYMBOL subrange = symalloc();
  subrange->kind = SUBRANGE;
  subrange->basicdt = INTEGER;
  subrange->lowbound = low;
  subrange->highbound = high;
  subrange->size = basicsizes[INTEGER];
  tok->symtype = subrange;

  if (DEBUG & DB_MAKESUB) {
    printf("making subrange\n");
    dbugprinttok(tok);
  }

  return tok;
}


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

/* makeprogram makes the tree structures for the top-level program */
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


/* findid finds an identifier in the symbol table, sets up symbol table
   pointers, changes a constant to its number equivalent */
TOKEN findid(TOKEN tok) { /* the ID token */
    SYMBOL sym, typ;
    sym = searchst(tok->stringval);
    tok->symentry = sym;
    // tok->symtype = sym;

    
    if (sym->kind == CONSTSYM) {
      if (sym->basicdt == REAL) {
        tok->tokentype = NUMBERTOK;
        tok->basicdt = REAL;
        tok->realval = sym->constval.realnum;
      }
      else if (sym->basicdt == INTEGER) {
        tok->tokentype = NUMBERTOK;
        tok->basicdt = INTEGER;
        tok->intval = sym->constval.intnum;
      }

      if (DEBUG & DB_FINDID) { 
        printf("hit constant\n");
        dbugprinttok(sym);
        dbugprinttok(tok);
      };
      return tok;
    }

    typ = sym->datatype;
    tok->symtype = typ;
    if ( typ->kind == BASICTYPE ||
         typ->kind == POINTERSYM)
        tok->basicdt = typ->basicdt;

    if (DEBUG & DB_FINDID) { 
      printf("hit identifier\n");
      dbugprinttok(sym);
      dbugprinttok(tok);
    };

    return tok;
  }

/* findtype looks up a type name in the symbol table, puts the pointer
   to its type into tok->symtype, returns tok. */

TOKEN findtype(TOKEN tok) {
    SYMBOL sym = searchst(tok->stringval);
    if (sym->kind == TYPESYM) {
      sym = sym->datatype;
   }
    tok->symtype = sym;
    if (DEBUG & DB_FINDTYPE) {
      printf("finding type\n");
      dbugprinttok(tok);
    }
    return tok;
  }

/* reducedot handles a record reference.
   dot is a (now) unused token that is recycled. */
TOKEN reducedot(TOKEN var, TOKEN dot, TOKEN field) {
  
  printf("reducedot\n");
  printf("var: \n");
  ppexpr(var);
  printf("\n");
  printf("field->stringval: %s\n", field->stringval);
  printf("\n");
  

  

  SYMBOL recordSymbol = var->symtype;
  SYMBOL moverField;
  if(recordSymbol->kind != RECORDSYM){
    printf("Called on non-record type\n");
    printf("recordSymbol->namestring: %s\n", recordSymbol->namestring);
    recordSymbol = recordSymbol->datatype;
    printf("New recordSymbol->namestring: %s\n", recordSymbol->namestring);
    moverField = recordSymbol->datatype->datatype;
  }
  else{
    moverField = recordSymbol->datatype;
  }


  printf("recordSymbol->namestring: %s\n", recordSymbol->namestring);



  int fieldOffset = 0;
  while (moverField != NULL){
    printf("moverField->namestring: %s\n", moverField->namestring);
    // if (moverField->basicdt){
    //   printf("moverField->basicdt: %s\n", moverField->basicdt);
    // }else{
    //   printf("moverField->basicdt is null\n");
    // }
    
    if (strcmp(moverField->namestring, field->stringval) == 0){
      var->symtype = moverField;

      fieldOffset = moverField->offset;
      printf("found field match\n");
      break;
    }
    moverField = moverField->link;
  }

  printf("offset: %d\n", fieldOffset);

  TOKEN offsetToken = makeintc(fieldOffset);

  TOKEN referenceTok = makearef(var, offsetToken, NULL);

  if (moverField) {
    printf("setting basicdt\n");
    referenceTok->symtype = moverField;
    printf("referenceTok->symtype->namestring: %s\n",
    referenceTok->symtype->datatype->namestring);
    printf("referenceTok->symtype->basicdt: %d\n", referenceTok->symtype->datatype->basicdt);
    referenceTok->basicdt = referenceTok->symtype->datatype->basicdt;
  }
  else{
    printf("moverField is null\n");
    // return NULL;
  }


  return referenceTok;
 
}


/* arrayref processes an array reference a[i]
   subs is a list of subscript expressions.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN arrayref(TOKEN arr, TOKEN tok, TOKEN subs, TOKEN tokb) {
  if (subs->link){
    printf("subs is not null\n");

  TOKEN curArr = copytok(arr);
  TOKEN retTok;
  TOKEN variableTree = NULL;
  
  int rollingOffset = 0;
  int count = 0;

  while (subs) {
    printf("\ncount: %d\n", count);
    int low = curArr->symtype->lowbound;
    int high = curArr->symtype->highbound;
    int size;
    
    if (low == 1){
      size = (curArr->symtype->size / (high + low - 1));
    }

    else{
      size = (curArr->symtype->size / (high + low + 1));
    }
    TOKEN elesize = makeintc(size);
    printf("low: %d\n", low);
    printf("high: %d\n", high);
    printf("size: %d\n", size);

    TOKEN indexTok;
    TOKEN timesop = makeop(TIMESOP);

    if (subs->tokentype == NUMBERTOK) {
      rollingOffset += size * subs->intval - size * low;;
    }

    else if (subs->tokentype == IDENTIFIERTOK){
      indexTok = talloc();
      indexTok->tokentype = IDENTIFIERTOK;
      strcpy(indexTok->stringval, subs->stringval);
      indexTok->basicdt = STRINGTYPE;
      elesize->link = indexTok;
      timesop->operands = elesize;
    }



    if (low == 1){
      rollingOffset -= size;
    }
    

    retTok = makearef(curArr, makeintc(rollingOffset), NULL);
    retTok->symtype = curArr->symtype->datatype;


    curArr = retTok;



    if (subs->tokentype == NUMBERTOK) {
      int offset = size * subs->intval - size * low;
      retTok->link = makeintc(offset);
      retTok->link->tokentype = NUMBERTOK;
    }
    else if (subs->tokentype == IDENTIFIERTOK) {
        if (variableTree){
          TOKEN varPlus = makeop(PLUSOP);
          varPlus->operands = variableTree;
          varPlus->operands->link = timesop;
      }
      else{
        variableTree = timesop;
      }
    }


    subs = subs->link;
    count += 1;
  }

  printf("rolling offset: %d\n", rollingOffset);
  if(variableTree != NULL){
    ppexpr(variableTree);
  }

  TOKEN finalOffset = makeop(PLUSOP);

  finalOffset->operands = makeintc(rollingOffset);
  finalOffset->operands->link = variableTree;

  TOKEN dimensionalToken =  makearef(arr, finalOffset, NULL);
  // dimensionalToken->symtype = dimensionalToken->symtype->symtype;
  return dimensionalToken;

  }


  
  else{
    printf("subs is null\n");

    TOKEN timesop = makeop(TIMESOP);
    int low = arr->symtype->lowbound;
    int high = arr->symtype->highbound;
    int size;
    
    size = (arr->symtype->size / (high - low + 1));
    TOKEN elesize = makeintc(size);


    TOKEN indexTok;

    if (subs->tokentype == NUMBERTOK) {
      indexTok = makeintc(subs->intval);
    }

    else if (subs->tokentype == IDENTIFIERTOK){
      indexTok = talloc();
      indexTok->tokentype = IDENTIFIERTOK;
      strcpy(indexTok->stringval, subs->stringval);
      indexTok->basicdt = STRINGTYPE;
    }


    elesize->link = indexTok;
    timesop->operands = elesize;
    TOKEN nsize;




    nsize = makeintc(-size * low);
    nsize->link = timesop;
    
    TOKEN plusop = makeop(PLUSOP);
    plusop->operands = nsize;
    
    printf("plusop\n");
    ppexpr(plusop);
    printf("\n");

    TOKEN offsetTok;
    if (subs->tokentype == NUMBERTOK) {
      printf("subs->intval: %d\n", subs->intval);
      printf("size: %d\n", size);
      printf("subs->intval * size: %d\n", indexTok->intval * size + nsize->intval);
      offsetTok = makeintc(indexTok->intval * size + nsize->intval);
    }

    else if (subs->tokentype == IDENTIFIERTOK){
      offsetTok = plusop;
    }

    printf("offsetTok\n");
    ppexpr(offsetTok);
    printf("\n");
    TOKEN retTok = makearef(arr, offsetTok, tokb);
    retTok->symtype->datatype = retTok->symtype->datatype->datatype;


    if (subs->tokentype == IDENTIFIERTOK){
      retTok->link = indexTok;
      retTok->link->tokentype = IDENTIFIERTOK;

    }


    printf("retTok\n");
    ppexpr(retTok);
    printf("\n");


    return retTok;
  }


}
  

TOKEN dolabel(TOKEN labeltok, TOKEN tok, TOKEN statement) {
    // Convert label value to index in the labels array.
    int labelValue = labeltok->intval;
    int labelIndex = -1;
    
    // Search for the label index.
    for(int i = 0; i < i < sizeof(labels) / sizeof(labels[0]); i++) {
        if (labels[i] == labelValue) {
            labelIndex = i;
            break;
        }
    }
    if (labelIndex == -1){
      
      return NULL;
    }

    // Construct the label token with the found index.
    TOKEN indexToken = makeintc(labelIndex);
    labeltok = makeop(LABELOP); // Assuming LABELOP is defined correctly elsewhere.
    labeltok->link = statement;
    
    labeltok->operands = indexToken;
    
    // Link the label operation with the provided statement using progn.
    tok = makeprogn(tok, labeltok);
    
    return tok;
}

/* dogoto is the action for a goto statement.
   tok is a (now) unused token that is recycled. */
TOKEN dogoto(TOKEN tok, TOKEN labeltok) {
    int labelValue = labeltok->intval;
    int labelIndex = -1;
    
    // Search for the label index.
    for(int i = 0; i < i < sizeof(labels) / sizeof(labels[0]); i++) {
        if (labels[i] == labelValue) {
            labelIndex = i;
            break;
        }
    }
    if (labelIndex == -1){
      
      return NULL;
    }


    return (makegoto(labelIndex));


}


/* dopoint handles a ^ operator.
   tok is a (now) unused token that is recycled. */
TOKEN dopoint(TOKEN var, TOKEN tok) {
  tok->symtype = var->symtype->datatype->datatype;
  ppexpr(tok);
  printf("\n");
  tok->operands = var;
  

  return tok;
}

/* install variables in symbol table */
void instvars(TOKEN idlist, TOKEN typetok)
  {  SYMBOL sym, typesym; int align;
     typesym = typetok->symtype;
     align = alignsize(typesym);
     while ( idlist != NULL )   /* for each id */
       {  sym = insertsym(idlist->stringval);
          sym->kind = VARSYM;
          sym->offset =
              wordaddress(blockoffs[blocknumber],
                          align);
          sym->size = typesym->size;
          blockoffs[blocknumber] =
                         sym->offset + sym->size;
          sym->datatype = typesym;
          sym->basicdt = typesym->basicdt;
          idlist = idlist->link;
        };
  }

/* instconst installs a constant in the symbol table */
void instconst(TOKEN idtok, TOKEN consttok) {
  SYMBOL sym;
  sym = insertsym(idtok->stringval);
  sym->kind = CONSTSYM;
  sym->basicdt = consttok->basicdt;
  if(sym->basicdt == REAL) {
      sym->constval.realnum = consttok->realval;
  }

  if(sym->basicdt == INTEGER) 
  {
      sym->constval.intnum = consttok->intval;
  }
  if (DEBUG & DB_INSTCONST) {
    printf("install const\n");
    dbugprinttok(sym);
  }
}

/* instlabel installs a user label into the label table */
void  instlabel (TOKEN num) {
  labels[labelnumber++] = num->intval;  

}

/* instenum installs an enumerated subrange in the symbol table,
   e.g., type color = (red, white, blue)
   by calling makesubrange and returning the token it returns. */
TOKEN instenum(TOKEN idlist) {
  int count = 0;

  TOKEN list = copytok(idlist);
  while (list) {
    instconst(list, makeintc(count));
    count ++;
    list = list->link;
  }

  TOKEN tok = makesubrange(idlist, 0, count - 1);
  if (DEBUG & DB_INSTENUM) {
    printf("install enum\n");
    dbugprinttok(idlist);
  }

  return tok;
}

/* instdotdot installs a .. subrange in the symbol table.
   dottok is a (now) unused token that is recycled. */
TOKEN instdotdot(TOKEN lowtok, TOKEN dottok, TOKEN hightok) {
  int low = lowtok->intval;
  int high = hightok->intval;

  if (DEBUG & DB_INSTDOTDOT) {
    printf("install dot dot\n");
    dbugprinttok(lowtok);
    dbugprinttok(hightok);
  }

  return makesubrange(dottok, low, high);
}

/* instarray installs an array declaration into the symbol table.
   bounds points to a SUBRANGE symbol table entry.
   The symbol table pointer is returned in token typetok. */
TOKEN instarray(TOKEN bounds, TOKEN typetok) {

    // Recursively call instarray to ensure correct dimension order
    if (bounds->link) {
        typetok = instarray(bounds->link, typetok);
    }

    SYMBOL subrange = bounds->symtype;
    int low = subrange->lowbound;
    int high = subrange->highbound;
    SYMBOL typeSym;

    if (typetok->symtype){
      typeSym = typetok->symtype;
      printf("installed array with type of typetok %s\n", typeSym->namestring);
    }
    else{
      typeSym = searchst(typetok->stringval);
    }
    
    SYMBOL arraySym = symalloc();
    arraySym->kind = ARRAYSYM;
    arraySym->datatype = typeSym; 


    arraySym->lowbound = low;
    arraySym->highbound = high;

    if (typeSym->kind == ARRAYSYM) {
        arraySym->size = (high - low + 1) * typeSym->size;
    } else {

        arraySym->size = (high - low + 1) * typeSym->size;
    }

    typetok->symtype = arraySym;  


    return typetok;
}


/* instfields will install type in a list idlist of field name tokens:
   re, im: real    put the pointer to REAL in the RE, IM tokens.
   typetok is a token whose symtype is a symbol table pointer.
   Note that nconc() can be used to combine these lists after instrec() */
TOKEN instfields(TOKEN idlist, TOKEN typetok) {
  printf("instfields\n");
  printf("typetok->stringval: %s\n", typetok->stringval);
  SYMBOL symtypeTypeTok = searchst(typetok->stringval);
  printf("\n");
  TOKEN mover = idlist;

  while(mover != NULL){
    printf("mover->stringval %s\n", mover->stringval); 
    mover->symtype = symtypeTypeTok;
    printf("mover->symtype->namestring %s\n", mover->symtype->namestring);
    mover = mover->link;
  }


  return idlist;
}

/* instrec will install a record definition.  Each token in the linked list
   argstok has a pointer its type.  rectok is just a trash token to be
   used to return the result in its symtype */
TOKEN instrec(TOKEN rectok, TOKEN argstok) {
  printf("instrec\n");
  ppexpr(rectok);
  printf("\n");

  SYMBOL recordSymbol = symalloc();
  recordSymbol->kind = RECORDSYM;
  rectok->symtype = recordSymbol;

  int curOffset = 0;

  SYMBOL prev = NULL;

  while (argstok) {
    printf("argstok\n");
    printf("argstok->stringval: %s\n", argstok->stringval);
    printf("\n");
    SYMBOL field = makesym(argstok->stringval);
    field->datatype = argstok->symtype;
    field->size = argstok->symtype->size;
    int newSize = wordaddress(curOffset, alignsize(argstok->symtype));
    field->offset = newSize;
    curOffset = newSize + argstok->symtype->size;

    if (prev == NULL) {
      recordSymbol->datatype = field;
    } 
    else {
      prev->link = field;

    }
    prev = field;
    field->link = NULL;
    argstok = argstok->link;
    
  }

  recordSymbol->size = wordaddress(curOffset, 16); 

  return rectok;
}


/* instpoint will install a pointer type in symbol table */
TOKEN instpoint(TOKEN tok, TOKEN typename) {

  SYMBOL typesym = searchins(typename->stringval);


  SYMBOL pointsym = symalloc();
  pointsym->datatype = typesym;
  pointsym->size = basicsizes[POINTER];
  pointsym->kind = POINTERSYM;
  pointsym->basicdt = POINTER;

  tok->symtype = pointsym;
  

  return tok;
}


/* insttype will install a type name in symbol table.
   typetok is a token containing symbol table pointers. */
void insttype(TOKEN typename, TOKEN typetok) {
  SYMBOL typesym = searchins(typename->stringval);
  typesym->datatype = typetok->symtype;
  // printf("typesym->datatype->namestring: %s\n", typesym->datatype->namestring);
  typesym->size = typetok->symtype->size;
  typesym->kind = TYPESYM;
  typesym->basicdt = typetok->symtype->basicdt;
  printf("typename: %s\n", typename->stringval); // same as ppexpr typename
  
  printf("typesym->basicdt: %d\n", typesym->basicdt);


  if (DEBUG & DB_INSTTYPE) {
    printf("install type\n");
    dbugprinttok(typename);
    dbugprinttok(typetok);
  }
}


int wordaddress(int n, int wordsize)
  { return ((n + wordsize - 1) / wordsize) * wordsize; }
 
yyerror(s)
  char * s;
  { 
  fputs(s,stderr); putc('\n',stderr);
  }

int main(void)          /*  */
  { int res;
    initsyms();
    res = yyparse();
    printf("yyparse result = %8d\n", res);
    printst();
    // printstlevel(1);    /* to see level 0 too, change to:   printst();  */

    if (DEBUG & DB_PARSERES){ 

      dbugprinttok(parseresult);
    }

    ppexpr(parseresult);           /* Pretty-print the result tree */

    /* uncomment following to call code generator. */
     
    // gencode(parseresult, blockoffs[blocknumber], labelnumber);
 
  }