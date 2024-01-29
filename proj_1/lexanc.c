/* lex1.c         14 Feb 01; 31 May 12       */

/*
Name: S. Ram Janarthana Raja	
UT EID: rs53992
*/


/* This file contains code stubs for the lexical analyzer.
   Rename this file to be lexanc.c and fill in the stubs.    */

/* Copyright (c) 2001 Gordon S. Novak Jr. and
   The University of Texas at Austin. */

/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
utput);

   GNU General Public License for more details.
a	if ( num > INT_MAX ) {
			exponent ++;
			intError = 1;
		} if ( num > INT_MAX ) {
			exponent ++;
			intError = 1;
		} 
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include "token.h"
#include "lexan.h"

/* This file will work as given with an input file consisting only
   of integers separated by blanks:
   make lex1
   lex1
   12345 123    345  357
 */
extern int CHARCLASS[];
char* operators[] = { "+", "-", "*", "/", ":=", "=", "<>", "<",
	"<=", ">=", ">", "^", ".", "and", "or", "not",
	"div", "mod", "in" };

char* delimiters[] = { ",", ";", ":", "(", ")", "[", "]", ".."};

char* reservedWords[] = { "array", "begin", "case", "const", "do",
	"downto", "else", "end", "file", "for", 
	"function", "goto", "if", "label", "nil", 
	"of", "packed", "procedure", "program", "record",
	"repeat", "set", "then", "to", "type", "until",
	"var", "while", "with"};



/* Skip blanks and whitespace.  Expand this function to skip comments too. */
void skipblanks ()
{
	int c, d;
	while ((c = peekchar()) != EOF ){
		if (c == ' ' || c == '\n' || c == '\t') {
			getchar();
		} else if (c == '{'){
			while ((c = peekchar()) != EOF && (c != '}'))
				getchar();
			getchar();
		} else if (c == '(' && (d = peek2char()) != EOF && d == '*'){
			getchar();
			getchar();  //Skip over '(' and '*'
			while ((c = peekchar()) !=  EOF && (d = peek2char()) != EOF && !(c == '*' && d== ')'))
				getchar();
			getchar();
			getchar();  //Skip over '*' and ')'
		} else {
			break;
		}
	}
}

TOKEN getReservedWordTok(int val, TOKEN tok) {
	tok->tokentype = RESERVED;
	tok->whichval = val;
	return tok;
}

TOKEN getIdentifierTok(char word[], TOKEN tok) {
	tok->tokentype = IDENTIFIERTOK;
	strcpy(tok->stringval, word);
	return tok;
}

TOKEN getDelimiterTok(int val, TOKEN tok) {
	tok->tokentype = DELIMITER;
	tok->whichval = val;
	return tok;
}

TOKEN getOperatorTok(int val, TOKEN tok) {
	tok->tokentype = OPERATOR;
	tok->whichval = val;
	return tok;
}

TOKEN getStringTok(char word[], TOKEN tok) {
	tok->tokentype = STRINGTOK;
	strcpy(tok->stringval, word);
	return tok;
} 

TOKEN getIntegerTok(int val, TOKEN tok) {
	tok->tokentype = NUMBERTOK;
	tok->basicdt = INTEGER;
	tok->intval = val;
	return tok;
}

TOKEN getRealTok(double val, TOKEN tok) {
	tok->tokentype = NUMBERTOK;
	tok->basicdt = REAL;
	tok->realval = val;
	return tok;
}
/* Get identifiers and reserved words */
TOKEN identifier (TOKEN tok)
{
	int c, i, size = 0;
	char word[256];
	while ( (c = peekchar()) != EOF
			&& (CHARCLASS[c] == ALPHA || CHARCLASS[c] == NUMERIC))
	{ 
		c = getchar();
		word[size] = c;
		size++;
	}

	if (size >= 16)
		word[15] = '\0';
	else
		word[size] = '\0';


	for (i = 0; i < 29; i++)
	{
		if (strcmp(word, reservedWords[i]) == 0)
		{
			return getReservedWordTok(i + 1, tok);
		}
	}

	for (i = 13; i < 19 ; i++)
	{
		if (strcmp(word, operators[i]) == 0)
		{
			return getOperatorTok(i + 1, tok);
		}
	}

	return getIdentifierTok(word, tok); 
}

TOKEN getstring (TOKEN tok)
{
	getchar();
	int c, d, size = 0;
	char word[256];
	while ((c = peekchar()) != EOF && !(c == '\n' || c=='\t') ) {
		c = getchar();
		if( c == '\'') {
			if((d = peekchar()) != EOF && d != '\''){
				break;
			} else {
				getchar();
			}
		}
		word[size] = c;
		size ++;
	}

	if (size >= 16)
		word[15] = '\0';
	else
		word[size] = '\0';
	return getStringTok(word, tok);	

}


TOKEN special (TOKEN tok)
{
	int c, d, size = 0, flag = 0, val = 0, i;
	char oper[3];

	while ( (c = peekchar()) != EOF
			&& CHARCLASS[c] == SPECIAL) {
		c = getchar();	
		oper[size] = c;
		size ++;

		d = peekchar();
		oper[size] = d;	
		size ++;
		
		oper[size] = '\0';

		for(i = 0; i < 19; i ++){
			if(strcmp(oper, operators[i]) == 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			getchar();
			return getOperatorTok(i + 1, tok);
		} 
		
		for(i = 0; i < 8; i ++){
			if(strcmp(oper, delimiters[i]) == 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			getchar();
			return getDelimiterTok(i + 1, tok);
		}
		
		oper[size - 1] = '\0';

		for(i = 0; i < 19; i ++){
			if(strcmp(oper, operators[i]) == 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			return getOperatorTok(i + 1, tok);
		} 
		
		for(i = 0; i < 8; i ++){
			if(strcmp(oper, delimiters[i]) == 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			return getDelimiterTok(i + 1, tok);
		}
	}
	
}

TOKEN handleRealError(TOKEN tok){
	printf("Floating number out of range\n");
	return getRealTok(0.0, tok);
}

TOKEN returnRealTok(double real, TOKEN tok){
	if (real > FLT_MAX || real < FLT_MIN) {
		return handleRealError(tok);
	} else {
		return getRealTok(real, tok);
	}
}

int shortenInteger(long num) {
  while (num > INT_MAX) {
    num = num / 10;
  }
  return num;
}
/* Get and convert unsigned numbers of all types. */
TOKEN number (TOKEN tok)
{ 	
    
    double num = 0.0, real = 0.0, decimal = 0.0, multiplier = 10.0;
    long exponent = 0, expValue = 0;
    int  c, d, charval, dFlag = 0, negFlag = 0, eFlag = 0;
  
    while ((c = peekchar()) != EOF
            && (CHARCLASS[c] == NUMERIC))
    {   
        c = getchar();
        charval = c - '0';
        num = num * 10 + charval;
    }

    // The part after the decimal point
    if(c == '.' && (d = peek2char()) != EOF && CHARCLASS[d] == NUMERIC) {
        dFlag = 1;
        getchar();
        while ((c = peekchar()) != EOF
                && (CHARCLASS[c] == NUMERIC)) {
            c = getchar();
            charval = c - '0';
            decimal = decimal + ((double) charval / multiplier);
            multiplier *= 10;
        }   

        real = num + decimal;
        // printf("Real value: %f\n", real);
    }
  

	//The exponent part
	if(c == 'e') {
		eFlag = 1;
		getchar();
		c = peekchar();
		if (c == '-') {
			negFlag = 1;
			getchar();
		} else if (c == '+') {
			getchar();
		}

		while ((c = peekchar()) != EOF 
				&& CHARCLASS[c] == NUMERIC) {	
			c = getchar();
			charval = c - '0';

			if ( expValue > INT_MAX ){
				continue ;
			}
			expValue = expValue * 10 + charval;
		}

    if (negFlag){
      expValue = -expValue;
    
    }
	}

	if (dFlag) {
		if (eFlag) {
			if (negFlag) {
				exponent = exponent - expValue;
				real = real / pow (10, exponent);
			} else {
				exponent = exponent + expValue;
				real = real * pow (10, exponent);
			}

			return returnRealTok(real, tok);

		} else {

			return returnRealTok(real, tok);

		}

	}
	
	if (eFlag)  {
		real = (double) num;
		if (negFlag) {
			exponent = exponent - expValue;
			real = real / pow(10, exponent);
		} else {
			exponent = exponent + expValue;
			real = real * pow(10, exponent);
		}
		return returnRealTok(real, tok);		
	}


	if (num > INT_MAX) {
    printf("Integer number out of range\n");
  }
  return getIntegerTok(shortenInteger(num), tok);

}

