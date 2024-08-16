/**
 * Project Euler Problem 19
 *
 * This one ended up being very easy thanks to the Date object
 *
 * Problem:
 *
 * You are given the following information, but you may prefer to do some research
 * for yourself.
 *
 * 1 Jan 1900 was a Monday.
 * Thirty days has September,
 * April, June and November.
 * All the rest have thirty-one,
 * Saving February alone,
 * Which has twenty-eight, rain or shine.
 * And on leap years, twenty-nine.
 * A leap year occurs on any year evenly divisible by 4, but not on a century
 * unless it is divisible by 400.
 *
 * How many Sundays fell on the first of the month during the twentieth century
 * (1 Jan 1901 to 31 Dec 2000)?
 *
 * @return {number}
 */
exports.p0019 = function() {
    let answer = 0;
    for (let x = 1901; x < 2001; x += 1) {
        for (let y = 1; y < 13; y += 1) {
            if (new Date(x, y, 1).getDay() == 0) {
                answer += 1;
            }
        }
    }
    return answer;
};
