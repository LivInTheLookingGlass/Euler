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
using System;

namespace Euler
{
    public class p0019 : IEuler
    {
        public object Answer()
        {
            byte answer = 0;
            for (ushort x = 1901; x < 2001; x += 1)
                for (byte y = 1; y < 13; y += 1)
                    if (new DateTime(x, y, 1).DayOfWeek == DayOfWeek.Sunday)
                        answer += 1;
            return answer;
        }
    }
}

