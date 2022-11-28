#include "scanner.h"
#include "error.h"
void print_token ( token_t * token) {
    switch (token->type) {
	case T_ADD:
		printf("+\n");
        break;
	case T_SUB:
		printf("-\n");
        break;
	case T_MUL:
		printf("*\n");
        break;
	case T_DIV:
		printf("/\n");
        break;
	case T_ASSIGN:
		printf("=\n");
        break;
	case T_NOT_EQUAL:
		printf("!==\n");
        break;
	case T_LESS_EQUAL:
		printf("<=\n");
        break;
	case T_LESS:
		printf("<\n");
        break;
	case T_GREATER_EQUAL:
		printf(">=\n");
        break;
	case T_GREATER:
		printf(">\n");
        break;
	case T_PAR_LEFT:
		printf("(\n");
        break;
	case T_PAR_RIGHT:
		printf(")\n");
        break;
	case T_VAR_ID:
		printf("id\n");
        break;
	case T_INT_VAL:
		printf("int-lit\n");
        break;
	case T_DEC_VAL:
		printf("float_lit\n");
        break;
	case T_STRING_VAL:
		printf("string-lit\n");
        break;
	}
}

int main(){
    token_t token;
    int i = 3; 
    int error_type;
    if (error_type = get_next_token(&token)) {
            printf("%d\n",error_type);
            return error_type;
    }
    do {
        print_token(&token);
        i--;
    } while ((error_type = get_next_token(&token))==0);
    printf("%d\n",error_type);
}