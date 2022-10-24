#include <string.h>
#include <stdlib.h>
#include "str.h"

// constant for memory allocation and reallocation
#define STR_LEN_INC 8

bool str_init(string* s) {
    if ((s->str = (char *) malloc(STR_LEN_INC)) == NULL) {
        return false;
    }
    s->allocSize = STR_LEN_INC;
    s->length = 0;
    s->str[0] = '\0';
    return true;
}

void str_free(string* s) {
    free(s->str);
}

void str_clear(string* s) {
    s->length = 0;
    s->str[0] = '\0';
}

bool str_add_char(string* s, char c) {
    if (s->length + 1 >= s->allocSize) { // this means we need more memory
        if ((s->str = (char *) realloc(s->str, s->length + STR_LEN_INC)) == NULL) {
            return false;
        }
        s->allocSize = s->length + STR_LEN_INC;
    }
    s->str[s->length + 1] = c;
    s->length++;
    s->str[s->length] = '\0';
    return true;
}

bool str_copy_str(string* target, string* source) {
    if (source->length >= target->allocSize) { // this means we need more memory
        if ((target->str = (char *) realloc(target->str, source->length + 1)) == NULL) {
            return false;
        }
        target->allocSize = source->length + 1;
    }
    strcpy(target->str, source->str);
    target->length = source->length;
    return true;
}

int str_cmp_string(string* s1, string* s2) {
    return strcmp(s1->str, s2->str);
}

int str_cmp_const_str(string* s1, char* s2) {
    return strcmp(s1->str, s2);
}