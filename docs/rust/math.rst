math.rs
=======

View source code :source:`rust/src/include/math.rs`

.. rust:fn:: math::factorial<I>(n: u8) -> I where I: NumAssign + From<u8>

  Returns the factorial of a given number. Note that it only accepts a ``u8`` because
  any number that requires a larger type is *guaranteed* to overflow.

.. rust:fn:: n_choose_r<I>(n: usize, r: usize) -> I where I: Copy + From<u8> + From<u64> + NumAssign + PartialOrd

  Returns the number of ways to choose r items from a set of n.

.. literalinclude:: ../../rust/src/include/math.rs
   :language: rust
   :linenos:
