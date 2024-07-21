primes.h
========

.. c:namespace-push:: primes

.. c:type:: prime_counter

    Implements the :c:macro:`Iterator <c.iterator.IteratorHead>` API
    and yields successive prime numbers.

    .. c:member:: uintmax_t (*iterator_function)(prime_counter *pc)

        The function to advance the iterator and return the next element.

    .. c:member:: bool exhausted : 1

        An indicator that tells you if the iterator is exhausted.
    
    .. c:member:: bool started : 1

        An indicator that tells you if the interator has moved at all.

    .. c:member:: bool phase : 1

        An indicator that flips every time the iterator moves

    .. c:member:: size_t idx

        The current position of the counter.

    .. c:member:: uintmax_t stop

        The point where the counter is exhausted.

    .. c:member:: prime_sieve *ps

    .. c:function:: prime_counter prime_counter1(uintmax_t stop)
                    prime_counter prime_counter0()

    .. c:function:: void free_prime_counter(prime_counter pc)

.. c:type:: prime_sieve

    An :c:macro:`Iterator <c.iterator.IteratorHead>` that implements a modified sieve of eratosthenes

    .. c:member:: uintmax_t (*iterator_function)(prime_sieve *ps)

        The function to advance the iterator and return the next element.

    .. c:member:: bool exhausted : 1

        An indicator that tells you if the iterator is exhausted.
    
    .. c:member:: bool started : 1

        An indicator that tells you if the iterator has moved at all.

    .. c:member:: bool phase : 1

        An indicator that flips every time the iterator moves.

    .. c:member:: uintmax_t *sieve

        The sieve state used to generate new primes.

    .. c:member:: size_t sieve_len

        The length of the sieve state (divided by 2).

    .. c:member:: uintmax_t prime

        The current reference prime.

    .. c:member:: uintmax_t prime_squared

        The reference prime squared.

    .. c:member:: uintmax_t candidate

        The current candidate prime number.

    .. c:member:: prime_counter source

        The source of new reference prime numbers.

    .. c:function:: prime_sieve prime_sieve0()

    .. c:function:: void free_prime_sieve(prime_sieve ps)

.. c:type:: prime_factor_counter

    Implements the :c:macro:`Iterator <c.iterator.IteratorHead>` API
    and yields successive prime factors.

    .. c:member:: uintmax_t (*iterator_function)(prime_factor_counter *pfc)

        The function to advance the iterator and return the next element.

    .. c:member:: bool exhausted : 1

        An indicator that tells you if the iterator is exhausted.
    
    .. c:member:: bool started : 1

        An indicator that tells you if the interator has moved at all.

    .. c:member:: bool phase : 1

        An indicator that flips every time the iterator moves.

    .. c:member:: uintmax_t target

        The number you are trying to factorize.

    .. c:member:: uintmax_t current

        The current candidate prime factor.

    .. c:member:: prime_counter pc

        The source of new prime numbers

.. c:function:: prime_factor_counter prime_factors(uintmax_t n)

.. c:macro:: free_prime_factor_counter(pfc)

.. c:function:: uintmax_t is_composite(uintmax_t n)

    Tells you if a number is composite, and if so, its smallest prime factor.

.. c:function:: bool is_prime(uintmax_t n)

    Tests if a number is prime.

.. c:namespace-pop::
