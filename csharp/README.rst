C# Section
==========

.. |C# Check| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/csharp.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/csharp.yml

|C# Check|

All problems are solved in .NET 5, though an effort is made to support
other versions.

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

-  ☒ `1 <./p0001.cs>`__
