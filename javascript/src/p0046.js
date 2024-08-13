/**
 * Project Euler Problem 46
 *
 * Didn't even need to rearrange the formula to solve it trivially
 *
 * Revision 1:
 *
 * It turns out that rearranging the formula let me cut the time by ~50x
 *
 * Problem:
 *
 * It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and
 * twice a square.
 *
 * 9 = 7 + 2×1^2
 * 15 = 7 + 2×2^2
 * 21 = 3 + 2×3^2
 * 25 = 7 + 2×3^2
 * 27 = 19 + 2×2^2
 * 33 = 31 + 2×1^2
 *
 * It turns out that the conjecture was false.
 *
 * What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?
 *
 * @return {number}
 */
exports.p0046 = function() {
    const cachedPrimes = Array.from(primes.primes(6000));
    for (let goal = 35; ; goal += 2) {
        if (primes.isPrime(goal)) {
            continue;
        }
        let done = false;
        for (const p of cachedPrimes) {
            if (p >= goal) {
                continue;
            }
            for (let x = 1; x < Math.sqrt((goal - p) / 2) + 1; x++) {
                if (p + 2 * x * x === goal) {
                    done = true;
                    break;
                }
            }
            if (done) {
                break;
            }
        }
        if (!done) {
            return goal;
        }
    }
    return -1;
};

const primes = require('./lib/primes.js');
