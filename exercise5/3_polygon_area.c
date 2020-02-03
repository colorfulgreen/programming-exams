/* 计算凸多边形面积。以顺时针顺序输入点的坐标。*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float distance(int x0, int y0, int x1, int y1)
{
    return sqrt(pow(x1-x0, 2) + pow(y1-y0, 2));
}

int main(void)
{
    int x[32], y[32], n;
    scanf("%d", &n);
    for(int i=0; i<n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }

    float a, b, c; /* 切割三角形的三条边长 */
    float l;
    float area;
    for(int i=2; i<n; i++) {
        a = distance(x[0], y[0], x[i-1], y[i-1]);
        b = distance(x[0], y[0], x[i], y[i]);
        c = distance(x[i-1], y[i-1], x[i], y[i]);
        l = (a + b + c) / 2;
        area += sqrt(l*(l-a)*(l-b)*(l-c));
    }

    printf("%.2f\n", area);

    return EXIT_SUCCESS;
}
