#pragma once

// compiler info section

#if (defined(_MSC_VER) && !defined(__clang__))
    #define CL_COMPILER 1
#else
    #define CL_COMPILER 0
#endif
#if defined(__clang__)
    #define CLANG_COMPILER 1
#else
    #define CLANG_COMPILER 0
#endif
#if (defined(__GNUC__) && !defined(__clang__)) && !defined(__PCC__)
    #define GCC_COMPILER 1
#else
    #define GCC_COMPILER 0
#endif
#ifdef __PCC__
    #define PCC_COMPILER 1
#else
    #define PCC_COMPILER 0
#endif
#ifdef __EMSCRIPTEN__
    #define EMCC_COMPILER 1
#else
    #define EMCC_COMPILER 0
#endif
#define TCC_COMPILER (!(CL_COMPILER || CLANG_COMPILER || GCC_COMPILER || PCC_COMPILER || EMCC_COMPILER))

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
#if (defined(__arm__) || defined(__aarch64__) || defined(__thumb__) || defined(_M_ARM) || defined(_M_ARMT) || defined(__ARM_ARCH))
    #define ARM_COMPILER 1
#else
    #define ARM_COMPILER 0
#endif
#if (ARM_COMPILER && (defined(__thumb__) || defined(_M_ARMT)))
    #define ARM_THUMB 1
#else
    #define ARM_THUMB 0
#endif
#if (defined(__wasm__) || defined(__wasm32__) || defined(__wasm64__))
    #define WASM_COMPILER 1
    #include <emscripten.h>
#else
    #define WASM_COMPILER 0
    #define EMSCRIPTEN_KEEPALIVE
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

#ifndef swap
    #define swap(x, y) do { typeof(x) SWAP = x; x = y; y = SWAP; } while (0)
#endif

#if !(CL_COMPILER || TCC_COMPILER)
    #define likely(x)   __builtin_expect(!!(x), 1)
    #define unlikely(x) __builtin_expect(!!(x), 0)
#else
    #define likely(x) x
    #define unlikely(x) x
#endif

// constants section

#define MAX_FACTORIAL_64 20
#define MAX_FACTORIAL_128 34
#define PCC_SQRT_ACCURACY 8
#define MAX_POW_10_16 10000U
#define POW_OF_MAX_POW_10_16 4
#define MAX_POW_10_32 1000000000UL
#define POW_OF_MAX_POW_10_32 9
#define MAX_POW_10_64 10000000000000000000ULL
#define POW_OF_MAX_POW_10_64 19
#define MAX_POW_10_128 ((uintmax_t) MAX_POW_10_64 * (uintmax_t) MAX_POW_10_64)
#define POW_OF_MAX_POW_10_128 38

#ifndef UNITY_END
#define PROGRAM_TAIL(type, prob) \
int main(int argc, char const *argv[]) { \
    printf(type "\n", prob()); \
    return 0; \
}
#else
#define PROGRAM_TAIL(type, prob)
#endif
