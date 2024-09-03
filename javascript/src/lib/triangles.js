/**
 * Compute the factorial of a given number. Note that, unlike the version of this in other languages, this does not
 * guard against imprecision or overflow.
 * @param {Array<Array<number>>} triangle
 * @return {number}
 */
exports.reduceTriangle = function reduceTriangle(triangle) {
    centering = triangle[triangle.length - 1].length + 1;
    const potentialTotals = new Array(centering).fill(0);
    const _triangle = Array.from(triangle);
    _triangle.reverse();
    for (const parent of _triangle) {
        for (let i = 0; i < parent.length; i++) {
            potentialTotals[i] = Math.max(potentialTotals[i], potentialTotals[i + 1]) + parent[i];
        }
    }
    return potentialTotals[0];
};
