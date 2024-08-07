/*
Project Euler Problem 20

Problem:

n! means n × (n − 1) × ... × 3 × 2 × 1

For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100!
*/
using System;

namespace Euler
{
    public class p0020 : IEuler
    {
        public object Answer()
        {
            ulong[] numbers = new ulong[10];
            const ulong ten17 = 100000000000000000;
            numbers[0] = 1;
            for (byte i = 2; i <= 100; i++)
            {
                for (byte j = 0; j < 10; j++)
                {
                    numbers[j] *= i;
                }
                for (byte j = 0; j < 9; j++)
                {
                    if (numbers[j] > ten17)
                    {
                        numbers[j + 1] += numbers[j] / ten17;
                        numbers[j] %= ten17;
                    }
                }
            }
            ulong answer = 0;
            ulong power = 1;
            for (byte i = 0; i < 19; i++)
            {
                for (byte j = 0; j < 10; j++)
                {
                    ulong value = numbers[j] / power;
                    answer += value % 10;
                }
                power *= 10;
            }
            return (ushort)answer;
        }
    }
}


