use std::cmp::PartialOrd;

use num_traits::NumAssign;
use num_traits::one;

pub fn factorial<I: NumAssign + From<u8>>(n: u8) -> I {
    let mut answer: I = one();
    for i in 2..=n {
        answer *= i.into();
    }
    return answer
}

pub fn n_choose_r<I: Copy + From<u64> + NumAssign + PartialOrd>(n: usize, r: usize) -> I {
    // slow path for larger numbers
    let mut answer: I = one();
    let mut tmp: I;
    let mut factors: Vec<i8> = vec![0; n + 1];
    // collect factors of final number
    for i in 2..=n {
        factors[i] = 1;
    }
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
            tmp = answer;
            answer *= (i as u64).into();
            while answer < tmp && j <= n {
                while factors[j] < 0 {
                    tmp /= (j as u64).into();
                    factors[j] += 1;
                }
                j += 1;
                answer = tmp * (i as u64).into();
            }
            factors[i] -= 1;
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
