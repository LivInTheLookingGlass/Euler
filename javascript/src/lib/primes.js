const cache = [2, 3, 5, 7];
let lastCached = 7;

/**
 * Iterates over the prime numbers up to an (optional) limit, with caching.
 *
 * This iterator leverages the :js:func:`primes.modifiedEratosthenes` iterator, but adds
 * additional features. The biggest is a ``stop`` argument, which will prevent it
 * from yielding any numbers larger than that. The next is caching of any yielded
 * prime numbers.
 * @param {number | null} stop
 * @yield {number}
 */
function* primes(stop = null) {
    if (stop === null) {
        for (p of cache) {
            yield p;
        }
    } else {
        for (p of cache) {
            if (p < stop) {
                yield p;
            } else {
                break;
            }
        }
    }
    if (stop !== null && lastCached > stop) {
        return;
    }
    for (p of modifiedEratosthenes()) {
        if (p <= lastCached) {
            continue;
        }
        if (stop !== null && p > stop) {
            break;
        }
        cache.push(p);
        lastCached = p;
        yield p;
    }
}
exports.primes = primes;


/**
 * Iterates over prime numbers using the Sieve of Eratosthenes.
 *
 * This function implements the `Sieve of Eratosthenes <https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes>`_. In
 * general, it will iterate over all of the prime numbers. Below is a gif (courtesy of Wikipedia) that demonstrates
 * the principle of the sieve.
 *
 * .. image:: https://upload.wikimedia.org/wikipedia/commons/9/94/Animation_Sieve_of_Eratosth.gif
 *      :alt: Any animated example of the Sieve of Eratosthenes
 * @yield {number}
 */
function* modifiedEratosthenes() {
    yield 2;
    yield 3;
    yield 5;
    yield 7;
    const sieve = new Map();
    const recurse = primes();
    recurse.next();
    let prime = recurse.next().value;
    if (prime !== 3) {
        throw new Error();
    }
    let primeSquared = prime * prime;
    let step = 2;
    for (let candidate = 9; ; candidate += 2) {
        if (sieve.has(candidate)) { // if c is a multiple of some base prime, or
            step = sieve.get(candidate);
            sieve.delete(candidate);
        } else if (candidate < primeSquared) { // prime, or
            yield candidate;
            continue;
        } else { // the next base prime's square
            // if candidate != primeSquared:
            //     raise ValueError()
            step = prime * 2;
            prime = recurse.next().value;
            primeSquared = prime * prime;
        }
        let tc = candidate;
        do {
            tc += step; // the next multiple
        } while (sieve.has(tc)); // make sure to not overwrite another sieve entry
        sieve.set(tc, step);
    }
}
exports.modifiedEratosthenes = modifiedEratosthenes;


/**
 * Iterates over the prime factors of a number.
 *
 * @param {number} num
 * @yield {number}
 */
function* primeFactors(num) {
    if (num < 0) {
        yield -1;
        num = -num;
    }
    if (num === 0) {
        yield 0;
    } else {
        let root = Math.ceil(Math.sqrt(num));
        for (factor of primes()) {
            let modulo = num % factor;
            if (modulo == 0) {
                while (modulo == 0) { // double-check to call sqrt once
                    yield factor;
                    num /= factor;
                    modulo = num % factor;
                }
                root = Math.ceil(Math.sqrt(num));
            }
            if (num <= 1) {
                break;
            }
            if (factor > root) {
                yield num;
                break;
            }
        }
    }
}
exports.primeFactors = primeFactors;

/**
 * Iterates over the prime numbers (and their negatives) up to an (optional) limit, with caching.
 *
 * This iterator leverages the :js:func:`primes.primes` iterator.
 * @param {number | null} stop
 * @yield {number}
 */
function* primesAndNegatives(stop = null) {
    for (p of primes(stop)) {
        yield p;
        yield -p;
    }
}
exports.primesAndNegatives = primesAndNegatives;

/**
 * Tests if a number is composite
 * @param {number} n
 * @return {number} 0 if prime, or the first prime factor if not
 */
function isComposite(n) {
    const factors = primeFactors(n);
    const first = factors.next().value;
    if (factors.next().done) {
        return 0;
    }
    return first;
}
exports.isComposite = isComposite;

/**
 * Tests if a number is prime
 * @param {number} n
 * @return {boolean}
 */
function isPrime(n) {
    if (n < 2) {
        return false;
    }
    return !isComposite(n);
}
exports.isPrime = isPrime;
