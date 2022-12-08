#include <stdbool.h>

typedef enum
{
	ET_UNDEFINED,	// Data type undefined
	ET_INT,		// Integer data type
	ET_FLOAT,	    // Double data type
	ET_STRING,	// String data type
	ET_NULL,	
} exp_type;

typedef enum
{
	ES_PLUS,			// +
	ES_MINUS,			// -
	ES_CON,              // . 
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
	ES_ID,		// ID
	ES_INT_LIT,		// int
	ES_FLOAT_LIT,	// float
	ES_STR,			// string
	ES_NULL,        // null value
	ES_END,				// $
	ES_CATCH,			// catch for get_top_terminlal function
	ES_NON_TERM			// 
} exp_stack_symbol;

typedef struct item_stack {
    exp_stack_symbol symbol;
    exp_type etype;
	char* value;
    struct item_stack * next;
} item_stack_t;

typedef struct sstack {
    item_stack_t * top;
} sstack_t;

void stack_init (sstack_t * sstack);
bool stack_push (sstack_t * sstack, exp_stack_symbol symbol, exp_type type, char* value);
bool stack_push_after (sstack_t * sstack, exp_stack_symbol symbol, exp_type type, char* value);
bool stack_pop(sstack_t * sstack);
bool stack_pop_mult ( sstack_t * sstack, int count );
item_stack_t* get_top ( sstack_t * sstack);
item_stack_t* get_top_term ( sstack_t * sstack);
void stack_dispose (sstack_t * sstack);