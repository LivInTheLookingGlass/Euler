primes.rs
=========

View source code :source:`rust/src/include/primes.rs`

Includes
--------

- `num_traits::One <https://docs.rs/num-traits/latest/num_traits/identities/trait.One.html>`_
- `num_traits::Zero <https://docs.rs/num-traits/latest/num_traits/identities/trait.Zero.html>`_
- `num_traits::one <https://docs.rs/num-traits/latest/num_traits/identities/fn.one.html>`_
- `num_traits::zero <https://docs.rs/num-traits/latest/num_traits/identities/fn.zero.html>`_
- `itertools::Itertools <https://docs.rs/itertools/latest/itertools/trait.Itertools.html>`_
- :rsref:`std::collections::HashMap <std/collections/struct.HashMap>`
- :rsref:`std::cmp::Ord <std/cmp/trait.Ord>`
- :rsref:`std::hash::Hash <std/cmp/trait.Hash>`
- :rsref:`std::ops::Add <std/ops/trait.Add>`
- :rsref:`std::ops::Div <std/ops/trait.Div>`
- :rsref:`std::ops::Mul <std/ops/trait.Mul>`
- :rsref:`std::ops::Rem <std/ops/trait.Rem>`

.. rust:fn:: pub fn primes::primes<I>() -> Eratosthenes<I> where I: Hash + One + Zero + Add

  A convenience method that returns an iterator over the prime numbers.

.. rust:fn:: pub fn primes::primes_until<I>(x: I) -> Eratosthenes<I> where I: Hash + One + Zero + Add

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

  .. rust:fn:: pub fn primes::Eratosthenes::with_limit(limit: I) -> Eratosthenes<I> where I: Hash + One + Zero + Add

  .. rust:fn:: pub fn primes::Eratosthenes::next() -> Option<I> where I: Hash + One + Zero + Add + Mul + Ord + Copy

.. rust:fn:: pub fn primes::prime_factors<I>(x: I) -> PrimeFactors<I>

  A convenience method that returns an iterator over the prime factors of a given number.

.. rust:struct:: pub struct primes::PrimeFactors<I>

  This class will iterate over all the prime factors of a number. It *only* supports positive integers. To find the
  factors of a negative number, iterate over the prime factors of its absolute value and add ``-1`` as a factor manually.

  .. rust:fn:: pub fn primes::PrimeFactors::new(where I: NumAssign + Bounded + PartialOrd + Eq + Hash + Copyx: I)

  .. rust:fn:: pub fn primes::PrimeFactors::next() -> Option<I> where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I>

.. rust:fn:: pub fn primes::proper_divisors<I>(x: I) -> Vec<I> where I: NumAssign + Bounded + Ord + Eq + Hash + Copy

  This function returns a vector of the proper divisors of a number.

.. rust:fn:: pub fn is_composite<I>(x: I) -> I where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I>

  Returns ``0`` if the number is prime, and the smallest prime factor otherwise.

.. rust:fn:: pub fn is_prime<I>(x: I) -> bool where I: Hash + Zero + One + Add + Ord + Copy + Div<Output=I> + Rem<Output=I>

  Returns ``true`` if the number is prime, and ``false`` otherwise.

.. literalinclude:: ../../../../rust/src/include/primes.rs
   :language: rust
   :linenos:

.. tags:: rust-iterator, prime-number, divisor-count, divisibility
