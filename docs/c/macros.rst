macros.h
========

.. c:namespace-push:: macros

.. c:macro:: CL_COMPILER
             CLANG_COMPILER
             GCC_COMPILER
             INTEL_COMPILER
             AMD_COMPILER
             PCC_COMPILER
             TCC_COMPILER

    These macros detect which compiler the program is being made with. They will be 1
    if it is that compiler, and 0 otherwise.

    .. warning::

        This suite is not able to detect the difference between ``clang`` and ``aocc``
        without assistance. Please define :c:macro:`AMD_COMPILER` manually if on
        ``clang`` or ``aocc``.

.. c:macro:: X64_COMPILER
             X86_COMPILER
             ARM_COMPILER
             ARM_THUMB

    These macros attempt to detect the architecture the program is being compiled for.

.. c:macro:: static

    .. note::

        This macro only exists on ``pcc`` because it does not allow reproducible builds
        with static variables.

.. c:macro:: max(a, b)
             min(a, b)

    If these were not already defined, this header makes them

.. c:macro:: likely(x)
             unlikely(x)

    These macros implement the ``likely()`` and ``unlikely()`` flags, as in the Linux kernel to
    assist in branch prediction. On ``tcc`` and ``cl`` it has no effect.

.. c:macro:: MAX_FACTORIAL_64 20
             MAX_FACTORIAL_128 34

.. c:macro:: PCC_SQRT_ACCURACY 8

.. c:macro:: MAX_POW_10_16 10000U
             POW_OF_MAX_POW_10_16 4

.. c:macro:: MAX_POW_10_32 1000000000UL
             POW_OF_MAX_POW_10_32 9

.. c:macro:: MAX_POW_10_64 10000000000000000000ULL
             POW_OF_MAX_POW_10_64 19

.. c:macro:: MAX_POW_10_128 ((uintmax_t) MAX_POW_10_64 * (uintmax_t) MAX_POW_10_64)
             POW_OF_MAX_POW_10_128 38

.. c:namespace-pop::
