/**
 * Project Euler Problem 14
 *
 * This was pleasantly easy to adapt from my Python solution.
 *
 * Problem:
 *
 * The following iterative sequence is defined for the set of positive integers:
 *
 * n → n/2 (n is even)
 * n → 3n + 1 (n is odd)
 *
 * Using the rule above and starting with 13, we generate the following sequence:
 * 13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
 *
 * It can be seen that this sequence (starting at 13 and finishing at 1) contains
 * 10 terms. Although it has not been proved yet (Collatz Problem), it is thought
 * that all starting numbers finish at 1.
 *
 * Which starting number, under one million, produces the longest chain?
 *
 * NOTE: Once the chain starts the terms are allowed to go above one million.
 *
 * @return {number}
 */
exports.p0014 = function() {
    let biggestSeen = 0;
    let biggestIdx = 0;
    const cache = new Map();
    for (let x = 1; x < 1000000; x += 1) {
        const result = collatzLen(x, cache);
        if (result > biggestSeen) {
            biggestSeen = result;
            biggestIdx = x;
        }
    }
    return biggestIdx;
};

/**
 * @param {number} n
 * @param {Map} cache
 * @return {number}
 */
function collatzLen(n, cache) {
    if (n == 1) {
        return 0;
    } else if (cache.has(n)) {
        return cache.get(n);
    } else if (n % 2 == 0) {
        const result = 1 + collatzLen(n / 2, cache);
        cache.set(n, result);
        return result;
    } else {
        const result = 2 + collatzLen((3 * n + 1) / 2, cache);
        cache.set(n, result);
        return result;
    }
}
