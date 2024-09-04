/*
Project Euler Problem 19

This one ended up being very easy thanks to the DateTime library

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
package euler;

import java.time.DayOfWeek;
import java.time.LocalDate;

public class p0019 implements IEuler {
    @Override
    public Object answer() {
        byte answer = 0;
        for (short x = 1901; x < 2001; x++)
            for (byte y = 1; y < 13; y++)
                if (LocalDate.of(x, y, 1).getDayOfWeek() == DayOfWeek.SUNDAY)
                    answer++;
        return answer;
    }
}