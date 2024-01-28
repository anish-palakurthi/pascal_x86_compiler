## Project Notes
- making lexical analyzer for Pascal
    - special parser to tokenize code
- getChar() gets next character and moves pointer
- peekChar() returns the next char without incrementing pointer
- peek2Char() returns the second char without moving pointer
- our function is called as the method gettoken() in scanner.c which we implement in lexanc.c


## Closer Details

- we classify tokens into a tokentype which ranges from 0-5 and represents OPERATOR, DELIMITER, RESERVED, IDENTIFIERTOK, STRINGTOK, NUMBERTOK respectively
- datatype is an integer that denotes the type of data so INTEGER REAL STRINGTYPE BOOLETYPE POINTER
- tokenval is the value of the token stored in a union field 
- tabs, blanks, end of lines, and comments are considered separators
    - to treat these, we skip over but don't return
    - comments are contained between {} or * *
        - nesting is not possible and we can use these symbols simply
- here are the possible operators 1- 19
    -  "+ - * / := = <> < <= >= > ^ ."
    - Reserved Words: and or not div mod in
- Delimeters 1- 8
    - ", ; : ( ) [ ] .. "

- output will include the tokentype and the whichval
- other reserved words: 1- 29
- "array       downto    function   of           repeat    until
begin       else      goto       packed       set       var  
case        end       if         procedure    then      while
const       file      label      program      to        with 
do          for       nil        record       type"

- identifiers begin with a letter followed by any number of letters or digits < 15 characters are significant
    - stringval will hold the string

- strings are enclosed by apostrophes and double apostrophes within strings represent just one

- unsigned numbers begin with a digit and if there's a decimal, it needs to be followed by a digit
    - these can be followed by a signed decimal exponent
    - need to be converted to internal numeral