/*
* IFJ/IAL project 2022.
* 
* Authors: 
*   Vsevolod Tiemnohorov(xtiemn00)
*   xxx
*   xxx
*   xxx
*/

#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

#define ELSE 256
#define FLOAT 257
#define FUNCTION 258
#define IF 259
#define INT 260
#define NULL_R 261
#define RETURN 262
#define STRING 263
#define VOID 264
#define WHILE 265
#define VARIABLE 266
//all the keywords we have
char keywords[10][10] = {"else", "if", "float", "function", "int", "null", "return", "string", "void", "while"};

typedef struct Token {
    size_t pos; //position in code 
    int type;
    char *text; 
} Token_t;

int Check_Keyword(char *s);
void Scan_Word(FILE* f, Token_t token);

#endif