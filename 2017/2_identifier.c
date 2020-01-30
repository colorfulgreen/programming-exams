/*
 * 1. 存储输入语句
 * 2. 分离标识符
 * 3. 查找标识符
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1000
#define IDENTIFIERS_SIZE 100


int valid_start(char c) {
    return (('a' <= c && c <= 'z') ||
            ('A' <= c && c <= 'Z') ||
            c == '_');
}


int valid(char c) {
    return (('a' <= c && c <= 'z') ||
            ('A' <= c && c <= 'Z') ||
            ('0' <= c && c <= '9') ||
            c == '_');
}


void extract_identifiers(char *clause, int is_declaration, char **identifiers, int *n_identifiers) 
{
    int len = strlen(clause);
    int start = 0, end = 0;
    if(is_declaration == 1) {
        for(; valid(clause[start]) && start < len; start++)
            ;
    }
    while(start<len && end<len) {
        /* NOTE: for 的调整部分在循环体执行完后执行。
         * 所以当条件为假时，start 不再自增。<- 和 while 中使用自增的区别 */
        for(; !valid_start(clause[start]) && start < len; start++)
            ;
        end = start;
        for(; valid(clause[end]) && end < len; end++)
            ;

        char *s = malloc(sizeof(char) * (end-start+1));
        strncpy(s, clause + start, end-start);
        identifiers[(*n_identifiers)++] = s;

        start = end;

        /* 声明语句中，逗号后才会出现下一个标识符 */
        if(is_declaration)
            for(; clause[start] != ',' && start < len; start++)
                ;
    }
}

int main(void) 
{
    char *decla, *compu;
    decla = malloc(sizeof(char) * BUFFER_SIZE);
    compu = malloc(sizeof(char) * BUFFER_SIZE);
    fgets(decla, BUFFER_SIZE, stdin);
    fgets(compu, BUFFER_SIZE, stdin);

    char **identifiers;
    int n_identifiers = 0;
    identifiers = malloc(sizeof(char *) * IDENTIFIERS_SIZE);
    extract_identifiers(decla, 1, identifiers, &n_identifiers);

    char **identifiers2;
    int n_identifiers2 = 0;
    identifiers2 = malloc(sizeof(char *) * IDENTIFIERS_SIZE);
    extract_identifiers(compu, 0, identifiers2, &n_identifiers2);

    int found = 0;
    for(int i=0; i<n_identifiers2; i++) {
        found = 0;
        for(int j=0; j<n_identifiers; j++) {
            if(strcmp(identifiers2[i], identifiers[j]) == 0) {
                found = 1;
                break;
            }
        }
        if(found == 0) {
            printf("%s ", identifiers2[i]);
        }
    }
    printf("\n");
    return EXIT_SUCCESS;
}
