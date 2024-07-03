use rstest::rstest;
mod p0001;

const ANSWERS: [(&str, fn() -> u64, u64); 1] = [
    ("p0001", p0001::p0001, 233168)
];

fn main() {
    for (name, func, answer) in ANSWERS {
        let result = func();
        println!("Problem {} should return {}. Returned {}!", name, answer, result);
    }
}

#[rstest]
#[case(0)]
fn test_problem(#[case] idx: usize) -> Result<(), String> {
    let (_, func, answer) = ANSWERS[idx];
    let result = func();
    assert_eq!(answer, result);
    Ok(())
}
