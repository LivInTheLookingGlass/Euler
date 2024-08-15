utils.rs
========

View source code :source:`rust/src/include/utils.rs`

.. rust:enum:: utils::Answer

    This enum can represent either a large, signed integer or a string.
    
    .. rust:fn:: pub fn utils::Answer::Int(n: i128) -> utils::Answer
    
    .. rust:fn:: pub fn utils::Answer::String(s: String) -> utils::Answer

.. rust:fn:: pub fn utils::read_data_file(name: &str) -> String

    Reads a file from ``/_data`` and returns its contents as a String.

.. rust:fn:: pub fn utils::read_answer(n: usize) -> Answer

    Reads the csv file of answers in ``/_data`` and returns a specified answer.


.. literalinclude:: ../../../../rust/src/include/utils.rs
   :language: rust
   :linenos:
