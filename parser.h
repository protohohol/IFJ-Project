#ifndef _PARSER_H
#define _PARSER_H
#include "botomtotop.h"
#include "scanner.h"



int f_plist_kostylga( token_t * token );

int kostyluka (token_t * token);

int f_param_kostylga ( token_t * token );

int st_list ( token_t * token );

int define ( token_t * token );

int f_list ( token_t * token );

int declare ( token_t * token );

int expression ( token_t * token );

#endif