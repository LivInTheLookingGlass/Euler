primes.hpp
==========

View source code :source:`cplusplus/src/include/primes.hpp`

Includes
--------

- :external:cpp:type:`iostream`
- :external:cpp:type:`vector`
- :external:cpp:type:`map`
- :external:cpp:type:`limits`
- :external:cpp:type:`stdexcept`

.. cpp:namespace-push:: primes

.. cpp:class:: PrimeGenerator

  .. cpp:function:: PrimeGenerator<T> PrimeGenerator<T>()
  .. cpp:function:: PrimeGenerator<T> primes<T>()

    These constructors will return an infinite generator of prime numbers. Note, however, that it does not guard
    against overflow, so choose your type carefully.

  .. cpp:function:: PrimeGenerator<T> PrimeGenerator<T>(T upper_limit)
  .. cpp:function:: PrimeGenerator<T> primes_until<T>(T upper_limit)

    These constructors will return a finite generator of prime numbers, going to ``upper_limit``.

  .. cpp:function:: T next()

    Returns the next prime, or ``0`` if it is above the defined limit.

  .. cpp:function:: bool has_next()

    Returns ``true`` if there is a next value to generate.
    
.. cpp:class:: PrimeFactors

  .. cpp:function:: PrimeFactors<T> PrimeFactors<T>(T upper_limit)
  .. cpp:function:: PrimeFactors<T> prime_factors<T>(T upper_limit)

    These constructors will return a finite generator of prime factors of ``target``.

  .. cpp:function:: T next()

    Returns the next prime factor, or ``0`` if it is above the defined limit.

  .. cpp:function:: bool has_next()

    Returns ``true`` if there is a next value to generate.

.. cpp:function:: T is_composite<T>(T target)

  If ``target`` is composite, this returns its first prime factor (or ``-1``). Otherwise returns ``0``.

.. cpp:function:: bool is_prime<T>(T target)

  Tests if a given number is prime.

.. cpp:namespace-pop::

.. literalinclude:: ../../../../cplusplus/src/include/primes.hpp
   :language: C++
   :linenos:

.. tags:: cpp-iterator, prime-number
