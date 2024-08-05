/*
Project Euler Problem 14

This was easier to do in C# than I would have thought

Problem:

The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:
13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1

It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been
proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
*/
using System;

namespace Euler
{
    public class p0014 : IEuler
    {
        public object Answer()
        {
            uint biggestSeen = 0;
            ulong biggestIdx = 0;
            Dictionary<ulong, uint> cache = new();
            for (ulong x = 1; x < 1000000; x += 1)
            {
                uint result = CollatzLen(x, cache);
                if (result > biggestSeen)
                {
                    biggestSeen = result;
                    biggestIdx = x;
                }
            }
            return (uint)biggestIdx;
        }

        static uint CollatzLen(ulong n, IDictionary<ulong, uint> cache)
        {
            if (n == 1)
                return 0;
            else if (cache.ContainsKey(n))
                return cache[n];

            uint result;
            if (n % 2 == 0)
                result = 1 + CollatzLen(n / 2, cache);
            else
                result = 2 + CollatzLen((3 * n + 1) / 2, cache);
            cache.Add(n, result);
            return result;
        }
    }
}
