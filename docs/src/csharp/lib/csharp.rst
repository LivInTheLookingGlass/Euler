prime.cs
========

View source code :source:`csharp/include/prime.cs`

.. csharp:namespace:: Euler

.. csharp:class:: Prime

    .. csharp:method:: static IEnumerable<long> Primes(long? stop = null)

        Iterate over the prime numbers, optionally stopping before the specified value. Primes are cached between
        calls so we don't waste effort.

    .. csharp:method:: static IEnumerable<long> PrimeFactors(long n)

        Iterate over the prime factors of a number (but also ``-1`` and ``0`` in some cases).

    .. csharp:method:: static long isComposite(long n)

        Returns ``0`` if the given number is prime, and otherwise returns its smallest prime factor.

    .. csharp:method:: static bool isPrime(long n)

        Returns ``true`` if a number is prime, and ``false`` otherwise.

.. literalinclude:: ../../../../csharp/Euler/include/prime.cs
   :language: csharp
   :linenos:
