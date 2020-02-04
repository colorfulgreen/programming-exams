#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10000

typedef struct TOKEN_RECORD {
    char token[21];
    int lines[200];
    int n_lines;
} TokenRecord;
TokenRecord records[200];
int n_tokens = 0;

int is_valid_token(char *token) {
    if(strcmp(token, "a") == 0 || strcmp(token, "an") == 0 
            || strcmp(token, "the") == 0 || strcmp(token, "and") == 0) 
        return 0;

    int len = strlen(token);
    for(int i=0; i<len; i++) {
        if(!((token[i] >= 'a' && token[i] <= 'z') ||
                    (token[i] >= 'A' && token[i] <= 'Z') ||
                    token[i] == '-'))
            return 0;
    }
    return 1;
}

void record(char *token, int lineno) {
    int found;
    TokenRecord *record;
    for(int i=0; i<n_tokens; i++) {
        record = &records[i]; 
        if(strcmp(record->token, token) == 0) {
            if(record->lines[record->n_lines - 1] != lineno)
                record->lines[record->n_lines++] = lineno;
            return;
        }
    }
    record = &records[n_tokens++];
    strncpy(record->token, token, strlen(token));
    record->lines[0] = lineno;
    record->n_lines = 1;
    return;
}

void insertion_sort() 
{
    TokenRecord tmp;
    int i, j;
    for(i=0; i<n_tokens; i++) {
        tmp = records[i];
        for(j=i; j>1 && strcmp(records[j-1].token, tmp.token) > 0; j--)
            records[j] = records[j-1];
        records[j] = tmp;
    }
}

int main(void)
{
    FILE *f;
    char *line, *token;
    char *whitespace = " \t\n.";
    int lineno = 1;

    token = malloc(sizeof(char) * 21);
    line = malloc(sizeof(char) * BUFFER_SIZE);
    f = fopen("crossin.txt", "r");
    while(fgets(line, BUFFER_SIZE, f) != NULL) {
        for(token = strtok(line, whitespace);
                token != NULL;
                token = strtok(NULL, whitespace)) {
            if(is_valid_token(token))
                record(token, lineno);
        }
        lineno++;
    }
    fclose(f);

    /* 排序 */
    insertion_sort();

    int i, j;
    for(i=0; i<n_tokens; i++) {
        printf("%s:", records[i].token);
        for(j=0; j<records[i].n_lines - 1; j++)
            printf("%d,", records[i].lines[j]);
        printf("%d\n", records[i].lines[j]);
    }

    return EXIT_SUCCESS;
}
