.. Euler documentation master file, created by
   sphinx-quickstart on Fri Jun 28 11:07:39 2024.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to Euler's documentation!
=================================

This repo includes solutions in the following languages:

.. include:: ../README.rst
    :start-line: 2
    :end-before: This is the repository

Usage
-----

This project is divided into several Makefiles, connected by a root Makefile which redirects commands whever necessary.

.. highlight:: make

.. make:var:: PY

  A string that contains the command used for your Python interpreter. Defaults to ``python3``.

.. make:target:: clean

  Removes all temporary or cache files, as well as any build artifacts

.. make:target:: html

  This recipe redirects to the docs Makefile. Note that this is actually a
  multi-target recipe that includes any builder name supported by
  `Sphinx <https://www.sphinx-doc.org/en/master/usage/builders/index.html>`__.
  Only ``html`` has guaranteed support, but currently implemented are:

  - ``html``
  - ``dirhtml``
  - ``singlehtml``
  - ``epub``
  - ``latex``
  - ``man``
  - ``htmlhelp``
  - ``qthelp``
  - ``devhelp``
  - ``applehelp``
  - ``texinfo``
  - ``text``
  - ``gettext``
  - ``doctest``
  - ``linkcheck``
  - ``xml``
  - ``pseudoxml``

.. make:target:: cs%

  Recipes with this prefix are redirected to the C# directory. Please see language-specific documentation for more details.

.. make:target:: c%

  Recipes with this prefix are redirected to the C directory. Please see language-specific documentation for more details.

.. make:target:: js%

  Recipes with this prefix are redirected to the JavaScript directory. Please see language-specific documentation for more details.

.. make:target:: py%

  Recipes with this prefix are redirected to the Python directory. Please see language-specific documentation for more details.

.. make:target:: rs%

  Recipes with this prefix are redirected to the Rust directory. Please see language-specific documentation for more details.

.. make:target:: %

  If the recipe you call isn't covered by any others, it will get distributed to all languages. So for instance,
  ``make test`` would be translated to ``make cstest ctest jstest pytest rstest``

.. toctree::
   :maxdepth: 2

   c
   csharp
   javascript
   python
   rust

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
