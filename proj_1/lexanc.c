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

extern int CHARCLASS[];

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
      while ((c = peekchar()) != EOF
             && (c == ' ' || c == '\n' || c == '\t'))
          getchar();
    }

// These functions are called from the parser driver in scanner.c
/* Get identifiers and reserved words */
TOKEN identifier (TOKEN tok)
  {
    tok.tokentype = IDENTIFIERTOK;
    tok.basicdt = STRINGTYPE;

    //loop through and get the identifier name
    char *identifierName[16];
    int i = 0;

    while (peekchar() != EOF && CHARCLASS[peekchar()] == ALPHABETIC && i < 15)
      {
        identifierName[i] = getchar();
        i++;
      }

    identifierName[i] = '\0';
    tok.stringval = identifierName;

    }

TOKEN getstring (TOKEN tok)
  {

    tok.tokentype = STRINGTOK;
    tok.basicdt = STRINGTYPE;

    char *stringName[16];
    int i = 0; 

    while (peekchar() != EOF && CHARCLASS[peekchar()] == ALPHABETIC && i < 15)
      {
        curChar = getchar();
        if (curChar == '\'')
          {
            if (peekchar() == '\'')
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
    tok.stringval = stringName;


    }

TOKEN special (TOKEN tok)
  {
    }

/* Get and convert unsigned numbers of all types. */
TOKEN number (TOKEN tok)
  { long num;
    int  c, charval;
    num = 0;
    while ( (c = peekchar()) != EOF
            && CHARCLASS[c] == NUMERIC)
      {   c = getchar();
          charval = (c - '0');
          num = num * 10 + charval;
        }
    tok->tokentype = NUMBERTOK;
    tok->basicdt = INTEGER;
    tok->intval = num;
    return (tok);
  }

