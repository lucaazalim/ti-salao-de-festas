#include <stdio.h>

#include "datetime.h"
#include "scan-utils.h"

const char WEEK_DAYS_NAMES[][16] = {"Segunda-Feira", "Terça-Feira", "Quarta-Feira", "Quinta-Feira", "Sexta-Feira", "Sabado", "Domingo"};

void createDate(Date *date)
{
    printf("\tDia: ");
    scanf("%d", &date->day);

    printf("\tMês: ");
    scanf("%d", &date->month);

    printf("\tAno: ");
    scanf("%d", &date->year);
}

int dateEquals(Date date1, Date date2)
{
    return date1.day == date2.day 
    && date1.month == date2.month 
    && date1.year == date2.year;
}

int getWeekDayFromDate(Date date)
{

    int d = date.day;
    int m = date.month;
    int y = date.year;

    return (d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;
}