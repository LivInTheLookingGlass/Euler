use std::collections::HashSet;
use std::cmp::Ord;
use std::hash::Hash;
use std::ops::{Add,Div,Mul,Rem};

use num_traits::{one,One,Zero};
use itertools::Itertools;

use crate::include::primes::prime_factors;

pub struct ProperDivisors<I>
{
    seen: HashSet<I>,
    factors: Vec<I>,
    current_batch: Vec<I>,
    curr_index: usize,
    next_size: usize,
}

pub fn proper_divisors<I>(num: I) -> ProperDivisors<I>
where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I>
{
    return ProperDivisors::<I>::new(num);
}

impl<I> ProperDivisors<I>
where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I>
{
    pub fn new(num: I) -> Self {
        return ProperDivisors::<I>{
            seen: HashSet::new(),
            factors: prime_factors(num).collect(),
            current_batch: vec![],
            curr_index: 0,
            next_size: 1,
        };
    }
}

impl<I> Iterator for ProperDivisors<I>
where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I> + Mul<Output=I>
{
    type Item = I;

    fn next(&mut self) -> Option<Self::Item> {
        loop {
            if self.next_size > self.factors.len() {
                return None;
            }
            if self.curr_index == self.current_batch.len() {
                self.current_batch = self.factors
                                        .iter()
                                        .cloned()
                                        .combinations(self.next_size)
                                        .map(|v| v.into_iter().fold(one(), |x, y| x * y))
                                        .collect();
                self.next_size += 1;
                self.curr_index = 0;
            }
            while self.curr_index < self.current_batch.len() {
                let result = self.current_batch[self.curr_index];
                self.curr_index += 1;
                if !self.seen.contains(&result) {
                    self.seen.insert(result);
                    return Some(result);
                }
            }
            self.current_batch.clear();
            self.curr_index = 0;
        }
    }
}
