#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "scanner.h"
int error_type = 0;

void error(int flag){
    switch (flag)
    {
    case (LEX_ERR):
        exit(1);
        break;
    default:
        exit(1);
        break;
    }
}

void state(token_t * token){
    switch (token->type) {
        case (T_KW_RETURN):
            if (error_type = gettoken(token)) {
                error(error_type);
            }
            epxression(token);
            break;
        case (T_VAR_ID):
            if (error_type = gettoken(token)) {
                error(error_type);
            }
            if(token->data==T_ASSIGN){
                if (error_type = gettoken(token)) {
                error(error_type);
                }
                expression(token);
            }
            else
                expression(token);
            break;
        case (T_FUN_ID):
            if (error_type = gettoken(token)) {
                error(error_type);
            }
            delcare(token);
            break;
        case (T_KW_FUNCTION):
            if (error_type = gettoken(token)) {
                error(error_type);
            }
            if (token->data == T_FUN_ID){
                if (error_type = gettoken(token)) {
                    error(error_type);
                }
                define(token);
                if(token->data == T_COLON) {
                    if (error_type = gettoken(token)) {
                    error(error_type);
                    }
                    if(token->data == T_KW_FLOAT || token->data == T_KW_INT || token->data == T_KW_STRING) {
                        if (error_type = gettoken(token)) {
                            error(error_type);
                        }
                        if(token->data == T_BRACE_RIGHT){
                            if (error_type = gettoken(token)) {
                                error(error_type);
                            }
                            f_list(token);
                        } else {
                            error("отсылаем тип хибы интом или чем-нибудь, мне похуй");
                        }
                    }
                } else {
                    error("отсылаем тип хибы интом или чем-нибудь, мне похуй");
                }
            }else {
                error("отсылаем тип хибы интом или чем-нибудь, мне похуй");
            }
        case (T_KW_WHILE):

        case (T_KW_ELSE):
        case (T_KW_IF):
            state(token);
            if (token == T_BRACE_RIGHT) {
                if (error_type = gettoken(token)) {
                    error(error_type);
                }
            } else {
                error("отсылаем тип хибы интом или чем-нибудь, мне похуй");
            }
            st_list(token);
            break;
        default:
            error("отсылаем тип хибы интом или чем-нибудь, мне похуй");
    }
}

void st_list(token_t * token){
    switch (token->type) {
        case (T_KW_RETURN):
        case (T_VAR_ID):
        case (T_FUN_ID):
            state(token);
            if (token == T_SEMICOLON) {
                if (error_type = gettoken(token)) {
                    error(error_type);
                }
            } else {
                error("отсылаем тип хибы интом или чем-нибудь, мне похуй");
            }
            st_list(token);
            break;
        case (T_KW_FUNCTION):
        case (T_KW_WHILE):
        case (T_KW_ELSE):
        case (T_KW_IF):
            state(token);
            if (token == T_BRACE_RIGHT) {
                if (error_type = gettoken(token)) {
                    error(error_type);
                }
            } else {
                error("отсылаем тип хибы интом или чем-нибудь, мне похуй");
            }
            st_list(token);
            break;
        case (T_END_SYMBOL):
            return;
            break;
        case (T_EOF):
            return;
            break;
        default:
            error("отсылаем тип хибы интом или чем-нибудь, мне похуй");
    }
}

void prog(token_t * token){
    if(token->type == 22){  // if token is <?php
        if (error_type = gettoken(token)) {
            error(error_type);
        }
        st_list(token);
    }
    else
        error("отсылаем тип хибы интом или чем-нибудь, мне похуй");
}

int main(){
    token_t * token;
    if (error_type = gettoken(token)) {
        error(error_type);
    }
    prog(token);
}


