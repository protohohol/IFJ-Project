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

void symtable_init(symtable* table) {
    if (table == NULL) {
        return;
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        (*table)[i] = NULL;
    }
}

symtable* symtable_search(symtable* table, char* key) {
    if (table == NULL || key == NULL) {
        return NULL;
    }

    int index = get_hash(key);
    htab_item_t* tmpItem = (*table)[index];

    while (tmpItem != NULL) {

        if(!strcmp(tmpItem->key, key)) {
            return &tmpItem;
        }

        tmpItem = tmpItem->next;
    }

    return NULL;
}

symtable* symtable_insert(symtable* table, char* key) {
    if (table == NULL || key == NULL) {
        return NULL;
    }

    htab_item_t* tmpItem = symtable_search(table, key);
    if(tmpItem != NULL) {
        return NULL;
    }

    htab_item_t* newItem = (htab_item_t*)malloc(sizeof(htab_item_t));

    if (newItem == NULL) {
        return NULL;
    }

    newItem->key = (char*)malloc((strlen(key) + 1) * sizeof(char));
    if (newItem->key == NULL) {
        free(newItem);
        return NULL;
    }

    newItem->data.arguments = (string*)malloc(sizeof(string));
    if (newItem->data.arguments == NULL) {
        free(newItem->key);
        free(newItem);
        return NULL;
    }

    if (!str_init(newItem->data.arguments)) {
        free(newItem->data.arguments);
        free(newItem->key);
        free(newItem);
        return NULL;
    }

    strcpy(newItem->key, key);
    newItem->data.global_var = 0;
    newItem->data.type = NULL;
    newItem->next = NULL;

    int index = get_hash(key);
    htab_item_t* tmpItem_2 = (*table)[index];

    if (tmpItem_2 == NULL) {
        (*table)[index] = newItem;
    } else {
        newItem->next = tmpItem_2;
        (*table)[index] = newItem;
    }

    return &newItem;
}

int symtable_delete (symtable* table, char* key) {
    if(table == NULL || key == NULL) {
        return 0;
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
            return 1;
        }
        ++posCounter;
        previousItem = item;
        item = item->next;

    }
    return 0;
    
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

