#[cfg(test)]
use std::time::Duration;

use seq_macro::seq;
#[cfg(test)]
use rstest::rstest;

seq!(N in 0001..=0002 {
mod p~N;
});

type ProblemType = fn() -> u64;
type ProblemRef<'a> = (&'a str, ProblemType, u64);
const ANSWERS: [ProblemRef; 2] = [
    ("p0001", p0001::p0001, 233168),
    ("p0002", p0002::p0002, 4613732)
];

fn main() {
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
