fibonacci.rs
=============

View source code :source:`rust/src/include/fibonacci.rs`

Includes
--------

use std::ops::{Add,Mul};

use num_traits::{one,zero,One,Zero};

use crate::include::iter_cache::cache_iterator;

- :external:rust:trait:`num_traits::One`
- :external:rust:trait:`num_traits::Zero`
- :external:rust:fn:`num_traits::one`
- :external:rust:fn:`num_traits::zero`
- :external:rust:trait:`std::ops::Add`
- :external:rust:trait:`std::ops::Mul`

.. rust:struct:: pub struct fibonacci::CachingIterator<I, T> where I: Iterator<Item = T> + 'static, T: Clone + 'static

    This struct implements a global cache that maps an iterator-iterated pair to a cache of values. It is mostly
    intended for use with the prime function generator.

  .. rust:fn:: pub fn fibonacci::CachingIterator::new() -> CachingIterator<I, T> where I: Iterator<Item = T> + 'static, T: Clone + 'static

  .. rust:fn:: pub fn fibonacci::CachingIterator::default() -> CachingIterator<I, T> where I: Iterator<Item = T> + 'static, T: Clone + 'static

  .. rust:fn:: pub fn fibonacci::CachingIterator::next() -> Option<T> where T: Clone + 'static

.. literalinclude:: ../../../../rust/src/include/fibonacci.rs
   :language: rust
   :linenos:
