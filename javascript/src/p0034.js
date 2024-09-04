/**
 * Project Euler Problem 34
 *
 * This ended up being a filtering problem. The problem with my solution is that I
 * am not satisfied with my filter at all. I feel like there is a more efficient
 * way to go about it.
 *
 * Problem:
 *
 * 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
 *
 * Find the sum of all numbers which are equal to the sum of the factorial of
 * their digits.
 *
 * Note: as 1! = 1 and 2! = 2 are not sums they are not included.
 *
 * @return {number}
 */
exports.p0034 = function() {
    let answer = 0;
    for (let x = 10; x < 100000; x += 1) {
        const xs = x.toString();
        let sum = 0;
        for (let i = 0; i < xs.length; i += 1) {
            sum += Mathematics.factorial(Number(xs[i]));
        }
        if (sum == x) {
            answer += x;
        }
    }
    return answer;
};

const Mathematics = require('./lib/math.js');
