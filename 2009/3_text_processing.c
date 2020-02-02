#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1000
#define TOKEN_BUFFER_SIZE 100

int main(void)
{
    FILE *f;
    char line[BUFFER_SIZE];
    char token[TOKEN_BUFFER_SIZE];
    int len, token_len, n_spaces, pos;

    scanf("%s", token);
    f = fopen("filein.txt", "r");
    if(f == 0)
        return EXIT_FAILURE;

    token_len = strlen(token);
    while(fgets(line, BUFFER_SIZE, f) != NULL) {
        if(token_len == 0) {
            continue;
        }
        len = strlen(line);
        n_spaces = 0;
        /* 打印空格 */
        for(int i=0; i<len; i++)
            if(line[i] == ' ')
                n_spaces += 1;
        for(int i=0; i<n_spaces; i++)
            putchar(' ');
        /* 扫描并打印剩余字符  */
        for(int pos=0; pos<len;) {
            /* NOTE 转换大小写 ctype.h tolower/toupper */
            char ch = tolower(line[pos]);
            if (ch == ' ') {
                pos++;
                continue;
            }
            if(ch == token[0]) {
                if(strncmp(line+pos, token, token_len) == 0) {
                    pos += token_len;
                    continue;
                }
            }
            putchar(line[pos++]);
        }
    }

    return EXIT_SUCCESS;
}
