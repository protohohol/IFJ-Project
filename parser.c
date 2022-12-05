#include "parser.h"

int error_type;
symtable symt;

data_type convert_to_symtable_datatype(exp_type type) {
    switch ( type )
    {
    case ET_FLOAT:
        return D_FLOAT;
    case ET_INT:
        return D_INT;
    case ET_STRING:
        return D_STRING;
    default:
        return D_VOID;
    }
    return D_VOID;
}
 
int f_state ( token_t * token ) {
    printf("i am in f_state\n");
    switch (token->type) {
        case (T_KW_RETURN):
            if ( ( error_type = get_next_token(token) ) ) {
                return error_type;
            }
            if ( token->type == T_FUN_ID ) {
                return declare(token);
            } else {
            return expression(token);
            }
            break;
        case (T_VAR_ID):
            if ( ( error_type = get_next_token(token) ) ) {
                return error_type;
            }
            if( token->type == T_ASSIGN ){
                if (( error_type = get_next_token(token) )) {
                    return error_type;
                }
                if ( token->type == T_FUN_ID ) {
                    if ( ( error_type = get_next_token(token) ) ) {
                        return error_type;
                    }
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
            //printf("%d\n%s\n",token->type,token->data.string_c->str);
            if (( error_type = get_next_token(token) )) {
                return error_type;
            }
            return declare(token);
            break;
        case (T_KW_WHILE):
            printf("I am in WHILE\n");
            if (( error_type = get_next_token(token) )) {
                return error_type;
            }
            if (token->type == T_PAR_LEFT) {
                if (( error_type = get_next_token(token) )) {
                    return error_type;
                }
                error_type = expression(token);
                if (error_type != NO_ERR) {
                    return error_type;
                }
                if (token->type == T_PAR_RIGHT) {
                    if (( error_type = get_next_token(token) )) {
                        return error_type;
                    }
                    if (token->type == T_BRACE_LEFT) {
                        if (( error_type = get_next_token(token) )) {
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
            printf("i am in else \n");
            if ( ( error_type = get_next_token(token) ) ) {
                return error_type;
            }
            if (token->type == T_BRACE_LEFT) {
                if ( ( error_type = get_next_token(token) ) ) {
                    return error_type;
                }
                error_type = f_list(token);
                return error_type;
            } else {
                return SYNTAX_ERR;
            }
            break;
        case (T_KW_IF):
            printf("i am in if \n");
            if ( ( error_type = get_next_token(token) ) ) {
                return error_type;
            }
            if (token->type == T_PAR_LEFT) {
                error_type = expression(token);
                if (error_type != NO_ERR) {
                    return error_type;
                }
                //if ( token->type == T_PAR_RIGHT ) {
                    // if ( ( error_type = get_next_token(token) ) ) {
                    //     return error_type;
                    // }
                    if ( token->type == T_BRACE_LEFT) {
                        if ( ( error_type = get_next_token(token) ) ) {
                            return error_type;
                        }
                        return f_list(token);
                    } else {
                        return SYNTAX_ERR;
                    }
                //} else {
                //    return SYNTAX_ERR;
                //}
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
    printf("i am in f_list\n");
    switch (token->type) {
        case (T_KW_RETURN):
        case (T_VAR_ID):
        case (T_FUN_ID):
            error_type = f_state(token);
            if (error_type != NO_ERR) {
                return error_type;
            }
            if (token->type == T_SEMICOLON) {
                if (( error_type = get_next_token(token) )) {
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
                if (( error_type = get_next_token(token) )) {
                    return error_type;
                }
            } else {
                return SYNTAX_ERR;
            }
            return f_list(token);
            
            break;
        case (T_BRACE_RIGHT):
            printf("i am out }\n");
            return NO_ERR;
        default:
            return SYNTAX_ERR;
    }
}

int f_param_declare ( token_t * token ) {
    if ( token->type == T_STRING_VAL || token->type == T_DEC_VAL || token->type == T_INT_VAL || T_VAR_ID ) {
        if ( ( error_type = get_next_token(token) ) ) {
            return error_type;
        }
        return NO_ERR;
    } else {
        return SYNTAX_ERR;
    }
}

int f_plist_declare( token_t * token ) {
    if ( token->type == T_COMMA ) {
        if (( error_type = get_next_token(token) )) {
            return error_type;
        }
        error_type = f_param_declare(token);
        if (error_type) {
            return error_type;
        }
        return f_plist_declare(token);
    } else if ( token->type == T_DEC_VAL || token->type == T_INT_VAL || token->type == T_STRING_VAL || token->type == T_VAR_ID ) {
        error_type = f_param_declare(token);
        if (error_type) {
            return error_type;
        }
        return f_plist_declare(token);
    } else if ( token->type == T_PAR_RIGHT ) {
        if (( error_type = get_next_token(token) )) {
            return error_type;
        }
        return NO_ERR;
    } else {
        return SYNTAX_ERR;
    }
}

int f_param ( token_t * token ) {
    if ( token->type == T_KW_FLOAT || token->type == T_KW_INT || token->type == T_KW_STRING ) {
        if ( ( error_type = get_next_token(token) ) ) {
            return error_type;
        }
        if (token->type == T_VAR_ID) {
            if (( error_type = get_next_token(token) )) {
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
    printf("%d\n",token->type);
    if ( token->type == T_COMMA ) {
        if (( error_type = get_next_token(token) )) {
            return error_type;
        }
        error_type = f_param(token);
        if (error_type) {
            return error_type;
        }
        return f_plist(token);
    } else if ( token->type == T_KW_FLOAT || token->type == T_KW_INT || token->type == T_KW_STRING) {
        printf("p_list int\n");
        error_type = f_param(token);
        if (error_type) {
            return error_type;
        }
        return f_plist(token);
    } else if ( token->type == T_PAR_RIGHT ) {
        if (( error_type = get_next_token(token) )) {
            return error_type;
        }
        return NO_ERR;
    } else {
        printf("hihi\n");
        return SYNTAX_ERR;
    }
}

int declare(token_t * token) {
    printf("i am in declare\n");
    if(token->type == T_PAR_LEFT) {
            if (( error_type = get_next_token(token) )) {
                return error_type;
            }
            error_type = f_plist_declare(token);
            return error_type;
    } else {
        return SYNTAX_ERR;
    }
}

int define (token_t * token) {
    printf("i am in define\n");
    if(token->type == T_PAR_LEFT) {
            if (( error_type = get_next_token(token) )) {
                return error_type;
            }
            error_type = f_plist(token);
            return error_type;
    } else { 
        return SYNTAX_ERR;
    }
}

int state(token_t * token) {
    printf("i am in state\n");
    bool f_flag = false;
    htab_data_t* tmp;
    exp_type final_type; // НАДО БЛЯТЬ ДОПОЛНИТЬ СУКА 
    set_type(&final_type);
    switch (token->type) {
        // case (T_KW_RETURN):
        //     //generate_code("return", NULL, NULL, );
        //     if (( error_type = get_next_token(token) )) {
        //         return error_type;
        //     }
        //     if ( token->type == T_FUN_ID ) {
        //         return declare(token);
        //     } else {
        //     return expression(token);
        //     }
        //     break;
        case (T_VAR_ID):
            if( (tmp = symtable_search(&symt, token->data.string_c->str) ) == NULL ) {
                // printf("### : %s\n", token->data.string_c->str);
                tmp = symtable_insert(&symt, token->data.string_c->str);
            } else {
                f_flag = true;
            }
            if (( error_type = get_next_token(token) )) {
                return error_type;
            }
            if (token->type == T_ASSIGN) {
                if (( error_type = get_next_token(token) )) {
                    return error_type;
                }
                if (token->type == T_FUN_ID) {
                    return state(token);
                } else if (token->type == T_VAR_ID || token->type == T_INT_VAL || token->type == T_DEC_VAL || token->type == T_STRING_VAL) {
                    int result = expression(token);
                    if (result == NO_ERR) {
                        symtable_add_type(tmp, ( convert_to_symtable_datatype (final_type) ));
                        printf("tmp : %d\n", tmp->type);
                        // generate_code("=,E_last,NULL,tmp"); псведокод
                    }
                    return result;
                } else {
                    return SYNTAX_ERR;
                }
            }
            else {
                if (!f_flag) {
                    symtable_delete(&symt, tmp->id);
                    return SEM_ERR_UNDEFINED_VAR;
                }
                set_flag(true);
                set_id(tmp->id);
                return expression(token);//tut eben'
            }
            break;
        case (T_FUN_ID):
            if (( error_type = get_next_token(token) )) {
                return error_type;
            }
            return declare(token);
            break;
        case (T_KW_FUNCTION):
            if (( error_type = get_next_token(token) )) {
                return error_type;
            }
            if (token->type == T_FUN_ID){
                if (( error_type = get_next_token(token) )) {
                    return error_type;
                }
                error_type = define(token);
                if (error_type) {
                    return error_type;
                }
                if(token->type == T_COLON) {
                    if (( error_type = get_next_token(token) )) {
                        return error_type;
                    }
                    if( token->type == T_KW_FLOAT || token->type == T_KW_INT || token->type == T_KW_STRING || token->type == T_KW_VOID ) {
                        if (( error_type = get_next_token(token) )) {
                            return error_type;
                        return error_type;
                        }
                        if(token->type == T_BRACE_LEFT){
                            if (( error_type = get_next_token(token) )) {
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
            if (( error_type = get_next_token(token) )) {
                return error_type;
            }
            if (token->type == T_PAR_LEFT) {
                if (( error_type = get_next_token(token) )) {
                    return error_type;
                }
                error_type = expression(token);
                if (error_type != NO_ERR) {
                    return error_type;
                }
                if (token->type == T_PAR_RIGHT) {
                    if (( error_type = get_next_token(token) )) {
                        return error_type;
                    }
                    if (token->type == T_BRACE_LEFT) {
                        if (( error_type = get_next_token(token) )) {
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
            printf("i am in else\n");
            if ( ( error_type = get_next_token(token) ) ) {
                return error_type;
            }
            if (token->type == T_BRACE_LEFT) {
                if ( ( error_type = get_next_token(token) ) ) {
                    return error_type;
                }
                error_type = f_list(token);
                return error_type;
            } else {
                return SYNTAX_ERR;
            }
            break;
        case (T_KW_IF):
            printf("i am in if \n");
            if ( ( error_type = get_next_token(token) ) ) {
                return error_type;
            }
            if (token->type == T_PAR_LEFT) {
                error_type = expression(token);
                if (error_type != NO_ERR) {
                    return error_type;
                }
                // if ( token->type == T_PAR_RIGHT ) {
                //     if ( ( error_type = get_next_token(token) ) ) {
                //         return error_type;
                //     }
                    if ( token->type == T_BRACE_LEFT) {
                        if ( ( error_type = get_next_token(token) ) ) {
                            return error_type;
                        }
                        return f_list(token);
                    } else {
                        return SYNTAX_ERR;
                    }
                // } else {
                //     printf("i am here\n");
                //     return SYNTAX_ERR;
                // }
            } else {
                return SYNTAX_ERR;
            }
            break;
        default:
            return SYNTAX_ERR;
    }
}

int st_list(token_t * token) {
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
                if (( error_type = get_next_token(token) )) {
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
                if (( error_type = get_next_token(token) )) {
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
    if(token->type == T_PROLOG){  // if token is <?php white symbol declare(strictypes=1);
        if (( error_type = get_next_token(token) )) {
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
    symtable_init(&symt);
    set_symtable(symt);
    set_flag(false);
    if (!str_init(&s)) {
        return 1;
    }
    set_source(stdin);
    set_src_str(&s);
    if ((error_type = get_next_token(&token)) == 0) {
        error_type = prog(&token);
    }
    printf("%d\n",error_type);
    return error_type;
}