/*
Project Euler Problem 34

This ended up being a filtering problem. The problem with my solution is that I
am not satisfied with my filter at all. I feel like there is a more efficient
way to go about it.

Problem:

145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of
their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.
*/
use crate::math::factorial;

pub fn p0034() -> i128 {
    let mut answer: u32 = 0;
    for x in 10..100000 {
        let string: String = x.to_string();
        let sum = 
            string.bytes()
                  .into_iter()
                  .fold(0, |a, b| a + factorial::<u32>(b - '0' as u8));
        if sum == x {
            answer += x;
        }
    }
    return answer.into();
}