primes.lua
=========

View source code :source:`lua/src/lib/primes.lua`

This module directly ports some of the logic found in Python's :external:py:obj:`primes`.

.. lua:function:: prime(stop)

    :return: An iterator over the prime numbers, optionally up to ``stop``
    :rtype: table

.. lua:function:: primes_factors(n)

    :return: An iterator over the prime factors of ``n``
    :rtype: table

.. literalinclude:: ../../../../lua/src/lib/primes.lua
   :language: Lua
   :linenos:
