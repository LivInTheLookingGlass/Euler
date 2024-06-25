# C# Section

All problems are solved in .NET 6, though an effort is made to support other versions.

## Organization

All C# files share a common prefix with their problem number. All shared functions are defined in the include folder.

## Makefile

There are two main recipes in this Makefile

### dependencies

This recipe installs all the required and test dependencies. See the Dependencies section for more info

### test

This recipe runs tests in multiple threads

## Tests

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
