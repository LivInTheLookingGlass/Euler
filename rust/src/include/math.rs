use std::cmp::PartialOrd;
use std::fmt::Debug;
use std::mem::size_of;

use num_traits::NumAssign;
use num_traits::one;
use num_traits::CheckedMul;

const MAX_FACTORIAL: [u8; 16] = [
    5, // u8
    8, // u16
    10, 12, // u32
    14, 16, 18, 20, // u64
    22, 24, 25, 27, 29, 30, 32, 34 // u128
];

pub fn factorial<I>(n: u8) -> I
where I: NumAssign + From<u8>
{
    let mut answer: I = one();
    for i in 2..=n {
        answer *= i.into();
    }
    return answer
}

pub fn n_choose_r<I>(n: usize, r: usize) -> I
where I: Copy + From<u8> + From<u64> + NumAssign + PartialOrd + CheckedMul + Debug
{
    if n < r {
        panic!("Out of function's bounds");
    }
    if n < MAX_FACTORIAL[size_of::<I>() - 1] as usize {
        return factorial::<I>(n as u8) / factorial::<I>(r as u8) / factorial::<I>((n - r) as u8);
    }
    // slow path for larger numbers
    let mut answer: I = one();
    let mut factors: Vec<i8> = vec![1; n + 1];
    factors[0] = 0;
    factors[1] = 0;
    // negative factor values indicate need to divide
    for i in 2..=r {
        factors[i] -= 1;
    }
    for i in 2..=(n - r) {
        factors[i] -= 1;
    }
    // this loop reduces to prime factors only
    for i in (1..n).rev() {
        for j in 2..i {
            if i % j == 0 {
                factors[j] += factors[i];
                factors[i / j] += factors[i];
                factors[i] = 0;
                break;
            }
        }
    }
    let mut i: usize = 2;
    let mut j: usize = 2;
    while i <= n {
        while factors[i] > 0 {
            let mut result = answer.checked_mul(&(i as u64).into());
            while result.is_none() && j <= n {
                while factors[j] < 0 {
                    answer /= (j as u64).into();
                    factors[j] += 1;
                }
                j += 1;
                result = answer.checked_mul(&(i as u64).into());
            }
            factors[i] -= 1;
            answer = result.unwrap_or_else(|| panic!("nCr overflow: {:?} * {}", answer, i));
        }
        i += 1;
    }
    while j <= n {
        while factors[j] < 0 {
            answer /= (j as u64).into();
            factors[j] += 1;
        }
        j += 1;
    }
    return answer;
}
