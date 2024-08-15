#include "../include/macros.h"
// this file should trigger compilation errors on non-x86 targets

int main(int argc, char const *argv[]) {
    #if CL_COMPILER
        __asm {
            aaa;
        }
    #else
        __asm__ (
            "aaa;"
        );
    #endif
}
