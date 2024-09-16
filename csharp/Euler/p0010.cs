/*
Project Euler Problem 10

Problem:

The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/
using System;

namespace Euler
{
    public class p0010 : IEuler
    {
        public object Answer()
        {
            return Prime.Primes<long>(2000000).Sum();
        }
    }
}
