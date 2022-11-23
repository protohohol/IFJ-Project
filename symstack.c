#include "symstack.h"
#include <stdlib.h>
#include <stdbool.h>



void stack_init (sstack_t * sstack) {
    sstack->top = NULL;     
}

bool stack_push (sstack_t * sstack, exp_stack_symbol symbol, exp_type type) {
    item_stack_t *  new_item = ( item_stack_t* ) malloc ( sizeof ( struct item_stack ) );
    if ( new_item == NULL ) {
        return false;
    }
    new_item->symbol = symbol;
	new_item->etype = type;
	new_item->next = sstack->top;
	sstack->top = new_item;
	return true;
}

bool stack_push_after (sstack_t * sstack, exp_stack_symbol symbol, exp_type type) {
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
			if ( prev != NULL) {
				new_item->next = prev->next;
				prev->next = new_item;
			} else {
				new_item->next = sstack->top;
				sstack->top = new_item;
			}
			return true;
		}
		tmp = tmp->next;
		prev = tmp;
	}
	return false;
}

bool stack_pop(sstack_t * sstack) {
	if (sstack->top != NULL) {
		item_stack_t * tmp = sstack->top;
		sstack->top = tmp->next;
		free(tmp);
		return true;
	}
	return false;
}

bool stack_pop_mult ( sstack_t * sstack, int count ) {
    return true;
}

item_stack_t* get_top ( sstack_t * sstack) {
    return sstack->top;
}

item_stack_t* get_top_term ( sstack_t * sstack) {
	item_stack_t * tmp = sstack->top;
    while (tmp != NULL) {
		if ( tmp->symbol < ES_CATCH ) {
			return tmp;
		}
		tmp = tmp->next;
	}
}

void stack_dispose (sstack_t * sstack) { 
	while ( ( stack_pop (sstack) ) != 0 );
}


