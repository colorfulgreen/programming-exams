#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
    int v;
    struct NODE *next;
} Node;

int main(void)
{
    Node *head = NULL, *p = NULL;
    int v;

    while((scanf("%d", &v) == 1) && v != -1) {
        p = malloc(sizeof(Node));
        p->v = v;
        p->next = head;
        head = p;
    }


    scanf("%d", &v);
    while(head != NULL && head->v == v) {
        p = head;
        head = head->next;
        free(p);
    }
    p = head;
    while(p->next != NULL) {
        if(p->next->v == v) {
            p->next = p->next->next;
            free(p->next);
        }
        else {
            p = p->next;
        }
    }

    p = head;
    while(p->next != NULL) {
        printf("%d ", p->v);
        p = p->next;
    }
    printf("%d", p->v);

    return 0;
}
