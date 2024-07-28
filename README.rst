LivInTheLookingGlass’s Project Euler solutions
==============================================

.. |Ci| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/c.yml?logo=github&logoSize=auto&label=C%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/c.yml
.. |Cpi| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/cplusplus.yml?logo=github&logoSize=auto&label=Cpp%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/cplusplus.yml
.. |C#i| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/csharp.yml?logo=github&logoSize=auto&label=C%23%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/csharp.yml
.. |JavaScript| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/javascript.yml?logo=github&logoSize=auto&label=Js%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/javascript.yml
.. |Python| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/python.yml?logo=github&logoSize=auto&label=Py%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python.yml
.. |Rust| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/rust.yml?logo=github&logoSize=auto&label=Rs%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/rust.yml
.. |CodeQL| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/codeql.yml?logo=github&logoSize=auto&label=CodeQL
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/codeql.yml
.. |ESLint| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/eslint.yml?logo=github&logoSize=auto&label=ESLint
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/eslint.yml
.. |RustClippy| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/rust-clippy.yml?logo=github&logoSize=auto&label=Clippy
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/rust-clippy.yml
.. |PythonLint| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/python-lint.yml?logo=github&logoSize=auto&label=mypy%2Bisort
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python-lint.yml
.. |C-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=C&logo=codecov&logoSize=auto&label=C%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=C
.. |Cp-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=Cpp&logo=codecov&logoSize=auto&label=Cpp%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=Cpp
.. |Cs-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=Csharp&logo=codecov&logoSize=auto&label=C%23%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=C%23
.. |Js-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=JavaScript&logo=codecov&logoSize=auto&label=Js%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=JavaScript
.. |Py-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=Python&logo=codecov&logoSize=auto&label=Py%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=Python
.. |Rs-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=Rust&logo=codecov&logoSize=auto&label=Rs%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=Rust
.. |br| raw:: html

  <br/>

+------------+-------------------------+--------+-------------------+
| Language   | Version                 | Solved | Status            |
+============+=========================+========+===================+
| C          | C99+ in: ``gcc``, |br|  | 17     | |Ci| |br|         |
|            | ``clang``, ``msvc``,    |        | |C-Cov| |br|      |
|            | |br| ``pcc``, ``tcc``   |        | |CodeQL|          |
+------------+-------------------------+--------+-------------------+
| C++        | C++98+ in |br|          | 10     | |Cpi| |br|        |
|            | ``gcc``, ``clang`` |br| |        | |Cp-Cov| |br|     |
|            | C++14+ in ``msvc``      |        | |CodeQL|          |
+------------+-------------------------+--------+-------------------+
| C#         | .NET 2+                 |  6     | |C#i| |br|        |
|            |                         |        | |Cs-Cov| |br|     |
|            |                         |        | |CodeQL|          |
+------------+-------------------------+--------+-------------------+
| JavaScript | Node 12+ |br|           |  6     | |JavaScript| |br| |
|            | Bun                     |        | |Js-Cov| |br|     |
|            |                         |        | |CodeQL| |br|     |
|            |                         |        | |ESLint|          |
+------------+-------------------------+--------+-------------------+
| Python     | CPython 3.6+ |br|       | 77     | |Python| |br|     |
|            | Pypy 3.6+ |br|          |        | |Py-Cov| |br|     |
|            | GraalPy 23.1+           |        | |CodeQL| |br|     |
|            |                         |        | |PythonLint|      |
+------------+-------------------------+--------+-------------------+
| Rust       | 1.69+                   | 20     | |Rust| |br|       |
|            |                         |        | |Rs-Cov| |br|     |
|            |                         |        | |RustClippy|      |
+------------+-------------------------+--------+-------------------+

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
1. Repeat step 1
2. Create a Ruby section
