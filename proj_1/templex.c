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
#include <limits.h>
#include <math.h>
#include <float.h>
#include "token.h"
#include "lexan.h"


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

int isInArray(char *arr[], int size, char word[]) {
  for (int i = 0; i < size; i++) {
    if (strcmp(arr[i], word) == 0) {
      return i;
    }
  }
  return -1;
}

TOKEN populateToken(TOKEN tok, int val, int ttype) {
  tok->tokentype = ttype;
  tok->whichval = val;
  return tok;
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
  while ( (curChar = peekchar()) != EOF
			&& (CHARCLASS[curChar] == ALPHA || CHARCLASS[curChar] == NUMERIC)){
        getchar();
      }

	word[length] = '\0';

  int res = isInArray(operators, 19, word);

  if (res != -1) {
    return populateToken(tok, res + 1, OPERATOR);
  }

  res = isInArray(reserved, 29, word);
  if (res != -1) {
    return populateToken(tok, res + 1, RESERVED);
  }


  tok->tokentype = IDENTIFIERTOK;
	strcpy(tok->stringval, word);
	return tok;
  
}


TOKEN getstring (TOKEN tok)
{

  getchar();
  int firstChar;
  int length = 0;
  char string[16];

  while ((firstChar = peekchar()) != EOF){
    firstChar = getchar();

    if (firstChar == '\'') {
      if (peekchar() != EOF && peekchar( ) != '\'') {
        break;
      } else {
        getchar();
      }
    }
    if (length >= 15) {
      continue;
    }
    string[length] = firstChar;
    length++;
  }

  string[length] = '\0';
  tok->tokentype = STRINGTOK;
	strcpy(tok->stringval, string);
	return tok;
}



TOKEN special (TOKEN tok)
{
	int firstChar;
  
	char opString[3];

	if ((firstChar = peekchar()) != EOF
			&& CHARCLASS[firstChar] == SPECIAL) {
    
    int length = 0, res = -1;
		firstChar = getchar();	
		int secondChar = peekchar();
		opString[length] = firstChar;
    length++;
		opString[length] = secondChar;	
		length ++;
		
		opString[length] = '\0';

    res = isInArray(delimiters, 8, opString);
    if (res != -1) {
      getchar();
      return populateToken(tok, res + 1, DELIMITER);
    }

    res = isInArray(operators, 19, opString);
    if (res != -1) {
      getchar();
      return populateToken(tok, res + 1, OPERATOR);
    }
	
		opString[length - 1] = '\0';


    res = isInArray(delimiters, 8, opString);
    if (res != -1) {
      return populateToken(tok, res + 1, DELIMITER);
    }

    res = isInArray(operators, 19, opString);
    if (res != -1) {
      return populateToken(tok, res + 1, OPERATOR);
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

int shortenInteger(long long num) {
  while (num > INT_MAX) {
        num /= 10;
    }
  return (int)num;
}

/* Get and convert unsigned numbers of all types. */
TOKEN number (TOKEN tok)
{ 	
    double num = 0.0, real = 0.0, decimal = 0.0, multiplier = 10.0;
    long exponent = 0, expValue = 0;
    int  c, d, charval, dFlag = 0, negFlag = 0, eFlag = 0;
  

    // The part before the decimal point
    while ((c = peekchar()) != EOF
            && (CHARCLASS[c] == NUMERIC))
    {   
        c = getchar();
        charval = c - '0';
        num = num * 10 + charval;

    }


    // The part after the decimal point
    if ((peekchar()) == '.' && (CHARCLASS[peek2char()] == NUMERIC)) {
        dFlag = 1;
        getchar();
        while ((c = peekchar()) != EOF && (CHARCLASS[c] == NUMERIC)) {
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

			if (expValue > INT_MAX ){
				continue;
			}
			expValue = expValue * 10 + charval;
		}


	}


  //Putting it together
	if (dFlag) {
		if (eFlag) {
			if (negFlag) {
				real = real / pow (10, expValue);
			} 
      else {
				real = real * pow (10, expValue);
			}

			return returnRealTok(real, tok);

		} else {

			return returnRealTok(real, tok);

		}

	}
	
	if (eFlag)  {
		real = (double) num;
		if (negFlag) {
			real = real / pow(10, expValue);
		} else {
			real = real * pow(10, expValue);
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
