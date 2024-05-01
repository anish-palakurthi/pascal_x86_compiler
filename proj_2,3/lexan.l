%{    /* lex2.l -- partial lex specification for Pascal    22 Jul 13 */

/* Copyright (c) 2013 Gordon S. Novak Jr. and The University of Texas at Austin
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

/*
 * Last modified: 0132, 14/07/25
 */

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
// #include "token.h"
#include "lexan.h"

int maketoken(int type, int which);
int install_str();
int install_id();
int install_intgr();
int install_fnum();
int yywrap();

/* If the lex yytext buffer turns out to be too small to hold comments,
   add the following lines:  */
//*
 #undef YYLMAX
 #define YYLMAX 256
//*/

TOKEN yylval;     /* This is the type of the lexical analyzer result */

static char* reserved[] = {	" ", "array", "begin", "case", "const", "do",
							"downto", "else", "end", "file", "for",
							"function", "goto", "if", "label", "nil",
							"of", "packed", "procedure", "program", "record",
							"repeat", "set", "then", "to", "type",
							"until", "var", "while", "with" };
static int reserved_size = 30;

static char* operators[] = {" ", "+", "-", "*", "/", ":=", "=", "<>", "<", "<=",
							">=", ">", "^", "."};
static int operators_size = 14;

static char* delimiters[] = {" ", ",", ";", ":", "(", ")", "[", "]", ".."};
static int delimiters_size = 9;

%}

/* regular definitions */

delim    	[ \t\n\f\r]
ws       	{delim}+
letter   	[A-Za-z]
digit    	[0-9]
id       	{letter}({letter}|{digit})*

intgr		{digit}+
exp			[Ee][+-]?{digit}+
intexp		{intgr}{exp}
fnumber  	{digit}+(\.{digit}+)?([Ee][+\-]?{digit}+)?

%x commentmultiline
commentsingle	\{[^}]*\}
commentmulti	\(\*([^*)\n \t\f\r]+|(\*\))|[*)])*\*\)		/* almost there */
comment			{commentsingle}|{commentmulti}

string		('([^']|(''))*')

reserved	(?i:array|begin|case|const|do|downto|else|end|file|for|function|goto|if|label|nil|of|packed|procedure|program|record|repeat|set|then|to|type|until|var|while|with)

opsym		"+"|"-"|"*"|"/"|"<"|"<="|"="|"<>"|">"|">="|":="|"."|"^"
/* operator	(?i:and)|(?i:or)|(?i:not)|(?i:div)|(?i:mod)|(?i:in)|{opsym} */
operator	(?i:and|or|not|div|mod|in)|{opsym}

delimiter	","|";"|":"|"("|")"|"["|"]"|".."

%%

<commentmultiline>[^*)\n]+
<commentmultiline>{delim}
<commentmultiline>"*)"       	BEGIN(INITIAL);
<commentmultiline>[*)]

{ws}	{ /* no action and no return */ }

{commentsingle} { /* no action and no return */ }
"(*"			BEGIN(commentmultiline);

(?i:array)      { return (maketoken(RESERVED, ARRAY)); }
(?i:begin)      { return (maketoken(RESERVED, BEGINBEGIN)); }
(?i:case)      	{ return (maketoken(RESERVED, CASE)); }
(?i:const)     	{ return (maketoken(RESERVED, CONST)); }
(?i:do)      	{ return (maketoken(RESERVED, DO)); }
(?i:downto)     { return (maketoken(RESERVED, DOWNTO)); }
(?i:else)      	{ return (maketoken(RESERVED, ELSE)); }
(?i:end)      	{ return (maketoken(RESERVED, END)); }
(?i:file)      	{ return (maketoken(RESERVED, FILEFILE)); }
(?i:for)      	{ return (maketoken(RESERVED, FOR)); }
(?i:function)   { return (maketoken(RESERVED, FUNCTION)); }	
(?i:goto)      	{ return (maketoken(RESERVED, GOTO)); }
(?i:if)      	{ return (maketoken(RESERVED, IF)); }
(?i:label)     	{ return (maketoken(RESERVED, LABEL)); }
(?i:nil)      	{ return (maketoken(RESERVED, NIL)); }
(?i:of)      	{ return (maketoken(RESERVED, OF)); }
(?i:packed)     { return (maketoken(RESERVED, PACKED)); }	
(?i:procedure)  { return (maketoken(RESERVED, PROCEDURE)); } 	
(?i:program)    { return (maketoken(RESERVED, PROGRAM)); }
(?i:record)     { return (maketoken(RESERVED, RECORD)); }	
(?i:repeat)     { return (maketoken(RESERVED, REPEAT)); }	
(?i:set)      	{ return (maketoken(RESERVED, SET)); }
(?i:then)      	{ return (maketoken(RESERVED, THEN)); }
(?i:to)      	{ return (maketoken(RESERVED, TO)); }
(?i:type)      	{ return (maketoken(RESERVED, TYPE)); }
(?i:until)     	{ return (maketoken(RESERVED, UNTIL)); }
(?i:var)      	{ return (maketoken(RESERVED, VAR)); }
(?i:while)     	{ return (maketoken(RESERVED, WHILE)); }
(?i:with)      	{ return (maketoken(RESERVED, WITH)); }

"+"			{ return (maketoken(OPERATOR, PLUS)); }
"-"			{ return (maketoken(OPERATOR, MINUS)); }
"*"			{ return (maketoken(OPERATOR, TIMES)); }
"/"			{ return (maketoken(OPERATOR, DIVIDE)); }
"<"       	{ return (maketoken(OPERATOR, LT)); }
"<="      	{ return (maketoken(OPERATOR, LE)); }
"="       	{ return (maketoken(OPERATOR, EQ)); }
"<>"      	{ return (maketoken(OPERATOR, NE)); }
">"       	{ return (maketoken(OPERATOR, GT)); }
">="      	{ return (maketoken(OPERATOR, GE)); }
":="      	{ return (maketoken(OPERATOR, ASSIGN)); }
"."       	{ return (maketoken(OPERATOR, DOT)); }
"^"			{ return (maketoken(OPERATOR, POINT)); }
(?i:and)	{ return (maketoken(OPERATOR, AND)); }
(?i:or)		{ return (maketoken(OPERATOR, OR)); }
(?i:not)	{ return (maketoken(OPERATOR, NOT)); }
(?i:div)	{ return (maketoken(OPERATOR, DIV)); }
(?i:mod)	{ return (maketoken(OPERATOR, MOD)); }
(?i:in)		{ return (maketoken(OPERATOR, IN)); }

","			{ return (maketoken(DELIMITER, COMMA)); }
";"       	{ return (maketoken(DELIMITER, SEMICOLON)); }
":"			{ return (maketoken(DELIMITER, COLON)); }
"("			{ return (maketoken(DELIMITER, LPAREN)); }
")"			{ return (maketoken(DELIMITER, RPAREN)); }
"["			{ return (maketoken(DELIMITER, LBRACKET)); }
"]"			{ return (maketoken(DELIMITER, RBRACKET)); }
".."		{ return (maketoken(DELIMITER, DOTDOT)); }

{string}	{ return (install_str()); }

{id}      	{ return (install_id()); }

{intgr}		{ return (install_intgr()); }

{fnumber} 	{ return (install_fnum()); }

%%

/* Note that lex always returns two values:
   1. "What is it?": a small integer such as NUMBER that indicates the
      kind of item that was found; this is the return() value.
   2. The value itself.  This is yylval, which points to a TOKEN.   */

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

	yylval = talloc();		/* Make new token, set yylval to point to it */
	yylval->tokentype = STRINGTOK;
	yylval->basicdt = STRINGTYPE;

	int c, i, len, stop, counter;
	len = yyleng;

	i = 1;
	counter = 0;
	
	while (i < len && counter < 15) {
		c = yytext[i];
		yylval->stringval[counter] = c;

		if ((char) c == '\'') {
			i++;
		}
		i++;
		counter++;
	}

	/* 17 because the apostrophe delimiters are included in yytext */
	if (len >= 17) {
		yylval->stringval[counter] = '\0';
	}
	else if (len <= 0) {
		yylval->stringval[0] = '\0';
	}
	else {
		yylval->stringval[counter - 1] = '\0';
	}
	
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


