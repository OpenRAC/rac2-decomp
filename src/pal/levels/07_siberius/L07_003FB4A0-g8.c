#include "include_asm.h"

#include "common.h"
extern void *part_find_owned_effect_slot(u8 *, s32, s32);
extern f32 moby_update_aim_target_strength_pal(u8 *, s32);
extern f32 ApproachValue(f32 *, f32, f32);
extern void moby_set_state(u8 *, u8, s32);
extern f32 g_bomb_scale __attribute__((sda));
typedef struct { u8 pad[0x20]; f32 angle; u8 pad24[12]; u32 flags; } SpinnerState;

void homing_bomb_tick_fuse_pal(u8 *a0)
{
    SpinnerState *s1 = *(SpinnerState **)(a0 + 0x68);

    if (*(u8 *)(a0 + 0x20) == 0) {
        f32 scale;
        s1->flags = 0;
        scale = g_bomb_scale;
        *(f32 *)(a0 + 0x2C) = *(f32 *)(*(u8 **)(a0 + 0x24) + 0x24) * scale;
        moby_set_state(a0, 1, -1);
        *(u32 *)(a0 + 0x98) = 0;
        *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
        return;
    }
    {
        s32 id = part_find_owned_effect_slot(a0, 0x10000, 0);
        f32 angle = moby_update_aim_target_strength_pal(a0, id);
        ApproachValue(&s1->angle, 0.0f, angle);
    }
    if (s1->angle <= 0.0f)
        moby_set_state(a0, 3, -1);
    *(u8 *)(a0 + 0xA8) = 0xFF;
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
void func_PAL_L07_003FB570(u8 *self, float *target)
{
    SibVector offset, velocity, delta, angles, rotationInput;
    float matrix[12] __attribute__((aligned(16)));
    u8 *state;
    u8 *movement;
    u8 *position = self + 0x10;
    float rate, elapsed;
    state = *(u8 **)(self + 0x68);
    FastVecSub(&offset, target, position);
    rate = g_bomb_rate * (0.00040000002f);
    elapsed = g_bomb_elapsed_param * (0.020000001f);
    movement = state + 0x50;
    offset.value[2] = 0.0f;
    math_step_value_toward_target((float *)(self + 0x18), (float *)(state + 0x5C), *(float *)(state + 0x60), rate, rate, elapsed);
    vec_scale_to_length(&velocity, &offset, elapsed);
    rotationInput.quad = 0;
    rotationInput.value[2] = *(float *)(state + 0x64);
    angles.quad = rotationInput.quad;
    euler_rotation_basis(matrix, &angles);
    matrix_mul_vec3(&velocity, &velocity, matrix);
    FastVecSub(&delta, &velocity, movement);
    vec_clamp_length(delta.value, rate);
    FastVecAdd(movement, movement, &delta);
    FastVecAdd(position, position, movement);
}
