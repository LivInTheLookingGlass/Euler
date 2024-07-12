primes.rs
=========

View source code `here on GitHub! <https://github.com/LivInTheLookingGlass/Euler/blob/master/rust/src/primes.rs>`_

.. rust:fn:: primes::primes() -> Eratosthenes

  A convenience method that returns an iterator over the prime numbers.

.. rust:struct:: primes::Eratosthenes

  This class implements the `Sieve of Eratosthenes <https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes>`_. In general,
  it will iterate over all of the prime numbers. You can also provide an optional ``limit`` argument, which will force
  it to not yield any numbers above that limit. Below is a gif (courtesy of Wikipedia) that demonstrates the principle
  of the sieve.

  .. image:: https://upload.wikimedia.org/wikipedia/commons/9/94/Animation_Sieve_of_Eratosth.gif
    :alt: Any animated example of the Sieve of Eratosthenes

  .. rust:fn:: primes::Eratosthenes::new() -> Eratosthenes

  .. rust:fn:: primes::Eratosthenes::with_limit(limit: u64) -> Eratosthenes

  .. rust:fn:: primes::Eratosthenes::next() -> Option<u64>

.. rust:fn:: primes::prime_factors(x: u64) -> PrimeFactors

  A convenience method that returns an iterator over the prime factors of a given number.

.. rust:struct:: primes::PrimeFactors

  This class will iterate over all the prime factors of a number. It *only* supports positive integers. To find the
  factors of a negative number, iterate over the prime factors of its absolute value and add ``-1`` as a factor manually.

  .. rust:fn:: primes::PrimeFactors::new(x: u64) -> PrimeFactors

  .. rust:fn:: primes::PrimeFactors::next() -> Option<u64>

.. rust:fn:: primes::proper_divisors(x: u64) -> Vec<u64>

  This function returns a vector of the proper divisors of a number.

.. literalinclude:: ../../rust/src/primes.rs
   :language: rust
   :linenos:
