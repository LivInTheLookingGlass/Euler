Usage
=====

This project is divided into several Makefiles, connected by a root Makefile which redirects commands whever necessary.

.. highlight:: make

Root Recipes
------------

.. make:var:: PY

  A string that contains the command used for your Python interpreter. Defaults to ``python3``.

.. make:target:: help

  Prints the recipes found in all subfolders.

.. make:target:: clean

  Removes all temporary or cache files, as well as any build artifacts.

.. make:target:: html
.. make:target:: dirhtml
.. make:target:: singlehtml
.. make:target:: epub
.. make:target:: latex

  These recipes redirect to the docs Makefile. Note that this is a multi-target recipe that includes many of the
  builder names supported by `Sphinx <https://www.sphinx-doc.org/en/master/usage/builders/index.html>`__.

.. make:target:: c_%

  Recipes with this prefix are redirected to the C directory. Please see language-specific documentation for more details.

.. make:target:: cp_%

  Recipes with this prefix are redirected to the C++ directory. Please see language-specific documentation for more details.

.. make:target:: cs_%

  Recipes with this prefix are redirected to the C# directory. Please see language-specific documentation for more details.

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
  ``make test`` would be translated to ``make c_test cp_test cs_test js_test py_test rs_test``

Universal Recipes
-----------------

The recipes in this section are supported by every language.

.. make:target:: help

  Prints the recipes found in a given folder.

.. make:target:: test
.. make:target:: test_auto
.. make:target:: test_%

  These recipes will run through the test routine of whichever language they are called for. If called with no suffix,
  tests will be run in a single thread. If called with the ``auto`` suffix, it will run using all or nearly all the
  of the CPUs on the machine. If called with an integer suffix, it will run tests in that number of threads. Note that
  while not all test runners support specifying a number of threads, the recipe is maintained in all languages for
  compatibility reasons.

.. make:target:: clean

  Removes all temporary or cache files, as well as any build artifacts.
