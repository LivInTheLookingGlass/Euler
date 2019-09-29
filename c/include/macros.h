#ifndef _MACROS_H
#define _MACROS_H

#if (defined(_MSC_VER) && !defined(__clang__))
    #define CL_COMPILER 1
#else
    #define CL_COMPILER 0
#endif
#ifdef __clang__
    #define CLANG_COMPILER 1
#else
    #define CLANG_COMPILER 0
#endif
#if (defined(__GNUC__) && !defined(__clang__)) && !defined(__INTEL_COMPILER) && !defined(__PCC__)
    #define GCC_COMPILER 1
#else
    #define GCC_COMPILER 0
#endif
#ifdef __INTEL_COMPILER
    #define INTEL_COMPILER 1
#else
    #define INTEL_COMPILER 0
#endif
#define AMD_COMPILER 0
#ifdef __PCC__
    #define PCC_COMPILER 1
#else
    #define PCC_COMPILER 0
#endif
#define TCC_COMPILER (!CL_COMPILER && !CLANG_COMPILER && !GCC_COMPILER && !INTEL_COMPILER && !PCC_COMPILER)

#ifndef max
    #define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
    #define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define MAX_FACTORIAL_64 20
#define MAX_FACTORIAL_128 34
#define PCC_SQRT_ACCURACY 8

#endif
