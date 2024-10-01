primes.f90
==========

View source code :source:`fortran/include/primes.f90`

.. f:module:: primes

.. f:function:: next_prime(last)

    :p integer last: The last prime you received (or 1)
    :returns answer: The next prime in the sequence
    :rtype answer: integer

.. f:subroutine:: expand_sieve(potential_n)

    A helper routine that lets you pre-initialize the cache of primes to a high number.
    Otherwise you incur a cost of ``O(n loglogn)`` each time ``n`` doubles.

    :p integer potential_n: The size you wish to expand the sieve to
    :pattrs potential_n: optional

.. literalinclude:: ../../../../fortran/src/include/primes.f90
   :language: Fortran
   :linenos:

.. tags:: fortran-iterator, prime-number
