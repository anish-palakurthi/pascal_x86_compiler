/* lex1.c         14 Feb 01; 31 May 12; 11 Jan 18; 20 Jan 24       */

/* This file contains code stubs for the lexical analyzer.
   Rename this file to be lexanc.c and fill in the stubs.    */

/* Copyright (c) 2024 Gordon S. Novak Jr. and
   The University of Texas at Austin. */

/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "token.h"
#include "lexan.h"
#include <limits.h>
#include <math.h>
#include <float.h>

extern int CHARCLASS[];
char *reserved[] = {"array", "begin", "case", "const", "do", "downto", "else", "end", "file", "for", "function", "goto", "if", "label", "nil", "of", "packed", "procedure", "program", "record", "repeat", "set", "then", "type", "until", "var", "while", "with"};

char *operators[] = {"+", "-", "*", "/", ":=", "=", "<>", "<", "<=", ">=", ">", "^", ".", "and", "or", "not", "div", "mod", "in"};

char *delimiters[] = {",", ";", ":", "(", ")", "[", "]", ".."};


/* This file will work as given with an input file consisting only
   of integers separated by blanks:
   make lex1
   lex1
   12345 123    345  357
   */

/* Skip blanks and whitespace.  Expand this function to skip comments too. */
void skipblanks ()
  {
      int c;
      while ((c = peekchar()) != EOF){

        // {} comments
        if (c == '{'){

          //goes until close and then skips the closing bracket
          while((c = peekchar()) != EOF && c != '}'){
            getchar();
          }
          getchar();

        }

        // (* *) comments
        else if (c == '('){
          if (peek2char() != EOF && peek2char() == '*'){

            //skips opening
            getchar();
            getchar();

            //goes until close and then skips the closing brackets
            while((c = peekchar()) != EOF && c != '*' && peek2char() != EOF && peek2char() != ')'){
              getchar();
            }
            getchar();
            getchar();
          }

        }

        //default skips
        else if (c == ' ' || c == '\n' || c == '\t'){
          getchar();
        }

        else{
          break;
        }
    }

  }

int isReserved(char *identifierName)
  {
    int i;
    for (i = 0; i < 29; i++)
      {
        if (strcmp(identifierName, reserved[i]) == 0)
          {
            return i;
          }
      }
    return -1;
  }

// These functions are called from the parser driver in scanner.c
/* Get identifiers and reserved words */
TOKEN identifier (TOKEN tok)
  {
    // tok.tokentype = IDENTIFIERTOK;
    // tok.basicdt = STRINGTYPE;

    //loop through and get the identifier name
    char identifierName[16];
    int i = 0;

    while (peekchar() != EOF && (CHARCLASS[peekchar()] == ALPHA || CHARCLASS[peekchar() == NUMERIC]) && i < 15)
      {
        char curChar = getchar();
        identifierName[i] = curChar;
        i++;
      }

    identifierName[i] = '\0';
    // tok.stringval = identifierName;

    //check if the identifier is a reserved word
    int reservedIndex = isReserved(identifierName);
    if (reservedIndex != -1)
      {
        tok->tokentype = RESERVED;
        tok->whichval = reservedIndex + 1;
        return tok;
      }
    
    //if not a reserved word, check if it is a alphabetic operator
    for (int j = 13; j < 19; j++){
      if (strcmp(identifierName, operators[j]) == 0){
        tok->tokentype = OPERATOR;
        tok->whichval = j + 1;
        return tok;
      }
    }

    tok->tokentype = IDENTIFIERTOK;
    strcpy(tok->stringval, identifierName);
    return tok;



    }

TOKEN getstring (TOKEN tok)
  {

    tok->tokentype = STRINGTOK;
    tok->basicdt = STRINGTYPE;

    char stringName[16];
    int i = 0; 

    while (peekchar() != EOF && CHARCLASS[peekchar()] == ALPHA && i < 15)
      {
        char curChar = getchar();
        if (curChar == '\'')
          {
            if (peekchar() != EOF && peekchar() == '\'')
              {
                stringName[i] = curChar;
                i++;
                stringName[i] = curChar;
                i++;
                getchar();
              }
            else
              {
                break;
              }
          }
        else
          {
            stringName[i] = curChar;
            i++;
          }
      }

    stringName[i] = '\0';

    strcpy(tok->stringval, stringName);

    return tok;

    }

TOKEN special (TOKEN tok)
  {
    int opIndex = 0;

    char operatorName[3];
    char curChar;

    while(peekchar() != EOF && CHARCLASS[peekchar()] == SPECIAL)
      {
        curChar = getchar();
        operatorName[opIndex] = curChar;
        opIndex++;

        if (CHARCLASS[peekchar()] == SPECIAL)
          {
            curChar = getchar();
            operatorName[opIndex] = curChar;
            opIndex++;
          }

        operatorName[opIndex] = '\0';


        for (int i = 0; i < 13; i++)
          {
            if (strcmp(operatorName, operators[i]) == 0)
              {
                tok->tokentype = OPERATOR;
                tok->whichval = i + 1;
                return tok;
              }
          }

        for (int i = 0; i < 8; i++){
          if (strcmp(operatorName, delimiters[i]) == 0){
            tok->tokentype = DELIMITER;
            tok->whichval = i + 1;
            return tok;
          }
        }
      }
    
    return tok;
  }

TOKEN getRealTok(double val, TOKEN tok) {
	tok->tokentype = NUMBERTOK;
	tok->basicdt = REAL;
	tok->realval = val;
	return tok;
}

TOKEN handleRealError(TOKEN tok){
	printf("Real number out of range \n");
	return getRealTok(0.0, tok);
}

TOKEN returnRealTok(double real, TOKEN tok){
	if (real > FLT_MAX || real < FLT_MIN) {
		return handleRealError(tok);
	} else {
		return getRealTok(real, tok);
	}
}



/* Get and convert unsigned numbers of all types. */
TOKEN number (TOKEN tok)

  { 
    	long num = 0, exponent = 0, expValue = 0;
	double real = 0.0, decimal = 0.0, multiplier = 10.0;
	int  c, d, charval, dFlag = 0, negFlag = 0, eFlag = 0, intError = 0, floatError = 0;

	while ((c = peekchar()) != EOF
			&& (CHARCLASS[c] == NUMERIC))
	{   
		c = getchar();
		charval = c - '0';

		if ( num > INT_MAX ) {
			exponent ++;
			intError = 1;
		} else {
			num = num * 10 + charval;
		}
	
	}

	if ( num > INT_MAX ) {
		exponent ++;
		intError = 1;
	} 

	//The part after the decimal point
	if(c == '.' && (d = peek2char()) != EOF && CHARCLASS[d] == NUMERIC) {
		intError = 0;
		dFlag = 1;
		getchar();
		while ((c = peekchar()) != EOF
				&& (CHARCLASS[c] == NUMERIC)) {
			c = getchar();
			charval = c - '0';
			decimal = decimal + ((double) charval / multiplier);
			multiplier *= 10;
		}	

		real = (double) num + decimal;

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
    
    
    
    
    
    /* long num;
    int  c, charval;
    num = 0;
    int exponent = 0;

    while ((c = peekchar()) != EOF
            && CHARCLASS[c] == NUMERIC)
      {   c = getchar();
          charval = (c - '0');

          if(num > (INT_MAX)){
            exponent++;
          }
          else{
            num = num * 10 + charval;
          }
        }

    if (num > INT_MAX){
      exponent++;
    }


    if (c == '.')   
      {   double d = num;
          double power = 1.0;
          while ( (c = peekchar()) != EOF
                  && CHARCLASS[c] == NUMERIC)
            {   c = getchar();
                charval = (c - '0');
                d = d * 10.0 + charval;
                power *= 10.0;
              }
          tok->tokentype = NUMBERTOK;
          tok->basicdt = REAL;
          tok->realval = d / power;
        }

    tok->tokentype = NUMBERTOK;
    tok->basicdt = INTEGER;
    tok->intval = num;
    return (tok); */
  }

