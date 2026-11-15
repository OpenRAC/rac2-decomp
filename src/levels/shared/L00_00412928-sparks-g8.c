#include "common.h"
extern char D_L00_001B8C80[]; extern char D_00189ED0[];
extern int D_L00_001A8FF0;
extern float D_L00_001B1344 __attribute__((sda));
extern float D_L00_001B1348 __attribute__((sda));
extern float D_L00_001B134C __attribute__((sda));
extern float D_L00_001B1350 __attribute__((sda));
extern float D_L00_001B135C __attribute__((sda));
extern float D_L00_001B1354 __attribute__((sda));
extern float D_L00_001B1358 __attribute__((sda));
extern void FastVecSub(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecScale(void *,void *,float);
extern float FastVecDot(void *,void *);
extern float math_random_float_range(float,float),math_random_signed_float_range(float,float);
extern int math_random_int_below(int);
extern int func_001163B0(void);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern unsigned char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int FloatToInt(float);
/* Emit paired particles, either outward or toward the camera. */
/* Throws out pairs of sparks from a point. They fly sideways or toward the camera, depending on the mode. */
void part_emit_spark_particle_pairs(char *pos, int count, int mode) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    FastVecSub(direction, D_L00_001B8C80+0x140, (float *)pos);
    if (D_L00_001A8FF0 == 0) {
        direction[2] = 0.0f;
        axis[0] = 0.0f; axis[1] = 0.0f; axis[2] = 1.0f; axis[3] = 1.0f;
    } else {
        FastVecSub(extra, pos, D_00189ED0);
        vec_scale_to_length(axis, extra, 1.0f);
        FastVecScale(extra, axis, FastVecDot(axis, direction));
        FastVecSub(direction, direction, extra);
    }
    for (i = 0; i < count; i++) {
        size = math_random_float_range(D_L00_001B1358, D_L00_001B135C);
        sign = math_random_int_below(2);
        if (sign == 0)
            sign--;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        speed = math_random_float_range(D_L00_001B1344, D_L00_001B1348) * (1.0f / 60.0f);
        vec_scale_to_length((char *)velocity, (char *)velocity, speed);
        velocity[2] = math_random_float_range(D_L00_001B134C, D_L00_001B1350) * (1.0f / 60.0f);
        qcopy(point, pos);
        point[0] += math_random_signed_float_range(0.0f, 0.15f);
        point[1] += math_random_signed_float_range(0.0f, 0.15f);
        point[2] += math_random_signed_float_range(0.0f, 0.15f);
        if (mode == 0) {
            if (!(func_001163B0() & 1)) {
                FastVecScale(velocity, velocity, 1.5f);
                particle = part_spawn_ground_effect(point, 60, size * 0.35f, size, 0x7F800000, 0, sign, velocity, 0, D_L00_001B1354);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 60, size * 0.245f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, D_L00_001B1354);
            } else {
                FastVecSub(extra, D_L00_001B8C80+0x140, point);
                vec_scale_to_length((char *)extra, (char *)extra, speed);
                FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
                particle = part_spawn_ground_effect(point, 40, size * 2.05f, size, 0x7F800000, 0, sign, velocity, 0, D_L00_001B1354);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 40, size * 1.43500006f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, D_L00_001B1354);
            }
        } else {
            if (!(func_001163B0() & 1)) {
                FastVecScale(velocity, velocity, 1.5f);
                particle = part_spawn_ground_effect(point, 60, size * 0.3f, size, 0x7F800000, 0, sign, velocity, 0, D_L00_001B1354);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 60, size * 0.21000000834465027f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, D_L00_001B1354);
            } else {
                FastVecSub(extra, D_L00_001B8C80+0x140, point);
                vec_scale_to_length((char *)extra, (char *)extra, speed);
                FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
                particle = part_spawn_ground_effect(point, 40, size * 0.25f, size, 0x7F800000, 0, sign, velocity, 0, D_L00_001B1354);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 40, size * 0.175f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, D_L00_001B1354);
            }
        }
        if (particle)
            particle[9] = FloatToInt(4.0f) + 0x70;
    }
}
