#include <stdio.h>
#include <stdlib.h>

typedef struct FREQ {
    int num;
    int count;
} Freq;

int main(void)
{
    int n, *numbers, freq_len, i, j, found;
    Freq *freq;
    scanf("%d", &n);
    numbers = malloc(sizeof(int) * n);
    freq = malloc(sizeof(Freq) * n);

    freq_len = 0;
    for(i=0; i<n; i++) {
        scanf("%d", &numbers[i]);

        for(j=0; j<freq_len; j++) {
            if(numbers[i] == freq[j].num) {
                freq[j].count++;
                found = 1;
                break;
            }
        }
        if(!found) {
            freq[freq_len++].num = numbers[i];
            freq[freq_len++].count = 1;
        }
    }

    int max_count = 0, index = 0;
    for(i = 0; i<freq_len; i++) {
        if(freq[i].count > max_count) {
            max_count = freq[i].count;
            index = i;
        } 
    }

    printf("%d\n", freq[index].num);

    return 0;
}
