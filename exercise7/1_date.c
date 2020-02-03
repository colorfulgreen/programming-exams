#include <stdio.h>
#include <stdlib.h>

int MON2DAY[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

typedef struct DATE {
    int year;
    int month;
    int day;
} Date;

int is_leap_year(int year) {
    if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        return 1;
    return 0;
}

int days_in_year(int year, int month, int day) 
{
    int is_leap = is_leap_year(year);
    int days = 0;
    for(int i=1; i<month; i++) {
        days += MON2DAY[is_leap][i];
    }
    days += day;
    return days;
}

int main(void) {
    Date d1, d2;
    scanf("%d %d %d", &d1.year, &d1.month, &d1.day);
    scanf("%d %d %d", &d2.year, &d2.month, &d2.day);

    int delta = 0;
    for(int i=d1.year; i<d2.year; i++)
        delta += days_in_year(i, 12, 31);
    delta -= days_in_year(d1.year, d1.month, d1.day);
    delta += days_in_year(d2.year, d2.month, d2.day);
    printf("%d\n", delta);

    return 0;
}
