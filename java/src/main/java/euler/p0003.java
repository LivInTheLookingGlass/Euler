/*
Project Euler Problem 3

The lesson I've taken from these is that Streams are significantly more cumbersome in Java than in other languages

Problem:

The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
*/
package euler;

import java.util.Comparator;

import euler.lib.Primes;

public class p0003 implements IEuler {
    @Override
    public Object answer() {
        return (short) Primes.primeFactors(600851475143L)
                             .max(Comparator.naturalOrder())
                             .get()
                             .intValue();
    }
}