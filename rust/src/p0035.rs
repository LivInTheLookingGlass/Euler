/*
Project Euler Problem 35

Problem:

The number, 197, is called a circular prime because all rotations of the
digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71,
73, 79, and 97.

How many circular primes are there below one million?
*/
use crate::include::primes::is_prime;
use crate::include::utils::Answer;

pub fn p0035() -> Answer {
    let mut answer: u64 = 0;
    for x in 0..1000000 {
        if Rotations::new(x).all(is_prime) {
            answer += 1;
        }
    }
    return Answer::Int(answer.into());
}

struct Rotations {
    x: String,
    i: usize,
}

impl Rotations {
    pub fn new(x: u64) -> Self {
        return Rotations{
            x: x.to_string(),
            i: 0,
        };
    }
}

impl Iterator for Rotations {
    type Item = u64;

    fn next(&mut self) -> Option<Self::Item> {
        if self.i < self.x.len() {
            let result = (self.x[self.i..].to_owned() + self.x[..self.i]).parse::<u64>().unwrap();
            self.i += 1;
            return Some(result);
        }
        return None;
    }
}
