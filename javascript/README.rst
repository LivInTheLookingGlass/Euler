JavaScript Section
==================

.. |JavaScript Check| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/javascript.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/javascript.yml

|JavaScript Check|

All problems are solved in ES6+ Javascript

Organization
------------

All javascript files share a common prefix with their problem number.
Though it is currently not the case, some of these files may export
utilities for other problems to use.

Makefile
--------

There are eight recipes in this Makefile

dependencies
~~~~~~~~~~~~

This recipe installs all the required and test dependencies. See the
Dependencies section for more info

test
~~~~

This recipe runs tests in a single thread and performs benchmarks on
each. This test infrastructure is based on mocha and benchmark.js,
though it currently does not export benchmark info except to fail tests
for time limit reasons.

test\_\*
~~~~~~~~

This recipe runs tests in the specified number of threads and performs
benchmarks on each. This test infrastructure is based on mocha and benchmark.js,
though it currently does not export benchmark info except to fail tests
for time limit reasons. If you specify the number of threads as `auto`, it
will default to using 1 fewer threads than you have CPUs.

dependencies
~~~~~~~~~~~~

Install all dependencies for the NodeJS platform.

lint
~~~~

This recipe runs es-lint on the JavaScript files.

bun_test
~~~~~~~~

Run through all tests in sequence. Utilizes the bun runtime and test runner.

bun_dependencies
~~~~~~~~~~~~~~~~

Installs bun and runs bun install.

webpack
~~~~~~~

Packages these tests for use in browsers.

clean
~~~~~

Remove any installed modules or webpack files.

Tests
-----

Generic Problems
~~~~~~~~~~~~~~~~

For each problem it will check the answer against a known dictionary. If
the problem is not in the "known slow" category (meaning that I generate
the correct answer with a poor solution), it will run it as many times
as the benchmark plugin wants. Otherwise it is run exactly once*.

\* This is a TODO for the Javascript section

A test fails if it gets the wrong answer or if it takes more than 1
minute.

Dependencies
------------

I try to keep the dependencies of this project as small as possible,
except for test plugins. At the moment there are no non-test
dependencies for this section.

Problems Solved
---------------

-  ☒ `1 <./src/p0001.js>`__
-  ☒ `2 <./src/p0002.js>`__
-  ☒ `3 <./src/p0003.js>`__
-  ☒ `4 <./src/p0004.js>`__
-  ☒ `5 <./src/p0005.js>`__
-  ☒ `6 <./src/p0006.js>`__
-  ☒ `7 <./src/p0007.js>`__
-  ☒ `8 <./src/p0008.js>`__
-  ☒ `9 <./src/p0009.js>`__
-  ☒ `10 <./src/p0010.js>`__
-  ☒ `11 <./src/p0011.js>`__
-  ☒ `12 <./src/p0012.js>`__
-  ☒ `13 <./src/p0013.js>`__
-  ☒ `14 <./src/p0014.js>`__
-  ☒ `15 <./src/p0015.js>`__
-  ☒ `16 <./src/p0016.js>`__
-  ☒ `17 <./src/p0017.js>`__
-  ☒ `18 <./src/p0019.js>`__
-  ☒ `19 <./src/p0019.js>`__
-  ☒ `20 <./src/p0020.js>`__
-  ☒ `21 <./src/p0021.js>`__
-  ☒ `22 <./src/p0022.js>`__
-  ☒ `23 <./src/p0023.js>`__
-  ☒ `27 <./src/p0027.js>`__
-  ☒ `28 <./src/p0028.js>`__
-  ☒ `34 <./src/p0034.js>`__
-  ☒ `35 <./src/p0035.js>`__
-  ☒ `37 <./src/p0037.js>`__
-  ☒ `41 <./src/p0041.js>`__
-  ☒ `46 <./src/p0046.js>`__
-  ☒ `60 <./src/p0060.js>`__
-  ☒ `67 <./src/p0067.js>`__
-  ☒ `76 <./src/p0076.js>`__
-  ☒ `836 <./src/p0836.js>`__
