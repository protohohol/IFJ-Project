#include <stdio.h>
#include <stdbool.h>
#include "symbol_table.h"

int get_hash(char *key) {
  int result = 1;
  int length = strlen(key);
  for (int i = 0; i < length; i++) {
    result += key[i];
  }
  return (result % MAX_SIZE);
}

bool symtable_init(symtable* table) {
    if (table == NULL) {
        return false;
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        (*table)[i] = NULL;
    }

    // htab_data_t* tmpData = symtable_insert(table, "reads");
    // symtable_add_type(tmpData, D_STRING);

    // htab_data_t* tmpData = symtable_insert(table, "readi");
    // symtable_add_type(tmpData, D_INT);

    // htab_data_t* tmpData = symtable_insert(table, "readf");
    // symtable_add_type(tmpData, D_FLOAT);

    // htab_data_t* tmpData = symtable_insert(table, "write");
    // symtable_add_type(tmpData, D_VOID);
    // symtable_add_arguments(tmpData, D_TERM, true);

    // htab_data_t* tmpData = symtable_insert(table, "floatval");
    // symtable_add_type(tmpData, D_FLOAT);
    // symtable_add_arguments(tmpData, D_TERM, false);

    // htab_data_t* tmpData = symtable_insert(table, "intval");
    // symtable_add_type(tmpData, D_INT);
    // symtable_add_arguments(tmpData, D_TERM, false);

    // htab_data_t* tmpData = symtable_insert(table, "strval");
    // symtable_add_type(tmpData, D_STRING);
    // symtable_add_arguments(tmpData, D_TERM, false);

    // htab_data_t* tmpData = symtable_insert(table, "strlen");
    // symtable_add_type(tmpData, D_INT);
    // symtable_add_arguments(tmpData, D_STRING, false);

    // htab_data_t* tmpData = symtable_insert(table, "substring");
    // symtable_add_type(tmpData, D_STRING);
    // symtable_add_arguments(tmpData, D_STRING, false);
    // symtable_add_arguments(tmpData, D_INT, false);
    // symtable_add_arguments(tmpData, D_INT, false);

    // htab_data_t* tmpData = symtable_insert(table, "ord");
    // symtable_add_type(tmpData, D_INT);
    // symtable_add_arguments(tmpData, D_STRING, false);

    // htab_data_t* tmpData = symtable_insert(table, "chr");
    // symtable_add_type(tmpData, D_STRING);
    // symtable_add_arguments(tmpData, D_INT, false);
    return true;
}

htab_data_t* symtable_search(symtable* table, char* key) {
    if (table == NULL || key == NULL) {
        return NULL;
    }

    int index = get_hash(key);
    htab_item_t* tmpItem = (*table)[index];

    while (tmpItem != NULL) {

        if(!strcmp(tmpItem->key, key)) {
            return &tmpItem->data;
        }

        tmpItem = tmpItem->next;
    }

    return NULL;
}

htab_data_t* symtable_insert(symtable* table, char* key) {
    if (table == NULL || key == NULL) {
        return NULL;
    }

    htab_data_t* tmpData = symtable_search(table, key);
    if(tmpData != NULL) {
        return NULL;
    }

    htab_item_t* newItem = (htab_item_t*) malloc(sizeof(htab_item_t));

    if (newItem == NULL) {
        return NULL;
    }

    newItem->key = (char*)malloc((strlen(key) + 1) * sizeof(char));
    if (newItem->key == NULL) {
        free(newItem);
        return NULL;
    }

    newItem->data.id = (char*)malloc((strlen(key) + 1) * sizeof(char));
    if (newItem->data.id == NULL) {
        free(newItem->key);
        free(newItem);
        return NULL;
    }

    newItem->data.arguments = (string*)malloc(sizeof(string));
    if (newItem->data.arguments == NULL) {
        free(newItem->key);
        free(newItem->data.id);
        free(newItem);
        return NULL;
    }

    if (!str_init(newItem->data.arguments)) {
        free(newItem->data.arguments);
        free(newItem->key);
        free(newItem->data.id);
        free(newItem);
        return NULL;
    }

    strcpy(newItem->key, key);
    strcpy(newItem->data.id, key);
    newItem->data.global_var = false;
    newItem->data.argumets_amount = 0;
    newItem->data.infinite = false;
    // newItem->data.type = NULL;
    newItem->next = NULL;

    int index = get_hash(key);
    htab_item_t* tmpItem_2 = (*table)[index];

    if (tmpItem_2 == NULL) {
        (*table)[index] = newItem;
    } else {
        newItem->next = tmpItem_2;
        (*table)[index] = newItem;
    }

    return &newItem->data;
}

bool symtable_add_arguments (htab_data_t* data, data_type type, bool infinite_args) {

    if (data == NULL) {
        return false;
    }
    
    data->infinite = infinite_args;

    if (type == D_INT) {
        if (!str_add_char(data->arguments, 'i')) {
            return false;
        }
        ++data->argumets_amount;
    } else if (type == D_FLOAT) {
        if (!str_add_char(data->arguments, 'f')) {
            return false;
        }
        ++data->argumets_amount;
    } else if (type == D_STRING) {
        if (!str_add_char(data->arguments, 's')) {
            return false;
        }
        ++data->argumets_amount;
    } else if (type == D_TERM) {
        if (!str_add_char(data->arguments, 't')) {
            return false;
        }
        ++data->argumets_amount;
    }
    return true;
}

bool symtable_add_type (htab_data_t* data, data_type type) {
    if (data == NULL) {
        return false;
    }

    data->type = type;
    return true;
}

bool symtable_delete (symtable* table, char* key) {
    if(table == NULL || key == NULL) {
        return false;
    }

    int index = get_hash(key);
    htab_item_t* previousItem = NULL;
    htab_item_t* item = (*table)[index];
    int posCounter = 0;

    while (item != NULL) {
        
        if (item->key == key) {
            if (posCounter == 0) {
                (*table)[index] = item->next;
            }
            else {
                previousItem->next = item->next;
            }
            free(item->key);
            
            if (item->data.arguments != NULL) {
                str_free(item->data.arguments);
                free(item->data.arguments);
            }

            free(item);
            return true;
        }
        ++posCounter;
        previousItem = item;
        item = item->next;

    }
    return false;
    
}

void symtable_free(symtable* table) {
    if(table == NULL) {
        return;
    }

    htab_item_t* tmpItem_next = NULL;

    for (int i = 0; i < MAX_SIZE; i++) {
        htab_item_t* tmpItem = (*table)[i];

        while (tmpItem != NULL) {
            tmpItem_next = tmpItem->next;

            free(tmpItem->key);

            if (tmpItem->data.arguments != NULL) {
                str_free(tmpItem->data.arguments);
                free(tmpItem->data.arguments);
            }

            free(tmpItem);
            tmpItem = tmpItem_next;       
        }

        (*table)[i] = NULL;
    }
}

void symtable_stack_init(symtable_stack_t* stack) {
    // if (stack == NULL) {
    //     return false;
    // }

    // symtable tmp;
    // stack->top->symt = &tmp;

    // stack->top->next = NULL;
    // stack->top->prev = NULL;
    // return symtable_init(stack->top->symt);

    stack->top = NULL;
}

void symtable_stack_pop(symtable_stack_t* stack) {
    if (stack == NULL || stack->top == NULL) {
        return;
    }

    symtable_level_t* current;
    do {
        current = stack->top;
    } while (current->next != NULL);

    if (current->prev != NULL) {
        current->prev->next = NULL;
    }

    symtable_free(current->symt);
}

void symtable_stack_free(symtable_stack_t* stack) {
    if (stack == NULL || stack->top == NULL) {
        return;
    }

    while (stack->top->next != NULL) {
        symtable_stack_pop(stack);
    }

    symtable_stack_pop(stack);
}

symtable_level_t* symtable_stack_push(symtable_stack_t* stack, symtable* symt) {
    if (stack == NULL || symt == NULL) {
        return NULL;
    }

    // symtable tmp;
    // if(!symtable_init(&tmp)) {
    //     return NULL;
    // }

    if (stack->top == NULL) {
        stack->top = (symtable_level_t*) malloc(sizeof(symtable_level_t));
        stack->top->next = NULL;
        stack->top->prev = NULL;
        stack->top->symt = symt;
        return stack->top;
    }

    symtable_level_t* current;
    do {
        current = stack->top;
    } while (current->next != NULL);

    symtable_level_t* l_tmp = (symtable_level_t*) malloc(sizeof(symtable_level_t));
    l_tmp->symt = symt;
    l_tmp->prev = current;
    l_tmp->next = NULL;

    current->next = l_tmp;
    return l_tmp;
}