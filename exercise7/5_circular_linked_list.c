#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
    int seq;
    struct NODE *next;
} Node;

int main(void)
{
    int n, m, q;
    Node *head, *p, *tmp;
    scanf("%d %d %d", &n, &m, &q);
    /* 构造循环链表 */
    head = malloc(sizeof(Node));
    head->seq = 1;
    p = head;
    for(int i=2; i<=n; i++) {
        p->next = malloc(sizeof(Node));
        p->next->seq = i;
        p = p->next;
        p->next = NULL;
    }
    p->next = head;

    /* 定位到第 p-1 个节点 */
    p = head;
    for(int i=2; i<q; i++)
        p = p->next;

    /* 报数 */
    while(p->next != p) {
        for(int i=2; i<=m; i++) {
            p = p->next;
        }
        tmp = p->next;
        p->next = p->next->next;
        free(tmp);
    }

    printf("%d\n", p->seq);
    return 0;
}
