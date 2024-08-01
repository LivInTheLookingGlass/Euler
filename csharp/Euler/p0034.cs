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
using System;

namespace Euler
{
    public class p0034 : IEuler
    {
        public object Answer()
        {
            int answer = 0;
            for (int x = 10; x < 100000; x += 1)
            {
                string xs = x.ToString();
                int sum = 0;
                for (byte i = 0; i < xs.Length; i += 1)
                {
                    sum += (int)Mathematics.Factorial((ulong)(xs[i] - '0'));
                }
                if (sum == x)
                {
                    answer += x;
                }
            }
            return answer;
        }
    }
}
