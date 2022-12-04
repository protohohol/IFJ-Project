#include "botomtotop.h"

symtable symt;
char* id;
int ass_flag;
exp_type* type;

void set_symtable(symtable source) {
    *symt = *source;
}

void set_id (char* source) {
    id = source;
}

void set_flag(bool source) {
    ass_flag = source;
}

void set_type(exp_type* source) {
    type = source;
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
    switch ( token->type ) {
    case T_VAR_ID:
        return 0;//check_type_of_var();
        break;
    case T_INT_VAL:
        return ET_INT;
        break;
    case T_DEC_VAL:
        return ET_FLOAT;
        break; 
    case T_STRING_VAL:
        return ET_STRING;
        break;
    default:
        return ET_UNDEFINED;
        break;
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

void tac_generate ( ) {
    return;
}
int check_sem ( exp_rules rule, item_stack_t * op1, item_stack_t * op2, item_stack_t * op3, exp_type * type) {
    switch (rule) {
        case (R_ID):
            if (op1->etype == ET_UNDEFINED) {
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
            return NO_ERR;

        case (R_ADD):
            // printf("t1 : %d\tt2 : %d\tt3 : %d\n", op1->etype, op2->etype, op3->etype);
            if (op1->etype == ET_INT && op3->etype == ET_INT) {
                *type = ET_INT;
            } else if ((op1->etype == ET_INT || op1->etype == ET_FLOAT) && (op3->etype == ET_INT || op3->etype == ET_FLOAT)) {
                *type = ET_FLOAT;
            } else {
                return SEM_ERR_TYPE_COMPAT;
            }
            return NO_ERR;

        default:
            return -1;
    }
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
            tac_generate();
        } else {
            tac_generate();
        }
        stack_pop_mult(exp_stack,count+1);
        stack_push(exp_stack, ES_NON_TERM, tmptype);
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
    stack_push(&exp_stack,ES_END,ET_UNDEFINED);
    // if (ass_flag) {
    //     ass_flag = false;
    // }
    while( !( ( convert_to_symbol(token) == ES_END ) && ( ( get_top_term(&exp_stack) )->symbol == ES_END ) ) ) {
        //printf( "%d\n",(get_top_term(&exp_stack) )->symbol);
        switch (get_cond(token,&exp_stack)) {
        case C_EQ:
            //printf("i am in C_EQ\n");
            tmp_sym = convert_to_symbol(token);
            tmp_type = convert_to_type(token);
            stack_push(&exp_stack,tmp_sym,tmp_type); // TUT PROVERKU DOBAV JESTLI NE VPADLU
            if ( ( error_type = get_next_token(token) ) ) {
                return error_type;
            }
            break;
        case C_LESS:
            //printf("i am in C_LESS\n");
            stack_push_after(&exp_stack,ES_CATCH, ET_UNDEFINED);
            // printf("token type : %d\n", token->type);
            tmp_sym = convert_to_symbol(token);
            tmp_type = convert_to_type(token);
            // printf("tmp_type : %d\n", tmp_type);
            stack_push(&exp_stack,tmp_sym,tmp_type);
            // printf("push : %d\n", get_top(&exp_stack)->etype);
            if ( ( error_type = get_next_token(token) ) ) {
                return error_type;
            }
            break;
        case C_MORE:
            //printf("i am in C_MORE\n");
            // printf("push more : %d\n", get_top(&exp_stack)->etype);
            found = find_catch(&count,&exp_stack);
            if (found && ( count == 3)) { 
                op_1 = exp_stack.top->next->next;
                op_2 = exp_stack.top->next;
                op_3 = exp_stack.top;
                // printf("op1 : %d\top2 : %d\top3 : %d\n", op_1->etype, op_2->etype, op_3->etype);
                if ( ( error_type = rule_test ( count, op_1, op_2, op_3, &exp_stack ) ) ) {
                    return error_type;
                }
                //printf( "%d\n",(get_top_term(&exp_stack) )->symbol);
            } else if ( found && ( count == 1 ) ) {
                op_1 = exp_stack.top;
                // printf("op1 else if: %d\n", op_1->etype);
                if ( ( error_type = rule_test ( count, op_1, NULL, NULL, &exp_stack ) ) ) {
                    return error_type;
                }
            }
            else {
                return SYNTAX_ERR;
            }
            break;
        case C_NONE:
            //printf("i am in C_NONE\n");
            if (( ( get_top_term(&exp_stack) )->symbol != ES_END )) {
                return SYNTAX_ERR;  
            } else {
                return 0;
            }  
            break;
        }
    }
    stack_dispose(&exp_stack);
    return 0;
}