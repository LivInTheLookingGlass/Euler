/*
Project Euler Problem 19

This one ended up being very easy thanks to the time library

Problem:

You are given the following information, but you may prefer to do some research
for yourself.

    1 Jan 1900 was a Monday.
    Thirty days has September,
    April, June and November.
    All the rest have thirty-one,
    Saving February alone,
    Which has twenty-eight, rain or shine.
    And on leap years, twenty-nine.
    A leap year occurs on any year evenly divisible by 4, but not on a century
    unless it is divisible by 400.

How many Sundays fell on the first of the month during the twentieth century
(1 Jan 1901 to 31 Dec 2000)?
*/
#ifndef EULER_P0019
#define EULER_P0019
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint16_t p0019() {
    uint16_t answer = 0;
    struct tm date = {0};

    for (int year = 1901; year <= 2000; ++year) {
        for (int month = 0; month < 12; ++month) {
            date.tm_year = year - 1900;
            date.tm_mon = month;
            date.tm_mday = 1;

            if (mktime(&date) == -1) {
                fprintf(stderr, "mktime failed to normalize the date.\n");
                return -1;
            }

            if (date.tm_wday == 0) {
                ++answer;
            }
        }
    }
    return answer;
}


#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    printf("%" PRIu16 "\n", p0019());
    return 0;
}
#endif
#endif
