#include "symstack.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>



void stack_init (sstack_t * sstack) {
	sstack->top = NULL;
	// printf("zalupa\n");
}

bool stack_push (sstack_t * sstack, exp_stack_symbol symbol, exp_type type, char* value) {
	// if (value == NULL) {
	// 	printf("NULL\n");
	// }
	// printf("hi11123123\n");
	// printf("value : %s\n", value);
    item_stack_t *  new_item = ( item_stack_t* ) malloc ( sizeof ( struct item_stack ) );
    if ( new_item == NULL ) {
        return false;
    }
    new_item->symbol = symbol;
	new_item->etype = type;
	new_item->value = NULL;
	if (value == NULL) {
		new_item->value = NULL;
	} else {
		new_item->value = (char*) malloc((strlen(value)+1) * __CHAR_BIT__);
		if (new_item->value == NULL) {
			free(new_item);
			return false;
		}
		strcpy(new_item->value, value);
		// printf("\t\t\t\t\t\t\tnewItem : %s\n", new_item->value);
	}
	new_item->next = sstack->top;
	sstack->top = new_item;
	return true;
}

bool stack_push_after (sstack_t * sstack, exp_stack_symbol symbol, exp_type type, char* value) {
	item_stack_t * tmp = sstack->top;
	item_stack_t * prev = NULL;
    while (tmp != NULL) {
		if ( tmp->symbol < ES_CATCH ) {
			item_stack_t *  new_item = ( item_stack_t* ) malloc ( sizeof ( struct item_stack ) );
			if ( new_item == NULL ) {
				return false;
			}
			new_item->symbol = symbol;
			new_item->etype = type;
			new_item->value = NULL;
			if (value == NULL) {
				new_item->value = NULL;
			} else {
				new_item->value = (char*) malloc((strlen(value)+1) * __CHAR_BIT__);
				if (new_item->value == NULL) {
					free(new_item);
					return false;
				}
				strcpy(new_item->value, value);
			}
			if ( prev == NULL) {
				new_item->next = sstack->top;
				sstack->top = new_item;
			} else {
				new_item->next = prev->next;
				prev->next = new_item;
			}
			return true;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return false;
}

bool stack_pop_mult ( sstack_t * sstack, int count ) {
    for ( int i = 0; i < count; i++)
	{
		stack_pop(sstack);
	}
	return true;
}

bool stack_pop ( sstack_t * sstack ) {
	if (sstack->top != NULL) {
		item_stack_t * tmp = sstack->top;
		if (tmp->value != NULL) {
			free(tmp->value);
		}
		sstack->top = tmp->next;
		free(tmp);
		return true;
	}
	return false;
}

item_stack_t* get_top ( sstack_t * sstack ) {
    return sstack->top;
}

item_stack_t* get_top_term ( sstack_t * sstack ) {
	item_stack_t * tmp = sstack->top;
    while (tmp != NULL) {
		if ( tmp->symbol < ES_CATCH ) {
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

void stack_dispose (sstack_t * sstack) { 
	while ( ( stack_pop (sstack) ) != 0 );
}