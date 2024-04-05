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

  constantVal   :  STRING
            | signedId
            |  signedNumber
            ;

  constant   :  IDENTIFIER EQ constantVal { instconst($1, $3); }
            ; 

  statementList  :  statement SEMICOLON statementList      { $$ = cons($1, $3); }
            |  statement
            ;


//
  tdef       :  IDENTIFIER EQ type SEMICOLON    { insttype($1, $3); }
             ;
             
  constantVal      :  tdef constantVal
             |  tdef 
             ;

  fields     :  idlist COLON type             { $$ = instfields($1, $3); }
             ;
  field_list :  fields SEMICOLON field_list   { $$ = nconc($1, $3); }
             |  fields
             ;






  type       :  simpletype
             |  ARRAY LBRACKET stype_list RBRACKET OF type   { $$ = instarray($3, $6); }
             |  RECORD field_list END                          { $$ = instrec($1, $2); }
             |  POINT IDENTIFIER                              { $$ = instpoint($1, $2); }
             ;
  stype_list :  simpletype COMMA stype_list  { $$ = cons($1, $3); }
             |  simpletype                { $$ = cons($1, NULL); }
             ;
  simpletype :  IDENTIFIER   { $$ = findtype($1); }
             |  LPAREN idlist RPAREN         { $$ = instenum($2); }
             |  constantVal DOTDOT constantVal     { $$ = instdotdot($1, $2, $3); }
             ;
             
  tblock     :  TYPE constantVal vblock       { $$ = $3; }
             |  vblock
             ;

//
  cblock     :  CONST constantList tblock              { $$ = $3; }
             |  tblock
             ;

  constantList     :  constant SEMICOLON constantList    
            |  constant SEMICOLON          
            ;  

  vblock     :  VAR varspecs block       { $$ = $3; }
             |  block
             ;


  lblock     :  LABEL labelValList SEMICOLON cblock  { $$ = $4; }
             |  block
             ;
  labelValList    :  NUMBER COMMA labelValList  { instlabel($1); }
            |  NUMBER                { instlabel($1); }
            ;           
  varspecs   :  vargroup SEMICOLON varspecs   
             |  vargroup SEMICOLON            
             ;

  label      :  NUMBER COLON statement          { $$ = dolabel($1, $2, $3); }
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
            |  WHILE expr DO statement       { $$ = makewhile($1, $2, $3, $4); }
            |  GOTO NUMBER                  { $$ = dogoto($1, $2); }

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
  expressionList  :  expr COMMA expressionList           { $$ = cons($1, $3); }
             |  expr
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

  factor     : 
              variable
             |  STRING
             | NUMBER
             |  NIL 
             |  functionCall
             |  LPAREN expr RPAREN             { $$ = $2; }       
             |  NOT factor          { $$ = unaryop($1, $2); }
             ;

  
  variable   :  IDENTIFIER                            { $$ = findid($1); }
            |  variable LBRACKET expressionList RBRACKET   { $$ = arrayref($1, $2,
             $3, $4); }
             |  variable DOT IDENTIFIER                { $$ = reducedot($1, $2, $3); }
             |  variable POINT                         { $$ = dopoint($1, $2); }
             ;
%%


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

 int labelnumber = 0;  
 int labels[100];

/* cons links a new item onto the front of a list.  Equivalent to a push.
   (cons 'a '(b c))  =  (a b c)    */
TOKEN cons(TOKEN item, TOKEN list)           /* add item to front of list */
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

  return temp;
}




/* binop links a binary operator op to two operands, lhs and rhs. */
TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs){ 
    
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


    
  

/* unaryop links a unary operator op to one operand, lhs */
TOKEN unaryop(TOKEN op, TOKEN lhs){
  lhs->link = NULL;
  op->operands = lhs;
  if (DEBUG & DB_BINOP)
       { printf("unaryop\n");
         dbugprinttok(op);
         dbugprinttok(lhs);
       };
  return op;
}


/* makeop makes a new operator token with operator number opnum.
   Example:  makeop(FLOATOP)  */
TOKEN makeop(int op){
    TOKEN tok = talloc();
    tok->whichval = op;
    tok->tokentype = OPERATOR;

    return tok;
}

/* makefloat forces the item tok to be floating, by floating a constant
   or by inserting a FLOATOP operator */
TOKEN makefloat(TOKEN tok){
  if (tok->tokentype == NUMBERTOK){
    tok->realval = (double) tok->intval;
    tok->basicdt = REAL;
    return tok;
  }
  TOKEN floatToken = makeop(FLOATOP);
  floatToken->operands = tok;
  return floatToken;
    

}



/* makefix forces the item tok to be integer, by truncating a constant
   or by inserting a FIXOP operator */
TOKEN makefix(TOKEN tok){
  if(tok->tokentype == NUMBERTOK){
    tok->intval = (int) tok->realval;
    tok->basicdt = INTEGER;
    return tok;
  } else{
    TOKEN fixToken = makeop(FIXOP);
    fixToken->operands = tok;
    return fixToken;
  }
}

/* makeintc makes a new integer number token with num as its value */
TOKEN makeintc(int num) {
  TOKEN tok = talloc();
  tok->intval = num;
  tok->tokentype = NUMBERTOK;
  tok->basicdt = INTEGER;
  if (DEBUG & DB_MAKENUM) {
      printf("makeintc\n");
      dbugprinttok(tok);
  }
  return tok;
}


/* copytok makes a new token that is a copy of origtok */
TOKEN copytok(TOKEN target) {
  TOKEN copy = talloc();
  copy->tokentype = target->tokentype;
  copy->symentry = target->symentry;
  copy->basicdt = target->basicdt;
  copy->link = target->link;
  copy->whichval = target->whichval;
  copy->intval = target->intval;
  copy->realval = target->realval;
  copy->symtype = target->symtype;

  return copy;
}


/* makeif makes an IF operator and links it to its arguments.
   tok is a (now) unused token that is recycled to become an IFOP operator */
TOKEN makeif(TOKEN tok, TOKEN exp, TOKEN thenpart, TOKEN elsepart)
  {  //decomposing if token
     tok->tokentype = OPERATOR;  

    //determining expression
     tok->operands = exp;
     tok->whichval = IFOP;

     //exp->thenpart->elsepart
     thenpart->link = elsepart;
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


/* makeprogn makes a PROGN operator and links it to the list of statements.
   tok is a (now) unused token that is recycled. */
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


/* makelabel makes a new label, using labelnumber++ */
TOKEN makelabel(){
  TOKEN tok = talloc();
  tok->tokentype = OPERATOR;
  tok->whichval = LABELOP;
  tok->operands = makeintc(labelnumber++);
  return tok;

}

/* Corrected dolabel function. Assumes labels and labelnumber are correctly declared and accessible. */
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

/* instlabel installs a user label into the label table */
void instlabel (TOKEN num) {
  labels[labelnumber++] = num->intval;  

}


/* makegoto makes a GOTO operator to go to the specified label.
   The label number is put into a number token. */
TOKEN makegoto(int label){
  TOKEN tok = makeop(GOTOOP);
  tok->operands = makeintc(label);
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



/* findid finds an identifier in the symbol table, sets up symbol table
   pointers, changes a constant to its number equivalent */
TOKEN findid(TOKEN tok) { /* the ID token */
    SYMBOL symbol =  searchst(tok->stringval);
    tok->symentry = symbol;
    

    if (symbol->kind == CONSTSYM) {
      tok->tokentype = NUMBERTOK;
      switch(symbol->basicdt){
        case INTEGER:
          tok->intval = symbol->constval.intnum;
          tok->basicdt = INTEGER;
          break;
        case REAL:
          tok->realval = symbol->constval.realnum;
          tok->basicdt = REAL;
          break;
        default:
          break;
      }

      return tok;
    }
    
    tok->symtype = symbol->datatype;
    if ( symbol->datatype->kind == BASICTYPE ||
         symbol->datatype->kind == POINTERSYM)
        tok->basicdt = symbol->datatype->basicdt;


    return tok;
  }



/* instconst installs a constant in the symbol table */
void instconst(TOKEN idtok, TOKEN consttok){

  //create and return the symbol table entry
  SYMBOL constSymbol = insertsym(idtok->stringval);

  //update the symbol table entry to reflect the token's value and data type
  constSymbol->basicdt = consttok->basicdt;
  constSymbol->kind = CONSTSYM;

  int type = consttok->basicdt;
  if (type == INTEGER){
    constSymbol->constval.intnum = consttok->intval;
  }
  else if (type == REAL){
    constSymbol->constval.realnum = consttok->realval;
  }
  else {
    return;
  }
}


/* makesubrange makes a SUBRANGE symbol table entry, puts the pointer to it
   into tok, and returns tok. */
TOKEN makesubrange(TOKEN tok, int low, int high) {

  SYMBOL rangeSym = symalloc();
  tok->symtype = rangeSym;

  rangeSym->lowbound = low;
  rangeSym->highbound = high;
  rangeSym->basicdt = INTEGER;
  rangeSym->kind = SUBRANGE;
  rangeSym->size = sizeof(INTEGER);

  return tok;
}



/* instenum installs an enumerated subrange in the symbol table,
   e.g., type color = (red, white, blue)
   by calling makesubrange and returning the token it returns. */
TOKEN instenum(TOKEN idlist){
  int numOptions = 0;

  TOKEN traversal = copytok(idlist);

  while (traversal != NULL) {
    instconst(traversal, makeintc(numOptions++));
    traversal = traversal->link;
  }

  TOKEN enumRange = makesubrange(idlist, 0, numOptions - 1);


  return enumRange;
}



/* instdotdot installs a .. subrange in the symbol table.
   dottok is a (now) unused token that is recycled. */
TOKEN instdotdot(TOKEN lowtok, TOKEN dottok, TOKEN hightok){

  return makesubrange(dottok, lowtok->intval,  hightok->intval);
}



/* findtype looks up a type name in the symbol table, puts the pointer
   to its type into tok->symtype, returns tok. */
TOKEN findtype(TOKEN tok){
  SYMBOL sym = searchst(tok->stringval);
  if (sym->kind == TYPESYM) {
      sym = sym->datatype;
   }
  tok->symtype = sym;
  return tok;
}

/* wordaddress pads the offset n to be a multiple of wordsize.
   wordsize should be 4 for integer, 8 for real and pointers,
   16 for records and arrays */
int wordaddress(int n, int wordsize)
  { return ((n + wordsize - 1) / wordsize) * wordsize; }
 


/* instvars will install variables in symbol table.
   typetok is a token containing symbol table pointer for type. */
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


/* insttype will install a type name in symbol table.
   typetok is a token containing symbol table pointers. */
void  insttype(TOKEN typename, TOKEN typetok) {
  SYMBOL typesym = searchins(typename->stringval);
  typesym->kind = TYPESYM;
  typesym->datatype = typetok->symtype;
  typesym->size = typetok->symtype->size;


}


/* instpoint will install a pointer type in symbol table */
TOKEN instpoint(TOKEN tok, TOKEN typename) {

  SYMBOL typeSymbol = searchins(typename->stringval);


  SYMBOL pointSymbol = symalloc();
  pointSymbol->kind = POINTERSYM;
  pointSymbol->basicdt = POINTER;
  pointSymbol->datatype = typeSymbol;
  pointSymbol->size = sizeof(POINTER);

  tok->symtype = pointSymbol;



  return tok;
}



/* instrec will install a record definition.  Each token in the linked list
   argstok has a pointer its type.  rectok is just a trash token to be
   used to return the result in its symtype */
TOKEN instrec(TOKEN rectok, TOKEN argstok) {
  
  SYMBOL recordSymbol = symalloc();
  recordSymbol->kind = RECORDSYM;
  rectok->symtype = recordSymbol;

  int curOffset = 0;

  SYMBOL prev = NULL;

  while (argstok) {
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

  recordSymbol->size = wordaddress(curOffset, 8); 

  return rectok;
}



/* instfields will install type in a list idlist of field name tokens:
   re, im: real    put the pointer to REAL in the RE, IM tokens.
   typetok is a token whose symtype is a symbol table pointer.
   Note that nconc() can be used to combine these lists after instrec() */
TOKEN instfields(TOKEN idlist, TOKEN typetok){

  TOKEN mover = idlist;

  while(mover != NULL){
    mover->symtype = typetok->symtype;
    mover = mover->link;
  }

  return idlist;
  
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


/* makearef makes an array reference operation.
   off is be an integer constant token
   tok (if not NULL) is a (now) unused token that is recycled. */
TOKEN makearef(TOKEN var, TOKEN off, TOKEN tok){
  
  TOKEN finalOffset = off; // Start with the assumption we'll use the provided offset

  if (var->link){
    
    if (var->link->tokentype == NUMBERTOK){
    finalOffset->intval = var->link->intval + off->intval;
    }
    else if(var->link->tokentype == IDENTIFIERTOK){
      TOKEN plusOp = makeop(PLUSOP);
      plusOp->operands = var->link;
      plusOp->link = off;
      finalOffset = plusOp;
      finalOffset->tokentype = IDENTIFIERTOK;
    }
    
  }

  if (off->basicdt == INTEGER  &&  var->whichval == AREFOP) {
    
    TOKEN secondOffset = var->operands->link;
    if (secondOffset->tokentype == NUMBERTOK) { // Assuming secondOffset is the offset in the nested AREF
      // Directly sum the integer values of the offsets
      int sumOffsets = secondOffset->intval + off->intval;
      finalOffset = makeintc(sumOffsets); // Use this new offset for the final AREF
    }
  }

  // Now, we create the AREF operation using the possibly updated finalOffset
  TOKEN arefTok = makeop(AREFOP);
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
  
  arefTok->operands = var;
  
  
  arefTok->symentry = var->symentry;
  
  if (var->symentry && var->symentry->datatype) {
    arefTok->basicdt = var->symentry->datatype->basicdt;
  }

  

  return arefTok;
}









/* reducedot handles a record reference.
   dot is a (now) unused token that is recycled. */
TOKEN reducedot(TOKEN var, TOKEN dot, TOKEN field) {



  SYMBOL recordSymbol = var->symentry;
  SYMBOL moverField = recordSymbol->datatype->datatype;

  int fieldOffset = 0;
  while (moverField != NULL){
    if (strcmp(moverField->namestring, field->stringval) == 0){
      var->symentry = moverField;

      fieldOffset = moverField->offset;
      break;
    }
    moverField = moverField->link;
  }

  TOKEN offsetToken = makeintc(fieldOffset);

  TOKEN referenceTok = makearef(var, offsetToken, NULL);

  if (moverField) {
    referenceTok->basicdt = moverField->datatype->basicdt;
  }


  return referenceTok;
 
}


/* arrayref processes an array reference a[i]
   subs is a list of subscript expressions.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN arrayref(TOKEN arr, TOKEN tok, TOKEN subs, TOKEN tokb) {
  if (subs->link){
    TOKEN curArr = copytok(arr);
    TOKEN retTok;
    TOKEN variableTree = NULL;
    
    int rollingOffset = 0;
    int count = 0;

    while (subs) {
      int low = curArr->symtype->lowbound;
      int high = curArr->symtype->highbound;
      int size;
      
      if (low == 1){
        size = (curArr->symtype->size / (high + low - 1));
      }

      else{
        size = (curArr->symtype->size / (high + low + 1));
      }
      TOKEN unitSize = makeintc(size);


      TOKEN indexTok;
      TOKEN timesOp = makeop(TIMESOP);

      if (subs->tokentype == NUMBERTOK) {
        rollingOffset += size * subs->intval - size * low;;
      }

      else if (subs->tokentype == IDENTIFIERTOK){
        indexTok = talloc();
        indexTok->tokentype = IDENTIFIERTOK;
        strcpy(indexTok->stringval, subs->stringval);
        indexTok->basicdt = STRINGTYPE;
        unitSize->link = indexTok;
        timesOp->operands = unitSize;
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
            varPlus->operands->link = timesOp;
        }
        else{
          variableTree = timesOp;
        }
      }


      subs = subs->link;
      count += 1;
    }

    
    TOKEN finalOffset = makeplus(makeintc(rollingOffset),variableTree, NULL);


    return makearef(arr, finalOffset, NULL);

  }
  else{
    TOKEN timesOp = makeop(TIMESOP);
    int low = arr->symtype->lowbound;
    int high = arr->symtype->highbound;
    int size;
    
    if (low == 1){
      size = (arr->symtype->size / (high + low - 1));
    }
    else{
      size = (arr->symtype->size / (high + low + 1));
    }
    TOKEN unitSize = makeintc(size);


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


    unitSize->link = indexTok;
    timesOp->operands = unitSize;
    TOKEN negativeUnit;




    negativeUnit = makeintc(-1 * size);
    negativeUnit->link = timesOp;
    
    TOKEN plusOp = makeop(PLUSOP);
    plusOp->operands = negativeUnit;
    


    TOKEN retTok = makearef(arr, plusOp, tokb);

    if (subs->tokentype == NUMBERTOK) {
      int offset = size * subs->intval - size * low;
      retTok->link = makeintc(offset);
      retTok->link->tokentype = NUMBERTOK;
    }

    else if (subs->tokentype == IDENTIFIERTOK){
      retTok->link = indexTok;
      retTok->link->tokentype = IDENTIFIERTOK;

    }


    return retTok;
  }


}


int  checkReal(TOKEN tok) {
  return (tok->basicdt == REAL);

}

int checkInt(TOKEN tok) {
  return (tok->basicdt == INTEGER);

}





/* dopoint handles a ^ operator.
   tok is a (now) unused token that is recycled. */
TOKEN dopoint(TOKEN var, TOKEN tok) {
  tok->operands = var;
  tok->symentry = var->symentry->datatype->datatype;
  
  return tok;
}




/* instarray installs an array declaration into the symbol table.
   bounds points to a SUBRANGE symbol table entry.
   The symbol table pointer is returned in token typetok. */
TOKEN instarray(TOKEN bounds, TOKEN typetok) {
  
  if (bounds->link) {
    typetok = instarray(bounds->link, typetok);
  } 
  SYMBOL arrSymbol = symalloc();
  arrSymbol->kind = ARRAYSYM;
  arrSymbol->datatype = typetok->symtype;

  
  arrSymbol->lowbound = bounds->symtype->lowbound;
  arrSymbol->highbound = bounds->symtype->highbound;

  
  if (bounds->link){
    arrSymbol->size = (arrSymbol->lowbound + arrSymbol->highbound - 1) * (typetok->symtype->size);
  }
  else{
    arrSymbol->size = (arrSymbol->highbound - arrSymbol->lowbound +  1) * (typetok->symtype->size);

  }


  typetok->symtype = arrSymbol;

  return typetok;
  }






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

    printstlevel(1);    /* to see level 0 too, change to:   printst();  */

    if (DEBUG & DB_PARSERES){ 

      dbugprinttok(parseresult);
    }

    ppexpr(parseresult);           /* Pretty-print the result tree */

    /* uncomment following to call code generator. */
     
    // gencode(parseresult, blockoffs[blocknumber], labelnumber);
 
  }

