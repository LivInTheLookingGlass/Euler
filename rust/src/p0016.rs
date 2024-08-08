/*
Project Euler Problem 16

Problem:

2**15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2**1000?
*/
use crate::include::utils::Answer;

pub fn p0016() -> Answer {
    let mut numbers: Vec<u128> = vec![0; 9];
    let ten36: u128 = 1000000000000000000000000000000000000;
    numbers[0] = 1;
    for _ in 0..1000 {
        for number in numbers.iter_mut() {
            *number *= 2;
        }
        for j in 0..8 {
            if numbers[j] > ten36 {
                numbers[j + 1] += numbers[j] / ten36;
                numbers[j] %= ten36;
            }
        }
    }
    let mut answer: i128 = 0;
    let mut power: u128 = 1;
    for _ in 0..36 {
        for number in numbers.iter() {
            answer += ((number / power) % 10) as i128;
        }
        power *= 10;
    }
    return Answer::Int(answer);
}
