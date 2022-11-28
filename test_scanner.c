#include "scanner.h"
#include "error.h"
void print_token ( token_t * token) {
    switch (token->type) {
	case T_EOL:
		printf("eol\n");
        break;
	case T_EOF:
		printf("eof\n");
        break;
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
	case T_DOT:
		printf(".\n");
        break;
	case T_COMMA:
		printf(",\n");
        break;
	case T_GREATER:
		printf(">\n");
        break;
	case T_GREATER_EQUAL:
		printf(">=\n");
        break;
	case T_LESS:
		printf("<\n");
        break;
	case T_LESS_EQUAL:
		printf("<=\n");
        break;
	case T_ASSIGN:
		printf("=\n");
        break;
	case T_NOT_EQUAL:
		printf("!==\n");
        break;
	case T_PAR_LEFT:
		printf("(\n");
        break;
	case T_PAR_RIGHT:
		printf(")\n");
        break;
	case T_BRACE_LEFT:
		printf("{\n");
        break;
	case T_BRACE_RIGHT:
		printf("}\n");
        break;
	case T_SEMICOLON:
		printf(";\n");
        break;
	case T_COLON:
		printf(":\n");
        break;
	case T_EQUAL:
		printf("===\n");
        break;
	case T_END_SYMBOL:
		printf("?>\n");
        break;
	case T_KW_ELSE:
		printf("else\n");
        break;
	case T_KW_FLOAT:
		printf("float\n");
        break;
	case T_KW_FUNCTION:
		printf("function\n");
        break;
	case T_KW_IF:
		printf("if\n");
        break;
	case T_KW_INT:
		printf("int\n");
        break;
	case T_KW_NULL:
		printf("null\n");
        break;
	case T_KW_RETURN:
		printf("return\n");
        break;
	case T_KW_STRING:
		printf("string\n");
        break;
	case T_KW_VOID:
		printf("void\n");
        break;
	case T_KW_WHILE:
		printf("whlie\n");
        break;
	case T_VAR_ID:
		printf("id : \t%s\n", token->data.string_c->str);
        break;
	case T_FUN_ID:
		printf("id : \t%s\n", token->data.string_c->str);
        break;
	case T_INT_VAL:
		printf("int-lit : \t%d\n", token->data.int_c);
		string s;
		if (str_init(&s)) {
			token->data.string_c = &s;
		}
        break;
	case T_DEC_VAL:
		printf("float_lit : \t%f\n", token->data.double_c);
		if (str_init(&s)) {
			token->data.string_c = &s;
		}
        break;
	case T_STRING_VAL:
		printf("string-lit : \t\"%s\"\n", token->data.string_c->str);
		if (str_init(&s)) {
			token->data.string_c = &s;
		}
        break;
	case T_START_SYMBOL:
		printf("<?php\n");
        break;
	default:
		printf("default : %d\n", token->type);
		break;
	}
}

int main() {
    token_t token;
	string s;
	if (str_init(&s)) {
		token.data.string_c = &s;
	}
    // int i = 3; 
    int error_type;
	set_source(stdin);
	while ((error_type = get_next_token(&token)) == 0 && token.type != T_EOF) {
		// printf("%d\n", token.type);
		print_token(&token);
		token.data.string_c = &s;
		// printf("t.d.s.l : %d\n", token.data->string_c->length);
	}
	str_free(&s);
	printf("%d\n",error_type);
	return error_type;
    // if (error_type == get_next_token(&token)) {
    //         printf("%d\n",error_type);
    //         return error_type;
    // }
    // do {
	// 	printf("hi\n");
	// 	printf("%d\n",error_type);
    //     print_token(&token);
    //     i--;
    // } while ((error_type == get_next_token(&token))==0);
    // printf("%d\n",error_type);
	return 0;
}