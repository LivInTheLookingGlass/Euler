/*
Project Euler Problem 37

I was surprised how fast my brute-force solution went, but it worked

Problem:

The number 3797 has an interesting property. Being prime itself, it is possible
to continuously remove digits from left to right, and remain prime at each
stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797,
379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from left to
right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
*/
use crate::include::primes::{is_prime,primes};
use crate::include::utils::Answer;

pub fn p0037() -> Answer {
    let mut answer: u64 = 0;
    let mut count: u64 = 0;
    for p in primes::<u64>() {
        if count == 11 {
            break;
        }
        else if p < 10 {
            continue;
        }
        else {
            let mut left = p;
            let mut right = p;
            while is_prime(right) {
                right /= 10;
            }
            if right != 0 {
                continue;
            }
            while is_prime(left) {
                let mut x = 10;
                while x < left {
                    x *= 10;
                }
                left %= x / 10;
            }
            if left != 0 {
                continue;
            }
            answer += p;
            count += 1;
        }
    }
    return Answer::Int(answer.into());
}
