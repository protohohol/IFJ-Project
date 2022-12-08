#include "parser.h"

int error_type;
symtable_stack_t symt_stack;
string fun_name;
string fun_list;
int param_counter;
DLList inst_list;
taCode data_glob;


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
    case ET_NULL:
        return D_VOID;
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
            if (fun_name.str[0] == '\0') {
                return symtable_search(symt_stack.top->symt, token->data.string_c->str)->type;
            } else {
                return symtable_search(symt_stack.active->symt, token->data.string_c->str)->type;
            }
        default:
            return 550; // error
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
                    return kostyluka(token);
                }
                else {
                    return SYNTAX_ERR;
                }
            } else {
                return SYNTAX_ERR;
            }
        } else {
            return SYNTAX_ERR;
        }
    } else {
        return SYNTAX_ERR;
    }
    return SEM_ERR_OTHER;
}

int f_plist_kostylga( token_t * token ) {
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
    bool f_flag = false;
    htab_data_t* tmp;
    htab_data_t* item_tmp;
    exp_type final_type;
    set_type(&final_type);

    switch (token->type) {
        case (T_INT_VAL):
        case (T_STRING_VAL):
        case (T_DEC_VAL):
        case (T_PAR_LEFT):
            return expression(token);
        
        case (T_KW_RETURN):
            if ( ( error_type = get_next_token(token) ) ) {
                return error_type;
            }
            if ( token->type == T_FUN_ID ) {
                /*
                Semantic check :

                */
                if ((item_tmp = symtable_search(symt_stack.top->symt, token->data.string_c->str))==NULL) {
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
                            if (convert_exp_to_d_type(final_type) == D_VOID) {
                                return result;
                            }
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
            if(fun_name.str[0]== '\0') {
                if( (tmp = symtable_search(symt_stack.top->symt, token->data.string_c->str) ) == NULL ) {
                    tmp = symtable_insert(symt_stack.top->symt, token->data.string_c->str);
                } else {
                    f_flag = true;
                }
            } else {
                if( (tmp = symtable_search(symt_stack.active->symt, token->data.string_c->str) ) == NULL ) {
                tmp = symtable_insert(symt_stack.active->symt, token->data.string_c->str);
                } else {
                    f_flag = true;
                }   
            }
            if (( error_type = get_next_token(token) )) {
                return error_type;
            }
            if (token->type == T_ASSIGN) {
                if (!f_flag) {
                    data_glob.operator = I_DEFVAR;
                    data_glob.operand_1.frame = F_LF;
                    set_operand_value(&data_glob.operand_1, tmp->id);
                    if (fun_name.str[0] != '\0') {
                        DLL_InsertAfter(&inst_list, &data_glob);
                        DLL_Next(&inst_list);
                    } else {
                        DLL_InsertLast(&inst_list, &data_glob);
                    }
                    clear_data(&data_glob);

                }

                if (( error_type = get_next_token(token) )) {
                    return error_type;
                }
                if (token->type == T_FUN_ID) {
                     /*
                    Sematick check: 
                    If we found the defined function, we retype our variable to type, that function returns
                    Else we create a temporary definition in table, and add that to list of undefined but used fucntions
                    in the end of analysis we will check, if it was defined late.
                    */
                    if((item_tmp = symtable_search(symt_stack.top->symt, token->data.string_c->str)) == NULL) {
                        return SEM_ERR_UNDEFINED_FUNCTION;
                    } else {
                        symtable_add_type(tmp, item_tmp->type);

                        data_glob.operator = I_CREATEFRAME;
                        DLL_InsertAfter(&inst_list, &data_glob);
                        clear_data(&data_glob);

                        DLL_Next(&inst_list);

                        int i = declare(token);

                        data_glob.operator = I_MOVE;
                        set_operand_value(&data_glob.result, tmp->id);
                        data_glob.result.frame = F_LF;
                        set_operand_value(&data_glob.operand_1, "$$$ret_val");
                        data_glob.operand_1.frame = F_TF;
                        DLL_InsertAfter(&inst_list, &data_glob);
                        clear_data(&data_glob);

                        DLL_Next(&inst_list);

                        return i;
                    }
                    return SEM_ERR_OTHER;
                } else if (token->type == T_VAR_ID || token->type == T_INT_VAL || token->type == T_DEC_VAL || token->type == T_STRING_VAL || token->type == T_PAR_LEFT) {
                    int result = expression(token);
                    if (result == NO_ERR) {
                        symtable_add_type(tmp, ( convert_exp_to_d_type (final_type) ));

                        data_glob.operator = I_MOVE;
                        set_operand_value(&data_glob.result, tmp->id);
                        data_glob.result.frame = F_LF;
                        set_operand_value(&data_glob.operand_1, "tmp1");
                        data_glob.operand_1.frame = F_GF;
                        if (fun_name.str[0] != '\0') {
                            DLL_InsertAfter(&inst_list, &data_glob);
                            DLL_Next(&inst_list);
                        } else {
                            DLL_InsertLast(&inst_list, &data_glob);
                        }
                        clear_data(&data_glob);

                        data_glob.operator = I_MOVE;
                        set_operand_value(&data_glob.result, "tmp1");
                        data_glob.result.frame = F_GF;
                        data_glob.operand_1.type = D_VOID;
                        set_operand_value(&data_glob.operand_1, "nil");
                        if (fun_name.str[0] != '\0') {
                            DLL_InsertAfter(&inst_list, &data_glob);
                            DLL_Next(&inst_list);
                        } else {
                            DLL_InsertLast(&inst_list, &data_glob);
                        }
                        clear_data(&data_glob);

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
                return expression(token);
            }
            break;

        case (T_FUN_ID):
            if (symtable_search(symt_stack.top->symt, token->data.string_c->str) == NULL) {
                return SEM_ERR_UNDEFINED_FUNCTION;
            } else {
                data_glob.operator = I_CREATEFRAME;
                if (fun_name.str[0] != '\0') {
                    DLL_InsertAfter(&inst_list, &data_glob);
                    DLL_Next(&inst_list);
                } else {
                    DLL_InsertLast(&inst_list, &data_glob);
                }
                clear_data(&data_glob);

                int dec_ret = declare(token);

                return dec_ret;
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

        default:
            return SYNTAX_ERR;
    }
}

int f_list ( token_t * token ) {
    switch (token->type) {
        case (T_INT_VAL):
        case (T_STRING_VAL):
        case (T_DEC_VAL):
        case (T_PAR_LEFT):
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
            return NO_ERR;
        default:
            return SYNTAX_ERR;
    }
}

int f_param_declare ( token_t * token ) {
    if ( token->type == T_STRING_VAL || token->type == T_DEC_VAL || token->type == T_INT_VAL || token->type == T_VAR_ID ) {
        char* last_fun = NULL;
        str_get_last_fun_name(&fun_list, &last_fun);
        htab_data_t* item = symtable_search(symt_stack.top->symt, last_fun);
        if (item == NULL) {
            return SEM_ERR_UNDEFINED_FUNCTION;
        }
        if (!(param_counter<=item->argumets_amount)) {
            return SEM_ERR_WRONG_PARAM;
        }

        data_type data_tmp;
        if (token->type == T_VAR_ID) {

            char* c_tmp = (char*) malloc(256 * __CHAR_BIT__);
            if (c_tmp == NULL) {
                return ERROR_INTERNAL;
            }

            sprintf(c_tmp, "%%%d", param_counter);

            data_glob.operator = I_DEFVAR;
            data_glob.operand_1.frame = F_TF;
            set_operand_value(&data_glob.operand_1, c_tmp);
            DLL_InsertLast(&inst_list, &data_glob);
            clear_data(&data_glob);

            data_glob.operator = I_MOVE;
            data_glob.result.frame = F_TF;
            set_operand_value(&data_glob.result, c_tmp);
            data_glob.operand_1.frame = F_LF;
            set_operand_value(&data_glob.operand_1, token->data.string_c->str);
            DLL_InsertLast(&inst_list, &data_glob);
            clear_data(&data_glob);

            free(c_tmp);

            if(fun_name.str[0] == '\0'){ 
                htab_data_t* tmp = symtable_search(symt_stack.top->symt,token->data.string_c->str);
                if (tmp == NULL)
                { 
                    data_tmp = (symtable_search(symt_stack.active->symt,token->data.string_c->str)->type);    
                }
                else {
                    data_tmp = tmp->type;
                }
                  
            } else {
                data_tmp = (symtable_search(symt_stack.active->symt, token->data.string_c->str)->type);    
            }
        } else {

            char* c_tmp = (char*) malloc(256 * __CHAR_BIT__);
            if (c_tmp == NULL) {
                return ERROR_INTERNAL;
            }


            sprintf(c_tmp, "%%%d", param_counter);

            if (fun_name.str[0] == '\0') {
                data_glob.operator = I_DEFVAR;
                data_glob.operand_1.frame = F_TF;
                set_operand_value(&data_glob.operand_1, c_tmp);
                DLL_InsertLast(&inst_list, &data_glob);
                clear_data(&data_glob);

                data_glob.operator = I_MOVE;
                data_glob.result.frame = F_TF;
                set_operand_value(&data_glob.result, c_tmp);
                data_glob.operand_1.type = convert_to_d_type(token);
                set_operand_value(&data_glob.operand_1, token->data.string_c->str);
                DLL_InsertLast(&inst_list, &data_glob);
                clear_data(&data_glob);
            } else {
                data_glob.operator = I_DEFVAR;
                data_glob.operand_1.frame = F_TF;
                set_operand_value(&data_glob.operand_1, c_tmp);
                DLL_InsertAfter(&inst_list, &data_glob);
                clear_data(&data_glob);

                DLL_Next(&inst_list);

                data_glob.operator = I_MOVE;
                data_glob.result.frame = F_TF;
                set_operand_value(&data_glob.result, c_tmp);
                data_glob.operand_1.type = convert_to_d_type(token);
                set_operand_value(&data_glob.operand_1, token->data.string_c->str);
                DLL_InsertAfter(&inst_list, &data_glob);
                clear_data(&data_glob);

                DLL_Next(&inst_list);
            }

            free(c_tmp);

            data_tmp = convert_to_d_type(token);
        }
        data_type arg_type = convert_from_arg_to_d_type(item->arguments->str[param_counter]);
        if (arg_type != D_TERM) {
            if (arg_type != data_tmp) {
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
        str_get_last_fun_name(&fun_list, &tmp);
        if (!(symtable_search(symt_stack.top->symt, tmp)->infinite))
        {  
            if (param_counter != (symtable_search(symt_stack.top->symt, tmp))->argumets_amount) {
                return SEM_ERR_WRONG_PARAM;
            }
        }
        param_counter = 0;

        char* tmp_c;

        if (fun_name.str[0] == '\0') {
            data_glob.operator = I_CALL;
            str_get_last_fun_name(&fun_list, &tmp_c);
            set_operand_value(&data_glob.operand_1, tmp_c);
            DLL_InsertLast(&inst_list, &data_glob);
            clear_data(&data_glob);
        } else {
            data_glob.operator = I_CALL;
            str_get_last_fun_name(&fun_list, &tmp_c);
            set_operand_value(&data_glob.operand_1, tmp_c);
            DLL_InsertAfter(&inst_list, &data_glob);
            clear_data(&data_glob);

            DLL_Next(&inst_list);
        }

        if (tmp_c != NULL) {
            free(tmp_c);
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
        if ( ( error_type = get_next_token(token) ) ) {
            return error_type;
        }
        if (token->type == T_VAR_ID) {

            char* c_tmp = (char*) malloc(256 * __CHAR_BIT__);
            if (c_tmp == NULL) {
                return ERROR_INTERNAL;
            }

            sprintf(c_tmp, "%%%d", param_counter);

            data_glob.operator = I_DEFVAR;
            data_glob.operand_1.frame = F_LF;
            set_operand_value(&data_glob.operand_1, token->data.string_c->str);
            DLL_InsertAfter(&inst_list, &data_glob);
            clear_data(&data_glob);

            DLL_Next(&inst_list);

            data_glob.operator = I_MOVE;
            data_glob.result.frame = F_LF;
            set_operand_value(&data_glob.result, token->data.string_c->str);
            data_glob.operand_1.frame = F_LF;
            set_operand_value(&data_glob.operand_1, c_tmp);
            DLL_InsertAfter(&inst_list, &data_glob);
            clear_data(&data_glob);

            DLL_Next(&inst_list);

            free(c_tmp);

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
        error_type = f_param(token);
        if (error_type) {
            return error_type;
        }
        return f_plist(token);
    } else if ( token->type == T_PAR_RIGHT ) {
        htab_data_t* tmp;
        if((tmp = symtable_search(symt_stack.top->symt,fun_name.str))){
            tmp->argumets_amount = param_counter;
        } else {
            return ERROR_INTERNAL;
        }
        param_counter = 0;

        if (( error_type = get_next_token(token) )) {
            return error_type;
        }
        return NO_ERR;
    } else {
        return SYNTAX_ERR;
    }
}

int declare(token_t * token) {
    char* tmp = token->data.string_c->str;
    if (symtable_search(symt_stack.top->symt, tmp) == NULL) {
        return SEM_ERR_UNDEFINED_FUNCTION;
    } else {
        str_add_fun_name(&fun_list, tmp);
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
    bool f_flag = false;
    htab_data_t* tmp;
    exp_type final_type;
    set_type(&final_type);
    htab_data_t* item_tmp;

    switch (token->type) {
        case (T_INT_VAL):
        case (T_STRING_VAL):
        case (T_DEC_VAL):
        case (T_PAR_LEFT):
            return expression(token);
        case (T_KW_RETURN):
            data_glob.operator = I_CALL;
            set_operand_value(&data_glob.operand_1, "$$exit");
            DLL_InsertLast(&inst_list, &data_glob);

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
                tmp = symtable_insert(symt_stack.top->symt, token->data.string_c->str);
            } else {
                f_flag = true;
            }

            if (( error_type = get_next_token(token) )) {
                return error_type;
            }
            if (token->type == T_ASSIGN) {
                
                if (!f_flag) {
                    data_glob.operator = I_DEFVAR;
                    data_glob.operand_1.frame = F_LF;
                    set_operand_value(&data_glob.operand_1, tmp->id);
                    DLL_InsertLast(&inst_list, &data_glob);
                    clear_data(&data_glob);
                }

                if (( error_type = get_next_token(token) )) {
                    return error_type;
                }
                if (token->type == T_FUN_ID) {
                    /*
                    Sematick check: 
                    */
                    if((item_tmp = symtable_search(symt_stack.top->symt, token->data.string_c->str)) == NULL) {
                        return SEM_ERR_UNDEFINED_FUNCTION;
                    } else {
                        symtable_add_type(tmp, item_tmp->type);

                        data_glob.operator = I_CREATEFRAME;
                        DLL_InsertLast(&inst_list, &data_glob);
                        clear_data(&data_glob);

                        int dec_ret = declare(token);

                        data_glob.operator = I_MOVE;
                        set_operand_value(&data_glob.result, tmp->id);
                        data_glob.result.frame = F_LF;
                        set_operand_value(&data_glob.operand_1, "$$$ret_val");
                        data_glob.operand_1.frame = F_TF;
                        DLL_InsertLast(&inst_list, &data_glob);
                        clear_data(&data_glob);

                        return dec_ret;
                    }
                } else if (token->type == T_VAR_ID || token->type == T_INT_VAL || token->type == T_DEC_VAL || token->type == T_STRING_VAL || token->type == T_PAR_LEFT) {
                    set_symtable(symt_stack.top->symt);
                    int result = expression(token);
                    if (result == NO_ERR) {
                        symtable_add_type(tmp, ( convert_exp_to_d_type (final_type) )); 

                        data_glob.operator = I_MOVE;
                        set_operand_value(&data_glob.result, tmp->id);
                        data_glob.result.frame = F_LF;
                        set_operand_value(&data_glob.operand_1, "tmp1");
                        data_glob.operand_1.frame = F_GF;
                        DLL_InsertLast(&inst_list, &data_glob);
                        clear_data(&data_glob);

                        data_glob.operator = I_MOVE;
                        set_operand_value(&data_glob.result, "tmp1");
                        data_glob.result.frame = F_GF;
                        data_glob.operand_1.type = D_VOID;
                        set_operand_value(&data_glob.operand_1, "nil");
                        DLL_InsertLast(&inst_list, &data_glob);
                        clear_data(&data_glob);

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
                return expression(token); 
            }
            break;

        case (T_FUN_ID):
            if ((item_tmp = symtable_search(symt_stack.top->symt,token->data.string_c->str)) != NULL) {

                data_glob.operator = I_CREATEFRAME;
                DLL_InsertLast(&inst_list, &data_glob);
                clear_data(&data_glob);

                int dec_ret = declare(token);

                return dec_ret;
            } else {
                return SEM_ERR_UNDEFINED_FUNCTION;
            }
        case (T_KW_FUNCTION):

            if (( error_type = get_next_token(token) )) {
                return error_type;
            }
            if (token->type == T_FUN_ID) {

                data_glob.operator = I_LABEL;
                set_operand_value(&data_glob.operand_1, token->data.string_c->str);
                DLL_InsertFirst(&inst_list, &data_glob);
                clear_data(&data_glob);

                DLL_First(&inst_list);

                data_glob.operator = I_PUSHFRAME;
                DLL_InsertAfter(&inst_list, &data_glob);
                clear_data(&data_glob);

                DLL_Next(&inst_list);

                data_glob.operator = I_DEFVAR;
                data_glob.operand_1.frame = F_LF;
                set_operand_value(&data_glob.operand_1, "$$$ret_value");
                DLL_InsertAfter(&inst_list, &data_glob);
                clear_data(&data_glob);

                DLL_Next(&inst_list);

                data_glob.operator = I_MOVE;
                set_operand_value(&data_glob.result, "$$$ret_value");
                data_glob.result.frame = F_LF;
                data_glob.operand_1.type = D_VOID;
                set_operand_value(&data_glob.operand_1, "nil");
                DLL_InsertAfter(&inst_list, &data_glob);
                clear_data(&data_glob);

                DLL_Next(&inst_list);

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
                        if(symtable_add_type(symtable_search(symt_stack.top->symt, fun_name.str), d_tmp)) {

                        } else
                        if (( error_type = get_next_token(token) )) {
                            return error_type;
                        }
                        if (token->type == T_BRACE_LEFT) {
                            if (( error_type = get_next_token(token) )) {
                                return error_type;
                            }
                            set_symtable(symt_stack.active->symt);
                            int f_ret = f_list(token);

                            data_glob.operator = I_MOVE;
                            data_glob.result.frame = F_LF;
                            set_operand_value(&data_glob.result, "$$$ret_val");
                            data_glob.operand_1.frame = F_GF;
                            set_operand_value(&data_glob.operand_1, "tmp3");
                            DLL_InsertAfter(&inst_list, &data_glob);
                            clear_data(&data_glob);

                            DLL_Next(&inst_list);

                            data_glob.operator = I_POPFRAME;
                            DLL_InsertAfter(&inst_list, &data_glob);
                            clear_data(&data_glob);

                            DLL_Next(&inst_list);

                            data_glob.operator = I_RETURN;
                            DLL_InsertAfter(&inst_list, &data_glob);
                            clear_data(&data_glob);

                            DLL_Next(&inst_list);

                            return f_ret;
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
            set_symtable(symt_stack.top->symt);
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
        default:
            return SYNTAX_ERR;
    }
}

int st_list(token_t * token) {
    switch (token->type) {
        case (T_INT_VAL):
        case (T_STRING_VAL):
        case (T_DEC_VAL):
        case (T_PAR_LEFT):
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
    if (token->type == T_PROLOG) {  // if token is <?php white symbol declare(strictypes=1);
        if (( error_type = get_next_token(token) )) {
            return error_type;
        }
        error_type = st_list(token);
        return error_type;
    } else {
        return SYNTAX_ERR;
    }
}

int main() {
    token_t token;
    string s;
    str_init(&fun_list);
    str_init(&fun_name);
    set_fun_name(&fun_name);
    DLL_Init(&inst_list);
    init_data(&data_glob);

    data_glob.operator = I_LABEL;
    set_operand_value(&data_glob.operand_1, "$$main");
    DLL_InsertLast(&inst_list, &data_glob);
    clear_data(&data_glob);

    data_glob.operator = I_CREATEFRAME;
    DLL_InsertLast(&inst_list, &data_glob);
    clear_data(&data_glob);

    data_glob.operator = I_PUSHFRAME;
    DLL_InsertLast(&inst_list, &data_glob);
    clear_data(&data_glob);

    symtable_stack_init(&symt_stack);
    param_counter = 0;

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
    set_symtable(symt_stack.top->symt);
    set_flag(false);
    if (!str_init(&s)) {
        return 1;
    }
    set_source(stdin);
    set_src_str(&s);
    set_inst_list(&inst_list);
    if ((error_type = get_next_token(&token)) == 0) {
        error_type = kostyluka(&token);
    }
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

    data_glob.operator = I_LABEL;
    set_operand_value(&data_glob.operand_1, "$$exit");
    DLL_InsertLast(&inst_list, &data_glob);

    free_data_value(&data_glob);

    if (!error_type) {
        print_instruction(&inst_list);
    }

    symtable_stack_free(&symt_stack);
    return error_type;
}