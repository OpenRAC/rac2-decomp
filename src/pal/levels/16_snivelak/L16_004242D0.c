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
void part_spawn_spinning_fragment_pal(char *self) {
    char position[0x10];
    char *vars = *(char **)(self + 0x68);
    char *particle;
    s32 kind;
    s32 alpha;

    FastVecSub(position, self + 0x10, vars);
    kind = ((s32)(math_random_int_range(3, 7)) * 5 + 2) / 6 & 0xFF;
    alpha = func_00313EA0(0xFF) & 0xFF;
    particle = (char *)part_spawn_hero_relative(position, vars, 0x60006080, kind, 2.5f, alpha, 0);
    if (particle == 0)
        return;
    particle[9] = (u8)(FloatToInt(4.0f) - 16);
}

