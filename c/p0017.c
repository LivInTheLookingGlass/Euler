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
#include <stdio.h>

unsigned int to_string_len(unsigned long long n);
unsigned int to_string_len(unsigned long long n) {
    if (n >= 1000) {
        return to_string_len(n / 1000 % 100) + 8;  //len("thousand")
    }
    else if (n >= 100) {
        unsigned int hundreds = to_string_len(n / 100 % 10) + 7;  // len("hundred")
        if (n % 100)
            return hundreds + 3 /* len("and") */ + to_string_len(n % 100);
        return hundreds;
    }
    else if (n >= 20) {
        unsigned int tens = 0;
        switch (n / 10) {
            case 4:
                tens = 5;  // len("forty")
                break;
            case 5:
                tens = 5;  // len("fifty")
                break;
            case 6:
                tens = 5;  // len("sixty")
                break;
            case 7:
                tens = 7;  // len("seventy")
                break;
            default:
                tens = 6;  // len("ninety") and the like
                break;
        }
        if (n % 10)
            return tens + to_string_len(n % 10);
        return tens;
    }
    switch (n) {
        case 1: return 3;  // len("one")
        case 2: return 3;  // len("two")
        case 3: return 5;  // len("three")
        case 4: return 4;  // len("four")
        case 5: return 4;  // len("five")
        case 6: return 3;  // len("six")
        case 7: return 5;  // len("seven")
        case 8: return 5;  // len("eight")
        case 9: return 4;  // len("nine")
        case 10: return 3;  // len("ten")
        case 11: return 6;  // len("eleven")
        case 12: return 6;  // len("twelve")
        case 13: return 8;  // len("thirteen")
        case 14: return 8;  // len("fourteen")
        case 15: return 7;  // len("fifteen")
        case 16: return 7;  // len("sixteen")
        case 17: return 9;  // len("seventeen")
        case 18: return 8;  // len("eighteen")
        case 19: return 8;  // len("nineteen")
        default: return -1;
    }
}

unsigned long long p0017() {
    unsigned long long answer = 0;
    for (unsigned int x = 1; x < 1001; x += 1) {
        answer += to_string_len(x);
    }
    return answer;
}


#ifndef UNITY_END
int main(int argc, char const *argv[])  {
    unsigned long long answer = p0017();
    printf("%llu\n", answer);
    return 0;
}
#endif
#endif
