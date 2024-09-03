/*
Project Euler Problem 25

Problem:

The Fibonacci sequence is defined by the recurrence relation:

    Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.

Hence the first 12 terms will be:

    F1 = 1
    F2 = 1
    F3 = 2
    F4 = 3
    F5 = 5
    F6 = 8
    F7 = 13
    F8 = 21
    F9 = 34
    F10 = 55
    F11 = 89
    F12 = 144

The 12th term, F12, is the first term to contain three digits.

What is the index of the first term in the Fibonacci sequence to contain 1000
digits?
*/
use crate::include::utils::Answer;

pub fn p0025() -> Answer {
    let mut answer: u64 = 0;
    let mut a: Vec<u64> = vec![0];
    let mut b: Vec<u64> = vec![1];
    loop {
        answer += 1;
        let mut overflow: bool = false;
        let mut result: u64;
//        println!("{:?} + {:?}", a, b);
        for i in 0..b.len() {
            (result, overflow) = b[i].overflowing_add(a[i] + overflow as u64);
            a[i] = b[i];
            b[i] = result;
        }
        if overflow {
            b.push(1);
            a.push(0);
        }
        // below approximates log10(a) >= 999
        if a.len() >= 52 && a[a.len() - 1] > (1 << 54) + (1 << 53) {
            break;
        }
    }
    return Answer::Int(answer.into());
}
