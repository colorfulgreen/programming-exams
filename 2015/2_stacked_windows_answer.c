/* TODO 没看懂 */
#include <stdio.h>

int windows[100][5];
int s[100][2]; /* 窗口叠放顺序，1 在最上面 */

void update(int windows[][5], int n)
{
    int i,j,k,temp,p,x,y;
    for(i=0; i<n; i++) {
        k = i;
        for(j = i + 1; j < n; j++) {
            if(s[i][1] > s[j][1])
                k = j;
        }
        if(k != i) {
            x = -1;
            y = -1;
            for(p = 0; p < n; p++) {
                if(windows[p][0] == s[i][0])
                    x = p;
                if(windows[p][0] == s[k][0])
                    y = k;
                if(x && y) /* 找到 */ 
                    break;
            }
            for(p = 0; p < 5; p++) {
                temp = windows[x][p];
                windows[x][p] = windows[y][p];
                windows[y][p] = temp;
            }
        }
    }

    /* 计算活动区域 */
    for(i = 1; i < n; i++) {
        for(j = 0; j < n && j != i; j++) {
            if(windows[i][3] < windows[j][3] && windows[j][3] < windows[i][1]) /* 判断是否上下覆盖，行 */
                windows[i][3] = windows[j][3];
            else
                if(windows[i][2] < windows[j][2] && windows[j][2] < windows[i][4]) /* 判断是否左右覆盖，列 */
                    windows[j][2] = windows[i][4];
        }
    }
}

void change(int s[][2], int n, int k)
{
    int i,j;
    s[k][1] = 1;
    for(i=0; i<n && i != k; i++) {
        s[i][1] += s[i][1];
    }
}


int main()
{
    int n, m, i, j, p, t;
    int clicks[100][2], c[100][5];
    scanf("%d", &n);
    for(i=0; i<n; i++) {
        for(j=0; j<5; j++) {
            scanf("%d", &windows[i][j]);
            c[i][j] = windows[i][j]; /* 保留副本 */
        }
        s[i][0] = windows[i][0];
        s[i][1] = i + 1;
    }

    scanf("%d", &m);
    for(i=0; i<m; i++) {
        for(j=0; j<2; j++)
            scanf("%d", &clicks[i][j]);
    }

    /* 重新计算每个窗口的活动区域 */
    update(windows, n);
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            if(clicks[i][0] < windows[j][1] && clicks[i][0] > windows[j][3]) {
                change(s, n, i);
                if(i != m-1) {
                    for(p=0; p<n; p++) {
                        for(t=0; t<5; t++) {
                            windows[p][t] = c[p][t];
                        }
                    }
                }
                update(windows,n);
            }
        }
    }
    
    for(i=0; i<n; i++)
        printf("%5d", windows[i][0]);
    printf("\n");

    return 0;
}
