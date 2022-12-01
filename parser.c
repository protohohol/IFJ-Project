#include "parser.h"
int error_type;






int f_state ( token_t * token ) {
    switch (token->type) {
        case (T_KW_RETURN):
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            if ( token->type == T_FUN_ID ) {
                return declare(token);
            } else {
            return expression(token);
            }
            break;
        case (T_VAR_ID):
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            if( token->type == T_ASSIGN ){
                if (error_type = get_next_token(token)) {
                    return error_type;
                }
                if ( token->type == T_FUN_ID ) {
                    return declare(token);
                } else if ( token->type == T_VAR_ID || token->type == T_INT_VAL || token->type == T_DEC_VAL || token->type == T_STRING_VAL  ) {
                    return expression(token);    
                } else {
                    return SYNTAX_ERR;
                }
            }
            else
                return expression(token);
            break;
        case (T_FUN_ID):
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            return declare(token);
            break;
        case (T_KW_WHILE):
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            if (token->type == T_PAR_LEFT) {
                if (error_type = get_next_token(token)) {
                    return error_type;
                }
                error_type = expression(token);
                if (error_type != NO_ERR) {
                    return error_type;
                }
                if (token->type == T_PAR_RIGHT) {
                    if (error_type = get_next_token(token)) {
                        return error_type;
                    }
                    if (token->type == T_BRACE_LEFT) {
                        if (error_type = get_next_token(token)) {
                            return error_type;
                        }
                        return f_list(token);
                    } else {
                        return SYNTAX_ERR;
                    }
                } else {
                    return SYNTAX_ERR;
                }
            } else {
                return SYNTAX_ERR;
            }
            break;
        case (T_KW_ELSE):
            if ( error_type = get_next_token(token) ) {
                return error_type;
            }
            if (token->type == T_BRACE_LEFT) {
                if ( error_type = get_next_token(token) ) {
                    return error_type;
                }
                error_type = f_list(token);
                return error_type;
            } else {
                return SYNTAX_ERR;
            }
            break;
        case (T_KW_IF):
            if ( error_type = get_next_token(token) ) {
                return error_type;
            }
            if (token->type == T_PAR_LEFT) {
                if ( error_type = get_next_token(token) ) {
                    return error_type;
                }
                error_type = expression(token);
                if (error_type != NO_ERR) {
                    return error_type;
                }
                if ( token->type == T_PAR_RIGHT ) {
                    if ( error_type = get_next_token(token) ) {
                        return error_type;
                    }
                    if ( token->type == T_BRACE_LEFT) {
                        if ( error_type = get_next_token(token) ) {
                            return error_type;
                        }
                        return f_list(token);
                    } else {
                        return SYNTAX_ERR;
                    }
                } else {
                    return SYNTAX_ERR;
                }
            } else {
                return SYNTAX_ERR;
            }
            break;
        case (T_BRACE_RIGHT):
            return NO_ERR;
        default:
            return SYNTAX_ERR;
    }
}

int f_list ( token_t * token ) {
    switch (token->type) {
        case (T_KW_RETURN):
        case (T_VAR_ID):
        case (T_FUN_ID):
            error_type = f_state(token);
            if (error_type != NO_ERR) {
                return error_type;
            }
            if (token->type == T_SEMICOLON) {
                if (error_type = get_next_token(token)) {
                    return error_type;
                }
                return f_list(token);
            } else {
                return SYNTAX_ERR;
            }
            break;
        case (T_KW_WHILE):
        case (T_KW_ELSE):
        case (T_KW_IF):
            error_type = f_state(token);
            if (error_type != NO_ERR) {
                return error_type;
            }
            if (token->type == T_BRACE_RIGHT) {
                if (error_type = get_next_token(token)) {
                    return error_type;
                }
            } else {
                return SYNTAX_ERR;
            }
            return f_list(token);
            break;
        default:
            return SYNTAX_ERR;
    }
}
int f_param_d ( token_t * token ) {
    if ( token->type == T_STRING_VAL || token->type == T_DEC_VAL || token->type == T_INT_VAL|| T_VAR_ID ) {
        if ( error_type = get_next_token(token) ) {
            return error_type;
        }
        return NO_ERR;
    } else {
        return SYNTAX_ERR;
    }
}

int f_plist_d( token_t * token ) {
    if ( token->type == T_COMMA ) {
        if (error_type = get_next_token(token)) {
            return error_type;
        }
        error_type = f_param_d(token);
        if (error_type) {
            return error_type;
        }
        return f_plist_d(token);
    } else if ( token->type == T_DEC_VAL || token->type == T_INT_VAL || token->type == T_STRING_VAL || token->type == T_VAR_ID ) {
        error_type = f_param_d(token);
        if (error_type) {
            return error_type;
        }
        return f_plist_d(token);
    } else if ( token->type == T_PAR_RIGHT ) {
        if (error_type = get_next_token(token)) {
            return error_type;
        }
        return NO_ERR;
    } else {
        return SYNTAX_ERR;
    }
}

int f_param ( token_t * token ) {
    if ( token->type == T_KW_FLOAT || token->type == T_KW_INT || token->type == T_KW_STRING ) {
        if ( error_type = get_next_token(token) ) {
            return error_type;
        }
        if (token->type == T_VAR_ID) {
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            return NO_ERR;
        } else {
            return SYNTAX_ERR;
        }
    } else {
        return SYNTAX_ERR;
    }
}


int f_plist( token_t * token ) {
    if ( token->type == T_COMMA ) {
        if (error_type = get_next_token(token)) {
            return error_type;
        }
        error_type = f_param(token);
        if (error_type) {
            return error_type;
        }
        return f_plist(token);
    } else if ( token->type == T_KW_FLOAT || token->type == T_KW_INT || token->type == T_KW_STRING) {
        error_type = f_param(token);
        if (error_type) {
            return error_type;
        }
        return f_plist(token);
    } else if ( token->type == T_PAR_RIGHT ) {
        if (error_type = get_next_token(token)) {
            return error_type;
        }
        return NO_ERR;
    } else {
        return SYNTAX_ERR;
    }
}

int declare(token_t * token){
    if(token->type == T_PAR_LEFT) {
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            error_type = f_plist_d(token);
            if (error_type) {
                return error_type;
            }
    }
}

int define (token_t * token) {
    if(token->type == T_PAR_LEFT) {
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            error_type = f_plist(token);
            if (error_type) {
                return error_type;
            }
    }
}

int state(token_t * token){
    printf("i am in state\n");
    switch (token->type) {
        case (T_KW_RETURN):
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            if ( token->type == T_FUN_ID ) {
                return declare(token);
            } else {
            return expression(token);
            }
            break;
        case (T_VAR_ID):
            //check_sem();
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            if( token->type == T_ASSIGN ){
                if (error_type = get_next_token(token)) {
                    return error_type;
                }
                if ( token->type == T_FUN_ID ) {
                    return state(token);
                } else if ( token->type == T_VAR_ID || token->type == T_INT_VAL || token->type == T_DEC_VAL || token->type == T_STRING_VAL  ) {
                    return expression(token);    
                } else {
                    return SYNTAX_ERR;
                }
            }
            else
                return expression(token);//tut eben'
            break;
        case (T_FUN_ID):
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            return declare(token);
            break;
        case (T_KW_FUNCTION):
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            if (token->type == T_FUN_ID){
                if (error_type = get_next_token(token)) {
                    return error_type;
                }
                error_type = define(token);
                if (error_type) {
                    return error_type;
                }
                if(token->type == T_COLON) {
                    if (error_type = get_next_token(token)) {
                        return error_type;
                    }
                    if( token->type == T_KW_FLOAT || token->type == T_KW_INT || token->type == T_KW_STRING ) {
                        if (error_type = get_next_token(token)) {
                            return error_type;
                        }
                        if(token->type == T_BRACE_RIGHT){
                            if (error_type = get_next_token(token)) {
                                return error_type;
                            }
                            return f_list(token);
                        } else {
                            return SYNTAX_ERR;
                        }
                    } else {
                        return SYNTAX_ERR;
                    }
                } else {
                    return SYNTAX_ERR;;
                }
            }else {
                return SYNTAX_ERR;
            }
            break;
        case (T_KW_WHILE):
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            if (token->type == T_PAR_LEFT) {
                if (error_type = get_next_token(token)) {
                    return error_type;
                }
                error_type = expression(token);
                if (error_type != NO_ERR) {
                    return error_type;
                }
                if (token->type == T_PAR_RIGHT) {
                    if (error_type = get_next_token(token)) {
                        return error_type;
                    }
                    if (token->type == T_BRACE_LEFT) {
                        if (error_type = get_next_token(token)) {
                            return error_type;
                        }
                        return st_list(token);
                    } else {
                        return SYNTAX_ERR;
                    }
                } else {
                    return SYNTAX_ERR;
                }
            } else {
                return SYNTAX_ERR;
            }
            break;
        case (T_KW_ELSE):
            if ( error_type = get_next_token(token) ) {
                return error_type;
            }
            if (token->type == T_BRACE_LEFT) {
                if ( error_type = get_next_token(token) ) {
                    return error_type;
                }
                error_type = st_list(token);
                return error_type;
            } else {
                return SYNTAX_ERR;
            }
            break;
        case (T_KW_IF):
            if ( error_type = get_next_token(token) ) {
                return error_type;
            }
            if (token->type == T_PAR_LEFT) {
                if ( error_type = get_next_token(token) ) {
                    return error_type;
                }
                error_type = expression(token);
                if (error_type != NO_ERR) {
                    return error_type;
                }
                if ( token->type == T_PAR_RIGHT ) {
                    if ( error_type = get_next_token(token) ) {
                        return error_type;
                    }
                    if ( token->type == T_BRACE_LEFT) {
                        if ( error_type = get_next_token(token) ) {
                            return error_type;
                        }
                        return st_list(token);
                    } else {
                        return SYNTAX_ERR;
                    }
                } else {
                    return SYNTAX_ERR;
                }
            } else {
                return SYNTAX_ERR;
            }
            break;
        default:
            return SYNTAX_ERR;
    }
}

int st_list(token_t * token){
    printf("i am in st_list\n");
    switch (token->type) {
        case (T_KW_RETURN):
        case (T_VAR_ID):
        case (T_FUN_ID):
            error_type = state(token);
            if (error_type != NO_ERR) {
                return error_type;
            }
            if (token->type == T_SEMICOLON) {
                if (error_type = get_next_token(token)) {
                    return error_type;
                }
                return st_list(token);
            } else {
                return SYNTAX_ERR;
            }
            break;
        case (T_KW_FUNCTION):
        case (T_KW_WHILE):
        case (T_KW_ELSE):
        case (T_KW_IF):
            error_type = state(token);
            if (error_type != NO_ERR) {
                return error_type;
            }
            if (token->type == T_BRACE_RIGHT) {
                if (error_type = get_next_token(token)) {
                    return error_type;
                }
            } else {
                return SYNTAX_ERR;
            }
            return st_list(token);
            break;
        case (T_END_SYMBOL):
            return NO_ERR;
            break;
        case (T_EOF):
            
            return NO_ERR;
            break;
        default:
            return SYNTAX_ERR;
    }
}

int prog(token_t * token){
    if(token->type == T_PROLOG){  // if token is <?php
        if (error_type = get_next_token(token)) {
            return error_type;
        }
        error_type = st_list(token);
        return error_type;
    }
    else {
        return SYNTAX_ERR;
    }
}

int main(){
    token_t  token;
    string s;
	if (str_init(&s)) {
		token.data.string_c = &s;
	}
    set_source(stdin);
    if ((error_type = get_next_token(&token)) == 0) {
        error_type = prog(&token);
    }
    printf("%d\n",error_type);
    return error_type;
}


