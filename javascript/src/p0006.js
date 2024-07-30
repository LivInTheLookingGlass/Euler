/**
 * Project Euler Problem 6
 *
 * This turned out to be really easy
 *
 * Problem:
 *
 * The sum of the squares of the first ten natural numbers is,
 * 1**2 + 2**2 + ... + 10**2 = 385
 *
 * The square of the sum of the first ten natural numbers is,
 * (1 + 2 + ... + 10)**2 = 55**2 = 3025
 *
 * Hence the difference between the sum of the squares of the first ten natural
 * numbers and the square of the sum is 3025 − 385 = 2640.
 *
 * Find the difference between the sum of the squares of the first one hundred
 * natural numbers and the square of the sum.
 *
 * @return {number}
 */

exports.p0006 = function() {
    let sum = 1;
    let sumOfSquares = 1;
    for (let i = 2; i < 101; i++) {
        sumOfSquares += i * i;
        sum += i;
    }
    const squareOfSum = sum * sum;
    return squareOfSum - sumOfSquares;
};
