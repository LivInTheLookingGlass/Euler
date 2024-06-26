LivInTheLookingGlass’s Project Euler solutions
==============================================

.. |C| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/c.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/c.yml
.. |C#| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/csharp.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/csharp.yml
.. |JavaScript| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/javascript.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/javascript.yml
.. |Python| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/python.yml
.. |CodeQL| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/codeql.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/codeql.yml
.. |Pages| image:: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/pages.yml/badge.svg
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/pages.yml
.. |br| raw:: html

  <br/>
.. |total| replace:: 642

+------------+---------------------+--------------+--------------+
| Language   | Version             | Solved       | Status       |
+============+=====================+==============+==============+
| C          | C11+ in: |br|       | 17 / |total| | |C|          |
|            | ``gcc``, ``pcc``,   |              |              |
|            | ``tcc``, |br|       |              |              |
|            | ``clang``, ``msvc`` |              |              |
+------------+---------------------+--------------+--------------+
| C#         | .NET 5+             | 1 / |total|  | |C#|         |
+------------+---------------------+--------------+--------------+
| JavaScript | Node 12+            | 2 / |total|  | |JavaScript| |
+------------+---------------------+--------------+--------------+
| Python     | CPython 3.6+ |br|   | 70 / |total| | |Python|     |
|            | Pypy 3.8+ |br|      |              |              |
|            | GraalPy 23.1+       |              |              |
+------------+---------------------+--------------+--------------+
| CodeQL Scanning                                 | |CodeQL|     |
+-------------------------------------------------+--------------+
| Documentation (in progress)                     | |Pages|      |
+-------------------------------------------------+--------------+

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

-  ``make c*`` will go to the c Makefile
-  ``make cs*`` will go to the csharp Makefile
-  ``make py*`` will go to the python Makefile
-  ``make js*`` will go to the javascript Makefile
-  Any make recipes supported by Sphinx will be redirected to the docs Makefile
-  All other recipes will be run for all languages

For more information, please see the README documents in each section.