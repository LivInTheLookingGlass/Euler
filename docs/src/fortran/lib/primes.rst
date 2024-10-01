primes.f90
==========

View source code :source:`fortran/include/primes.f90`

.. f:module:: primes

.. f:function:: next_prime(last)

    :p integer(i18t) last: The last prime you received (or 1)
    :returns answer: The next prime in the sequence
    :rtype answer: integer(i18t)

.. f:subroutine:: prime_factor(num, factor)

    :p integer(i18t) num: The number you want to factor
    :pattrs num: intent(inout)
    :p integer(i18t) factor: The factor produced
    :pattrs factor: intent(out)

.. f:function:: is_composite(n)

    :p integer(i18t) n: The number you want to determine the compositeness of
    :returns answer: The first prime factor if composite, or 0 otherwise
    :rtype answer: integer(i18t)

.. f:function:: is_prime(n)

    :p integer(i18t) n: The number you want to determine the primality of
    :returns answer:
    :rtype answer: logical

.. f:subroutine:: expand_sieve(potential_n)

    A helper routine that lets you pre-initialize the cache of primes to a high number.
    Otherwise you incur a cost of ``O(n loglogn)`` each time ``n`` doubles.

    .. note::

        If you call this with a value lower than the current size, there is *no cost*, and I highly
        encourage you to do so.

    :p integer(i18t) potential_n: The size you wish to expand the sieve to
    :pattrs potential_n: optional

.. literalinclude:: ../../../../fortran/src/include/primes.f90
   :language: Fortran
   :linenos:

.. tags:: fortran-iterator, prime-number
