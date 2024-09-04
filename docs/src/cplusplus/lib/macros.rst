macros.hpp
==========

View source code :source:`cplusplus/src/include/macros.hpp`

.. c:namespace-push:: cppmacros

.. c:macro:: CL_COMPILER
             CLANG_COMPILER
             GCC_COMPILER

    These macros detect which compiler the program is being made with. They will be 1
    if it is that compiler, and 0 otherwise.

.. c:macro:: X64_COMPILER
             X86_COMPILER
             ARM_COMPILER
             ARM_THUMB

    These macros attempt to detect the architecture the program is being compiled for.

.. c:macro:: likely(x)
             unlikely(x)

    These macros implement the ``likely()`` and ``unlikely()`` flags, as in the
    `Linux kernel <https://stackoverflow.com/q/109710>`__ to assist in branch prediction. On ``cl`` it has no effect.

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

.. c:macro:: PROGRAM_TAIL(prob)

    Conditionally generates a ``main()`` function if running under the Python test runner or compiling as a standalone
    program. Takes in as an argument the name of the function which implements this Project Euler solution.

.. c:namespace-pop::

.. literalinclude:: ../../../../cplusplus/src/include/macros.hpp
   :language: C++
   :linenos:
