math.h
======

View source code :source:`c/src/include/math.h`

Includes
--------

- `macros.h <./macros.html>`__

.. c:namespace-push:: math
    
.. c:function:: uintmax_t factorial(unsigned int n)

    .. warning::
        
        This function only works for numbers smaller than
        :c:macro:`MAX_FACTORIAL_64` or :c:macro:`MAX_FACTORIAL_128`,
        depending on the size of :c:expr:`uintmax_t`.

.. c:function:: uintmax_t n_choose_r(unsigned int n, unsigned int r)

    Returns -1 if there is an overflow. Otherwise returns n choose r.

    .. warning::
        
        This function only works for numbers smaller than
        :c:macro:`MAX_FACTORIAL_64` or :c:macro:`MAX_FACTORIAL_128`,
        depending on the size of :c:expr:`uintmax_t`.

.. note::

    The following are only available or necessary for the ``pcc`` compiler, as it has
    a hard time including ``<stdlib.h>``.

.. c:function:: unsigned char imprecise_log10(uintmax_t x)
                double sqrt(double S)
                uintmax_t ceil(double x)

.. c:namespace-pop::

.. literalinclude:: ../../../../c/src/include/math.h
   :language: C
   :linenos: