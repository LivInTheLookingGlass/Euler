math.h
======

View source code `here on GitHub! <https://github.com/LivInTheLookingGlass/Euler/blob/master/cplusplus/src/include/math.h>`_

.. c:namespace-push:: math
    
.. c:function:: uintmax_t factorial(unsigned int n)

    .. warning::
        
        This function only works for numbers smaller than
        :c:macro:`MAX_FACTORIAL_64` or :c:macro:`MAX_FACTORIAL_128`,
        depending on the size of ``uintmax_t``.

.. c:function:: uintmax_t n_choose_r(unsigned int n, unsigned int r)

    Returns -1 if there is an overflow. Otherwise returns n choose r.

    .. warning::
        
        This function only works for numbers smaller than
        :c:macro:`MAX_FACTORIAL_64` or :c:macro:`MAX_FACTORIAL_128`,
        depending on the size of ``uintmax_t``.

.. c:namespace-pop::

.. literalinclude:: ../../cplusplus/src/include/math.h
   :language: C++
   :linenos:
