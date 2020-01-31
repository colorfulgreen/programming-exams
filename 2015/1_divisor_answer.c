#include <stdio.h>

int main()
{
    int n, m, a[100], b[100], suma, sumb;
    int s, t;
    int i = 0, j = 0, k = 0;
    suma = 0;
    sumb = 0;
    /* 输入并拷贝数字 */
    scanf("%d %d", &n, &m);
    s = n;
    t = m;

    /* 求 a 的约数 */
    if(n == 0) {
        a[k] = 0;
        k++;
    }
    for(i = 1; i <= n / 2; i++) {
        if(n % i == 0) {
            a[k] = i;
            k++;
        }
    }
    a[k] = -1; /* 最后一个标记 */

    /* 求 b 的约数 */
    k = 0;
    if(m == 0) {
        b[k] = 0;
        k++;
    }
    for(i = 1; i <= m / 2; i++) {
        if(m % i == 0) {
            b[k] = i;
            k++;
        }
    }
    b[k] = -1; /* 最后一个标记 */

    for(i = 0; a[i] != -1; i++)
        suma += a[i];
    if(suma == m) {
        for(i = 0; b[i] != -1; i++)
            sumb += b[i];
        if(sumb == n) { 
            printf("%d,", n);
            for(i = 0; a[i] != -1; i++) {
                if(a[i + 1] == -1)
                    printf("%d",a[i]);
                else
                    printf("%d+", a[i]);
            }
            printf("=%d\n", m);

            printf("%d,", m);
            for(i = 0; b[i] != -1; i++) {
                if(b[i + 1] == -1)
                    printf("%d",b[i]);
                else
                    printf("%d+", b[i]);
            }
            printf("=%d\n", n);
            printf("1\n");
            return 0;
        }
    }
    printf("0\n");
    return 0;
}

