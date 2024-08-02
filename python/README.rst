Python Section
==============

.. |Python Check| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python.yml

|Python Check|

All problems are solved in type-hinted python3

Organization
------------

All files share a common prefix with their problem number. Several of
the problems also have code leveraged as if they were a library. I am in
the midst of moving these function into a library subfolder. That
list is (approximately):

-  p0004 for palindrome detection
-  p0028 getting the corners of number spirals

Makefile
--------

There are three main recipes in this Makefile

dependencies
~~~~~~~~~~~~

This recipe installs all the required and test dependencies. See the
Dependencies section for more info

test
~~~~

This recipe runs tests in a single thread and performs benchmarks and
style checks on them.

test\_\*
~~~~~~~~

This recipe runs tests in multiple threads, using however many are
specified by the number after the \_. For example, ``test_3`` would
spawn three python processes. Because benchmark disables itself when
running in children processes, benchmark info is not available with this
recipe.

Tests
-----

Prime Numbers
~~~~~~~~~~~~~

There is a single test for the prime number infrastructure. It has three
components:

1. It checks that it correctly generates the first million primes in the
   correct order
2. It checks that is_prime() operates correctly for all numbers in that
   range, including all composites between them
3. It checks that the whole series takes <200ns/prime to compute

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
except for test plugins. At the moment there are only two non-test
dependencies:

u-msgpack-python
~~~~~~~~~~~~~~~~

This serialization library encodes things in the MessagePack format. The
reason it is not only for testing is that it allows me to read from a
cache of prime numbers stored on disk. This is not required, and if you
remove it (and the import) things would still run correctly.

sortedcontainers
~~~~~~~~~~~~~~~~

This library provides a collection of sorted containers. At the time of
writing this, the only one I use is SortedSet() for the prime number
generator. If I were willing to remove the prime number cache this would
not be needed. I could also implement my own if need be.

Environment Variables
---------------------

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

-  ☒ `1 <./src/0001.py>`__
-  ☒ `2 <./src/0002.py>`__
-  ☒ `3 <./src/0003.py>`__
-  ☒ `4 <./src/0004.py>`__
-  ☒ `5 <./src/0005.py>`__
-  ☒ `6 <./src/0006.py>`__
-  ☒ `7 <./src/0007.py>`__
-  ☒ `8 <./src/0008.py>`__
-  ☒ `9 <./src/0009.py>`__
-  ☒ `10 <./src/0010.py>`__
-  ☒ `11 <./src/0011.py>`__
-  ☒ `12 <./src/0012.py>`__
-  ☒ `13 <./src/0013.py>`__
-  ☒ `14 <./src/0014.py>`__
-  ☒ `15 <./src/0015.py>`__
-  ☒ `16 <./src/0016.py>`__
-  ☒ `17 <./src/0017.py>`__
-  ☒ `18 <./src/0018.py>`__
-  ☒ `19 <./src/0019.py>`__
-  ☒ `20 <./src/0020.py>`__
-  ☒ `21 <./src/0021.py>`__
-  ☒ `22 <./src/0022.py>`__
-  ☒ `23 <./src/0023.py>`__
-  ☒ `24 <./src/0024.py>`__
-  ☒ `25 <./src/0025.py>`__
-  ☒ `27 <./src/0027.py>`__
-  ☒ `28 <./src/0028.py>`__
-  ☒ `29 <./src/0029.py>`__
-  ☒ `30 <./src/0030.py>`__
-  ☒ `31 <./src/0031.py>`__
-  ☒ `32 <./src/0032.py>`__
-  ☒ `33 <./src/0033.py>`__
-  ☒ `34 <./src/0034.py>`__
-  ☒ `35 <./src/0035.py>`__
-  ☒ `36 <./src/0036.py>`__
-  ☒ `37 <./src/0037.py>`__
-  ☒ `38 <./src/0038.py>`__
-  ☒ `39 <./src/0039.py>`__
-  ☒ `40 <./src/0040.py>`__
-  ☒ `41 <./src/0041.py>`__
-  ☒ `42 <./src/0042.py>`__
-  ☒ `43 <./src/0043.py>`__
-  ☒ `44 <./src/0044.py>`__
-  ☒ `45 <./src/0045.py>`__
-  ☒ `46 <./src/0046.py>`__
-  ☒ `47 <./src/0047.py>`__
-  ☒ `48 <./src/0048.py>`__
-  ☒ `49 <./src/0049.py>`__
-  ☒ `50 <./src/0050.py>`__
-  ☒ `52 <./src/0052.py>`__
-  ☒ `53 <./src/0053.py>`__
-  ☒ `55 <./src/0055.py>`__
-  ☒ `56 <./src/0056.py>`__
-  ☒ `57 <./src/0057.py>`__
-  ☒ `58 <./src/0058.py>`__
-  ☒ `59 <./src/0059.py>`__
-  ☒ `60 <./src/0060.py>`__
-  ☒ `67 <./src/0067.py>`__
-  ☒ `69 <./src/0069.py>`__
-  ☒ `71 <./src/0071.py>`__
-  ☒ `73 <./src/0073.py>`__
-  ☒ `74 <./src/0074.py>`__
-  ☒ `76 <./src/0076.py>`__
-  ☒ `77 <./src/0077.py>`__
-  ☒ `81 <./src/0081.py>`__
-  ☒ `87 <./src/0087.py>`__
-  ☒ `89 <./src/0089.py>`__
-  ☒ `92 <./src/0092.py>`__
-  ☒ `98 <./src/0098.py>`__
-  ☒ `99 <./src/0099.py>`__
-  ☒ `118 <./src/0118.py>`__
-  ☒ `123 <./src/0123.py>`__
-  ☒ `134 <./src/0134.py>`__
-  ☒ `145 <./src/0145.py>`__
-  ☒ `187 <./src/0187.py>`__
-  ☒ `206 <./src/0206.py>`__
-  ☒ `357 <./src/0357.py>`__
-  ☒ `836 <./src/0836.py>`__
