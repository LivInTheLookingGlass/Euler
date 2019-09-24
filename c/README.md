# C Section

All problems are solved in C11, though most if not all of it is C99-compatible. It is tested on clang, gcc, and cl (the Visual Studios compiler).

## Organization

All C files share a common prefix with their problem number. All shared functions are moved to header files in the include subfolder

## Makefile

There are three main recipes in this Makefile

### dependencies

This recipe installs all the required and test dependencies. See the Dependencies section for more info

### test

This recipe runs tests in a single thread and performs benchmarks on each. This test infrastructure is recycled from the python section.

### test_*

This recipe runs tests in multiple threads, using however many are specified by the number after the _. For example, `test_3` would spawn three python processes. Because benchmark disables itself when running in children processes, benchmark info is not available with this recipe.

## Tests

### Generic Problems

For each problem it will check the answer against a known dictionary. If the problem is not in the "known slow" category (meaning that I generate the correct answer with a poor solution), it will run it as many times as the benchmark plugin wants. Otherwise it is run exactly once.

A test fails if it gets the wrong answer or if it takes more than 1 minute.

## Dependencies

I try to keep the dependencies of this project as small as possible, except for test plugins. At the moment there are no non-test dependencies for this section.

Note that there are optional test that leverage the Python infrastructure. If you want these tests to work you need to go to the python folder and run `make dependencies` or define the [`NO_OPTIONAL_TESTS`](#no-slow-tests) environment variable.

## Environment Variables

### COMPILER_OVERRIDE

If this variable is defined, it should contain a comma-separated list of the compilers you would like to test from the following list (case insensitive):

* cl
* clang
* gcc
* icc (not yet supported)
* pcc (not yet supported)
* tcc

If this variable is not defined, compilers will be auto-detected using `which()`.

### GCC_OVERRIDE

If this variable is defined, it should hold a string representing the `gcc` binary you would like to use. One case you may want this in is on OSX, where `gcc` is often remapped to `clang`.

### NO_OPTIONAL_TESTS

If this variable is defined to something other than 0 or an empty string, the test suite will skip any tests which are not directly related to Project Euler problems. This value will default to the same value as [`ONLY_SLOW`](#only-slow).

### NO_SLOW

If this variable is defined to something other than 0 or an empty string, problems in the known_slow group will not be tested. This variable defaults to True on Termux systems. If both [`NO_SLOW`](#no-slow) and [`ONLY_SLOW`](#only-slow) are truthy, they will be ignored and a warning will be issued.

### ONLY_SLOW

If this variable is defined to something other than 0 or an empty string, *only* problems in the known_slow group will be tested. If both [`NO_SLOW`](#no-slow) and [`ONLY_SLOW`](#only-slow) are truthy, they will be ignored and a warning will be issued.
