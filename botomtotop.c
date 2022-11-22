#include "botomtotop.h"
int error_type;




exp_cond get_cond (token_t *token) {
    return 1;
}

exp_stack_symbol convert_to_symbol (token_t * token){
    return 1;
}
exp_type convert_to_type (token_t * token){
    return 1;
}

int expression (token_t * token) {
    sstack_t * exp_stack;
    stack_init(exp_stack);
    exp_stack_symbol tmp_sym;
    exp_type tmp_type;
    stack_push(exp_stack,ES_END,ET_UNDEFINED);
    while( ( token->type != T_SEMICOLON ) & ( ( get_top(exp_stack) )->symbol != ES_START ) ) {
        switch (get_cond(token))
        {
        case C_EQ:
            tmp_sym = convert_to_symbol(token);
            tmp_type = convert_to_type(token);
            stack_push(exp_stack,tmp_sym,tmp_type); // TUT PROVERKU DOBAV JESTLI NE VPADLU
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            break;
        case C_LESS:
            tmp_sym = convert_to_symbol(token);
            tmp_type = convert_to_type(token);
            stack_push(exp_stack,tmp_sym,tmp_type);
            if (error_type = get_next_token(token)) {
                return error_type;
            }
            break;
        case C_MORE:
            
            break;
        case C_NONE:
            return SYNTAX_ERR;
            break;
        default:
            break;
        }

    }
}