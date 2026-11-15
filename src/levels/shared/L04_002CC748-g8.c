#include "names.h"
/* The -G8 sibling of L04_002CC748.c: this body reads the level's small-data angle
   D_L04_001AD840 through $gp, which needs -G8. */

typedef int s32;

typedef unsigned int u32;

typedef unsigned char u8;

typedef unsigned short u16;

typedef short s16;

typedef float f32;

extern f32 D_L04_001AD840 __attribute__((sda));
extern f32 D_L04_001AD844;
extern u8 D_L04_001B9540[];
extern u8 D_L04_001B9680[];

extern s32 func_310060(f32 *vec, f32 angle);
extern f32 func_30EF70(f32 *vec, void *mat);
extern f32 func_30FF88(s32 value);
extern void func_3076D0(u32 a0, u32 a1);
extern void func_3074C8(u8 *a0, u32 a1);
extern void func_L04_003A0008(u8 *a0, u32 a1);

/* advances every ripple patch of the record the object at +0x28 points to */
void func_L04_003A1FE0(u8 *moby) {
    u8 *vars = *(u8 **)(*(u32 *)(moby + 0x28) + 0x68);
    u8 *table;
    f32 pos[4];
    s32 i;
    s32 offset;
    s32 nearby;

    if (*(s32 *)(vars + 0x10) < 0)
        return;
    if (*(s32 *)(vars + 0x18) == -1)
        return;

    i = *(s32 *)(vars + 0x10);
    if (i >= *(s32 *)(moby + 0x4))
        return;
    offset = i * 0x1190;
    for (; i < *(s32 *)(moby + 0x4); i++, offset += 0x1190) {
        table = D_L04_001B9540;
        nearby = 1;
        *(f32 *)((u8 *)(offset + *(s32 *)(moby + 0x8)) + 0x8) =
            *(f32 *)(*(u32 *)(moby + 0x28) + 0x18);
        pos[0] = *(f32 *)((u8 *)(offset + *(s32 *)(moby + 0x8)) + 0x0) + D_L04_001AD840 * 0.5f;
        pos[1] = *(f32 *)((u8 *)(offset + *(s32 *)(moby + 0x8)) + 0x4) + D_L04_001AD844 * 0.5f;
        pos[2] = *(f32 *)((u8 *)(offset + *(s32 *)(moby + 0x8)) + 0x8);
        pos[3] = 22.6f;
        if (func_310060(pos, 71.5f) == -1 ||
            func_30EF70(pos, D_L04_001B9680) > 71.5f)
            nearby = 0;
        *(f32 *)((u8 *)(offset + *(s32 *)(moby + 0x8)) + 0x4C) =
            1.0f - func_30FF88(*(s16 *)(vars + 0x16)) / func_30FF88(60);
        if (nearby)
            *(u16 *)((u8 *)(offset + *(s32 *)(moby + 0x8)) + 0x1E) =
                *(u16 *)(*(u8 **)(moby + 0x10) + i * 2);
        else
            *(u16 *)((u8 *)(offset + *(s32 *)(moby + 0x8)) + 0x1E) = 0;
        *(u32 *)((u8 *)(offset + *(s32 *)(moby + 0x8)) + 0x48) = *(u8 *)(vars + 0x14);
        if (i == 0) {
            AdvanceWaterRippleStep(*(u8 **)(moby + 0x8), *(u32 *)(moby + 0x0));
            if (*(u32 *)(table + 0x400) != 0)
                func_3076D0(*(u32 *)(moby + 0x2C), *(u32 *)(moby + 0x28));
            else
                func_3074C8(*(u32 *)(moby + 0x2C), *(u32 *)(moby + 0x28));
        }
    }
}
