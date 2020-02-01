#include <stdio.h>
#include <stdlib.h>

#define N 8

void print_board();
void set_row(int row);

int rows[N];
int n_successes = 0;

void set_row(int row) {
    if(row == N) {
        n_successes += 1;
        print_board();
        return;
    }

    int col, i;
    /* 循环检查是否可以放置到某一列 */
    for(col = 0; col < N; col++) {
        for(i = 0; i < row; i++) {
            if((rows[i] == col) || 
                    (col - rows[i] == row - i) || 
                    (col - rows[i] == i - row))
                break;
        }
        /* 没有找到冲突，可以放到该列 */
        if(i == row) {
            rows[i] = col;
            set_row(row + 1);
        }
    }
}


void print_board()
{
    printf("\n#%d\n", n_successes);
    for(int row = 0; row < N; row++) {
        for(int col = 0; col < N; col++) {
            if(col != 0) 
                putchar(' ');
            if(rows[row] == col) 
                putchar('1');
            else
                putchar('0');
        }
        putchar('\n');
    }
}


int main(void)
{
    int row = 0;
    for(int col = 0; col < N; col++) {
        rows[row] = col;
        set_row(row + 1);
    }
    printf("%d\n", n_successes);

    return EXIT_SUCCESS;
}
