/*
Project Euler Problem 7

Problem:

By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that
the 6th prime is 13.

What is the 10 001st prime number?
*/
using System;

namespace Euler
{
    public class p0007 : IEuler
    {
        public object Answer()
        {
            int i = 0;
            foreach (long p in Prime.Primes<long>())
                if (i++ == 10000)
                    return (int)p;
            return -1;
        }
    }
}
