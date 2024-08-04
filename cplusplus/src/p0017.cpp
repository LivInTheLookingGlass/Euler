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
#include <iostream>
#include <stdexcept>
#include <string>

std::string ToString(unsigned long long n);
std::string ToString(unsigned long long n) {
    if (n >= 1000) {
        return ToString(n / 1000 % 100) + " thousand";
    }
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

unsigned long long p0017() {
    unsigned long long answer = 0;
    for (unsigned int x = 1; x < 1001; x += 1) {
        std::string str = ToString(x);
        size_t pos = str.find(" ");
        while (pos != std::string::npos) {
            str.replace(pos, 1, "");
            pos = str.find(" ", pos + 1);
        }
        pos = str.find("-");
        while (pos != std::string::npos) {
            str.replace(pos, 1, "");
            pos = str.find("-", pos + 1);
        }
        answer += str.length();
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[])  {
    std::cout << p0017() << std::endl;
    return 0;
}
#endif
#endif