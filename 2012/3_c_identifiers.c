#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 301

int valid(char c)
{
    if(c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') 
            || (c >= '0' && 'c' <= 9))
        return 1;
    return 0;
}

/* 返回待处理的起始位置 */
int consume_invalid_chars(const char *s, int len, int pos) {
    for(; pos<len && !valid(s[pos]); pos++)
        ;
    return pos;
}

int consume_valid_chars(const char *s, int len, int pos) {
    for(; pos<len && valid(s[pos]); pos++)
        ;
    return pos;
}

int consume_quote(const char *s, int len, int pos) {
    pos++;
    for(; pos<len && s[pos] != '"'; pos++)
        ;
    return pos;
}

int check_if(const char *s, int len, int pos)
{
    if(pos + 2 < len && s[pos+1] == 'f' && !valid(s[pos+2])) {
        printf("if: %d\n", pos);
        return 1;
    }
    return 0;
}

int check_for(const char *s, int len, int pos)
{
    if(pos + 3 < len && s[pos+1] == 'o' && s[pos+2] == 'r' 
            && !valid(s[pos+3])) {
        printf("for: %d\n", pos);
        return 1;
    }
    return 0;
}

int check_while(const char *s, int len, int pos)
{
    if(pos + 5 < len && s[pos+1] == 'h' && s[pos+2] == 'i' 
            && s[pos+3] == 'l' && s[pos+4] == 'e' && !valid(s[pos+5])) {
        printf("while: %d\n", pos);
        return 1;
    }
    return 0;
}

int main(void)
{
    int len;
    int pos = 0, found;
    char *s = malloc(sizeof(char) * BUFFER_SIZE);
    fgets(s, BUFFER_SIZE, stdin);
    len = strlen(s);
    s[len-1] = '\0';

    while(pos < len) {
        pos = consume_invalid_chars(s, len, pos);
        if(pos < len) {
            switch(s[pos]) {
                case 'i':
                    found = check_if(s, len, pos);
                    if(found) 
                        pos += 2;
                    else
                        pos = consume_valid_chars(s, len, pos);
                    break;
                case 'w':
                    found = check_while(s, len, pos);
                    if(found) 
                        pos += 5;
                    else
                        pos = consume_valid_chars(s, len, pos);
                    break;
                case 'f':
                    found = check_for(s, len, pos);
                    if(found) 
                        pos += 3;
                    else
                        pos = consume_valid_chars(s, len, pos);
                    break;
                case '"':
                    pos = consume_quote(s, len, pos);
                    break;
                default:
                    pos = consume_valid_chars(s, len, pos);
                    break;
            }
        }
    }
}
