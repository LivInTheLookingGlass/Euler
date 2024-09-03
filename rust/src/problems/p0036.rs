/*
Project Euler Problem 36

Rust implementing a `reverse_bits()` function made this much more pleasant than expected

Problem:

The decimal number, 585 = 10010010012 (binary), is palindromic in both bases.

Find the sum of all numbers, less than one million, which are palindromic in
base 10 and base 2.

(Please note that the palindromic number, in either base, may not include
leading zeros.)
*/
use crate::include::utils::{is_palindrome,Answer};

pub fn p0036() -> Answer {
    let mut answer: u64 = 0;
    for x in 1..1000000u64 {
        if is_palindrome(format!("{x:b}")) && is_palindrome(x) {
            answer += x;
        }
    }
    return Answer::Int(answer.into());
}
