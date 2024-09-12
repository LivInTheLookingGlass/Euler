Java Section
============

.. |Javai| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/java.yml?logo=github&label=Java%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/java.yml
.. |Java-lint| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/java-lint.yml?logo=github&label=Linting
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/java-lint.yml
.. |CodeQL| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/codeql.yml?logo=github&label=CodeQL
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/codeql.yml
.. |Ja-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=Java&logo=codecov&label=Java%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=Java

|Javai| |Ja-Cov| |Java-lint| |CodeQL|

All problems are solved in Java 8+.

Organization
------------

All Java files share a common prefix with their problem number. All shared
functions are defined in the include folder.

Makefile
--------

There are three main recipes in this Makefile

dependencies
~~~~~~~~~~~~

This recipe installs all the required and test dependencies. See the
Dependencies section for more info

test
~~~~

This recipe runs tests in multiple threads

lint
~~~~

This recipe runs ``maven``\ s builtin formatter

Tests
-----

Prime Infrastructure Test
~~~~~~~~~~~~~~~~~~~~~~~~~

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
the correct answer with a poor solution), it will always be run.
Otherwise it tries to detect the ``NO_SLOW`` environment variable and
dynamically skip them.

A test fails if it gets the wrong answer or if it takes more than 1
minute.

Dependencies
------------

I try to keep the dependencies of this project as small as possible,
except for test plugins. At the moment there are no non-test
dependencies for this section.

Problems Solved
---------------

-  ☒ `1 <./src/main/java/p0001.java>`__
-  ☒ `2 <./src/main/java/p0002.java>`__
-  ☒ `4 <./src/main/java/p0004.java>`__
-  ☒ `6 <./src/main/java/p0006.java>`__
-  ☒ `8 <./src/main/java/p0008.java>`__
-  ☒ `9 <./src/main/java/p0009.java>`__
-  ☒ `11 <./src/main/java/p0011.java>`__
-  ☒ `13 <./src/main/java/p0013.java>`__
-  ☒ `14 <./src/main/java/p0014.java>`__
-  ☒ `15 <./src/main/java/p0015.java>`__
-  ☒ `16 <./src/main/java/p0016.java>`__
-  ☒ `17 <./src/main/java/p0017.java>`__
-  ☒ `19 <./src/main/java/p0019.java>`__
-  ☒ `20 <./src/main/java/p0020.java>`__
-  ☒ `22 <./src/main/java/p0022.java>`__
-  ☒ `34 <./src/main/java/p0034.java>`__
-  ☒ `76 <./src/main/java/p0076.java>`__
-  ☒ `836 <./src/main/java/p0836.java>`__
