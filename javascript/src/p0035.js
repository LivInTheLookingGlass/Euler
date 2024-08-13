/**
 * Project Euler Problem 35
 *
 * This ended up being a filtering problem. The problem with my solution is that I
 * am not satisfied with my filter at all. I feel like there is a more efficient
 * way to go about it.
 *
 * Problem:
 *
 * The number, 197, is called a circular prime because all rotations of the
 * digits: 197, 971, and 719, are themselves prime.
 *
 * There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71,
 * 73, 79, and 97.
 *
 * How many circular primes are there below one million?
 *
 * @return {number}
 */
exports.p0035 = function() {
    let answer = 0;
    for (let x = 0; x < 1000000; x++) {
        let broken = false;
        for (const rot of rotations(x)) {
            if (!primes.isPrime(rot)) {
                broken = true;
                break;
            }
        }
        if (!broken) {
            answer++;
        }
    }
    return answer;
};

/**
 * Iterate over the rotations of a number's decimal representation
 * @param {number} x
 * @yield {number}
 */
function* rotations(x) {
    yield x;
    const xs = x.toString();
    for (let i = 1; i < xs.length; i++) {
        yield parseInt(xs.substring(i) + xs.substring(0, i));
    }
}

const primes = require('./lib/primes.js');
