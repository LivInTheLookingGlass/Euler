#[cfg(test)]
use std::iter::zip;
#[cfg(test)]
use std::fs::read_to_string;
#[cfg(test)]
use std::path::PathBuf;
#[cfg(all(test, target_os = "linux", target_env = "gnu"))]
use std::time::Duration;
#[cfg(test)]
use std::time::Instant;

#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
use wasm_bindgen::prelude::*;
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
use js_sys::Array;

#[cfg(test)]
use rstest::rstest;
#[cfg(test)]
use itertools::Itertools;
#[cfg(test)]
use seq_macro::seq;

pub mod problems;
pub mod include;
pub use crate::include::*;
pub use crate::include::problems::{generate_supported_problems,get_problem};
pub use crate::include::utils::*;

#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
#[wasm_bindgen]
pub fn run_problem(n: usize) -> JsValue {
    let Some((_, problem_function, _)) = get_problem(n) else { return JsValue::UNDEFINED };
    return match problem_function() {
        Answer::String(e) => JsValue::from_str(&e),
        Answer::Int(e) => JsValue::from(e),
    }
}

#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
#[wasm_bindgen]
pub fn get_problems(include_slow: bool) -> JsValue {
    let problems = generate_supported_problems(include_slow);
    let js_array = Array::new_with_length(problems.len() as u32);

    for (i, &item) in problems.iter().enumerate() {
        js_array.set(i as u32, item.into());
    }

    return JsValue::from(js_array);
}

#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
#[wasm_bindgen]
pub fn get_js_answer(n: usize) -> JsValue {
    return match get_answer(n) {
        Answer::String(e) => JsValue::from_str(&e),
        Answer::Int(e) => JsValue::from(e),
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
#[case::problem_25(25)]
#[case::problem_27(27)]
#[case::problem_34(34)]
#[case::problem_35(35)]
#[case::problem_36(36)]
#[case::problem_37(37)]
#[case::problem_41(41)]
#[case::problem_43(43)]
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
    let start = Instant::now();
    let result = func();
    let _elapsed = start.elapsed();
    assert_eq!(get_answer(id), result);
    #[cfg(all(target_os = "linux", target_env = "gnu"))]
    {
        assert!(
            _slow || _elapsed <= Duration::new(60, 0),
            "Should take at most 60s, but actually took {:?}",
            _elapsed
        );
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
        let &[p, s] = &v[..] else { panic!() };
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
            assert_eq!(
                (0..i).combinations(j).count() as u128,
                math::n_choose_r::<u128>(i, j)
            );
        }
    }
    Ok(())
}

#[cfg(test)]
#[rstest]
fn test_data_file(#[files("../_data/*")] path: PathBuf) -> Result<(), String> {
    assert_eq!(
        read_to_string(&path.as_path()
                            .to_str()
                            .unwrap()).unwrap(),
        get_data_file(&path.as_path()
                           .file_name()
                           .unwrap()
                           .to_str()
                           .unwrap())
    );
    Ok(())
}
