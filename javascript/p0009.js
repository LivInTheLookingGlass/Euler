/**
 * Project Euler Problem 9
 *
 * Brute force on this problem has been very effective, so why stop now
 *
 * Problem:
 *
 * A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
 * a**2 + b**2 = c**2
 *
 * For example, 3**2 + 4**2 = 9 + 16 = 25 = 5**2.
 *
 * There exists exactly one Pythagorean triplet for which a + b + c = 1000.
 * Find the product abc.
 *
 * @return {number}
 */
exports.p0009 = function() {
    for (let c = 3; ; c++) {
        let c_square = c * c;
        for (let b = 2; b < c; b++) {
            let b_square = b * b;
            for (let a = 1; a < b; a++) {
                let a_square = a * a;
                if (a_square + b_square == c_square && a + b + c === 1000) {
                    return a * b * c;
                }
            }
        }
    }
    return 0;
}
