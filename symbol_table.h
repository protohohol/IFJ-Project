#ifndef _SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "str.h"

#define MAX_SIZE 25000

typedef enum {
    D_INT,
    D_FLOAT,
    D_VOID,
    D_STRING,
    D_TERM,
    D_UNDEFINED,
} data_type;

typedef struct {
    data_type type;
    string* arguments;
    char* id;
    bool global_var;
    int argumets_amount;
    bool infinite;
    bool is_defined;
} htab_data_t;

typedef struct htab_item {
    htab_data_t data;
    char* key;
    struct htab_item* next;
} htab_item_t;

typedef htab_item_t* symtable[MAX_SIZE];

typedef struct symtable_level {
    symtable* symt;
    struct symtable_level* next;
    struct symtable_level* prev;
} symtable_level_t;

typedef struct symtable_stack {
    symtable_level_t* top;
    symtable_level_t* active;
} symtable_stack_t;

bool symtable_init (symtable* table);

int get_hash (char *key);

htab_data_t* symtable_insert (symtable* table, char* key);

htab_data_t* symtable_search (symtable* table, char* key);

bool symtable_add_arguments (htab_data_t* data, data_type type, bool infinite_args);

bool symtable_add_type (htab_data_t* data, data_type type);

bool symtable_delete (symtable* table, char* key);

void symtable_free (symtable* table);

void symtable_stack_init(symtable_stack_t* stack);

void symtable_stack_free(symtable_stack_t* stack);

symtable_level_t* symtable_stack_push(symtable_stack_t* stack);

void symtable_stack_pop(symtable_stack_t* stack);

#endif