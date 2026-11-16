#include "include_asm.h"
#include "common.h"

/* func_PAL_L05_00380258, the PAL copy of func_L05_0037DA58: the same C, where the duration is scaled
   to 50 Hz, 1.0f/60.0f becomes 0.020000001f and 0.002f becomes 0.0028800003f. */

extern float math_random_float_range(float, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
typedef unsigned int Quad37DA58 __attribute__((mode(TI)));
extern char g_origin_vec[];
extern void vec_scale_to_length(void *, void *, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern char *part_spawn_ground_effect(void *, int, float, float, int, int, int, void *, int, float);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern int FloatToInt(float);
extern unsigned char *g_particle_params_table[];

void func_PAL_L05_00380258(float *position, int count, int color, int duration)
{
    float velocity[4], point[4], direction[4], axis[4], half[4];
    float size, angle;
    int sign, i;
    char *particle;
    *(Quad37DA58 *)axis = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    FastVecSub(direction, g_origin_vec, position);
    vec_scale_to_length(half, direction, 0.5f);
    direction[2] = 0;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(0.5f, 2.0f);
        sign = math_random_int_below(2);
        if (!sign) --sign;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        vec_scale_to_length(velocity, velocity, math_random_float_range(0.05f, 3.0f) * 0.020000001f);
        velocity[2] = math_random_float_range(1.0f, 5.0f) * 0.020000001f;
        FastVecAdd(point, position, half);
        position[0] += math_random_signed_float_range(0, 0.15f);
        position[1] += math_random_signed_float_range(0, 0.15f);
        position[2] += math_random_signed_float_range(0, 0.15f);
        particle = part_spawn_ground_effect(position, ((s32)duration * 5 + 2) / 6, size * 0.1f, size, color, 0, sign, velocity, 0, 0.0028800003f);
        if (particle) {
            particle[2] = g_particle_params_table[0x61][6];
            particle[9] = FloatToInt(4.0f) + 0x70;
        }
        particle = part_spawn_ground_effect(position, ((s32)duration * 5 + 2) / 6, size * 0.07f, size * 0.7f, 0x7f7f7f7f, 1, -sign, velocity, 0, 0.0028800003f);
        if (particle) {
            particle[2] = g_particle_params_table[0x61][6];
            particle[9] = FloatToInt(4.0f) + 0x70;
        }
    }
}
