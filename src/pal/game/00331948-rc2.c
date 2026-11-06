/* func_PAL_00331948, the PAL copy of func_0032FDD0: the same C, where the first
 * read is negated only while the byte at D_PAL_001A7ACC is clear. */
#include "common.h"

extern void func_00282C88(f32 *v);
extern f32 func_00282DF0(f32 *v);
extern s8 D_00189E20[];
extern f32 D_001B284C;
extern u8 D_PAL_001A7ACC;

void func_PAL_00331948(s8 *a0) {
    s8 *base;
    s8 *base2;
    s8 *obj;
    f32 vec[2];

    obj = *(s8 **)(a0 + 0x68);
    if (D_PAL_001A7ACC != 0) {
        base = D_00189E20;
        (*(f32 *)((s8 *)(obj) + (0x54))) = (*(f32 *)((s8 *)(base) + (0x1FB0)));
    } else {
        base = D_00189E20;
        (*(f32 *)((s8 *)(obj) + (0x54))) = -(*(f32 *)((s8 *)(base) + (0x1FB0)));
    }
    base2 = D_00189E20;
    (*(f32 *)((s8 *)(obj) + (0x50))) = -(*(f32 *)((s8 *)(base2) + (0x1FB4)));
    if ((*(f32 *)((s8 *)(obj) + (0x54))) > 1.0f) {
        (*(f32 *)((s8 *)(obj) + (0x54))) = 1.0f;
    } else if ((*(f32 *)((s8 *)(obj) + (0x54))) < -1.0f) {
        (*(f32 *)((s8 *)(obj) + (0x54))) = -1.0f;
    }
    if ((*(f32 *)((s8 *)(obj) + (0x50))) > 1.0f) {
        (*(f32 *)((s8 *)(obj) + (0x50))) = 1.0f;
    } else if ((*(f32 *)((s8 *)(obj) + (0x50))) < -1.0f) {
        (*(f32 *)((s8 *)(obj) + (0x50))) = -1.0f;
    }
    func_00282C88(vec);
    vec[0] = (*(f32 *)((s8 *)(obj) + (0x50)));
    vec[1] = (*(f32 *)((s8 *)(obj) + (0x54)));
    D_001B284C = func_00282DF0(vec);
}
