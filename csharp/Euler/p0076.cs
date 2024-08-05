/*
Project Euler Problem 76

I ended up having to do this iteratively, which I'm not super happy with. I feel like there is almost certainly a
closed-form solution to this, but I was unable to figure it out.

Problem:

It is possible to write five as a sum in exactly six different ways:

4 + 1
3 + 2
3 + 1 + 1
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1

How many different ways can one hundred be written as a sum of at least two
positive integers?
*/
using System;

namespace Euler
{
    public class p0076 : IEuler
    {
        public object Answer()
        {
            byte idx;
            uint answer = 0;
            byte sum = 100;
            byte[] counts = new byte[101];
            counts[2] = 100;
            while (counts[100] == 0)
            {
                counts[2] += 2;
                if (sum >= 100)
                {
                    answer += (uint)(100 + counts[2] - sum) / 2;
                    idx = 2;
                    do
                    {
                        counts[idx] = 0;
                        idx += 1;
                        counts[idx] += idx;
                        sum = 0;
                        for (byte i = (byte)(idx - 1); i < 101; i += 1)
                            sum += counts[i];
                    } while (sum > 100);
                }
                sum = 0;
                for (byte i = 0; i < 101; i += 1)
                    sum += counts[i];
            }
            return answer;
        }
    }
}
