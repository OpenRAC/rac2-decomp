/* Copies the object's quad at +0x10 into v and runs it through func_00282CC0 with t
   (vec_scale_to_length of +0xE0 and the $gp float) and FastVecSub with +0xC0, copies +0xF0
   into w, then passes v and w to SetCamera5Pose, or to func_00335370 and func_003353C8
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

void func_L01_003A64F0(u8 *a0)
{
    u128 v[1];
    u128 w[1];
    u128 t[1];

    qcopy(v, a0 + 0x10);
    vec_scale_to_length((u8 *)t, a0 + 0xE0, D_L01_001AF86C);
    FastVecAdd((u8 *)v, (u8 *)v, (u8 *)t);
    FastVecSub((u8 *)v, (u8 *)v, a0 + 0xC0);
    qcopy(w, a0 + 0xF0);
    if (*(s16 *)(D_L01_001B9510 + 0x86) != 5) {
        SetCamera5Pose((u8 *)v, (u8 *)w, 0, 0, 0);
    } else {
        func_00335370((u8 *)v);
        func_003353C8((u8 *)w);
    }
}
