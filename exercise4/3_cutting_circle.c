/* 用直线对圆进行切割，经过 N 次分割后，圆分成的块数为
 *  f(n) = f(n-1) + n
 *  f(0) = 1
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, n_pieces = 1;
    scanf("%d", &n);

    for(int i=1; i<=n; i++) {
        n_pieces += i;
    }

    printf("%d\n", n_pieces);
    return EXIT_SUCCESS;
}
