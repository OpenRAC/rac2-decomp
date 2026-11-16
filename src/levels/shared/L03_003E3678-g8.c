#include "common.h"

extern f32 math_step_value_toward_target(void *, void *, f32, f32, f32, f32);
extern void vec_fast_normalize3(void *, void *, void *, f32);
extern void quaternion_to_rotation_basis(void *, void *);
extern f32 g_path_puzzle_turn_rate_a __attribute__((sda));
extern f32 g_path_puzzle_turn_rate_b __attribute__((sda));
extern f32 g_path_puzzle_turn_speed __attribute__((sda));
extern f32 g_puzzle_rotation_quat[] __attribute__((sda));
extern f32 g_puzzle_target_quat[] __attribute__((sda));

/* Smoothly turns the puzzle to its new orientation and marks the turn as done when it arrives. */
void path_puzzle_animate_turn(u8 *object)
{
    f32 quaternion[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(object + 0x68);
    math_step_value_toward_target(vars + 0x4C, vars + 0x48, 1.0f,
                 g_path_puzzle_turn_rate_a * 0.00027777778450399637f,
                 g_path_puzzle_turn_rate_b * 0.00027777778450399637f,
                 g_path_puzzle_turn_speed * 0.01666666753590107f);
    vec_fast_normalize3(quaternion, g_puzzle_rotation_quat, g_puzzle_target_quat,
                 *(f32 *)(vars + 0x4C));
    quaternion_to_rotation_basis(quaternion, object + 0xC0);
    if (1.0f <= *(f32 *)(vars + 0x4C)) {
        *(short *)(vars + 0x56) = 1;
        qcopy(g_puzzle_rotation_quat, g_puzzle_target_quat);
    }
}
