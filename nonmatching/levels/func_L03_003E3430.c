/* Nonmatching reconstruction. Profile: -O2 -G0 -ffunction-sections.
 * 572/580 bytes; 0/8 in US, US2 and PAL. Scoped count cursor recovers the short initial count loop; switch block placement and candidate-list address/register allocation still differ. First if-chain draft was 560 bytes. Reopen with object field/list ownership and real loop lifetimes.
 * No complete strict linked validation or matching credit.
 */
#include "common.h"

extern f32 D_L03_0029BBF0[][4];
extern f32 D_L03_001B9BC0[];
extern f32 func_00283248(f32, f32);
extern void func_00283098(void *, void *, void *);
extern f32 func_00282DB0(void *, void *);
extern f32 func_00283BE0(f32, f32);

void func_L03_003E3430(u8 *object)
{
    f32 vector[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(object + 0x68);
    s32 count = 0;
    s32 i;
    s32 selected;
    f32 dot, angle, best, difference;
    {
        s32 cursor = 0;
        u8 *list = vars + 0x40;
        while (cursor < 8 && list[cursor] != 255) {
            cursor++;
            count++;
        }
    }
    switch (count) {
    case 0:
        *(short *)(vars + 0x52) = *(u16 *)(vars + 0x50);
        break;
    case 1:
        *(short *)(vars + 0x52) = vars[0x40];
        break;
    default:
        func_00283098(vector, D_L03_0029BBF0[*(short *)(vars + 0x52)], object + 0xC0);
        dot = func_00282DB0(vector, D_L03_001B9BC0);
        angle = func_00283248(dot, func_00282DB0(vector, D_L03_001B9BC0 + 4));
        best = -10.0f;
        selected = -1;
        for (i = 0; i < count; i++) {
            if (vars[0x40 + i] == *(short *)(vars + 0x52))
                continue;
            if (vars[0x40 + i] == 255)
                break;
            func_00283098(vector, D_L03_0029BBF0[vars[0x40 + i]], object + 0xC0);
            dot = func_00282DB0(vector, D_L03_001B9BC0);
            difference = func_00283BE0(func_00283248(dot, func_00282DB0(vector, D_L03_001B9BC0 + 4)), angle);
            if (0.0f < difference)
                difference -= 6.2831854820251465f;
            if (best < difference) {
                selected = vars[0x40 + i];
                best = difference;
            }
        }
        if (selected != -1)
            *(short *)(vars + 0x52) = selected;
    }
}
