/*
Project Euler Problem 4

This was pretty easy to do, given the C++ stdlib

Problem:

A palindromic number reads the same both ways. The largest palindrome made from
the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/
#ifndef EULER_P0004
#define EULER_P0004
#include <algorithm>
#include <cstdio>
#include <iostream>

unsigned int p0004() {
    unsigned int answer = 0, i, j, prod;
    for (i = 100; i < 1000; i++)    {
        for (j = 100; j < 1000; j++)    {
            prod = i * j;
            char buf[8] = {};
            sprintf(buf, "%u", prod);
            std::string forward(buf);
            std::string reverse = forward;
            std::reverse(reverse.begin(), reverse.end());
            if (forward == reverse) {
                answer = std::max(answer, prod);
            }
        }
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[])  {
    std::cout << p0004() << std::endl;
    return 0;
}
#endif
#endif
