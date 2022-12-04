#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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
    // printf("PIZDA TUT\n");
        if ((s->str = (char *) realloc(s->str, s->length + STR_LEN_INC)) == NULL) {
            return false;
        }
        s->allocSize = s->length + STR_LEN_INC;
    }
    s->str[s->length++] = c;
    s->str[s->length] = '\0';
    return true;
}

bool str_copy_string(string* target, string* source) {
    // printf("s.l : %d\ts.as : %d\ts.s : %s\n", source->length, source->allocSize, source->str);
    // printf("t.l : %d\tt.as : %d\tt.s : %s\n", target->length, target->allocSize, target->str);
    // printf("t.l : %d\tt.as : %d\tt.s : %s\n", target->length, target->allocSize, target->str);
    // if (target->allocSize == 0) {
    //     printf("NULLLLLL SUKAAAA\n");
    // }
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

char* str_copy_const_string(string* source) {
    // printf("hi!\n");
    char tmp[source->length];
    for (int i = 0; i < source->length; i++) {
        tmp[i] = source->str[i];
        printf("tmp[%d] = %c\n", i, tmp[i]);
    }
    return &tmp[0];
}

int str_cmp_string(string* s1, string* s2) {
    return strcmp(s1->str, s2->str);
}

int str_cmp_const_str(string* s1, char* s2) {
    return strcmp(s1->str, s2);
}