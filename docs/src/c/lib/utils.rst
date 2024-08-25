utils.h
=======

View source code :source:`c/src/include/utils.h`

Includes
--------

- :external:c:type:`inttypes`
- :external:c:type:`stdint`
- :external:c:type:`stdlib`
- :external:c:type:`string`
- :external:c:type:`stdio`
- :external:c:type:`direct` (if compiled for Windows)
- :external:c:type:`windows` (if compiled for Windows)
- :external:c:type:`libgen` (if not compiled for Windows)
- :external:c:type:`unistd` (if not compiled for Windows)

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

      .. c:member:: uint8_t int8

        Represents an 8-bit signed integer.

      .. c:member:: uint16_t int16

        Represents a 16-bit signed integer.

      .. c:member:: uint32_t int32

        Represents a 32-bit signed integer.

      .. c:member:: uint64_t int64

        Represents a 64-bit signed integer.

      .. c:member:: uint8_t uint8

        Represents an 8-bit unsigned integer.

      .. c:member:: uint16_t uint16

        Represents a 16-bit unsigned integer.

      .. c:member:: uint32_t uint32

        Represents a 32-bit unsigned integer.

      .. c:member:: uint64_t uint64

        Represents a 64-bit unsigned integer.

      .. c:member:: char *string

        Represents a string value.

   .. c:member:: uint16_t id

      Represents the problem ID.

   .. c:member:: AnswerType type

      Specifies the type of value stored in the ``value`` union. It is of type :c:enum:`AnswerType`.

.. c:enum:: AnswerType

   The `AnswerType` enum defines various types of values that can be stored in an `Answer`.

   .. c:enumerator:: ERRORT

      Represents an error state.

   .. c:enumerator:: INT8T

      Represents an 8-bit signed integer.

   .. c:enumerator:: INT16T

      Represents a 16-bit signed integer.

   .. c:enumerator:: INT32T

      Represents a 32-bit signed integer.

   .. c:enumerator:: INT64T

      Represents a 64-bit signed integer.

   .. c:enumerator:: UINT8T

      Represents an 8-bit unsigned integer.

   .. c:enumerator:: UINT16T

      Represents a 16-bit unsigned integer.

   .. c:enumerator:: UINT32T

      Represents a 32-bit unsigned integer.

   .. c:enumerator:: UINT64T

      Represents a 64-bit unsigned integer.

   .. c:enumerator:: STRINGT

      Represents a string value.

.. c:namespace-pop::

.. literalinclude:: ../../../../c/src/include/utils.h
   :language: C
   :linenos:

.. tags:: file-io
