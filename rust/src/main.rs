#[cfg(test)]
use std::env::var_os;
#[cfg(test)]
use std::iter::zip;
#[cfg(test)]
use std::time::{Duration,Instant};

use seq_macro::seq;
#[cfg(test)]
use rstest::rstest;
#[cfg(test)]
use itertools::Itertools;

pub mod include;
use include::math;
use include::primes;
seq!(N in 0001..=0020 {
mod p~N;
});
mod p0022;
mod p0024;
mod p0034;
mod p0069;
mod p0076;
mod p0077;
mod p0087;
mod p0357;
mod p0836;

type ProblemType = fn() -> i128;
type ProblemRef<'a> = (&'a u32, ProblemType, bool, i128);

fn get_problem<'b>(n: u32) -> ProblemRef<'b> {
    return match n {
        1 =>   (  &1, p0001::p0001, false, 233168),
        2 =>   (  &2, p0002::p0002, false, 4613732),
        3 =>   (  &3, p0003::p0003, false, 6857),
        4 =>   (  &4, p0004::p0004, false, 906609),
        5 =>   (  &5, p0005::p0005, false, 232792560),
        6 =>   (  &6, p0006::p0006, false, 25164150),
        7 =>   (  &7, p0007::p0007, false, 104743),
        8 =>   (  &8, p0008::p0008, false, 23514624000),
        9 =>   (  &9, p0009::p0009, false, 31875000),
        10 =>  ( &10, p0010::p0010, false, 142913828922),
        11 =>  ( &11, p0011::p0011, false, 70600674),
        12 =>  ( &12, p0012::p0012, false, 76576500),
        13 =>  ( &13, p0013::p0013, false, 5537376230),
        14 =>  ( &14, p0014::p0014, false, 837799),
        15 =>  ( &15, p0015::p0015, false, 137846528820),
        16 =>  ( &16, p0016::p0016, false, 1366),
        17 =>  ( &17, p0017::p0017, false, 21124),
        18 =>  ( &18, p0018::p0018, false, 1074),
        19 =>  ( &19, p0019::p0019, false, 171),
        20 =>  ( &20, p0020::p0020, false, 648),
        22 =>  ( &22, p0022::p0022, false, 871198282),
        24 =>  ( &24, p0024::p0024, false, 2783915460),
        34 =>  ( &34, p0034::p0034, false, 40730),
        69 =>  ( &69, p0069::p0069, false, 510510),
        76 =>  ( &76, p0076::p0076, false, 190569291),
        77 =>  ( &77, p0077::p0077, false, 71),
        87 =>  ( &87, p0087::p0087, false, 1097343),
        357 => (&357, p0357::p0357, true, 1739023853137),
        836 => (&836, p0836::p0836, false, i128::from_ne_bytes(*b"\x00\x00aprilfoolsjoke")),
        _ => panic!(),
    };
}

#[cfg(not(test))]
fn main() {
    let sieve = primes::primes::<u64>().take(10);
    for i in sieve {
        println!("{}", i);
    }
    let mut answers: Vec<u32> = (1..=20).collect();
    answers.push(22);
    answers.push(24);
    answers.push(34);
    answers.push(69);
    answers.push(76);
    answers.push(77);
    answers.push(87);
    answers.push(357);

    for id  in answers {
        let (_, func, _, answer) = get_problem(id);
        let result = func();
        println!("Problem {} should return {}. Returned {}!", id, answer, result);
    }
}

#[cfg(test)]
seq!(N in 01..=20 {
#[rstest]
#(
#[case::problem_~N(N)]
)*
#[case::problem_22(22)]
#[case::problem_24(24)]
#[case::problem_34(34)]
#[case::problem_69(69)]
#[case::problem_76(76)]
#[case::problem_77(77)]
#[case::problem_87(87)]
// #[case::problem_357(357)]
#[case::problem_836(836)]
fn test_problem(#[case] id: u32) -> Result<(), String> {
    let (_, func, slow, answer) = get_problem(id);
    let start = Instant::now();
    let result = func();
    let elapsed = start.elapsed();
    assert_eq!(answer, result);
    if !slow && var_os("TERMUX_VERSION").is_none() {
        assert!(elapsed <= Duration::new(60, 0));
    }
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
