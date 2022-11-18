#include <stdio.h>
#include <ctype.h>
#include "scanner.h"
#include "str.h"
#include "error.h"

FILE *source;

void set_source(FILE *f)
{
    source = f;
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
                    state = S_LESS;
                } else if (c == '>') {
                    state = S_GREATER;
                } else if (c == '!') {
                    state = S_NOT;
                } else if (c == '$') {
                    state = S_VAR_ID_1;
                }
            
            case (S_EQUAL):
                if (c == '=') {
                    state = S_EQUAL_EQUAL;
                } else {
                    ungetc(c, source);
                    token->type = T_ASSIGN;
                    str_free(s);
                    return NO_ERR;
                }

            case (S_EQUAL_EQUAL):
                if (c == '=') {
                    token->type = T_EQUAL;
                    str_free(s);
                    return NO_ERR;
                } else {
                    return LEX_ERR;
                }

            case (S_LESS):
                if (c == '=') {
                    token->type = T_LESS_EQUAL;
                    str_free(s);
                    return NO_ERR;
                } else {
                    ungetc(c, source);
                    token->type = T_LESS;
                    str_free(s);
                    return NO_ERR;
                }

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

            case (S_NOT):
                if (c == '=') {
                    state = S_NOT_EQUAL;
                } else {
                    return LEX_ERR;
                }

            case (S_NOT_EQUAL):
                if (c == '=') {
                    token->type = T_NOT_EQUAL;
                    str_free(s);
                    return NO_ERR;
                } else {
                    return LEX_ERR;
                }

            case (S_VAR_ID_1):
                if (isalpha(c)) {
                    state = S_VAR_ID_END;
                } else{
                    return LEX_ERR;
                }

            case (S_VAR_ID_END):
                if (isalpha(c) || isdigit(c) || c == '_') {
                    state = S_VAR_ID_END;
                } else {
                    token->type = T_VAR_ID;
                    str_free(s);
                    return NO_ERR;
                }
        }
    }
}

// int Check_Keyword(char *s) {
//     for(int i = 0; i < 10; i++) {
//         if (strcmp(s, keywords[i])) {
//             return 1;
//         }
//     }
//     return 0;
// }

// int Check_TypeID(char *s) {
//     for(int i = 0; i < 3; i++) {
//         if (strcmp(s, typeID[i])) {
//             return 1;
//         }
//     }
//     return 0;
// }
 
// int main (int argc, char* argv[]) {
//     char c; // responsible for reading each character
//     Token_t token[1];
//     int tokenCounter = 0; // ordinal number of the token
//     while((c = getchar()) != -1) {
//         switch (token[tokenCounter].state) {
//             case 0:
//                 if (c == '$') {
//                     token[tokenCounter].state = 1;
//                     strncat(token[tokenCounter].text, c, 1); // appending the text of token 
//                 }
//                 else if (isdigit(c)) {
//                     token[tokenCounter].type = T_INT;
//                     token[tokenCounter].state = 3;
//                 }
//                 else if (c == ':') {
//                     token[tokenCounter].type = T_COLON;
//                 }
//                 else if (c == ';') {
//                     token[tokenCounter].type = T_SEMICOLON;
//                 }
//                 else if (c == '{') {
//                     token[tokenCounter].type = T_BRACE_LEFT;
//                 }
//                 else if (c == '}') {
//                     token[tokenCounter].type = T_BRACE_RIGHT;
//                 }
//                 else if (c == '(') {
//                     token[tokenCounter].type = T_BRACKET_LEFT;
//                 }
//                 else if (c == ')') {
//                     token[tokenCounter].type = T_BRACKET_RIGHT;
//                 }
//                 else if (c == '=') {
//                     token[tokenCounter].type = T_EQUAL;
//                     token[tokenCounter].state = 4;
//                 }
//                 else if (c == '!') {
//                     token[tokenCounter].state = 4;
//                 }
//                 else if (c == '<') {
//                     token[tokenCounter].type = T_LESS;
//                     token[tokenCounter].state = 5;
//                 }
//                 else if (c == '>') {
//                     token[tokenCounter].type = T_GREATER;
//                     token[tokenCounter].state = 5;
//                 }
//                 else if (c == '+') {
//                     token[tokenCounter].type = T_PLUS;
                    
//                 }
//                 else if (c == '-') {
//                     token[tokenCounter].type = T_MINUS; 
//                 }
//                 else if (c == '*') {
//                     token[tokenCounter].type = T_STAR; 
//                 }
//                 else if (c == '/') {
//                     token[tokenCounter].state = 6;
//                 }
//                 else if (c == '?') {
//                     token[tokenCounter].state = 7;
//                 }
//             case 1:
//                 if (c == '_' || isalpha(c)) {
//                     token[tokenCounter].state = 2;
//                 }
//             case 2:
//                 if (c == '_' || isalpha(c) || isdigit(c)) {
//                     token[tokenCounter].type = T_ID;
//                 }
//             case 3:
//                 if (isdigit(c));

//                 else if (c == '.' || c == 'e' || c == 'E') {
//                     token[tokenCounter].type = T_FLOAT;
//                 }
//                 else {
//                     // error
//                 }
//             case 4:
//                 if (c == '=') {
//                     token[tokenCounter].state = 5;
//                 }
//                 else {
//                     // error
//                 }
//             case 5:
//                 if (c == '=') {
//                     if (token[tokenCounter].type == T_EQUAL) {
//                         token[tokenCounter].type = T_EQUAL_EQUAL_EQUAL;
//                     }
//                     else if (token[tokenCounter].type == T_LESS) {
//                         token[tokenCounter].type = T_LESS_EQUAL;
//                     }
//                     else if (token[tokenCounter].type == T_GREATER) {
//                         token[tokenCounter].type = T_GREATER_EQUAL;
//                     }
//                     else {
//                         token[tokenCounter].type = T_NOT_EQUAL_EQUAL;
//                     }
//                 }
//                 else {
//                     // error
//                 }
//             case 6:
//                 if (c == '/') {
//                         // its a comment
//                 }
//                 else {
//                     token[tokenCounter].type = T_SLASH; 
//                 }
//             case 7:
//                 if (c == '>') {
//                     token[tokenCounter].type = T_END_SYMBOL;
//                 }
//                 else if (isalpha(c)) {
//                     strncat(token[tokenCounter].text, c, 1);
//                 }
//                 else {
//                     if (Check_TypeID(token[tokenCounter].text) == 1) {
                        
//                     }
//                 }


//         }
//     }
//     return 0;
// }