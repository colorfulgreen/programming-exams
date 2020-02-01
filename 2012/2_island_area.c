#include <stdio.h>
#include <stdlib.h>

int **board;
int **valid_mask; /* 初始状态 -1 有效 1 无效 0 */
int size;

void notice_neighbor_bad_news(int x, int y)
{

    printf("Notice x=%d y=%d\n", x, y);
    for(int i=x-1; i>=0; i--) {
        /* 陷阱：避免重复扩散. 仅扩散给不知道坏消息的邻居，即 valid[i][y] != 0 */
        if(board[i][y] == 0 && valid_mask[i][y] != 0) {
            valid_mask[i][y] = 0;
            notice_neighbor_bad_news(i, y);
        }
        else
            break;
    }
    for(int i=x+1; i<size; i++) {
        if(board[i][y] == 0 && valid_mask[i][y] != 0) {
            valid_mask[i][y] = 0;
            notice_neighbor_bad_news(i, y);
        }
        else
            break;
    }
    for(int j=y-1; j>=0; j--) {
        if(board[x][j] == 0 && valid_mask[x][j] != 0) {
            valid_mask[x][j] = 0;
            notice_neighbor_bad_news(x, j);
        }
        else
            break;
    }
    for(int j=y+1; j<size; j++) {
        if(board[x][j] == 0 && valid_mask[x][j] != 0) {
            valid_mask[x][j] = 0;
            notice_neighbor_bad_news(x, j);
        }
        else
            break;
    }

}

void set_valid_mask()
{
    /* 置边缘部分的 0 为无效 */
    for(int i=0; i<size; i++) {
        if(board[0][i] == 0)
            valid_mask[0][i] = 0;
        if(board[size-1][i] == 0)
            valid_mask[size-1][i] = 0;
        if(board[i][0] == 0)
            valid_mask[i][0] = 0;
        if(board[i][size-1] == 0)
            valid_mask[i][size-1] = 0;
    }

    /* 标记中心 */
    for(int i=1; i<size-1; i++) {
        for(int j=1; j<size-1; j++) {
            if(board[i][j] == 1)
                continue;
            if(valid_mask[i-1][j] != 0 && valid_mask[i+1][j] != 0
                    && valid_mask[i][j-1] != 0 && valid_mask[i][j+1] != 0) {
                valid_mask[i][j] = 1;
            }
            else {
                valid_mask[i][j] = 0;
                notice_neighbor_bad_news(i, j);
            }
        }
    }
}

int main(void)
{
    /* 输入 board，初始化 valid_mask */
    scanf("%d", &size);
    board = malloc(sizeof(int *) * size);
    valid_mask = malloc(sizeof(int *) * size);
    for(int i=0; i<size; i++) {
        board[i] = malloc(sizeof(int) * size);
        valid_mask[i] = malloc(sizeof(int) * size);
    }
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++) {
            scanf("%d", &board[i][j]);
            valid_mask[i][j] = board[i][j] == 1 ? 1 : -1;
        }
    }

    set_valid_mask();

    int area = 0;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            printf("%d ", valid_mask[i][j]);
            if(board[i][j] == 0 && valid_mask[i][j] == 1)
                area++;
        }
        printf("\n");
    }

    printf("%d\n", area);

}
