/*
Project Euler Problem 34

This ended up being a filtering problem. The problem with my solution is that I
am not satisfied with my filter at all. I feel like there is a more efficient
way to go about it.

Problem:

145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of
their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.
*/
package euler;

public class p0020 implements IEuler {
    @Override
    public Object answer() {
        long[] numbers = new long[11];
        long ten16 = 10000000000000000L;
        numbers[0] = 1;
        for (byte i = 2; i <= 100; i++) {
            for (byte j = 0; j < 10; j++)
                numbers[j] *= i;
            for (byte j = 0; j < 9; j++) {
                if (numbers[j] > ten16) {
                    numbers[j + 1] += numbers[j] / ten16;
                    numbers[j] %= ten16;
                }
            }
        }
        long answer = 0;
        long power = 1;
        for (byte i = 0; i < 19; i++) {
            for (byte j = 0; j < 10; j++)
                answer += (numbers[j] / power) % 10;
            power *= 10;
        }
        return (short) answer;
    }
}
