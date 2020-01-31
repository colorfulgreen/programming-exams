#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INVALID 9999
#define true 1
#define false 0

const int LEN = 200;
char name[LEN][LEN];
int num[LEN];
int curIndex = 0;

char *typeContent;
int typeContentLen = 0;
int lastPos = 0;

void parse(char enumStr[], int len);
char *getTypeContent(char enumStr[], int len);
char eval(char c);
void scan(char enumStr[], int *pos);

void parse(char enumStr[], int len) 
{
    char *content = getTypeContent(enumStr, len);
    int BEG = 0;
    while(lastPos < typeContentLen)
        scan(content, &BEG);
}

/* 取 { 和 } 之间的内容 */
char *getTypeContent(char enumStr[], int len)
{
    int i = 0;
    int pos = 0;
    while(true) {
        if(enumStr[i] == '{') {
            while(i++) {
                if(enumStr[i] == '}') {
                    typeContent[pos++] = '\0';
                    typeContentLen = pos;
                    return typeContent;
                }
                else {
                    typeContent[pos++] = enumStr[i];
                }
            }
        }
        i++;
    }
    return NULL;
}


/* TODO 返回类型应该是 int 而不是 char ? */
char eval(char c)
{
    return c - '0';
}


void scan(char enumStr[], int *pos)
{
    printf("########\n");
    int end = *pos;
    int i = 0;
    while(true) {
        printf(">> %d %c\n", i, enumStr[i]);
        if(enumStr[end] == ',') {
            name[curIndex][i] = 0;
            num[curIndex] = INVALID;
            *pos = end + 1;
            curIndex++;
            return;
        }
        if(enumStr[end] == '=') {
            name[curIndex][i] = 0;
            while(true) {
                end++;
                if(enumStr[end] != ' ') {
                    num[curIndex] = atoi(&enumStr[end]);
                    break;
                }
            }
            while(true) {
                if(end > typeContentLen) {
                    lastPos = typeContentLen;
                    return;
                }
                end++;
                if(enumStr[end] == ',')
                    break;
            }
            *pos = end + 1;
            curIndex++;
            return;
        }
        name[curIndex][i++] = enumStr[end++];
    }
}


/* TODO int & ? */
int count(int num, int *preCount)
{
    if(num != INVALID) {
        *preCount = num;
        return *preCount;
    }
    else {
        *preCount = *preCount + 1;
        return *preCount;
    }
}


void print()
{
    int i = 0;
    int preCount = 0;
    for(int i=0; i<curIndex; i++) {
        printf("%s:%d\n", name[i], count(num[i], &preCount));
    }
}

int main()
{
    typeContent = (char *)malloc(LEN);
    for(int i=0; i<LEN; i++)
    {
        num[i] = INVALID;
    }
    char enumStr[LEN];
    fgets(enumStr, LEN, stdin);
    parse(enumStr, strlen(enumStr));
    // printf("dsaf %s %d\n", enumStr, strlen(enumStr));
    print();

    getchar();
    getchar();
    return 0;
}
