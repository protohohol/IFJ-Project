#ifndef _SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "str.h"

#define MAX_SIZE 25000

typedef enum {
    D_VOID,
    D_INT,
    D_DOUBLE,
    D_FLOAT,
    D_STRING,
}data_type;

typedef struct {
    data_type type;
    string* arguments;
    int global_var;

}htab_data_t;

typedef struct htab_item {
    htab_data_t data;
    char* key;
    struct htab_item* next;
}htab_item_t;

typedef htab_item_t* symtable[MAX_SIZE];

void symtable_init (symtable* table);

int get_hash (char *key);

symtable* symtable_insert (symtable* table, char* key);

symtable* symtable_search (symtable* table, char* key);

int symtable_delete (symtable* table, char* key);

void symtable_free (symtable* table);

#endif