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

#include "str.h"

typedef enum  {
    T_EOL,                  // end of line
    T_EOF,                  // end of file
    T_MUL,                  // *
	T_DIV,                  // /
	T_ADD,                  // +
	T_SUB,                  // -
	T_DOT,                  // .
	T_GREATER,              // >
	T_GREATER_EQUAL,        // >=
	T_LESS,                 // <
	T_LESS_EQUAL,           // <=
    T_PAR_LEFT,             // (
	T_PAR_RIGHT,            // )
	T_BRACKET_LEFT,         // [
	T_BRACKET_RIGHT,        // ]
	T_SEMICOLON,            // ;
	T_COLON,                // :
    T_ASSIGN,               // =
	T_EQUAL,                // ===
	T_NOT_EQUAL,            // !==
    T_FUN_ID,               // function identifier
    T_VAR_ID,               // variable identifier
    T_START_SYMBOL,         // <?php
	T_END_SYMBOL,           // ?>
    T_ELSE,                 // keyword "else"
	T_IF,                   // keyword "if"
	T_FLOAT,                // keyword "float"
	T_FUNCTION,             // keyword "function"
	T_INT,                  // keyword "int"
	T_NULL,                 // keyword "null"
	T_RETURN,               // keyword "return"
	T_STRING,               // keyword "string"
	T_VOID,                 // keyword "void"
	T_WHILE,                // keyword "while"
} token_type;

typedef enum {
    S_START = 100,
    S_EOL,
    S_EOF,
    S_MUL,
	S_GREATER,
	S_GREATER_EQUAL,
	S_LESS,
	S_LESS_EQUAL,
    S_PAR_LEFT,
	S_PAR_RIGHT,
	S_BRACKET_LEFT,
	S_BRACKET_RIGHT,
	S_SEMICOLON,
	S_COLON,
    S_EQUAL,
    S_EQUAL_EQUAL,
	S_EQUAL_EQUAL_EQUAL,
    S_NOT,
    S_NOT_EQUAL,
	S_NOT_EQUAL_EQUAL,
    S_FUN_ID,
    S_VAR_ID,
    S_START_SYMBOL,
	S_END_SYMBOL,
    S_ELSE,
	S_IF,
	S_FLOAT,
	S_FUNCTION,
	S_INT,
	S_NULL,
	S_RETURN,
	S_STRING,
	S_VOID,
	S_WHILE,
} fm_state;

// all the keywords we have
// char keywords[10][10] = {"else", "if", "float", "function", "int", "null", "return", "string", "void", "while"};
// seperate list fot type identifiers 
// char typeID[3][10] = {"int", "float", "string"};

typedef union {
	string *string_c;	// text content
	double double_c; 	// decimal content
	int int_c; 			// integer content
} data_u;

typedef struct token {
    token_type type; 	// token type
    data_u *data; 		// token content
} token_t;

/**
 * @brief Sets input to be analyzed
 * 
 * @param f pointer to file
 */
void set_source(FILE* f);

/**
 * @brief Get the Next Token object
 * 
 * @param s pointer to string
 * @return 0 if operation was successful
 * @return -1 if an error appeared
 */
int get_next_token(token_t* t);

#endif