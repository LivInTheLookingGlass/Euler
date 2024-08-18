utils.hpp
=========

View source code :source:`cplusplus/src/include/utils.hpp`

.. cpp:namespace-push:: utils
    
.. cpp:function:: std::string get_data_file(const std::string name)

    Return a character array containing the whole contents of a file found in _data.

.. cpp:function:: std::string get_parent_directory(const std::string &path, uint32_t levels)
    
.. cpp:function:: Answer get_answer(const uint16_t id)

    Return an :cpp:struct:`Answer` representing a given problem's solution.

.. cpp:struct:: Answer

   The Answer object represents the solution to a Project Euler problems. It can hold different types of values and
   an identifier.

   .. cpp:union:: value

      .. cpp:member:: uint8_t int8

        Represents an 8-bit signed integer.

      .. cpp:member:: uint16_t int16

        Represents a 16-bit signed integer.

      .. cpp:member:: uint32_t int32

        Represents a 32-bit signed integer.

      .. cpp:member:: uint64_t int64

        Represents a 64-bit signed integer.

      .. cpp:member:: uint8_t uint8

        Represents an 8-bit unsigned integer.

      .. cpp:member:: uint16_t uint16

        Represents a 16-bit unsigned integer.

      .. cpp:member:: uint32_t uint32

        Represents a 32-bit unsigned integer.

      .. cpp:member:: uint64_t uint64

        Represents a 64-bit unsigned integer.

      .. cpp:member:: char *string

        Represents a c-string value.

   .. cpp:member:: uint16_t id

      Represents the problem ID.

   .. cpp:member:: AnswerType type

      Specifies the type of value stored in the ``value`` union. It is of type :cpp:enum:`AnswerType`.

.. cpp:enum-struct:: AnswerType

   The `AnswerType` enum defines various types of values that can be stored in an `Answer`.

   .. cpp:enumerator:: ERROR

      Represents an error state.

   .. cpp:enumerator:: INT8

      Represents an 8-bit signed integer.

   .. cpp:enumerator:: INT16

      Represents a 16-bit signed integer.

   .. cpp:enumerator:: INT32

      Represents a 32-bit signed integer.

   .. cpp:enumerator:: INT64

      Represents a 64-bit signed integer.

   .. cpp:enumerator:: UINT8

      Represents an 8-bit unsigned integer.

   .. cpp:enumerator:: UINT16

      Represents a 16-bit unsigned integer.

   .. cpp:enumerator:: UINT32

      Represents a 32-bit unsigned integer.

   .. cpp:enumerator:: UINT64

      Represents a 64-bit unsigned integer.

   .. cpp:enumerator:: STR

      Represents a c-string value.

.. cpp:namespace-pop::

.. literalinclude:: ../../../../cplusplus/src/include/utils.hpp
   :language: C++
   :linenos:

.. tags:: file-io
