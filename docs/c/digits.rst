digits.h
========

.. c:namespace-push:: digits

.. c:type:: digit_counter

    Implements the :c:macro:`Iterator <c.iterator.IteratorHead>` API
    and yields successive decimal digits of a given number.

    .. c:member:: unsigned char (*iterator_function)(digit_counter *dc)

        The function to advance the iterator and return the next element.

    .. c:member:: bool exhausted : 1

        An indicator that tells you if the iterator is exhausted.
    
    .. c:member:: bool started : 1

        An indicator that tells you if the interator has moved at all.

    .. c:member:: bool phase : 1

        An indicator that flips every time the iterator moves.

    .. c:member:: unsigned char *digits

        This array holds the individual digits of a parsed integer.

    .. c:member:: size_t idx

        This represents the current position in :c:member:`digits`.

.. c:function:: digit_counter digits(uintmax_t n)

.. c:function:: void free_digit_counter(digit_counter dc)

.. c:namespace-pop::
