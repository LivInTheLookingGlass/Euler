primes.rs
=========

View source code :source:`rust/src/include/primes.rs`

Includes
--------

- `iter_cache.rs <./iter_cache.html>`_
- :external:rust:trait:`num_traits::One`
- :external:rust:trait:`num_traits::Zero`
- :external:rust:fn:`num_traits::one`
- :external:rust:fn:`num_traits::zero`
- :external:rust:trait:`itertools::Itertools`
- :external:rust:struct:`std::collections::HashMap`
- :external:rust:struct:`std::iter::TakeWhile`
- :external:rust:trait:`std::cmp::Ord`
- :external:rust:trait:`std::hash::Hash`
- :external:rust:trait:`std::ops::Add`
- :external:rust:trait:`std::ops::Div`
- :external:rust:trait:`std::ops::Mul`
- :external:rust:trait:`std::ops::Rem`

.. rust:fn:: pub fn primes::primes<I>() -> impl Iterator<Item = I>

  A convenience method that returns an iterator over the prime numbers.

.. rust:fn:: pub fn primes::primes_until<I>(x: I) -> impl Iterator<Item = I>

  A convenience method that returns an iterator over the prime numbers until a given limit.

.. rust:struct:: pub struct primes::Eratosthenes<I> where I: Hash

  This class implements the `Sieve of Eratosthenes <https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes>`_. In general,
  it will iterate over all of the prime numbers. You can also provide an optional ``limit`` argument, which will force
  it to not yield any numbers above that limit. Below is a gif (courtesy of Wikipedia) that demonstrates the principle
  of the sieve.

  .. image:: https://upload.wikimedia.org/wikipedia/commons/9/94/Animation_Sieve_of_Eratosth.gif
    :alt: Any animated example of the Sieve of Eratosthenes

  .. rust:fn:: pub fn primes::Eratosthenes::new() -> Eratosthenes<I> where I: Hash + One + Zero + Add

  .. rust:fn:: pub fn primes::Eratosthenes::default() -> Eratosthenes<I> where I: Hash + One + Zero + Add

  .. rust:fn:: pub fn primes::Eratosthenes::next() -> Option<I> where I: Hash + One + Zero + Add + Mul + Ord + Copy

.. rust:fn:: pub fn primes::prime_factors<I>(x: I) -> PrimeFactors<I>

  A convenience method that returns an iterator over the prime factors of a given number.

.. rust:struct:: pub struct primes::PrimeFactors<I>

  This class will iterate over all the prime factors of a number. It *only* supports positive integers. To find the
  factors of a negative number, iterate over the prime factors of its absolute value and add ``-1`` as a factor manually.

  .. rust:fn:: pub fn primes::PrimeFactors::new(where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copyx: I)

  .. rust:fn:: pub fn primes::PrimeFactors::next() -> Option<I> where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I>

.. rust:fn:: pub fn is_composite<I>(x: I) -> I where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I>

  Returns ``0`` if the number is prime, and the smallest prime factor otherwise.

.. rust:fn:: pub fn is_prime<I>(x: I) -> bool where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I>

  Returns ``true`` if the number is prime, and ``false`` otherwise.

.. literalinclude:: ../../../../rust/src/include/primes.rs
   :language: rust
   :linenos:

.. tags:: rust-iterator, prime-number, divisor-count, divisibility
