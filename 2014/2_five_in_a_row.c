#include <stdio.h>
#include <stdlib.h>

#define SIZE 19

int board[SIZE][SIZE];

int is_in_row(int x, int y) 
{
    int i, value=board[x][y];

    /* 向右 */
    i = 0;
    while(i++ < 5) {
        if(!(x+i < SIZE && board[x+i][y] == value))
            break;
        /* 陷阱：不能在 for 后用 i == 4 判断第 4 次条件满足，
                 因为 i==4 && 后还有其它判断条件.*/
        if(i == 4)
            return 1;
    }

    /* 向下 */
    i = 0;
    while(i++ < 5) {
        if(!(y+i < SIZE && board[x][y+i] == value))
            break;
        if(i == 4)
            return 1;
    }

    /* 向右上 */
    i = 0;
    while(i++ < 5) {
        if(!(x+i < SIZE && y-i >= 0 && board[x+i][y-i]))
            break;
        if(i == 4)
            return 1;
    }

    /* 向右下 */
    i = 0;
    while(i++ < 5) {
        if(!(x+i < SIZE && y+i < SIZE && board[x+i][y+i] == value))
            break;
        if(i == 4)
            return 1;
    }

    return 0;
}


int main(void)
{
    int i, j;

    /* NOTE 输入矩阵，scanf 可以自动处理换行(空白字符) */
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    int people, is_win = 0;
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            if(board[i][j] == 0)
                continue;
            is_win = is_in_row(i, j);
            if(is_win) {
                printf("%d:(%d,%d)\n", board[i][j], i+1, j+1); /* 陷阱：题目要求从1开始编号 */
                return EXIT_SUCCESS;
            }
        }
    }

    printf("no\n");
    return EXIT_SUCCESS;
}
