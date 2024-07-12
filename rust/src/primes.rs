use std::collections::HashMap;

pub struct Eratosthenes {
    sieve: HashMap<u64, Vec<u64>>,
    prime: u64,
    candidate: u64,
    limit: u64,
}

impl Default for Eratosthenes {
    fn default() -> Self {
        return Eratosthenes{
            sieve: HashMap::new(),
            prime: 0,
            candidate: 2,
            limit: u64::MAX,
        };
    }
}

impl Eratosthenes {
    pub fn new() -> Eratosthenes {
        return Default::default();
    }

    pub fn with_limit(limit: u64) -> Eratosthenes {
        let mut ret: Eratosthenes = Default::default();
        ret.limit = limit;
        return ret;
    }
}

impl Iterator for Eratosthenes {
    type Item = u64;

    fn next(&mut self) -> Option<Self::Item> {
        fn next_prime(sieve: &mut HashMap<u64, Vec<u64>>, candidate: u64) -> u64 {
            match sieve.get(&candidate) {
                Some(numbers) => {
                    for num in numbers.to_owned() {
                        sieve
                            .entry(candidate + num)
                            .and_modify(|v| v.push(num))
                            .or_insert_with(|| vec![num]);
                    }
                    sieve.remove(&candidate);
                    return next_prime(sieve, candidate + 1);
                }
                None => {
                    sieve.insert(candidate * candidate, vec![candidate]);
                    return candidate;
                }
            }
        }

        self.prime = next_prime(&mut self.sieve, self.candidate);
        self.candidate = self.prime + 1; // This number will be the next to be tested

        if self.prime > self.limit {
            return None;
        }
        return Some(self.prime);
    }
}

pub struct PrimeFactors {
    number: u64
}

impl PrimeFactors {
    pub fn new(x: u64) -> PrimeFactors {
        return PrimeFactors{
            number: x
        };
    }
}

impl Iterator for PrimeFactors {
    type Item = u64;

    fn next(&mut self) -> Option<Self::Item> {
        for p in Eratosthenes::new() {
            if self.number % p == 0 {
                self.number = self.number / p;
                return Some(p);
            }
            else if self.number < p {
                break;
            }
        }
        return None;
    }
}
