#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned short x, y, z;
    scanf("%hd %hd", &x, &y);
    x >>= 8;
    x <<= 8;
    y >>= 8;
    z = x + y;
    printf("%hu\n", z);

    return EXIT_SUCCESS;
}
