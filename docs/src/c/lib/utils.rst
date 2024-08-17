utils.h
=======

View source code :source:`c/src/include/utils.h`

.. c:namespace-push:: utils
    
.. c:function:: char *get_data_file(const char *name)

    Return a character array containing the whole contents of a file found in _data.

.. c:function:: char *get_parent_directory(const char *name, const uint32_t levels)
    
.. c:function:: Answer get_answer(const uint16_t id)

    Return an :c:struct:`Answer` representing a given problem's solution.

.. c:struct:: Answer

   The Answer struct represents the solution to a Project Euler problems. It can hold different types of values and
   an identifier.

   .. c:union:: value

      .. c:member:: uint8_t INT8

        Represents an 8-bit signed integer.

      .. c:member:: uint16_t INT16

        Represents a 16-bit signed integer.

      .. c:member:: uint32_t INT32

        Represents a 32-bit signed integer.

      .. c:member:: uint64_t INT64

        Represents a 64-bit signed integer.

      .. c:member:: uint8_t UINT8

        Represents an 8-bit unsigned integer.

      .. c:member:: uint16_t UINT16

        Represents a 16-bit unsigned integer.

      .. c:member:: uint32_t UINT32

        Represents a 32-bit unsigned integer.

      .. c:member:: uint64_t UINT64

        Represents a 64-bit unsigned integer.

      .. c:member:: char *STR

        Represents a string value.

   .. c:member:: uint16_t id : 12

      A 12-bit integer field used to store the problem ID.

   .. c:member:: AnswerType type : 4

      A 4-bit field that specifies the type of value stored in the ``value`` union. It is of type :c:enum:`AnswerType`.

.. c:enum:: AnswerType

   The `AnswerType` enum defines various types of values that can be stored in an `Answer`.

   .. c:enumerator:: ERROR

      Represents an error state.

   .. c:enumerator:: INT8

      Represents an 8-bit signed integer.

   .. c:enumerator:: INT16

      Represents a 16-bit signed integer.

   .. c:enumerator:: INT32

      Represents a 32-bit signed integer.

   .. c:enumerator:: INT64

      Represents a 64-bit signed integer.

   .. c:enumerator:: UINT8

      Represents an 8-bit unsigned integer.

   .. c:enumerator:: UINT16

      Represents a 16-bit unsigned integer.

   .. c:enumerator:: UINT32

      Represents a 32-bit unsigned integer.

   .. c:enumerator:: UINT64

      Represents a 64-bit unsigned integer.

   .. c:enumerator:: STR

      Represents a string value.

.. c:namespace-pop::

.. literalinclude:: ../../../../c/src/include/utils.h
   :language: C
   :linenos:

.. tags:: file-io
