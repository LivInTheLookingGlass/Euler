#pragma once
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

typedef uint8_t packed_BCD_pair;
typedef struct {
    // a little-endian, arbitrary-precision, binary-coded decimal number
    packed_BCD_pair *digits;
    size_t bcd_digits;
    size_t decimal_digits;
    bool negative : 1;
    bool zero : 1;
    bool even : 1;
    bool constant : 1;
} BCD_int;


const BCD_int BCD_two = {
    .digits = (packed_BCD_pair[]) {2},
    .bcd_digits = 1,
    .decimal_digits = 1,
    .even = true,
    .constant = true
};  // note that non-specified values are initialized to NULL or 0


const BCD_int BCD_one = {
    .digits = (packed_BCD_pair[]) {1},
    .bcd_digits = 1,
    .decimal_digits = 1,
    .constant = true
};  // note that non-specified values are initialized to NULL or 0


const BCD_int BCD_zero = {
    .zero = true,
    .even = true,
    .constant = true
};  // note that non-specified values are initialized to NULL or 0

void free_BCD_int(BCD_int x);
inline void free_BCD_int(BCD_int x) {
    if (!x.constant) {
        free(x.digits);
        x.digits = NULL;
        x.bcd_digits = x.decimal_digits = x.negative = x.zero = 0;
    }
}

BCD_int new_BCD_int(uintmax_t a, bool negative) {
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
    for (size_t i = 0; i < c.bcd_digits; i++) {
        c.digits[i] = (((a % 100) / 10) << 4) | (a % 10);
        a /= 100;
    }
    return c;
}

BCD_int copy_BCD_int(BCD_int a);
inline BCD_int copy_BCD_int(BCD_int a) {
    BCD_int b = a;
    b.digits = (packed_BCD_pair *) malloc(sizeof(packed_BCD_pair) * b.bcd_digits);
    memcpy(b.digits, a.digits, b.bcd_digits);
    return b;
}

BCD_int BCD_from_bytes(const uint8_t *str, size_t chars, bool negative, bool little_endian) {
    // converts a bytestring to a little-endian BCD int
    BCD_int c;
    if (!chars || str == NULL) {
        c.zero = true;
        c.bcd_digits = c.decimal_digits = c.negative = 0;
        c.digits = NULL;
        return c;
    }
    size_t i;
    c.zero = false;
    c.negative = negative;
    c.digits = (packed_BCD_pair *) malloc(sizeof(packed_BCD_pair) * chars);
    if (little_endian)
        for (i = 0; i < chars; i++)
            c.digits[i] = str[i];
    else    {
        size_t j;
        for (i = 0, j = chars - 1; i < chars; i++, j--)
            c.digits[i] = str[j];
    }
    for (i = chars - 1; i != -1; i--) {
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
    if (unlikely(i == -1)) {
        c.zero = true;
        c.bcd_digits = c.decimal_digits = c.negative = 0;
        free(c.digits);
        c.digits = NULL;
    }
    return c;
}

BCD_int BCD_from_ascii(const char *str, size_t digits, bool negative);
inline BCD_int BCD_from_ascii(const char *str, size_t digits, bool negative) {
    // packs an ASCII digit string into big-endian bytes, then runs through BCD_from_bytes()
    size_t length = (digits + 1) / 2, i, j;
    uint8_t *bytes = (uint8_t *) malloc(sizeof(uint8_t) * length);
    j = i = digits % 2;
    if (i)
        bytes[0] = str[0] - '0';
    for (; i < length; i++, j += 2)
        bytes[i] = ((str[j] - '0') << 4) | ((str[j + 1] - '0') & 0xF);
    BCD_int ret = BCD_from_bytes(bytes, length, negative, false);
    free(bytes);
    return ret;
}

BCD_int sub_bcd(BCD_int x, BCD_int y);

BCD_int add_bcd(BCD_int x, BCD_int y) {
    // performing this on two n-digit numbers will take O(n) time
    if (unlikely(x.zero))
        return copy_BCD_int(y);
    if (unlikely(y.zero))
        return copy_BCD_int(x);
    if (x.negative != y.negative) {
        // if signs don't match, absolute value would go down.
        // that means we need to flip y's sign and move through sub_bcd()
        y.negative = !y.negative;
        return sub_bcd(x, y);
    }
    BCD_int z;
    size_t i, min_digits = min(x.bcd_digits, y.bcd_digits), max_digits = max(x.bcd_digits, y.bcd_digits);
    z.zero = false;  // result can't be zero because x and y are non-zero and share a sign
    z.negative = x.negative;  // we know this is also y.negative
    z.digits = (packed_BCD_pair *) malloc(sizeof(packed_BCD_pair) * (max_digits + 1));
    packed_BCD_pair a, b, c;
    bool overflow = false;
    for (i = 0; i < min_digits; i++) {
        a = x.digits[i];
        b = y.digits[i];
        if (!(overflow || a)) {
            c = b;
            overflow = false;
        }
        else if (!(overflow || b)) {
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
                        "add %3, %%al;"    // add the register containing b to al
                        "daa;"             // have the CPU make sure register al contains valid, packed BCD digits
                        "setc %1;"         // set the register containing overflow to hold the carry bit, set by daa
                                           // this next section tells the compiler what to do after execution
                      : "=a" (c),          // store the contents of register al in symbol c
                        "=rgm" (overflow)  // and a general register or memory location gets assigned to symbol overflow (referenced as %1)
                                           // then below tells the compiler what our inputs are
                      : "a" (a),           // symbol a should get dumped to register al
                        "rgm" (b)          // and symbol b in a general register or memory location (referenced as %3)
                    );
                #endif
            #else
                // otherwise fall back to doing it in C
                c = a + b;                             // set c to be the result of (a + b) % 0x100
                if ((overflow = (a > 0x99 - b))) {  // if c would overflow the decimal range
                    c += 0x60;                         // and add 0x60 to make a decimal digit
                }
                if (((a & 0xF) + (b & 0xF)) > 9) {  // if the lower nibble be bigger than 9
                    c += 0x06;                         // add 6 to make a decimal digit
                }
            #endif
            }
        z.digits[i] = c;
    }
    if (x.bcd_digits < y.bcd_digits)
        x = y;
    for (; overflow && i < max_digits; i++) {  // while there's overflow and digits, continue adding
        a = x.digits[i] + overflow;
        if ((a & 0x0F) == 0x0A)  // since all that's left is overflow, we don't need to check ranges
            a += 0x06;
        if ((overflow = ((a & 0xF0) == 0xA0)))
            a += 0x60;
        z.digits[i] = a;
    }
    for (; i < max_digits; i++)  // if there's no more overflow, but still digits left, copy directly
        z.digits[i] = x.digits[i];
    z.digits[max_digits] = overflow;
    z.bcd_digits = max_digits + overflow;
    if (overflow)
        z.decimal_digits = max_digits * 2 + 1;
    else if (z.digits[max_digits - 1] & 0xF0)
        z.decimal_digits = max_digits * 2;
    else
        z.decimal_digits = max_digits * 2 - 1;
    return z;
}

BCD_int mul_bcd_pow_10(BCD_int x, uintmax_t tens) {
    // this takes O(log_100(x)) time. Note that it's significantly faster if tens is even
    // returns x * 10^tens
    BCD_int ret;
    if (unlikely(x.zero))
        return new_BCD_int(0, false);
    ret.zero = false;
    ret.negative = x.negative;
    ret.decimal_digits = x.decimal_digits + tens;
    ret.bcd_digits = (ret.decimal_digits + 1) / 2;
    ret.digits = (packed_BCD_pair *) calloc(ret.bcd_digits, sizeof(packed_BCD_pair));
    if (tens % 2 == 0) {
        // +--+--+    +--+--+--+
        // |23|01| -> ...|23|01|
        // +--+--+    +--+--+--+
        const size_t digit_diff = ret.bcd_digits - x.bcd_digits;
        memcpy(ret.digits + digit_diff, x.digits, x.bcd_digits);
    }
    else    {
        // +--+--+    +--+--+--+
        // |23|01| -> ...|30|12|
        // +--+--+    +--+--+--+
        // +--+--+    +--+--+--+--+
        // |34|12| -> ...|40|23|01|
        // +--+--+    +--+--+--+--+
        const size_t digit_diff = ret.bcd_digits - x.bcd_digits - ret.decimal_digits % 2;
        // note that digit_diff needs to be adjusted on this branch, so it can't be common
        ret.digits[digit_diff] = x.digits[0] << 4;
        for (size_t i = 1; i < x.bcd_digits; i++) {
            ret.digits[i + digit_diff] = x.digits[i] << 4;
            ret.digits[i + digit_diff] |= x.digits[i - 1] >> 4;
        }
        ret.digits[x.bcd_digits + digit_diff] |= x.digits[x.bcd_digits - 1] >> 4;
    }
    return ret;
}

BCD_int shift_bcd_left(BCD_int x, uintmax_t tens);
inline BCD_int shift_bcd_left(BCD_int x, uintmax_t tens) {
    return mul_bcd_pow_10(x, tens);
}

BCD_int mul_bcd_cuint(BCD_int x, uintmax_t y) {
    // this takes roughly O(log(y) * log(x)) time, and is nearly linear if y is a multiple of 10
    // it works by breaking the multiplication down into groups of addition
    // full formula for performance is something like:
    // y = 10^a * b
    // f(i) = sum(n = 1 thru 19, (i % 10^(n + 1)) / 10^n) + i / 10^20
    // bool(i) = 1 if i else 0
    // time = O(bool(a) * log_100(x) + f(b) * log_100(xy))
    if (unlikely(!y || x.zero))
        return new_BCD_int(0, false);
    uint8_t tens = 0;  // will up size when there's an 848-bit system
    BCD_int ret, sum, mul_by_power_10;
    // first remove factors of ten
    while (y % 10 == 0) {
        y /= 10;
        ++tens;
    }
    if (tens)
        ret = mul_bcd_pow_10(x, tens);
    else
        ret = new_BCD_int(0, x.negative);
    // then for decreasing powers of ten, batch additions
    uintmax_t p = (sizeof(uintmax_t) == 16) ? MAX_POW_10_128 : MAX_POW_10_64;
    tens = (sizeof(uintmax_t) == 16) ? POW_OF_MAX_POW_10_128 : POW_OF_MAX_POW_10_64;
    for (; p > 1; p /= 10, --tens) {
        while (y >= p) {
            mul_by_power_10 = mul_bcd_pow_10(x, tens);
            sum = add_bcd(ret, mul_by_power_10);
            free_BCD_int(mul_by_power_10);
            free_BCD_int(ret);
            ret = sum;
            y -= p;
        }
    }
    // then do simple addition
    while (y--) {
        sum = add_bcd(ret, x);
        free_BCD_int(ret);
        ret = sum;
    }
    return ret;
}

BCD_int pow_cuint_cuint(uintmax_t x, uintmax_t y);
inline BCD_int pow_cuint_cuint(uintmax_t x, uintmax_t y) {
    // this takes roughly O(xylog_100(xy)) time
    BCD_int answer = new_BCD_int(1, false), tmp;
    while (y--) {
        tmp = mul_bcd_cuint(answer, x);
        free_BCD_int(answer);
        answer = tmp;
    }
    return answer;
}

uint16_t mul_dig_pair(packed_BCD_pair ab, packed_BCD_pair cd);
inline uint16_t mul_dig_pair(packed_BCD_pair ab, packed_BCD_pair cd) {
    // multiplies two digits pairs and returns an unsigned C short. valid range is 0 thru 9801
    uint8_t a, b, c, d;
    // first unpack the digits
    a = ab >> 4;
    b = ab & 0xF;
    c = cd >> 4;
    d = cd & 0xF;
    // then solve by FOIL
    return 100 * a * c + 10 * (a * d + b * c) + b * d;
}

BCD_int mul_bcd(BCD_int x, BCD_int y) {
    // multiplies two BCD ints by breaking them down into their component bytes and adding the results
    // this takes O(log_100(x) * log_100(y) * log_100(xy)) time
    BCD_int answer = new_BCD_int(0, false), addend, tmp;
    if (unlikely(x.zero || y.zero))
        return answer;
    size_t i, j;
    uint16_t staging;
    uintmax_t ipow_10 = 0, pow_10;
    for (i = 0; i < x.bcd_digits; i++, ipow_10 += 2) {
        for (j = 0, pow_10 = ipow_10; j < y.bcd_digits; j++, pow_10 += 2) {
            staging = mul_dig_pair(x.digits[i], y.digits[j]);
            if (staging == 0)
                continue;
            if (likely(pow_10)) {
                tmp = new_BCD_int(staging, false);
                addend = mul_bcd_pow_10(tmp, pow_10);  // this was not added to performance analysis
                free_BCD_int(tmp);
            }
            else
                addend = new_BCD_int(staging, false);
            tmp = add_bcd(answer, addend);
            free_BCD_int(addend);
            free_BCD_int(answer);
            answer = tmp;
        }
    }
    answer.negative = !(x.negative == y.negative);
    return answer;
}

BCD_int pow_bcd(BCD_int x, BCD_int y) {
    // this takes O(y * 2log_100(x) * log_100(x)^2) time
    BCD_int answer = new_BCD_int(1, false), tmp, one = new_BCD_int(1, false);
    while (!y.zero) {
        tmp = mul_bcd(answer, x);
        free_BCD_int(answer);
        answer = tmp;
        tmp = sub_bcd(y, one);
        free_BCD_int(y);
        y = tmp;
    }
    free_BCD_int(one);
    return answer;
}

signed char cmp_bcd(BCD_int x, BCD_int y) {
    // returns:
    // 1 if x > y
    // -1 if y > x
    // else 0
    if (x.negative != y.negative)
        return (x.negative) ? -1 : 1;
    if (x.decimal_digits != y.decimal_digits) {
        if (x.decimal_digits > y.decimal_digits)
            return (x.negative) ? -1 : 1;
        return (x.negative) ? 1 : -1;
    }
    for (size_t i = x.bcd_digits - 1; i != -1; i--) {
        if (x.negative)
            return (x.digits[i] > y.digits[i]) ? -1 : 1;
        return (x.digits[i] > y.digits[i]) ? 1 : -1;
    }
    return 0;
}

BCD_int sub_bcd(BCD_int x, BCD_int y) {
    if (unlikely(x.zero)) {
        BCD_int ret = copy_BCD_int(y);
        ret.negative = !ret.negative;
        return ret;
    }
    if (unlikely(y.zero))
        return copy_BCD_int(x);
    if (x.negative != y.negative) {
        // if signs don't match, absolute value would go up.
        // that means we need to flip y's sign and move through add_bcd()
        y.negative = !y.negative;
        return add_bcd(x, y);
    }
    signed char cmp = cmp_bcd(x, y);
    BCD_int z;
    if ((z.zero = !cmp))
        return new_BCD_int(0, false);
    z.negative = (cmp == -1);
    size_t i, min_digits = min(x.bcd_digits, y.bcd_digits), max_digits = max(x.bcd_digits, y.bcd_digits);
    z.digits = (packed_BCD_pair *) malloc(sizeof(packed_BCD_pair) * max_digits);
    packed_BCD_pair a, b, c;
    bool carry = false;
    for (i = 0; i < min_digits; i++) {
        a = x.digits[i];
        b = y.digits[i];
        if (!(carry || a)) {
            c = b;
            carry = false;
        }
        else if (!(carry || b)) {
            c = a;
            carry = false;
        }
        else    {
            b += carry;  // incorporate carry from last pair
            #if (!defined(NO_ASSEMBLY) && X86_COMPILER)
                // if on these architectures, there's assembly tricks to adjust BCD in-silicon
                #if CL_COMPILER
                    // CL compiler has a different syntax for inline assembly, does a lot less lifting
                    // note that the syntax here is: op [dest [, src]]
                    // brackets indicate a C symbol is referenced rather than a register
                    __asm   {
                        mov al, [a];         // move C symbol a to register al
                        sub al, [b];         // add C symbol b to register al
                        das;                 // have the CPU make sure register al contains valid, packed BCD digits
                        setc [carry];        // set C symbol carry to contain the carry bit, set by daa
                        mov [c], al;         // move register al to C symbol c
                    }
                #else
                    // this is the standard GCC/LLVM syntax for it
                    // note that the syntax here is: op [[src, ] dest]
                    // %\d indicates a C symbol is referenced, see the lookups at the end of code for which
                    __asm__(
                        "sub %3, %%al;"    // add the register containing b to al
                        "das;"             // have the CPU make sure register al contains valid, packed BCD digits
                        "setc %1;"         // set the register containing carry to hold the carry bit, set by daa
                                           // this next section tells the compiler what to do after execution
                      : "=a" (c),          // store the contents of register al in symbol c
                        "=rgm" (carry)     // and a general register or memory location gets assigned to symbol carry (referenced as %1)
                                           // then below tells the compiler what our inputs are
                      : "a" (a),           // symbol a should get dumped to register al
                        "rgm" (b)          // and symbol b in a general register or memory location (referenced as %3)
                    );
                #endif
            #else
                // otherwise fall back to doing it in C
                c = a - b;                             // set c to be the result of (a - b) % 0x100
                if ((carry = (c & 0xF0) > 0x99)) {  // if c would overflow the decimal range
                    c -= 0x60;                         // and subtract 0x60 to make a decimal digit
                }
                if ((c & 0x0F) > 9) {                 // if the lower nibble be bigger than 9
                    c -= 0x06;                         // subtract 6 to make a decimal digit
                }
            #endif
            }
        z.digits[i] = c;
    }
    if (x.bcd_digits < y.bcd_digits)
        x = y;
    for (; carry && i < max_digits; i++) {  // while there's carry and digits, continue adding
        a = x.digits[i] - carry;
        if ((a & 0x0F) == 0x0F)  // since all that's left is carry, we don't need to check ranges
            a -= 0x06;
        if ((carry = ((a & 0xF0) == 0xF0)))
            a -= 0x60;
        z.digits[i] = a;
    }
    for (; i < max_digits; i++)  // if there's no more carry, but still digits left, copy directly
        z.digits[i] = x.digits[i];
    z.bcd_digits = i;
    z.decimal_digits = z.bcd_digits / 2;
    if (!(z.digits[i - 1] & 0xF0))
        z.decimal_digits--;
    return z;
}

BCD_int div_bcd_pow_10(BCD_int a, uintmax_t tens) {
    if (unlikely(a.zero))
        return copy_BCD_int(a);
    BCD_int ret;
    ret.negative = a.negative;
    ret.zero = false;
    ret.decimal_digits = a.decimal_digits - tens;
    if (tens % 2 == 0) {
        ret.bcd_digits = a.bcd_digits - tens / 2;
        ret.digits = (packed_BCD_pair *) malloc(sizeof(packed_BCD_pair) * ret.bcd_digits);
        memcpy(ret.digits, a.digits + tens / 2, ret.bcd_digits);
    }
    else {
        // TODO
    }
    return ret;
}

BCD_int shift_bcd_right(BCD_int a, uintmax_t tens);
inline BCD_int shift_bcd_right(BCD_int a, uintmax_t tens) {
    return div_bcd_pow_10(a, tens);
}

void iadd_bcd(BCD_int *const x, const BCD_int y) {
    BCD_int ret = add_bcd(*x, y);
    free_BCD_int(*x);
    *x = ret;
}

uintmax_t bcd_to_unsigned(BCD_int a) {
    if (a.zero)
        return 0;
    uintmax_t answer = 0;
    for (size_t i = 0; i < a.bcd_digits; ++i) {
        size_t digit = a.bcd_digits - i - 1;
        answer = answer * 100 + ((a.digits[digit] & 0xF0) >> 4) * 10 + (a.digits[digit] & 0xF);
    }
    return answer;
}

intmax_t bcd_to_signed(BCD_int a);
inline intmax_t bcd_to_signed(BCD_int a) {
    intmax_t answer = (intmax_t) bcd_to_unsigned(a);
    if (a.negative)
        return -answer;
    return answer;
}

void print_bcd(BCD_int x) {
    if (unlikely(x.zero)) {
        printf("0");
        return;
    }
    if (x.negative)
        printf("-");
    size_t i = x.bcd_digits - 1;
    printf("%x", x.digits[i]);
    if (i--)
        for (; i != -1; i--)
            printf("%02x", x.digits[i]);
}

void print_bcd_ln(BCD_int x);
inline void print_bcd_ln(BCD_int x) {
    print_bcd(x);
    printf("\n");
}
