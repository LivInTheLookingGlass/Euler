bcd.h
=====

View source code :source:`c/src/include/bcd.h`

Includes
--------

- `"macros.h" <./macros.html>`__
- `"math.h" <./math.html>`__ (if compiled on PCC)
- :external:c:type:`stdint`
- :external:c:type:`stdbool`
- :external:c:type:`stdio`
- :external:c:type:`string`
- :external:c:type:`stdlib` (if not compiled on PCC)
- :external:c:type:`math` (if not compiled on PCC)

This library implements a `Binary Coded Decimal <https://en.wikipedia.org/wiki/Binary-coded_decimal>`__ object in C. Mostly
this is done to prove that I could, but also because it allows for incredibly easy printing of arbitrary-sized integers.
It was also a good exercise in x86 assembly, as several portions are accellerated by handcrafted assembly.

.. c:namespace-push:: bcd

.. c:type:: uint8_t packed_BCD_pair

    This is an alias to distinguish BCD digit-pairs from normal characters.

.. c:type:: BCD_int

    .. c:member:: packed_BCD_pair *digits

        This array holds the digit-pairs that encode the number. Because of this, you must use :c:func:`~c.bcd.free_bcd` to destroy
        these objects without leaking memory.

    .. c:member:: size_t bcd_digits

        This field indicates the size of the array. It DOES NOT match the number of decimal digits.

    .. c:member:: size_t decimal_digits

        This field indicates the number of decimal digits encoded. It should be within 1 of :c:expr:`2*bcd_digits`.

    .. c:member:: bool negative : 1

        Since digits are encoded by absolute value, this field tells you if the number is negative.

    .. c:member:: bool zero : 1

        Shortcut value to determine if the encoded integer is 0.

.. c:function:: void free_BCD_int(BCD_int x)

.. c:function:: BCD_int new_BCD_int(uintmax_t a, bool negative)

.. c:function:: BCD_int BCD_from_bytes(const uint8_t *str, size_t chars, bool negative, bool little_endian)

    Takes in an arbitrary-sized encoded integer (like in Python's :external:py:meth:`int.from_bytes`) to a
    :c:type:`BCD_int`.

.. c:function:: BCD_int BCD_from_ascii(const char *str, size_t digits, bool negative)

    From an ASCII-encoded integer to a :c:func:`~c.bcd.BCD_int`.

.. c:function:: BCD_int add_bcd(BCD_int x, BCD_int y)

    Returns :c:expr:`x + y`.

.. c:function:: BCD_int sub_bcd(BCD_int x, BCD_int y)

    Returns :c:expr:`x - y`.

.. c:function:: BCD_int mul_bcd_cuint(BCD_int x, uintmax_t y)

    Returns :c:expr:`x * y`, handling type conversion for you.

.. c:function:: BCD_int pow_cuint_cuint(uintmax_t x, uintmax_t y)

    Returns :c:expr:`pow(x, y)`, handling type conversion for you.

.. c:function:: BCD_int mul_bcd(BCD_int x, BCD_int y)

    Returns :c:expr:`x * y`.

.. c:function:: BCD_int pow_bcd(BCD_int x, BCD_int y)

    Returns :c:expr:`pow(x, y)`.

.. c:function:: BCD_int mul_bcd_pow_10(BCD_int x, uintmax_t tens)
                BCD_int shift_bcd_left(BCD_int x, uintmax_t tens)

    Returns :c:expr:`x * pow(10, tens)`.

.. c:function:: BCD_int div_bcd_pow_10(BCD_int a, uintmax_t tens)
                BCD_int shift_bcd_right(BCD_int a, uintmax_t tens)

    Returns :c:expr:`x / pow(10, tens)`.

.. c:function:: void iadd_bcd(BCD_int *const x, const BCD_int y)

    Transforms :c:expr:`x` to be :c:expr:`x + y` without needing to make a new assignment.

.. c:function:: signed char cmp_bcd(BCD_int x, BCD_int y)

    Returns 1 if :c:expr:`x > y`, -1 if :c:expr:`y > x`, and otherwise 0.

.. c:function:: void print_bcd(BCD_int x)
                void print_bcd_ln(BCD_int x)

    Writes a :c:type:`BCD_int` to `stdout`, and optionally adds a newline.

.. c:function:: uintmax_t bcd_to_unsigned(BCD_int a)

    Converts a :c:type:`BCD_int` to an uint32_teger.

    .. warning::

        This method DOES NOT guard against overflow.

.. c:function:: intmax_t bcd_to_signed(BCD_int a)

    Converts a :c:type:`BCD_int` to a signed integer.

    .. warning::

        This method DOES NOT guard against overflow.

.. c:function:: uint16_t mul_dig_pair(packed_BCD_pair ab, packed_BCD_pair cd)

    Convenience method to multiply a digit pair.

.. c:namespace-pop::

.. literalinclude:: ../../../../c/src/include/bcd.h
   :language: C
   :linenos:

.. tags:: large-numbers
