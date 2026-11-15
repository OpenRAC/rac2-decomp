#include "include_asm.h"
#include "common.h"

extern void FastVecSub(float *out, const float *a, const float *b);
extern void vec_scale_to_length(float *out, const float *a, float s);
extern void QueueMobyImpact(void *obj, void *block);

/* Builds a small hit record pointing from a source to an object and delivers it as damage. */
void func_L05_003CFB90(u8 *owner, float *source)
{
    u8 blk[0x30];
    *(int *)(blk + 0x14) = 0x10000;
    *(int *)(blk + 0x20) = 1;
    blk[0x19] = 2;
    *(u8 **)(blk + 0x10) = owner;
    *(u16 *)(blk + 0x1A) = *(u16 *)(owner + 0xAA);
    blk[0x18] = 0;
    FastVecSub((float *)blk, (float *)(owner + 0x10), source);
    vec_scale_to_length((float *)blk, (float *)blk, 1.0f);
    *(float *)(blk + 0xC) = 5627.9248046875f;
    *(float *)(blk + 0x1C) = 5.0f;
    QueueMobyImpact(owner, blk);
}
