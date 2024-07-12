primes.rs
=========

View source code `here on GitHub! <https://github.com/LivInTheLookingGlass/Euler/blob/master/rust/src/primes.rs>`_

.. rust:fn:: primes::primes() -> Eratosthenes
.. rust:struct:: primes::Eratosthenes

  .. rust:fn:: primes::Eratosthenes::new() -> Eratosthenes

  .. rust:fn:: primes::Eratosthenes::with_limit(limit: u64) -> Eratosthenes

  .. rust:fn:: primes::Eratosthenes::next() -> Option<u64>

.. rust:fn:: primes::prime_factors(x: u64 -> PrimeFactors
.. rust:struct:: primes::PrimeFactors

  .. rust:fn:: primes::PrimeFactors::new(x: u64) -> PrimeFactors

  .. rust:fn:: primes::PrimeFactors::next() -> Option<u64>

.. rust:fn:: primes::proper_divisors(x: u64) -> Vec<u64>

.. literalinclude:: ../../rust/src/primes.rs
   :language: rust
   :linenos:
