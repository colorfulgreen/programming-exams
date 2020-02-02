#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
    int v;
    int seq;
} Node;

int main(void)
{
    int n;
    Node *array;
    scanf("%d", &n);
    if(n == 0)
        return 0;

    array = malloc(sizeof(Node) * n);
    for(int i=0; i<n; i++) {
        scanf("%d", &array[i].v);
        array[i].seq = -1;
    }

    int min;
    int seq = 1;
    int update = 1;
    while(1) {
        update = 0;
        /* 找下一个最小值 */
        for(int i=0; i < n; i++) 
            if(array[i].seq == -1) {
                min = array[i].v;
                break;
            }
        for(int i=0; i<n; i++) {
            if(array[i].seq == -1 && array[i].v <= min) { /* seq 充当是否处理过的标记 */
                min = array[i].v;
                update = 1;
            }
        }

        if(!update) /* 陷阱：update=0 时不执行后续更新逻辑 */
            break;

        /* 设置序号 */
        for(int j=0; j<n; j++) {
            if(array[j].v == min) {
                array[j].seq = seq;
            }
        }
        seq++;
    }

    for(int i; i<n-1; i++)
        printf("%d ", array[i].seq);
    printf("%d\n", array[n-1].seq);

    return EXIT_SUCCESS;
     
}
