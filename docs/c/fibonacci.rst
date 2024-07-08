fibonacci.h
========

.. c:namespace-push:: fibonacci

.. c:type:: fibonacci

    Implements the :c:macro:`Iterator <c.iterator.IteratorHead>` API
    and yields successive Fibonacci numbers.

    .. c:member:: uintmax_t (*iterator_function)(*digit_counter)

        The function to advance the iterator and return the next element.

    .. c:member:: bool exhausted : 1

        An indicator that tells you if the iterator is exhausted.
    
    .. c:member:: bool started : 1

        An indicator that tells you if the interator has moved at all.

    .. c:member:: bool phase : 1

        An indicator that flips every time the iterator moves.

    .. c:member:: uintmax_t a
                  uintmax_t b

    .. c:member:: uintmax_t limit

        This represents the largest number the iterator is allowed to yield.

    .. c:function:: fibonacci fibonacci1(uintmax_t limit)

    .. c:function:: fibonacci fibonacci0()

.. c:namespace-pop::
