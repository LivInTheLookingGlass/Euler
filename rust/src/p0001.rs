/*
Project Euler Problem 1

I did this in the traditional way, as I'm mostly using this folder as a way
to learn Rust

Problem:

If we list all the natural numbers below 10 that are multiples of 3 or 5, we
get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.
*/
pub fn p0001() -> i128 {
    let mut answer: u32 = 0;
    for i in (0..1000).step_by(3) {
        answer += i;
    }
    for i in (0..1000).step_by(5) {
        answer += i;
    }
    for i in (0..1000).step_by(15) {
        answer -= i;
    }
    return answer.into();
}
