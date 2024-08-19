math.rs
=======

View source code :source:`rust/src/include/math.rs`

Includes
--------

- `num_traits::NumAssign <https://docs.rs/num-traits/latest/num_traits/trait.NumAssign.html>`_
- `num_traits::one <https://docs.rs/num-traits/latest/num_traits/identities/fn.one.html>`_
- :rsref:`std::cmp::PartialOrd <std/cmp/trait.PartialOrd>`
- :rsref:`std::cmp::PartialOrd <std/mem/fn.size_of>`

.. rust:fn:: pub fn math::factorial<I>(n: u8) -> I where I: NumAssign + From<u8>

  Returns the factorial of a given number. Note that it only accepts a ``u8`` because
  any number that requires a larger type is *guaranteed* to overflow.

.. rust:fn:: pub fn n_choose_r<I>(n: usize, r: usize) -> I where I: Copy + From<u8> + From<u64> + NumAssign + PartialOrd

  Returns the number of ways to choose r items from a set of n.

.. literalinclude:: ../../../../rust/src/include/math.rs
   :language: rust
   :linenos:
