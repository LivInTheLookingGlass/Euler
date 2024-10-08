/*
Project Euler Problem 43

This was pretty easy to do with zip()

Revision 1:

Roughly halve runtime by making a special case for 1, 2

Problem:

The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order,
but it also has a rather interesting sub-string divisibility property.

Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:

    d2d3d4=406 is divisible by 2
    d3d4d5=063 is divisible by 3
    d4d5d6=635 is divisible by 5
    d5d6d7=357 is divisible by 7
    d6d7d8=572 is divisible by 11
    d7d8d9=728 is divisible by 13
    d8d9d10=289 is divisible by 17

Find the sum of all 0 to 9 pandigital numbers with this property.
*/
use itertools::Itertools;

use crate::include::utils::Answer;

pub fn p0043() -> Answer {
    let mut answer: u64 = 0;
    let divisibility: [u16; 6] = [3, 5, 7, 11, 13, 17];
    for d in (0..10u16).permutations(10) {
        if d[3] % 2 == 1{
            continue;
        }
        let mut broken = false;
        for ((&a, &b, &c), divisor) in d.iter().tuple_windows::<(_,_,_)>().skip(2).take(6).zip(divisibility) {
            if (a * 100 + b * 10 + c) % divisor != 0 {
                broken = true;
                break;
            }
        }
        if !broken {
            answer += d.into_iter().fold(0u64, |acc, x| acc * 10 + x as u64);
        }
    }
    return Answer::Int(answer.into());
}
