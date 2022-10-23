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
    T_STAR=256, T_STAR_STAR, T_SLASH, T_PLUS, T_MINUS, T_DOT, T_GREATER, T_GREATER_EQUAL, T_LESS, T_LESS_EQUAL,
    T_BRACE_LEFT, T_BRACE_RIGHT, T_BRACKET_LEFT, T_BRACKET_RIGHT, T_SEMICOLON,
    T_EQUAL, T_EQUAL_EQUAL_EQUAL, T_NOT_EQUAL_EQUAL,

    T_ID, T_INT, T_FLOAT, T_DOUBLE, T_STRING,

    T_ELSE, T_IF, T_FLOAT_K, T_FUNCTION, T_INT_K, T_NULL, T_RETURN, T_STRING_K, T_VOID, T_WHILE
};
// all the keywords we have
char keywords[10][10] = {"else", "if", "float", "function", "int", "null", "return", "string", "void", "while"};

typedef struct Token {
    size_t pos; // position in code 
    enum TokenType type;
    char *text; 
} Token_t;

int Check_Keyword(char *s);

#endif