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
  u_constant :  NUMBER
             |  NIL 
             |  STRING
             ;
  sign       :  PLUS 
             |  MINUS
             ;
  constant   :  sign IDENTIFIER     { $$ = unaryop($1, $2); }
             |  IDENTIFIER
             |  sign NUMBER         { $$ = unaryop($1, $2); }
             |  NUMBER
             |  STRING
             ;
  idlist     :  IDENTIFIER COMMA idlist { $$ = cons($1, $3); }
             |  IDENTIFIER    { $$ = cons($1, NULL); }
             ;
  numlist    :  NUMBER COMMA numlist  { instlabel($1); }
             |  NUMBER                { instlabel($1); }
             ;
  cdef       :  IDENTIFIER EQ constant { instconst($1, $3); }
             ;
  clist      :  cdef SEMICOLON clist    
             |  cdef SEMICOLON          
             ;  
  tdef       :  IDENTIFIER EQ type     { insttype($1, $3); }
             ;
  tlist      :  tdef SEMICOLON tlist
             |  tdef SEMICOLON
             ;
  s_list     :  statement SEMICOLON s_list      { $$ = cons($1, $3); }
             |  statement                  { $$ = cons($1, NULL); }
             ;
  fields     :  idlist COLON type             { $$ = instfields($1, $3); }
             ;
  field_list :  fields SEMICOLON field_list   { $$ = nconc($1, $3); }
             |  fields
             ;
  label      :  NUMBER COLON statement          { $$ = dolabel($1, $2, $3); }
             ;
  lblock     :  LABEL numlist SEMICOLON cblock  { $$ = $4; }
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
             |  constant DOTDOT constant     { $$ = instdotdot($1, $2, $3); }
             ;
  block      :  BEGINBEGIN statement endpart   { $$ = makeprogn($1,cons($2, $3)); }  
             ;
  statement  :  BEGINBEGIN statement endpart   { $$ = makeprogn($1,cons($2, $3)); }
             |  IF expr THEN statement endif   { $$ = makeif($1, $2, $4, $5); }
             |  assignment
             |  funcall
             |  WHILE expr DO statement       { $$ = makewhile($1, $2, $3, $4); }
             |  FOR assignment TO expr DO statement   { $$ = makefor(1, $1, $2, $3, $4, $5, $6); }
             |  REPEAT s_list UNTIL expr              { $$ = makerepeat($1, $2, $3, $4); }
             |  GOTO NUMBER                  { $$ = dogoto($1, $2); }
             |  label
             ;
  funcall    :  IDENTIFIER LPAREN expr_list RPAREN    { $$ = makefuncall($2, $1, $3); }
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
             |  variable LBRACKET expr_list RBRACKET   { $$ = arrayref($1, $2,
             $3, $4); }
             |  variable POINT                         { $$ = dopoint($1, $2); }
             
             |  variable DOT IDENTIFIER                { $$ = reducedot($1, $2, $3); }
             ;
  plus_op    :  PLUS 
             |  MINUS  
             |  OR
             ;
  compare_op :  EQ 
             |  LT 
             |  GT 
             |  NE 
             |  LE 
             |  GE 
             |  IN
             ;
  times_op   :  TIMES 
             |  DIVIDE 
             |  DIV 
             |  MOD 
             |  AND
             ;
  s_expr     :  sign term                       { $$ = unaryop($1, $2); }
             |  term 
             |  s_expr plus_op term                 { $$ = binop($2, $1, $3); }
             ;
  expr       :  expr compare_op s_expr              { $$ = binop($2, $1, $3); }
             |  s_expr 
             ;
  expr_list  :  expr COMMA expr_list           { $$ = cons($1, $3); }
             |  expr                        { $$ = cons($1, NULL); }
             ;
  term       :  term times_op factor              { $$ = binop($2, $1, $3); }
             |  factor
             ;
  factor     :  u_constant
             |  variable
             |  LPAREN expr RPAREN             { $$ = $2; }       
             |  funcall
             |  NOT factor          { $$ = unaryop($1, $2); }
             ;

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

 int labelnumber = 0;  /* sequential counter for internal label numbers */
 int labeltable[50];

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



TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs) {
    // printf("binop\n");
    // dbugprinttok(lhs);
    // dbugprinttok(rhs);

    // Handle NIL as zero.
    if (rhs->whichval == (NIL - RESERVED_BIAS)) {
        rhs = makeintc(0);
    }

    op->operands = lhs; // Link operands to operator.
    lhs->link = rhs; // Link second operand to first.
    rhs->link = NULL; // Terminate operand list.



      // Existing logic
      if (isReal(lhs) && isReal(rhs)) {
          op->basicdt = REAL;
      } else if (isReal(lhs) && isInt(rhs)) {
          op->basicdt = REAL;
          TOKEN ftok = makefloat(rhs);
          lhs->link = ftok;
          // printf("made int rhs into a float\n");
      } else if (isInt(lhs) && isReal(rhs)) {
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
  copy->whichval = target->whichval;
  copy->intval = target->intval;
  copy->realval = target->realval;
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
  
  areftok->symentry = var->symentry;
  areftok->symtype = var->symtype;


  if (var->symentry && var->symentry->datatype) {
    areftok->basicdt = var->symentry->datatype->basicdt;
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
    tok = makeprogn(tok, assign);
    TOKEN label = makelabel();
    int current = labelnumber - 1;
    assign->link = label;

    TOKEN ifs = tokb;
    TOKEN body = tokc;
    body = makeprogn(body, statements);

    TOKEN leoper = makeop(LEOP);
    ifs = makeif(ifs, leoper, body, NULL);
    TOKEN iden = copytok(assign->operands);
    TOKEN iden2 = copytok(iden);
    TOKEN iden3 = copytok(iden);
    iden->link = expr;
    leoper->operands = iden;

    TOKEN assgn = makeop(ASSIGNOP);
    TOKEN increment = makeop(PLUSOP);

    iden3->link=makeintc(1);
    increment->operands=iden3;
    iden2->link=increment;
    assgn->operands=iden2;

    TOKEN gototok = makegoto(current);
    assgn->link = gototok;
    statements->link = assgn;

    leoper->link = body;
    ifs->operands = leoper;
    label->link = ifs;
    if (DEBUG && DB_MAKEFOR) {
         printf("makefor\n");
         dbugprinttok(tok);
    }
    return tok;
}

/* makewhile makes structures for a while statement.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN makewhile(TOKEN tok, TOKEN expr, TOKEN tokb, TOKEN statement) {
  
  TOKEN label = makelabel();
  int current = labelnumber - 1;
  tok = makeprogn(tok, label);

  TOKEN gototok = makegoto(current);
  statement->link = gototok;
  TOKEN body = makeprogn(tokb, statement);

  TOKEN ifs = talloc();
  ifs = makeif(ifs, expr, body, NULL);
  label->link = ifs;

  if (DEBUG && DB_MAKEWHILE) {
     printf("makewhile\n");
     dbugprinttok(tok);
  }
  return tok;
  
}

TOKEN write_fxn_args_type_check(TOKEN fn, TOKEN args) {

	if (args->basicdt == STRINGTYPE) {
		return fn;
	}

	TOKEN out = NULL;

	SYMBOL fn_sym = searchst(fn->stringval);
	if (!fn_sym) {
		printf(" Error: function \"%s\" is not defined.\n", fn->stringval);
		return out;
	}

	int fn_arg_type = fn_sym->datatype->link->basicdt;
	int args_type = args->basicdt;

	if (args_type == STRINGTYPE) {
		out = fn;
	}
	else {

		int replace_index = 5;
		if (strcmp(fn->stringval, "writeln") == 0) {
			replace_index = 7;
		}

		if (strcmp(fn->stringval, "write") == 0) {

			if (args_type == INTEGER) {
				fn->stringval[replace_index] = 'i';
				fn->stringval[replace_index + 1] = '\0';
				out = fn;
			}
			else if (args_type == REAL) {
				fn->stringval[replace_index] = 'f';
				fn->stringval[replace_index + 1] = '\0';
				out = fn;				
			}

		}
		else if (strcmp(fn->stringval, "writeln") == 0) {

			if (args_type == INTEGER) {
				fn->stringval[replace_index] = 'i';
				fn->stringval[replace_index + 1] = '\0';
				out = fn;
			}
			else if (args_type == REAL) {
				fn->stringval[replace_index] = 'f';
				fn->stringval[replace_index + 1] = '\0';
				out = fn;
			}

		}
	}

	return out;
}

/* makefuncall makes a FUNCALL operator and links it to the fn and args.
   tok is a (now) unused token that is recycled. */
TOKEN makefuncall(TOKEN tok, TOKEN fn, TOKEN args) {
  if (strcmp(fn->stringval, "new") == 0) {
    tok = makeop(ASSIGNOP);
    tok->operands = args;

    SYMBOL typsym = args->symtype;
    typsym = typsym->datatype;

    TOKEN funcal = talloc();
    funcal->tokentype = OPERATOR;
    funcal->whichval = FUNCALLOP;
    funcal->operands = fn;
    funcal->basicdt = typsym->basicdt;
    fn->link = makeintc(typsym->size);
    args->link = funcal;

  } else {
    tok->tokentype = OPERATOR;
    tok->whichval = FUNCALLOP;
    tok->operands = fn;
    tok->basicdt = args->basicdt;
    fn->link=args;


  }

  if (strcmp(fn->stringval, "writeln") == 0) {
    fn = write_fxn_args_type_check(fn, args);
    if (!fn) {
      return NULL;
    }
  }

  if (DEBUG && DB_MAKEFUNCALL) {
         printf("makefuncall\n");
         dbugprinttok(tok);
  }
  return tok;
}

/* makerepeat makes structures for a repeat statement.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN makerepeat(TOKEN tok, TOKEN statements, TOKEN tokb, TOKEN expr) {

   TOKEN label = makelabel();
   int current = labelnumber - 1;
   tok = makeprogn(tok, label);

   TOKEN body = tokb;
   body = makeprogn(body, statements);
   label->link = body;

   TOKEN gototok = makegoto(current);
   TOKEN emptytok = makeprogn((TOKEN) talloc(), NULL);
   emptytok->link = gototok;

   TOKEN ifs = talloc();
   ifs = makeif(ifs, expr, emptytok, gototok);
   body->link = ifs;

   if (DEBUG && DB_MAKEREPEAT) {
         printf("make repeat\n");
         dbugprinttok(tok);
   }

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
TOKEN makeprogram(TOKEN name, TOKEN args, TOKEN statements) {
    TOKEN tok = talloc();
    TOKEN nameToArgs = talloc();
    tok->tokentype = OPERATOR;
    tok->whichval = PROGRAMOP;
    tok->operands = name;
    nameToArgs = makeprogn(nameToArgs, args);
    name->link = nameToArgs;
    nameToArgs->link = statements;
    if (DEBUG & DB_MAKEPROGRAM) { 
      printf("makeprogram\n");
      dbugprinttok(tok);
      dbugprinttok(nameToArgs);
    };
    return tok;
  }



/* finds label number in label table for user defined labels */
int findlabelnumber(int label) {
  if (DEBUG & DB_FINDLABEL) {
    printf("finding label\n");
  }
  for(int i = 0; i < labelnumber; i ++) {
    if (labeltable[i] == label) {
      if (DEBUG & DB_FINDLABEL) {
       printf("found label : ");
       printf("%d\n", i);
      }
      return i;
    }
  }
  return -1;
}

/* findid finds an identifier in the symbol table, sets up symbol table
   pointers, changes a constant to its number equivalent */
TOKEN findid(TOKEN tok) { /* the ID token */
    SYMBOL sym, typ;
    sym = searchst(tok->stringval);
    tok->symentry = sym;
    
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


  SYMBOL recsym = var->symtype;
  printf("recsym->namestring: %s\n", recsym->namestring);
  
  SYMBOL curfield = recsym->datatype->datatype;
  

  int offset = 0;
  while(curfield) {
    printf("curfield->namestring: %s\n", curfield->namestring);
    if (strcmp(curfield->namestring, field->stringval) == 0) {
      offset = curfield->offset;
      var->symtype = curfield;

      break;
    } 
    else {
      curfield = curfield->link;
    }
  }

  printf("offset: %d\n", offset);


  dot = makearef(var, makeintc(offset), dot);

  if (curfield) {
    dot->basicdt = curfield->datatype->basicdt;
  }


  if (DEBUG & DB_REDUCEDOT) {
    printf("reducedot\n");
    //printf("-- %s ** %s", curfield->namestring, field->stringval);
    dbugprinttok(var);
    dbugprinttok(dot);
    dbugprinttok(field);
  }
  return dot;
 
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

  return makearef(arr, finalOffset, NULL);

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
  

/* dolabel is the action for a label of the form   <number>: <statement>
   tok is a (now) unused token that is recycled. */
TOKEN dolabel(TOKEN labeltok, TOKEN tok, TOKEN statement) {
    int real_label = findlabelnumber(labeltok->intval);
    if (real_label == -1) {
      printf("Error: user defined label not found");
    }

    labeltok = makeop(LABELOP);
    TOKEN tokb = makeintc(real_label);
    labeltok->operands=tokb;
    labeltok->link = statement;
    tok = makeprogn(tok, labeltok);

    if (DEBUG & DB_DOLABEL) {
      printf("dolabel\n");
      dbugprinttok(tok);
    }

    return tok;
}

/* dogoto is the action for a goto statement.
   tok is a (now) unused token that is recycled. */
TOKEN dogoto(TOKEN tok, TOKEN labeltok) {
    int real_label = findlabelnumber(labeltok->intval);
    if (real_label == -1) {
      printf("Error: user defined label not found");
    }  

    tok = makegoto(real_label);
    if (DEBUG & DB_DOGOTO) {
      printf("dogoto\n");
      dbugprinttok(tok);
    }

    return tok;
}


/* dopoint handles a ^ operator.
   tok is a (now) unused token that is recycled. */
TOKEN dopoint(TOKEN var, TOKEN tok) {
  tok->symtype = var->symtype->datatype->datatype;
  tok->operands = var;
  


  if (DEBUG & DB_DOPOINT) {
    printf("dopoint\n");
    dbugprinttok(tok);
  }

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
  labeltable[labelnumber++] = num->intval;  

  if (DEBUG & DB_INSTLABEL) {
    printf("install label\n");
    printf("current table\n");
    for (int i = 0; i < labelnumber; i ++) {
      printf("label ");
      printf("%d", i);
      printf(" : ");
      printf("%d\n", labeltable[i]);
    }
  }
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
    SYMBOL typesym;

    if (typetok->symtype){
      typesym = typetok->symtype;
      printf("installed array with type of typetok %s\n", typesym->namestring);
    }
    else{
      typesym = searchst(typetok->stringval);
    }
    SYMBOL arraysym = symalloc();
    arraysym->kind = ARRAYSYM;
    arraysym->datatype = typesym;  // Use the updated type from recursive calls or the initial type

    int low = subrange->lowbound;
    int high = subrange->highbound;
    arraysym->lowbound = low;
    arraysym->highbound = high;

    // Calculate the size of the current array dimension
    // If this is the base case (no more linked bounds), use the type's size.
    // Otherwise, use the size calculated in the recursive call (typesym->size)
    if (typesym->kind == ARRAYSYM) {
        arraysym->size = (high - low + 1) * typesym->size;
    } else {
        // This assumes typesym points to the original data type at the base case,
        // and its size field holds the size of a single element of that type.
        arraysym->size = (high - low + 1) * typesym->size;
    }

    typetok->symtype = arraysym;  // Update the token's symbol to the new array symbol

    if (DEBUG & DB_INSTARRAY) {
        printf("Finished instarray().\n");
        dbugprint1tok(typetok);
    }

    return typetok;
}


/* instfields will install type in a list idlist of field name tokens:
   re, im: real    put the pointer to REAL in the RE, IM tokens.
   typetok is a token whose symtype is a symbol table pointer.
   Note that nconc() can be used to combine these lists after instrec() */
TOKEN instfields(TOKEN idlist, TOKEN typetok) {
  SYMBOL typesym = typetok->symtype;
  // printf("typesym name %s\n", typesym->namestring);
  TOKEN temp = idlist;
  while(temp) {
    // printf("temp name %s\n", temp->stringval);
    temp->symtype = typesym;     

    // printf("temp type %s\n", temp->symtype->namestring);
    temp = temp->link;
  }


  if (DEBUG & DB_INSTFIELD) {
      printf("install fields\n");
      dbugprinttok(idlist);
  }

  return idlist;
}

/* instrec will install a record definition.  Each token in the linked list
   argstok has a pointer its type.  rectok is just a trash token to be
   used to return the result in its symtype */
TOKEN instrec(TOKEN rectok, TOKEN argstok) {
  //Do storage allocation algorithm
  SYMBOL recsym = symalloc();
  recsym->kind = RECORDSYM;
  int count = 0, next = 0, align;

  SYMBOL prev = NULL;
  while (argstok) {
    align = alignsize(argstok->symtype);
    SYMBOL recfield = makesym(argstok->stringval);
    recfield->datatype = argstok->symtype;

    recfield->offset = wordaddress(next, align);
    recfield->size = argstok->symtype->size;
    next = recfield->offset + recfield->size;
    if (count == 0) {
      recsym->datatype = recfield;
      prev = recfield;
    } else {
      prev->link = recfield;
      prev = recfield;
    }
    recfield->link = NULL;
    count ++;
    argstok = argstok->link;
  }

  recsym->size = wordaddress(next, 16); 
  rectok->symtype = recsym;

  if (DEBUG & DB_INSTREC) {
      printf("install rec\n");
      printf("total size %d\n", recsym->size);
      dbugprinttok(rectok);

  }
  return rectok;
}

/* instpoint will install a pointer type in symbol table */
TOKEN instpoint(TOKEN tok, TOKEN typename) {

  SYMBOL typesym = searchins(typename->stringval);


  SYMBOL pointsym = symalloc();
  pointsym->datatype = typesym;
  pointsym->kind = POINTERSYM;
  pointsym->size = basicsizes[POINTER];
  pointsym->basicdt = POINTER;

  tok->symtype = pointsym;

  if (DEBUG & DB_INSTPOINT) {
      printf("install point\n");
      dbugprinttok(tok);
  }

  return tok;
}


/* insttype will install a type name in symbol table.
   typetok is a token containing symbol table pointers. */
void  insttype(TOKEN typename, TOKEN typetok) {
  SYMBOL typesym = searchins(typename->stringval);
  typesym->kind = TYPESYM;
  typesym->datatype = typetok->symtype;
  typesym->size = typetok->symtype->size;

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

    printstlevel(1);    /* to see level 0 too, change to:   printst();  */

    if (DEBUG & DB_PARSERES){ 

      dbugprinttok(parseresult);
    }

    ppexpr(parseresult);           /* Pretty-print the result tree */

    /* uncomment following to call code generator. */
     
    // gencode(parseresult, blockoffs[blocknumber], labelnumber);
 
  }