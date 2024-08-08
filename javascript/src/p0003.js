/**
 * Project Euler Problem 3
 *
 * Finally ported prime factor generator to js
 *
 * Problem:
 *
 * The prime factors of 13195 are 5, 7, 13 and 29.
 *
 * What is the largest prime factor of the number 600851475143 ?
 *
 * @return {number}
 */
exports.p0003 = function() {
    return Math.max(...primes.primeFactors(600851475143));
};

const primes = require('./lib/primes.js');

