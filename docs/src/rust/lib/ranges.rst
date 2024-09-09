ranges.rs
=======

View source code :source:`rust/src/include/ranges.rs`

Includes
--------

- :external:rust:trait:`num_traits::NumAssign`
- :external:rust:fn:`num_traits::one`
- :external:rust:fn:`num_traits::zero`
- :external:rust:trait:`std::cmp::PartialOrd`
- :external:rust:trait:`std::marker::Copy`

.. rust:fn:: pub fn ranges::range_entry3<I>(start: I, idx: I, step: I) -> I where I: NumAssign

  Returns the factorial of a given number. Note that it only accepts a ``u8`` because
  any number that requires a larger type is *guaranteed* to overflow.

.. rust:fn:: pub fn ranges::range_entry4<I>(start: I, stop: I, idx: I, step: I) -> Option<I> where I: NumAssign + PartialOrd + Copy

  Returns the number of ways to choose r items from a set of n.

.. literalinclude:: ../../../../rust/src/include/ranges.rs
   :language: rust
   :linenos:
