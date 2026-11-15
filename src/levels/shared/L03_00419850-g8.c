#include "include_asm.h"
#include "common.h"


typedef struct { f32 v[4]; } Vec4 __attribute__((aligned(16)));

extern f32 D_L03_001B1A9C __attribute__((sda));
extern s32 D_L03_001B1A94 __attribute__((sda));
extern f32 D_L03_001B1A98 __attribute__((sda));

extern void func_L03_00339128(Vec4 *, u8 *, s32, s32, f32, s32, s32, s32);

/* Draws a small marker sprite just above the object. */
void func_L03_00419850(u8 *object)
{
    Vec4 frame;
    u8 *state = *(u8 **)(object + 0x68);

    qcopy(&frame, object + 0x10);
    frame.v[2] = frame.v[2] + D_L03_001B1A9C;
    CreateTimedEffectEntry(&frame, object, *(s32 *)(state + 0x10) + 2,
                      D_L03_001B1A94, D_L03_001B1A98, 0x20, 2, 0xFF);
}
