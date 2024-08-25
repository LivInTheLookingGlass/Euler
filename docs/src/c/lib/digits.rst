digits.h
========

View source code :source:`c/src/include/digits.h`

Includes
--------

- `"macros.h" <./macros.html>`__ (implicitly, via iterator.h)
- `"iterator.h" <./iterator.html>`__
- `"math.h" <./math.html>`__ (if compiled on PCC)
- :external:c:type:`stdint`
- :external:c:type:`stdbool` (implicitly, via iterator.h)
- :external:c:type:`stdlib` (if not compiled on PCC)
- :external:c:type:`math` (if not compiled on PCC)

.. c:namespace-push:: digits

.. c:type:: digit_counter

    Implements the :c:macro:`Iterator <c.iterator.IteratorHead>` API
    and yields successive decimal digits of a given number.

    .. c:member:: uint8_t (*iterator_function)(digit_counter *dc)

        The function to advance the iterator and return the next element.

    .. c:member:: bool exhausted : 1

        An indicator that tells you if the iterator is exhausted.
    
    .. c:member:: bool started : 1

        An indicator that tells you if the interator has moved at all.

    .. c:member:: bool phase : 1

        An indicator that flips every time the iterator moves.

    .. c:member:: uint8_t *digits

        This array holds the individual digits of a parsed integer.

    .. c:member:: size_t idx

        This represents the current position in :c:member:`digits`.

.. c:function:: digit_counter digits(uintmax_t n)

.. c:function:: void free_digit_counter(digit_counter dc)

.. c:namespace-pop::

.. literalinclude:: ../../../../c/src/include/digits.h
   :language: C
   :linenos:

.. tags:: c-iterator
