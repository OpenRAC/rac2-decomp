#include "names.h"
/* Decimal-exponent formatter reconstructed from retail and the current
 * public rac1-decomp counterpart src/core/00119D88.c:func_00119F38
 * (origin/main 69c3e42d). The software-double helper identities and the
 * complete 64-bit value passed to func_0011C000 follow the RAC2 callers.
 */
extern int dpcmp(double, double) __asm__("func_00123028");
extern double dpsub(double, double) __asm__("func_00122A98");
extern double dpmul(double, double) __asm__("func_00122B00");
extern double dpdiv(double, double) __asm__("func_00122DA8");
extern unsigned long func_001212C8(double);
extern int func_0011C000(unsigned long);
extern void (*D_00134698)(int);
extern void func_0011C7E8(const char *, ...);

/* Prints a decimal number in the form 0.123e+4. */
void func_0011C090(double value)
{
    int exponent = 0;
    int digits;
    if (value < 0.0) {
        value = -value;
        D_00134698('-');
    }
    if (value < 0.1) {
        while (value < 0.1) {
            value *= 10.0;
            exponent--;
        }
    } else if (value >= 1.0) {
        while (value >= 1.0) {
            value /= 10.0;
            exponent++;
        }
    }
    digits = DoubleBitsToDigits(DoubleToUnsignedLongLong(value * 1000000.0));
    PrintFormatted("0.%d", digits);
    if (exponent >= 0) PrintFormatted("e+%d", exponent);
    else PrintFormatted("e%d", exponent);
}
