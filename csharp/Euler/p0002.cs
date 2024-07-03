/*
Project Euler Problem 2

This is a port of the optimized version found in python. For a proof of why this
works, see that implementation

Problem:

Each new term in the Fibonacci sequence is generated by adding the previous two
terms. By starting with 1 and 2, the first 10 terms will be:

1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

By considering the terms in the Fibonacci sequence whose values do not exceed
four million, find the sum of the even-valued terms.
*/
using System;

namespace Euler
{
    public class p0002 : IEuler
    {
        public Task<Int64> Answer()
        {
            Int64 answer = 0,
                  i = 2,
                  j = 8,
                  tmp = 0;
            while (i < 4000000)
            {
                answer += i;
                tmp = 4 * j + i;
                i = j;
                j = tmp;
            }
            return Task.FromResult<Int64>(answer);
        }
    }
}
