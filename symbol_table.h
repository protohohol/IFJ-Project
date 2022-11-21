#ifndef _SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H

#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 25000

typedef struct htab_item
{
    char* key;
    struct htab_item* next;
}htab_item_t;

typedef htab_item_t* htab_t[MAX_SIZE];

void htab_init(htab_t* table);



#endif