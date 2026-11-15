#include "common.h"
#include "structs.h"
#include "double_parts.h"

extern void r1_func_0011D4A0(void);

extern double __floatsidf(int);
extern double __muldf3(double, double);
extern double __adddf3(double, double);

/* Converts a 64-bit whole number to a double. */
double func_001213B8(long value) {
    double high;
    double low;
    unsigned long lower;
    int word;
    high = __floatsidf((int)(value >> 32));
    high = __muldf3(high, 65536.0);
    high = __muldf3(high, 65536.0);
    lower = (unsigned long)value & 0xFFFFFFFFUL;
    word = (int)lower;
    low = __floatsidf(word);
    if (word < 0)
        low = __adddf3(low, 4294967296.0);
    return __adddf3(high, low);
}

/* func_00121450 is in 00121450.c, its own public libgcc module. */


extern void runtime_tail_call_helper(void);
extern void r1_func_0011D4A0_00121B18(void);

/* rac1-decomp src/core/0011DD68.c: func_0011DD98 */
/* Tail call: retail is `j r1_func_0011D4A0_00121B18` + nop, with no frame at all.
   2.9-ee emits it natively for a void function that ends in a call. */
/* Jumps straight to another runtime helper without doing any work itself. */
void runtime_tail_call_helper(void) {
    r1_func_0011D4A0_00121B18();
}

/* func_00121B20 and func_001220F0 (libgcc2.c's L_udivdi3 and L_umoddi3,
   `__udivdi3`/`__umoddi3`) are compiled C now: src/core/00121B20.c and
   src/core/001220F0.c. */

/* func_00122630 is in 00122630.c with its qualified packing profile. */

/* The runtime's own IEEE double unpacking: the sign, the kind (2 zero,
   3 normal, 4 infinity, 0 signalling NaN, 1 quiet NaN) and, for every kind
   but the zero, the fraction left-justified in the top bits of a 64-bit word
   with the implicit one at 2^60.

   Two spellings carry the retail bytes: the zero case is a `while` whose body
   returns, which keeps the block a loop head so the label that follows it is
   aligned to 8 bytes (retail's standalone `nop` at +0x34), and the normal
   path assigns the exponent, the kind and the fraction in that order, which
   is where retail puts the three stores. */
/* Takes a double apart into its sign, kind, exponent and fraction. */
void fp_unpack_double(double *value, DoubleParts *parts) {
    unsigned long bits = *(unsigned long *) value;
    unsigned int exponent = (unsigned int) (bits >> 52) & 0x7FF;
    unsigned long long fraction = bits & 0xFFFFFFFFFFFFFULL;

    parts->sign = (unsigned int) (bits >> 63);
    while (exponent == 0) {
        parts->kind = 2;
        return;
    }
    if (exponent == 0x7FF) {
        if (fraction == 0) {
            parts->kind = 4;
            return;
        }
        if (fraction & 0x8000000000000ULL) {
            parts->kind = 1;
        } else {
            parts->kind = 0;
        }
        parts->fraction.ll = fraction;
        return;
    }
    parts->exponent = (int) exponent - 1023;
    parts->kind = 3;
    parts->fraction.ll = (fraction << 8) | 0x1000000000000000ULL;
}

/* func_00122800 is in 00122800.c with its SDK compiler profile. */

extern void fp_unpack_double(double *, DoubleParts *);
extern DoubleParts *fp_add_double_parts(DoubleParts *, DoubleParts *, DoubleParts *);
extern double fp_pack_double(DoubleParts *);
extern int fp_compare_double_parts(DoubleParts *, DoubleParts *);

/* Adds two doubles using software math. */
double __adddf3(double first, double second) {
    DoubleParts a, b, result;
    fp_unpack_double(&first, &a);
    fp_unpack_double(&second, &b);
    return fp_pack_double(fp_add_double_parts(&a, &b, &result));
}

/* Subtracts the second double from the first using software math. */
double __subdf3(double first, double second) {
    DoubleParts a, b, result;
    fp_unpack_double(&first, &a);
    fp_unpack_double(&second, &b);
    b.sign ^= 1;
    return fp_pack_double(fp_add_double_parts(&a, &b, &result));
}

/* func_00122B00 is in 00122B00.c with its SDK assembler profile. */

/* libgcc dp-bit.o: dpdiv (GCC's fp-bit.c `divide`, whose static `_fpdiv_parts`
   this cc1 inlines because it has a single caller). GPL version 2-or-later
   with the libgcc linking exception. The single-precision sibling is fpdiv in
   the vendored src/core/001232F0.c; the source is rac1-decomp
   src/libgcc/fp-bit.c built with -DNO_DENORMALS -DUS_SOFTWARE_GOFAST.

   The 64-bit shift-subtract loop over the fraction, and the rounding block's
   `ANDI $v1,$a3,0xFF` / `0x80` against GARDMASK/GARDMSB, are the double
   constants: NGARDS 8, GARDROUND 0x7f, GARDMASK 0xff, GARDMSB 0x80,
   FRACBITS 52, so IMPLICIT_1 is 1LL<<60 -- which is retail's
   `ori $v0,$zero,0x8000; dsll32 $v0,$v0,13`. */

#define DP_FRACBITS 52
#define DP_NGARDS 8
#define DP_IMPLICIT_1 (1LL << (DP_FRACBITS + DP_NGARDS))
#define DP_GARDROUND 0x7f
#define DP_GARDMASK 0xff
#define DP_GARDMSB 0x80

extern DoubleParts __thenan_df;

static __inline__ DoubleParts *dp_div_nan(void) {
    return &__thenan_df;
}

/* fp-bit.c's own static INLINE predicates, spelled as they are there:
   the `== CLASS_INFINITY` form is what makes retail compare with
   `xori`/`beqz` rather than `addiu`/`beq`. */
static __inline__ int dp_div_isnan(DoubleParts *number) {
    return number->kind == 0 || number->kind == 1;
}
static __inline__ int dp_div_isinf(DoubleParts *number) {
    return number->kind == 4;
}
static __inline__ int dp_div_iszero(DoubleParts *number) {
    return number->kind == 2;
}

static __inline__ DoubleParts *dp_div_parts(DoubleParts *a, DoubleParts *b) {
    unsigned long bit;
    unsigned long numerator;
    unsigned long denominator;
    unsigned long quotient;

    if (dp_div_isnan(a)) {
        return a;
    }
    if (dp_div_isnan(b)) {
        return b;
    }

    a->sign = a->sign ^ b->sign;

    if (dp_div_isinf(a) || dp_div_iszero(a)) {
        if (a->kind == b->kind) {
            return dp_div_nan();
        }
        return a;
    }
    if (dp_div_isinf(b)) {
        a->fraction.ll = 0;
        a->exponent = 0;
        return a;
    }
    if (dp_div_iszero(b)) {
        a->kind = 4;
        return a;
    }

    a->exponent = a->exponent - b->exponent;
    numerator = a->fraction.ll;
    denominator = b->fraction.ll;

    if (numerator < denominator) {
        numerator *= 2;
        a->exponent--;
    }
    bit = DP_IMPLICIT_1;
    quotient = 0;
    while (bit) {
        if (numerator >= denominator) {
            quotient |= bit;
            numerator -= denominator;
        }
        bit >>= 1;
        numerator *= 2;
    }

    if ((quotient & DP_GARDMASK) == DP_GARDMSB) {
        if (quotient & (1 << DP_NGARDS)) {
            quotient += DP_GARDROUND + 1;
        } else if (numerator) {
            quotient += DP_GARDROUND + 1;
        }
    }

    a->fraction.ll = quotient;
    return a;
}

/* Divides the first double by the second using software math. */
double __divdf3(double first, double second) {
    DoubleParts a, b;
    DoubleParts *res;

    fp_unpack_double(&first, &a);
    fp_unpack_double(&second, &b);

    res = dp_div_parts(&a, &b);

    return fp_pack_double(res);
}

static __inline__ int double_parts_iszero(DoubleParts *parts) {
    return parts->kind == 2;
}
static __inline__ int double_parts_isnan(DoubleParts *parts) {
    return parts->kind == 0 || parts->kind == 1;
}
static __inline__ int double_parts_isinf(DoubleParts *parts) {
    return parts->kind == 4;
}

/* Compares two doubles. Gives -1, 0 or 1 for less, equal or greater. */
int __cmpdf2(double first, double second) {
    DoubleParts a, b;
    fp_unpack_double(&first, &a);
    fp_unpack_double(&second, &b);
    return fp_compare_double_parts(&a, &b);
}

/* Converts a signed 32-bit whole number to a double. */
double __floatsidf(int value) {
    DoubleParts parts;
    parts.kind = 3;
    parts.sign = value < 0;
    if (value == 0)
        parts.kind = 2;
    else {
        parts.exponent = 60;
        if (parts.sign != 0) {
            if (value == (int)0x80000000)
                return -2147483648.0;
            parts.fraction.ll = -value;
        } else
            parts.fraction.ll = value;
        while (parts.fraction.ll < (1UL << 60)) {
            parts.fraction.ll <<= 1;
            --parts.exponent;
        }
    }
    return fp_pack_double(&parts);
}

/* Converts a double to a signed 32-bit whole number, clamping when it is too big. */
int __fixdfsi(double value) {
    DoubleParts parts;
    int result;
    fp_unpack_double(&value, &parts);
    if (double_parts_iszero(&parts))
        return 0;
    if (double_parts_isnan(&parts))
        return 0;
    if (double_parts_isinf(&parts))
        return parts.sign != 0 ? (int)0x80000000 : 0x7FFFFFFF;
    if (parts.exponent < 0)
        return 0;
    if (parts.exponent > 30)
        return parts.sign != 0 ? (int)0x80000000 : 0x7FFFFFFF;
    result = (int)(parts.fraction.ll >> (60 - parts.exponent));
    return parts.sign != 0 ? -result : result;
}

/* Converts a double to an unsigned 32-bit whole number, clamping when it is out of range. */
unsigned int __fixunsdfsi(double value) {
    DoubleParts parts;
    fp_unpack_double(&value, &parts);
    if (double_parts_iszero(&parts))
        return 0;
    if (double_parts_isnan(&parts))
        return 0;
    if (parts.sign != 0)
        return 0;
    if (double_parts_isinf(&parts))
        return 0xFFFFFFFFU;
    if (parts.exponent < 0)
        return 0;
    if (parts.exponent > 31)
        return 0xFFFFFFFFU;
    if (parts.exponent > 60)
        return parts.fraction.ll << (parts.exponent - 60);
    return parts.fraction.ll >> (60 - parts.exponent);
}
