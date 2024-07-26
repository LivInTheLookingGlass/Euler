"""
Project Euler Problem 19

This one ended up being very easy thanks to the datetime library

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
"""
from datetime import date
from typing import Iterable


def monthly_iterator(years: range, months: range = range(1, 13), day: int = 1) -> Iterable[date]:
    for x in years:
        for y in range(1, 13):
            _day = date(x, y, day)
            if _day.weekday() == 6:
                yield _day


def main() -> int:
    return sum(1 for _ in monthly_iterator(years=range(1901, 2001)))


if __name__ == '__main__':
    print(main())  # pragma: no cover
