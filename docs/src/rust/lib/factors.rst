factors.rs
==========

View source code :source:`rust/src/include/factors.rs`

Includes
--------

- `primes.rs <./primes.html>`_
- :external:rust:trait:`num_traits::One`
- :external:rust:trait:`num_traits::Zero`
- :external:rust:fn:`num_traits::one`
- :external:rust:fn:`num_traits::zero`
- :external:rust:trait:`itertools::Itertools`
- :external:rust:struct:`std::collections::HashMap`
- :external:rust:trait:`std::cmp::Ord`
- :external:rust:trait:`std::hash::Hash`
- :external:rust:trait:`std::ops::Add`
- :external:rust:trait:`std::ops::Div`
- :external:rust:trait:`std::ops::Mul`
- :external:rust:trait:`std::ops::Rem`

.. rust:fn:: pub fn factors::proper_divisors<I>() -> ProperDivisors<I> where I: Hash + One + Zero + Add + Div + Rem + Mul

  A convenience method that returns an iterator over the prime numbers.

.. literalinclude:: ../../../../rust/src/include/factors.rs
   :language: rust
   :linenos:

.. tags:: rust-iterator, divisor-count, divisibility
