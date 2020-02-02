#include <stdio.h>
#include <stdlib.h>

double cubic_root(double x, int n) 
{
#if 0
    if(n == 0)
        return x;
    double v = cubic_root(x, n-1);
    return v*2/3 + x/(3*v*v);
#endif
    /* NOTE 尾递归改成迭代 */
    double v = x;
    for(int i=1; i<=n; i++) {
        v = v*2/3 + x/(3*v*v);  
    }
    return v;
}


int main(void)
{
    double x, result;
    int n;

    /* NOTE scanf 输入结束的判断 */
    while(scanf("%lf %d", &x, &n) != EOF) {
        result = cubic_root(x, n);
        /* NOTE 精度处理，保留小数点后6位 */
        printf("%.6f\n", result);
    }

    return EXIT_SUCCESS;
}
