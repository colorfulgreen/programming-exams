#include <stdio.h>
#include <stdlib.h>
#define MAX 1001

struct segment {
    int sx, sy, ex, ey;
    int seg_num;
} s[MAX];

int cmp(const void *a, const void *b) 
{
    if((*(struct segment *)a).seg_num > (*(struct segment *)b).seg_num)
        return -1;
    else
        return 1;
}


int main() 
{
    int n, i, j;
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        scanf("%d%d%d%d", &s[i].sx, &s[i].sy, &s[i].ex, &s[i].ey);
        s[i].seg_num = 1;
    }

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            /* 将两条相邻线段合并成一条 */
            /* TODO 不考虑共用起点、公用终点吗？ */
            if(s[i].ex == s[j].sx && s[i].ey == s[j].sy) {
                s[i].ex = s[j].ex;
                s[i].ey = s[j].ey;
                s[j].sx = s[i].sx;
                s[j].sy = s[i].sy;
                s[i].seg_num += s[j].seg_num;
                s[j].seg_num = s[i].seg_num;
            } else if(s[j].ex == s[i].sx && s[j].ey == s[i].sy) {
                s[j].ex = s[i].ex;
                s[j].ey = s[i].ey;
                s[i].sx = s[j].sx;
                s[i].sy = s[j].sy;
                s[i].seg_num += s[j].seg_num;
                s[j].seg_num = s[i].seg_num;
            }
        }
    }
    qsort(s, n, sizeof(struct segment), cmp);
    printf("%d %d %d %d %d\n", s[0].seg_num, s[0].sy, s[0].sy, s[0].ex, s[0].ey);

    return EXIT_SUCCESS;
}
