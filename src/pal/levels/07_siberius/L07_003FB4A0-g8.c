#include "include_asm.h"

#include "common.h"
extern void *part_find_owned_effect_slot(u8 *, s32, s32);
extern f32 moby_update_aim_target_strength_pal(u8 *, s32);
extern f32 ApproachValue(f32 *, f32, f32);
extern void moby_set_state(u8 *, u8, s32);
extern f32 g_bomb_scale __attribute__((sda));
typedef struct { u8 pad[0x20]; f32 angle; u8 pad24[12]; u32 flags; } SpinnerState;

/* Starts the homing bomb on its first update. After that it counts its fuse angle down and switches to state 3 when it runs out. */
void homing_bomb_tick_fuse_pal(u8 *moby)
{
    SpinnerState *vars = *(SpinnerState **)(moby + 0x68);

    if (*(u8 *)(moby + 0x20) == 0) {
        f32 scale;
        vars->flags = 0;
        scale = g_bomb_scale;
        *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24) * scale;
        moby_set_state(moby, 1, -1);
        *(u32 *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        return;
    }
    {
        s32 id = part_find_owned_effect_slot(moby, 0x10000, 0);
        f32 fuse_angle = moby_update_aim_target_strength_pal(moby, id);
        ApproachValue(&vars->angle, 0.0f, fuse_angle);
    }
    if (vars->angle <= 0.0f)
        moby_set_state(moby, 3, -1);
    *(u8 *)(moby + 0xA8) = 0xFF;
}

typedef int SibQuad __attribute__((mode(TI)));
typedef union { SibQuad quad; float value[4]; } SibVector;
extern float g_bomb_rate __attribute__((sda));
extern float g_bomb_elapsed_param __attribute__((sda));
extern void FastVecSub(void *, void *, void *);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void euler_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_clamp_length(float *, float);
extern void FastVecAdd(void *, void *, void *);

/* The incoming second pointer is live at the first vector subtraction. */
/* Steers the homing bomb toward the target point: eases its speed and turns it flat toward the target (PAL: 50 Hz timings). */
void homing_bomb_move_to_target_pal(u8 *moby, float *target)
{
    SibVector offset, velocity, delta, angles, rotation_input;
    float matrix[12] __attribute__((aligned(16)));
    u8 *vars;
    u8 *movement;
    u8 *position = moby + 0x10;
    float rate, elapsed;
    vars = *(u8 **)(moby + 0x68);
    FastVecSub(&offset, target, position);
    rate = g_bomb_rate * (0.00040000002f);
    elapsed = g_bomb_elapsed_param * (0.020000001f);
    movement = vars + 0x50;
    offset.value[2] = 0.0f;
    math_step_value_toward_target((float *)(moby + 0x18), (float *)(vars + 0x5C), *(float *)(vars + 0x60), rate, rate, elapsed);
    vec_scale_to_length(&velocity, &offset, elapsed);
    rotation_input.quad = 0;
    rotation_input.value[2] = *(float *)(vars + 0x64);
    angles.quad = rotation_input.quad;
    euler_rotation_basis(matrix, &angles);
    matrix_mul_vec3(&velocity, &velocity, matrix);
    FastVecSub(&delta, &velocity, movement);
    vec_clamp_length(delta.value, rate);
    FastVecAdd(movement, movement, &delta);
    FastVecAdd(position, position, movement);
}
