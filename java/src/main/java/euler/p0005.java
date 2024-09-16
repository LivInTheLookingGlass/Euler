/*
Project Euler Problem 5

Problem:

2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/
package euler;

import euler.lib.Primes;

public class p0005 implements IEuler {
    @Override
    public Object answer() {
        int answer = 1;
        int[] factorTracker = new int[20], localFactorTracker = new int[20];
        for (int i = 2; i < 21; i++) {
            Primes.primeFactors(i)
                  .mapToInt(Long::intValue)
                  .forEach(p -> localFactorTracker[p]++);
            for (int j = 2; j < 20; j++) {
                factorTracker[j] = Math.max(factorTracker[j], localFactorTracker[j]);
                localFactorTracker[j] = 0;
            }
        }
        for (int i = 2; i < 20; i++)
            for (int j = 0; j < factorTracker[i]; j++)
                answer *= i;
        return answer;
    }
}