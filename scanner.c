#include "scanner.h"
#include "error.h"

FILE *source;
string *src_str;

void set_source(FILE *f)
{
    source = f;
}

void set_src_str(string *src) {
    src_str = src;
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
        if (!is_type(s, token)) {
            token->type = T_FUN_ID;
        }
        token->type = T_FUN_ID;
        return false;
    }
}

const int get_next_token(token_t *token) {
    if (source == NULL || src_str == NULL) {
        return ERROR_INTERNAL;
    }

    token->data.string_c = src_str;
    string l_s;
    string *s = &l_s;
    if (!str_init(s)) {
        return ERROR_INTERNAL;
    }
    
    int state = S_START;
    char c;
    char esc_str[4]; // for hexadecimal and octal escape symbols


    while (true) {
        c = getc(source);
        // str_clear(token->data.string_c);
        // printf("s len : %d\n", s->allocSize);
        // printf("c : %d\ns : %s\n", c, s->str);

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
                } else if (c == ',') {
                    token->type = T_COMMA;
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
                } else if (c == ')') {
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
                } else if (c == '/') {
                    state = S_COMMENT_START;
                } else {
                    str_free(s);
                    return LEX_ERR;
                }
                break;

            case (S_COMMENT_START):
                if (c == '/') {
                    state = S_COMMENT_LINE;
                } else if (c == '*') {
                    state = S_COMMENT_BLOCK;
                } else {
                    ungetc(c, source);
                    str_free(s);
                    token->type = T_DIV;
                    return NO_ERR;
                }
                break;

            case (S_COMMENT_LINE):
                if (c == EOF) {
                    ungetc(c, source);
                    state = S_START;
                } else if (c == '\n') {
                    state = S_START;
                }
                break;

            case (S_COMMENT_BLOCK):
                if (c == EOF) {
                    str_free(s);
                    return LEX_ERR;
                } else if (c == '*') {
                    state = S_COMMENT_BLOCK_END;
                }
                break;

            case (S_COMMENT_BLOCK_END):
                if (c == EOF) {
                    str_free(s);
                    return LEX_ERR;
                } else if (c == '/') {
                    state = S_START;
                } else {
                    state = S_COMMENT_BLOCK;
                }
                break;

            case (S_STRING):
                if (c > 31 && c != 34 && c != '\\') {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                } else if (c == '\"') {
                    // printf("hi\n");
                    // printf("t.d.s.l : \ns.l : %d\n", token->data->string_c->length, s->allocSize);
                    if (!str_copy_string(token->data.string_c, s)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    token->type = T_STRING_VAL;
                    str_free(s);
                    return NO_ERR;
                } else if (c == '$') {
                    str_free(s);
                    return LEX_ERR;
                } else if (c == '\\') {
                    // printf("@@hi1\n");
                    state = S_ESC;
                } else {
                    str_free(s);
                    return LEX_ERR;
                }
                break;

            case (S_ESC):
                if (c == '\\') {
                    if (!str_add_char(s, '\\')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_STRING;
                } else if (c == 'n') {
                    // printf("hi1\n");
                    if (!str_add_char(s, '\n')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_STRING;
                } else if (c == 'r') {
                    if (!str_add_char(s, '\r')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_STRING;
                } else if (c == 't') {
                    if (!str_add_char(s, '\t')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_STRING;
                } else if (c == 'v') {
                    if (!str_add_char(s, '\v')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_STRING;
                } else if (c == 'e') {
                    if (!str_add_char(s, '\e')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_STRING;
                } else if (c == 'f') {
                    if (!str_add_char(s, '\f')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_STRING;
                } else if (c == '$') {
                    if (!str_add_char(s, '$')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_STRING;
                } else if (c == '\"') {
                    if (!str_add_char(s, '\"')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_STRING;
                } else if ((c >= '0' && c <= '9')) {
                    esc_str[0] = c;
                    state = S_ESC_OCT_START;
                } else if (c == 'x') {
                    state = S_ESC_HEX_START;
                } else {
                    if (!str_add_char(s, '\\')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_STRING;
                }
                break;

            case (S_ESC_OCT_START):
                if ((c >= '0' && c <= '9')) {
                    esc_str[1] = c;
                    state = S_ESC_OCT;
                } else {
                    ungetc(c, source);
                    if (!str_add_char(s, '\\')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    if (!str_add_char(s, esc_str[0])) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_STRING;
                }
                break;

            case (S_ESC_OCT):
                if (c >= '0' && c <= '7' && esc_str[0] >= '0' && esc_str[0] <= '3' && esc_str[1] >= '0' && esc_str[1] <= '7') {
                    esc_str[2] = c;
                    int tmp = ((esc_str[0] - '0') * 8 * 8) + ((esc_str[1] - '0') * 8) + (esc_str[2] - '0');
                    if (!str_add_char(s, (char)tmp)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                } else {
                    ungetc(c, source);
                    ungetc(c, source);
                    if (!str_add_char(s, '\\')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    if (!str_add_char(s, esc_str[0])) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                }
                state = S_STRING;
                break;

            case (S_ESC_HEX_START):
                if (tolower(c) >= 'a' && tolower(c) <= 'f') {
                    esc_str[0] = c;
                    state = S_ESC_HEX;
                } else {
                    ungetc(c, source);
                    if (!str_add_char(s, '\\')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    if (!str_add_char(s, 'x')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_STRING;
                }
                break;

            case (S_ESC_HEX):
                if (tolower(c) >= 'a' && tolower(c) <= 'f') {
                    esc_str[1] = c;
                    int tmp[2];
                    for (int i = 0; i < 2; i++) {
                        if (esc_str[i] >= '0' && esc_str[i] <= '9') {
                            tmp[i] = esc_str[i] - '0';
                        } else {
                            tmp[i] = tolower(esc_str[i]) - 'a' + 10;
                        }
                    }
                    if (!str_add_char(s, (char)((tmp[0] * 16) + tmp[1]))) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                } else {
                    ungetc(c, source);
                    ungetc(c, source);
                    if (!str_add_char(s, '\\')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    if (!str_add_char(s, 'x')) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                }
                state = S_STRING;
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
                    // printf("t.d.s.l : %d\n", token->data->string_c->length);
                    // token->data.int_c = atoi(s->str);
                    if (!str_copy_string(token->data.string_c, s)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    str_free(s);
                    return NO_ERR;
                }
                break;

            case (S_DEC_START):
                if (isdigit(c)) {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_DEC;
                } else if (c == '-' || c == '+') {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    state = S_EXP;
                } else {
                    str_free(s);
                    return LEX_ERR;
                }
                break;

            case (S_EXP):
                if (isdigit(c)) {
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
                    // token->data.double_c = strtod(s->str, NULL);
                    if (!str_copy_string(token->data.string_c, s)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
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
                    if (!str_copy_string(token->data.string_c, s)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                    str_free(s);
                    return NO_ERR;
                }
                break;

            case (S_START_SYMBOL):
                // printf("c : %c\ts : %s\tlen : %d\n", c, s->str, s->length);
                if (s->length < 5) {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                } else if (!str_cmp_const_str(s, "<?php")) {
                    if (c == '/' || isspace(c)) {
                        ungetc(c, source);
                    } else {
                        str_free(s);
                        return SYNTAX_ERR;
                    }
                    if (ftell(source) != 5) {
                        // printf("ftell : %ld\n", ftell(source));
                        str_free(s);
                        return SYNTAX_ERR;
                    }
                    token->type = T_START_SYMBOL;
                    state = S_START;
                    // token->type = T_START_SYMBOL;
                    // str_free(s);
                    // return NO_ERR;
                } else {
                    str_free(s);
                    return LEX_ERR;
                }
                break;

            // case (S_START_SYMBOL_COMMENT):
            //     if (c == '/') {
            //         state = S_START_SYMBOL_L_C;
            //     } else if (c == '*') {
            //         state = S_START_SYMBOL_B_C;
            //     } else {
            //         str_free(s);
            //         return LEX_ERR;
            //     }

            // case (S_START_SYMBOL_L_C) {
            //     if (c == EOL) {
            //         state = S_START_SYMBOL_CONT;
            //     } else {

            //     }
            // }

            case (S_END_SYMBOL):
                if (c == '>') {
                    if (getc(source) != EOF) {
                        str_free(s);
                        return SYNTAX_ERR;
                    }
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
                    ungetc(c, source);
                    str_free(s);
                    return NO_ERR;
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

            // case (S_KW_FUN_START):
            //     if(isalpha(c) || c == '_') {
            //         if (!str_add_char(s, c)) {
            //             str_free(s);
            //             return ERROR_INTERNAL;
            //         }
            //         state = S_KW_FUN;
            //     } else {
            //         ungetc(c, source);
            //         str_free(s);
            //         return LEX_ERR;
            //     }
            //     break;

            case (S_KW_FUN):
                if (isalnum(c) || c == '_') {
                    if (!str_add_char(s, c)) {
                        str_free(s);
                        return ERROR_INTERNAL;
                    }
                } else if (token->type == T_START_SYMBOL) {
                    if (s->length < 29) {
                        if (!str_add_char(s, c)) {
                            str_free(s);
                            return ERROR_INTERNAL;
                        }
                    } else {
                        // printf("s : %s\n", s->str);
                        if (!str_cmp_const_str(s, "<?phpdeclare(strict_types=1);")) {
                            str_free(s);
                            token->type = T_PROLOG;
                            return NO_ERR;
                        } else {
                            str_free(s);
                            return SYNTAX_ERR;
                        }
                    }
                } else {
                    ungetc(c, source);
                    if (!is_keyword(s, token) && !is_type(s, token)) {
                        if (!str_copy_string(token->data.string_c, s)) {
                            str_free(s);
                            return ERROR_INTERNAL;
                        }
                    }
                    str_free(s);
                    return NO_ERR;
                }
                break;
        }
    }
}