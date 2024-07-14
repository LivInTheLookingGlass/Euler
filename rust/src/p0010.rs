use crate::primes::primes;

pub fn p0010() -> u64 {
    return primes::<u64>().take_while(|&p| p < 2000000).sum();
}
