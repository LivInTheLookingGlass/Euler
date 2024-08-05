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
        public object Answer()
        {
            for (uint c = 3; ; c++)
            {
                uint c_square = c * c;
                for (uint b = 2; b < c; b++)
                {
                    uint b_square = b * b;
                    for (uint a = 1; a < b; a++)
                    {
                        uint a_square = a * a;
                        if (a_square + b_square == c_square && a + b + c == 1000)
                            return a * b * c;
                    }
                }
            }
        }
    }
}
