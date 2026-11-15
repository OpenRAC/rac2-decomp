#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;
extern void FastVecSub(char *, char *, char *);
extern f32 func_002E73F8(f32);
extern f32 func_00313F98(f32, f32);
extern f32 func_00313F38(f32, f32);
extern f32 FastAddRotations(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern s32 vec_fast_helper_b(char *);
extern void FastVecSub(char *, char *, char *);
extern s32 math_random_int_range(s32, s32);
extern s32 func_00313EA0(s32);
extern void *part_spawn_hero_relative(char *, char *, u32, u32, f32, u32, u32);
extern s32 FloatToInt(f32);

/* spawns the level's score pickup effect for this object */
void func_PAL_L16_00424590(char *arg0) {
    char buf[0x10];
    char *st = *(char **)(arg0 + 0x68);
    char *obj;
    s32 handle;
    s32 a;

    FastVecSub(buf, arg0 + 0x10, st);
    handle = ((s32)(math_random_int_range(3, 7)) * 5 + 2) / 6 & 0xFF;
    a = func_00313EA0(0xFF) & 0xFF;
    obj = (char *)part_spawn_hero_relative(buf, st, 0x60006080, handle, 2.5f, a, 0);
    if (obj == 0)
        return;
    obj[9] = (u8)(FloatToInt(4.0f) - 16);
}

