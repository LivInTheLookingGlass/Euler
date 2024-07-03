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

-  ☒ `1 <./p0001.rs>`__

