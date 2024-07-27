primes.rs
=========

View source code `here on GitHub! <https://github.com/LivInTheLookingGlass/Euler/blob/master/rust/src/primes.rs>`_

.. rust:fn:: primes::primes<I>() -> Eratosthenes<I>

  A convenience method that returns an iterator over the prime numbers.

.. rust:fn:: primes::primes_until<I>(x: I) -> Eratosthenes<I>

  A convenience method that returns an iterator over the prime numbers until a given limit.

.. rust:struct:: primes::Eratosthenes<I> where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy

  This class implements the `Sieve of Eratosthenes <https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes>`_. In general,
  it will iterate over all of the prime numbers. You can also provide an optional ``limit`` argument, which will force
  it to not yield any numbers above that limit. Below is a gif (courtesy of Wikipedia) that demonstrates the principle
  of the sieve.

  .. image:: https://upload.wikimedia.org/wikipedia/commons/9/94/Animation_Sieve_of_Eratosth.gif
    :alt: Any animated example of the Sieve of Eratosthenes

  .. rust:fn:: primes::Eratosthenes::new() -> Eratosthenes<I>

  .. rust:fn:: primes::Eratosthenes::with_limit(limit: I) -> Eratosthenes<I>

  .. rust:fn:: primes::Eratosthenes::next() -> Option<I>

.. rust:fn:: primes::prime_factors<I>(x: I) -> PrimeFactors<I>

  A convenience method that returns an iterator over the prime factors of a given number.

.. rust:struct:: primes::PrimeFactors<I> where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy

  This class will iterate over all the prime factors of a number. It *only* supports positive integers. To find the
  factors of a negative number, iterate over the prime factors of its absolute value and add ``-1`` as a factor manually.

  .. rust:fn:: primes::PrimeFactors::new(x: I) -> PrimeFactors<I>

  .. rust:fn:: primes::PrimeFactors::next() -> Option<I>

.. rust:fn:: primes::proper_divisors<I>(x: I) -> Vec<I> where I: NumAssign + Bounded + Ord + Eq + Hash + Copy

  This function returns a vector of the proper divisors of a number.

.. rust:fn:: fn is_composite<I>(x: I) -> I where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy

  Returns ``0`` if the number is prime, and the smallest prime factor otherwise.

.. rust:fn:: fn is_prime<I>(x: I) -> bool where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copy

  Returns ``true`` if the number is prime, and ``false`` otherwise.

.. literalinclude:: ../../rust/src/include/primes.rs
   :language: rust
   :linenos:
