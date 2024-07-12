#[cfg(test)]
use std::time::Duration;
#[cfg(test)]
use std::iter::zip;

use seq_macro::seq;
#[cfg(test)]
use rstest::rstest;
#[cfg(test)]
use itertools::Itertools;

seq!(N in 0001..=0002 {
mod p~N;
});
mod primes;

type ProblemType = fn() -> u64;
type ProblemRef<'a> = (&'a str, ProblemType, u64);
const ANSWERS: [ProblemRef; 2] = [
    ("p0001", p0001::p0001, 233168),
    ("p0002", p0002::p0002, 4613732),
//    ("p0003", p0003::p0003, 6857),
];

fn main() {
    let sieve = primes::primes().take(10);
    for i in sieve {
        println!("{}", i);
    }
    for (name, func, answer) in ANSWERS {
        let result = func();
        println!("Problem {} should return {}. Returned {}!", name, answer, result);
    }
}

#[cfg(test)]
seq!(N in 0..2 {
#[rstest]
#[timeout(Duration::new(60, 0))]
#(
#[case(N)]
)*
fn test_problem(#[case] idx: usize) -> Result<(), String> {
    let (_, func, answer) = ANSWERS[idx];
    let result = func();
    assert_eq!(answer, result);
    Ok(())
}
});


#[cfg(test)]
#[test]
fn test_primes() -> Result<(), String> {
    let primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113];
    let sieve = primes::primes().take(primes.len());
    for (p, s) in zip(primes, sieve) {
        assert_eq!(p, s);
    }
    Ok(())
}

#[cfg(test)]
#[test]
fn test_prime_factors() -> Result<(), String> {
    for v in primes::primes().take(15).combinations(2) {
        let p = v[0];
        let s = v[1];
        for f in primes::prime_factors(p * s) {
            assert!(f == p || f == s);
        }
    }
    Ok(())
}
