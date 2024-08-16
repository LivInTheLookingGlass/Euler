/*
Project Euler Problem 2

More iterator usage

Problem:

Each new term in the Fibonacci sequence is generated by adding the previous two
terms. By starting with 1 and 2, the first 10 terms will be:

1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

By considering the terms in the Fibonacci sequence whose values do not exceed
four million, find the sum of the even-valued terms.
*/

#ifndef EULER_P0002
#define EULER_P0002
#include <stdint.h>
#include <stdio.h>
#include "include/fibonacci.h"

uint64_t p0002() {
    uint64_t answer = 0;
    fibonacci fib = fibonacci1(3999999);
    while (!fib.exhausted) {
        next(fib);  // odd (1, 3, 13, 55, ...)
        next(fib);  // odd (1, 5, 21, 89, ...)
        answer += next(fib);  // even (2, 8, 34, 144, ...)
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    printf("%lu\n", p0002());
    return 0;
}
#endif
#endif
