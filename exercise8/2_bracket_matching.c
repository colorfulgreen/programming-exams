#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 80

char stack[80];
int sp=0;

int is_empty() {
    if(sp == 0)
        return 1;
    return 0;
}

void push(char ch) {
    stack[sp++] = ch;
}

void pop() {
    if(!is_empty())
        sp--;
}

char top() {
    if(!is_empty()) 
        return stack[sp-1];
    return '\0';
}

int main(void)
{
    char s[81];
    int len, match = 1;
    FILE *in, *out;
    in = fopen("correct.in", "r");
    out = fopen("correct.out", "w");
    fscanf(in, "%s", s);
    for(int i=0; i<strlen(s); i++) {
        switch(s[i]) {
            case '(':
            case '[':
            case '{':
                push(s[i]);
                break;
            case ')':
                if('(' == top()) 
                    pop();
                else
                    match = 0;
                break;
            case ']':
                if('[' == top()) 
                    pop();
                else
                    match = 0;
                break;
            case '}':
                if('{' == top())
                    pop();
                else
                    match = 0;
                break;
        }
        if(!match)
            break;
    }
    if(match && is_empty()) {
        fprintf(out, "True\n");
    }
    else
        fprintf(out, "False\n");

    return 0;
}
