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
#include <ctype.h>
#include <stdlib.h>
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
	T_BRACE_LEFT,         	// {
	T_BRACE_RIGHT,        	// }
	T_SEMICOLON,            // ;
	T_COLON,                // :
    T_ASSIGN,               // =
	T_EQUAL,                // ===
	T_NOT_EQUAL,            // !==
    T_START_SYMBOL,         // <?php
	T_END_SYMBOL,           // ?>
    T_KW_ELSE,              // keyword "else"
	T_KW_IF,                // keyword "if"
	T_KW_FLOAT,             // keyword "float"
	T_KW_FUNCTION,          // keyword "function"
	T_KW_INT,               // keyword "int"
	T_KW_NULL,              // keyword "null"
	T_KW_RETURN,            // keyword "return"
	T_KW_STRING,            // keyword "string"
	T_KW_VOID,              // keyword "void"
	T_KW_WHILE,             // keyword "while"
	T_VAR_ID,				// variable identifier
	T_FUN_ID,				// function identifier
	T_INT_VAL,				// integer value
	T_DEC_VAL,				// decimal value
	T_STRING_VAL,			// string value
} token_type;

typedef enum {
    S_START = 100,			// start state
    S_EOF,					// end of file state
    S_MUL,					// state for multiply
	S_GREATER,				// state for greater
	S_GREATER_EQUAL,		// state for greater or equal
	S_LESS,					// state for less
	S_LESS_EQUAL,			// state for less or equal
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
	S_VAR_ID,
	S_KW_FUN_START,			// start state for keyword or function name
    S_KW_FUN,				// state for keyword or function name 
	S_KW_TYPE,				// state for type keywords
    S_START_SYMBOL,			// state for prolog
	S_END_SYMBOL,			// state for end symbol (?>)
    S_ELSE,
	S_IF,
	S_FLOAT,
	S_FUNCTION,
	S_INT_DEC,				// state for int or decimal
	S_DEC_START,			// start state for decimal
	S_DEC,					// state for decimal
	S_EXP,					// state for exponential
	S_INT,
	S_STRING,
	S_ESC,
	S_ESC_OCT_START,
	S_ESC_OCT,
	S_ESC_HEX_START,
	S_ESC_HEX,
	S_COMMENT_START,
	S_COMMENT_LINE,
	S_COMMENT_BLOCK,
	S_COMMENT_BLOCK_END,
} fm_state;

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
 * @param t pointer to token
 * @return 0 if operation was successful
 */
const int get_next_token(token_t* t);

#endif