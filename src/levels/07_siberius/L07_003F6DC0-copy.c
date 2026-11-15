#include "common.h"
typedef int SibQuad __attribute__((mode(TI)));
typedef union { SibQuad quad; float value[4]; } SibVector;
extern float D_L07_001B0FE0 __attribute__((sda));
extern float D_L07_001B0FE4 __attribute__((sda));
extern void FastVecSub(void *, void *, void *);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void euler_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_clamp_length(float *, float);
extern void FastVecAdd(void *, void *, void *);
/* The incoming second pointer is live at the first vector subtraction. */
/* Moves the homing bomb toward a target point with smooth speed changes and turns it to face the way it moves. */
void homing_bomb_move_to_target(u8 *self, float *target)
{
    SibVector offset, velocity, delta, angles, rotationInput;
    float matrix[12] __attribute__((aligned(16)));
    u8 *state;
    u8 *movement;
    u8 *position = self + 0x10;
    float rate, elapsed;
    state = *(u8 **)(self + 0x68);
    FastVecSub(&offset, target, position);
    rate = D_L07_001B0FE0 * (1.0f / 3600.0f);
    elapsed = D_L07_001B0FE4 * (1.0f / 60.0f);
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
