/* !! 答案似乎是错误的，答案认为 左右上下最远端都有1 即 被1包围。反例见下图。

1 1 1 1 1 1
1 1 0 0 0 1
0 0 0 0 1 0
1 1 0 1 1 1
0 1 0 1 0 0
1 1 1 1 1 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int N;
    int island[100][100];
    int data[100][4];

    while(scanf("%d", &N) != EOF) {
        int i, j;
        memset(data, -1, 100*4*sizeof(int));
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                scanf("%d", &island[i][j]);
                printf("%d ", island[i][j]);
            }
            putchar('\n');
        }

        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                if(island[i][j] == 1) {
                    if(data[i][0] == -1) /* 第 i 行最左边 1 的位置 */
                        data[i][0] = j;
                    if(data[j][2] == -1) /* 第 j 列最上边 1 的位置 */
                        data[j][2] = i;
                    data[i][1] = j;
                    data[j][3] = i;
                }
            }
        }

        int area = 0;
        for(i=0; i<N; i++) {
            for(j=0; j<4; j++) {
                printf("%d ", data[i][j]);
            }
            putchar('\n');
            for(j=0; j<N; j++) {
                if(island[i][j] == 0) {
                    if(i>data[j][2] && i<data[j][3] && j>data[i][0] && j<data[i][1]) {
                        area++;
                    }
                }
            }
        }
        printf("%d\n", area);
    }
    return 0;
}
