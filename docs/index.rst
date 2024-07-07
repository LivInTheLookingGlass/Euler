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

.. make:target:: cs_%

  Recipes with this prefix are redirected to the C# directory. Please see language-specific documentation for more details.

.. make:target:: c_%

  Recipes with this prefix are redirected to the C directory. Please see language-specific documentation for more details.

.. make:target:: docs_%

  Recipes with this prefix are redirected to the docs directory.

.. make:target:: js_%

  Recipes with this prefix are redirected to the JavaScript directory. Please see language-specific documentation for more details.

.. make:target:: py_%

  Recipes with this prefix are redirected to the Python directory. Please see language-specific documentation for more details.

.. make:target:: rs_%

  Recipes with this prefix are redirected to the Rust directory. Please see language-specific documentation for more details.

.. make:target:: %

  If the recipe you call isn't covered by any others, it will get distributed to all languages. So for instance,
  ``make test`` would be translated to ``make cs_test c_test js_test py_test rs_test``

+-----------------+-----+------+------+------+------+
|                 |**C**|**C#**|**Js**|**Py**|**Rs**|
+=================+=====+======+======+======+======+
| Documentatation |  ⏱  |      |      |      |   ⏱  |
+-----------------+-----+------+------+------+------+
| Linting         |     |      |      |      |      |
+-----------------+-----+------+------+------+------+
| Coverage        |  ✔  |   ⏱  |      |      |   ⏱  |
+=================+=====+======+======+======+======+
| Problem 001     |  ✔  |   ✔  |   ✔  |   ✔  |   ✔  |
+-----------------+-----+------+------+------+------+-+-----------------+-----+------+------+------+------+
| Problem 002     |  ✔  |   ✔  |   ✔  |   ✔  |   ✔  |
+-----------------+-----+------+------+------+------+
| Problem 003     |  ✔  |      |      |   ✔  |      |
+-----------------+-----+------+------+------+------+
| Problem 004     |  ✔  |      |      |   ✔  |      |
+-----------------+-----+------+------+------+------+
| Problem 005     |  ✔  |      |      |   ✔  |      |
+-----------------+-----+------+------+------+------+
| Problem 006     |  ✔  |      |      |   ✔  |      |
+-----------------+-----+------+------+------+------+
| Problem 007     |  ✔  |      |      |   ✔  |      |
+-----------------+-----+------+------+------+------+
| Problem 008     |  ✔  |      |      |   ✔  |      |
+-----------------+-----+------+------+------+------+
| Problem 009     |  ✔  |      |      |   ✔  |      |
+-----------------+-----+------+------+------+------+
| Problem 010     |  ✔  |      |      |   ✔  |      |
+-----------------+-----+------+------+------+------+
| Problem 011     |  ✔  |      |      |   ✔  |      |
+-----------------+-----+------+------+------+------+
| Problem 012     |  ⏱  |      |      |   ✔  |      |
+-----------------+-----+------+------+------+------+
| Problem 013     |  ✔  |      |      |   ✔  |      |
+-----------------+-----+------+------+------+------+
| Problem 014     |  ✔  |      |      |   ✔  |      |
+-----------------+-----+------+------+------+------+
| Problem 015     |  ✔  |      |      |   ✔  |      |
+-----------------+-----+------+------+------+------+
| Problem 016     |  ✔  |      |      |   ✔  |      |
+-----------------+-----+------+------+------+------+

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
