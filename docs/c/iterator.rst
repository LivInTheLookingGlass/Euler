iterator.h
==========

.. c:namespace-push:: iterator

.. c:macro:: IteratorHead(return_type, struct_type)

    This macro allows a struct to implement my Iterator API, which is
    heavily inspired by Python. You should put it at the top of a struct
    like so:

    .. code-block:: C
        
        struct counter {
            IteratorHead(uintmax_t, counter);
            uintmax_t idx;
            uintmax_t stop;
            intmax_t step;
        };

    It imparts the following internal properties.

    .. c:member:: return_type (*iterator_function)(struct_type *it)

        The function to advance the iterator and return the next element.

    .. c:member:: bool exhausted : 1

        An indicator that tells you if the iterator is exhausted.

    .. c:member:: bool started : 1

        An indicator that tells you if the interator has moved at all.

    .. c:member:: bool phase : 1

        An indicator that flips every time the iterator moves.

.. c:macro:: IteratotionHead(it)

    This macro implements the base functionality of all :c:macro:`Iterator <IteratorHead>` functions.
    It must be at the top of all iteration functions, with the iterator passed
    as an argument.

.. c:macro:: IteratorInitHead(it, advance)

    This macro implements the library-managed portion of iterator construction.
    The first argument should be the uninitialized iterator, and the second
    argument should be a pointer to its iteration function.

.. c:macro:: next(state)
.. c:macro:: next_p(state)

    These macros implement the iteration operation. The only difference between
    them is that :c:macro:`next` takes in a struct and
    :c:macro:`next_p` takes a pointer. Both yield `return_type`.

.. c:type:: counter

    This is an example implementation of the :c:macro:`Iterator <IteratorHead>`
    API used in this project. You can construct it using any of the factory
    functions found below, and it is generally used much like Python's
    :py:ref:`range` object.

    .. c:member:: uintmax_t (*iterator_function)(counter *it)

    .. c:member:: bool exhausted : 1

    .. c:member:: bool started : 1

    .. c:member:: bool phase : 1

    .. c:member:: uintmax_t idx

    .. c:member:: uintmax_t stop

    .. c:member:: intmax_t step

    .. c:function:: uintmax_t iterate_counter(counter *i)

    .. c:function:: counter counter3(uintmax_t start, uintmax_t stop, intmax_t step)

    .. c:function:: counter counter2(uintmax_t start, uintmax_t stop)

    .. c:function:: counter counter1(uintmax_t stop)

.. c:namespace-pop::
