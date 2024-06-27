# Python Section

[![Python Check](https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python.yml/badge.svg)](https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python.yml)

All problems are solved in type-hinted python3

## Organization

All files share a common prefix with their problem number. Several of the problems also have code leveraged as if they were a library. That list is (approximately):

* p0002 for the fibonacci sequence
* p0003 for prime numbers and factors
* p0004 for palindrome detection
* p0007 for is_prime()
* p0008 for iterating over a series in groups of n
* p0015 for n_choose_r
* p0018 for trianglar pathfinding
    * only used by p0018 and p0067
* p0021 for proper divisors
* p0052 and p0074 for digits functions
    * p0052 for a sequence
    * p0074 for a generator
* p0055 for retrieving a number from its digits

## Makefile

There are three main recipes in this Makefile

### dependencies

This recipe installs all the required and test dependencies. See the Dependencies section for more info

### test

This recipe runs tests in a single thread and performs benchmarks and style checks on them.

### test_*

This recipe runs tests in multiple threads, using however many are specified by the number after the _. For example, `test_3` would spawn three python processes. Because benchmark disables itself when running in children processes, benchmark info is not available with this recipe.

## Tests

### Prime Numbers

There is a single test for the prime number infrastructure. It has three components:

1. It checks that it correctly generates the first million primes in the correct order
2. It checks that is_prime() operates correctly for all numbers in that range, including all composites between them
3. It checks that the whole series takes <200ns/prime to compute

### Generic Problems

For each problem it will check the answer against a known dictionary. If the problem is not in the "known slow" category (meaning that I generate the correct answer with a poor solution), it will run it as many times as the benchmark plugin wants. Otherwise it is run exactly once.

A test fails if it gets the wrong answer or if it takes more than 1 minute.

## Dependencies

I try to keep the dependencies of this project as small as possible, except for test plugins. At the moment there are only two non-test dependencies:

### u-msgpack-python

This serialization library encodes things in the MessagePack format. The reason it is not only for testing is that it allows me to read from a cache of prime numbers stored on disk. This is not required, and if you remove it (and the import) things would still run correctly.

### sortedcontainers

This library provides a collection of sorted containers. At the time of writing this, the only one I use is SortedSet() for the prime number generator. If I were willing to remove the prime number cache this would not be needed. I could also implement my own if need be.

## Environment Variables

### NO_OPTIONAL_TESTS

If this variable is defined to something other than 0 or an empty string, the test suite will skip any tests which are not directly related to Project Euler problems. This value will default to the same value as [`ONLY_SLOW`](#only-slow).

### NO_SLOW

If this variable is defined to something other than 0 or an empty string, problems in the known_slow group will not be tested. This variable defaults to True on Termux systems. If both [`NO_SLOW`](#no-slow) and [`ONLY_SLOW`](#only-slow) are truthy, they will be ignored and a warning will be issued.

### ONLY_SLOW

If this variable is defined to something other than 0 or an empty string, *only* problems in the known_slow group will be tested. If both [`NO_SLOW`](#no-slow) and [`ONLY_SLOW`](#only-slow) are truthy, they will be ignored and a warning will be issued.
## Problems Solved

- [x] [1](./p0001.py)
- [x] [2](./p0002.py)
- [x] [3](./p0003.py)
- [x] [4](./p0004.py)
- [x] [5](./p0005.py)
- [x] [6](./p0006.py)
- [x] [7](./p0007.py)
- [x] [8](./p0008.py)
- [x] [9](./p0009.py)
- [x] [10](./p0010.py)
- [x] [11](./p0011.py)
- [x] [12](./p0012.py)
- [x] [13](./p0013.py)
- [x] [14](./p0014.py)
- [x] [15](./p0015.py)
- [x] [16](./p0016.py)
- [x] [17](./p0017.py)
- [x] [18](./p0018.py)
- [x] [19](./p0019.py)
- [x] [20](./p0020.py)
- [x] [21](./p0021.py)
- [x] [22](./p0022.py)
- [x] [23](./p0023.py)
- [x] [24](./p0024.py)
- [x] [25](./p0025.py)
- [x] [27](./p0027.py)
- [x] [29](./p0029.py)
- [x] [30](./p0030.py)
- [x] [31](./p0031.py)
- [x] [32](./p0032.py)
- [x] [33](./p0033.py)
- [x] [34](./p0034.py)
- [x] [35](./p0035.py)
- [x] [36](./p0036.py)
- [x] [37](./p0037.py)
- [x] [38](./p0038.py)
- [x] [39](./p0039.py)
- [x] [40](./p0040.py)
- [x] [41](./p0041.py)
- [x] [42](./p0042.py)
- [x] [43](./p0043.py)
- [x] [44](./p0044.py)
- [x] [45](./p0045.py)
- [x] [46](./p0046.py)
- [x] [47](./p0047.py)
- [x] [48](./p0048.py)
- [x] [49](./p0049.py)
- [x] [50](./p0050.py)
- [x] [52](./p0052.py)
- [x] [53](./p0053.py)
- [x] [55](./p0055.py)
- [x] [56](./p0056.py)
- [x] [57](./p0057.py)
- [x] [59](./p0059.py)
- [x] [67](./p0067.py)
- [x] [69](./p0069.py)
- [x] [71](./p0071.py)
- [x] [73](./p0073.py)
- [x] [74](./p0074.py)
- [x] [76](./p0076.py)
- [x] [77](./p0077.py)
- [x] [87](./p0087.py)
- [x] [92](./p0092.py)
- [x] [98](./p0098.py)
- [x] [118](./p0118.py)
- [x] [123](./p0123.py)
- [x] [134](./p0134.py)
- [x] [145](./p0145.py)
- [x] [187](./p0187.py)
- [x] [206](./p0206.py)
