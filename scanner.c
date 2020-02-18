#include <stdio.h>
#include <ctype.h>
#include <string.h>
int isalphabet(char ch){
    if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) return 1;
    else return 0;
}
int main(void)
{
    FILE *fp = fopen("source.txt", "r");
    char ch;
    char tkval[32]="";
    int tkidx = 0;
    int state = 0, flag = 1;

    ch = fgetc(fp);
    while (flag) {
        switch (state) {
        case 0:
            if (ch==' ' || ch == '\t' || ch == '\n') {
                ch = fgetc(fp);
                state = 0;
            }
            else if (isalpha(ch)!=0) {
                tkval[tkidx++] = ch;
                state = 1;
                ch = fgetc(fp);
                if(ch == ' '){
                    state = 9;
                    tkval[tkidx] = '\0'; tkidx = 0;
                    printf("CLIT <state=%d>: %s\n", state, tkval);
                    state = 0;
                }
            }
            ///this block recognizes real and numeric
            else if(isdigit(ch) != 0){
                tkval[tkidx++] = ch;
                state = 3;
                ch = fgetc(fp);
            }
            ///opening parenthesis
            else if(ch == '('){
                tkval[tkidx++] = ch;
                state = 10;
                tkval[tkidx] = '\0'; tkidx = 0;
                printf("LPT <state=%d>: %s\n", state, tkval);
                ch = fgetc(fp);
                state = 0;
            }
            ///closing parenthesis
            else if(ch == ')'){
                tkval[tkidx++] = ch;
                state = 11;
                tkval[tkidx] = '\0'; tkidx = 0;
                printf("RPT <state=%d>: %s\n", state, tkval);
                ch = fgetc(fp);
                state = 0;
            }
            ///opening curly brace
            else if(ch == '{'){
                tkval[tkidx++] = ch;
                state = 10;
                tkval[tkidx] = '\0'; tkidx = 0;
                printf("LCB <state=%d>: %s\n", state, tkval);
                ch = fgetc(fp);
                state = 0;
            }
            ///closing curly brace
            else if(ch == '}'){
                tkval[tkidx++] = ch;
                state = 10;
                tkval[tkidx] = '\0'; tkidx = 0;
                printf("RCB <state=%d>: %s\n", state, tkval);
                ch = fgetc(fp);
                state = 0;
            }
            ///opening Square bracket
            else if(ch == '['){
                tkval[tkidx++] = ch;
                state = 10;
                tkval[tkidx] = '\0'; tkidx = 0;
                printf("LSB <state=%d>: %s\n", state, tkval);
                ch = fgetc(fp);
                state = 0;
            }
            ///ending Square bracket
            else if(ch == ']'){
                tkval[tkidx++] = ch;
                state = 10;
                tkval[tkidx] = '\0'; tkidx = 0;
                printf("RSB <state=%d>: %s\n", state, tkval);
                ch = fgetc(fp);
                state = 0;
            }
            ///semicolon
            else if(ch == ';'){
                tkval[tkidx++] = ch;
                state = 10;
                tkval[tkidx] = '\0'; tkidx = 0;
                printf("SEMI <state=%d>: %s\n", state, tkval);
                ch = fgetc(fp);
                state = 0;
            }

            ///this block is for EOF
            else if (feof(fp)) {
                printf("Done!\n");
                flag = 0;
            }
            ///error state
            else{
                tkval[tkidx++] = ch;
                state = 99;
            }
        break;

        ///for SLIT, CLIT and ID
        case 1:
            if (isalphabet(ch)) {
                tkval[tkidx++] = ch;
                state = 1;
                ch = fgetc(fp);
            } else if(isdigit(ch)){
                tkval[tkidx++] = ch;
                state = 7;
                ch = fgetc(fp);
            }
            else {
                state = 2;
            }
        break;

        ///If ID found then print
        case 2:
            tkval[tkidx] = 0; tkidx = 0;
            printf("SLIT <state=%d>: %s\n", state, tkval);
            state = 0;
        break;

        case 3:
            if (isdigit(ch) != 0) {
                tkval[tkidx++] = ch;
                state = 3;
                ch = fgetc(fp);
            } else if(ch == '.'){
                tkval[tkidx++] = ch;
                state = 5;
                ch = fgetc(fp);
            }else state = 4;
        break;

        case 4:
                tkval[tkidx] = '\0'; tkidx = 0;
                printf("ILIT <state=%d>: %s\n", state, tkval);
                state = 0;
            break;

        case 5:
            if(isdigit(ch) != 0){
                tkval[tkidx++] = ch;
                state = 5;
                ch = fgetc(fp);
            }else state = 6;
            break;

        case 6:
                tkval[tkidx] = '\0'; tkidx = 0;
                printf("RLIT <state=%d>: %s\n", state, tkval);
                state = 0;
            break;

        case 7:
           if (isalnum(ch)!=0) {
                tkval[tkidx++] = ch;
                state = 7;
                ch = fgetc(fp);
            } else {
                state = 8;
            }
            break;

         case 8:
            tkval[tkidx] = '\0'; tkidx = 0;
            printf("ID <state=%d>: %s\n", state, tkval);
            state = 0;
            break;

        case 99:
            tkval[tkidx] = 0; tkidx = 0;
            printf("ERR <state=%d>(ERROR FOR THE CHAR): %s\n", state, tkval);
            flag = 0;
        break;


        }///switch ends here

    }///while ends here

    return 0;
}

