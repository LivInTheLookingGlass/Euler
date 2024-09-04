/*
Project Euler Problem 16

Problem:

2**15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2**1000?
*/
package euler;

public class p0016 implements IEuler {
    @Override
    public Object answer() {
        long[] numbers = new long[18];
        long ten17 = 100000000000000000L;
        numbers[0] = 1;
        for (short i = 0; i < 1000; i++) {
            for (byte j = 0; j < 18; j++)
                numbers[j] *= 2;
            for (byte j = 0; j < 17; j++)
                if (numbers[j] > ten17) {
                    numbers[j + 1] += numbers[j] / ten17;
                    numbers[j] %= ten17;
                }
        }
        long answer = 0;
        long power = 1;
        for (byte i = 0; i < 19; i++) {
            for (byte j = 0; j < 18; j++)
                answer += (numbers[j] / power) % 10;
            power *= 10;
        }
        return (short) answer;
    }
}