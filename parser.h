#ifndef _PARSER_H
#define _PARSER_H
#include "scanner.h"
#include "error.h"

int st_list ( token_t * token );
int define ( token_t * token );
int f_list ( token_t * token );
int declare ( token_t * token );
#endif