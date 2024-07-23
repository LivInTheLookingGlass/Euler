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

pub fn n_choose_r<I: NumAssign + From<i8> + From<u64> + PartialOrd>(n: u64, r: u64) -> I {
    // slow path for larger numbers
    let mut answer: I = one();
    let sn: usize = n.into();
    let sr: usize = r.into();
    let mut tmp: I;
    let mut factors: Vec<i8> = vec![0; n + 1];
    // collect factors of final number
    for i in 2..=sn {
        factors[i] = 1;
    }
    // negative factor values indicate need to divide
    for i in 2..=sr {
        factors[i] -= 1;
    }
    for i in 2..=(sn - sr) {
        factors[i] -= 1;
    }
    // this loop reduces to prime factors only
    for i in (1..sn).rev() {
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
    while i <= sn {
        while factors[i] > 0 {
            tmp = answer;
            answer *= i.into();
            while answer < tmp && j <= sn {
                while factors[j] < 0 {
                    tmp /= j.into();
                    factors[j] += 1;
                }
                j += 1;
                answer = tmp * i.into();
            }
            if answer < tmp {
                return (-1).into();  // this indicates an overflow
            }
            factors[i] -= 1;
        }
        i += 1;
    }
    while j <= sn {
        while factors[j] < 0 {
            answer /= j.into();
            factors[j] += 1;
        }
        j += 1;
    }
    return answer;
}
