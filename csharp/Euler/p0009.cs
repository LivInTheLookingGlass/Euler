/*
Project Euler Problem 9



Problem:

A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
a**2 + b**2 = c**2

For example, 3**2 + 4**2 = 9 + 16 = 25 = 5**2.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/
using System;

namespace Euler
{
    public class p0009 : IEuler
    {
        public Task<Int64> Answer()
        {
            for (int c = 3; ; c++)
            {
                int c_square = c * c;
                for (int b = 2; b < c; b++)
                {
                    int b_square = b * b;
                    for (int a = 1; a < b; a++)
                    {
                        int a_square = a * a;
                        if (a_square + b_square == c_square && a + b + c == 1000)
                        {
                            return Task.FromResult<Int64>(a * b * c);
                        }
                    }
                }
            }
        }
    }
}
