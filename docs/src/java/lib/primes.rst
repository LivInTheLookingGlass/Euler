Primes.java
===========

View source code :source:`java/src/main/java/euler/lib/Primes.java`

.. java:type:: public class Primes

    .. java:method:: public static Stream<Long> primes()

        :return: Iterates over the prime numbers

    .. java:method:: public static Stream<Long> primesUntil(long limit)

        :return: Iterates over the prime numbers, up until a given limit

    .. java:method:: public static Stream<Long> primeFactors(long target)

        :return: Iterates over the prime factors of a number

.. literalinclude:: ../../../../java/src/main/java/euler/lib/Primes.java
   :language: java
   :linenos:

.. tags:: prime-number, java-iterator
