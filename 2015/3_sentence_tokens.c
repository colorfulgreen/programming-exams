#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 10000
#define MAX_WORD_COUNT 1000

char *tokens[MAX_WORD_COUNT];
int n_tokens = 0;

int valid(char ch) 
{
    if ((ch >= 'a' && ch <= 'z') ||
            (ch >= 'A' && ch <= 'Z') ||
            (ch >= '0' && ch <= '9'))
        return 1;
    return 0;
}


void insertion_sort(char **tokens, int n_tokens)
{
    char *tmp;
    int i, j;
    for(i=0; i<n_tokens; i++) {
        tmp = tokens[i];
        for(j=i; j>1 && strcmp(tokens[j-1], tmp) > 0; j--)  /* NOTE 库函数 strcmp，不用自己手写 */
            tokens[j] = tokens[j-1];
        tokens[j] = tmp;
    }
}


void parse_tokens_in_line(char *line, int len)
{
    int start = 0, pos = 0;
    while(start < len) {
        for(; start < len && !valid(line[start]);start++)
            ;
        pos = start;
        for(; pos < len && valid(line[pos]); pos++)
            ;
        /* 陷阱：不要把空字符串拷贝到 tokens 中 */
        if(pos - start != 0)
            tokens[n_tokens++] = strndup(line+start, pos-start);
        start = pos;
    }
}

int main(void)
{
    /* 将输入文本解析为 tokens */
    char *line;
    line = malloc(sizeof(char) * MAX_LINE_SIZE);
    while(fgets(line, MAX_LINE_SIZE, stdin) != NULL) { /* NOTE fgets 遇到 EOF 返回 NULL */
        parse_tokens_in_line(line, strlen(line));
    }
    if(n_tokens == 0)
        return EXIT_SUCCESS;
    
    /* 将 tokens 排序 */
    insertion_sort(tokens, n_tokens);

    /* 输出排重结果 */
    printf("%s\n", tokens[0]);
    for(int i=1; i<n_tokens; i++) {
        if(strcmp(tokens[i], tokens[i-1]) == 0)
            continue;
        printf("%s\n", tokens[i]);
    }

    return EXIT_SUCCESS;
}
