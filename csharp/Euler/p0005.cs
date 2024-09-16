/*
Project Euler Problem 5

Problem:

2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/
using System;

namespace Euler
{
    public class p0005 : IEuler
    {
        public object Answer()
        {
            int answer = 1;
            byte[] factorTracker = new byte[20], localFactorTracker = new byte[20];
            for (byte i = 2; i < 21; i++) {
                foreach (byte p in Prime.PrimeFactors(i))
                    localFactorTracker[p]++;
                for (byte j = 2; j < 20; j++) {
                    factorTracker[j] = Math.Max(factorTracker[j], localFactorTracker[j]);
                    localFactorTracker[j] = 0;
                }
            }
            for (byte i = 2; i < 20; i++)
                for (byte j = 0; j < factorTracker[i]; j++)
                    answer *= i;
            return answer;
        }
    }
}
