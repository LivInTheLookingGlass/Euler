Lua Section
============

.. |Luai| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/lua.yml?logo=github&label=Lua%20Tests
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/lua.yml
.. |LuaCheck| image:: https://img.shields.io/github/actions/workflow/status/LivInTheLookingGlass/Euler/lua-lint.yml?logo=github&label=LuaCheck
   :target: https://github.com/LivInTheLookingGlass/Euler/actions/workflows/lua-lint.yml
.. |Lu-Cov| image:: https://img.shields.io/codecov/c/github/LivInTheLookingGlass/Euler?flag=Lua&logo=codecov&label=Lu%20Cov
   :target: https://app.codecov.io/github/LivInTheLookingGlass/Euler?flags%5B0%5D=Lua

|Luai| |LuaCheck| |Lu-Cov|

Organization
------------

All files share a common prefix with their problem number. All shared
functions are moved to files in the include subfolder

Makefile
--------

There are three main recipes in this Makefile

test
~~~~

Runs the test script

test\_\*
~~~~~~~~

In most subdirectories this would run tests in parallel, however this is not implemented for lua, and it will be redirected to ``test``

clean
~~~~~

Cleans up any stray files from runtime

Tests
-----

Generic Problems
~~~~~~~~~~~~~~~~

For each problem it will check the answer against a known dictionary. If
the problem is not in the "known slow" category (meaning that I generate
the correct answer with a poor solution), it will run it as many times
as the benchmark plugin wants. Otherwise it is run exactly once.

A test fails if it gets the wrong answer or if it takes more than 1
minute.

Dependencies
------------

I try to keep the dependencies of this project as small as possible,
except for test plugins. At the moment there are no dependencies for this section.

Problems Solved
---------------

-  ☒ `1 <./src/p0001.lua>`__
-  ☒ `2 <./src/p0002.lua>`__
-  ☒ `3 <./src/p0003.lua>`__
-  ☒ `4 <./src/p0004.lua>`__
-  ☒ `5 <./src/p0005.lua>`__
-  ☒ `6 <./src/p0006.lua>`__
-  ☒ `7 <./src/p0007.lua>`__
-  ☒ `8 <./src/p0008.lua>`__
-  ☒ `9 <./src/p0009.lua>`__
-  ☒ `10 <./src/p0010.lua>`__
-  ☒ `11 <./src/p0011.lua>`__
-  ☒ `13 <./src/p0013.lua>`__
-  ☒ `14 <./src/p0014.lua>`__
-  ☒ `15 <./src/p0015.lua>`__
-  ☒ `16 <./src/p0016.lua>`__
-  ☒ `17 <./src/p0017.lua>`__
-  ☒ `19 <./src/p0019.lua>`__
-  ☒ `20 <./src/p0020.lua>`__
-  ☒ `22 <./src/p0022.lua>`__
-  ☒ `28 <./src/p0028.lua>`__
-  ☒ `34 <./src/p0034.lua>`__
-  ☒ `76 <./src/p0076.lua>`__
-  ☒ `836 <./src/p0836.lua>`__
