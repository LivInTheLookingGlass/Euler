/*
Project Euler Problem 76 6206s

I ended up having to do this with recursion, which I normally do not like to
use that much. Small changes can have large effects on later results. Still,
this seems to work for the moment.

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
    unsigned long answer = 0;
    unsigned char idx, i, sum, counts[101] = {0};
    counts[1] = 100;
    while (!counts[100]) {
        sum = counts[1];
        for (i = 2; i < 100; ++i) {
            sum += counts[i] * i;
        }
        ++counts[1];
        if (sum > 100)  {
            idx = 1;
            do {
                counts[idx] = 0;
                ++counts[++idx];
                sum = counts[1];
                for (i = 2; i < 100; ++i) {
                    sum += counts[i] * i;
                }
            } while (sum > 100);
            counts[1] = 100 - sum;
        }
        else if (sum == 100)    {
            ++answer;
        }
    }
    printf("%lu", answer);
    return 0;
}
