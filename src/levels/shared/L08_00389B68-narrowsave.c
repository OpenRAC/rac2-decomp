/* func_L08_00389B68: variadic, built with -mastra-quad-saves and -frac2-narrow-saves-below.
   register_precision keeps $ra's save at 64 bits; the narrower save takes the lower slot.
   The packet pointer is reloaded at every store in retail. */
#include "common.h"
extern volatile u32 * volatile ref_L08_00389B68_00 __attribute__((sda));
extern u32 *ref_L08_00389B68_01 MACRO_ADDR;
extern void func_00282AB0(void *, void *, int);
void func_L08_00389B68(int count, ...) __attribute__((register_precision(ra, 64)));
void func_L08_00389B68(int count, ...) {
    if (count) {
        ref_L08_00389B68_00[0] = (count + 1) | 0x10000000;
        ref_L08_00389B68_00[1] = 0;
        ref_L08_00389B68_00[2] = 0;
        ref_L08_00389B68_00[3] = (count + 1) | 0x50000000;
        ref_L08_00389B68_00[4] = count + 0x8000;
        ref_L08_00389B68_00[5] = 0x10000000;
        ref_L08_00389B68_00[6] = 14;
        ref_L08_00389B68_00[7] = 0;
        ref_L08_00389B68_01 = (u32 *)(ref_L08_00389B68_00 + 8);
        func_00282AB0(ref_L08_00389B68_01, (char *)__builtin_next_arg(count) - 0x38, count * 16);
        ref_L08_00389B68_00 = (u32 *)((char *)ref_L08_00389B68_00 + count * 16);
    }
}
