/*
Project Euler Problem 20

Problem:

n! means n × (n − 1) × ... × 3 × 2 × 1

For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100!
*/

pub fn p0020() -> i128 {
    let mut numbers: Vec<u128> = vec![0; 5];
    let ten36: u128 = 1000000000000000000000000000000000000;
    numbers[0] = 1;
    for i in 2..=100 {
        for number in numbers {
            number *= i;
        }
        for j in 0..4 {
            if numbers[j] > ten36 {
                numbers[j + 1] += numbers[j] / ten36;
                numbers[j] %= ten36;
            }
        }
    }
    let mut answer: i128 = 0;
    let mut power: u128 = 1;
    for _ in 0..36 {
        for number in numbers {
            answer += ((number / power) % 10) as i128;
        }
        power *= 10;
    }
    return answer;
}
