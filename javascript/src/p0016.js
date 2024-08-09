/**
 * Project Euler Problem 16
 *
 * Problem:
 * 2**15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
 *
 * What is the sum of the digits of the number 2**1000?
 * @return {number}
 */
exports.p0016 = function() {
    const ten13 = 10000000000000;
    const numbers = [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    for (let i = 0; i < 1000; i++) {
        for (let j = 0; j < numbers.length; j++) {
            numbers[j] *= 2;
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
