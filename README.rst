LivInTheLookingGlass’s Project Euler solutions
==============================================

.. |Ci| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/c.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/c.yml
.. |C#i| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/csharp.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/csharp.yml
.. |Cpi| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/cplusplus.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/cplusplus.yml
.. |JavaScript| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/javascript.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/javascript.yml
.. |Python| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python.yml
.. |Rust| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/rust.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/rust.yml
.. |CodeQL| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/codeql.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/codeql.yml
.. |ESLint| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/eslint.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/eslint.yml
.. |RustClippy| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/rust-clippy.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/rust-clippy.yml
.. |PythonLint| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python-lint.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python-lint.yml
.. |Pages| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/pages.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/pages.yml
.. |Coverage| image:: https://codecov.io/github/LivInTheLookingGlass/Euler/graph/badge.svg?token=6GHBNILEHG 
   :target: https://codecov.io/github/LivInTheLookingGlass/Euler
.. |br| raw:: html

  <br/>

+------------+-------------------------+--------+-------------------+
| Language   | Version                 | Solved | Status            |
+============+=========================+========+===================+
| C          | C99+ in: ``gcc``, |br|  | 17     | |Ci|              |
|            | ``clang``, ``msvc``,    |        |                   |
|            | |br| ``pcc``, ``tcc``   |        |                   |
+------------+-------------------------+--------+-------------------+
| C++        | C++98+ in |br|          |  3     | |Cpi|             |
|            | ``gcc``, ``clang`` |br| |        |                   |
|            | C++14+ in ``msvc``      |        |                   |
+------------+-------------------------+--------+-------------------+
| C#         | .NET 2+                 |  6     | |C#i|             |
+------------+-------------------------+--------+-------------------+
| JavaScript | Node 12+                |  6     | |JavaScript|      |
+------------+-------------------------+--------+-------------------+
| Python     | CPython 3.6+ |br|       | 70     | |Python|          |
|            | Pypy 3.6+ |br|          |        |                   |
|            | GraalPy 23.1+           |        |                   |
+------------+-------------------------+--------+-------------------+
| Rust       | 1.69+                   | 11     | |Rust|            |
+------------+-------------------------+--------+-------------------+
| Documentation (in progress)                   | |Pages|           |
+-----------------------------------------------+-------------------+
| Code Coverage                                 | |Coverage|        |
+-----------------------------------------------+-------------------+
| Code Scanning                                 | |CodeQL| |br|     |
|                                               | |ESLint| |br|     |
|                                               | |PythonLint| |br| |
|                                               | |RustClippy|      |
+-----------------------------------------------+-------------------+

Coverage
--------

.. image:: https://codecov.io/github/LivInTheLookingGlass/Euler/graphs/icicle.svg?token=6GHBNILEHG

This is the repository I keep for prospective employers to look at
project Euler code that I have written.

This is useful because it has defined problems and answers such that you
can compare answers with other people.

All solutions are tested against multiple operating systems and
language/compiler versions. For more information, see
``.github/workflows/``

This is NOT meant to help others on Project Euler problems
----------------------------------------------------------

If you are working on Project Euler problems, DO NOT use this as a source
-------------------------------------------------------------------------

The repo is divided into sections for each language. The top-level
Makefile will direct recipes using prefixes

-  ``make c_*`` will go to the c Makefile
-  ``make cp_*`` will go to the csharp Makefile
-  ``make cs_*`` will go to the csharp Makefile
-  ``make docs_*`` will go to the docs Makefile
-  ``make js_*`` will go to the javascript Makefile
-  ``make py_*`` will go to the python Makefile
-  ``make rs_*`` will go to the rust Makefile
-  Any make recipes supported by Sphinx will be redirected to the docs Makefile
-  All other recipes will be run for all languages

For more information, please see the README documents in each section.

Roadmap
-------

1. Make sure no language is below Makefile in code percentage
2. Create a C++ section
  a. Make stubs for test code
  b. Port C infrastructure to C++
  c. Write minimal documentation
  d. Port problems 1-n, until higher than Makefile percentage
3. Repeat step 1
4. Create a Ruby section
