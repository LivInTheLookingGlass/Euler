Euler Java Implementation
=========================

.. include:: ../../java/README.rst
    :start-line: 2
    :end-before: Makefile

.. include:: ../../java/README.rst
    :start-after: dependencies for this section.
    :end-before: Problems Solved

Usage
-----

.. highlight:: make

This folder contains a Makefile with several recipes, most of which are aliases to ``dotnet`` commands.
This facilitates the root Makefile dispatching tasks to each language, many of which have more complex
build or test processes.

.. make:target:: test

  Alias for ``maven test -Dtest.single``.

.. make:target:: test_auto

  .. note::

    WIP

  Runs tests in parallel with one less thread than you have CPUs. Alias for ``maven test-T 1C``.

.. make:target:: test_%

  .. note::

    WIP

  Runs tests in parallel with the specified number of threads. Alias for ``maven test -T $*``. 

.. make:target:: clean

  Alias for ``maven clean``, with some degree of fallback if ``maven`` is not installed.

.. make:target:: lint

  Alias for ``maven formatter:format``.

Test Infrastructure
-------------------

.. java:type:: public interface IEuler

   .. java:method:: Object answer()

    :return: The answer to a Project Euler problem

.. java:type:: public class EulerTest

   .. java:method:: void eulerTestProblem()

      A JUnit theory that, for each registered solution, will test against the known answer and a one minute time limit.

Library Code
------------

.. toctree::
   :glob:
   :maxdepth: 1

   java/lib/*

Problems Solved
---------------

.. toctree::
   :glob:
   :maxdepth: 1

   java/p[0-9][0-9][0-9][0-9]