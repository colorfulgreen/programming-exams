#include <stdio.h>
#include <stdlib.h>

void print_reverse(int n) {
    if(n == 0)
        return;
    int mod = n % 10;
    printf("%d", mod);
    print_reverse((n - mod) / 10);
}

int main(void)
{
    int n, n2, rev = 0, mod = 0;
    scanf("%d", &n);
    /* 陷阱：n 后面还要用，这里拷贝一份以修改 */
    n2 = n;
    while(n2 != 0) {
        mod = n2 % 10;
        rev = rev * 10 + mod;
        n2 = (n2 - mod) / 10;
    }
  
    if(rev % n == 0) {
        printf("%d*%d=%d\n", n, rev/n, rev);
    }
    else {
        printf("%d ", n);
        print_reverse(n);
        printf("\n");
    }

    return EXIT_SUCCESS;
}
