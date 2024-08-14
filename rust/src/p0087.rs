/*
Project Euler Problem 87

I ended up having to do this with recursion, which I normally do not like to
use that much. Small changes can have large effects on later results. Still,
this seems to work for the moment.

Revision 1:

Shorten the code slightly to take advantage of the primes_until() stop argument.
Probably loses performance slightly.

Problem:

The smallest number expressible as the sum of a prime square, prime cube, and
prime fourth power is 28. In fact, there are exactly four numbers below fifty
that can be expressed in such a way:

28 = 2**2 + 2**3 + 2**4
33 = 3**2 + 2**3 + 2**4
49 = 5**2 + 2**3 + 2**4
47 = 2**2 + 3**3 + 2**4

How many numbers below fifty million can be expressed as the sum of a prime
square, prime cube, and prime fourth power?
*/
use std::collections::HashSet;

use crate::include::primes::primes_until;
use crate::include::utils::Answer;


pub fn p0087() -> Answer {
    let mut seen: HashSet<u64> = HashSet::new();
    let root2_50m = f64::powf(50_000_000.0, 1.0 / 2.0).floor() as u64;
    let root3_50m = f64::powf(50_000_000.0, 1.0 / 3.0).floor() as u64;
    let root4_50m = f64::powf(50_000_000.0, 1.0 / 4.0).floor() as u64;
    for x in primes_until(root2_50m) {
        let x2 = x * x;
        for y in primes_until(root3_50m) {
            let y3 = y * y * y;
            for z in primes_until(root4_50m) {
                let total = x2 + y3 + z * z * z * z;
                if total < 50_000_000 {
                    seen.insert(total);
                }
                else {
                    break;
                }
            }
        }
    }
    return Answer::Int((seen.len() as u64).into());
}
