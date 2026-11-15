#include "names.h"
/* func_PAL_00320D00, the PAL copy of func_0031F6E8: the same C, where the 60 Hz step 1/60 becomes 0.020000001f, the lifetimes 60 and 40 become 50 and 33, and the last particle argument gains a * 1.44f. */
#include "common.h"
extern float g_camera_eye_state[]; extern char D_00189ED0[];
extern int D_001A8CA0;
extern float D_001AFE0C __attribute__((sda));
extern float D_001AFE10 __attribute__((sda));
extern float D_001AFE14 __attribute__((sda));
extern float D_001AFE18 __attribute__((sda));
extern float D_001AFE1C __attribute__((sda));
extern float D_001AFE20 __attribute__((sda));
extern float D_001AFE24 __attribute__((sda));
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
void func_PAL_00320D00(char *pos, int count, int mode) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    FastVecSub(direction, g_camera_eye_state, (float *)pos);
    if (D_001A8CA0 == 0) {
        direction[2] = 0.0f;
        axis[0] = 0.0f; axis[1] = 0.0f; axis[2] = 1.0f; axis[3] = 1.0f;
    } else {
        FastVecSub(extra, pos, D_00189ED0);
        vec_scale_to_length(axis, extra, 1.0f);
        FastVecScale(extra, axis, FastVecDot(axis, direction));
        FastVecSub(direction, direction, extra);
    }
    for (i = 0; i < count; i++) {
        size = math_random_float_range(D_001AFE20, D_001AFE24);
        sign = math_random_int_below(2);
        if (sign == 0)
            sign--;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        speed = math_random_float_range(D_001AFE0C, D_001AFE10) * 0.020000001f;
        vec_scale_to_length((char *)velocity, (char *)velocity, speed);
        velocity[2] = math_random_float_range(D_001AFE14, D_001AFE18) * 0.020000001f;
        qcopy(point, pos);
        point[0] += math_random_signed_float_range(0.0f, 0.15f);
        point[1] += math_random_signed_float_range(0.0f, 0.15f);
        point[2] += math_random_signed_float_range(0.0f, 0.15f);
        if (mode == 0) {
            if (!(func_001163B0() & 1)) {
                FastVecScale(velocity, velocity, 1.5f);
                particle = part_spawn_ground_effect(point, 50, size * 0.35f, size, 0x7F800000, 0, sign, velocity, 1, D_001AFE1C * 1.44f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 50, size * 0.245f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 1, D_001AFE1C * 1.44f);
            } else {
                FastVecSub(extra, g_camera_eye_state, point);
                vec_scale_to_length((char *)extra, (char *)extra, speed);
                FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
                particle = part_spawn_ground_effect(point, 33, size * 2.05f, size, 0x7F800000, 0, sign, velocity, 1, D_001AFE1C * 1.44f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 33, size * 1.43500006f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 1, D_001AFE1C * 1.44f);
            }
        } else {
            if (!(func_001163B0() & 1)) {
                FastVecScale(velocity, velocity, 1.5f);
                particle = part_spawn_ground_effect(point, 50, size * 0.3f, size, 0x7F800000, 0, sign, velocity, 1, D_001AFE1C * 1.44f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 50, size * 0.21000000834465027f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 1, D_001AFE1C * 1.44f);
            } else {
                FastVecSub(extra, g_camera_eye_state, point);
                vec_scale_to_length((char *)extra, (char *)extra, speed);
                FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
                particle = part_spawn_ground_effect(point, 33, size * 0.25f, size, 0x7F800000, 0, sign, velocity, 1, D_001AFE1C * 1.44f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 33, size * 0.175f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 1, D_001AFE1C * 1.44f);
            }
        }
        if (particle)
            particle[9] = FloatToInt(4.0f) + 0x70;
    }
}
