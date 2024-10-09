math.f90
========

View source code :source:`fortran/include/math.f90`

.. f:module:: math

.. f:function:: factorial(n)

    :p integer n:
    :returns answer: n!
    :rtype answer: integer(i18t)

.. f:function:: n_choose_r(n, r)

    :p integer n:
    :p integer r:
    :returns answer: nCr
    :rtype answer: integer(i18t)

.. f:function:: n_choose_r_slow(n, r)

    This is a helper function for numbers that would otherwise overflow using the naive calculation of
    ``factorial(n) / factorial(r) / factorial(n - r)``. It's a slower path, but a much more reliable one
    because it actually factorizes the numbers and cancels out as many as possible before multiplying.

    :p integer n:
    :p integer r:
    :returns answer: nCr
    :rtype answer: integer(i18t)

.. literalinclude:: ../../../../fortran/src/include/math.f90
   :language: Fortran
   :linenos:
