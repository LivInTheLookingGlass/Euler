# C Section

[![C Check](https://github.com/LivInTheLookingGlass/Euler/actions/workflows/c.yml/badge.svg)](https://github.com/LivInTheLookingGlass/Euler/actions/workflows/c.yml)

All problems are solved in C11, though most if not all of it is C99-compatible. It is tested on clang, gcc, and cl (the Visual Studios compiler).

## Organization

All C files share a common prefix with their problem number. All shared functions are moved to header files in the include subfolder

## Makefile

There are four main recipes in this Makefile

### dependencies

This recipe installs all the required and test dependencies. See the Dependencies section for more info

### test

This recipe runs tests in a single thread and performs benchmarks on each. This test infrastructure is recycled from the python section.

### test_*

This recipe runs tests in multiple threads, using however many are specified by the number after the _. For example, `test_3` would spawn three python processes. Because benchmark disables itself when running in children processes, benchmark info is not available with this recipe.

### native

This recipe builds a test executable using the Unity test framework. It recycles no Python infrastructure, but consequently cannot test some features like compiler macros and deterministic building.

## Tests

### Compiler Detection Macros

There are a set of macros which detect which compiler is being used. These macros are mostly used to route around issues with particular compilers. For instance, PCC does not allow me to include `<stdlib.h>` or `<math.h>` on the systems I've tested it on, so I need to route around that. This test checks that those macros are correct.

### Prime Infrastructure Test

This test checks five things:

1. It checks `is_prime()` for numbers up to `MAX_PRIME`, where that is defined in the test
2. It checks that `is_composite()` returns truthy values on composites in that range, and falsey values on primes
3. It checks that `is_composite()` returns the smallest prime factor on composite numbers
4. It checks that the prime numbers are generated in the correct order
5. It checks that all these operations are completed in less than 200ns * `MAX_PRIME`

### Generic Problems

For each problem it will check the answer against a known dictionary. If the problem is not in the "known slow" category (meaning that I generate the correct answer with a poor solution), it will run it as many times as the benchmark plugin wants. Otherwise it is run exactly once.

A test fails if it gets the wrong answer or if it takes more than 1 minute.

## Dependencies

I try to keep the dependencies of this project as small as possible, except for test plugins. At the moment there are no non-test dependencies for this section.

Note that there are optional test that leverage the Python infrastructure. If you want these tests to work you need to go to the python folder and run `make dependencies` or define the [`NO_OPTIONAL_TESTS`](#no-slow-tests) environment variable.

## Environment Variables

### COMPILER_OVERRIDE

If this variable is defined, it should contain a comma-separated list of the compilers you would like to test from the following list (case insensitive):

* aocc (AMD Optimized C Compiler)
* cl (Visual Studios compiler)
* clang
* gcc
* icc (Intel C Compiler)
* pcc (Portable C Compiler)
* tcc (Tiny C Compiler)

If this variable is not defined, compilers will be auto-detected using `which()`.

### AOCC_OVERRIDE

If this variable is defined, it should hold a string representing the AMD compiler binary you would like to use. One case you may want this in is to test both the AMD compiler and traditional clang by renaming the AMD compiler's executable.

### GCC_OVERRIDE

If this variable is defined, it should hold a string representing the `gcc` binary you would like to use. One case you may want this in is on OSX or Termux, where `gcc` is often remapped to `clang`.

### NO_OPTIONAL_TESTS

If this variable is defined to something other than 0 or an empty string, the test suite will skip any tests which are not directly related to Project Euler problems. This value will default to the same value as [`ONLY_SLOW`](#only-slow).

### NO_SLOW

If this variable is defined to something other than 0 or an empty string, problems in the known_slow group will not be tested. This variable defaults to True on Termux systems. If both [`NO_SLOW`](#no-slow) and [`ONLY_SLOW`](#only-slow) are truthy, they will be ignored and a warning will be issued.

### ONLY_SLOW

If this variable is defined to something other than 0 or an empty string, *only* problems in the known_slow group will be tested. If both [`NO_SLOW`](#no-slow) and [`ONLY_SLOW`](#only-slow) are truthy, they will be ignored and a warning will be issued.

## Problems Solved

- [x] [1](./p0001.c)
- [x] [2](./p0002.c)
- [x] [3](./p0003.c)
- [x] [4](./p0004.c)
- [x] [5](./p0005.c)
- [x] [6](./p0006.c)
- [x] [7](./p0007.c)
- [x] [8](./p0008.c)
- [x] [9](./p0009.c)
- [x] [10](./p0010.c)
- [x] [11](./p0011.c)
- [ ] [12](./p0012.c)
- [x] [13](./p0013.c)
- [x] [14](./p0014.c)
- [x] [15](./p0015.c)
- [x] [16](./p0016.c)
- [x] [34](./p0034.c)
- [x] [76](./p0076.c)

