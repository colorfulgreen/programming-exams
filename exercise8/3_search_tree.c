#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 100
#define MAX_LINE 1000

typedef struct NODE {
    char token[MAX_WORD];
    struct NODE *left;
    struct NODE *right;
} Node;
Node *root = NULL;

Node *insertTree(Node *root, char *token) {
    if(root == NULL) {
        root = malloc(sizeof(Node));
        strcpy(root->token, token);
        root->left = NULL;
        root->right = NULL;
        return root;
    }

    int cmp = strcmp(root->token, token);
    if(cmp > 0) 
        root->left = insertTree(root->left, token);
    else if(cmp < 0)
        root->right = insertTree(root->right, token);
    return root;
}

void printTree(Node *root, FILE *out) {
    if(root == NULL)
        return;
    printTree(root->left, out);
    fprintf(out, "%s ", root->token);
    printTree(root->right, out);
}

int main(void)
{
    FILE *in, *out;
    char *line, *token;
    char *whitespace = " \t\n";
    line = malloc(sizeof(char) * MAX_LINE);
    token = malloc(sizeof(char) * MAX_WORD);
    in = fopen("3sort.in", "r");
    out = fopen("3sort.out", "w");
    while(fgets(line, MAX_LINE, in) != NULL) {
        for(token = strtok(line, whitespace);
                token != NULL;
                token = strtok(NULL, whitespace)) {
            root = insertTree(root, token);
        }
    }

    printTree(root, out);

    fclose(in);
    fclose(out);
    return 0;
}
