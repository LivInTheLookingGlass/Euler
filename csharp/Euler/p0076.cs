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
        public Task<object> Answer()
        {
            ushort idx;
            int answer = 0;
            int sum = 100;
            int[] counts = new int[101];
            counts[2] = 100;
            while (counts[100] == 0)
            {
                counts[2] += 2;
                if (sum >= 100)
                {
                    answer += (100 + counts[2] - sum) / 2;
                    idx = 2;
                    while (true)
                    {
                        counts[idx] = 0;
                        idx += 1;
                        counts[idx] += idx;
                        // sum = Enumerable.Sum(counts);
                        sum = 0;
                        for (int i = idx - 1; i < 101; i += 1)
                            sum += counts[i];
                        if (sum <= 100)
                            break;
                    }
                    counts[2] = 100 - sum - (sum % 2);
                }
                sum = Enumerable.Sum(counts);
            }
            return Task.FromResult<object>(answer);
        }
    }
}
