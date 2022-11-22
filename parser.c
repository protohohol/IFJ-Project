#include "parser.h"
int error_type = 0;



// int if_build_f (token_t * token) {
//     for ( int i = 0; i<8; i++ ) {
//         if(( str_cmp_const_str (token->data->string_c,built_in_arr[i]) )) {
//                 return i+1;
//             }
//         }
//     return 0;
// }
// int dec_list (token_t * token) {
//         switch ( if_build_f(token) ) {
//             case F_USER:
//                 if (error_type = get_next_token(token)) {
//                     return error_type;
//                 }
//                 return declare(token);
//                 break;
//             case F_SREAD:
//                 if (error_type = get_next_token(token)) {
//                     return error_type;
//                 }
//                 break;
//             case F_IREAD:
//                 /* code */
//                 break;
//             case F_FREAD:
//                 /* code */
//                 break;
//             case F_WRITE:
//                 /* code */
//                 break;
//             case F_STRLN:
//                 /* code */
//                 break;
//             case F_SUBSTR:
//                 /* code */
//                 break;
//             case F_ORD:
//                 /* code */
//                 break;
//             case F_CHR:
//                 break;
//             }
// }

int f_state ( token_t * token ) {
    switch (token->type) {
        case (T_KW_RETURN):
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            return expression(token);
            break;
        case (T_VAR_ID):
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            if(token->type == T_ASSIGN){
                if (error_type = get_next_token(token)) {
                    return error_type;
                }
                return expression(token);
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

int f_param ( token_t * token ) {
    if ( token->type == T_KW_FLOAT || token->type == T_KW_INT || token->type == T_KW_STRING ) {
        if ( error_type = get_next_token(token) ) {
            return error_type;
        }
        return NO_ERR;
    } else if ( token->type == T_VAR_ID ) {
        if ( error_type = get_next_token(token) ) {
            return error_type;
        }
        return NO_ERR;
    } else {
        return SYNTAX_ERR;
    }
}

int f_plist( token_t * token ) {
    if ( token->type == T_DOT ) {
        if (error_type = get_next_token(token)) {
            return error_type;
        }
        error_type = f_param(token);
        if (error_type) {
            return error_type;
        }
        return f_plist(token);
    } else if ( token->type == T_KW_FLOAT || token->type == T_KW_INT || token->type == T_KW_STRING || token->type == T_VAR_ID) {
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
            error_type = f_plist(token);
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
    switch (token->type) {
        case (T_KW_RETURN):
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            return expression(token);
            break;
        // case (T_VAR_ID):
        //     if (error_type = get_next_token(token)) {
        //         error(error_type);
        //     }
        //     if(token->type == T_ASSIGN){
        //         if (error_type = get_next_token(token)) {
        //         error(error_type);
        //         }
        //         expression(token);
        //     }
        //     else
        //         expression(token);
        //     break;
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
    if(token->type == T_START_SYMBOL){  // if token is <?php
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
    token_t * token;
    if ((error_type = get_next_token(token)) == 0) {
        error_type = prog(token);
    }
    return error_type;
}


