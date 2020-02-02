#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    float f;
    int rnum;
    scanf("%f", &f);

    /* NOTE 四舍五入：加上 0.5 后取整 */
    rnum = f + 0.5;
    printf("%d\n", rnum);

    return EXIT_SUCCESS;
}
