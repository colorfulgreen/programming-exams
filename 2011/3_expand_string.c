#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

#define __DEBUG 1

void expand(char start, char end) 
{
    start++;
    for(; start<=end; start++)
        printf("%c", start);

    return;
}


void check_expand(char start, char end)
{
    if(start >= 'a' && start <= 'z' && end >= 'a' && end <= 'z')
        expand(start, end);
    else if(start >= 'A' && start <= 'Z' && end >= 'A' && end <= 'Z')
        expand(start, end);
    else if(start >= '0' && start <= '9' && end >= '0' && end <= '9')
        expand(start, end);
    else {
        printf("-%c", end);
    }

    return;
}


int main(void)
{
#if __DEBUG
    freopen("3_data", "r", stdin);
#endif

    int len;
    char *string = malloc(sizeof(char) * BUFFER_SIZE);
    fgets(string, BUFFER_SIZE, stdin);
    len = strlen(string);
    string[len-1] = '\0';

    for(int pos=0; pos<len; ) {
        if(string[pos] != '-') {
            putchar(string[pos]);
            pos+=1;
        }
        else if(pos-1>=0 && pos+1<len) {
            check_expand(string[pos-1], string[pos+1]);
            pos+=2;
        }
        else { /* 特殊情形：- 出现在第一个字符或最后一个字符 */
            putchar(string[pos]);
            pos+=1;
        }

    }
    putchar('\n');
    
    return EXIT_SUCCESS;
}
