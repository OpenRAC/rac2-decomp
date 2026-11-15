#include "common.h"

extern void func_00282CF0(void *out, void *first, void *second);
extern void func_002AD6F0(void *out, void *position, void *rotation, void *direction);

void func_L08_003D0508(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    float displacement[4] __attribute__((aligned(16)));
    if (object[0x20] == 0) {
        qcopy(state + 0x90, object + 0x10);
        *(s32 *)(state + 0x8C) |= 1;
        *(u16 *)(state + 0x3E) = 15;
        *(u8 **)(state + 8) = state + 0x50;
        *(u8 **)state = state + 0x20;
        object[0x20] = 1;
        *(u16 *)(object + 0x34) |= 0x20;
    }
    FastVecSub(displacement, object + 0x10, state + 0x90);
    func_002AD6F0(state + 0x50, displacement, object + 0xF0, object + 0xF0);
    qcopy(state + 0x90, object + 0x10);
}
