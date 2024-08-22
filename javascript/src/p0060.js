/**
 * Project Euler Problem 60
 *
 * Problem:
 *
 * The primes 3, 7, 109, and 673, are quite remarkable. By taking any two primes and concatenating them in any order the
 * result will always be prime. For example, taking 7 and 109, both 7109 and 1097 are prime. The sum of these four
 * primes, 792, represents the lowest sum for a set of four primes with this property.
 *
 * Find the lowest sum for a set of five primes for which any two primes concatenate to produce another prime.
 *
 * @return {number}
 */
exports.p0060 = function() {
    const iterator = primes.primes();
    const cachedPrimes = [3];
    iterator.next(); // 2 is excluded because higher even numbers can't be prime
    iterator.next();
    iterator.next(); // 5 is excluded because if a number ends with 5, it's divisible by 5
    const compat = new Map();
    for (const x of iterator) {
        const strX = String(x);
        for (const y of cachedPrimes) {
            if (primes.isPrime(Number(`${strX}${y}`)) && primes.isPrime(Number(`${y}${strX}`))) {
                for (const [a, b, c] of iters.combinations(compat.get(y) || new Set(), 3)) {
                    // remember these checks are commutative
                    if (compat.get(b).has(a) && compat.get(c).has(a) && compat.get(c).has(b)) {
                        const strA = String(a);
                        const strB = String(b);
                        const strC = String(c);
                        const concatenations = [
                            Number(`${strA}${strX}`),
                            Number(`${strX}${strA}`),
                            Number(`${strB}${strX}`),
                            Number(`${strX}${strB}`),
                            Number(`${strC}${strX}`),
                            Number(`${strX}${strC}`),
                        ];
                        if (concatenations.every(primes.isPrime)) {
                            return x + y + a + b + c;
                        }
                    }
                }
                if (!compat.has(x)) {
                    compat.set(x, new Set());
                }
                compat.get(x).add(y);
                if (!compat.has(y)) {
                    compat.set(y, new Set());
                }
                compat.get(y).add(x);
            }
        }
        cachedPrimes.push(x);
    }
    return -1;
};

const iters = require('./lib/iters.js');
const primes = require('./lib/primes.js');
