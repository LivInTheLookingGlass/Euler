/*
Project Euler Problem 17

I feel like there is a better way to recurse this problem, but I could not
think of one at the time

Problem:

If the numbers 1 to 5 are written out in words: one, two, three, four, five,
then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in
words, how many letters would be used?

NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and
forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20
letters. The use of "and" when writing out numbers is in compliance with
British usage.
*/
#ifndef EULER_P0017
#define EULER_P0017
#include <stdint.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include "include/macros.hpp"

std::string ToString(uint64_t n);
std::string ToString(uint64_t n) {
    if (n >= 1000)
        return ToString(n / 1000 % 100) + " thousand";
    else if (n >= 100) {
        std::string hundreds = ToString(n / 100 % 10) + " hundred";
        if (n % 100)
            return hundreds + " and " + ToString(n % 100);
        return hundreds;
    }
    else if (n >= 20) {
        std::string tens = "";
        switch (n / 10) {
            case 2:
                tens = "twenty";
                break;
            case 3:
                tens = "thirty";
                break;
            case 4:
                tens = "forty";
                break;
            case 5:
                tens = "fifty";
                break;
            case 6:
                tens = "sixty";
                break;
            case 7:
                tens = "seventy";
                break;
            case 8:
                tens = "eighty";
                break;
            case 9:
                tens = "ninety";
                break;
            default:
                throw std::invalid_argument("n is not in the accepted range");
        }
        if (n % 10)
            return tens + "-" + ToString(n % 10);
        return tens;
    }
    switch (n) {
        case 1: return "one";
        case 2: return "two";
        case 3: return "three";
        case 4: return "four";
        case 5: return "five";
        case 6: return "six";
        case 7: return "seven";
        case 8: return "eight";
        case 9: return "nine";
        case 10: return "ten";
        case 11: return "eleven";
        case 12: return "twelve";
        case 13: return "thirteen";
        case 14: return "fourteen";
        case 15: return "fifteen";
        case 16: return "sixteen";
        case 17: return "seventeen";
        case 18: return "eighteen";
        case 19: return "nineteen";
        default: throw std::invalid_argument("n is not in the accepted range");
    }
}

uint64_t EMSCRIPTEN_KEEPALIVE p0017() {
    uint64_t answer = 0;
    std::string filter[2] = {" ", "-"};
    size_t pos, i;
    for (uint32_t x = 1; x < 1001; x += 1) {
        std::string str = ToString(x);
        for (pos = 0, i = 0; i < 2; i++)
            while ((pos = str.find(filter[i], pos)) != std::string::npos)
                str.replace(pos, 1, "");

        answer += str.length();
    }
    return answer;
}

PROGRAM_TAIL(p0017)
#endif
