/**
 * @file scanner.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

// all types for tokens
enum TokenType{
    T_STAR=256, T_SLASH, T_PLUS, T_MINUS, T_DOT, T_GREATER, T_GREATER_EQUAL, T_LESS, T_LESS_EQUAL,
    T_BRACE_LEFT, T_BRACE_RIGHT, T_BRACKET_LEFT, T_BRACKET_RIGHT, T_SEMICOLON, T_COLON,
    T_EQUAL, T_EQUAL_EQUAL_EQUAL, T_NOT_EQUAL_EQUAL,

    T_ID, T_INT, T_FLOAT, T_DOUBLE, T_STRING,

    T_START_SYMBOL, T_END_SYMBOL,

    T_ELSE, T_IF, T_FLOAT_K, T_FUNCTION, T_INT_K, T_NULL, T_RETURN, T_STRING_K, T_VOID, T_WHILE
};
// all the keywords we have
char keywords[10][10] = {"else", "if", "float", "function", "int", "null", "return", "string", "void", "while"};
//seperate list fot type identifiers 
char typeID[3][10] = {"int", "float", "string"};

typedef struct Token {
    size_t pos; // position in code 
    enum TokenType type;
    int state = 0; // states of finite-state machine
    char *text; 
} Token_t;

int Check_Keyword(char *s);
int Check_TypeID(char *s);

#endif