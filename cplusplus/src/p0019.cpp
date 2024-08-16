/*
Project Euler Problem 19

This one ended up being very easy thanks to the ctime library

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
#include <iostream>
#include <stdexcept>
#include <stdint.h>

#ifdef _WIN32
#include <cstring>
#include <windows.h>
#else
#include <ctime>
#endif

uint16_t p0019() {
    uint16_t answer = 0;

#ifdef _WIN32
    SYSTEMTIME systemTime;
    FILETIME fileTime;
    SYSTEMTIME normalizedTime;
#else
    std::tm date = {0};
#endif

    for (int year = 1901; year <= 2000; ++year) {
        for (int month = 0; month <= 11; ++month) {
#ifdef _WIN32
            std::memset(&systemTime, 0, sizeof(systemTime));
            systemTime.wYear = year;
            systemTime.wMonth = month + 1;
            systemTime.wDay = 1;

            if (!SystemTimeToFileTime(&systemTime, &fileTime)) {
                throw std::runtime_error("SystemTimeToFileTime failed.");
            }
            if (!FileTimeToSystemTime(&fileTime, &normalizedTime)) {
                throw std::runtime_error("FileTimeToSystemTime failed.");
            }

            if (normalizedTime.wDayOfWeek == 0) {
                ++answer;
            }
#else
            date.tm_year = year - 1900;
            date.tm_mon = month;
            date.tm_mday = 1;

            if (std::mktime(&date) == -1) {
                throw std::runtime_error("mktime failed to normalize the date.");
            }
            if (date.tm_wday == 0) {
                ++answer;
            }
#endif
        }
    }
    return answer;
}


#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    std::cout << p0019() << std::endl;
    return 0;
}
#endif
#endif
