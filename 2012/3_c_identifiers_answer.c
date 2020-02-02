/* 思路：关键字 if/while/for 前后一定有分隔符 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 128
#define MAX_LEN 300
#define KW_NUM 3

/* 将双引号之间的内容 # 代替 */

void replaceQuota(char buf[])
{
    int i;
    int len = strlen(buf);
    int quotaL = 0, quotaR = 0;
    for(i=0; i<len; i++) {
        if(buf[i] == '"') {
            if(quotaL == 0) {
                quotaL = 1;
            } else {
                quotaL = quotaR = 0;
            }
        }
        else {
            if(quotaL == 1) {
                buf[i] = '#';
            }
        }
    }
}

/* 是否为分隔符 */
int isdelim(char ch) {
    switch(ch) {
        case ' ':
        case '=':
        case ',':
        case ';':
        case '<':
        case '>':
        case '(':
        case ')':
        case '{':
        case '}':
            return 1;
        default:
            return 0;
    }
}

/* 从 input 的 pos 处开始取一个单词返回，返回单词放在 word 中。 
 * 函数返回下次查找开始位置 */
int getWord(char input[], int pos, char word[]) {
    int len = strlen(input);
    int i;
    int isbegin = 0;
    int wpos = 0;
    for(i=pos; i<len; i++) {
        if(isdelim(input[i])) {
            if(isbegin == 0)  /* 掠过该分隔符 */
                continue; 
            else
                break;  /* 单词获取结束 */
        }
        else {
            isbegin = 1;
            word[wpos++] = input[i];
        }
    }
    word[wpos] = '\0';
    return (i>=len) ? -1 : i; /* 文件尾返回 -1 */
}


int main()
{
    char input[300];
    char word[MAX_WORD_LEN];
    freopen("3_data", "r", stdin);

    char delim[] = ",();\"+-*/=<>?:"; /* 单词分隔符 */
    while(gets(input) != NULL) {
        replaceQuota(input);
        int beg_pos = 0;
        do {
            beg_pos = getWord(input, beg_pos, word);
            int wlen = strlen(word);
            if(strcmp("if", word) == 0) {
                printf("if: %d\n", beg_pos - wlen + 1);
            }
            else if(strcmp("while", word) == 0) {
                printf("for: %d\n", beg_pos - wlen + 1);
            }
            else if(strcmp("for", word) == 0) {
                printf("for: %d\n", beg_pos - wlen + 1);
            }
        } while(beg_pos >= 0);
    }
    return 0;
}
