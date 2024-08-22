/**
 * Iterate over the different combinations of the elements in a given iterable
 *
 * Note that this is a direct port of the recipe given in python's itertools
 * @param {Iterable.<T>} iterable
 * @param {number} r
 * @yield {T}
 */
exports.combinations = function* combinations(iterable, r) {
    const pool = Array.from(iterable);
    const n = pool.length;
    if (r > n) {
        return;
    }
    indices = [...Array(r).keys()];

    yield Array.from(indices.map((i) => pool[i]));
    while (true) {
        let broken = false;
        let i = r - 1;
        for (; i > -1; i--) {
            if (indices[i] !== i + n - r) {
                broken = true;
                break;
            }
        }
        if (!broken) {
            return;
        }
        indices[i] += 1;
        for (let j = i + 1; j < r; j += 1) {
            indices[j] = indices[j-1] + 1;
        }
        yield Array.from(indices.map((i) => pool[i]));
    }
};

/**
 * Iterate over the different combinations of the elements in a given iterable
 *
 * Note that this is a direct port of the recipe given in python's itertools
 * @param {Iterable.<T>} iterable
 * @param {number} r
 * @yield {T}
 */
exports.combinationsWithReplacement = function* combinationsWithReplacement(iterable, r) {
    const pool = Array.from(iterable);
    const n = pool.length;
    if (r > n) {
        return;
    }
    indices = [...Array(r).keys()];

    yield Array.from(indices.map((i) => pool[i]));
    while (true) {
        let broken = false;
        let i = r - 1;
        for (; i > -1; i--) {
            if (indices[i] !== i + n - r) {
                broken = true;
                break;
            }
        }
        if (!broken) {
            return;
        }
        indices.fill(indices[i] + 1, i, r);
        yield Array.from(indices.map((i) => pool[i]));
    }
};

/**
 * Iterate over the abundant numbers
 * @param {null | number} stop
 * @yield {number}
 */
exports.abundants = function* abundants(stop = null) {
    for (let x = 12; !stop || x < stop; x++) {
        let sum = 0;
        for (const y of factors.properDivisors(x)) {
            sum += y;
        }
        if (sum > x) {
            yield x;
        }
    }
};

const factors = require('./factors.js');
