#include <stdio.h>
#include <stdlib.h>

int magic[9][9];

void fillup(int n, int pos, int value) 
{
    int i;
    for(i=0; i<n; i++) /* 上 */
        magic[pos][pos+i] = value++;
    for(i=1; i<n; i++) /* 右 */
        magic[pos+i][pos+n-1] = value++;
    for(i=n-2; i>=0; i--) /* 下 */
        magic[pos+n-1][pos+i] = value++;
    for(i=n-2; i>=1; i--) /* 左 */
        magic[pos+i][pos] = value++;
    if(n>=2)
        fillup(n-2, pos+1, value);
}

int main(void)
{
    int n;
    scanf("%d", &n);
    fillup(n, 0, 1);

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++)
            printf("%4d", magic[i][j]);
        printf("\n");
    }
    return 0;
}
