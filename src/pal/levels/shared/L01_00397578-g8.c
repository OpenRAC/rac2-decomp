#include "include_asm.h"

#include "common.h"
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float), fast_subtract_rotations(float, float);
extern void FastVecAdd(void *, void *, void *), vec_clear_128(void *);
extern void FadeToBlack(int), hero_reset_for_area_start(int), hero_reset_position_and_direction_pal(void *, void *, int, int);
extern int PlayMobySound(int, int, void *);
extern void SetCamera5Pose(void *, void *, int, int, int), object_copy_vector_to_selected(void *), cam_set_state_rotation(void *);
extern void anim_start_blended_pal(void *, int, int, int), set_hero_animation_pal(int, int, float);
extern unsigned char g_state_flag_c;
extern int g_camera_lock_flag;
typedef struct {
    char pad[0x80];
    float pos[4];
    float rot[4];
    char pad2[0x2214];
    unsigned char state;
    char pad3[10];
    unsigned char flag;
} TransitionPlayerState;
extern TransitionPlayerState g_hero_state;

/* Puts the hero beside the pad, facing away from it, with a fixed camera pose and the arrival animation, then moves the pad moby to its next state (PAL). */
void hero_enter_from_pad_pal(unsigned char *moby) {
    float spawn_pos[4], spawn_rot[4], camera_pos[4], camera_rot[4];
    char *vars = *(char **)(moby + 0x68);
    spawn_pos[0] = math_fast_sin_or_cos_a(*(float *)(vars + 0x1C))*2.5f;
    spawn_pos[1] = math_fast_sin_or_cos_b(*(float *)(vars + 0x1C))*2.5f;
    spawn_pos[2] = 0;
    FastVecAdd(spawn_pos, spawn_pos, vars + 0x10);
    vec_clear_128(spawn_rot);
    spawn_rot[2] = FastAddRotations(*(float *)(vars + 0x1C), 3.1415929794311523f);
    FadeToBlack(8);
    if (g_hero_state.state == 3) hero_reset_for_area_start(0);
    hero_reset_position_and_direction_pal(spawn_pos, spawn_rot, 0x6F, 0);
    PlayMobySound(0, 0, moby);
    camera_pos[0] = math_fast_sin_or_cos_a(*(float *)(vars + 0x1C))*1.25f;
    camera_pos[1] = math_fast_sin_or_cos_b(*(float *)(vars + 0x1C))*1.25f;
    camera_pos[2] = 0;
    camera_pos[0] += math_fast_sin_or_cos_a(FastAddRotations(*(float *)(vars + 0x1C), 1.5707964897155762f))*4.0f;
    camera_pos[1] += math_fast_sin_or_cos_b(FastAddRotations(*(float *)(vars + 0x1C), 1.5707964897155762f))*4.0f;
    FastVecAdd(camera_pos, camera_pos, vars + 0x10);
    camera_pos[2] += 1;
    vec_clear_128(camera_rot);
    camera_rot[2] = fast_subtract_rotations(*(float *)(vars + 0x1C), 1.5707964897155762f);
    SetCamera5Pose(camera_pos, camera_rot, 1, 0, 0);
    object_copy_vector_to_selected(camera_pos);
    cam_set_state_rotation(camera_rot);
    qcopy_nc(moby + 0x10, g_hero_state.pos);
    qcopy_nc(moby + 0xF0, g_hero_state.rot);
    if (moby[0x43] != 1) anim_start_blended_pal(moby, 1, 0, 0);
    set_hero_animation_pal(0x7B, 0, 0.0f);
    if (g_state_flag_c) *(unsigned short *)(moby + 0x34) |= 0x8000;
    g_hero_state.flag = 1;
    g_camera_lock_flag = 1;
    moby[0x20] = 2;
    *(int *)(vars + 0x6C) = 50;
}

typedef struct {
    u8 pad0[0x18];
    f32 f18;
    u8 pad1[0x60 - 0x1C];
    f32 f60;
    f32 f64;
    f32 f68;
} State_397870;
typedef struct {
    u8 pad0[0x24];
    f32 f24;
} Class_397870;
typedef struct {
    u8 pad0[0x18];
    f32 f18;
    u8 pad1[0x20 - 0x1C];
    u8 b20;
    u8 pad2[0x24 - 0x21];
    Class_397870 *cls;
    u8 pad3[0x2C - 0x28];
    f32 f2C;
    u8 pad4[0x68 - 0x30];
    State_397870 *st;
    u8 pad5[0xF0 - 0x6C];
    f32 fF0;
    f32 fF4;
    f32 fF8;
    f32 fFC;
} Obj_397870;
extern void part_spawn_sparkle_trail_above_ground_pal(Obj_397870 *a0);
extern float g_collectible_height_scale __attribute__((sda));
extern float g_bob_base_height __attribute__((sda));
extern float g_bob_l01_amplitude __attribute__((sda));
extern float g_bolt_bob_spin_speed __attribute__((sda));
extern int g_sparkle_chance __attribute__((sda));
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern int math_random_int_below(int);
extern void gold_bolt_glow_rings_update_pal(Obj_397870 *);

/* Updates a gold bolt: sets its height, bobs and spins it while idle, draws its glow rings and sometimes spawns a sparkle (PAL). */
void gold_bolt_update_pal(Obj_397870 *moby)
{
    State_397870 *vars = moby->st;
    float bob;

    moby->f2C = moby->cls->f24 * g_collectible_height_scale;

    if (moby->b20 == 1) {
        bob = math_fast_sin_or_cos_b(moby->fFC);
        moby->f18 = vars->f18 + g_bob_base_height + g_bob_l01_amplitude * bob;
        moby->fF0 = FastAddRotations(moby->fF0, vars->f68);
        moby->fF4 = FastAddRotations(moby->fF4, vars->f64);
        moby->fF8 = FastAddRotations(moby->fF8, vars->f60);
        moby->fFC = FastAddRotations(moby->fFC, 0.0003490659f * g_bolt_bob_spin_speed);
    }

    gold_bolt_glow_rings_update_pal(moby);
    if (math_random_int_below(g_sparkle_chance) == 0)
        part_spawn_sparkle_trail_above_ground_pal(moby);
}
