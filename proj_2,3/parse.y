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
  
  
  idlist   :  IDENTIFIER COMMA idlist
                          { $$ = cons($1, $3); }
           |  IDENTIFIER  { $$ = cons($1, NULL); }
           ;

  constantVal   :  STRING
             | signedId
             |  signedNumber
             ;

  constant :  IDENTIFIER EQ constantVal { instconst($1, $3); }
            ;
  
  statementList  :  statement SEMICOLON statementList      { $$ = cons($1, $3); }
             |  statement
             ;
 
  typeList      :  IDENTIFIER EQ TYPE typeList
             |  IDENTIFIER EQ TYPE
             ;

  tblock     :  TYPE typeList vblock       { $$ = $3; }
             |  vblock
             ;

  cblock     :  CONST constantList tblock              { $$ = $3; }
             |  block
             ;

  constantList     :  constant SEMICOLON constantList    
            |  constant SEMICOLON          
            ;  
  
  vblock     :  VAR varspecs block       { $$ = $3; }
             |  block
             ;
  
  lblock     :  LABEL labelValList SEMICOLON block       { $$ = $4; }
             |  block
             ;

  labelValList: NUMBER COMMA labelValList   {instlabel($1);}
             |  NUMBER                      {instlabel($1);}
             ;
             
  varspecs   :  vargroup SEMICOLON varspecs   
             |  vargroup SEMICOLON            
             ;
  
  label      : NUMBER COLON statement       { $$ = dolabel($1, $2, $3); }
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


//helper methods to check if a token is real or integer
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

/* binop links a binary operator op to two operands, lhs and rhs. */
TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs){ 
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

/* makelabel makes a new label, using labelnumber++ */
TOKEN makelabel(){
  TOKEN tok = talloc();
  tok->tokentype = OPERATOR;
  tok->whichval = LABELOP;
  tok->operands = makeintc(labelnumber++);
  return tok;

}

/* makegoto makes a GOTO operator to go to the specified label.
   The label number is put into a number token. */
TOKEN makegoto(int label){
  TOKEN tok = talloc();
  tok->tokentype = OPERATOR;
  tok->whichval = GOTOOP;
  tok->operands = makeintc(label);
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


/* makefuncall makes a FUNCALL operator and links it to the fn and args.
   tok is a (now) unused token that is recycled. */
TOKEN makefuncall(TOKEN tok, TOKEN fn, TOKEN args)
  {  
     fn->link = args;
     tok->tokentype = OPERATOR;  
     tok->operands = fn;
     tok->whichval = FUNCALLOP;
    SYMBOL sym = searchst(fn->stringval);
    if (sym->datatype->datatype){
      tok->basicdt = sym->datatype->datatype->basicdt;
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

/* makewhile makes structures for a while statement.
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
  SYMBOL sym = searchst(tok->stringval);
  tok->symentry = sym;

  if (sym->kind == VARSYM){
    SYMBOL typ = sym->datatype;
    tok->symtype = typ;
    if ( typ->kind == BASICTYPE ||
        typ->kind == POINTERSYM)
        tok->basicdt = typ->basicdt;
  }
  //if symbol isn't var
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


/* findtype looks up a type name in the symbol table, puts the pointer
   to its type into tok->symtype, returns tok. */
TOKEN findtype(TOKEN tok){
  SYMBOL sym = searchst(tok->stringval);
  tok->symentry = sym;
  tok->symtype = sym;
  return tok;
}



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

/* dolabel is the action for a label of the form   <number>: <statement>
   tok is a (now) unused token that is recycled. */
TOKEN dolabel(TOKEN labeltok, TOKEN tok, TOKEN statement){
  tok = makeprogn(tok, labeltok);

  int labelValue = labeltok->intval;
  int labelIndex = -1;

  for(int i = 0; i < sizeof(labels) / sizeof(labels[0]); i++) {
    if (labels[i] == labelValue) {
      labelIndex = i;
      break;
    }
  }

  if (labelIndex == -1){
    fprintf(stderr, "Label not found\n");
    return NULL;
  }

  TOKEN indexToken = makeintc(labelIndex);
  labeltok->operands = indexToken;
  labeltok->link = statement;


  return tok;
  


}

/* instlabel installs a user label into the label table */
void  instlabel (TOKEN num){
  labels[labelnumber++] = num->intval;  

}

/* nconc concatenates two token lists, destructively, by making the last link
   of lista point to listb.
   (nconc '(a b) '(c d e))  =  (a b c d e)  */
/* nconc is useful for putting together two fieldlist groups to
   make them into a single list in a record declaration. */
/* nconc should return lista, or listb if lista is NULL. */
TOKEN nconc(TOKEN lista, TOKEN listb){

  if (lista == NULL){
    return listb;
  }
  
  TOKEN mover = lista;
  while(mover->link != NULL){
    mover = mover->link;
  }
  mover->link = listb;

  return lista;

}


/* wordaddress pads the offset n to be a multiple of wordsize.
   wordsize should be 4 for integer, 8 for real and pointers,
   16 for records and arrays */
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




/* instrec will install a record definition.  Each token in the linked list
   argstok has a pointer its type.  rectok is just a trash token to be
   used to return the result in its symtype */
TOKEN instrec(TOKEN rectok, TOKEN argstok);

/* instfields will install type in a list idlist of field name tokens:
   re, im: real    put the pointer to REAL in the RE, IM tokens.
   typetok is a token whose symtype is a symbol table pointer.
   Note that nconc() can be used to combine these lists after instrec() */
TOKEN instfields(TOKEN idlist, TOKEN typetok);

/* fillintc smashes tok, making it into an INTEGER constant with value num */
TOKEN fillintc(TOKEN tok, int num);


/* makepnb is like makeprogn, except that if statements is already a progn,
   it just returns statements.  This is optional. */
TOKEN makepnb(TOKEN tok, TOKEN statements);

/* appendst makes a progn containing statements followed by more */
TOKEN appendst(TOKEN statements, TOKEN more);

/* dogoto is the action for a goto statement.
   tok is a (now) unused token that is recycled. */
TOKEN dogoto(TOKEN tok, TOKEN labeltok);

/* settoktype sets up the type fields of token tok.
   typ = type pointer, ent = symbol table entry of the variable  */
void  settoktype(TOKEN tok, SYMBOL typ, SYMBOL ent);


/* makewhile makes structures for a while statement.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN makewhile(TOKEN tok, TOKEN expr, TOKEN tokb, TOKEN statement);




/* makesubrange makes a SUBRANGE symbol table entry, puts the pointer to it
   into tok, and returns tok. */
TOKEN makesubrange(TOKEN tok, int low, int high);

/* instenum installs an enumerated subrange in the symbol table,
   e.g., type color = (red, white, blue)
   by calling makesubrange and returning the token it returns. */
TOKEN instenum(TOKEN idlist);

/* instdotdot installs a .. subrange in the symbol table.
   dottok is a (now) unused token that is recycled. */
TOKEN instdotdot(TOKEN lowtok, TOKEN dottok, TOKEN hightok);


/* searchins will search for symbol, inserting it if not present. */
SYMBOL searchins(char name[]);

/* insttype will install a type name in symbol table.
   typetok is a token containing symbol table pointers. */
void  insttype(TOKEN typename, TOKEN typetok);

/* instpoint will install a pointer type in symbol table */
TOKEN instpoint(TOKEN tok, TOKEN typename);



/* makeplus makes a + operator.
   tok (if not NULL) is a (now) unused token that is recycled. */
TOKEN makeplus(TOKEN lhs, TOKEN rhs, TOKEN tok){
  tok = makeop(PLUSOP);
  return tok;
}

/* addint adds integer off to expression exp, possibly using tok */
TOKEN addint(TOKEN exp, TOKEN off, TOKEN tok);

/* addoffs adds offset, off, to an aref expression, exp */
TOKEN addoffs(TOKEN exp, TOKEN off);

/* mulint multiplies expression exp by integer n */
TOKEN mulint(TOKEN exp, int n);

/* makearef makes an array reference operation.
   off is be an integer constant token
   tok (if not NULL) is a (now) unused token that is recycled. */
TOKEN makearef(TOKEN var, TOKEN off, TOKEN tok);

/* reducedot handles a record reference.
   dot is a (now) unused token that is recycled. */
TOKEN reducedot(TOKEN var, TOKEN dot, TOKEN field);
// assert( var->symtype->kind == RECORDSYM );

/* arrayref processes an array reference a[i]
   subs is a list of subscript expressions.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN arrayref(TOKEN arr, TOKEN tok, TOKEN subs, TOKEN tokb);
// assert( arr->symtype->kind == ARRAYSYM );

/* dopoint handles a ^ operator.  john^ becomes (^ john) with type record
   tok is a (now) unused token that is recycled. */
TOKEN dopoint(TOKEN var, TOKEN tok);
//     assert( var->symtype->kind == POINTERSYM );
//     assert( var->symtype->datatype->kind == TYPESYM );

/* instarray installs an array declaration into the symbol table.
   bounds points to a SUBRANGE symbol table entry.
   The symbol table pointer is returned in token typetok. */
TOKEN instarray(TOKEN bounds, TOKEN typetok);
//     assert(bounds->symtype->kind == SUBRANGE );