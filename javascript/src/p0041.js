/**
 * Project Euler Problem 41
 *
 * Once I found out where the end was, it seemed to be relatively easy
 *
 * Problem:
 *
 * We shall say that an n-digit number is pandigital if it makes use of all the
 * digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is
 * also prime.
 *
 * What is the largest n-digit pandigital prime that exists?
 *
 * @return {number}
 */
exports.p0041 = function() {
    let answer = -1;
    for (const p of primes.primes()) {
        curDigits = p.toString();
        numDigits = curDigits.length;
        if (numDigits > 7) {
            break;
        }
        let cont = false;
        for (const digit of curDigits) {
            if (parseInt(digit) > numDigits || (curDigits.split(digit).length - 1) !== 1) {
                cont = true;
                break;
            }
        }
        if (cont) {
            continue;
        } else if (p > answer) {
            answer = p;
        }
    }
    return answer;
};

const primes = require('./lib/primes.js');
