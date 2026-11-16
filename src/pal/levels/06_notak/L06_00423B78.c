#include "include_asm.h"

#include "common.h"
extern void FastVecSub(char *, char *, char *);
extern void FastVecAdd(char *, char *, char *);
extern int FloatToInt(float);
extern void vec_scale_to_length(char *, char *, float);
extern int math_random_int_below(int);
extern char g_hero_l06_position[];
extern int math_random_int_below(int);
extern float math_random_signed_float_range(float, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);

void part_spawn_colored_burst_pal(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    FastVecSub((char *)direction, (char *)g_hero_l06_position, (char *)pos);
    vec_scale_to_length((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(0.5f, 2.0f);
        sign = math_random_int_below(2);
        if (!sign) sign--;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        vec_scale_to_length((char *)velocity, (char *)velocity, math_random_float_range(0.05f, 3.0f) * 0.020000001f);
        velocity[2] = math_random_float_range(1.0f, 5.0f) * 0.020000001f;
        FastVecAdd((char *)origin, (char *)pos, (char *)offset);
        pos[0] += math_random_signed_float_range(0, 0.15f);
        pos[1] += math_random_signed_float_range(0, 0.15f);
        pos[2] += math_random_signed_float_range(0, 0.15f);
        particle = part_spawn_ground_effect(origin, 17, size * 0.1f, size, 0x7F801010, 0, sign, velocity, 0, 0.0028800003f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
        particle = part_spawn_ground_effect(origin, 17, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.0028800003f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
    }
}


extern void moby_set_state(char *, int, int);
extern int math_fast_float_d(char *);
extern void func_PAL_002A7E68(char *, int, int, int);

void actor_choose_idle_anim_pal(char *a0)
{
    char *o = *(char **)(a0 + 0x68);

    if (*(int *)(o + 0x5A0) == 1) {
        if (*(int *)(o + 0x23C) == -1) {
            if (math_fast_float_d(o + 0x25C)) {
                moby_set_state(a0, 7, 2);
                if (*(unsigned char *)(a0 + 0x43) != 0x13) {
                    func_PAL_002A7E68(a0, 0x13, 0, 17);
                }
                o[0x48] = FloatToInt(20.0f);
                o[0x4A] = FloatToInt(24.0f);
            }
        } else {
            moby_set_state(a0, 8, 2);
            if (*(unsigned char *)(a0 + 0x43) != 0x12) {
                func_PAL_002A7E68(a0, 0x12, 0, 17);
            }
            o[0x48] = FloatToInt(20.0f);
            o[0x4A] = FloatToInt(24.0f);
        }
    } else if (*(short *)(o + 0x492) != 0 && math_fast_float_d(o + 0x25C)) {
        *(short *)(o + 0x492) = 0;
        moby_set_state(a0, 7, 2);
        if (!math_random_int_below(2)) {
            if (*(unsigned char *)(a0 + 0x43) != 0x11) {
                func_PAL_002A7E68(a0, 0x11, 0, 17);
            }
            o[0x48] = FloatToInt(20.0f);
            o[0x4A] = FloatToInt(24.0f);
        } else {
            if (*(unsigned char *)(a0 + 0x43) != 0x13) {
                func_PAL_002A7E68(a0, 0x13, 0, 17);
            }
            o[0x48] = FloatToInt(20.0f);
            o[0x4A] = FloatToInt(24.0f);
        }
    } else if (*(short *)(o + 0x492) == 0 && math_fast_float_d(o + 0x25C)) {
        moby_set_state(a0, 9, 2);
        if (*(unsigned char *)(a0 + 0x43) != 0x12) {
            func_PAL_002A7E68(a0, 0x12, 0, 17);
        }
        o[0x48] = FloatToInt(20.0f);
        o[0x4A] = FloatToInt(24.0f);
    }
}

