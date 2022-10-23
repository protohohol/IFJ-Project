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
    int state = 0; // states of finite-state machine
    Token_t token[1];
    int tokenCounter = 0; // ordinal number of the token
    while((c = getchar()) != -1){
        switch (state){
            case 0:
                if(c == '$'){
                    state = 1;
                    strncat(token[tokenCounter].text, c, 1); // appending the text of token 
                }
                if(isdigit(c)){
                    state = 3;
                }
            case 1:
                if(c == '_' || isalpha(c)){
                    state = 2;
                }
            case 2:
                if(c == '_' || isalpha(c) || isdigit(c)){
                    // token[tokenCounter].type = VARIABLE;
                }
        }
    }
    return 0;
}