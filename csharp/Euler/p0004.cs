/*
Project Euler Problem 4

I couldn't figure out how to do this as efficiently as I would have liked. I am
SURE that there is a better way to check if a number is a palindrome, but I
could not think of one.

Problem:

A palindromic number reads the same both ways. The largest palindrome made from
the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/
using System;

namespace Euler
{
    public class p0004 : IEuler
    {
        private static string Reverse(string s)
        {
            char[] charArray = s.ToCharArray();
            Array.Reverse(charArray);
            return new string(charArray);
        }

        private static bool IsPalindrome(Int64 x)
        {
            string rep = x.ToString();
            return rep == Reverse(rep);
        }

        public Task<Int64> Answer()
        {
            Int64 answer = 0;
            for (int v = 101; v < 1000; v++)
            {
                for (int u = 100; u < v; u++)
                {
                    Int64 p = u * v;
                    if (IsPalindrome(p) && p > answer)
                    {
                        answer = p;
                    }
                }
            }
            return Task.FromResult<Int64>(answer);
        }
    }
}
