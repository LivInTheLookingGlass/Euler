/*
Project Euler Problem 24

This one was fairly easy for code golf, thanks to the port of Python's itertools

Problem:

A permutation is an ordered arrangement of objects. For example, 3124 is one
possible permutation of the digits 1, 2, 3 and 4. If all of the permutations
are listed numerically or alphabetically, we call it lexicographic order. The
lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4,
5, 6, 7, 8 and 9?
*/
use itertools::Itertools;

use crate::include::utils::Answer;

pub fn p0024() -> Answer {
    return Answer::Int(
        (0..10)
            .permutations(10)
            .nth(999999)
            .unwrap()
            .into_iter()
            .map(|y| y.to_string())
            .fold("".to_owned(), |y, z| y + &z)
            .parse::<i128>()
            .unwrap()
    );
}
