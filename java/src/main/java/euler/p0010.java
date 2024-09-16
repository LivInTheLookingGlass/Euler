/*
Project Euler Problem 10

Problem:

The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/
package euler;

import euler.lib.Primes;

public class p0010 implements IEuler {
    @Override
    public Object answer() {
        return Primes.primesUntil(2000000L)
                     .filter(i -> i != null)
                     .reduce(0L, Long::sum);
    }
}