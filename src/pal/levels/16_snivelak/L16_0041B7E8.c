#include "include_asm.h"
#include "names.h"


typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;
extern void FastVecSub(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, f32);
extern void func_PAL_0032F3B8(char *, char *, char *, f32);
extern void PlayMobySound(s32, s32, char *);
extern f32 math_fabs(f32);
extern f32 math_random_signed_float_range(f32, f32);
extern f32 math_random_float_range(f32, f32);
extern void func_PAL_002735D0(char *, s32, s32, s32, char *, char *, char *, s32, f32, f32);
extern void vec_random_direction(char *, f32, f32);
extern char D_001B9B00[];
extern f32 FastAddRotations(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern s32 vec_fast_helper_b(char *);
extern void FastVecSub(char *, char *, char *);
extern s32 func_00313EE0(s32, s32);
extern s32 func_00313EA0(s32);
extern s32 func_003320E0(char *, char *, u32, u32, f32, u32, u32);
extern s32 func_002E8648(f32);

/* lays the object's ten measurement points out along a ring and asks the engine to arm them */
void func_PAL_L16_0041BF40(char *arg0) {
    char buf0[0x10];
    char buf1[0x10];
    f32 f20;
    f32 f30;
    s16 h;
    s32 i;

    FastVecSub(buf0, D_001B9B00, arg0 + 0x10);
    vec_scale_to_length(buf0, buf0, 1.0f);
    func_PAL_0032F3B8(arg0, arg0 + 0x10, buf0, 0.0f);
    PlayMobySound(0, 0, arg0);
    for (i = 0; i < 5; i++) {
        vec_random_direction(buf1, 0.10000001f, 0.3f);
        *(f32 *)(buf1 + 8) = math_fabs(*(f32 *)(buf1 + 8));
        h = *(s16 *)(arg0 + 0xAA);
        f20 = math_random_signed_float_range(90.0f, 180.0f);
        f30 = math_random_float_range(10.0f, 20.0f);
        func_PAL_002735D0(arg0, 2, h, i, arg0 + 0x10, arg0 + 0xF0, buf1, 0xFF, f20, f30);
    }
}

