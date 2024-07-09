use std::collections::HashMap;

pub struct ModifiedEratosthenes {
    sieve: HashMap<u64, u64>,
    prime: u64,
    candidate: u64,
    recurse: Option<Box<ModifiedEratosthenes>>
}

impl ModifiedEratosthenes {
    pub fn new() -> ModifiedEratosthenes {
        return ModifiedEratosthenes{
            sieve: HashMap::new(),
            prime: 0,
            candidate: 2,
            recurse: None
        };
    }
}

impl Iterator for ModifiedEratosthenes {
    type Item = u64;

    fn next(&mut self) -> Option<Self::Item> {
        if self.candidate == 2 {
            self.candidate = 3;
            self.prime = 3;
            println!("Returning 2");
            return Some(2);
        }
        let mut candidate = self.candidate;
        self.candidate += 2;
        loop {
            let prime_squared = self.prime * self.prime;
            println!("Candidate: {}", candidate);
            let step: u64;
            if self.sieve.contains_key(&candidate) {
                step = self.sieve.remove(&candidate)?;
                println!("Candidate in cache as {}", step);
            }
            else if candidate < prime_squared {
                println!("Candidate not in cache, but less than {}", prime_squared);
                return Some(candidate);
            }
            else {
                if candidate != prime_squared {
                    panic!("Something has gone wrong in the sieve");
                }
                step = self.prime * 2;
                if self.recurse.is_none() {
                    self.recurse = Some(Box::new(ModifiedEratosthenes::new()));
                    let mut recursed = self.recurse.take()?;
                    let _ = (*recursed).next();
                }
                let mut recursed = self.recurse.take()?;
                self.prime = ((*recursed).next())?;
            }
            println!("This is the good part");
            candidate += step;
            while self.sieve.contains_key(&candidate) {
                candidate += step;
            }
            self.sieve.insert(candidate, step);
        }
    }
}