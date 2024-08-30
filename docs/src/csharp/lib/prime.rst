prime.cs
========

View source code :source:`csharp/include/prime.cs`

Includes
--------

.. csharp:namespace:: Euler

.. csharp:class:: Prime

    .. csharp:method:: static IEnumerable<T> Primes<T>(T? stop = null)

        This function implements the `Sieve of Eratosthenes <https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes>`_. In general,
        it will iterate over all of the prime numbers. You can also provide an optional ``stop`` argument, which will force
        it to not yield any numbers above that limit. Below is a gif (courtesy of Wikipedia) that demonstrates the principle
        of the sieve.

        .. image:: https://upload.wikimedia.org/wikipedia/commons/9/94/Animation_Sieve_of_Eratosth.gif
            :alt: Any animated example of the Sieve of Eratosthenes

    .. csharp:method:: static IEnumerable<T> PrimeFactors<T>(T n)

        This function will iterate over all the prime factors of a number, as well as ``-1`` and ``0`` if relevant.

    .. csharp:method:: static dynamic isComposite(long n)

        Returns ``0`` if the number is prime, and the smallest prime factor otherwise.

    .. csharp:method:: static bool isPrime(dynamic n)

        Returns ``true`` if the number is prime, and ``false`` otherwise.

.. literalinclude:: ../../../../csharp/Euler/include/prime.cs
   :language: csharp
   :linenos:

.. tags:: csharp-iterator, prime-number
