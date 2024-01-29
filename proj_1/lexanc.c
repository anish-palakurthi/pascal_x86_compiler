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


extern int CHARCLASS[];
char *reserved[] = { "array", "begin", "case", "const", "do", "downto", "else", "end", "file", "for",  "function", "goto", "if", "label", "nil", "of", "packed", "procedure", "program", "record", "repeat", "set", "then", "to", "type", "until", "var", "while", "with"};

char *operators[] = { "+", "-", "*", "/", ":=", "=", "<>", "<", "<=", ">=", ">", "^", ".", "and", "or", "not", "div", "mod", "in" };  

char *delimiters[] = { ",", ";", ":", "(", ")", "[", "]", ".."};



/* Skip blanks and whitespace.  Expand this function to skip comments too. */
void skipblanks ()
{
  
	int firstChar, secondChar;

  // Skip blanks, tabs, newlines, and comments (both kinds)
	while ((firstChar = peekchar()) != EOF ){

    //Single character skip
		if (firstChar == ' ' || firstChar == '\n' || firstChar == '\t') {

      //Consume single character
			getchar();
		} 
    //Skips comments of (* ... *) type when firstChar and secondChar match opening pattern
    else if (firstChar == '(' && (secondChar = peek2char()) == '*' && secondChar != EOF){
			
      //Consume openers
      getchar();
			getchar(); 

      //Skip until closing pattern is found
			while ((firstChar = peekchar()) !=  EOF && (secondChar = peek2char()) != EOF && (firstChar != '*' || secondChar != ')')){
          getchar();
      }

      //Consume closers
			getchar();
			getchar();  
		} 

    //Skips comments of { ... } type when firstChar matches opening pattern
    else if (firstChar == '{'){

      //Skips until closing pattern is found
			while ((firstChar = peekchar()) != EOF && (firstChar != '}')){
				getchar();
      }

      //Consume closer
			getchar();
		} 

    //No blanks, tabs, newlines, or comments found
    else {
			break;
		}
	}
}

/* Get identifiers and reserved words */
TOKEN identifier (TOKEN tok)
{
	int curChar;
  int length = 0;
	char word[16];
	while ( (curChar = peekchar()) != EOF
			&& (CHARCLASS[curChar] == ALPHA || CHARCLASS[curChar] == NUMERIC) && length < 15)
	{ 
		curChar = getchar();
		word[length] = curChar;
		length++;
	}

	word[length] = '\0';


	for (int i = 0; i < 29; i++)
	{
		if (strcmp(word, reserved[i]) == 0)
		{
      tok->tokentype = RESERVED;
      tok->whichval = i + 1;
      return tok;
		}
	}

	for (int i = 13; i < 19 ; i++)
	{
		if (strcmp(word, operators[i]) == 0)
		{
			tok->tokentype = OPERATOR;
      tok->whichval = i + 1;
      return tok;
		}
	}

  tok->tokentype = IDENTIFIERTOK;
	strcpy(tok->stringval, word);
	return tok;
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
  tok->tokentype = STRINGTOK;
	strcpy(tok->stringval, word);
	return tok;

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
      tok->tokentype = OPERATOR;
      tok->whichval = i + 1;
      return tok;
		} 
		
		for(i = 0; i < 8; i ++){
			if(strcmp(oper, delimiters[i]) == 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			getchar();
			tok->tokentype = DELIMITER;
      tok->whichval = i + 1;
      return tok;
		}
		
		oper[size - 1] = '\0';

		for(i = 0; i < 19; i ++){
			if(strcmp(oper, operators[i]) == 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
      tok->tokentype = OPERATOR;
      tok->whichval = i + 1;
      return tok;
		} 
		
		for(i = 0; i < 8; i ++){
			if(strcmp(oper, delimiters[i]) == 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			tok->tokentype = DELIMITER;
      tok->whichval = i + 1;
      return tok;
		}
	}
	
}

TOKEN handleRealError(TOKEN tok){
	printf("Floating number out of range\n");
  tok->tokentype = NUMBERTOK;
	tok->basicdt = REAL;
	tok->realval = 0.0;
	return tok;
}

TOKEN returnRealTok(double real, TOKEN tok){
	if (real > FLT_MAX || real < FLT_MIN) {
		return handleRealError(tok);
	} else {
  tok->tokentype = NUMBERTOK;
	tok->basicdt = REAL;
	tok->realval = real;
	return tok;
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
  tok->tokentype = NUMBERTOK;
	tok->basicdt = INTEGER;
	tok->intval = shortenInteger(num);
	return tok;
  

}

