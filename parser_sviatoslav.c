#include "parser.h"

int error_type;
symtable_stack_t symt_stack;
string fun_name;
string fun_list;
int param_counter;



data_type convert_from_arg_to_d_type(char a){
    if (a == 'i') {
        return D_INT;
    } else if (a == 'f') {
        return D_FLOAT;
    } else if ( a == 's' ) {
        return D_STRING;
    } else if ( a == 't') {
        return D_TERM;
    }
    return D_UNDEFINED;
}

/**
 * @brief converts exp_type to data_type
 * 
 * @param type 
 * @return data_type 
 */
data_type convert_exp_to_d_type(exp_type type) {
    switch ( type ) {
    case ET_FLOAT:
        return D_FLOAT;
    case ET_INT:
        return D_INT;
    case ET_STRING:
        return D_STRING;
    default:
        return -1;
    }
}

/**
 * @brief converts data_type to exp_type
 * 
 * @param type 
 * @return exp_type 
 */
exp_type convert_to_exp(data_type type) {
    switch ( type ) {
    case D_FLOAT:
        return ET_FLOAT;
    case D_INT:
        return ET_INT;
    case D_STRING:
        return ET_STRING;
    default:
        return -1;
    }
}

/**
 * @brief converts token type to data_type
 * 
 * @param token pointer to token
 * @return data_type 
 */
data_type convert_to_d_type(token_t* token) {
    switch (token->type) {
        case (T_KW_FLOAT):
        case (T_DEC_VAL):
            return D_FLOAT;
        case (T_KW_INT):
        case (T_INT_VAL):
            return D_INT;
        case (T_STRING_VAL):
        case (T_KW_STRING):
            return D_STRING;
        case (T_KW_VOID):
            return D_VOID;
        case (T_VAR_ID):
            return symtable_search(symt_stack.active->symt, token->data.string_c->str)->type;
        default:
            return -1; // error
    }
}

/**
 * @brief converts token type to type from symtable (char)
 * 
 * @param token pointer to token
 * @return char 
 */
char convert_to_char(token_t* token) {
    switch (token->type) {
        case (T_KW_FLOAT):
            return 'f';
        case (T_KW_INT):
            return 'i';
        case (T_KW_STRING):
            return 's';
        default:
            return ' '; // error
    }
}

int kostyluka (token_t * token) {
    while(token->type != T_KW_FUNCTION && token->type != T_EOF && token->type != T_END_SYMBOL) {
        if (( error_type = get_next_token(token) )) {
                return error_type;
        }
    }
    if(token->type == T_EOF || token->type == T_END_SYMBOL){
        str_clear(&fun_name);
        return NO_ERR;
    }
    if (( error_type = get_next_token(token) )) {
        return error_type;
    }
    printf("type:   %d\n", token->type);
    if (token->type == T_FUN_ID) {
        symtable_stack_push(&symt_stack);
        htab_data_t* item = symtable_insert(symt_stack.top->symt, token->data.string_c->str);
        str_copy_string(&fun_name,token->data.string_c);
        item->is_defined = false;
        if (( error_type = get_next_token(token) )) {
            return error_type;
        }
        if (token->type == T_PAR_LEFT)
        {
            if (( error_type = get_next_token(token) )) {
                return error_type;
            }
            error_type = f_plist_kostylga(token);
            if(error_type)
                return error_type;
        
            if(token->type == T_COLON) {
                if (( error_type = get_next_token(token) )) {
                    return error_type;
                }
                if ( token->type == T_KW_FLOAT || token->type == T_KW_INT || token->type == T_KW_STRING || token->type == T_KW_VOID ) {
                    data_type d_tmp = convert_to_d_type(token);
                    if(!(symtable_add_type(symtable_search(symt_stack.top->symt, fun_name.str), d_tmp))){
                        return ERROR_INTERNAL; 
                    }
                    // printf("ebanina %d\n", token->type);
                    return kostyluka(token);
                }
                else {
                    printf("1\n");
                    return SYNTAX_ERR;
                }
            } else {
                printf("22\n");
                return SYNTAX_ERR;
            }
        } else {
            printf("3\n");
            return SYNTAX_ERR;
        }
    } else {
        printf("4\n");
        return SYNTAX_ERR;
    }
    return SEM_ERR_OTHER;
}

int f_plist_kostylga( token_t * token ) {
    printf("%d\n",token->type);
    if ( token->type == T_COMMA ) {
        if (( error_type = get_next_token(token) )) {
            return error_type;
        }
        error_type = f_param_kostylga(token);
        if (error_type) {
            return error_type;
        }
        return f_plist_kostylga(token);
    } else if ( token->type == T_KW_FLOAT || token->type == T_KW_INT || token->type == T_KW_STRING) {
        printf("p_list int\n");
        error_type = f_param_kostylga(token);
        if (error_type) {
            return error_type;
        }
        return f_plist_kostylga(token);
    } else if ( token->type == T_PAR_RIGHT ) {
        htab_data_t* tmp;
        if((tmp = symtable_search(symt_stack.top->symt,fun_name.str))){
            tmp->argumets_amount= param_counter;
        } else {
            return ERROR_INTERNAL;
        }
        param_counter = 0;
        if (( error_type = get_next_token(token) )) {
            return error_type;
        }
        return NO_ERR;
    } else {
        printf("hihi\n");
        return SYNTAX_ERR;
    }
}

int f_param_kostylga ( token_t * token ) {
    if ( token->type == T_KW_FLOAT || token->type == T_KW_INT || token->type == T_KW_STRING ) {
        data_type tmp = convert_to_d_type(token);
        if (!symtable_add_arguments(symtable_search(symt_stack.top->symt, fun_name.str), tmp, false)) {
            return ERROR_INTERNAL;
        }
        if ( ( error_type = get_next_token(token) ) ) {
            return error_type;
        }
        if (token->type == T_VAR_ID) {
            htab_data_t* item = symtable_insert(symt_stack.active->symt, token->data.string_c->str);
            symtable_add_type(item, tmp);
            param_counter++;
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



int f_state ( token_t * token ) {
    printf("i am in f_state\n");
    bool f_flag = false;
    htab_data_t* tmp;
    htab_data_t* item_tmp;
    exp_type final_type;
    set_type(&final_type);

    switch (token->type) {
        
        case (T_KW_RETURN):
            // set_symtable(symt_stack.active->symt);
            if ( ( error_type = get_next_token(token) ) ) {
                return error_type;
            }
            if ( token->type == T_FUN_ID ) {
                /*
                Semantic check :

                */
                if((item_tmp = symtable_search(symt_stack.top->symt, token->data.string_c->str))==NULL) {
                    return SEM_ERR_UNDEFINED_FUNCTION;
                } else {
                    if (fun_name.str[0] == '\0') {
                        return NO_ERR;
                    } else {
                        tmp = symtable_search(symt_stack.top->symt, fun_name.str);
                        if (tmp !=NULL)
                        {
                            if (item_tmp->type == tmp->type){
                                return NO_ERR;
                            } else {
                                return SEM_ERR_WRONG_PARAM;
                            }
                        } else {
                            return ERROR_INTERNAL;
                        }
                        
                    }
                }
            } else {
                int result = expression(token);
                if (result == NO_ERR) {
                    if( (item_tmp = (symtable_search(symt_stack.top->symt, fun_name.str))) != NULL)  {
                        if (!(item_tmp->type == convert_exp_to_d_type(final_type))) {
                            return SEM_ERR_WRONG_PARAM;
                        } else {
                            return result;
                        }
                    } else {
                        return SEM_ERR_UNDEFINED_FUNCTION;
                    }
                }
            }
        case (T_VAR_ID):
            
            //set_symtable(symt_stack.active->symt);
            if(fun_name.str[0]== '\0') {
                if( (tmp = symtable_search(symt_stack.top->symt, token->data.string_c->str) ) == NULL ) {
                // printf("### : %s\n", token->data.string_c->str);
                tmp = symtable_insert(symt_stack.top->symt, token->data.string_c->str);
                } else {
                f_flag = true;
                }
            } else {
                if( (tmp = symtable_search(symt_stack.active->symt, token->data.string_c->str) ) == NULL ) {
                // printf("### : %s\n", token->data.string_c->str);
                tmp = symtable_insert(symt_stack.active->symt, token->data.string_c->str);
                } else {
                    f_flag = true;
                }   
            }
            if (( error_type = get_next_token(token) )) {
                return error_type;
            }
            if (token->type == T_ASSIGN) {
                if (( error_type = get_next_token(token) )) {
                    return error_type;
                }
                if (token->type == T_FUN_ID) {
                     /*
                    Sematick check: 
                    If we found the defined function, we retype our variable to type, that function retruns
                    Else we create a temporary definition in table, and add that to list of undefined but used fucntions
                    in the end of analysis we will check, if it was defined late.
                    */
                    if((item_tmp = symtable_search(symt_stack.top->symt, token->data.string_c->str))==NULL) {
                        return SEM_ERR_UNDEFINED_FUNCTION;
                    }   else {
                        printf("that's okay, %d %d \n",tmp->type, item_tmp->type);
                        symtable_add_type(tmp, item_tmp->type);
                        return declare(token);
                    }
                    return SEM_ERR_OTHER;
                } else if (token->type == T_VAR_ID || token->type == T_INT_VAL || token->type == T_DEC_VAL || token->type == T_STRING_VAL) {
                    int result = expression(token);
                    if (result == NO_ERR) {
                        symtable_add_type(tmp, ( convert_exp_to_d_type (final_type) ));
                        // printf("############tmp : %d\n", tmp->type);
                        // generate_code("=,E_last,NULL,tmp"); псведокод
                    }
                    return result;
                } else {
                    return SYNTAX_ERR;
                }
            }
            else {
                if (!f_flag) {
                    symtable_delete(symt_stack.active->symt, tmp->id);
                    return SEM_ERR_UNDEFINED_VAR;
                }
                set_flag(true);
                set_id(tmp->id);
                // if (symtable_search(&symt, tmp->id) == NULL) {
                //     printf("NULL!!\n");
                // }
                return expression(token); // tut eben'
            }
            break;

        case (T_FUN_ID):
            //printf("%d\n%s\n",token->type,token->data.string_c->str);
            // if (( error_type = get_next_token(token) )) {
            //     return error_type;
            // }
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
                if ( ( error_type = get_next_token(token) ) ) {
                    return error_type;
                }
                error_type = expression(token);
                if (error_type != NO_ERR) {
                    return error_type;
                }
                if ( token->type == T_PAR_RIGHT ) {
                    if ( ( error_type = get_next_token(token) ) ) {
                        return error_type;
                    }
                    if ( token->type == T_BRACE_LEFT) {
                        if ( ( error_type = get_next_token(token) ) ) {
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

        // case (T_BRACE_RIGHT):
        //     return NO_ERR;

        default:
            return SYNTAX_ERR;
    }
}

int f_list ( token_t * token ) {
    printf("i am in f_list\n");
    switch (token->type) {
        case (T_INT_VAL):
        case (T_STRING_VAL):
        case (T_DEC_VAL):
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
    if ( token->type == T_STRING_VAL || token->type == T_DEC_VAL || token->type == T_INT_VAL || token->type == T_VAR_ID ) {
        char* last_fun = NULL;
        str_get_last_fun_name(&fun_list, &last_fun);
        // printf("last fun : %s\n", last_fun);
        htab_data_t* item = symtable_search(symt_stack.top->symt, last_fun);
        if (item == NULL) {
            return SEM_ERR_UNDEFINED_FUNCTION;
        }
        if (!(param_counter<=item->argumets_amount)) {
            printf("param counter, arguments_amount : %d , %d", param_counter,item->argumets_amount);
            printf("bombom\n");
            return SEM_ERR_WRONG_PARAM;
        }
        data_type data_tmp;
        if (token->type==T_VAR_ID) {   
            /*
            По-хорошему надо добавить проверочки в серчи
            */
           printf("%c ", fun_name.str[0]);
            if(fun_name.str[0]== '\0'){ 
                printf("bimbim\n");
                htab_data_t* tmp = symtable_search(symt_stack.top->symt,token->data.string_c->str);
                if (tmp == NULL)
                { 
                    data_tmp = (symtable_search(symt_stack.active->symt,token->data.string_c->str)->type);    
                }
                else {
                    data_tmp = tmp->type;
                }
                
            //    data_tmp = (symtable_search(symt_stack.top->symt,token->data.string_c->str))->type;    
            } else {
                printf("brombrom\n");
                data_tmp = (symtable_search(symt_stack.active->symt,token->data.string_c->str)->type);    
            }
        } else {
            printf("%d\n", token->type);
            data_tmp = convert_to_d_type(token);
            printf("%d\n", data_tmp);
        }
        data_type arg_type = convert_from_arg_to_d_type(item->arguments->str[param_counter]);
        if ( arg_type != D_TERM) {
            if(arg_type != data_tmp ){
                printf("i am here\n");
                printf("%d\n", arg_type);
                printf("%c , %d\n",item->arguments->str[param_counter], data_tmp);
                return SEM_ERR_WRONG_PARAM;
            } else {
                param_counter++;
            }
        }
        if ( ( error_type = get_next_token(token) ) ) {
            return error_type;
        }
        if (last_fun != NULL) {
                free(last_fun);
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
    } else if ( token->type == T_DEC_VAL || token->type == T_INT_VAL || token->type == T_STRING_VAL || token->type == T_VAR_ID) {
        error_type = f_param_declare(token);
        if (error_type) {
            return error_type;
        }
        return f_plist_declare(token);
    } else if ( token->type == T_PAR_RIGHT ) {
        char * tmp;
        str_get_last_fun_name(&fun_list,&tmp);
        if (!(symtable_search(symt_stack.top->symt,tmp)->infinite))
        {  
        if(param_counter != (symtable_search(symt_stack.top->symt,tmp))->argumets_amount){
            printf("bambam\n");
            return SEM_ERR_WRONG_PARAM;
        }
        }
        param_counter = 0;
        if ( tmp != NULL) {
            free(tmp);
        }
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
        data_type tmp = convert_to_d_type(token);
        if (!symtable_add_arguments(symtable_search(symt_stack.top->symt, fun_name.str), tmp, false)) {
            return ERROR_INTERNAL;
        }
        // printf("\targ : %s\n", symtable_search(symt_stack.top->symt, fun_name)->arguments->str);
        if ( ( error_type = get_next_token(token) ) ) {
            return error_type;
        }
        if (token->type == T_VAR_ID) {
            htab_data_t* item = symtable_insert(symt_stack.active->symt, token->data.string_c->str);
            symtable_add_type(item, tmp);
            param_counter++;
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
        htab_data_t* tmp;
        if((tmp = symtable_search(symt_stack.top->symt,fun_name.str))){
            tmp->argumets_amount= param_counter;
        } else {
            return ERROR_INTERNAL;
        }
        param_counter = 0;
        if (( error_type = get_next_token(token) )) {
            return error_type;
        }
        return NO_ERR;
    } else {
        // printf("hihi\n");
        return SYNTAX_ERR;
    }
}

int declare(token_t * token) {
    printf("i am in declare\n");
    char* tmp = token->data.string_c->str;
    if (symtable_search(symt_stack.top->symt, tmp) == NULL) {
        return SEM_ERR_UNDEFINED_FUNCTION;
    } else {
        str_add_fun_name(&fun_list,tmp);
    }
    if (( error_type = get_next_token(token) )) { // here we skip function fun_id token
        return error_type;
    }
    if (token->type == T_PAR_LEFT) {
        
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
    if (token->type == T_PAR_LEFT) {
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
    exp_type final_type;
    set_type(&final_type);
    htab_data_t* item_tmp;

    switch (token->type) {
        case (T_INT_VAL):
        case (T_STRING_VAL):
        case (T_DEC_VAL):
            return expression(token);
        case (T_KW_RETURN):
            //generate_code("return", NULL, NULL, );
            if (( error_type = get_next_token(token) )) {
                return error_type;
            }
            if ( token->type == T_FUN_ID ) {
                if ((item_tmp = symtable_search(symt_stack.top->symt,token->data.string_c->str))!=NULL) {
                    return declare(token);    
                } else {
                    return SEM_ERR_UNDEFINED_FUNCTION;
                }
            } else {
            /*
            We need to process empty expressions
            */
            return expression(token);
            }
            break;
        case (T_VAR_ID):
            if( (tmp = symtable_search(symt_stack.top->symt, token->data.string_c->str) ) == NULL ) {
                // printf("### : %s\n", token->data.string_c->str);
                tmp = symtable_insert(symt_stack.top->symt, token->data.string_c->str);
                // printf("type of ininitialized variable: %d \n",tmp->type);
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
                    /*
                    Sematick check: 
                    */
                    if((item_tmp = symtable_search(symt_stack.top->symt, token->data.string_c->str))==NULL) {
                        return SEM_ERR_UNDEFINED_FUNCTION;
                    }   else {
                        symtable_add_type(tmp, item_tmp->type);
                        return declare(token);
                    }
                } else if (token->type == T_VAR_ID || token->type == T_INT_VAL || token->type == T_DEC_VAL || token->type == T_STRING_VAL) {
                    //set_symtable(symt_stack.top->symt);
                    int result = expression(token);
                    if (result == NO_ERR) {
                        symtable_add_type(tmp, ( convert_exp_to_d_type (final_type) )); 
                        // printf("############tmp : %d\n", tmp->type);
                        // generate_code("=,E_last,NULL,tmp"); псведокод
                    }
                    return result;
                } else {
                    return SYNTAX_ERR;
                }
            }
            else {
                 /*    
                We have an expression without assign, so we set_flag, thats displays, that we are not in assign
                Same way we set id, that we need to process in expression function 
                Before that we need to delete a item in table, if we created it before, so we checking the f_flag
                */
                if (!f_flag) {
                    symtable_delete(symt_stack.top->symt, tmp->id);
                    return SEM_ERR_UNDEFINED_VAR;
                }
                set_flag(true);
                set_id(tmp->id);
                // if (symtable_search(&symt, tmp->id) == NULL) {
                //     printf("NULL!!\n");
                // }
                return expression(token); 
            }
            break;

        case (T_FUN_ID):
            if ((item_tmp = symtable_search(symt_stack.top->symt,token->data.string_c->str))!=NULL) {
                return declare(token);    
            } else {
                return SEM_ERR_UNDEFINED_FUNCTION;
            }
        case (T_KW_FUNCTION):
            printf("i am in function\n");
            if (( error_type = get_next_token(token) )) {
                return error_type;
            }
            if (token->type == T_FUN_ID) {
                symtable_stack_push(&symt_stack);
                htab_data_t* item = symtable_search(symt_stack.top->symt, token->data.string_c->str);
                if (item == NULL) {
                    item = symtable_insert(symt_stack.top->symt, token->data.string_c->str);
                    item->is_defined = true;
                } else {
                    if (item->is_defined) {
                        return SEM_ERR_UNDEFINED_FUNCTION;
                    } else {
                        item->is_defined = true;
                    }                    
                } 
                str_copy_string(&fun_name,token->data.string_c);
                //printf("dvatanka %s\n",fun_name.str);
                item->is_defined = true;
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
                    if ( token->type == T_KW_FLOAT || token->type == T_KW_INT || token->type == T_KW_STRING || token->type == T_KW_VOID ) {
                        data_type d_tmp = convert_to_d_type(token);
                        if(symtable_add_type(symtable_search(symt_stack.top->symt, fun_name.str), d_tmp))
                            printf("that's okay, %d %d \n",d_tmp, symtable_search(symt_stack.top->symt, fun_name.str)->type);
                        else
                            printf("it is really bad\n");
                        // printf("\t\t\t\ttype : %d\n", symtable_search(symt_stack.top->symt, fun_name)->type);
                        if (( error_type = get_next_token(token) )) {
                            return error_type;
                        }
                        if (token->type == T_BRACE_LEFT) {
                            if (( error_type = get_next_token(token) )) {
                                return error_type;
                            }
                            set_symtable(symt_stack.active->symt);
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
        case (T_KW_WHILE):
            set_symtable(symt_stack.top->symt);
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
                    // printf("tt : %d\n", token->type);
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
            set_symtable(symt_stack.top->symt);
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
            set_symtable(symt_stack.top->symt);
            if ( ( error_type = get_next_token(token) ) ) {
                return error_type;
            }
            if (token->type == T_PAR_LEFT) {
                if ( ( error_type = get_next_token(token) ) ) {
                    return error_type;
                }
                // set_par(true);
                error_type = expression(token);
                if (error_type != NO_ERR) {
                    return error_type;
                }
                if ( token->type == T_PAR_RIGHT ) {
                    if ( ( error_type = get_next_token(token) ) ) {
                        return error_type;
                    }
                    if ( token->type == T_BRACE_LEFT) {
                        if ( ( error_type = get_next_token(token) ) ) {
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
        default:
            return SYNTAX_ERR;
    }
}

int st_list(token_t * token) {
    printf("i am in st_list\n");
    // printf("tt : %d\n", token->type);
    switch (token->type) {
        case (T_INT_VAL):
        case (T_STRING_VAL):
        case (T_DEC_VAL):
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
            error_type = state(token);
            if (error_type != NO_ERR) {
                return error_type;
            }
            if (token->type == T_BRACE_RIGHT) {
                if (fun_name.str[0] != '\0') {
                    str_clear(&fun_name);
                    symtable_stack_pop(&symt_stack);
                }
                if (( error_type = get_next_token(token) )) {
                    return error_type;
                }
            } else {
                return SYNTAX_ERR;
            }
            return st_list(token);
            break;
            
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

int main() {
    token_t token;
    string s;
    str_init(&fun_list);
    str_init(&fun_name);
    // str_add_fun_name(&fun_list, "aboba");
    // str_add_fun_name(&fun_list, "gogoga");
    // str_add_fun_name(&fun_list, "lologa");
    // printf("fun_list : %s\n", fun_list.str);
    // char* found = NULL;
    // str_get_last_fun_name(&fun_list, &found);
    // printf("found : %s\n", found);
    // printf("1 : %d\t2 : %d\t3 : %d\t4 : %d\n", str_find_fun_name(&fun_list, "aboba"), str_find_fun_name(&fun_list, "gogoga"), str_find_fun_name(&fun_list, "lologa"), str_find_fun_name(&fun_list, "abafsda"));
    symtable_stack_init(&symt_stack);
    param_counter = 0;
    // symtable_stack_t st_stack;
    // symtable symt2;
    // symtable_stack_init(&st_stack);
    // if (!symtable_init(&symt)) {
    //     return ERROR_INTERNAL;
    // }
    symtable_stack_push(&symt_stack);
    htab_data_t* tmpData1 = symtable_insert(symt_stack.top->symt, "reads");
    symtable_add_type(tmpData1, D_STRING);

    htab_data_t* tmpData2 = symtable_insert(symt_stack.top->symt, "readi");
    symtable_add_type(tmpData2, D_INT);

    htab_data_t* tmpData3 = symtable_insert(symt_stack.top->symt, "readf");
    symtable_add_type(tmpData3, D_FLOAT);

    htab_data_t* tmpData4 = symtable_insert(symt_stack.top->symt, "write");
    symtable_add_type(tmpData4, D_VOID);
    symtable_add_arguments(tmpData4, D_TERM, true);

    htab_data_t* tmpData5 = symtable_insert(symt_stack.top->symt, "floatval");
    symtable_add_type(tmpData5, D_FLOAT);
    symtable_add_arguments(tmpData5, D_TERM, false);

    htab_data_t* tmpData6 = symtable_insert(symt_stack.top->symt, "intval");
    symtable_add_type(tmpData6, D_INT);
    symtable_add_arguments(tmpData6, D_TERM, false);

    htab_data_t* tmpData7 = symtable_insert(symt_stack.top->symt, "strval");
    symtable_add_type(tmpData7, D_STRING);
    symtable_add_arguments(tmpData7, D_TERM, false);

    htab_data_t* tmpData8 = symtable_insert(symt_stack.top->symt, "strlen");
    symtable_add_type(tmpData8, D_INT);
    symtable_add_arguments(tmpData8, D_STRING, false);

    htab_data_t* tmpData9 = symtable_insert(symt_stack.top->symt, "substring");
    symtable_add_type(tmpData9, D_STRING);
    symtable_add_arguments(tmpData9, D_STRING, false);
    symtable_add_arguments(tmpData9, D_INT, false);
    symtable_add_arguments(tmpData9, D_INT, false);

    htab_data_t* tmpData10 = symtable_insert(symt_stack.top->symt, "ord");
    symtable_add_type(tmpData10, D_INT);
    symtable_add_arguments(tmpData10, D_STRING, false);

    htab_data_t* tmpData11 = symtable_insert(symt_stack.top->symt, "chr");
    symtable_add_type(tmpData11, D_STRING);
    symtable_add_arguments(tmpData11, D_INT, false);
    // if (!symtable_init(&symt2)) {
    //     return ERROR_INTERNAL;
    // }
    set_symtable(symt_stack.top->symt);
    set_flag(false);
    // set_par(false);
    if (!str_init(&s)) {
        return 1;
    }
    set_source(stdin);
    set_src_str(&s);
    // symtable_insert(&symt, "aboba");
    // symtable_insert(&symt2, "hubabon");
    // symtable_stack_push(&st_stack, &symt);
    // symtable_stack_push(&st_stack, &symt2);
    // printf("symt : %s\tsymt2 : %s\n", symtable_search(st_stack.top->symt, "aboba")->id, symtable_search(st_stack.top->next->symt, "hubabon")->id);
    // symtable_stack_pop(&st_stack);
    if ((error_type = get_next_token(&token)) == 0) {
        error_type = kostyluka(&token);
    }
    printf("ja debil %d\n",error_type);
    if (error_type) {
        return error_type;
    }
    if (fseek(stdin, 0L, SEEK_SET)) {
        perror("stdin");
        exit(EXIT_FAILURE);
    }
    set_source(stdin);
    if ((error_type = get_next_token(&token)) == 0) {
        error_type = prog(&token);
    }
    printf("%d\n",error_type);
    // symtable_free(symt_stack.top->symt);
    // symtable_free(symt_stack.active->symt);
    symtable_stack_free(&symt_stack);
    return error_type;
}