/*
Project Euler Problem 1

I know that this could be done faster with a traditional for loop, but I wanted
to see if iterators were reasonably possible in C, since it makes the prime
number infrastructure a lot easier to set up.

Problem:

If we list all the natural numbers below 10 that are multiples of 3 or 5, we
get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.
*/
package euler;

public class p0001 implements IEuler {
    @Override
    public Object answer() {
        int answer = 0;
        for (int i = 0; i < 1000; i += 3)
            answer += i;

        for (int i = 0; i < 1000; i += 5)
            answer += i;

        for (int i = 0; i < 1000; i += 15)
            answer -= i;

        return answer;
    }
}