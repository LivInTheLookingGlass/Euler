factors.h
=========

View source code :source:`c/src/include/factors.h`

Includes
--------

- `iterator.h <./iterator.html>`__
- `macros.h <./macros.html>`__ (implicitly)

This file implements an :c:macro:`Iterator <IteratorHead>` that yields proper
factors for a given number. It is generally used by first calling
:c:func:`proper_divisor_count` and the :c:macro:`next`/:c:macro:`next_p` functions.

.. c:namespace-push:: factors

.. c:type:: factor_counter

    .. c:member:: uintmax_t (*iterator_function)(factor_counter *it)

    .. c:member:: bool exhausted : 1

    .. c:member:: bool started : 1

    .. c:member:: bool phase : 1

    .. c:member:: uintmax_t target
    
    .. c:member:: uintmax_t current

    .. c:function:: uintmax_t advance_factor_counter(factor_counter *fc)

.. c:function:: factor_counter proper_divisors(uintmax_t target)

.. c:function:: uintmax_t proper_divisor_count(uintmax_t target)

.. c:namespace-pop::

.. literalinclude:: ../../../../c/src/include/factors.h
   :language: C
   :linenos:

.. tags:: factorization, divisor-count, c-iterator