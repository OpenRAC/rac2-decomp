#include "common.h"

extern void func_L03_003CAAF0(u8 *, void *, void *);
extern s32 func_L03_00419BD8(u32, u8 *, u8 *);
extern s32 func_L03_00419C58(u32, void *);
extern f32 func_00282E80(void *, void *);
extern f32 func_002A89A8(void *, s32, f32);
extern u8 D_00189EA0[];

void func_L03_003CAB80(u8 *object, void *unused, f32 *output)
{
    f32 first[4] __attribute__((aligned(16)));
    f32 second[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(object + 0x68);
    s32 region;
    f32 distance;
    func_L03_003CAAF0(object, first, second);
    if (func_L03_00419BD8(*(u32 *)(vars + 0x64), (u8 *)first, D_00189EA0) != 0) {
        qcopy(output, first);
    } else if (func_L03_00419BD8(*(u32 *)(vars + 0x64), (u8 *)second, D_00189EA0) != 0) {
        qcopy(output, second);
    } else {
        region = func_L03_00419C58(*(u32 *)(vars + 0x64), first);
        if (region != -1) {
            qcopy(output, first);
        } else if (func_L03_00419C58(*(u32 *)(vars + 0x64), second) != region) {
            qcopy(output, second);
        } else {
            distance = func_00282E80(D_00189EA0, first);
            if (distance < func_00282E80(D_00189EA0, second))
                qcopy(output, first);
            else
                qcopy(output, second);
        }
    }
    output[2] += 0.5f;
    output[2] = func_002A89A8(output, 0, 0.5f);
}
