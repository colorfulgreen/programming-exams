#include <stdio.h>

int main(void)
{
    char ch;
    int m[2][2];
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            scanf("%d", &m[i][j]);
    ch = getchar();  /* getchar 会得到一个换行符 */
    printf("get=%c#\n", ch);
    ch = getchar();
    printf("get=%c#\n", ch);
    return 0;
}
