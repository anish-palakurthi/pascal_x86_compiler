%{    /* lex2.l -- partial lex specification for Pascal   06 Oct 21 */

/* Copyright (c) 2021 Gordon S. Novak Jr. and The University of Texas at Austin
   */
/* 22 Jul 13; 20 Feb 19; 16 Sep 20
   */

/* This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>. */

/* To use:
        make lex2
        lex2
        x < 3.14            */

/* This file will work as given on a simple input such as:
   if i<j then x := 3.14

   Copy this file to lexan.l and expand it for your assignment.
   Use:
        make lexer
        lexer <graph1.pas
   */

#include <ctype.h>
#include <string.h>
#include "lexan.h"
#include <limits.h>
#include "stdbool.h"

int maketoken(int type, int which);
int install_id();
int install_fnum();
int yywrap();
int install_string();
int install_int();

/* If the lex yytext buffer turns out to be too small to hold comments,
   add the following lines:
 #undef YYLMAX
 #define YYLMAX 256
 */

TOKEN talloc();

extern TOKEN yylval;    /* This is the type of the lexical analyzer result */

%}

/* regular definitions */

/* regular definitions */

delim    	[ \t\n\f\r]
ws       	{delim}+
letter   	[A-Za-z]
digit    	[0-9]
id       	{letter}({letter}|{digit})*

intgr		{digit}+
fnumber  	{digit}+(\.{digit}+)?([Ee][+\-]?{digit}+)?



string		('([^']|(''))*')








%%


{ws}      { /* no action and no return */ }
array        {return(maketoken(RESERVED, ARRAY));}
begin        {return(maketoken(RESERVED, BEGINBEGIN));}
case         {return(maketoken(RESERVED, CASE));}
const        {return(maketoken(RESERVED, CONST));}
do           {return(maketoken(RESERVED, DO));}
downto       {return(maketoken(RESERVED, DOWNTO));}
else         {return(maketoken(RESERVED, ELSE));}
end          {return(maketoken(RESERVED, END));}
file         {return(maketoken(RESERVED, FILEFILE));}
for          {return(maketoken(RESERVED, FOR));}
function     {return(maketoken(RESERVED, FUNCTION));}
goto         {return(maketoken(RESERVED, GOTO));}
if           {return(maketoken(RESERVED, IF));}
label        {return(maketoken(RESERVED, LABEL));}
nil          {return(maketoken(RESERVED, NIL));}
of           {return(maketoken(RESERVED, OF));}
packed       {return(maketoken(RESERVED, PACKED));}
procedure    {return(maketoken(RESERVED, PROCEDURE));}
program      {return(maketoken(RESERVED, PROGRAM));}
record       {return(maketoken(RESERVED, RECORD));}
repeat       {return(maketoken(RESERVED, REPEAT));}
set          {return(maketoken(RESERVED, SET));}
then         {return(maketoken(RESERVED, THEN));}
to           {return(maketoken(RESERVED, TO));}
type         {return(maketoken(RESERVED, TYPE));}
until        {return(maketoken(RESERVED, UNTIL));}
var          {return(maketoken(RESERVED, VAR));}
while        {return(maketoken(RESERVED, WHILE));}
with         {return(maketoken(RESERVED, WITH));}
{id}         {return(install_id());}
{string}     {return(install_str());}
{intgr}    {return(install_intgr());}
{fnumber}    {return(install_fnum());}

or           {return(maketoken(OPERATOR, OR));}
not          {return(maketoken(OPERATOR, NOT));}
div          {return(maketoken(OPERATOR, DIV));}
and          {return(maketoken(OPERATOR, AND));}
mod          {return(maketoken(OPERATOR, MOD));}
in           {return(maketoken(OPERATOR, IN));}

"+"          {return(maketoken(OPERATOR, PLUS));}
"-"          {return(maketoken(OPERATOR, MINUS));}
"*"          {return(maketoken(OPERATOR, TIMES));}
"/"          {return(maketoken(OPERATOR, DIVIDE));}
":="         {return(maketoken(OPERATOR, ASSIGN));}
"="          {return(maketoken(OPERATOR, EQ));}
"<>"         {return(maketoken(OPERATOR, NE));}
"<"          {return(maketoken(OPERATOR, LT));}
"<="         {return(maketoken(OPERATOR, LE));}
">="         {return(maketoken(OPERATOR, GE));}
">"          {return(maketoken(OPERATOR, GT));}
"^"          {return(maketoken(OPERATOR, POINT));}
"."          {return(maketoken(OPERATOR, DOT));}

","          {return(maketoken(DELIMITER, COMMA));}
";"          {return(maketoken(DELIMITER, SEMICOLON));}
":"          {return(maketoken(DELIMITER, COLON));}
"("          {return(maketoken(DELIMITER, LPAREN));}
")"          {return(maketoken(DELIMITER, RPAREN));}
"["          {return(maketoken(DELIMITER, LBRACKET));}
"]"          {return(maketoken(DELIMITER, RBRACKET));}
".."         {return(maketoken(DELIMITER, DOTDOT));} 



"{"          { 
              while ( input() != '}');
               }

"(*"    {       loop:
                  while (input() != '*');
                  switch (input()){
                        case ')': break;
                        case '*': unput('*');
                        default: goto loop;
                        }
         }

%%
/* Make simple tokens. */
int maketoken(int type, int which) {
	yylval = (TOKEN) talloc();
	yylval->tokentype = type;

	if (type == RESERVED) {
		yylval->whichval = which - RESERVED_BIAS;
	}
	else if (type == OPERATOR) {
		yylval->whichval = which - OPERATOR_BIAS;
	}
	else if (type == DELIMITER) {
		yylval->whichval = which - DELIMITER_BIAS;
	}
	else {
		yylval->whichval = which;
	}
	
	return which;
}

int install_str() {

    yylval = talloc();        /* Make new token, set yylval to point to it */
    yylval->tokentype = STRINGTOK;
    yylval->basicdt = STRINGTYPE;

    int i = 0;
    int letterIndex = 0;

    while (i < yyleng) {
        if (i == 0 || i == yyleng - 1 || letterIndex > 14) {
            // Skip the first and last character or if maximum length is exceeded.
            i++;
            continue;
        }

        // Directly assigning to yylval->stringval and incrementing letterIndex.
        yylval->stringval[letterIndex] = yytext[i];
        letterIndex++;

        // Increment i normally, and skip an extra index if a single quote is found.
        if (yytext[i] == '\'') {
            i++;
        }
        i++;
    }

    // Null-terminate the string in the final struct.
    yylval->stringval[letterIndex] = '\0';
    return STRING;
}


int install_id() {
	int i, c, n;
	yylval = (TOKEN) talloc();		/* Make new token, set yylval to point to it */
	yylval->tokentype = IDENTIFIERTOK;
	n = yyleng;			/* Number of characters */
	if (n > 15) {
		n = 15;
	}

	for (i = 0; i < n; i++) {
		c = yytext[i];
		/* if (islower(c)) c = toupper(c); */ /* to raise to upper case */
		yylval->stringval[i] = c;
	}
	yylval->stringval[n] = '\0';

	/* printf("id  %10s   n = %4d\n", yytext, n); */

	return IDENTIFIER;
}

int install_intgr() {

	yylval = talloc();		/* Make new token, set yylval to point to it */
	yylval->tokentype = NUMBERTOK;
	yylval->basicdt = INTEGER;

	long num;
	char *end;
	
	errno = 0;		// not being used for anything at the moment
	num = strtol(yytext, &end, 10);			// convert to long int

	if (num > INT_MAX) {
		printf("Integer number out of range\n");
		yylval->intval = INT_MAX;
	}
	else {
		yylval->intval = num;
	}

	return NUMBER;
}

int install_fnum() {

	yylval = talloc();		/* Make new token, set yylval to point to it */
	yylval->tokentype = NUMBERTOK;
	yylval->basicdt = REAL;

	float num;
	char *end;

	errno = 0;
	num = strtof(yytext, &end);			// convert to float

	if (errno == ERANGE) {
		printf("Floating number out of range\n");
		yylval->realval = 0;
	}
	else {
		yylval->realval = num;
	}

	return NUMBER;
}

int yywrap() {
	yylex_destroy();
	return 1;		/* lex may need this. */
}