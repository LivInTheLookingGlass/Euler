#[cfg(test)]
use std::time::Duration;
#[cfg(test)]
use std::iter::zip;

use seq_macro::seq;
#[cfg(test)]
use rstest::rstest;
#[cfg(test)]
use itertools::Itertools;

seq!(N in 0001..=0012 {
mod p~N;
});
mod p0015;
mod p0076;
mod math;
mod primes;

type ProblemType = fn() -> i128;
type ProblemRef<'a> = (&'a str, ProblemType, i128);
const ANSWERS: [ProblemRef; 14] = [
    ("p0001", p0001::p0001, 233168),
    ("p0002", p0002::p0002, 4613732),
    ("p0003", p0003::p0003, 6857),
    ("p0004", p0004::p0004, 906609),
    ("p0005", p0005::p0005, 232792560),
    ("p0006", p0006::p0006, 25164150),
    ("p0007", p0007::p0007, 104743),
    ("p0008", p0008::p0008, 23514624000),
    ("p0009", p0009::p0009, 31875000),
    ("p0010", p0010::p0010, 142913828922),
    ("p0011", p0011::p0011, 70600674),
    ("p0012", p0012::p0012, 76576500),
    ("p0015", p0015::p0015, 137846528820),
    ("p0034", p0034::p0034, 40730),
    ("p0076", p0076::p0076, 190569291),
];

fn main() {
    let sieve = primes::primes::<u64>().take(10);
    for i in sieve {
        println!("{}", i);
    }
    for (name, func, answer) in ANSWERS {
        let result = func();
        println!("Problem {} should return {}. Returned {}!", name, answer, result);
    }
}

#[cfg(test)]
seq!(N in 0..14 {
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
    let sieve = primes::primes::<u32>().take(primes.len());
    for (p, s) in zip(primes, sieve) {
        assert_eq!(p, s);
    }
    Ok(())
}

#[cfg(test)]
#[test]
fn test_prime_factors() -> Result<(), String> {
    for v in primes::primes_until::<u32>(256).combinations(2) {
        let p = v[0];
        let s = v[1];
        assert!(primes::is_prime(p));
        assert!(primes::is_prime(s));
        assert!(primes::is_composite(p * s) != 0);
        for f in primes::prime_factors(p * s) {
            assert!(primes::is_prime(f));
            assert!(f == p || f == s);
        }
    }
    Ok(())
}
