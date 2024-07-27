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

-  ☒ `1 <./p0001.py>`__
-  ☒ `2 <./p0002.py>`__
-  ☒ `3 <./p0003.py>`__
-  ☒ `4 <./p0004.py>`__
-  ☒ `5 <./p0005.py>`__
-  ☒ `6 <./p0006.py>`__
-  ☒ `7 <./p0007.py>`__
-  ☒ `8 <./p0008.py>`__
-  ☒ `9 <./p0009.py>`__
-  ☒ `10 <./p0010.py>`__
-  ☒ `11 <./p0011.py>`__
-  ☒ `12 <./p0012.py>`__
-  ☒ `13 <./p0013.py>`__
-  ☒ `14 <./p0014.py>`__
-  ☒ `15 <./p0015.py>`__
-  ☒ `16 <./p0016.py>`__
-  ☒ `17 <./p0017.py>`__
-  ☒ `18 <./p0018.py>`__
-  ☒ `19 <./p0019.py>`__
-  ☒ `20 <./p0020.py>`__
-  ☒ `21 <./p0021.py>`__
-  ☒ `22 <./p0022.py>`__
-  ☒ `23 <./p0023.py>`__
-  ☒ `24 <./p0024.py>`__
-  ☒ `25 <./p0025.py>`__
-  ☒ `27 <./p0027.py>`__
-  ☒ `28 <./p0028.py>`__
-  ☒ `29 <./p0029.py>`__
-  ☒ `30 <./p0030.py>`__
-  ☒ `31 <./p0031.py>`__
-  ☒ `32 <./p0032.py>`__
-  ☒ `33 <./p0033.py>`__
-  ☒ `34 <./p0034.py>`__
-  ☒ `35 <./p0035.py>`__
-  ☒ `36 <./p0036.py>`__
-  ☒ `37 <./p0037.py>`__
-  ☒ `38 <./p0038.py>`__
-  ☒ `39 <./p0039.py>`__
-  ☒ `40 <./p0040.py>`__
-  ☒ `41 <./p0041.py>`__
-  ☒ `42 <./p0042.py>`__
-  ☒ `43 <./p0043.py>`__
-  ☒ `44 <./p0044.py>`__
-  ☒ `45 <./p0045.py>`__
-  ☒ `46 <./p0046.py>`__
-  ☒ `47 <./p0047.py>`__
-  ☒ `48 <./p0048.py>`__
-  ☒ `49 <./p0049.py>`__
-  ☒ `50 <./p0050.py>`__
-  ☒ `52 <./p0052.py>`__
-  ☒ `53 <./p0053.py>`__
-  ☒ `55 <./p0055.py>`__
-  ☒ `56 <./p0056.py>`__
-  ☒ `57 <./p0057.py>`__
-  ☒ `58 <./p0058.py>`__
-  ☒ `59 <./p0059.py>`__
-  ☒ `60 <./p0060.py>`__
-  ☒ `67 <./p0067.py>`__
-  ☒ `69 <./p0069.py>`__
-  ☒ `71 <./p0071.py>`__
-  ☒ `73 <./p0073.py>`__
-  ☒ `74 <./p0074.py>`__
-  ☒ `76 <./p0076.py>`__
-  ☒ `77 <./p0077.py>`__
-  ☒ `81 <./p0081.py>`__
-  ☒ `87 <./p0087.py>`__
-  ☒ `89 <./p0089.py>`__
-  ☒ `92 <./p0092.py>`__
-  ☒ `98 <./p0098.py>`__
-  ☒ `99 <./p0099.py>`__
-  ☒ `118 <./p0118.py>`__
-  ☒ `123 <./p0123.py>`__
-  ☒ `134 <./p0134.py>`__
-  ☒ `145 <./p0145.py>`__
-  ☒ `187 <./p0187.py>`__
-  ☒ `206 <./p0206.py>`__
-  ☒ `357 <./p0357.py>`__
