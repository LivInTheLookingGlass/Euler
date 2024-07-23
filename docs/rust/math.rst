math.rs
=======

View source code `here on GitHub! <https://github.com/LivInTheLookingGlass/Euler/blob/master/rust/src/math.rs>`_

.. rust:fn:: math::factorial<I: NumAssign + From<u8>>(n: u8) -> I

  Returns the factorial of a given number. Note that it only accepts a ``u8`` because
  any number that requires a larger type is *guaranteed* to overflow.

.. rust:fn:: math::n_choose_r<I: NumAssign + PartialOrd>(n: u64, r: u64) -> I

  Returns the number of ways to choose r items from a set of n.

.. literalinclude:: ../../rust/src/math.rs
   :language: rust
   :linenos:
