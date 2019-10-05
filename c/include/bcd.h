#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "macros.h"

#if !PCC_COMPILER
    #include <stdlib.h>
    #include <math.h>
#else
    #include "math.h"
#endif

typedef unsigned char packed_BCD_pair;
typedef struct {
    // a little-endian, arbitrary-precision, binary-coded decimal number
    packed_BCD_pair *digits;
    size_t bcd_digits;
    size_t decimal_digits;
    bool negative : 1;
    bool zero : 1;
} BCD_int;

void free_BCD_int(BCD_int x)    {
    free(x.digits);
    x.digits = NULL;
    x.bcd_digits = x.decimal_digits = x.negative = x.zero = 0;
}

BCD_int new_BCD_int(uintmax_t a, bool negative)   {
    BCD_int c;
    #if !PCC_COMPILER
        c.decimal_digits = ceil(log10(a + 1));
    #else
        c.decimal_digits = imprecise_log10(a + 1);
    #endif
    c.bcd_digits = (c.decimal_digits + 1) / 2;
    c.digits = (packed_BCD_pair *) malloc(sizeof(packed_BCD_pair) * c.bcd_digits);
    c.negative = negative;
    c.zero = !a;
    for (size_t i = 0; i < c.bcd_digits; i++)   {
        c.digits[i] = (((a % 100) / 10) << 4) | (a % 10);
        a /= 100;
    }
    return c;
}

BCD_int copy_BCD_int(BCD_int a) {
    BCD_int b = a;
    b.digits = (packed_BCD_pair *) malloc(sizeof(packed_BCD_pair) * b.bcd_digits);
    memcpy(b.digits, a.digits, b.bcd_digits);
    return b;
}

BCD_int BCD_from_bytes(const unsigned char *str, size_t chars, bool negative, bool little_endian)   {
    // converts a bytestring to a little-endian BCD int
    BCD_int c;
    if (!chars || str == NULL)  {
        c.zero = true;
        c.bcd_digits = c.decimal_digits = c.negative = 0;
        c.digits = NULL;
        return c;
    }
    size_t i;
    c.zero = false;
    c.negative = negative;
    c.digits = (packed_BCD_pair *) malloc(sizeof(packed_BCD_pair) * chars);
    if (little_endian)  {
        for (i = 0; i < chars; i++) {
            c.digits[i] = str[i];
        }
    }
    else    {
        size_t j;
        for (i = 0, j = chars - 1; i < chars; i++, j--) {
            c.digits[i] = str[j];
        }
    }
    for (i = chars - 1; i != -1; i--)   {
        if (c.digits[i] & 0xF0) {
            c.decimal_digits = i * 2 + 1;
            c.bcd_digits = i + 1;
            break;
        }
        if (c.digits[i] & 0x0F) {
            c.decimal_digits = i * 2;
            c.bcd_digits = i + 1;
            break;
        }
    }
    if (i == -1)    {
        c.zero = true;
        c.bcd_digits = c.decimal_digits = c.negative = 0;
        free(c.digits);
        c.digits = NULL;
    }
    return c;
}

BCD_int BCD_from_ascii(const char *str, size_t digits, bool negative)   {
    // packs an ASCII digit string into big-endian bytes, then runs through BCD_from_bytes()
    size_t length = (digits + 1) / 2, i, j;
    unsigned char *bytes = (unsigned char *) malloc(sizeof(unsigned char) * length);
    j = i = digits % 2;
    if (i)  {
        bytes[0] = str[0] - '0';
    }
    for (; i < length; i++, j += 2) {
        bytes[i] = ((str[j] - '0') << 4) | ((str[j + 1] - '0') & 0xF);
    }
    BCD_int ret = BCD_from_bytes(bytes, length, negative, false);
    free(bytes);
    return ret;
}

BCD_int sub_bcd(BCD_int x, BCD_int y);

BCD_int add_bcd(BCD_int x, BCD_int y)   {
    if (x.zero) {
        return copy_BCD_int(y);
    }
    if (y.zero) {
        return copy_BCD_int(x);
    }
    if (x.negative && !y.negative) {
        return sub_bcd(x, y);
    }
    if (y.negative && !x.negative) {
        return sub_bcd(y, x);
    }
    BCD_int z;
    size_t i, min_digits = min(x.bcd_digits, y.bcd_digits), max_digits = max(x.bcd_digits, y.bcd_digits);
    z.zero = false;
    z.negative = x.negative && y.negative;
    z.digits = (packed_BCD_pair *) malloc(sizeof(packed_BCD_pair) * (max_digits + 1));
    packed_BCD_pair a, b, c;
    bool overflow = false;
    for (i = 0; i < min_digits; i++) {
        a = x.digits[i];
        b = y.digits[i];
        if (!(overflow || a))   {
            c = b;
            overflow = false;
        }
        else if (!(overflow || b))  {
            c = a;
            overflow = false;
        }
        else    {
            b += overflow;  // incorporate overflow from last pair
            #if (!defined(NO_ASSEMBLY) && X86_COMPILER)
                // if on these architectures, there's assembly tricks to adjust BCD in-silicon
                #if CL_COMPILER
                    // CL compiler has a different syntax for inline assembly, does a lot less lifting
                    // note that the syntax here is: op [dest [, src]]
                    // brackets indicate a C symbol is referenced rather than a register
                    __asm   {
                        mov al, [a];         // move C symbol a to register al
                        add al, [b];         // add C symbol b to register al
                        daa;                 // have the CPU make sure register al contains valid, packed BCD digits
                        setc [overflow];     // set C symbol overflow to contain the carry bit, set by daa
                        mov [c], al;         // move register al to C symbol c
                    }
                #else
                    // this is the standard GCC/LLVM syntax for it
                    // note that the syntax here is: op [[src, ] dest]
                    // %\d indicates a C symbol is referenced, see the lookups at the end of code for which
                    __asm__(
                        "add %3, %%al;"   // add the register containing b to al
                        "daa;"            // have the CPU make sure register al contains valid, packed BCD digits
                        "setc %1;"        // set the register containing overflow to hold the carry bit, set by daa
                                          // this next section tells the compiler what to do after execution
                      : "=al" (c),        // store the contents of register al in symbol c
                        "=rl" (overflow)  // and a general register gets assigned to symbol overflow (referenced as %1)
                                          // then below tells the compiler what our inputs are
                      : "al" (a),         // symbol a should get dumped to register al
                        "rl" (b)          // and symbol b in a general register (referenced as %3)
                    );                       
                #endif
            #else
                // otherwise fall back to doing it in C
                c = a + b;                             // set c to be the result of (a + b) % 0x100
                if (a > 0x99 - b)   {                  // if c would overflow the decimal range
                    overflow = true;                   // set overflow to true
                    c += 0x60;                         // and add 0x60 to make a decimal digit
                }
                else    {
                    overflow = false;                  // overflow defaults to 0
                }
                if (((a & 0xF) + (b & 0xF)) > 9)    {  // if the lower nibble be bigger than 9
                    c += 0x06;                         // add 6 to make a decimal digit
                }
            #endif
            }
        z.digits[i] = c;
    }
    if (x.bcd_digits < y.bcd_digits)    {
        x = y;
    }
    for (; overflow && i < max_digits; i++) {  // while there's overflow and digits, continue adding
        a = x.digits[i] + overflow;
        if ((a & 0x0F) == 0x0A) {  // since all that's left is overflow, we don't need to check ranges
            a += 0x06;
        }
        if ((overflow = ((a & 0xF0) == 0xA0)))  {
            a += 0x60;
        }
        z.digits[i] = a;
    }
    for (; i < max_digits; i++) {  // if there's no more overflow, but still digits left, copy directly
        z.digits[i] = x.digits[i];
    }
    z.digits[max_digits] = overflow;
    z.bcd_digits = max_digits + overflow;
    if (z.digits[max_digits])   {
        z.decimal_digits = max_digits * 2 + 1;
    }
    else if (z.digits[max_digits - 1] & 0xF0)   {
        z.decimal_digits = max_digits * 2;
    }
    else    {
        z.decimal_digits = max_digits * 2 - 1;
    }
    return z;
}

BCD_int sub_bcd(BCD_int x, BCD_int y)   {
    if (x.zero) {
        return copy_BCD_int(y);
    }
    if (y.zero) {
        return copy_BCD_int(x);
    }
    if (x.negative == y.negative)   {
        return add_bcd(x, y);
    }
    // TODO
}

BCD_int bcd_int_divide_pwr_10(BCD_int a, uintmax_t tens)    {
    if (a.zero) {
        return copy_BCD_int(a);
    }
    BCD_int ret;
    ret.negative = a.negative;
    ret.zero = false;
    ret.decimal_digits = a.decimal_digits - tens;
    if (tens % 2 == 0)  {
        ret.bcd_digits = a.bcd_digits - tens / 2;
        ret.digits = (packed_BCD_pair *) malloc(sizeof(packed_BCD_pair) * ret.bcd_digits);
        memcpy(ret.digits, a.digits + tens / 2, ret.bcd_digits);
    }
    else    {
        // TODO
    }
    return ret;
}

void print_bcd(BCD_int x)   {
    if (x.zero) {
        printf("0");
        return;
    }
    if (x.negative) {
        printf("-");
    }
    size_t i = x.bcd_digits - 1;
    printf("%x", x.digits[i]);
    if (i--)    {
        for (; i != -1; i--)  {
            printf("%02x", x.digits[i]);
        }
    }
}
