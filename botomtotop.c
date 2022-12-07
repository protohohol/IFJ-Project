#include "botomtotop.h"

symtable* symt_l;
char* id;
bool ass_flag;
// bool par_flag;
exp_type* type;
DLList* i_list;

void set_symtable(symtable* source) {
    symt_l = source;
}

void set_id (char* source) {
    id = source;
}

void set_flag(bool source) {
    ass_flag = source;
}

// void set_par(bool source) {
//     par_flag = source;
// }

void set_type(exp_type* source) {
    type = source;
}

void set_inst_list(DLList* source) {
    i_list = source;
}

exp_type data_to_exp(data_type source) {
    switch (source) {
        case (D_INT):
            return ET_INT;
        case (D_FLOAT):
            return ET_FLOAT;
        case (D_STRING):
            return ET_STRING;
        default:
            return ET_UNDEFINED;
    }
}

data_type exp_to_data(exp_type source) {
    switch (source) {
        case (ET_INT):
            return D_INT;
        case (ET_FLOAT):
            return D_FLOAT;
        case (ET_STRING):
            return D_STRING;
        case (ET_NULL):
            return D_VOID;
        default:
            return D_UNDEFINED;
    }
}

instructions rule_to_inst(exp_rules source) {
    switch (source) {
        case (R_EQ):
            return I_EQ;
        case (R_NEQ):
            return I_NOT;
        case (R_L):
        case (R_LEQ):
            return I_LT;
        case (R_GR):
        case (R_GREQ):
            return I_GT;
        case (R_ADD):
            return I_ADD;
        case (R_CON):
            return I_CONCAT;
        case (R_DIV):
            return I_DIV;
        case (R_ID):
            return I_MOVE;
        case (R_MUL):
            return I_MUL;
        case (R_SUB):
            return I_SUB;
        default:
            return 100; // error
    }
}

int get_cond (token_t *token,sstack_t * stack_exp) {
    const int tmp_symbol = convert_to_symbol(token);
    item_stack_t * pstack = get_top_term(stack_exp);
    const int tmp_stack_symbol = pstack->symbol;
    switch ( tmp_symbol ) {
        case ES_PLUS:
        case ES_MINUS:
        case ES_CON:
            switch ( tmp_stack_symbol ) {
                case ES_PLUS:
                case ES_MINUS:
                case ES_CON:
                    return C_MORE; 
                case ES_MUL:
                case ES_DIV:
                    return C_MORE ;
                case ES_MTN:
                case ES_MEQ:
                case ES_LTN:
                case ES_LEQ:
                    return C_LESS;
                case ES_EQ:
                case ES_NEQ:
                    return C_LESS;
                case ES_ID:
                case ES_INT_LIT:
                case ES_FLOAT_LIT:
                case ES_STR:
                case ES_NULL:
                    return C_MORE ;
                case ES_LEFT_BRACKET:
                    return C_LESS ;
                case ES_RIGHT_BRACKET:
                    return C_MORE;
                case ES_END:
                    return C_LESS;
                default:
                    return C_NONE;
            }
            break;
        case ES_MUL:
        case ES_DIV:
            switch ( tmp_stack_symbol ) {
                case ES_PLUS:
                case ES_MINUS:
                case ES_CON:
                    return C_LESS; 
                case ES_MUL:
                case ES_DIV:
                    return C_MORE ;
                case ES_MTN:
                case ES_MEQ:
                case ES_LTN:
                case ES_LEQ:
                    return C_LESS;
                case ES_EQ:
                case ES_NEQ:
                    return C_LESS;
                case ES_ID:
                case ES_INT_LIT:
                case ES_FLOAT_LIT:
                case ES_STR:
                case ES_NULL:
                    return C_MORE ;
                case ES_LEFT_BRACKET:
                    return C_LESS ;
                case ES_RIGHT_BRACKET:
                    return C_MORE;
                case ES_END:
                    return C_LESS;
                default:
                    return C_NONE;
            }
            break;
        case ES_MTN:
        case ES_MEQ:
        case ES_LTN:
        case ES_LEQ:
            switch ( tmp_stack_symbol ) {
                case ES_PLUS:
                case ES_MINUS:
                case ES_CON:
                    return C_MORE; 
                case ES_MUL:
                case ES_DIV:
                    return C_MORE ;
                case ES_MTN:
                case ES_MEQ:
                case ES_LTN:
                case ES_LEQ:
                    return C_MORE;
                case ES_EQ:
                case ES_NEQ:
                    return C_LESS;
                case ES_ID:
                case ES_INT_LIT:
                case ES_FLOAT_LIT:
                case ES_STR:
                case ES_NULL:
                    return C_MORE ;
                case ES_LEFT_BRACKET:
                    return C_LESS ;
                case ES_RIGHT_BRACKET:
                    return C_MORE;
                case ES_END:
                    return C_LESS;
                default:
                    return C_NONE;
            }
            break;
        case ES_EQ:
        case ES_NEQ:
            switch ( tmp_stack_symbol ) {
                case ES_PLUS:
                case ES_MINUS:
                case ES_CON:
                    return C_MORE; 
                case ES_MUL:
                case ES_DIV:
                    return C_MORE ;
                case ES_MTN:
                case ES_MEQ:
                case ES_LTN:
                case ES_LEQ:
                    return C_MORE;
                case ES_EQ:
                case ES_NEQ:
                    return C_MORE;
                case ES_ID:
                case ES_INT_LIT:
                case ES_FLOAT_LIT:
                case ES_STR:
                case ES_NULL:
                    return C_MORE ;
                case ES_LEFT_BRACKET:
                    return C_LESS ;
                case ES_RIGHT_BRACKET:
                    return C_MORE;
                case ES_END:
                    return C_LESS;
                default:
                    return C_NONE;
            }
            break;
        case ES_ID:
        case ES_INT_LIT:
        case ES_FLOAT_LIT:
        case ES_STR:
        case ES_NULL:
            switch ( tmp_stack_symbol ) {
                case ES_PLUS:
                case ES_MINUS:
                case ES_CON:
                    return C_LESS; 
                case ES_MUL:
                case ES_DIV:
                    return C_LESS ;
                case ES_MTN:
                case ES_MEQ:
                case ES_LTN:
                case ES_LEQ:
                    return C_LESS;
                case ES_EQ:
                case ES_NEQ:
                    return C_LESS;
                case ES_ID:
                case ES_INT_LIT:
                case ES_FLOAT_LIT:
                case ES_STR:
                case ES_NULL:
                    return C_NONE ;
                case ES_LEFT_BRACKET:
                    return C_LESS ;
                case ES_RIGHT_BRACKET:
                    return C_NONE;
                case ES_END:
                    return C_LESS;
                default:
                    return C_NONE;
            }
            break;
        case ES_LEFT_BRACKET:
            switch ( tmp_stack_symbol ) {
                case ES_PLUS:
                case ES_MINUS:
                case ES_CON:
                    return C_LESS; 
                case ES_MUL:
                case ES_DIV:
                    return C_LESS ;
                case ES_MTN:
                case ES_MEQ:
                case ES_LTN:
                case ES_LEQ:
                    return C_LESS;
                case ES_EQ:
                case ES_NEQ:
                    return C_LESS;
                case ES_ID:
                case ES_INT_LIT:
                case ES_FLOAT_LIT:
                case ES_STR:
                case ES_NULL:
                    return C_NONE ;
                case ES_LEFT_BRACKET:
                    return C_LESS ;
                case ES_RIGHT_BRACKET:
                    return C_NONE;
                case ES_END:
                    return C_LESS;
                default:
                    return C_NONE;
            }
            break;
        case ES_RIGHT_BRACKET:
            switch ( tmp_stack_symbol ) {
                case ES_PLUS:
                case ES_MINUS:
                case ES_CON:
                    return C_MORE; 
                case ES_MUL:
                case ES_DIV:
                    return C_MORE;
                case ES_MTN:
                case ES_MEQ:
                case ES_LTN:
                case ES_LEQ:
                    return C_MORE;
                case ES_EQ:
                case ES_NEQ:
                    return C_MORE;
                case ES_ID:
                case ES_INT_LIT:
                case ES_FLOAT_LIT:
                case ES_STR:
                case ES_NULL:
                    return C_MORE ;
                case ES_LEFT_BRACKET:
                    return C_EQ ;
                case ES_RIGHT_BRACKET:
                    return C_MORE;
                case ES_END:
                    return C_NONE;
                default:
                    return C_NONE;
            }
            break;
        case ES_END:
            switch ( tmp_stack_symbol ) {
                case ES_PLUS:
                case ES_MINUS:
                case ES_CON:
                    return C_MORE; 
                case ES_MUL:
                case ES_DIV:
                    return C_MORE;
                case ES_MTN:
                case ES_MEQ:
                case ES_LTN:
                case ES_LEQ:
                    return C_MORE;
                case ES_EQ:
                case ES_NEQ:
                    return C_MORE;
                case ES_ID:
                case ES_INT_LIT:
                case ES_FLOAT_LIT:
                case ES_STR:
                case ES_NULL:
                    return C_MORE ;
                case ES_LEFT_BRACKET:
                    return C_NONE ;
                case ES_RIGHT_BRACKET:
                    return C_MORE;
                case ES_END:
                    return C_NONE;
                default:
                    return C_NONE;
            }
            break;
        default:
            return C_NONE;
            break;
    }
}

const int convert_to_symbol (token_t * token) {
    switch (token->type) {
	case T_ADD:
		return ES_PLUS;
	case T_SUB:
		return ES_MINUS;
    case T_DOT:
        return ES_CON;
	case T_MUL:
		return ES_MUL;
	case T_DIV:
		return ES_DIV;
	case T_ASSIGN:
		return ES_EQ;
	case T_NOT_EQUAL:
		return ES_NEQ;
    case T_EQUAL:
		return ES_EQ;
	case T_LESS_EQUAL:
		return ES_LEQ;
	case T_LESS:
		return ES_LTN;
	case T_GREATER_EQUAL:
		return ES_MEQ;
	case T_GREATER:
		return ES_MTN;
	case T_PAR_LEFT:
		return ES_LEFT_BRACKET;
	case T_PAR_RIGHT:
		return ES_RIGHT_BRACKET;
	case T_VAR_ID:
		return ES_ID;
	case T_INT_VAL:
		return ES_INT_LIT;
	case T_DEC_VAL:
		return ES_FLOAT_LIT;
	case T_STRING_VAL:
		return ES_STR;
    case T_KW_NULL:
		return ES_NULL;
    default :
        return ES_END;
	}
}

int convert_to_type ( token_t * token ) {
    htab_data_t* tmp;
    switch ( token->type ) {
    case T_VAR_ID:
        if ((tmp = symtable_search(symt_l, token->data.string_c->str)) != NULL) {
            return data_to_exp(tmp->type);
        } else {
            printf("мы в пизде\n");
            return ET_UNDEFINED;
        }
    case T_INT_VAL:
        return ET_INT;

    case T_DEC_VAL:
        return ET_FLOAT;

    case T_STRING_VAL:
        return ET_STRING;

    case T_KW_NULL:
        return ET_NULL;

    default:
        return ET_UNDEFINED;
    }
}

bool find_catch ( int * count , sstack_t * sstack) {
    item_stack_t * tmp = sstack->top;
    bool flag;
    *count = 0;
    while ( tmp != NULL ) {
        if ( tmp->symbol != ES_CATCH ) {
            flag = false;
            *count = *count + 1;
        } else {
            flag = true;
            break;
        }
        tmp = tmp->next;
    }
    return flag;
}

void tac_generate (instructions instruction, item_stack_t * op1, item_stack_t * op2, item_stack_t * op3) {
    // taCode data;
    // switch (instruction) {
    //     case (I_DEFVAR):
    //         data.operand_1.type = exp_to_data(op1->etype);
    //         data.operand_1.value = 
    // }
    return;
}

int check_sem (exp_rules rule, item_stack_t * op1, item_stack_t * op2, item_stack_t * op3, exp_type * type) {
    taCode data;
    init_data(&data);
    switch (rule) {
        case (R_ID):
            if (op1->etype == ET_UNDEFINED) {
                free_data_value(&data);
                return SEM_ERR_UNDEFINED_VAR;
            } else if (op1->etype == ET_INT) {
                *type = ET_INT;
            } else if (op1->etype == ET_FLOAT) {
                // printf("hi2\n");
                *type = ET_FLOAT;
            } else if (op1->etype == ET_STRING) {
                // printf("hi3\n");
                *type = ET_STRING;
            }
            // data.operand_1.type = exp_to_data(op1->etype);
            // set_operand_value(&data.operand_1, op1->value); // dobavit proverku blya po bratski realno nado
            // data.operator = I_DEFVAR;
            // DLL_InsertLast(i_list, &data);
            // taCode tmp;
            // DLL_GetLast(i_list, &tmp);
            // printf("\t\t\t\t\t\ttestim jebat : %s\t\t\t\t\top : %s\t\t\t\t\t\tdata : %s\n", tmp.operand_1.value, op1->value, data.operand_1.value);
            free_data_value(&data);
            return NO_ERR;
        case (R_MUL):
        case (R_SUB):
        case (R_ADD):
            // printf("t1 : %d\tt2 : %d\tt3 : %d\n", op1->etype, op2->etype, op3->etype);
            if (op1->etype == ET_INT && op3->etype == ET_INT) {
                *type = ET_INT;
            } else if (op1->etype == ET_FLOAT && op2->etype == ET_FLOAT) {
                *type = ET_FLOAT;
            } else if ((op1->etype == ET_INT || op1->etype == ET_FLOAT) && (op3->etype == ET_INT || op3->etype == ET_FLOAT)) {
                if (op1->etype == ET_INT) {

                    data.operator = I_MOVE;
                    set_operand_value(&data.result, "tmp2");
                    data.operand_1.type = exp_to_data(ET_NULL);
                    set_operand_value(&data.operand_1, "nil");
                    DLL_InsertLast(i_list, &data);
                    clear_data(&data);
                    // taCode tmp;
                    // DLL_GetLast(i_list, &tmp);
                    // printf("\t\t\t\t\t\t\t\t\ttmp : %s\n", tmp.operand_1.value);

                    data.operator = I_INT2FLOAT;
                    set_operand_value(&data.result, "tmp2");
                    data.result.frame = F_GF;
                    set_operand_value(&data.operand_1, op1->value);
                    char* ptr = NULL;
                    strtol(data.operand_1.value, &ptr, 10);
                    if (ptr == NULL) {
                        data.operand_1.type = exp_to_data(ET_INT);
                    } else {
                        data.operand_1.frame = F_GF;
                    }
                    DLL_InsertLast(i_list, &data);
                    clear_data(&data);

                    // data.operand_1.type = exp_to_data(op1->etype);
                    // generate(retype(op1, float));
                } else {

                    data.operator = I_MOVE;
                    set_operand_value(&data.result, "tmp2");
                    data.operand_1.type = exp_to_data(ET_NULL);
                    set_operand_value(&data.operand_1, "nil");
                    DLL_InsertLast(i_list, &data);
                    clear_data(&data);
                    // taCode tmp;
                    // DLL_GetLast(i_list, &tmp);
                    // printf("\t\t\t\t\t\t\t\t\ttmp : %s\n", tmp.operand_1.value);

                    data.operator = I_INT2FLOAT;
                    set_operand_value(&data.result, "tmp2");
                    data.result.frame = F_GF;
                    set_operand_value(&data.operand_1, op3->value);
                    char* ptr = NULL;
                    strtol(data.operand_1.value, &ptr, 10);
                    if (ptr == NULL) {
                        data.operand_1.type = exp_to_data(ET_INT);
                    } else {
                        data.operand_1.frame = F_GF;
                    }
                    DLL_InsertLast(i_list, &data);
                    clear_data(&data);

                    // generate(retype(op3, float));
                }
                *type = ET_FLOAT;
            } else {
                free_data_value(&data);
                return SEM_ERR_TYPE_COMPAT; // надо поменять все ретерны на запись в переменной или добавить фри перед каждым ретерном
            }

            if (rule == R_MUL) {
                data.operator = I_MUL;
            } else if (rule == R_ADD) {
                data.operator = I_ADD;
            } else {
                data.operator = I_SUB;
            }

            data.operand_1.frame = F_GF;
            data.operand_1.type = exp_to_data(op1->etype);
            set_operand_value(&data.result, "tmp1");
            data.operator = I_ADD;
            // printf("hi");
            clear_data(&data);
            
            return NO_ERR;

        case (R_EQ):
        case (R_NEQ):
        case (R_LEQ):
        case (R_L):
        case (R_GR):
        case (R_GREQ):
            *type = ET_UNDEFINED;
            free_data_value(&data);
            return NO_ERR;

        case (R_CON):
            if (op1->etype == ET_STRING && op3->etype == ET_STRING) {
                free_data_value(&data);
                return NO_ERR;
            } else {
                free_data_value(&data);
                return SEM_ERR_TYPE_COMPAT;
            }

        case (R_DIV):
            if (op1->etype == ET_FLOAT && op3->etype == ET_FLOAT) {
            } else if (op1->etype == ET_INT && op3->etype == ET_FLOAT) {

                data.operator = I_MOVE;
                set_operand_value(&data.result, "tmp2");
                data.operand_1.type = exp_to_data(ET_NULL);
                set_operand_value(&data.operand_1, "nil");
                DLL_InsertLast(i_list, &data);
                clear_data(&data);
                // taCode tmp;
                // DLL_GetLast(i_list, &tmp);
                // printf("\t\t\t\t\t\t\t\t\ttmp : %s\n", tmp.operand_1.value);

                data.operator = I_INT2FLOAT;
                set_operand_value(&data.result, "tmp2");
                data.result.frame = F_GF;
                set_operand_value(&data.operand_1, op1->value);
                char* ptr = NULL;
                strtol(data.operand_1.value, &ptr, 10);
                if (ptr == NULL) {
                    data.operand_1.type = exp_to_data(ET_INT);
                } else {
                    data.operand_1.frame = F_GF;
                }
                DLL_InsertLast(i_list, &data);
                clear_data(&data);

                // generate(retype(op1, float));
            } else if (op3->etype == ET_INT && op1->etype == ET_FLOAT) {

                data.operator = I_MOVE;
                set_operand_value(&data.result, "tmp2");
                data.operand_1.type = exp_to_data(ET_NULL);
                set_operand_value(&data.operand_1, "nil");
                DLL_InsertLast(i_list, &data);
                clear_data(&data);
                // taCode tmp;
                // DLL_GetLast(i_list, &tmp);
                // printf("\t\t\t\t\t\t\t\t\ttmp : %s\n", tmp.operand_1.value);

                data.operator = I_INT2FLOAT;
                set_operand_value(&data.result, "tmp2");
                data.result.frame = F_GF;
                set_operand_value(&data.operand_1, op3->value);
                char* ptr = NULL;
                strtol(data.operand_1.value, &ptr, 10);
                if (ptr == NULL) {
                    data.operand_1.type = exp_to_data(ET_INT);
                } else {
                    data.operand_1.frame = F_GF;
                }
                DLL_InsertLast(i_list, &data);
                clear_data(&data);
                
                // generate(retype(op3, float));
            } else {
                free_data_value(&data);
                return SEM_ERR_TYPE_COMPAT;
            }

            *type = ET_FLOAT;
            free_data_value(&data);
            return NO_ERR;

        case (R_PAR):
            *type = op2->etype;
            free_data_value(&data);
            return NO_ERR;

        default:
            free_data_value(&data);
            return -1;
    }
    // *type = ET_UNDEFINED;
    // return NO_ERR;
}

int rule_test (int count, item_stack_t * op1, item_stack_t * op2, item_stack_t * op3, sstack_t * exp_stack) {
    exp_rules rule;
    int error_type;
    exp_type tmptype;
    if ( count == 1 ) {
        if ( op1->symbol == ES_ID || op1->symbol == ES_INT_LIT || op1->symbol == ES_FLOAT_LIT || op1->symbol == ES_STR || op1->symbol == ES_NULL ) {
            rule = R_ID;
        } else {
            rule = R_ERROR;
        }
    } else if ( count == 3 ) {
        if ( (op1->symbol == ES_LEFT_BRACKET) & (op2->symbol == ES_NON_TERM) & (op3->symbol == ES_RIGHT_BRACKET) ) {
            rule =  R_PAR;
            printf("par\n");
        } else if ( op1->symbol == ES_NON_TERM && op3->symbol == ES_NON_TERM ) {
            switch ( op2->symbol )
            {
            case ES_PLUS:
                rule = R_ADD;
                printf("ADD\n");
                break;
            case ES_MINUS:
                rule = R_SUB;
                break;
            case ES_CON:
                rule = R_CON;
                break;
            case ES_MUL:
                printf("MUL\n");
                rule = R_MUL;
                break;
            case ES_DIV:
                rule = R_DIV;
                break;
            case ES_EQ:
                printf("EQ\n");
                rule = R_EQ;
                break;
            case ES_NEQ:
                rule = R_NEQ;
                break;
            case ES_LEQ:
                rule = R_LEQ;
                break;
            case ES_LTN:
                rule = R_L;
                break;
            case ES_MEQ:
                rule = R_GREQ;
                break;
            case ES_MTN:
                rule = R_GR;
                break;
            default:
                rule = R_ERROR;
                break;
            }
        } else {
            rule = R_ERROR;
        }
    } else {
        rule = R_ERROR;
    }
    if ( rule == R_ERROR ) {
        return SYNTAX_ERR;
    } else {
        if( ( error_type = check_sem ( rule, op1, op2, op3, &tmptype ) ) ){
            return error_type;
        } else if ( ( rule == R_ADD ) && ( tmptype == ET_STRING) ) {
            // tac_generate();
        } else {
            // tac_generate();
        }
        string s;
        str_init(&s);
        if (op1->value != NULL) {
            // printf("jeste ne pizda\n");
            str_add_more_chars(&s, op1->value);
        }
        stack_pop_mult(exp_stack,count+1);
        // printf("string : %s\n", s.str);
        // if (op1 != NULL) {
        //     printf("op1122 val : %s\n", op1->value);
        // }
        if (rule == R_ID) {
            // printf("op : %s\n", op1->value);
            stack_push(exp_stack, ES_NON_TERM, tmptype, s.str);
            str_free(&s);
        } else {
            stack_push(exp_stack, ES_NON_TERM, tmptype, NULL);
        }
        *type = tmptype;
    }
    return NO_ERR;
} 

int expression (token_t * token) {
    printf("i am in expressions\n");
    int error_type;
    sstack_t exp_stack;
    stack_init(&exp_stack);
    item_stack_t * op_1;
    item_stack_t * op_2;
    item_stack_t * op_3;
    int tmp_sym;
    int tmp_type;
    bool found;
    int count;
    taCode data;
    init_data(&data);

    stack_push(&exp_stack, ES_END, ET_UNDEFINED, NULL);
    if (ass_flag) {
        ass_flag = false;
        htab_data_t* item = symtable_search(symt_l, id);
        printf("id : %s\n", id);
        // if (item == NULL) {
        //     printf("hi\n");
        // }
        stack_push_after(&exp_stack, ES_CATCH, ET_UNDEFINED, NULL);
        stack_push(&exp_stack, ES_ID, data_to_exp(item->type), item->id);
    }
    while( !( ( convert_to_symbol(token) == ES_END ) && ( ( get_top_term(&exp_stack) )->symbol == ES_END ) ) ) {
        //printf( "%d\n",(get_top_term(&exp_stack) )->symbol);
        switch (get_cond(token, &exp_stack)) {
        case C_EQ:
            // printf("i am in C_EQ\n");
            tmp_sym = convert_to_symbol(token);
            tmp_type = convert_to_type(token);
            stack_push(&exp_stack, tmp_sym, tmp_type, token->data.string_c->str); // TUT PROVERKU DOBAV JESTLI NE VPADLU
            if ( ( error_type = get_next_token(token) ) ) {
                free_data_value(&data);
                stack_dispose(&exp_stack);
                return error_type;
            }
            break;
        case C_LESS:
            printf("i am in C_LESS\n");
            stack_push_after(&exp_stack, ES_CATCH, ET_UNDEFINED, NULL);
            printf("token type : %d\n", token->type);
            tmp_sym = convert_to_symbol(token);
            printf("token type : %d\n", token->type);
            tmp_type = convert_to_type(token);
            printf("token type : %d\n", token->type);
            // printf("tmp_type : %d\n", tmp_type);
            if (token->type == T_VAR_ID || token->type == T_STRING_VAL || token->type == T_DEC_VAL || token->type == T_INT_VAL) {
                // printf("\t\t\t\t\t\t\t\t\ttoken str val : %s\n", token->data.string_c->str);
                stack_push(&exp_stack, tmp_sym, tmp_type, token->data.string_c->str);
            } else {
                stack_push(&exp_stack, tmp_sym, tmp_type, NULL);
            }
            // printf("push string : %s\n", get_top(&exp_stack)->value);
            // printf("push : %d\n", get_top(&exp_stack)->etype);
            if ( ( error_type = get_next_token(token) ) ) {
                free_data_value(&data);
                stack_dispose(&exp_stack);
                return error_type;
            }
            break;
        case C_MORE:
            printf("i am in C_MORE\n");
            printf("push more : %d\n", get_top(&exp_stack)->etype);
            found = find_catch(&count, &exp_stack);
            if (found && ( count == 3)) {
                op_1 = exp_stack.top->next->next;
                op_2 = exp_stack.top->next;
                op_3 = exp_stack.top;
                // printf("op1 : %d\top2 : %d\top3 : %d\n", op_1->etype, op_2->etype, op_3->etype);
                if ( ( error_type = rule_test ( count, op_1, op_2, op_3, &exp_stack ) ) ) {
                    free_data_value(&data);
                    stack_dispose(&exp_stack);
                    return error_type;
                }
                //printf( "%d\n",(get_top_term(&exp_stack) )->symbol);
            } else if ( found && ( count == 1 ) ) {
                // printf("push string : %s\n", get_top(&exp_stack)->value);
                op_1 = get_top(&exp_stack);
                // if (op_1 != NULL) {
                //     printf("op val : %s\n", op_1->value);
                // }
                // printf("stack top type : %d\n", op_1->etype);
                // printf("op1 else if: %d\n", op_1->etype);
                if ( ( error_type = rule_test ( count, op_1, NULL, NULL, &exp_stack ) ) ) {
                    free_data_value(&data);
                    stack_dispose(&exp_stack);
                    return error_type;
                }
            }
            else {
                free_data_value(&data);
                stack_dispose(&exp_stack);
                return SYNTAX_ERR;
            }
            break;
        case C_NONE:
            // printf("i am in C_NONE\n");
            if (( ( get_top_term(&exp_stack) )->symbol != ES_END )) {
                free_data_value(&data);
                stack_dispose(&exp_stack);
                return SYNTAX_ERR;  
            } else {
                // item_stack_t* tmp1;
                // if ((tmp1 = get_top(&exp_stack)) != NULL) {
                //     printf("type : %d\tvalue : %s\n", tmp1->etype, tmp1->value);
                // }
                free_data_value(&data);
                stack_dispose(&exp_stack);
                return NO_ERR;
            }
            break;
        }
    }

    item_stack_t* tmp1;
    if ((tmp1 = get_top(&exp_stack)) != NULL) {
        data.operator = I_MOVE;
        set_operand_value(&data.operand_1, tmp1->value);
        data.operand_1.type = exp_to_data(tmp1->etype);
        data.result.frame = F_GF;
        set_operand_value(&data.result, "tmp1");
        DLL_InsertLast(i_list, &data);
        clear_data(&data);
    } else {

    }
    // item_stack_t* tmp1;
    // if ((tmp1 = get_top(&exp_stack)) != NULL) {
    //     printf("type : %d\tvalue : %s\n", tmp1->etype, tmp1->value);
    // }
    stack_dispose(&exp_stack);
    free_data_value(&data);
    // printf("tt : %d\n", token->type);
    return NO_ERR;
}