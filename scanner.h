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

//all types for tokens
enum TokenType{
    STAR, STAR_STAR, SLASH, PLUS, MINUS, DOT, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,
    BRACE_LEFT, BRACE_RIGHT, BRACKET_LEFT, BRACKET_RIGHT, SEMICOLON
    EQUAL, EQUAL_EQUAL_EQUAL, NOT_EQUAL_EQUAL,

    ID, INT, FLOAT, DOUBLE, STRING

    ELSE, IF, FLOAT_K, FUNCTION, INT_K, NULL, RETURN, STRING_K, VOID, WHILE
};
//all the keywords we have
char keywords[10][10] = {"else", "if", "float", "function", "int", "null", "return", "string", "void", "while"};

typedef struct Token {
    size_t pos; //position in code 
    enum TokenType type;
    char *text; 
} Token_t;

int Check_Keyword(char *s);

#endif