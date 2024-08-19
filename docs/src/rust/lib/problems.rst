problems.rs
===========

View source code :source:`rust/src/include/problems.rs`

Includes
--------

- `seq_macro::seq <https://docs.rs/seq-macro/latest/seq_macro/macro.seq.html>`_

.. rust:fn:: pub fn get_problem(n: usize) -> Option<(usize, fn() -> utils::Answer, bool)>

  Returns a reference to a specific problem. This reference includes its id, the function, and a boolean indicating
  whether the function should return in over one minute runtime.

.. rust:fn:: pub fn generate_supported_problems(include_slow: bool) -> Vec<usize>

  Generates a vector of the supported problem IDs, optionally excluding slow problems.

.. literalinclude:: ../../../../rust/src/include/problems.rs
   :language: rust
   :linenos:
