#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct tnode {
    char *word;
    int nline;
    int line[15];
    struct tnode *left;
    struct tnode *right;
};

int getWord(char *word, int lim, FILE *in);
struct tnode *addTree(struct tnode *, char *, int line);
void treePrint(struct tnode *, FILE *out);

int main()
{
    struct tnode *root;
    char word[MAXWORD];
    char c;
    int line = 1;

    FILE *in, *out;
    in = fopen("crossin.txt", "r");
    out = fopen("crossout.txt", "w");

    root = NULL;
    while((c = getWord(word, MAXWORD, in)) != EOF) {
        if(c == '\n')
            line++;
        if(isalpha(word[0]))
            root = addTree(root, word, line);
        word[0] = '\0';
    }
    treePrint(root, out);
    return 0;
}


int getWord(char *word, int lim, FILE *in)
{
    int c;
    char *w = word;

    while(isspace(c=fgetc(in)))
        if(c == '\n')
            return c;
    if(c != EOF)
        *w++ = c;
    if(!(isalpha(c)) && c != '-') {
        *w = '\0';
        return c;
    }
    for(; --lim>0; w++)
        if(!isalnum(*w=fgetc(in)) && !(*w == '-')) {
            ungetc(*w, in);
            break;
        }
    *w = '\0';

    return word[0];
}


struct tnode *addTree(struct tnode *p, char *w, int line)
{
    int cond;
    if(p == NULL) {
        p = (struct tnode *) malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->nline = 1;
        p->line[p->nline - 1] = line;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        if(p->line[p->nline - 1] != line) {
            p->nline++;
            p->line[p->nline - 1] = line;
        }
    } else if(cond < 0)
        p->left = addTree(p->left, w, line);
    else
        p->right = addTree(p->right, w, line);

    return p;
}


void treePrint(struct tnode *p, FILE *out)
{
    int i;
    if(p != NULL) {
        treePrint(p->left, out);
        /* 输出时再做过滤 1. 忽略 stopwords 2. 排重 */
        if(strcmp(p->word, "a") 
                && strcmp(p->word, "an")
                && strcmp(p->word, "the")
                && strcmp(p->word, "and")) {
            fprintf(out, "%s:", p->word);
            fprintf(out, "%d", p->line[0]);
            for(i = 1; i < p->nline && p->line[i] != p->line[i-1]; i++) {
                fprintf(out, "%d", p->line[i]);
            }
            fprintf(out, "\n");
        }
        treePrint(p->right, out);
    }
}
