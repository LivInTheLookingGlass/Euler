#ifndef _MACROS_H
#define _MACROS_H

// compiler info section

#if (defined(_MSC_VER) && !defined(__clang__))
    #define CL_COMPILER 1
#else
    #define CL_COMPILER 0
#endif
#if (defined(__clang__) && !defined(AMD_COMPILER))
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
#ifndef AMD_COMPILER
    #if CLANG_COMPILER
        #warning This suite can't detect the difference between clang and aocc. If this is aocc, you need to add -DAMD_COMPILER=1
    #endif
    #define AMD_COMPILER 0
#endif
#ifdef __PCC__
    #define PCC_COMPILER 1
#else
    #define PCC_COMPILER 0
#endif
#define TCC_COMPILER (!(AMD_COMPILER || CL_COMPILER || CLANG_COMPILER || GCC_COMPILER || INTEL_COMPILER || PCC_COMPILER))

#if (defined(_M_X64) || defined(_M_AMD64) || defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64))
    #define X64_COMPILER 1
#else
    #define X64_COMPILER 0
#endif
#if (!X64_COMPILER && (defined(_M_X86) || defined(_M_IX86) || defined(i386) || defined(__i386) || defined(__i386__) || defined(_X86_)))
    #define X86_COMPILER 1
#else
    #define X86_COMPILER 0
#endif
#if (defined(__arm__) || defined(__thumb__) || defined(_M_ARM) || defined(_M_ARMT))
    #define ARM_COMPILER 1
#else
    #define ARM_COMPILER 0
#endif
#if (ARM_COMPILER && (defined(__thumb__) || defined(_M_ARMT)))
    #define ARM_THUMB 1
#else
    #define ARM_THUMB 0
#endif

// compiler workaround section

#if PCC_COMPILER
    #warning static is being redefined to '' because you are on PCC. \
    This is happening because PCC does not allow reproducible builds with the static keyword used globally. \
    Make sure this does not have side effects, or undefine/redefine static per-usage.
    #define static
#endif

// helper macro function section

#ifndef max
    #define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
    #define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

// constants section

#define MAX_FACTORIAL_64 20
#define MAX_FACTORIAL_128 34
#define PCC_SQRT_ACCURACY 8

#endif
