Fortran Section
===============

All problems are solved in Fortran90, and should be compliant with later standards.

Organization
------------

All Fortran files share a common prefix with their problem number. All shared
functions are moved to header files in the include subfolder

Makefile
--------

There are three main recipes in this Makefile

test
~~~~

This recipe runs tests in a single thread and performs benchmarks on each.

test\_\*
~~~~~~~~

This recipe currently redirects to ``test``, but in future versions may
spawn a number of threads equal to the suffix given, with ``auto`` equalling
the number of CPUs on the system.

clean
~~~~~

This removes any build files, as well as the test runner executable

Tests
-----

Generic Problems
~~~~~~~~~~~~~~~~

For each problem it will check the answer against a known dictionary. If
the problem is not in the "known slow" category (meaning that I generate
the correct answer with a poor solution), it will run it as many times
as the benchmark plugin wants. Otherwise it is run exactly once.

A test fails if it gets the wrong answer or if it takes more than 1
minute.

Dependencies
------------

I try to keep the dependencies of this project as small as possible,
except for test plugins. At the moment there are no dependencies for this section.

Problems Solved
---------------

-  ☒ `1 <./src/p0001.for>`__
-  ☒ `2 <./src/p0002.for>`__
-  ☒ `6 <./src/p0006.for>`__
-  ☒ `9 <./src/p0009.for>`__
-  ☒ `836 <./src/p0836.for>`__
