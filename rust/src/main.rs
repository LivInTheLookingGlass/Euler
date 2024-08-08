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
use include::utils::{Answer,get_answer};
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

type ProblemType = fn() -> Answer;
type ProblemRef<'a> = (&'a usize, ProblemType, bool);

fn get_problem<'b>(n: usize) -> ProblemRef<'b> {
    return match n {
        1 =>   (  &1, p0001::p0001, false),
        2 =>   (  &2, p0002::p0002, false),
        3 =>   (  &3, p0003::p0003, false),
        4 =>   (  &4, p0004::p0004, false),
        5 =>   (  &5, p0005::p0005, false),
        6 =>   (  &6, p0006::p0006, false),
        7 =>   (  &7, p0007::p0007, false),
        8 =>   (  &8, p0008::p0008, false),
        9 =>   (  &9, p0009::p0009, false),
        10 =>  ( &10, p0010::p0010, false),
        11 =>  ( &11, p0011::p0011, false),
        12 =>  ( &12, p0012::p0012, false),
        13 =>  ( &13, p0013::p0013, false),
        14 =>  ( &14, p0014::p0014, false),
        15 =>  ( &15, p0015::p0015, false),
        16 =>  ( &16, p0016::p0016, false),
        17 =>  ( &17, p0017::p0017, false),
        18 =>  ( &18, p0018::p0018, false),
        19 =>  ( &19, p0019::p0019, false),
        20 =>  ( &20, p0020::p0020, false),
        22 =>  ( &22, p0022::p0022, false),
        24 =>  ( &24, p0024::p0024, false),
        34 =>  ( &34, p0034::p0034, false),
        69 =>  ( &69, p0069::p0069, false),
        76 =>  ( &76, p0076::p0076, false),
        77 =>  ( &77, p0077::p0077, false),
        87 =>  ( &87, p0087::p0087, false),
        357 => (&357, p0357::p0357, true),
        836 => (&836, p0836::p0836, false),
        _ => panic!(),
    };
}

#[cfg(not(test))]
fn main() {
    let sieve = primes::primes::<u64>().take(10);
    for i in sieve {
        println!("{}", i);
    }
    let mut answers: Vec<usize> = (1..=20).collect();
    answers.push(22);
    answers.push(24);
    answers.push(34);
    answers.push(69);
    answers.push(76);
    answers.push(77);
    answers.push(87);
    answers.push(357);

    for id  in answers {
        let (_, func, _) = get_problem(id);
        let answer = get_answer(id);
        let result = func();
        match (answer, result) {
            (Answer::String(e), Answer::String(r)) => println!("Problem {} should return {}. Returned {}!", id, e, r),
            (Answer::Int(e), Answer::Int(r)) => println!("Problem {} should return {}. Returned {}!", id, e, r),
            _ => panic!("Type mismatch in answer return"),
        }
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
fn test_problem(#[case] id: usize) -> Result<(), String> {
    let (_, func, slow) = get_problem(id);
    let answer = get_answer(id);
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
