Euler C# Implementation
=======================

.. include:: ../csharp/README.rst
    :start-line: 2
    :end-before: Problems Solved

Test Infrastructure
-------------------

.. csharp:namespace:: Euler

.. csharp:interface:: Euler.IEuler

   .. csharp:method:: Task<Int64> Answer

.. csharp:namespace:: EulerTest

.. csharp:class:: EulerTest

   .. csharp:method:: Task EulerTest_Problem

      An Xunit theory that, for each registered solution, will test against the known answer and a one minute time limit.

Problems Solved
---------------

.. toctree::
   :maxdepth: 1

   csharp/p0001.rst
