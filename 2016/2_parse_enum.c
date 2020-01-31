#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 1000

/* 处理一个 token，返回当前 token 的枚举值 */
int parse_token(char *token, int len, int index) {
    int i;
    for(i = 0; i < len && token[i] != '='; i++)
        putchar(*(token+i));

    if(token[i] == '=') {
        /* 陷阱：注意 i++，切换字符串所属，下标要调整 */
        i++;
        index = 0;
        for(; i < len && *(token + i) >= '0' && *(token + i) <= '9'; i++) {
            index *= 10;
            index += *(token + i) - '0';
        }
    }

    printf(" %d\n", index);
    return index;
}


int main(void)
{
    char *input = malloc(sizeof(char) * INPUT_SIZE);
    char *token;
    int index = 0;
    fgets(input, INPUT_SIZE, stdin);
    while(*input++ != '{')
        ;

    const char *whitespace = " \t\n,;}";
    for(token = strtok(input, whitespace);
            token != NULL;
            token = strtok(NULL, whitespace)) {
        index = parse_token(token, strlen(token), index);
        index++;
    }

    return EXIT_SUCCESS;
}
