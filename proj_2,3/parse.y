%{     /* pars1.y    Pascal Parser      Gordon S. Novak Jr.  ; 30 Jul 13   */

/* Copyright (c) 2013 Gordon S. Novak Jr. and
   The University of Texas at Austin. */

/* 
 Student: S. Ram Janarthana Raja
 UTEID  : rs53992
 */ 


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
  program    : PROGRAM IDENTIFIER LPAREN idlist RPAREN SEMICOLON cblock DOT { parseresult = makeprogram($2, $4, $7); } ;
             ;

  //
  constant   :  signedId
             |  signedNumber
             |  STRING
             ;
  
  idlist   :  IDENTIFIER COMMA idlist
                          { $$ = cons($1, $3); }
           |  IDENTIFIER  { $$ = cons($1, NULL); }
           ;

  
  constantAssign       :  IDENTIFIER EQ constant { instconst($1, $3); }
             ;
  
  constantList     :  constantAssign SEMICOLON constantList    
             |  constantAssign SEMICOLON          
             ;  
           
  typeList      :  IDENTIFIER EQ TYPE typeList
             |  IDENTIFIER EQ TYPE
             ;
             
  statementList     :  statement SEMICOLON statementList      { $$ = cons($1, $3); }
             |  statement
             ;
  cblock     :  CONST constantList tblock              { $$ = $3; }
             |  tblock
             ;
  tblock     :  TYPE typeList vblock       { $$ = $3; }
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

  block      :  BEGINBEGIN statement endpart   { $$ = makeprogn($1,cons($2, $3)); }  
             ;

  statement  :  block
             |  IF expr THEN statement endif   { $$ = makeif($1, $2, $4, $5); }
             |  assignment
             |  functionCall
             |  FOR assignment TO expr DO statement   { $$ = makefor(1, $1, $2, $3, $4, $5, $6); }
             |  REPEAT statementList UNTIL expr              { $$ = makerepeat($1, $2, $3, $4); }
             ;

  functionCall    :  IDENTIFIER LPAREN expressionList RPAREN    { $$ = makefuncall($2, $1, $3); }
             ;
  expressionList  :  expr COMMA expressionList           { $$ = cons($1, $3); }
             |  expr
             ;
  endpart    :  SEMICOLON statement endpart    { $$ = cons($2, $3); }
             |  END                            { $$ = NULL; }
             ;
  endif      :  ELSE statement                 { $$ = $2; }
             |  /* empty */                    { $$ = NULL; }
             ;
  assignment :  variable ASSIGN expr         { $$ = binop($2, $1, $3); }
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

  signedExpression     :  signedTerm
             |  signedExpression PLUS term                 { $$ = binop($2, $1, $3); }
             |  signedExpression MINUS term                 { $$ = binop($2, $1, $3); }
             |  signedExpression OR term                 { $$ = binop($2, $1, $3); }
             ;

  term       :  term TIMES factor              { $$ = binop($2, $1, $3); }
             |  term DIVIDE factor              { $$ = binop($2, $1, $3); }
             |  term DIV factor              { $$ = binop($2, $1, $3); }
             |  term MOD factor              { $$ = binop($2, $1, $3); }
             |  term AND factor              { $$ = binop($2, $1, $3); }
             |  factor
             ;

  sign       :  PLUS 
             |  MINUS
             ;

  signedId   :  sign IDENTIFIER     { $$ = unaryop($1, $2); }
             |  IDENTIFIER
             ;              
  signedNumber : sign NUMBER        { $$ = unaryop($1, $2); }
             |  NUMBER
             ;

  signedTerm :  sign term           { $$ = unaryop($1, $2); }
             |  term
             ;

  factor     :  NUMBER
             |  NIL 
             |  STRING
             |  variable
             |  LPAREN expr RPAREN             { $$ = $2; }       
             |  functionCall
             |  NOT factor          { $$ = unaryop($1, $2); }
             ;
  type       :  IDENTIFIER   { $$ = findtype($1); }
             ;
  variable   :  IDENTIFIER                            { $$ = findid($1); }
            ;
%%

/* You should add your own debugging flags below, and add debugging
   printouts to your programs.

   You will want to change DEBUG to turn off printouts once things
   are working.
  */

#define DEBUG           31             /* set bits here for debugging, 0 = off  */
#define DB_CONS         0             /* bit to trace cons */
#define DB_BINOP        0             /* bit to trace binop */
#define DB_MAKEIF       0             /* bit to trace makeif */
#define DB_MAKEPROGN    0             /* bit to trace makeprogn */
#define DB_PARSERES     0             /* bit to trace parseresult */
#define DB_MAKEPROGRAM  0
#define DB_MAKENUM      0
#define DB_MAKECOPY     0
#define DB_MAKEFOR      0
#define DB_MAKEFUNCALL  0


 

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

int isReal(TOKEN tok) {
  if(tok->basicdt == REAL)
    return 1;
  else 
    return 0;
}

int isInt(TOKEN tok) {
  if(tok->basicdt == INTEGER)
    return 1;
  else 
    return 0;
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
//helper to create an operator token of specific op type
TOKEN makeOperatorTok(int op){
    TOKEN tok = talloc();
    tok->whichval = op;
    tok->tokentype = OPERATOR;

    return tok;
}
TOKEN makeFloatToken(TOKEN tok){
  if (tok->tokentype == NUMBERTOK){
    tok->basicdt = REAL;
    tok->realval = (double) tok->intval;
    return tok;
  }
  else{
    TOKEN floatToken = makeOperatorTok(FLOATOP);
    floatToken->operands = tok;
    return floatToken;
  }
}
TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs)        /* reduce binary operator */
  { op->operands = lhs;          /* link operands to operator       */
    lhs->link = rhs;             /* link second operand to first    */
    rhs->link = NULL;            /* terminate operand list          */

    int lhType;
    int rhType;

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

    if (lhType == 1 && rhType == 0) {

      TOKEN temptoken = talloc();

      //assignment operation
      if (op->whichval == ASSIGNOP){
        op->basicdt = INTEGER;
        TOKEN temptoken = talloc();
        if (rhs->tokentype == NUMBERTOK) {
          temptoken->intval = (int) rhs->realval;
          temptoken->basicdt = INTEGER;
        }
        else{
          temptoken = makeOperatorTok(FIXOP);
          temptoken->operands = rhs;
        }
        lhs->link = temptoken;
      }

      //computation operation
      else{
        op->basicdt = REAL;
        TOKEN temptoken = makeFloatToken(lhs);
        temptoken->link = rhs;
      }
    }

    //other casting cases
    else if (lhType == 0 && rhType == 0) {
      op->basicdt = REAL;
    }

    else if (lhType == 0 && rhType == 1) {
      op->basicdt = REAL;
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

/* copytok makes a new token that is a copy of origtok */
TOKEN copytok(TOKEN target) {
  TOKEN copy = talloc();
  copy->tokentype = target->tokentype;
  copy->basicdt = target->basicdt;
  copy->symtype = target->symtype;
  copy->symentry = target->symentry;
  copy->link = target->link;
  copy->whichval = target->whichval;
  copy->intval = target->intval;
  copy->realval = target->realval;
  if (DEBUG & DB_MAKECOPY) {
    printf("copytok\n");
    dbugprinttok(copy);
  }
  return copy;
}


void instconst(TOKEN idtok, TOKEN consttok){
  SYMBOL sym = insertsym(idtok->stringval);
  sym->kind = CONSTSYM;
  sym->basicdt = consttok->basicdt;
  int type = consttok->basicdt;
  
  if (type == INTEGER){
    sym->constval.intnum = consttok->intval;
  }
  else if (type == REAL){
    sym->constval.realnum = consttok->realval;
  }



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


//helper method to create a number token
TOKEN makeNumTok(int num) {
  TOKEN tok = talloc();
  tok->intval = num;
  tok->tokentype = NUMBERTOK;
  tok->basicdt = INTEGER;
  if (DEBUG & DB_MAKENUM) {
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


TOKEN makerepeat(TOKEN tok, TOKEN statements, TOKEN tokb, TOKEN expr) {

   TOKEN repeatStart = talloc();
  repeatStart->tokentype = OPERATOR;
  repeatStart->whichval = LABELOP;
  repeatStart->operands = makeNumTok(labelnumber++);
   
   
   tok = makeprogn(tok, repeatStart);

   
   TOKEN shellBody = makeprogn(tokb, statements);
   repeatStart->link = shellBody;

   TOKEN repeatStartGoTo = talloc();
   repeatStartGoTo->tokentype = OPERATOR;
   repeatStartGoTo->whichval = GOTOOP;
   repeatStartGoTo->operands = makeNumTok(labelnumber - 1);
   TOKEN filler = makeprogn((TOKEN) talloc(), NULL);
   filler->link = repeatStartGoTo;

   TOKEN ifs = makeif(talloc(), expr, filler, repeatStartGoTo);
   shellBody->link = ifs;


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



//method to find the symbol entry of specified toke
TOKEN findid(TOKEN tok) { /* the ID token */
  SYMBOL sym = searchst(tok->stringval);
  tok->symentry = sym;

  if (sym->kind == VARSYM){

    SYMBOL typ = sym->datatype;
    tok->symtype = typ;
    if ( typ->kind == BASICTYPE ||
        typ->kind == POINTERSYM)
        tok->basicdt = typ->basicdt;
  }
  else{
    tok->tokentype = NUMBERTOK;
    if (sym->basicdt == INTEGER){
      tok->basicdt = INTEGER;
      tok->intval = sym->constval.intnum;
    }
    else if (sym->basicdt == REAL){
      tok->basicdt = REAL;
      tok->realval = sym->constval.realnum;
    }
  }

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