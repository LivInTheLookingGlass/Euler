/**
 * Project Euler Problem 37
 *
 * I was surprised how fast my brute-force solution went, but it worked
 *
 * Problem:
 *
 * The number 3797 has an interesting property. Being prime itself, it is possible
 * to continuously remove digits from left to right, and remain prime at each
 * stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797,
 * 379, 37, and 3.
 *
 * Find the sum of the only eleven primes that are both truncatable from left to
 * right and right to left.
 *
 * NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
 *
 * @return {number}
 */
exports.p0037 = function() {
    let answer = 0;
    let count = 0;
    for (const p of primes.primes()) {
        if (count == 11) {
            break;
        } else if (p < 10) {
            continue;
        } else {
            let right = p;
            let left = p;
            while (primes.isPrime(right)) {
                right = 0 | (right / 10);
            }
            if (right != 0) {
                continue;
            }
            while (primes.isPrime(left)) {
                let x = 10;
                while (x < left) {
                    x *= 10;
                }
                left %= 0 | (x / 10);
            }
            if (left != 0) {
                continue;
            }
            answer += p;
            count++;
        }
    }
    return answer;
};

const primes = require('./lib/primes.js');
