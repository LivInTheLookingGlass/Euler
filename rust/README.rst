Rust Section
============

.. |Rust Check| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/rust.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/rust.yml

|Rust Check|

Organization
------------

All files share a common prefix with their problem number. All shared
functions are moved to files in the include subfolder

Makefile
--------

There are three main recipes in this Makefile

test
~~~~

Alias for ``cargo test``

test\_\*
~~~~~~~~

Runs ``cargo test`` with a number of threads determined by the recipe suffix. If you call
``make test_3`` it will use 3 threads. ``make test_auto`` will let the test runner determine
the number of threads to use.

clean
~~~~~

Alias for ``cargo clean``

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
except for test plugins. At the moment there are no non-test
dependencies for this section.

Problems Solved
---------------

-  ☒ `1 <./src/p0001.rs>`__
-  ☒ `2 <./src/p0002.rs>`__
-  ☒ `3 <./src/p0003.rs>`__
-  ☒ `4 <./src/p0004.rs>`__
-  ☒ `5 <./src/p0005.rs>`__
-  ☒ `6 <./src/p0006.rs>`__
-  ☒ `7 <./src/p0007.rs>`__
-  ☒ `8 <./src/p0008.rs>`__
-  ☒ `9 <./src/p0009.rs>`__
-  ☒ `10 <./src/p0010.rs>`__
-  ☒ `11 <./src/p0011.rs>`__
-  ☒ `12 <./src/p0012.rs>`__
-  ☒ `14 <./src/p0014.rs>`__
-  ☒ `15 <./src/p0015.rs>`__
-  ☒ `16 <./src/p0016.rs>`__
-  ☒ `17 <./src/p0017.rs>`__
-  ☒ `18 <./src/p0018.rs>`__
-  ☒ `19 <./src/p0019.rs>`__
-  ☒ `20 <./src/p0020.rs>`__
-  ☒ `22 <./src/p0022.rs>`__
-  ☒ `24 <./src/p0024.rs>`__
-  ☒ `27 <./src/p0027.rs>`__
-  ☒ `34 <./src/p0034.rs>`__
-  ☒ `69 <./src/p0069.rs>`__
-  ☒ `76 <./src/p0076.rs>`__
-  ☒ `77 <./src/p0077.rs>`__
-  ☒ `87 <./src/p0087.rs>`__
-  ☒ `357 <./src/p0357.rs>`__
-  ☒ `836 <./src/p0836.rs>`__

