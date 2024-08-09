Euler C# Implementation
=======================

.. include:: ../csharp/README.rst
    :start-line: 2
    :end-before: Makefile

.. include:: ../csharp/README.rst
    :start-after: dependencies for this section.
    :end-before: Problems Solved

Usage
-----

.. highlight:: make

This folder contains a Makefile with several recipes, most of which are aliases to ``dotnet`` commands.
This facilitates the root Makefile dispatching tasks to each language, many of which have more complex
build or test processes.

.. make:target:: test

  Alias for ``dotnet test``.

.. make:target:: test_auto

  .. note::

    WIP

  Runs tests in parallel with one less thread than you have CPUs. Alias for ``dotnet test``.

.. make:target:: test_%

  .. note::

    WIP

  Runs tests in parallel with the specified number of threads. Alias for ``dotnet test``. 

.. make:target:: clean

  Alias for ``dotnet clean``, with some degree of fallback if ``dotnet`` is not installed.

.. make:target:: lint

  Alias for ``dotnet format --verify-no-changes``.

Test Infrastructure
-------------------

.. csharp:namespace:: Euler

.. csharp:class:: Euler.IEuler

   .. csharp:method:: object Answer()

.. csharp:namespace:: EulerTest

.. csharp:class:: EulerTest

   .. csharp:method:: Task EulerTest_Problem()

      An Xunit theory that, for each registered solution, will test against the known answer and a one minute time limit.

Library Code
------------

.. toctree::
   :numbered:
   :maxdepth: 1

   csharp/math
   csharp/primes
   csharp/utils

Problems Solved
---------------

.. toctree::
   :glob:
   :numbered:
   :maxdepth: 1

   csharp/p[0-9][0-9][0-9][0-9]