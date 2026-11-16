#include "include_asm.h"

#include "common.h"
typedef union { u8 b[0x2600]; s32 i[0x980]; f32 f[0x980]; char *ptr[0x980]; } Hero;
extern f32 D_L16_001B1AD0_gp[][4] SDATA(D_L16_001B1AD0);
extern f32 D_L16_001B1AF0_gp[] SDATA(D_L16_001B1AF0);
extern f32 g_turret_aim_params[] MACRO_ADDR;
extern f32 g_turret_aim_velocity_scale __attribute__((sda));
extern f32 g_turret_aim_speed __attribute__((sda));
extern s32 g_turret_aim_init_word __attribute__((sda));
extern u32 g_pad_pressed_flags __attribute__((nosda));
extern u8 g_extras_unlocked_flag[] __attribute__((sda));
extern char g_hero_state[];
extern char g_scene_origin_transform[];
extern char *g_aim_target_moby __attribute__((nosda));
extern char g_aim_target_position[];
extern s32 math_fast_float_d(char *);
extern void matrix_mul_vec3(char *, f32 *, char *);
extern void FastVecAdd(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, f32);
extern s32 coll_process_hit(char *, s32, char *, s32, f32);
extern s32 CollLine(char *, char *, s32, char *, s32);
extern void FastVecSub(char *, char *, char *);
extern char *SpawnEA7Moby_pal(char *, char *, char *, s32, f32);

/* Once the refire timer runs out while a fire button is held: places the alternating muzzle
   and the aim point in the turret's frame, aims at the hit of a ray (or the camera-line
   collision point, or the far end of the camera line), spawns the projectile and rearms. */
void FireAlternatingMuzzleShot_pal(char *moby) {
    char muzzle[16], aim[16], far[16], near[16], velocity[16];
    char *state = *(char **)(moby + 0x68);
    f32 speed;

    if (!math_fast_float_d(state + 0x8C)) return;
    if (!(g_pad_pressed_flags & 0xA0)) return;
    matrix_mul_vec3(muzzle, D_L16_001B1AD0_gp[*(s32 *)(state + 0x88)], moby + 0xC0);
    FastVecAdd(muzzle, muzzle, moby + 0x10);
    matrix_mul_vec3(aim, D_L16_001B1AF0_gp, moby + 0xC0);
    FastVecAdd(aim, aim, moby + 0x10);
    vec_scale_to_length(near, g_scene_origin_transform + 0x230, 2.0f);
    FastVecAdd(near, near, g_scene_origin_transform);
    vec_scale_to_length(far, g_scene_origin_transform + 0x230, 120.0f);
    FastVecAdd(far, far, g_scene_origin_transform);
    *(s32 *)(moby + 0x98) = 0;
    if (coll_process_hit(aim, 0, ((Hero *)g_hero_state)->ptr[0x2290 / 4], 0, g_turret_aim_params[3]) && g_aim_target_moby)
        FastVecSub(velocity, g_aim_target_moby + 0x10, muzzle);
    else if (CollLine(near, far, 0, ((Hero *)g_hero_state)->ptr[0x2290 / 4], 0))
        FastVecSub(velocity, g_aim_target_position, muzzle);
    else
        FastVecSub(velocity, far, muzzle);
    vec_scale_to_length(velocity, velocity, g_turret_aim_velocity_scale * 0.020000001f);
    speed = g_turret_aim_speed;
    *(s32 *)(moby + 0x98) = *(s32 *)(*(char **)(moby + 0x24) + 0x10);
    if (g_extras_unlocked_flag[0]) speed *= 5.0f;
    SpawnEA7Moby_pal(moby, velocity, muzzle, 0, speed);
    *(s32 *)(state + 0x8C) = ((s32)(g_turret_aim_init_word) * 5 + 2) / 6;
    *(s32 *)(state + 0x88) = (*(s32 *)(state + 0x88) + 1) & 1;
}
