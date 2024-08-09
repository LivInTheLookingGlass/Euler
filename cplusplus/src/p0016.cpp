/*
Project Euler Problem 16

Problem:

2**15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2**1000?
*/
#ifndef EULER_P0016
#define EULER_P0016
#include <iostream>
#include <vector>


unsigned long long p0016() {
    std::vector<unsigned long long> numbers(18, 0);
    const unsigned long long ten17 = 100000000000000000;
    numbers[0] = 1;
    for (unsigned short i = 0; i < 1000; i++) {
        for (size_t j = 0; j < numbers.size(); j++) {
            numbers[j] *= 2;
        }
        for (size_t j = 0; j < numbers.size() - 1; j++) {
            if (numbers[j] > ten17) {
                numbers[j + 1] += numbers[j] / ten17;
                numbers[j] %= ten17;
            }
        }
    }
    unsigned long long answer = 0;
    unsigned long long power = 1;
    for (unsigned char i = 0; i < 18; i++) {
        for (size_t j = 0; j < numbers.size(); j++) {
            answer += (numbers[j] / power) % 10;
        }
        power *= 10;
    }
    return answer;
}

#ifndef UNITY_END
int main(int argc, char const *argv[])  {
    std::cout << p0016() << std::endl;
    return 0;
}
#endif
#endif
