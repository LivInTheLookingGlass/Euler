/**
 * Project Euler Problem 7
 *
 * Finally ported the prime generator to js
 *
 * Problem:
 *
 * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that
 * the 6th prime is 13.
 *
 * What is the 10 001st prime number?
 *
 * @return {number}
 */
exports.p0007 = function() {
    let pgen = primes.modifiedEratosthenes();
    for (let idx = 1; ; idx++) {
        let num = pgen.next().value;
        if (idx === 10001) {
            return num;
        }
    }
    return -1;
};

const primes = require('./lib/primes.js');

