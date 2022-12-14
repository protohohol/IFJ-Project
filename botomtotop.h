#ifndef BOTOMTOTOP_H
#define BOTOMTOTOP_H



#include "error.h"
#include "symtable.h"
#include "code_generator.h"



typedef enum {
    R_EQ,		// A -> A === A
	R_NEQ,		// A -> A !== A
	R_L,		// A -> A < A
	R_GR,		// A -> A > A
	R_GREQ,		// A -> A => A
    R_LEQ,      // A -> A <= A
	R_ADD,		// A -> A + A
	R_SUB,	    // A -> A - A
    R_CON,       // A -> A . A
	R_MUL,		// A -> A * A
	R_DIV,		// A -> A / E
	R_PAR,		// A -> (A)
	R_ID,		    // A -> i
	R_ERROR,	    // rule error
} exp_rules;


typedef enum {
    C_MORE,
    C_LESS,
    C_EQ,
    C_NONE,
} exp_cond;

const int convert_to_symbol (token_t * token);
int convert_to_type (token_t * token);
void set_symtable(symtable* source);
void set_id (char* source);
void set_flag(bool source);
void set_type(exp_type* source);
void set_inst_list(DLList* source);
void set_fun_name(string* source);

#endif