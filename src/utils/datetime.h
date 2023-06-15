/**
 * @file datetime.h
 * @brief utility functions and structs related to datetime management
 * @author Luca Azalim
*/

#pragma once

/**
 * @brief array of strings containing the names of the days of the week
 */
extern const char WEEK_DAYS_NAMES[][16];

typedef struct
{
    int day;
    int month;
    int year;
} Date;

/** @brief scans necessary information and populates pointer variables
 * @param date date struct pointer
 */
void createDate(Date *date);

/** @brief compares two dates and returns whether they are equal or not
 * @param date1 first date to compare
 * @param date2 second date to compare
 * @return 0 if the dates are different and 1 if the dates are equal
 */
int dateEquals(Date date1, Date date2);

/** @brief returns the week day index from a specific date
 * @param date the date for which you would like to know the day of the week
 * @return an int from 0 to 6, where 0 represents Sunday and 6 represents Saturday
 */
int getWeekDayFromDate(Date date);