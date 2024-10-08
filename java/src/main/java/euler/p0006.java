/*
Project Euler Problem 6

This turned out to be really easy

Problem:

The sum of the squares of the first ten natural numbers is,
1**2 + 2**2 + ... + 10**2 = 385

The square of the sum of the first ten natural numbers is,
(1 + 2 + ... + 10)**2 = 55**2 = 3025

Hence the difference between the sum of the squares of the first ten natural
numbers and the square of the sum is 3025 − 385 = 2640.

Find the difference between the sum of the squares of the first one hundred
natural numbers and the square of the sum.
*/
package euler;

public class p0006 implements IEuler {
    @Override
    public Object answer() {
        int sum_of_squares = 0, sum = 0;
        for (int i = 1; i < 101; i++) {
            sum += i;
            sum_of_squares += i * i;
        }

        int square_of_sum = sum * sum;
        return square_of_sum - sum_of_squares;
    }
}