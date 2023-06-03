#pragma once

extern const char WEEK_DAYS_NAMES[][16];

typedef struct {
    int day;
    int month;
    int year;
} Date;

void createDate(Date *date);

int dateEquals(Date date1, Date date2);

int getWeekDayFromDate(Date date);