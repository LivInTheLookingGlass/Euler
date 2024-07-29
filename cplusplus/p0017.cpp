/*
Project Euler Problem 15

Turns out this is easy, if you think sideways a bit

You can only go down or right. If we say right=1, then you can only have 20 1s, since otherwise you go off the grid.
You also can't have fewer than 20 1s, since then you go off the grid the other way. This means you can look at it as a
bit string, and the number of 40-bit strings with 20 1s is 40c20.

Problem:

Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6
routes to the bottom right corner.

How many such routes are there through a 20×20 grid?
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
        while (pos != string::npos) {
            str.replace(pos, 1, "");
            pos = str.find(" ", pos + 1);
        }
        pos = str.find("-");
        while (pos != string::npos) {
            str.replace(pos, 1, "");
            pos = str.find("-", pos + 1);
        }
        answer += str.length;
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
