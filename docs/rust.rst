Euler Rust Implementation
=========================

.. include:: ../rust/README.rst
    :start-line: 2
    :end-before: Makefile

.. include:: ../rust/README.rst
    :start-after: Alias for ``cargo clean``
    :end-before: Problems Solved

Usage
-----

.. highlight:: make

This folder contains a Makefile with several recipes, most of which are aliases to ``cargo`` commands.
This facilitates the root Makefile dispatching tasks to each language, many of which have more complex
build or test processes.

.. make:target:: test

  Alias for ``cargo test``.

.. make:target:: test_auto

  Runs tests in parallel with one less thread than you have CPUs. Alias for ``cargo test -j``.

.. make:target:: test_%

  Runs tests in parallel with the specified number of threads. Alias for ``cargo test -j $*``.

.. make:target:: clean

  Alias for ``cargo clean``.

Library Code
------------

.. toctree::
   :numbered:
   :maxdepth: 1

   rust/digits
   rust/fibonacci
   rust/math
   rust/primes
   rust/triangles
   rust/utils

Problems Solved
---------------

.. toctree::
   :glob:
   :numbered:
   :maxdepth: 1

   rust/p[0-9][0-9][0-9][0-9]
