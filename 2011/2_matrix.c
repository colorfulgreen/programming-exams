#include <stdio.h>
#include <stdlib.h>

int **A;
int **B;

/* 陷阱：若用参数 int **matrix 传递 A，实际被赋值的是 A 的拷贝指针，A 仍为无效指针。
 
   void input_matrix(int rows, int cols, int **matrix);
   input_matrix(arows, acols, A);
 */
int **input_matrix(int rows, int cols)
{
    int **matrix;
    matrix = malloc(sizeof(int *) * rows);
    for(int i=0; i<rows; i++) {
        matrix[i] = malloc(sizeof(int) * cols);
        for(int j=0; j<cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    return matrix;
}

int main(void)
{
    int arows, acols, brows, bcols, x, y;
    scanf("%d %d", &arows, &acols);
    A = input_matrix(arows, acols);
    scanf("%d %d", &brows, &bcols);
    B = input_matrix(brows, bcols);
    scanf("%d %d", &x, &y);
    if(x < 1 || y < 1)
        return 0;

    x -= 1;
    y -= 1;
    for(int i=x; i<brows+x && i<arows; i++) 
        for(int j=y; j<bcols+y && j<acols; j++) {
            printf("%d %d %d\n", i, j, A[i][j]);
            A[i][j] = B[i-x][j-y];
        }
    for(int i=0; i<arows; i++) {
        for(int j=0; j<acols-1; j++)
            printf("%d ", A[i][j]);
        printf("%d\n", A[i][acols-1]);
    }
    return EXIT_SUCCESS;
}
