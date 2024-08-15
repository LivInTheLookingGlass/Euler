macros.h
========

View source code :source:`c/src/include/macros.h`

.. c:namespace-push:: macros

.. c:macro:: CL_COMPILER
             CLANG_COMPILER
             GCC_COMPILER
             PCC_COMPILER
             TCC_COMPILER

    These macros detect which compiler the program is being made with. They will be 1
    if it is that compiler, and 0 otherwise.

.. c:macro:: X64_COMPILER
             X86_COMPILER
             ARM_COMPILER
             ARM_THUMB

    These macros attempt to detect the architecture the program is being compiled for.

.. c:macro:: max(a, b)
             min(a, b)

    If these were not already defined, this header makes them.

.. c:macro:: swap(x, y)

    Swap the names of two variables of the same type.

.. c:macro:: likely(x)
             unlikely(x)

    These macros implement the ``likely()`` and ``unlikely()`` flags, as in the
    `Linux kernel <https://stackoverflow.com/q/109710>`__ to assist in branch prediction. On ``tcc`` and ``cl`` it has
    no effect.

.. c:macro:: MAX_FACTORIAL_64
             MAX_FACTORIAL_128

.. c:macro:: PCC_SQRT_ACCURACY

.. c:macro:: MAX_POW_10_16
             POW_OF_MAX_POW_10_16

.. c:macro:: MAX_POW_10_32
             POW_OF_MAX_POW_10_32

.. c:macro:: MAX_POW_10_64
             POW_OF_MAX_POW_10_64

.. c:macro:: MAX_POW_10_128
             POW_OF_MAX_POW_10_128

.. c:namespace-pop::

.. literalinclude:: ../../../../c/src/include/macros.h
   :language: C
   :linenos: