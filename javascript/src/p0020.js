/**
 * Project Euler Problem 20
 *
 * Problem:
 * @return {number}
 */
exports.p0020 = function() {
    const ten13 = 10000000000000;
    const numbers = [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    for (let i = 2; i <= 100; i++) {
        for (let j = 0; j < numbers.length; j++) {
            numbers[j] *= i;
        }
        for (let j = 0; j < numbers.length - 1; j++) {
            if (numbers[j] > ten13) {
                numbers[j + 1] += 0 | (numbers[j] / ten13);
                numbers[j] %= ten13;
            }
        }
    }
    let answer = 0;
    let power = 1;
    while (power < ten13) {
        for (let j = 0; j < numbers.length; j++) {
            answer += 0 | ((numbers[j] / power) % 10);
        }
        power *= 10;
    }
    return answer;
};
