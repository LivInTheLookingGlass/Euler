/*
Project Euler Problem 7

Problem:

By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that
the 6th prime is 13.

What is the 10 001st prime number?
*/
package euler;

import euler.lib.Primes;

public class p0007 implements IEuler {
    @Override
    public Object answer() {
        return (int) Primes.primes()
                           .skip(10000)
                           .findFirst()
                           .orElseThrow(() -> new RuntimeException("Prime number not found"));
    }
}