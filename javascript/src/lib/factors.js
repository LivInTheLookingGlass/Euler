/**
 * Iterates over the proper divisors of a given number
 * @param {number} num
 * @yield {number}
 */
function* properDivisors(num) {
    factors = [...primes.primeFactors(num)];
    const seen = new Set();
    yield 1;
    for (let x = 1; x < factors.length; x++) {
        for (const combo of iters.combinations(factors, x)) {
            ret = combo.reduce((a, x) => a * x, 1);
            if (!seen.has(ret)) {
                yield ret;
                seen.add(ret);
            }
        }
        seen.clear();
    }
}
exports.properDivisors = properDivisors;

const iters = require('./iters.js');
const primes = require('./primes.js');
