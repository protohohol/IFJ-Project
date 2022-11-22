#ifndef _PARSER_H
#define _PARSER_H
#include "scanner.h"
#include "error.h"

// char * built_in_arr [8][10] = {"reads","readi","readf","write","strlen","substring","ord","chr"};
// typedef enum {
//     F_USER,
//     F_SREAD,
//     F_IREAD,
//     F_FREAD,
//     F_WRITE,
//     F_STRLN,
//     F_SUBSTR,
//     F_ORD,
//     F_CHR,
// } built_in_f;

int st_list ( token_t * token );

int define ( token_t * token );

int f_list ( token_t * token );

int declare ( token_t * token );

int expression ( token_t * token );

#endif