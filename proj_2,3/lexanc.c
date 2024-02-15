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

//Reserved words, operators, delimiters
char *reservedWords[] = { "array", "begin", "case", "const", "do", "downto", "else", "end", "file", "for",  "function", "goto", "if", "label", "nil", "of", "packed", "procedure", "program", "record", "repeat", "set", "then", "to", "type", "until", "var", "while", "with"};

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


//Helper to check if a word is in an array
int isInArray(char *arr[], int size, char word[]) {
  for (int i = 0; i < size; i++) {
    if (strcmp(arr[i], word) == 0) {
      return i;
    }
  }
  return -1;
}

//Generic token populator helper
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

  //Get all characters in the word up to 15 characters
	while ( (curChar = peekchar()) != EOF && (CHARCLASS[curChar] == ALPHA || CHARCLASS[curChar] == NUMERIC)){ 
		
    curChar = getchar();
    if (length >= 15) {
      continue;
    }

		word[length] = curChar;
		length++;
	}

	word[length] = '\0';

  //checks if the word is an operator
  int res = isInArray(operators, 19, word);
  if (res != -1) {
    return populateToken(tok, res + 1, OPERATOR);
  }

  //checks if the word is a reserved word
  res = isInArray(reservedWords, 29, word);
  if (res != -1) {
    return populateToken(tok, res + 1, RESERVED);
  }

  //if not an operator or reserved word, it is an identifier
  tok->tokentype = IDENTIFIERTOK;
	strcpy(tok->stringval, word);
	return tok;
  
}


//Get a string from where the stream pointer currently is
TOKEN getstring (TOKEN tok)
{
  //consume first single quote
  getchar();

  int firstChar;
  int length = 0;
  char string[16];


  //Get all characters in the string up to 15 characters
  while ((firstChar = peekchar()) != EOF){
    firstChar = getchar();

    //if a single quote is followed by another, it is not seen as an ending quote
    if (firstChar == '\'') {

      //end
      if (peekchar() != EOF && peekchar( ) != '\'') {
        break;
      } 
      //consume one of the quotes
      else {
        getchar();
      }
    }

    //truncation logic
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


//Get the special character from the stream pointer
TOKEN special (TOKEN tok)
{
	int firstChar;
	char opString[3];

  //Since this is the default case, we have to make sure it is actually a special character
	if ((firstChar = peekchar()) != EOF
			&& CHARCLASS[firstChar] == SPECIAL) {
    
    //get the first and second chars since some special characters are 2 characters long
    int length = 0, res = -1;
		firstChar = getchar();	
		int secondChar = peekchar();
		opString[length] = firstChar;
    length++;
		opString[length] = secondChar;	
		length ++;
		
		opString[length] = '\0';

    //check if the special characters are a delimiter (2)
    res = isInArray(delimiters, 8, opString);
    if (res != -1) {
      getchar();
      return populateToken(tok, res + 1, DELIMITER);
    }

    //check if the special characters are a operator (2)
    res = isInArray(operators, 19, opString);
    if (res != -1) {
      getchar();
      return populateToken(tok, res + 1, OPERATOR);
    }
	
    //test for single special. longer special chars are checked first since they take priority
		opString[length - 1] = '\0';


    //check if char is a delimiter or operator
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

//Helper method to truncate out of range integers for testing output
int shortenInteger(long long num) {
  while (num > INT_MAX) {
        num /= 10;
    }
  return (int)num;
}

//helper to return a float token or print an error message if it is out of range
TOKEN returnFloat(double val, TOKEN tok){
	if (val > FLT_MAX || val < FLT_MIN) {
    printf("Floating number out of range\n");
    tok->tokentype = NUMBERTOK;
    tok->basicdt = REAL;
    tok->realval = 0.0;
	  return tok;
	} 
  else {
    tok->tokentype = NUMBERTOK;
    tok->basicdt = REAL;
    tok->realval = val;
    return tok;
	}
}

//helper to apply the exponent to its base
TOKEN exponentCheck(int exponent, double val, TOKEN tok){
  if (exponent > 0){
    val = val * pow (10, exponent);
  }
  else{
    val = val / pow(10, -exponent);
  }

  returnFloat(val, tok);
}


/* Get and convert unsigned numbers of all types. */
TOKEN number (TOKEN tok)
{ 	

  double val = 0.0;
  int firstChar;
  int digit;
  double decimal = 0.0;
  double decimalScalar = 0.1;
  int exponent = 0;



  //Gets all digits before the "."
  while (peekchar() != EOF && CHARCLASS[peekchar()] == NUMERIC){
    firstChar = getchar();
    digit = firstChar - '0';
    val = val * 10 + digit;
  }

  //all digits after the decimal if there is one
  if (peekchar() == '.'){
    if (CHARCLASS[peek2char()] == NUMERIC){

      //Consume decimal
      getchar();

      //Loop and divide by 10 to apply to the end
      while (peekchar() != EOF && CHARCLASS[peekchar()] == NUMERIC){
        firstChar = getchar();
        digit = firstChar - '0';
        decimal = decimal + ((double)digit * decimalScalar);
        decimalScalar /= 10;
      }
      val = val + decimal;
    }
  }


  if(peekchar() == 'e'){
    getchar();

    // Initialize the exponent sign as positive
    int exponentSign = 1;

    // Check if the next character is a sign
    if (peekchar() == '-' || peekchar() == '+'){
      if (peekchar() == '-'){
        exponentSign = -1;
      }
      getchar(); // Consume the sign character
    }

    // Process the exponent value
    while (peekchar() != EOF && CHARCLASS[peekchar()] == NUMERIC){
      firstChar = getchar();
      digit = firstChar - '0';
      exponent = exponent * 10 + digit;
    }

    // Apply the sign to the exponent
    exponent *= exponentSign;
  }

  //If the number is an integer
  if (decimal == 0.0 && exponent == 0){
    if (val > INT_MAX){
      printf("Integer number out of range\n");
    }

    tok->tokentype = NUMBERTOK;
    tok->basicdt = INTEGER;
    tok->intval = shortenInteger(val);
    return tok;
  }
  
  //any float can be used in this method, even if exponent = 0, the logic works
  return exponentCheck(exponent, val, tok);
  
  }
 

