# C Section

All problems are solved in C11, though most if not all of it is C99-compatible. It is tested only on clang and gcc, but there is no reason to thing that it would not work on a Windows-based compiler.

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