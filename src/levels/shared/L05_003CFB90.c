#include "include_asm.h"
#include "common.h"

extern void func_00282CF0(float *out, const float *a, const float *b);
extern void func_00282F20(float *out, const float *a, float s);
extern void func_002A8E20(void *obj, void *block);

void func_L05_003CFB90(u8 *a0, float *a1)
{
    u8 blk[0x30];
    *(int *)(blk + 0x14) = 0x10000;
    *(int *)(blk + 0x20) = 1;
    blk[0x19] = 2;
    *(u8 **)(blk + 0x10) = a0;
    *(u16 *)(blk + 0x1A) = *(u16 *)(a0 + 0xAA);
    blk[0x18] = 0;
    FastVecSub((float *)blk, (float *)(a0 + 0x10), a1);
    vec_scale_to_length((float *)blk, (float *)blk, 1.0f);
    *(float *)(blk + 0xC) = 5627.9248046875f;
    *(float *)(blk + 0x1C) = 5.0f;
    QueueMobyImpact(a0, blk);
}
