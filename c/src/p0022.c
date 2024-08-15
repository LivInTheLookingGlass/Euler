/*
Project Euler Problem 22

I know that this could be done faster with a traditional for loop, but I wanted
to see if iterators were reasonably possible in C, since it makes the prime
number infrastructure a lot easier to set up.

Problem:

If we list all the natural numbers below 10 that are multiples of 3 or 5, we
get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.
*/
#ifndef EULER_P0022
#define EULER_P0022
#include <stdio.h>
#include "include/macros.h"
#include "include/utils.h"

int cmpstr(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

unsigned long long p0022() {
    unsigned long long answer = 0;
    char *fstring = get_data_file("p0022_names.txt");
    const unsigned int name_count = 5163;
    char *names[5163] = {};
    size_t idx = 0, i = 0, pi = 0;
    do {
        while (fstring[i] && fstring[i] != ',')
            i++;
        const size_t len = i - pi - 2;
        if (unlikely(len == 0))
            continue;
        names[idx] = (char *)malloc(len);
        memcpy(names[idx], fstring + pi + 1, len);
        names[idx++][len] = 0;
        pi = ++i;
    } while (fstring[i]);
    qsort(names, sizeof(names)/sizeof(*names), sizeof(*names), cmpstr);
    for (idx = 0; idx < name_count; idx++) {
        unsigned long score = 0;
        for (i = 0; names[idx][i]; i++) {
            score += names[idx][i] & 0x3F;
        }
        answer += score * (idx + 1);
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[]) {
    printf("%llu\n", p0022());
    return 0;
}
#endif
#endif
