#include <stdio.h>
#include <stdlib.h>

int is_prime(int n) {
    for(int i=2; i<=n/2; i++) {
        if(n % i == 0)
            return 0;
    }
    return 1;
}

int main(void)
{
    int n, found = 0;
    scanf("%d", &n);
    for(int i=2; i<n; i++) {
        if(i % 10 != 1)
            continue;
        if(is_prime(i)) {
            printf("%d\n", i);
            found = 1;
        }
    }
    if(!found)
        printf("-1\n");
    return EXIT_SUCCESS;
}
