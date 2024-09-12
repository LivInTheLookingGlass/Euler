Rust Section
============

.. |Rust| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/rust.yml?logo=github&label=Rs%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/rust.yml
.. |RustClippy| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/rust-clippy.yml?logo=github&label=Clippy
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/rust-clippy.yml
.. |Rs-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=Rust&logo=codecov&label=Rs%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=Rust

|Rust| |Rs-Cov| |RustClippy|

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

-  ☒ `1 <./src/problems/p0001.rs>`__
-  ☒ `2 <./src/problems/p0002.rs>`__
-  ☒ `3 <./src/problems/p0003.rs>`__
-  ☒ `4 <./src/problems/p0004.rs>`__
-  ☒ `5 <./src/problems/p0005.rs>`__
-  ☒ `6 <./src/problems/p0006.rs>`__
-  ☒ `7 <./src/problems/p0007.rs>`__
-  ☒ `8 <./src/problems/p0008.rs>`__
-  ☒ `9 <./src/problems/p0009.rs>`__
-  ☒ `10 <./src/problems/p0010.rs>`__
-  ☒ `11 <./src/problems/p0011.rs>`__
-  ☒ `12 <./src/problems/p0012.rs>`__
-  ☒ `14 <./src/problems/p0014.rs>`__
-  ☒ `15 <./src/problems/p0015.rs>`__
-  ☒ `16 <./src/problems/p0016.rs>`__
-  ☒ `17 <./src/problems/p0017.rs>`__
-  ☒ `18 <./src/problems/p0018.rs>`__
-  ☒ `19 <./src/problems/p0019.rs>`__
-  ☒ `20 <./src/problems/p0020.rs>`__
-  ☒ `21 <./src/problems/p0021.rs>`__
-  ☒ `22 <./src/problems/p0022.rs>`__
-  ☒ `23 <./src/problems/p0023.rs>`__
-  ☒ `24 <./src/problems/p0024.rs>`__
-  ☒ `25 <./src/problems/p0025.rs>`__
-  ☒ `27 <./src/problems/p0027.rs>`__
-  ☒ `28 <./src/problems/p0028.rs>`__
-  ☒ `34 <./src/problems/p0034.rs>`__
-  ☒ `35 <./src/problems/p0035.rs>`__
-  ☒ `36 <./src/problems/p0036.rs>`__
-  ☒ `37 <./src/problems/p0037.rs>`__
-  ☒ `41 <./src/problems/p0041.rs>`__
-  ☒ `43 <./src/problems/p0043.rs>`__
-  ☒ `44 <./src/problems/p0044.rs>`__
-  ☒ `45 <./src/problems/p0045.rs>`__
-  ☒ `53 <./src/problems/p0053.rs>`__
-  ☒ `59 <./src/problems/p0059.rs>`__
-  ☒ `67 <./src/problems/p0067.rs>`__
-  ☒ `69 <./src/problems/p0069.rs>`__
-  ☒ `76 <./src/problems/p0076.rs>`__
-  ☒ `77 <./src/problems/p0077.rs>`__
-  ☒ `87 <./src/problems/p0087.rs>`__
-  ☒ `187 <./src/problems/p0187.rs>`__
-  ☒ `357 <./src/problems/p0357.rs>`__
-  ☒ `836 <./src/problems/p0836.rs>`__
