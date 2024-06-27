# JavaScript Section

[![JavaScript Check](https://github.com/LivInTheLookingGlass/Euler/actions/workflows/javascript.yml/badge.svg)](https://github.com/LivInTheLookingGlass/Euler/actions/workflows/javascript.yml)

All problems are solved in ES6+ Javascript

## Organization

All javascript files share a common prefix with their problem number. Though it is currently not the case, some of these files may export utilities for other problems to use.

## Makefile

There are two main recipes in this Makefile

### dependencies

This recipe installs all the required and test dependencies. See the Dependencies section for more info

### test

This recipe runs tests in a single thread and performs benchmarks on each. This test infrastructure is based on mocha and benchmark.js, though it currently does not export benchmark info except to fail tests for time limit reasons.

## Tests

### Generic Problems

For each problem it will check the answer against a known dictionary. If the problem is not in the "known slow" category (meaning that I generate the correct answer with a poor solution), it will run it as many times as the benchmark plugin wants. Otherwise it is run exactly once\*.

\* This is a TODO for the Javascript section

A test fails if it gets the wrong answer or if it takes more than 1 minute.

## Dependencies

I try to keep the dependencies of this project as small as possible, except for test plugins. At the moment there are no non-test dependencies for this section.

## Problems Solved

- [x] [1](./p0001.js)
- [x] [2](./p0002.js)
