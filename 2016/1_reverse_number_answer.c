#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getNumDecs(int num)
{
    int i = 0;
    while((num)/(int)pow(10, i))
        i++;
    return i;
}


int getReverseNum(int num, int decs)
{
    int reverseNum = 0;
    int i = 0;
    while(decs) {
        reverseNum += (num/(int)pow(10, decs-1)) * (int)pow(10, i);
        num = num % (int)pow(10, decs-1);
        decs--;
        i++;
    }
    return reverseNum;
}

int main()
{
    int num;
    scanf("%d", &num);
    int decs = getNumDecs(num);
    int reverseNum = getReverseNum(num, decs);
    if(0 == (reverseNum % num)) {
        printf("%d*%d=%d", num, reverseNum/num, reverseNum);
    }
    else
        printf("%d %d", num, reverseNum);
    getchar();
    getchar();
    return 0;
}
