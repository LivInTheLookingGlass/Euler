C++ Section
===========

.. |Cpi| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/cplusplus.yml?logo=github&label=Cpp%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/cplusplus.yml
.. |Cp-lint| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/cplusplus-lint.yml?logo=github&label=Linting
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/cplusplus-lint.yml
.. |CodeQL| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/codeql.yml?logo=github&label=CodeQL
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/codeql.yml
.. |Cp-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=Cpp&logo=codecov&label=Cpp%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=Cpp

|Cpi| |Cp-Cov| |Cp-lint| |CodeQL|

All problems are solved in C++98. It is tested on clang, g++, and msvc (the Visual Studios compiler).

Organization
------------

All C++ files share a common prefix with their problem number. All shared
functions are moved to header files in the include subfolder

Makefile
--------

There are four main recipes in this Makefile

dependencies
~~~~~~~~~~~~

This recipe installs all the required and test dependencies. See the
Dependencies section for more info

test
~~~~

This recipe runs tests in a single thread and performs benchmarks on
each. This test infrastructure is recycled from the python section.

test\_\*
~~~~~~~~

This recipe runs tests in multiple threads, using however many are
specified by the number after the \_. For example, ``test_3`` would
spawn three python processes. Because benchmark disables itself when
running in children processes, benchmark info is not available with this
recipe.

native
~~~~~~

This recipe borrows the C test infrastructure. This is entirely to allow
CodeQL to analyze my C++ code. It is not actually a supported test runner.
In future, it will be replaced with a C++-native test runner.

Tests
-----

Compiler Detection Macros
~~~~~~~~~~~~~~~~~~~~~~~~~

There are a set of macros which detect which compiler is being used.
These macros are mostly used to route around issues with particular
compilers. For instance, PCC does not allow me to include ``<stdlib.h>``
or ``<math.h>`` on the systems I've tested it on, so I need to route
around that. This test checks that those macros are correct.

Prime Infrastructure Test
~~~~~~~~~~~~~~~~~~~~~~~~~

(Note that this is in progress, and these tests will be run only when
there is an implementation to refer to. Since they are identical to the
test in the c folder, the test is already written and ready to go.)

This test checks five things:

1. It checks ``is_prime()`` for numbers up to ``MAX_PRIME``, where that
   is defined in the test
2. It checks that ``is_composite()`` returns truthy values on composites
   in that range, and falsey values on primes
3. It checks that ``is_composite()`` returns the smallest prime factor
   on composite numbers
4. It checks that the prime numbers are generated in the correct order
5. It checks that all these operations are completed in less than 200ns
   \* ``MAX_PRIME``

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
except for test plugins. At the moment there are no non-test
dependencies for this section.

Note that there are optional test that leverage the Python
infrastructure. If you want these tests to work you need to go to the
python folder and run ``make dependencies`` or define the
`NO_OPTIONAL_TESTS <#no-slow-tests>`__ environment variable.

Environment Variables
---------------------

COMPILER_OVERRIDE
~~~~~~~~~~~~~~~~~

If this variable is defined, it should contain a comma-separated list of
the compilers you would like to test from the following list (case
insensitive):

-  aocc (AMD Optimized C Compiler)
-  cl (Visual Studios compiler)
-  clang
-  gcc
-  icc (Intel C Compiler)
-  pcc (Portable C Compiler)
-  tcc (Tiny C Compiler)

If this variable is not defined, compilers will be auto-detected using
``which()``.

AOCC_OVERRIDE
~~~~~~~~~~~~~

If this variable is defined, it should hold a string representing the
AMD compiler binary you would like to use. One case you may want this in
is to test both the AMD compiler and traditional clang by renaming the
AMD compiler's executable.

GCC_OVERRIDE
~~~~~~~~~~~~

If this variable is defined, it should hold a string representing the
``gcc`` binary you would like to use. One case you may want this in is
on OSX or Termux, where ``gcc`` is often remapped to ``clang``.

NO_OPTIONAL_TESTS
~~~~~~~~~~~~~~~~~

If this variable is defined to something other than 0 or an empty
string, the test suite will skip any tests which are not directly
related to Project Euler problems. This value will default to the same
value as `ONLY_SLOW <#only-slow>`__.

NO_SLOW
~~~~~~~

If this variable is defined to something other than 0 or an empty
string, problems in the known_slow group will not be tested. This
variable defaults to True on Termux systems. If both
`NO_SLOW <#no-slow>`__ and `ONLY_SLOW <#only-slow>`__ are
truthy, they will be ignored and a warning will be issued.

ONLY_SLOW
~~~~~~~~~

If this variable is defined to something other than 0 or an empty
string, *only* problems in the known_slow group will be tested. If both
`NO_SLOW <#no-slow>`__ and `ONLY_SLOW <#only-slow>`__ are
truthy, they will be ignored and a warning will be issued.

Problems Solved
---------------

-  ☒ `1 <./src/p0001.cpp>`__
-  ☒ `2 <./src/p0002.cpp>`__
-  ☒ `3 <./src/p0003.cpp>`__
-  ☒ `4 <./src/p0004.cpp>`__
-  ☒ `5 <./src/p0005.cpp>`__
-  ☒ `6 <./src/p0006.cpp>`__
-  ☒ `7 <./src/p0007.cpp>`__
-  ☒ `8 <./src/p0008.cpp>`__
-  ☒ `9 <./src/p0009.cpp>`__
-  ☒ `10 <./src/p0010.cpp>`__
-  ☒ `11 <./src/p0011.cpp>`__
-  ☒ `13 <./src/p0013.cpp>`__
-  ☒ `14 <./src/p0014.cpp>`__
-  ☒ `15 <./src/p0015.cpp>`__
-  ☒ `16 <./src/p0016.cpp>`__
-  ☒ `17 <./src/p0017.cpp>`__
-  ☒ `20 <./src/p0020.cpp>`__
-  ☒ `22 <./src/p0022.cpp>`__
-  ☒ `34 <./src/p0034.cpp>`__
-  ☒ `76 <./src/p0076.cpp>`__
-  ☒ `836 <./src/p0836.cpp>`__
