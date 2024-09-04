/**
 * Project Euler Problem 76
 *
 * I ended up having to do this iteratively, which I'm not super happy with. I feel like there is almost certainly a
 * closed-form solution to this, but I was unable to figure it out.
 *
 * Problem:
 *
 * It is possible to write five as a sum in exactly six different ways:
 *
 * 4 + 1
 * 3 + 2
 * 3 + 1 + 1
 * 2 + 2 + 1
 * 2 + 1 + 1 + 1
 * 1 + 1 + 1 + 1 + 1
 *
 * How many different ways can one hundred be written as a sum of at least two
positive integers?
 *
 * @return {number}
 */
exports.p0076 = function() {
    let answer = 0;
    let sum = 100;
    const counts = [...Array(101)].fill(0);
    counts[2] = 100;
    while (counts[100] == 0) {
        counts[2] += 2;
        if (sum >= 100) {
            answer += 0 | ((100 + counts[2] - sum) / 2);
            let idx = 2;
            while (true) {
                counts[idx++] = 0;
                counts[idx] += idx;
                sum = 0;
                for (let i = idx - 1; i < 101; i += 1) {
                    sum += counts[i];
                }
                if (sum <= 100) {
                    break;
                }
            }
            counts[2] = 100 - sum - (sum % 2);
        }
        sum = counts.reduce((a, x) => a + x, 0);
    }
    return answer;
};
