/* Copies the object's quad at +0x10 into v and runs it through func_00282CC0 with t
   (func_00282F20 of +0xE0 and the $gp float) and func_00282CF0 with +0xC0, copies +0xF0
   into w, then passes v and w to func_00335438, or to func_00335370 and func_003353C8
   when the +0x86 short of D_L01_001B9510's object is 5. */
#include "common.h"

typedef unsigned int u128 __attribute__((mode(TI)));

extern f32 D_L01_001AF86C __attribute__((sda));
extern u8 *D_L01_001B9510 __attribute__((nosda));
extern void func_00282F20(u8 *, u8 *, f32);
extern void func_00282CC0(u8 *, u8 *, u8 *);
extern void func_00282CF0(u8 *, u8 *, u8 *);
extern void func_00335370(u8 *);
extern void func_003353C8(u8 *);
extern void func_00335438(u8 *, u8 *, s32, s32, s32);

/* Works out a point in front of the object and a second point, then draws a line or beam between them. */
void func_L01_003A64F0(u8 *object)
{
    u128 start[1];
    u128 end[1];
    u128 offset[1];

    qcopy(start, object + 0x10);
    vec_scale_to_length((u8 *)offset, object + 0xE0, D_L01_001AF86C);
    FastVecAdd((u8 *)start, (u8 *)start, (u8 *)offset);
    FastVecSub((u8 *)start, (u8 *)start, object + 0xC0);
    qcopy(end, object + 0xF0);
    if (*(s16 *)(D_L01_001B9510 + 0x86) != 5) {
        SetCamera5Pose((u8 *)start, (u8 *)end, 0, 0, 0);
    } else {
        CopyVectorToSelectedObject((u8 *)start);
        SetCameraStateRotation((u8 *)end);
    }
}
