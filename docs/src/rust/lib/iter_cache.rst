iter_cache.rs
=============

View source code :source:`rust/src/include/iter_cache.rs`

Includes
--------

- :external:rust:struct:`std::any::TypeId`
- :external:rust:struct:`std::collections::HashMap`
- :external:rust:trait:`std::sync::Mutex`
- :external:rust:struct:`std::sync::RwLock`
- :external:rust:fn:`std::sync::Once`

.. rust:struct:: pub struct iter_cache::CachingIterator<I, T> where I: Iterator<Item = T> + 'static, T: Clone + 'static

    This struct implements a global cache that maps an iterator-iterated pair to a cache of values. It is mostly
    intended for use with the prime function generator.

  .. rust:fn:: pub fn iter_cache::CachingIterator::new() -> CachingIterator<I, T> where I: Iterator<Item = T> + 'static, T: Clone + 'static

  .. rust:fn:: pub fn iter_cache::CachingIterator::default() -> CachingIterator<I, T> where I: Iterator<Item = T> + 'static, T: Clone + 'static

  .. rust:fn:: pub fn iter_cache::CachingIterator::next() -> Option<T> where T: Clone + 'static

.. literalinclude:: ../../../../rust/src/include/iter_cache.rs
   :language: rust
   :linenos:
