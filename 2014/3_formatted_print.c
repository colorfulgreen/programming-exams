#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 101
#define MAX_N_TOKENS 50

char *tokens[MAX_N_TOKENS];
int n_tokens = 0;

int whitespace(char ch)
{
    if(ch == ' ' || ch == '\t' || ch == '\n')
        return 1;
    return 0;
}

/* 返回剩余字串的起始位置 */
int parse_tokens(char *line, int len, int start)
{
    int end = start;
    while(start < len) {
        for(; start < len && whitespace(line[start]) && line[start] != ':'; start++)
            ;
        end = start;
        for(; end < len && !whitespace(line[end]) && line[end] != ':'; end++)
            ;
        if(start != end)
            tokens[n_tokens++] = strndup(line + start, end - start);
        start = end;
        if(line[start] == ':')
            return start + 1; /* 陷阱：剩余字串要去掉 :  */
    }
    return start;
}


int main(void)
{
    int pos;
    char *line = malloc(sizeof(char) * BUFFER_SIZE);

    scanf("%d", &pos);
    getchar(); /* NOTE getchar 的作用 */
  
    int next_start, word_width = 0, space = 0;
    while(fgets(line, BUFFER_SIZE, stdin) != NULL) {
        /* 陷阱：每行前要重置状态 */
        n_tokens = 0;
        word_width = 0;

        next_start = parse_tokens(line, strlen(line), 0);

        /* 计算预留空白字符数 */
        for(int i=0; i<n_tokens; i++) {
            word_width += strlen(tokens[i]);
            word_width += 1;
        }
        space = pos - word_width;
        for(; space>0; space--) {
            putchar(' ');
        }

        /* 打印冒号前内容 */
        for(int i=0; i<n_tokens; i++) {
            printf("%s ", tokens[i]);
        }
        putchar(':');

        /* 解析冒号后的 tokens 并打印 */
        n_tokens = 0;
        parse_tokens(line, strlen(line), next_start);
        for(int i=0; i<n_tokens; i++) {
            printf(" %s", tokens[i]);
        }
        putchar('\n');
    }

    return EXIT_SUCCESS;
}
