/*
Project Euler Problem 4

I couldn't figure out how to do this as efficiently as I would have liked. I am
SURE that there is a better way to check if a number is a palindrome, but I
could not think of one.

Problem:

A palindromic number reads the same both ways. The largest palindrome made from
the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/
use itertools::Itertools;

fn is_palindrome(x: u64) -> bool {
    let s = x.to_string();
    return s == s.chars().rev().collect::<String>();
}

pub fn p0004() -> u64 {
    let mut answer: u64 = 0;
    for v in (100..1000).combinations(2) {
        let p = v.into_iter().product();
        if is_palindrome(p) && p > answer {
            answer = p;
        }
    }
    return answer;
}

