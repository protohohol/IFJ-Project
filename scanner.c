#include <ctype.h>
#include <string.h>
#include "scanner.h"

int Check_Keyword(char *s){
    for(int i = 0; i < 10; i++){
        if(strcmp(s, keywords[i])){
            return 1;
        }
    }
    return 0;
}
 
int main (int argc, char* argv[]) {
    char c; // responsible for reading each character
    Token_t token[1];
    int tokenCounter = 0; // ordinal number of the token
    while((c = getchar()) != -1){
        switch (token[tokenCounter].state){
            case 0:
                if(c == '$'){
                    token[tokenCounter].state = 1;
                    strncat(token[tokenCounter].text, c, 1); // appending the text of token 
                }
                else if(isdigit(c)){
                    token[tokenCounter].type = T_INT;
                    token[tokenCounter].state = 3;
                }
                else if(c == ':'){
                    token[tokenCounter].type = T_COLON;
                }
                else if(c == ';'){
                    token[tokenCounter].type = T_SEMICOLON;
                }
                else if(c == '{'){
                    token[tokenCounter].type = T_BRACE_LEFT;
                }
                else if(c == '}'){
                    token[tokenCounter].type = T_BRACE_RIGHT;
                }
                else if(c == '('){
                    token[tokenCounter].type = T_BRACKET_LEFT;
                }
                else if(c == ')'){
                    token[tokenCounter].type = T_BRACKET_RIGHT;
                }
                else if(c == '='){
                    token[tokenCounter].type = T_EQUAL;
                    token[tokenCounter].state = 4;
                }
                else if(c == '!'){
                    token[tokenCounter].state = 4;
                }
                else if(c == '<'){
                    token[tokenCounter].type = T_LESS;
                    token[tokenCounter].state = 5;
                }
                else if(c == '>'){
                    token[tokenCounter].type = T_GREATER;
                    token[tokenCounter].state = 5;
                }
            case 1:
                if(c == '_' || isalpha(c)){
                    token[tokenCounter].state = 2;
                }
            case 2:
                if(c == '_' || isalpha(c) || isdigit(c)){
                    token[tokenCounter].type = T_ID;
                }
            case 3:
                if(isdigit(c));

                else if(c == '.' || c == 'e' || c == 'E'){
                    token[tokenCounter].type = T_FLOAT;
                }
                else{
                    //error
                }
            case 4:
                if(c == '='){
                    token[tokenCounter].state = 5;
                }
                else{
                    //error
                }
            case 5:
                if(c == '='){
                    if(token[tokenCounter].type = T_EQUAL){
                        token[tokenCounter].type = T_EQUAL_EQUAL_EQUAL;
                    }
                    else if(token[tokenCounter].type = T_LESS){
                        token[tokenCounter].type = T_LESS_EQUAL;
                    }
                    else if(token[tokenCounter].type = T_GREATER){
                        token[tokenCounter].type = T_GREATER_EQUAL;
                    }
                    else{
                        token[tokenCounter].type = T_NOT_EQUAL_EQUAL;
                    }
                }
                else{
                    //error
                }

        }
    }
    return 0;
}