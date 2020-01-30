#include <stdio.h>
#include <stdlib.h>

int num;
int *input;
int *array;

/* NOTE 插入排序 */
void insertion_sort(int *array, int num) 
{
    int i, j, tmp;
    for(i=1; i<num; i++) {
        /* 每一轮将 array[i] 插入合适的位置 */
        tmp = array[i];
        for(j = i; j > 0 && array[j-1] > tmp; j--) {
            array[j] = array[j-1];
        }
        array[j] = tmp;
    }
}


int find_index(int *input, int value)
{
    for(int i=0; i<num; i++) {
        if(input[i] == value)
            return i+1;
    }
    return -1;
}


int main(void)
{
    scanf("%d", &num);
    input = malloc(sizeof(int) * num);
    array = malloc(sizeof(int) * num);
    for(int i=0; i<num; i++) {
        scanf("%d", &input[i]);
        array[i] = input[i];
    }
    insertion_sort(array, num);
    for(int i=0; i<num; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    if(num % 2 == 1) {
        printf("%d %d\n", array[num/2], find_index(input, array[num/2]));
    }
    else {
        printf("%d %d\n", array[num/2-1], find_index(input, array[num/2-1]));
        printf("%d %d\n", array[num/2], find_index(input, array[num/2]));
    }

    printf("%d\n", 7 & 2);
    return EXIT_SUCCESS;
}
