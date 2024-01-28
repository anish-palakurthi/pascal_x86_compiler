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

