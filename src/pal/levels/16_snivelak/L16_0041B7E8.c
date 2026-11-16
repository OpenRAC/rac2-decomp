#include "include_asm.h"
#include "names.h"


typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;
extern void FastVecSub(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, f32);
extern char *part_spawn_blast_effect_moby_pal(char *, char *, char *, f32);
extern int PlayMobySound(s32, s32, char *);
extern f32 math_fabs(f32);
extern f32 math_random_signed_float_range(f32, f32);
extern f32 math_random_float_range(f32, f32);
extern char *cam_moby_create_pal(char *, s32, s32, s32, char *, char *, char *, s32, f32, f32);
extern void vec_random_direction(char *, f32, f32);
extern char g_turret_debris_vectors[];
extern f32 FastAddRotations(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern s32 vec_fast_helper_b(char *);
extern void FastVecSub(char *, char *, char *);
extern s32 func_00313EE0(s32, s32);
extern s32 func_00313EA0(s32);
extern s32 func_003320E0(char *, char *, u32, u32, f32, u32, u32);
extern s32 func_002E8648(f32);

/* lays the object's ten measurement points out along a ring and asks the engine to arm them */
void turret_explode_into_debris_pal(char *moby) {
    char to_origin[0x10];
    char velocity[0x10];
    f32 speed;
    f32 life;
    s16 class_id;
    s32 i;

    FastVecSub(to_origin, g_turret_debris_vectors, moby + 0x10);
    vec_scale_to_length(to_origin, to_origin, 1.0f);
    part_spawn_blast_effect_moby_pal(moby, moby + 0x10, to_origin, 0.0f);
    PlayMobySound(0, 0, moby);
    for (i = 0; i < 5; i++) {
        vec_random_direction(velocity, 0.10000001f, 0.3f);
        *(f32 *)(velocity + 8) = math_fabs(*(f32 *)(velocity + 8));
        class_id = *(s16 *)(moby + 0xAA);
        speed = math_random_signed_float_range(90.0f, 180.0f);
        life = math_random_float_range(10.0f, 20.0f);
        cam_moby_create_pal(moby, 2, class_id, i, moby + 0x10, moby + 0xF0, velocity, 0xFF, speed, life);
    }
}

