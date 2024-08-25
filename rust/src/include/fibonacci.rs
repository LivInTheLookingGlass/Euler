use std::ops::{Add,Mul};

use num_traits::{one,zero,One,Zero};

use crate::include::iter_cache::cache_iterator;

pub fn fib<I>() -> impl Iterator<Item = I> where I: Copy + Zero + One + Add + 'static {
    return cache_iterator(Fibonacci::<I>::new());
}

pub fn fib_by_3<I>() -> impl Iterator<Item = I> where I: Copy + Zero + One + Add + Mul + 'static {
    return cache_iterator(FibonacciBy3::<I>::new());
}

pub struct Fibonacci<I> {
    a: I,
    b: I,
}

impl<I> Default for Fibonacci<I> where I: Zero + One {
    fn default() -> Self {
        return Fibonacci::<I>{
            a: zero(),
            b: one(),
        };
    }
}

impl<I> Fibonacci<I> where I: Zero + One {
    pub fn new() -> Self {
        return Default::default();
    }
}

impl<I> Iterator for Fibonacci<I> where I: Zero + One + Add + Copy {
    type Item = I;

    fn next(&mut self) -> Option<Self::Item> {
        let prior_a = self.a;
        let prior_b = self.b;
        self.b = self.a + self.b;
        self.a = prior_b;
        return Some(prior_a);
    }
}

pub struct FibonacciBy3<I> {
    a: I,
    b: I,
}

impl<I> Default for FibonacciBy3<I> where I: Zero + One + Add + Copy {
    fn default() -> Self {
        let two = one::<I>() + one();
        return FibonacciBy3::<I>{
            a: zero(),
            b: two,
        };
    }
}

impl<I> FibonacciBy3<I> where I: Zero + One + Add + Copy {
    pub fn new() -> Self {
        return Default::default();
    }
}

impl<I> Iterator for FibonacciBy3<I> where I: Zero + One + Add + Mul + Copy {
    type Item = I;

    fn next(&mut self) -> Option<Self::Item> {
        let two = one::<I>() + one();
        let four = two + two;
        let prior_a = self.a;
        let prior_b = self.b;
        self.b = four * self.b + self.a;
        self.a = prior_b;
        return Some(prior_a);
    }
}
