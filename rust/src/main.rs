#[cfg(test)]
use std::iter::zip;

#[cfg(all(test, target_os = "linux", target_env = "gnu"))]
use std::time::Duration;
#[cfg(test)]
use std::time::Instant;

use seq_macro::seq;
#[cfg(test)]
use rstest::rstest;
#[cfg(test)]
use itertools::Itertools;

pub mod include;
use include::primes;
use include::factors;
#[cfg(test)]
use include::math;
#[cfg(not(test))]
use include::problems::generate_supported_problems;
use include::problems::get_problem;
#[cfg(not(test))]
use include::utils::Answer;
use include::utils::get_answer;
seq!(N in 0001..=0024 {
pub mod p~N;
});
pub mod p0027;
pub mod p0034;
pub mod p0036;
pub mod p0037;
pub mod p0044;
pub mod p0045;
pub mod p0053;
pub mod p0059;
pub mod p0067;
pub mod p0069;
pub mod p0076;
pub mod p0077;
pub mod p0087;
pub mod p0187;
pub mod p0357;
pub mod p0836;


#[cfg(not(test))]
fn main() {
    let sieve = primes::primes::<u64>().take(10);
    for i in sieve {
        println!("{}", i);
    }
    for i in 4..100 {
        println!("{}: {:?}", i, factors::proper_divisors(i).collect::<Vec<u16>>());
    }
    let supported = generate_supported_problems(false);

    for id in supported {
        match get_problem(id) {
            Some((_, func, _)) => {
                let answer = get_answer(id);
                let result = func();
                match (answer, result) {
                    (Answer::String(e), Answer::String(r)) => println!("Problem {} should return {}. Returned {}!", id, e, r),
                    (Answer::Int(e), Answer::Int(r)) => println!("Problem {} should return {}. Returned {}!", id, e, r),
                    _ => panic!("Type mismatch in answer return"),
                }
            }
            None => panic!("Problem not found"),
        }
    }
}

#[cfg(test)]
seq!(N in 01..=20 {
#[rstest]
#(
#[case::problem_~N(N)]
)*
//#[case::problem_21(21)]
#[case::problem_22(22)]
#[case::problem_23(23)]
#[case::problem_24(24)]
#[case::problem_27(27)]
#[case::problem_34(34)]
#[case::problem_36(36)]
#[case::problem_37(37)]
#[case::problem_44(44)]
#[case::problem_45(45)]
#[case::problem_53(53)]
#[case::problem_59(59)]
#[case::problem_67(67)]
#[case::problem_69(69)]
#[case::problem_76(76)]
#[case::problem_77(77)]
#[case::problem_87(87)]
#[case::problem_187(187)]
// #[case::problem_357(357)]
#[case::problem_836(836)]
fn test_problem(#[case] id: usize) -> Result<(), String> {
    let Some((_, func, _slow)) = get_problem(id) else { panic!() };
    let answer = get_answer(id);
    let start = Instant::now();
    let result = func();
    let _elapsed = start.elapsed();
    assert_eq!(answer, result);
    #[cfg(all(target_os = "linux", target_env = "gnu"))]
    {
        if !_slow {
            assert!(
                _elapsed <= Duration::new(60, 0),
                "Should take at most 60s, but actually took {:?}",
                _elapsed
            );
        }
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

#[cfg(test)]
#[test]
fn test_proper_divisors() -> Result<(), String> {
    for i in 4..1024 {
        let divisors = factors::proper_divisors(i).collect::<Vec<u32>>();
        for &factor in divisors.iter() {
            if factor == 1 {
                continue;
            }
            assert!(divisors.iter().any(|&x| x * factor == i));
        }
    }
    Ok(())
}

#[cfg(test)]
#[test]
fn test_n_choose_r() -> Result<(), String> {
    for i in 0..68usize {
        for j in 0..i {
            assert_eq!((0..i).combinations(j).count() as u128, math::n_choose_r::<u128>(i, j));
        }
    }
    Ok(())
}
