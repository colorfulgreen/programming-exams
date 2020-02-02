#include <stdio.h>
#include <stdlib.h>

int order;
int A[9][9], B[9][9];

void input_matrix(int order, int matrix[][9])
{
    for(int i=0; i<order; i++)
        for(int j=0; j<order; j++)
            scanf("%d", &matrix[i][j]);
}

int cmp_0(int i, int j)
{
    return A[i][j] == B[i][j] ? 1 : 0;
}

int cmp_90(int i, int j) 
{
    return A[i][j] == B[j][order-1-i] ? 1 : 0;
}

int cmp_180(int i, int j)
{
    return A[i][j] == B[order-1-i][order-1-j] ? 1 : 0;
}

int cmp_270(int i, int j)
{
    return A[i][j] == B[order-1-j][i] ? 1 : 0;
}

/* NOTE 使用回调函数 */
int is_match(int (*cmp)(int, int))
{
    int i, j;
    for(i=0; i<order; i++) {
        for(j=0; j<order; j++) 
            if(!cmp(i, j)) 
                break;
        if(j != order)
            break;
    }
    if(i == order) 
        return 1;
    return 0;
}


int main(void)
{
    scanf("%d", &order);
    input_matrix(order, A);
    input_matrix(order, B);

    /* 旋转 0 */
    if(is_match(&cmp_0))
        printf("0\n");
    else if(is_match(&cmp_90))
        printf("90\n");
    else if(is_match(&cmp_180))
        printf("180\n");
    else if(is_match(&cmp_270))
        printf("270\n");
    else
        printf("-1\n");

    return 0;
}
