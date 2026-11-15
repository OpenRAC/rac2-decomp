#include "names.h"
/* func_PAL_L00_003EE450, the PAL copy of func_L00_003EA188: the same C, where the lifetime 60 becomes 50, 1/60 becomes 0.020000001f and the brightness is scaled by 1.44. */
#include "common.h"

/* The unsized macro-address view preserves the absolute flag load at -G8. */
extern float g_camera_l00_position[4];
extern float D_00189ED0[4];
extern int D_L00_001A8FF0[] MACRO_ADDR;
extern float D_L00_001B06E4 __attribute__((sda));
extern float D_L00_001B06E8 __attribute__((sda));
extern float D_L00_001B06EC __attribute__((sda));
extern float D_L00_001B06F0 __attribute__((sda));
extern float D_L00_001B06F8 __attribute__((sda));
extern float D_L00_001B06FC __attribute__((sda));
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
typedef int VectorBits __attribute__((mode(TI)));
extern void vec_clear_128(VectorBits *);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, float, int);
extern int FloatToInt(float);


void func_PAL_L00_003EE450(void *position, int count, float brightness)
{
    float velocity[4], lateral[4], axis[4], projected[4];
    FastVecSub(lateral, g_camera_l00_position, position);
    if (D_L00_001A8FF0[0] == 0) {
        lateral[2] = 0.0f;
        axis[0] = 0.0f;
        axis[1] = 0.0f;
        axis[3] = axis[2] = 1.0f;
    } else {
        FastVecSub(projected, position, D_00189ED0);
        vec_scale_to_length(axis, projected, 1.0f);
        FastVecScale(projected, axis, FastVecDot(axis, lateral));
        FastVecSub(lateral, lateral, projected);
    }
    if (count > 0) {
        do {
            char *particle;
            float angle;
            float scaled;
            float size = math_random_float_range(D_L00_001B06F8, D_L00_001B06FC);
            int spin = math_random_int_below(2);
            if (!spin)
                spin--;
            angle = math_random_float_range(-1.0471977f, 1.0471977f);
            math_apply_axis_rotation_to_quat(velocity, lateral, axis, angle);
            vec_scale_to_length(velocity, velocity, math_random_float_range(D_L00_001B06E4, D_L00_001B06E8) * 0.020000001f);
            velocity[2] = math_random_float_range(D_L00_001B06EC, D_L00_001B06F0) * 0.020000001f;
            vec_clear_128((VectorBits *)velocity);
            scaled = brightness * 1.44f;
            particle = part_spawn_ground_effect(position, 50, size * 0.1f, size,
                                     0x7F7F2020, 0, spin, velocity, scaled, 1);
            if (particle)
                *(unsigned char *)(particle + 9) = FloatToInt(4.0f) + 0x70;
            particle = part_spawn_ground_effect(position, 50, size * 0.07f, size * 0.7f,
                                     0x7FFF4040, 1, -spin, velocity, scaled, 1);
            if (particle)
                *(unsigned char *)(particle + 9) = FloatToInt(4.0f) + 0x70;
        } while (--count);
    }
}
