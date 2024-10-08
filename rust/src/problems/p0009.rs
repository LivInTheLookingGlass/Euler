/*
Project Euler Problem 9



Problem:

A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
a**2 + b**2 = c**2

For example, 3**2 + 4**2 = 9 + 16 = 25 = 5**2.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/
use crate::include::utils::Answer;

pub fn p0009() -> Answer {
    for c in 3.. {
        let c_square = c * c;
        for b in 2..c {
            let b_square = b * b;
            for a in 1..b {
                let a_square = a * a;
                if a_square + b_square == c_square && a + b + c == 1000 {
                    return Answer::Int((a * b * c).into());
                }
            }
        }
    }
    unreachable!();
}
