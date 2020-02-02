#include <stdio.h>
#include <stdlib.h>

int *numbers;
int *sums;
int count;


void cal_factors_sum(int index) {
    int number = numbers[index];
    int sum = 0;
    for(int i=1; i<number/2+1; i++) {
        if(number % i == 0)
            sum += i;
    }
    sums[index] = sum;
}

int main(void)
{
    int m, n, found = 0;
    scanf("%d %d", &m, &n);
    count = n - m + 1;
    numbers = malloc(sizeof(int) * count);
    sums = malloc(sizeof(int) * count);
    for(int i=0; i<count; i++) 
        numbers[i] = m + i;
    for(int i=0; i<count; i++) 
        cal_factors_sum(i);

    for(int i=0; i<count; i++) {
        for(int j=i+1; j<count; j++) {
            if(sums[i] == numbers[j] && sums[j] == numbers[i]) {
                printf("%d %d\n", numbers[i], numbers[j]);
                found = 1;
            }
        }
    }
    if(!found)
        printf("NONE\n");

    return EXIT_SUCCESS;
}
