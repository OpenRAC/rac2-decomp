/* Nonmatching reconstruction. Profile: -O2 -G0 -ffunction-sections.
 * 512/512 bytes; 0/8 in US, US2 and PAL. All loop/second-choice/return instructions match, but the input FP block and immediate best-angle setup differ. A measured input prefix fixes base addressing; changing declaration order ties. Preserve NaN-sensitive threshold and selection guards. Reopen with the input expression/FP allocation evidence.
 * No complete strict linked validation or matching credit.
 */
#include "common.h"

typedef struct { u8 before[0x148]; f32 x, y; } Input;
extern Input D_00138180;
extern f32 D_L03_0029BBF0[][4];
extern f32 D_L03_001B9BC0[];
extern f32 func_00283248(f32, f32);
extern void func_00283098(void *, void *, void *);
extern f32 func_00282DB0(void *, void *);
extern f32 func_00283C80(f32, f32);

s32 func_L03_003E3800(u8 *object)
{
    f32 vector[4] __attribute__((aligned(16)));
    f32 y = -D_00138180.y;
    f32 x = -D_00138180.x;
    u8 *vars = *(u8 **)(object + 0x68);
    f32 angle, best, dot, difference;
    s32 selected, i, id;
    if (x * x + y * y < 0.9f)
        return 0;
    angle = func_00283248(x, y);
    selected = -1;
    best = 1.57f;
    for (i = 0; i < 8 && vars[0x40 + i] != 255; i++) {
        id = vars[0x40 + i];
        func_00283098(vector, D_L03_0029BBF0[id], object + 0xC0);
        dot = func_00282DB0(vector, D_L03_001B9BC0);
        difference = func_00283C80(func_00283248(dot, func_00282DB0(vector, D_L03_001B9BC0 + 4)), angle);
        if (difference < best) {
            selected = id;
            best = difference;
        }
    }
    id = *(short *)(vars + 0x5C);
    if (id != *(short *)(vars + 0x50)) {
        func_00283098(vector, D_L03_0029BBF0[id], object + 0xC0);
        dot = func_00282DB0(vector, D_L03_001B9BC0);
        difference = func_00283C80(func_00283248(dot, func_00282DB0(vector, D_L03_001B9BC0 + 4)), angle);
        if (difference < best)
            selected = id;
    }
    if (selected != -1) {
        *(short *)(vars + 0x52) = selected;
        return 1;
    }
    return 0;
}
