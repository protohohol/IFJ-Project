#include "botomtotop.h"




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
                    return C_LESS ;
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
                    return C_LESS ;
                case T_PAR_LEFT:
                    return C_LESS ;
                case T_PAR_RIGHT:
                    return C_MORE;
                case ES_END:
                    return C_MORE;
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
                    return C_LESS ;
                case T_PAR_LEFT:
                    return C_LESS ;
                case T_PAR_RIGHT:
                    return C_MORE;
                case ES_END:
                    return C_MORE;
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
                    return C_LESS; 
                case ES_MUL:
                case ES_DIV:
                    return C_LESS ;
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
                    return C_LESS ;
                case T_PAR_LEFT:
                    return C_LESS ;
                case T_PAR_RIGHT:
                    return C_MORE;
                case ES_END:
                    return C_MORE;
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
                    return C_MORE;
                case ES_ID:
                case ES_INT_LIT:
                case ES_FLOAT_LIT:
                case ES_STR:
                    return C_LESS ;
                case T_PAR_LEFT:
                    return C_LESS ;
                case T_PAR_RIGHT:
                    return C_MORE;
                case ES_END:
                    return C_MORE;
                default:
                    return C_NONE;
            }
            break;
        case ES_ID:
        case ES_INT_LIT:
        case ES_FLOAT_LIT:
        case ES_STR:
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
                    return C_NONE ;
                case T_PAR_LEFT:
                    return C_NONE ;
                case T_PAR_RIGHT:
                    return C_MORE;
                case ES_END:
                    return C_MORE;
                default:
                    return C_NONE;
            }
            break;
        case T_PAR_LEFT:
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
                    return C_LESS ;
                case T_PAR_LEFT:
                    return C_LESS ;
                case T_PAR_RIGHT:
                    return C_EQ;
                case ES_END:
                    return C_NONE;
                default:
                    return C_NONE;
            }
            break;
        case T_PAR_RIGHT:
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
                    return C_NONE ;
                case T_PAR_LEFT:
                    return C_NONE ;
                case T_PAR_RIGHT:
                    return C_MORE;
                case ES_END:
                    return C_MORE;
                default:
                    return C_NONE;
            }
            break;
        case ES_END:
            switch ( tmp_stack_symbol ) {
                case ES_PLUS:
                case ES_MINUS:
                case ES_CON:
                    return C_LESS; 
                case ES_MUL:
                case ES_DIV:
                    return C_LESS;
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
                    return C_LESS ;
                case T_PAR_LEFT:
                    return C_LESS ;
                case T_PAR_RIGHT:
                    return C_NONE;
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
	}
}

int convert_to_type ( token_t * token ) {
    switch ( token->type ) {
    case T_VAR_ID:
        return check_type_of_var();
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
            *count = *count + 1;
        }
        tmp = tmp->next;
    }
}

int rule_test (int count, item_stack_t * op1, item_stack_t * op2, item_stack_t * op3) {
    exp_rules rule;
    if ( count == 1 ) {
        if ( op1->symbol == ES_ID || op1->symbol == ES_INT_LIT || op1->symbol == ES_FLOAT_LIT || op1->symbol == ES_STR ) {
            rule = R_ID;
        } else {
            rule = R_ERROR;
        }
    } else if ( count == 3 ) {
        if ( (op1->symbol == ES_LEFT_BRACKET) & (op2->symbol == ES_NON_TERM) & (op3->symbol == ES_RIGHT_BRACKET) ) {
            rule =  R_PAR;
        } else if ( op1->symbol == ES_NON_TERM && op3->symbol == ES_NON_TERM ) {
            switch ( op2->symbol )
            {
            case ES_PLUS:
                rule = R_ADD;
                break;
            case ES_MINUS:
                rule = R_ADD;
                break;
            case ES_CON:
                rule = R_ADD;
                break;
            case ES_MUL:
                rule = R_ADD;
                break;
            case ES_DIV:
                rule = R_ADD;
                break;
            case ES_EQ:
                rule = R_ADD;
                break;
            case ES_NEQ:
                rule = R_ADD;
                break;
            case ES_LEQ:
                rule = R_ADD;
                break;
            case ES_LTN:
                rule = R_ADD;
                break;
            case ES_MEQ:
                rule = R_ADD;
                break;
            case ES_MTN:
                rule = R_ADD;
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
    } //ТУТ НАДО ЕЩЕ ЭЛС ХАРМИМОВСКИЙ СПИЗДИ
    return NO_ERR;
} 

int expression (token_t * token) {
    int error_type;
    sstack_t * exp_stack;
    stack_init(exp_stack);
    item_stack_t * op_1;
    item_stack_t * op_2;
    item_stack_t * op_3;
    int tmp_sym;
    int tmp_type;
    bool found;
    int count;
    stack_push(exp_stack,ES_END,ET_UNDEFINED);
    while( ( convert_to_symbol(token) != ES_END ) & ( ( get_top(exp_stack) )->symbol != ES_END ) ) {
        switch (get_cond(token,exp_stack)) {
        case C_EQ:
            tmp_sym = convert_to_symbol(token);
            tmp_type = convert_to_type(token);
            stack_push(exp_stack,tmp_sym,tmp_type); // TUT PROVERKU DOBAV JESTLI NE VPADLU
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            break;
        case C_LESS:
            stack_push_after(exp_stack,ES_CATCH, ET_UNDEFINED);
            tmp_sym = convert_to_symbol(token);
            tmp_type = convert_to_type(token);
            stack_push(exp_stack,tmp_sym,tmp_type);
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            break;
        case C_MORE:
            found = find_catch(&count,exp_stack);
            if (found & ( count == 1)) {
                op_1 = exp_stack->top->next->next;
                op_2 = exp_stack->top->next;
                op_3 = exp_stack->top;
                if ( error_type = rule_test ( count, op_1, op_2, op_3 ) ) {
                    return error_type;
                }
            } else if ( found & ( count == 3 ) ) {
                op_1 = exp_stack->top;
                if ( error_type = rule_test ( count, op_1, NULL, NULL ) ) {
                    return error_type;
                }
            }
            else {
                return SYNTAX_ERR;
            }
            break;
        case C_NONE:
            return SYNTAX_ERR;  
            break;
        }
    }
    stack_dispose(exp_stack);
}