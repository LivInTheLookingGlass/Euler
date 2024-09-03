/**
 * Project Euler Problem 21
 *
 * Problem:
 * @return {number}
*/
exports.p0021 = function() {
    let answer = 0;
    const toCheck = [...Array(10000).keys()];
    for (const a of toCheck) {
        const b = d(a);
        if (a !== b && d(b) === a) {
            answer += a + b;
            if (b < 10000) {
                toCheck.splice(toCheck.find(b), 1);
            }
        }
    }
    return answer;
};

/**
 * @param {number} i
 * @return {number}
*/
function d(i) {
    return Array.from(factors.properDivisors(i)).reduce((x, y) => x + y, 0);
}

const factors = require('./lib/factors');
