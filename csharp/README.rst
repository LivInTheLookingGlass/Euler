C# Section
==========

.. |C#i| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/csharp.yml?logo=github&label=C%23%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/csharp.yml
.. |C#-lint| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/csharp-lint.yml?logo=github&label=Linting
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/csharp-lint.yml
.. |CodeQL| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/codeql.yml?logo=github&label=CodeQL
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/codeql.yml
.. |Cs-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=Csharp&logo=codecov&label=C%23%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=Csharp

|C#i| |Cs-Cov| |C#-lint| |CodeQL|

All problems are solved in .NET 2+.

Organization
------------

All C# files share a common prefix with their problem number. All shared
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

This recipe runs ``dotnet``\ s builtin linter with the
``--verify-no-changes`` flag

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

-  ☒ `1 <./Euler/p0001.cs>`__
-  ☒ `2 <./Euler/p0002.cs>`__
-  ☒ `3 <./Euler/p0003.cs>`__
-  ☒ `4 <./Euler/p0004.cs>`__
-  ☒ `6 <./Euler/p0006.cs>`__
-  ☒ `7 <./Euler/p0007.cs>`__
-  ☒ `8 <./Euler/p0008.cs>`__
-  ☒ `9 <./Euler/p0009.cs>`__
-  ☒ `10 <./Euler/p0010.cs>`__
-  ☒ `11 <./Euler/p0011.cs>`__
-  ☒ `13 <./Euler/p0013.cs>`__
-  ☒ `14 <./Euler/p0014.cs>`__
-  ☒ `15 <./Euler/p0015.cs>`__
-  ☒ `16 <./Euler/p0016.cs>`__
-  ☒ `17 <./Euler/p0017.cs>`__
-  ☒ `19 <./Euler/p0019.cs>`__
-  ☒ `20 <./Euler/p0020.cs>`__
-  ☒ `22 <./Euler/p0022.cs>`__
-  ☒ `34 <./Euler/p0034.cs>`__
-  ☒ `76 <./Euler/p0076.cs>`__
-  ☒ `836 <./Euler/p0836.cs>`__

