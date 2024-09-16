/*
Project Euler Problem 3

More lazy functions this time. Took a little while to figure out how to
eliminate the special case for 2.

Problem:

The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
*/
using System;

namespace Euler
{
    public class p0003 : IEuler
    {
        public object Answer()
        {
            return (short)Prime.PrimeFactors(600851475143).Max();
        }
    }
}
