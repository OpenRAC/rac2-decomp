#include "include_asm.h"

#include "common.h"
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern char g_camera_l15_position[];
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern s32 g_ship_damage_effect_count[] __attribute__((sda));
extern s32 g_gorn_ship_damage_joints[] SDATA(D_L15_001B1780);
extern s32 g_gorn_ship_part_joints[] SDATA(D_L15_001B17B0);
extern u8 g_ship_sound_slots[];
extern s32 PlayMobySound(s32 a, s32 b, void *c);
extern s32 math_random_int_below(s32 a);
extern f32 math_random_float_range(f32 a, f32 b);
extern s32 FloatToInt(f32 a);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern int PlayMobySound(int, int, void *);
extern int g_tether_l15_active[] __attribute__((sda));
extern char g_camera_position[];
extern int math_random_int_below(int);
extern int func_001163B0(void);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern unsigned char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);

/* Spawns a burst of count sparks at pos, thrown out around the camera-facing axis with random size, speed and spin (PAL). */
void gorn_part_spawn_spark_burst_pal(char *pos, int count, int mode) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    FastVecSub(direction, g_camera_l15_position, (float *)pos);
    if (g_tether_l15_active[0] == 0) {
        direction[2] = 0.0f;
        axis[0] = 0.0f; axis[1] = 0.0f; axis[2] = 1.0f; axis[3] = 1.0f;
    } else {
        FastVecSub(extra, pos, g_camera_position);
        vec_scale_to_length(axis, extra, 1.0f);
        FastVecScale(extra, axis, FastVecDot(axis, direction));
        FastVecSub(direction, direction, extra);
    }
    for (i = 0; i < count; i++) {
        size = math_random_float_range(0.75f, 2.0f);
        sign = math_random_int_below(2);
        if (sign == 0)
            sign--;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        speed = math_random_float_range(0.05f, 3.0f) * (0.020000001f);
        vec_scale_to_length((char *)velocity, (char *)velocity, speed);
        velocity[2] = math_random_float_range(1.0f, 5.0f) * (0.020000001f);
        qcopy(point, pos);
        point[0] += math_random_signed_float_range(0.0f, 0.15f);
        point[1] += math_random_signed_float_range(0.0f, 0.15f);
        point[2] += math_random_signed_float_range(0.0f, 0.15f);
        if (mode == 0) {
            if (!(func_001163B0() & 1)) {
                FastVecScale(velocity, velocity, 1.5f);
                particle = part_spawn_ground_effect(point, 50, size * 0.35f, size, 0x7F800000, 0, sign, velocity, 0, 0.0028800003f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 50, size * 0.245f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.0028800003f);
            } else {
                FastVecSub(extra, g_camera_l15_position, point);
                vec_scale_to_length((char *)extra, (char *)extra, speed);
                FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
                particle = part_spawn_ground_effect(point, 33, size * 2.05f, size, 0x7F800000, 0, sign, velocity, 0, 0.0028800003f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 33, size * 1.43500006f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.0028800003f);
            }
        } else {
            if (!(func_001163B0() & 1)) {
                FastVecScale(velocity, velocity, 1.5f);
                particle = part_spawn_ground_effect(point, 50, size * 0.3f, size, 0x7F800000, 0, sign, velocity, 0, 0.0028800003f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 50, size * 0.21000000834465027f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.0028800003f);
            } else {
                FastVecSub(extra, g_camera_l15_position, point);
                vec_scale_to_length((char *)extra, (char *)extra, speed);
                FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
                particle = part_spawn_ground_effect(point, 33, size * 0.25f, size, 0x7F800000, 0, sign, velocity, 0, 0.0028800003f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 33, size * 0.175f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.0028800003f);
            }
        }
        if (particle)
            particle[9] = FloatToInt(4.0f) + 0x70;
    }
}
