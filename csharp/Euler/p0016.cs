/*
Project Euler Problem 16

Problem:

2**15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2**1000?
*/
using System;

namespace Euler
{
    public class p0016 : IEuler
    {
        public object Answer()
        {
            ulong[] numbers = new ulong[16];
            const ulong ten17 = 100000000000000000;
            numbers[0] = 1;
            for (ushort i = 0; i < 1000; i++)
            {
                for (byte j = 0; j < 16; j++)
                {
                    numbers[j] *= 2;
                }
                for (byte j = 0; j < 15; j++)
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
                for (byte j = 0; j < 16; j++)
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


