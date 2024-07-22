macros.h
========

.. cpp:namespace-push:: macros

.. cpp:macro:: CL_COMPILER
               CLANG_COMPILER
               GCC_COMPILER
               INTEL_COMPILER
               AMD_COMPILER

    These macros detect which compiler the program is being made with. They will be 1
    if it is that compiler, and 0 otherwise.

    .. warning::

        This suite is not able to detect the difference between ``clang`` and ``aocc``
        without assistance. Please define :cpp:macro:`AMD_COMPILER` manually if on
        ``clang`` or ``aocc``.

.. cpp:macro:: X64_COMPILER
               X86_COMPILER
               ARM_COMPILER
               ARM_THUMB

    These macros attempt to detect the architecture the program is being compiled for.

.. cpp:macro:: likely(x)
               unlikely(x)

    These macros implement the ``likely()`` and ``unlikely()`` flags, as in the Linux kernel to
    assist in branch prediction. On ``tcc`` and ``cl`` it has no effect.

.. cpp:macro:: MAX_FACTORIAL_64
               MAX_FACTORIAL_128

.. cpp:macro:: PCC_SQRT_ACCURACY

.. cpp:macro:: MAX_POW_10_16
               POW_OF_MAX_POW_10_16

.. cpp:macro:: MAX_POW_10_32
               POW_OF_MAX_POW_10_32

.. cpp:macro:: MAX_POW_10_64
               POW_OF_MAX_POW_10_64

.. cpp:macro:: MAX_POW_10_128
               POW_OF_MAX_POW_10_128

.. cpp:namespace-pop::
