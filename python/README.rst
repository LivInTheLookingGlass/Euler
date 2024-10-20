Python Section
==============

.. |Python| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/python.yml?logo=github&label=Py%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python.yml
.. |PythonLint| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/python-lint.yml?logo=github&label=Linting
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python-lint.yml
.. |Py-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=Python&logo=codecov&label=Py%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=Python
.. |CodeQL| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/codeql.yml?logo=github&label=CodeQL
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/codeql.yml

|Python| |Py-Cov| |PythonLint| |CodeQL|

All problems are solved in type-hinted python3

Organization
------------

All files share a common prefix with their problem number. Several of
the problems also draw on code from the ``lib`` subfolder for those that
require similar tools and strategies.

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

-  ☒ `1 <./src/p0001.py>`__
-  ☒ `2 <./src/p0002.py>`__
-  ☒ `3 <./src/p0003.py>`__
-  ☒ `4 <./src/p0004.py>`__
-  ☒ `5 <./src/p0005.py>`__
-  ☒ `6 <./src/p0006.py>`__
-  ☒ `7 <./src/p0007.py>`__
-  ☒ `8 <./src/p0008.py>`__
-  ☒ `9 <./src/p0009.py>`__
-  ☒ `10 <./src/p0010.py>`__
-  ☒ `11 <./src/p0011.py>`__
-  ☒ `12 <./src/p0012.py>`__
-  ☒ `13 <./src/p0013.py>`__
-  ☒ `14 <./src/p0014.py>`__
-  ☒ `15 <./src/p0015.py>`__
-  ☒ `16 <./src/p0016.py>`__
-  ☒ `17 <./src/p0017.py>`__
-  ☒ `18 <./src/p0018.py>`__
-  ☒ `19 <./src/p0019.py>`__
-  ☒ `20 <./src/p0020.py>`__
-  ☒ `21 <./src/p0021.py>`__
-  ☒ `22 <./src/p0022.py>`__
-  ☒ `23 <./src/p0023.py>`__
-  ☒ `24 <./src/p0024.py>`__
-  ☒ `25 <./src/p0025.py>`__
-  ☒ `26 <./src/p0026.py>`__
-  ☒ `27 <./src/p0027.py>`__
-  ☒ `28 <./src/p0028.py>`__
-  ☒ `29 <./src/p0029.py>`__
-  ☒ `30 <./src/p0030.py>`__
-  ☒ `31 <./src/p0031.py>`__
-  ☒ `32 <./src/p0032.py>`__
-  ☒ `33 <./src/p0033.py>`__
-  ☒ `34 <./src/p0034.py>`__
-  ☒ `35 <./src/p0035.py>`__
-  ☒ `36 <./src/p0036.py>`__
-  ☒ `37 <./src/p0037.py>`__
-  ☒ `38 <./src/p0038.py>`__
-  ☒ `39 <./src/p0039.py>`__
-  ☒ `40 <./src/p0040.py>`__
-  ☒ `41 <./src/p0041.py>`__
-  ☒ `42 <./src/p0042.py>`__
-  ☒ `43 <./src/p0043.py>`__
-  ☒ `44 <./src/p0044.py>`__
-  ☒ `45 <./src/p0045.py>`__
-  ☒ `46 <./src/p0046.py>`__
-  ☒ `47 <./src/p0047.py>`__
-  ☒ `48 <./src/p0048.py>`__
-  ☒ `49 <./src/p0049.py>`__
-  ☒ `50 <./src/p0050.py>`__
-  ☒ `51 <./src/p0051.py>`__
-  ☒ `52 <./src/p0052.py>`__
-  ☒ `53 <./src/p0053.py>`__
-  ☒ `54 <./src/p0054.py>`__
-  ☒ `55 <./src/p0055.py>`__
-  ☒ `56 <./src/p0056.py>`__
-  ☒ `57 <./src/p0057.py>`__
-  ☒ `58 <./src/p0058.py>`__
-  ☒ `59 <./src/p0059.py>`__
-  ☒ `60 <./src/p0060.py>`__
-  ☒ `67 <./src/p0067.py>`__
-  ☒ `69 <./src/p0069.py>`__
-  ☒ `70 <./src/p0070.py>`__
-  ☒ `71 <./src/p0071.py>`__
-  ☒ `72 <./src/p0072.py>`__
-  ☒ `73 <./src/p0073.py>`__
-  ☒ `74 <./src/p0074.py>`__
-  ☒ `76 <./src/p0076.py>`__
-  ☒ `77 <./src/p0077.py>`__
-  ☒ `79 <./src/p0079.py>`__
-  ☒ `81 <./src/p0081.py>`__
-  ☒ `85 <./src/p0085.py>`__
-  ☒ `87 <./src/p0087.py>`__
-  ☒ `89 <./src/p0089.py>`__
-  ☒ `92 <./src/p0092.py>`__
-  ☒ `98 <./src/p0098.py>`__
-  ☒ `99 <./src/p0099.py>`__
-  ☒ `118 <./src/p0118.py>`__
-  ☒ `123 <./src/p0123.py>`__
-  ☒ `134 <./src/p0134.py>`__
-  ☒ `145 <./src/p0145.py>`__
-  ☒ `187 <./src/p0187.py>`__
-  ☒ `206 <./src/p0206.py>`__
-  ☒ `357 <./src/p0357.py>`__
-  ☒ `836 <./src/p0836.py>`__
