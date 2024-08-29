/*
Project Euler Problem 41

Once I found out where the end was, it seemed to be relatively easy

Problem:

We shall say that an n-digit number is pandigital if it makes use of all the
digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is
also prime.

What is the largest n-digit pandigital prime that exists?
*/
use crate::include::primes::primes;
use crate::include::utils::Answer;

pub fn p0041() -> Answer {
    let mut answer: i64 = -1;
    for p in primes::<i64>() {
        let cur_digits = p.to_string();
        let num_digits = cur_digits.len();
        if num_digits > 7 {
            break;
        }
        if cur_digits.bytes().any(|b| ((b - b'0') as usize > num_digits || cur_digits.bytes().filter(|c| *c == b).count() != 1)) {
            continue;
        }
        if p > answer {
            answer = p;
        }
    }
    return Answer::Int(answer.into());
}
