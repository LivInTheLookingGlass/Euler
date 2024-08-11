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

import euler.lib.Mathematics;

public class p0034 implements IEuler {
    @Override
    public Object answer() {
        int answer = 0;
        for (int x = 10; x < 100000; x += 1) {
            String xs = Integer.toString(x);
            int sum = 0;
            for (byte i = 0; i < xs.length(); i += 1)
                sum += (int) Mathematics.factorial(xs.charAt(i) - '0');
            if (sum == x)
                answer += x;
        }
        return (short) answer;
    }
}