/**
 * Project Euler Problem 10
 *
 * Yet again, having a good prime number infrastructure comes in handy
 *
 * Problem:
 *
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
 *
 * Find the sum of all the primes below two million.
 *
 * @return {number}
 */
exports.p0010 = function() {
    let answer = 0;
    for (const p of primes.primes(2000000)) {
        answer += p;
    }
    return answer;
};

const primes = require('./lib/primes.js');
