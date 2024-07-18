/*
Project Euler Problem 5

I solved this problem by testing all combinations of the various multiples. I
actually tried to solve this by hand before doing this, and it wasn't terribly
hard. The answer turns out to be (2**4 * 3**2 * 5 * 7 * 11 * 13 * 17 * 19)

Problem:

2520 is the smallest number that can be divided by each of the numbers from 1
to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the
numbers from 1 to 20?
*/
use itertools::Itertools;

pub fn p0005() -> i128 {
    let mut answer = u64::MAX;
    let group = 1..=20u64;
    for x in group.clone() {
        for multiples in group.clone().combinations(x as usize) {
            let num = multiples.into_iter().product();
            if num < answer && group.clone().all(|divisor| num % divisor == 0) {
                answer = num;
            }
        }
    }
    return answer.into();
}
