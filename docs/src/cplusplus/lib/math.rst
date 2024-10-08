math.hpp
========

View source code :source:`cplusplus/src/include/math.hpp`

Includes
--------

- `"macros.hpp" <./macros.html>`__
- :external:c:type:`math`
- :external:c:type:`stdlib`
- :external:c:type:`stdint`
- :external:c:type:`inttypes`

.. cpp:namespace-push:: math
    
.. cpp:function:: uintmax_t factorial(uint32_t n)

    .. warning::
        
        This function only works for numbers smaller than
        :c:macro:`MAX_FACTORIAL_64` or :c:macro:`MAX_FACTORIAL_128`,
        depending on the size of ``uintmax_t``.

.. cpp:function:: uintmax_t n_choose_r(uint32_t n, uint32_t r)

    Returns -1 if there is an overflow. Otherwise returns n choose r.

    .. warning::
        
        This function only works for numbers smaller than
        :c:macro:`MAX_FACTORIAL_64` or :c:macro:`MAX_FACTORIAL_128`,
        depending on the size of ``uintmax_t``.

.. cpp:namespace-pop::

.. literalinclude:: ../../../../cplusplus/src/include/math.hpp
   :language: C++
   :linenos:
