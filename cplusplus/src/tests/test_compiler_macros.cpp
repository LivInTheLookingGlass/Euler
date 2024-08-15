#include <stdio.h>
#include "../include/macros.h"

int main(int argc, char const *argv[]) {
    printf(
        "%d %d %d %d %d %d",
        CL_COMPILER,
        CLANG_COMPILER,
        GCC_COMPILER,
        X86_COMPILER,
        X64_COMPILER,
        ARM_COMPILER
    );
    return 0;
}
