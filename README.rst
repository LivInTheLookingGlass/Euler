Olivia's Project Euler Solutions
================================

.. |Ci| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/c.yml?logo=github&label=C%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/c.yml
.. |C-lint| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/c-lint.yml?logo=github&label=Linting
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/c-lint.yml
.. |Cpi| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/cplusplus.yml?logo=github&label=Cpp%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/cplusplus.yml
.. |Cp-lint| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/cplusplus-lint.yml?logo=github&label=Linting
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/cplusplus-lint.yml
.. |C#i| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/csharp.yml?logo=github&label=C%23%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/csharp.yml
.. |C#-lint| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/csharp-lint.yml?logo=github&label=Linting
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/csharp-lint.yml
.. |Javai| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/java.yml?logo=github&label=Java%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/java.yml
.. |Java-lint| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/java-lint.yml?logo=github&label=Linting
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/java-lint.yml
.. |JavaScript| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/javascript.yml?logo=github&label=Js%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/javascript.yml
.. |ESLint| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/eslint.yml?logo=github&label=ESLint
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/eslint.yml
.. |Python| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/python.yml?logo=github&label=Py%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python.yml
.. |PythonLint| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/python-lint.yml?logo=github&label=Linting
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python-lint.yml
.. |Rust| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/rust.yml?logo=github&label=Rs%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/rust.yml
.. |RustClippy| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/rust-clippy.yml?logo=github&label=Clippy
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/rust-clippy.yml
.. |CodeQL| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/codeql.yml?logo=github&label=CodeQL
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/codeql.yml
.. |C-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=C&logo=codecov&label=C%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=C
.. |Cp-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=Cpp&logo=codecov&label=Cpp%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=Cpp
.. |Cs-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=Csharp&logo=codecov&label=C%23%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=Csharp
.. |Ja-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=Java&logo=codecov&label=Java%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=Java
.. |Js-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=JavaScript&logo=codecov&label=Js%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=JavaScript
.. |Py-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=Python&logo=codecov&label=Py%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=Python
.. |Rs-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=Rust&logo=codecov&label=Rs%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=Rust
.. |br| raw:: html

  <br/>

.. |gcc| replace:: ``gcc``
.. |clang| replace:: ``clang``
.. |msvc| replace:: ``msvc``
.. |pcc| replace:: ``pcc``
.. |tcc| replace:: ``tcc``

+------------+---------------------------+--------+-------------------+
| Language   | Version                   | Solved | Status            |
+============+===========================+========+===================+
| C          | C99+ in: |clang|, |br|    | 22     | |Ci| |br|         |
|            | |gcc|, |pcc|, |tcc| |br|  |        | |C-Cov| |br|      |
|            | C11+ in: |msvc| [1]_      |        | |CodeQL| |br|     |
|            |                           |        | |C-lint|          |
+------------+---------------------------+--------+-------------------+
| C++        | C++98+ in: |br| |clang|   | 17     | |Cpi| |br|        |
|            | |gcc| |br|                |        | |Cp-Cov| |br|     |
|            | C++14+ in: |msvc| [1]_    |        | |CodeQL| |br|     |
|            |                           |        | |Cp-lint|         |
+------------+---------------------------+--------+-------------------+
| C#         | .NET 2+                   | 17     | |C#i| |br|        |
|            |                           |        | |Cs-Cov| |br|     |
|            |                           |        | |CodeQL| |br|     |
|            |                           |        | |C#-lint|         |
+------------+---------------------------+--------+-------------------+
| Java       | Java 8+ in Corretto, |br| | 17     | |Javai| |br|      |
|            |Dragonwell, Liberica, |br| |        | |Ja-Cov| |br|     |
|            | Microsoft, Oracle, |br|   |        | |CodeQL| |br|     |
|            | Semeru, Temurin, Zulu     |        | |Java-lint|       |
+------------+---------------------------+--------+-------------------+
| JavaScript | Node 12+ |br|             | 25     | |JavaScript| |br| |
|            | Bun 1.0+ |br|             |        | |Js-Cov| |br|     |
|            | Browser [2]_              |        | |CodeQL| |br|     |
|            |                           |        | |ESLint|          |
+------------+---------------------------+--------+-------------------+
| Python     | CPython 3.6+ |br|         | 79     | |Python| |br|     |
|            | Pypy 3.6+ |br|            |        | |Py-Cov| |br|     |
|            | GraalPy 23.1+ |br|        |        | |CodeQL| |br|     |
|            | Browser [3]_              |        | |PythonLint|      |
+------------+---------------------------+--------+-------------------+
| Rust       | 1.69+                     | 28     | |Rust| |br|       |
|            |                           |        | |Rs-Cov| |br|     |
|            |                           |        | |RustClippy|      |
+------------+---------------------------+--------+-------------------+

.. |test-js-link| raw:: html

   <a href="https://euler.oliviaappleton.com/_static/test-js.html" target="_blank">click here!</a>

.. |test-py-link| raw:: html

   <a href="https://euler.oliviaappleton.com/_static/test-py.html" target="_blank">click here!</a>

.. [1] This is the earliest standard the MSVC explicitly supports.
.. [2] While these solutions do run in most browsers, they need to be bundled with WebPack 5.93+ & Babel 7.25+ first,
   and these tests not yet automated as in Nodejs and Bun. To run these tests yourself, |test-js-link|
.. [3] While these solutions do run in most browsers, they need to be bundled with Pyodide 0.26.2+ first, and these
   tests are not yet automated as in CPython and pypy. To run these tests yourself, |test-py-link|

Coverage
--------
.. image:: https://codecov.io/github/LivInTheLookingGlass/Euler/graphs/icicle.svg?token=6GHBNILEHG
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler

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
-  ``make ja_*`` will go to the java Makefile
-  ``make js_*`` will go to the javascript Makefile
-  ``make py_*`` will go to the python Makefile
-  ``make rs_*`` will go to the rust Makefile
-  Any make recipes supported by Sphinx will be redirected to the docs Makefile
-  All other recipes will be run for all languages

For more information, please see the README documents in each section.
