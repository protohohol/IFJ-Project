#include "scanner.h"
#include "symstack.h"
#include "error.h"


typedef enum
{
	ES_PLUS,			// +
	ES_MINUS,			// -
	ES_MUL,			// *
	ES_DIV,			// /
	ES_EQ,				// ===
	ES_NEQ,			// !==
	ES_LEQ,			// <=
	ES_LTN,			// <
	ES_MEQ,			// >=
	ES_MTN,			// >
	ES_LEFT_BRACKET,	// (
	ES_RIGHT_BRACKET,	// )
	ES_IDENTIFIER,		// ID
	ES_INT_NUMBER,		// int
	ES_FLOAT_NUMBER,	// float
	ES_STRING,			// string
	ES_END,				// $
	ES_CATCH,			// catch for get_top_terminlal function
	ES_START,			// start non terminal
	ES_NON_TERM			// 
} exp_stack_symbol;


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
	ID,		    // A -> i
	EROR,	    // rule error
} exp_rules;

typedef enum
{
	ET_UNDEFINED,	/// Data type undefined
	ET_INT,		/// Integer data type
	ET_FLOAT,	    /// Double data type
	ET_STRING,	/// String data type
} exp_type;

typedef enum {
    C_MORE,
    C_LESS,
    C_EQ,
    C_NONE,
} exp_cond;