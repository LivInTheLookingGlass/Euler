/*
Project Euler Problem 76

I ended up having to do this iteratively, which I'm not super happy with. I feel like there is almost certainly a
closed-form solution to this, but I was unable to figure it out.

Revision 1:

Have counts store values instead of numeral counts to shave a few seconds off

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
#include <stdio.h>


int main(int argc, char const *argv[])  {
    unsigned int answer = 0;
    unsigned char idx, i, sum, counts[101] = {0};
    counts[1] = 100;
    while (!counts[100]) {
        sum = counts[1];
        for (i = 2; i < 100; ++i) {
            sum += counts[i];
        }
        ++counts[1];
        if (sum > 100)  {
            idx = 1;
            do {
                counts[idx] = 0;
                ++idx;
                counts[idx] += idx;
                sum = counts[1];
                for (i = 2; i < 100; ++i) {
                    sum += counts[i];
                }
            } while (sum > 100);
            counts[1] = 100 - sum;
        }
        else if (sum == 100)    {
            ++answer;
        }
    }
    printf("%u", answer);
    return 0;
}
