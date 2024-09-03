primes.hpp
==========

View source code :source:`cplusplus/src/include/primes.hpp`

Includes
--------

- :external:cpp:type:`iostream`
- :external:cpp:type:`vector`
- :external:cpp:type:`map`
- :external:cpp:type:`limits`

.. cpp:namespace-push:: primes
    
.. cpp:class:: PrimeGenerator

  .. cpp:function:: PrimeGenerator<T> PrimeGenerator<T>()
  .. cpp:function:: PrimeGenerator<T> primes<T>()

    These constructors will return an infinite generator of prime numbers. Note, however, that it does not guard
    against overflow, so choose your type carefully.

  .. cpp:function:: PrimeGenerator<T> PrimeGenerator<T>(T upper_limit)
  .. cpp:function:: PrimeGenerator<T> primes_until<T>(T upper_limit)

    These constructors will return a finite generator of prime numbers, going to ``upper_limit``.

  .. cpp:function:: bool next()

    Returns the next prime, or ``-1`` if it is above the defined limit.

  .. cpp:function:: bool has_next()

    Returns ``true`` if there is a next value to generate.

.. cpp:namespace-pop::

.. literalinclude:: ../../../../cplusplus/src/include/primes.hpp
   :language: C++
   :linenos:

.. tags:: cpp-iterator, prime-number
