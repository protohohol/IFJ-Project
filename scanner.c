#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "scanner.h"
#include "str.h"
#include "error.h"

FILE *source;

void set_source(FILE *f)
{
    source = f;
}

bool is_keyword(string *s, token_t *token) {
    if (!str_cmp_const_str(s, "else")) {
        token->type = T_KW_ELSE;
        return true;
    } else if (!str_cmp_const_str(s, "function")) {
        token->type = T_KW_FUNCTION;
        return true;
    } else if (!str_cmp_const_str(s, "if")) {
        token->type = T_KW_IF;
        return true;
    } else if (!str_cmp_const_str(s, "null")) {
        token->type = T_KW_NULL;
        return true;
    } else if (!str_cmp_const_str(s, "return")) {
        token->type = T_KW_RETURN;
        return true;
    } else if (!str_cmp_const_str(s, "void")) {
        token->type = T_KW_VOID;
        return true;
    } else if (!str_cmp_const_str(s, "while")) {
        token->type = T_KW_WHILE;
        return true;
    } else {
        token->type = T_FUN_ID;
        return false;
    }
}

bool is_type(string *s, token_t *token) {
    if (!str_cmp_const_str(s, "float")) {
        token->type = T_KW_FLOAT;
        return true;
    } else if (!str_cmp_const_str(s, "int")) {
        token->type = T_KW_INT;
        return true;
    } else if (!str_cmp_const_str(s, "string")) {
        token->type = T_KW_STRING;
        return true;
    } else {
        return false;
    }
}

const int get_next_token(token_t *token) {
    if (source == NULL) {
        return ERROR_INTERNAL;
    }

    string *s;
    if (!str_init(s)) {
        return ERROR_INTERNAL;
    }
    
    int state = S_START;
    char c;

    while (true) {
        c = getc(source);

        switch (state) {
            case (S_START):
                if (c == '+') {
                    token->type = T_ADD;
                    str_free(s);
                    return NO_ERR;
                } else if (isspace(c)) {
                    state = S_START;
                } else if (c == '-') {
                    token->type = T_SUB;
                    str_free(s);
                    return NO_ERR;
                } else if (c == '*') {
                    token->type = T_MUL;
                    str_free(s);
                    return NO_ERR;
                } else if (c == '.') {
                    token->type = T_DOT;
                    str_free(s);
                    return NO_ERR;
                } else if (c == ';') {
                    token->type = T_SEMICOLON;
                    str_free(s);
                    return NO_ERR;
                } else if (c == ':') {
                    token->type = T_COLON;
                    str_free(s);
                    return NO_ERR;
                } else if (c == '(') {
                    token->type = T_PAR_LEFT;
                    str_free(s);
                    return NO_ERR;
                } else if (c == '(') {
                    token->type = T_PAR_RIGHT;
                    str_free(s);
                    return NO_ERR;
                } else if (c == '{') {
                    token->type = T_BRACE_LEFT;
                    str_free(s);
                    return NO_ERR;
                } else if (c == '}') {
                    token->type = T_BRACE_RIGHT;
                    str_free(s);
                    return NO_ERR;
                } else if (c == '=') {
                    state = S_EQUAL;
                } else if (c == '<') {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_LESS;
                } else if (c == '>') {
                    state = S_GREATER;
                } else if (c == '!') {
                    state = S_NOT;
                } else if (c == '$') {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_VAR_ID;
                } else if (isalpha(c) || c == '_') {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_KW_FUN;
                } else if (isdigit(c)) {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_INT_DEC;
                } else if (c == '?') {
                    state = S_END_SYMBOL;
                } else if (c == EOF) {
                    token->type = T_EOF;
                    str_free(s);
                    return NO_ERR;
                } else if (c == '\"') {
                    state = S_STRING;
                } else {
                    str_free(s);
                    return LEX_ERR;
                }
                break;

            case (S_STRING):
                
                break;

            case (S_INT_DEC):
                if (isdigit(c)) {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                } else if (tolower(c) == 'e') {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_DEC_START;
                } else if (c == '.') {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_DEC;
                } else {
                    ungetc(c, source);
                    token->type = T_INT_VAL;
                    token->data->int_c = atoi(s->str);
                    str_free(s);
                    return NO_ERR;
                }
            break;

            case (S_DEC_START):
                if (isdigit(c) || c == '-' || c == '+') {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_DEC;
                } else {
                    str_free(s);
                    return LEX_ERR;
                }
            break;

            case (S_DEC):
                if (isdigit(c)) {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                } else {
                    ungetc(c, source);
                    token->type = T_DEC_VAL;
                    token->data->double_c = strtod(s->str, NULL);
                    str_free(s);
                    return NO_ERR;
                }
            break;

            case (S_VAR_ID):
                if (isalnum(c) || c == '_') {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                } else {
                    ungetc(c, source);
                    token->type = T_VAR_ID;
                    if (!str_copy_string(token->data->string_c, s)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    str_free(s);
                    return NO_ERR;
                }
                break;

            case (S_START_SYMBOL):
                if (!isspace(c)) {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_START_SYMBOL;
                } else if (!str_cmp_const_str(s, "<?php")) {
                    token->type = T_START_SYMBOL;
                    str_free(s);
                    return NO_ERR;
                } else {
                    str_free(s);
                    return ERROR_INTERNAL;
                }
                break;

            case (S_END_SYMBOL):
                if (c == '>') {
                    token->type = T_END_SYMBOL;
                    str_free(s);
                    return NO_ERR;
                } else if (isalpha(c)) {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_KW_TYPE;
                } else {
                    str_free(s);
                    return ERROR_INTERNAL;
                }
                break;

            case (S_KW_TYPE):
                if (isalpha(c)) {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                } else {
                    ungetc(c, source);
                    if (!is_type(s, token)) {
                        str_free(s);
                        return LEX_ERR;
                    } else {
                        str_free(s);
                        return NO_ERR;
                    }
                }
                break;
            
            case (S_EQUAL):
                if (c == '=') {
                    state = S_EQUAL_EQUAL;
                } else {
                    ungetc(c, source);
                    token->type = T_ASSIGN;
                    str_free(s);
                    return NO_ERR;
                }
                break;

            case (S_EQUAL_EQUAL):
                if (c == '=') {
                    token->type = T_EQUAL;
                    str_free(s);
                    return NO_ERR;
                } else {
                    return LEX_ERR;
                }
                break;

            case (S_LESS):
                if (c == '=') {
                    token->type = T_LESS_EQUAL;
                    str_free(s);
                    return NO_ERR;
                } else if (c == '?') {
                    state = S_START_SYMBOL;
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                }
                else {
                    ungetc(c, source);
                    token->type = T_LESS;
                    str_free(s);
                    return NO_ERR;
                }
                break;

            case (S_GREATER):
                if (c == '=') {
                    token->type = T_GREATER_EQUAL;
                    str_free(s);
                    return NO_ERR;
                } else {
                    ungetc(c, source);
                    token->type = T_GREATER;
                    str_free(s);
                    return NO_ERR;
                }
                break;

            case (S_NOT):
                if (c == '=') {
                    state = S_NOT_EQUAL;
                } else {
                    return LEX_ERR;
                }
                break;

            case (S_NOT_EQUAL):
                if (c == '=') {
                    token->type = T_NOT_EQUAL;
                    str_free(s);
                    return NO_ERR;
                } else {
                    return LEX_ERR;
                }
                break;

            case (S_KW_FUN_START):
                if(isalpha(c) || c == '_') {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_KW_FUN;
                } else {
                    ungetc(c, source);
                    str_free(s);
                    return LEX_ERR;
                }
                break;

            case (S_KW_FUN):
                if (isalnum(c) || c == '_') {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                } else {
                    ungetc(c, source);
                    if (!is_keyword(s, token) || !is_type(s, token)) {
                        if (!str_copy_string(token->data->string_c, s)) {
                            str_free(s);
                            return ERROR_INTERNAL;
                        }
                    }
                    str_free(s);
                    return NO_ERR;
                }
                break;

            case (S_INT):
                if (isdigit(c)) {
                    state = S_INT;
                } else if (c == '.') {
                    state = S_FLOAT;
                } else if (c == 'e' || c == 'E') {
                    state = S_EXP;
                } else if (c == ' ') {
                    token->type = T_KW_INT;
                    str_free(s);
                    return NO_ERR;
                } else {
                    return LEX_ERR;
                }
                break;

            case (S_FLOAT):
                if (isdigit(c)) {
                    state = S_FLOAT;
                } else if (c == ' ') {
                    token->type = T_KW_FLOAT;
                    str_free(s);
                    return NO_ERR;
                } else {
                    return LEX_ERR;
                }
                break;

            case (S_EXP):
                if (isdigit(c) || c == '+' || c == '-') {
                    state = S_EXP_END;
                } else {
                    return LEX_ERR;
                }
                break;

            case (S_EXP_END):
                if(isdigit(c)) {
                    state = S_EXP_END;
                } else if (c == ' ') {
                    token->type = T_KW_FLOAT;
                    str_free(s);
                    return NO_ERR;
                } else {
                    return LEX_ERR;
                }
                break;
        }
    }
}