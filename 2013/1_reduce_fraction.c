#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a, b;
    scanf("%d %d", &a, &b);

    /* TODO 待确认：因子降序，每个因子只用过一次；因子升序，每个因子要过多次 */
    for(int i=a; i>=2; i--) {
        if(a % i == 0 && b % i == 0) {
            a /= i;
            b /= i;
        }
    }

    printf("%d %d", a, b);

    return EXIT_SUCCESS;
}
