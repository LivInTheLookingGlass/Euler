/**
 * Iterates over prime numbers using the Sieve of Eratosthenes.
 *
 * This function implements the `Sieve of Eratosthenes <https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes>`_. In
 * general, it will iterate over all of the prime numbers. Below is a gif (courtesy of Wikipedia) that demonstrates
 * the principle of the sieve.
 *
 * .. image:: https://upload.wikimedia.org/wikipedia/commons/9/94/Animation_Sieve_of_Eratosth.gif
 *      :alt: Any animated example of the Sieve of Eratosthenes"""
 * @param {number} n
 * @return {number}
 */
exports.modifiedEratosthenes = function * modifiedEratosthenes(n) {
    yield 2;
    yield 3;
    yield 5;
    yield 7;
    const sieve = new Map();
    const recurse = modifiedEratosthenes();
    recurse.next();
    let prime = recurse.next().value;
    if (prime !== 3) {
        throw new Error();
    }
    let prime_squared = prime * prime;
    let step = 2;
    for (let candidate = 9; ; candidate += 2) {
        if (sieve.has(candidate)) {  // if c is a multiple of some base prime, or
            step = sieve.get(candidate);
            sieve.delete(candidate);
        }
        else if (candidate < prime_squared) {  // prime, or
            yield candidate;
            continue;
        }
        else {  // the next base prime's square
            // if candidate != prime_squared:
            //     raise ValueError()
            step = prime * 2;
            prime = recurse.next().value;
            prime_squared = prime * prime;
        }
        let tc = candidate
        do {
            tc += step;  // the next multiple
        } while (sieve.has(tc))  // make sure to not overwrite another sieve entry
        sieve.set(tc, step);
    }
};
