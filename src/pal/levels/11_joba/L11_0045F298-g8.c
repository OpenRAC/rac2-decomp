#include "common.h"

/* func_PAL_L11_0045F298, the PAL copy of func_L11_00459640: the same C at 50 Hz, where 1.0f / 60.0f
   becomes 0.020000001f, the lifetimes 60, 40, (10, 20) and (25, 60) become 50, 33, (8, 17) and
   (21, 50), and D_L11_001B1FF0 gains a factor of 1.44f (1.2 squared). */

extern void FastVecSub(void *, void *, void *);
extern float math_random_angle(void);
extern int math_random_int_range(int a0, int a1);
extern float math_random_float_range(float a, float b);
extern float math_random_signed_float_range(float, float);
extern void vec_scale_to_length(char *a0, void *a1, float f12);
extern void FastVecScale(char *a0, void *a1, float f12);
extern void FastVecAdd(void *a0, void *a1, void *a2);
extern int func_001163B0(void);
extern int math_random_int_below(int);
extern int FloatToInt(float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern char *part_spawn_ground_effect(void *, int, int, float, float, float, int, int, void *, int);
extern void *part_spawn_spinning_particle(void *, void *, int, int, float, float, int, int, int, int, int);
extern char D_L11_001BA8C0[];
extern float D_L11_001B1FE0 __attribute__((sda));
extern float D_L11_001B1FE4 __attribute__((sda));
extern float D_L11_001B1FE8 __attribute__((sda));
extern float D_L11_001B1FEC __attribute__((sda));
extern float D_L11_001B1FF0 __attribute__((sda));
extern float D_L11_001B1FF4 __attribute__((sda));
extern float D_L11_001B1FF8 __attribute__((sda));
extern int D_L11_001B2000 __attribute__((sda));
extern int D_L11_001B2004 __attribute__((sda));

void func_PAL_L11_0045F298(float *p, int count, int mode)
{
    float vel[4], pos[4], axis[4], up[4], a[4], b[4], out[4];
    int i, j, sign;
    char *effect;
    float size, speed, angle, r;

    FastVecSub(axis, D_L11_001BA8C0, p);
    axis[2] = 0;
    up[0] = 0;
    up[1] = 0;
    up[2] = 1;
    up[3] = 1;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(D_L11_001B1FF4, D_L11_001B1FF8);
        sign = math_random_int_below(2);
        if (!sign)
            --sign;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(vel, axis, up, angle);
        speed = math_random_float_range(D_L11_001B1FE0, D_L11_001B1FE4) * 0.020000001f;
        vec_scale_to_length((char *)vel, vel, speed);
        vel[2] = math_random_float_range(D_L11_001B1FE8, D_L11_001B1FEC) * 0.020000001f;
        qcopy(pos, p);
        pos[0] += math_random_signed_float_range(0, 0.15f);
        pos[1] += math_random_signed_float_range(0, 0.15f);
        pos[2] += math_random_signed_float_range(0, 0.15f);
        if (!mode) {
            if (!(func_001163B0() & 1)) {
                FastVecScale((char *)vel, vel, 1.5f);
                effect = part_spawn_ground_effect(pos, 50, D_L11_001B2000, size * 0.35f, size, D_L11_001B1FF0 * 1.44f, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = part_spawn_ground_effect(pos, 50, D_L11_001B2004, size * 0.245f, size * 0.7f, D_L11_001B1FF0 * 1.44f, 1, -sign, vel, 0);
            } else {
                FastVecSub(a, D_L11_001BA8C0, pos);
                vec_scale_to_length((char *)a, a, speed);
                FastVecAdd(vel, vel, a);
                effect = part_spawn_ground_effect(pos, 33, D_L11_001B2000, size * 2.05f, size, D_L11_001B1FF0 * 1.44f, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = part_spawn_ground_effect(pos, 33, D_L11_001B2004, size * 1.4350000619888306f, size * 0.7f, D_L11_001B1FF0 * 1.44f, 1, -sign, vel, 0);
            }
        } else {
            if (!(func_001163B0() & 1)) {
                FastVecScale((char *)vel, vel, 1.5f);
                effect = part_spawn_ground_effect(pos, 50, D_L11_001B2000, size * 0.3f, size, D_L11_001B1FF0 * 1.44f, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = part_spawn_ground_effect(pos, 50, D_L11_001B2004, size * (0.3f * 0.7f), size * 0.7f, D_L11_001B1FF0 * 1.44f, 1, -sign, vel, 0);
            } else {
                FastVecSub(a, D_L11_001BA8C0, pos);
                vec_scale_to_length((char *)a, a, speed);
                FastVecAdd(vel, vel, a);
                effect = part_spawn_ground_effect(pos, 33, D_L11_001B2000, size * 0.25f, size, D_L11_001B1FF0 * 1.44f, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = part_spawn_ground_effect(pos, 33, D_L11_001B2004, size * 0.175f, size * 0.7f, D_L11_001B1FF0 * 1.44f, 1, -sign, vel, 0);
            }
        }
        if (effect)
            effect[9] = FloatToInt(4.0f) + 112;
    }
    for (j = 1; j >= 0; j--) {
        angle = math_random_float_range(-0.9599312f, -1.3962636f);
        r = math_random_angle();
        vec_build_spherical_offset(a, math_random_float_range(0, 0.5f) * 0.020000001f, r, angle);
        FastVecSub(b, D_L11_001BA8C0, p);
        vec_scale_to_length((char *)b, b, 0.15f);
        FastVecAdd(p, p, b);
        size = math_random_float_range(30000, 60000);
        out[0] = p[0] + math_random_signed_float_range(0, 0.15f);
        out[1] = p[1] + math_random_signed_float_range(0, 0.15f);
        out[2] = p[2] + math_random_signed_float_range(0, 0.15f);
        if (mode)
            part_spawn_spinning_particle(out, a, 0x4F93E5FF, 0x102434EE, size, 0.5f, math_random_int_range(8, 17), 1, -1, -1, 0);
        else
            part_spawn_spinning_particle(out, a, 0x4F93E5FF, 0x102434EE, size, 0.5f, math_random_int_range(21, 50), 1, -1, -1, 0);
    }
}
