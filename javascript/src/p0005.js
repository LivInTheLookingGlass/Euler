/**
 * Project Euler Problem 5
 *
 * I solved this problem by testing all combinations of the various multiples. I
 * actually tried to solve this by hand before doing this, and it wasn't terribly
 * hard. The answer turns out to be (2**4 * 3**2 * 5 * 7 * 11 * 13 * 17 * 19)
 *
 * Problem:
 *
 * 2520 is the smallest number that can be divided by each of the numbers from 1
 * to 10 without any remainder.
 *
 * What is the smallest positive number that is evenly divisible by all of the
 * numbers from 1 to 20?
 *
 * @return {number}
 **/
exports.p0005 = function() {
    const group = [...Array(21).keys()].slice(1);
    let answer = 1000000000000;
    for (const x of group) {
        for (const multiples of iters.combinations(group, x)) {
            const num = multiples.reduce((a, x) => a * x, 1);
            if (num < answer && group.every((divisor) => num % divisor == 0)) {
                answer = num;
            }
        }
    }
    return answer;
};

const iters = require('./lib/iters.js');
