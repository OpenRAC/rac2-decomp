/* func_L08_00429EE8: retained near miss, 30 October 2026.
   Profile: -O2 -G0 -ffunction-sections.
   Standalone ABI-correct variant; old draft retained. func_002FC560 receives a 64-bit value and the final state argument is also 64 bits. The renderer retains its two-argument interface. Loop shape and constant/base hoisting remain.
   No linked match is claimed.
*/

#include "common.h"
extern s32 D_L08_001B3A30[];
extern f32 D_L08_001B3A20[];
extern s32 D_L08_001B39A0[];
extern u8 D_L08_002604A0[];
extern void func_002FC560(u32 reg, u64 value);
extern int func_L02_002F1658(void);
extern void func_L08_0042A980(void *a0, s32 a1);
extern void func_L08_0042A0B0(s32 a0, s32 a1, u8 *a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern int func_002A7820(int, int);
extern void func_L08_00389B68(s32 a0, s32 a1, s32 a2, s32 a3, unsigned long a4);

/* Steps the three lanes: wraps each scroll offset and re-stamps the two ring segments. */
void func_L08_00429EE8(u8 *object)
{
    s32 *context = *(s32 **)(object + 0x68);
    f32 *scroll = D_L08_001B3A20;
    s32 *entry = D_L08_001B3A30;
    s32 i;
    s32 x;
    s32 y;
    u8 *inner;

    func_002FC560(0x47, 0x51001);
    for (i = 0; i < 3; i++, scroll++, entry++) {
        if (*entry == 0)
            continue;
        if (D_L08_001B39A0[i] < 2)
            continue;
        if (func_L02_002F1658()) {
            *scroll = *scroll - 0.2f;
            if (*scroll <= -8.0f)
                *scroll = *scroll + 8.0f;
        }
        inner = D_L08_002604A0 + (i * 2 + 1) * 0x140;
        func_L08_0042A980((void *)*entry, i);
        y = context[1] + 0x3F;
        x = context[0] + 0x3F;
        func_L08_0042A0B0(y, x, D_L08_002604A0 + i * 2 * 0x140, 0x80, 0x40, i, -1);
        func_L08_0042A0B0(y, x, inner, 0x30, 0x10, i, func_002A7820(1, 0x14));
    }
    func_L08_00389B68(2, 0x47, 0x5340B, 0x42, 0x8000000044UL);
}
