#include "include_asm.h"

#include "common.h"
extern char *g_blast_l00_pool __attribute__((sda));
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern void math_apply_axis_rotation_to_quat(char *, char *, char *, float);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);

/* Allocate an owner-tagged effect record and initialize its mode-specific fields. */
char *func_PAL_L00_003EA9F8(char *rec, int mode, float amount, char *pos)
{
    char v[16] __attribute__((aligned(16)));
    char w[16] __attribute__((aligned(16)));
    char *p;
    char *base = g_blast_l00_pool;
    int i;
    int z = 0;
    float zero = (float)z;
    for (i = 0; i < 320; i++) {
        if (*(int *)(base + i * 128 + 124) != 0) continue;
        switch (mode) {
        case 0:
            if (++*(int *)(rec + 64) == 150) {
                --*(int *)(rec + 64);
                return 0;
            }
            break;
        case 1:
            if (++*(int *)(rec + 68) == 150) {
                --*(int *)(rec + 68);
                return 0;
            }
            break;
        }
        p = g_blast_l00_pool + i * 128;
        *(char **)(p + 124) = rec;
        ++*(int *)(rec + 56);
        {
            int color = math_random_int_range(95, 127);
            *(int *)(p + 120) = mode;
            *(int *)(p + 96) = color;
            *(int *)(p + 92) = color;
        }
        if (mode == 0) {
            int color;
            math_apply_axis_rotation_to_quat(p + 16, rec + 16, rec, math_random_angle());
            *(float *)(p + 60) = *(float *)(p + 56) = *(float *)(rec + 60) * math_random_float_range(zero, 1.25f);
            *(float *)(p + 64) = zero;
            color = math_random_int_range(0, 13);
            *(int *)(p + 108) = (color << 16) + (color << 8) + color;
            *(float *)(p + 72) = *(float *)(p + 68) = math_random_float_range(0.25f, 0.35f);
            *(float *)(p + 76) = math_random_float_range(0.75f, 1.0f);
            *(float *)(p + 36) = zero;
            *(int *)(p + 88) = *(int *)(p + 84) = math_random_int_range(83, 100);
            qcopy(p, *(char **)(p + 124) + 32);
            vec_scale_to_length(v, p + 16, math_random_float_range(0.15f, 0.75f));
            FastVecAdd(p, v, p);
            *(int *)(p + 112) = 2;
            goto zero_angle;
        } else if (mode == 1) {
            int color;
            math_apply_axis_rotation_to_quat(p + 16, rec + 16, rec, math_random_angle());
            *(float *)(p + 56) = zero;
            *(float *)(p + 60) = zero;
            *(float *)(p + 64) = zero;
            color = math_random_int_range(0, 13);
            *(int *)(p + 108) = (color << 16) + (color << 8) + color;
            *(float *)(p + 72) = *(float *)(p + 68) = math_random_float_range(0.25f, 0.5f);
            *(float *)(p + 76) = math_random_float_range(1.0f, 1.5f);
            *(float *)(p + 36) = math_random_float_range(0.080000006f, 0.10000001f);
            *(int *)(p + 88) = *(int *)(p + 84) = math_random_int_range(83, 100);
            qcopy(p, pos);
            *(int *)(p + 112) = 2;
zero_angle:
            *(float *)(p + 48) = zero;
        } else if (mode == 2) {
            int color;
            math_apply_axis_rotation_to_quat(p + 16, rec + 16, rec, amount);
            *(float *)(p + 56) = zero;
            *(float *)(p + 60) = zero;
            *(float *)(p + 64) = zero;
            color = math_random_int_range(1, 10);
            *(int *)(p + 108) = (color << 16) + (color << 8) + color;
            *(float *)(p + 72) = *(float *)(p + 68) = math_random_float_range(0.15f, 0.25f) * 0.5f;
            *(float *)(p + 76) = math_random_float_range(0.5f, 0.8f) * 1.15f;
            *(float *)(p + 36) = 0.07000001f;
            *(int *)(p + 88) = *(int *)(p + 84) = 75;
            vec_scale_to_length(v, *(char **)(p + 124), 0.2f);
            FastVecAdd(p, *(char **)(p + 124) + 32, v);
            vec_scale_to_length(w, p + 16, 0.75f);
            FastVecAdd(p, w, p);
            *(float *)(p + 48) = math_random_signed_float_range(0.062831864f, 0.12566373f);
            *(int *)(p + 112) = mode;
        }
        *(float *)(p + 32) = 0.00080000004f;
        *(int *)(p + 104) = *(int *)(p + 100) = 0x103080;
        *(float *)(p + 44) = *(float *)(p + 40) = math_random_signed_float_range(0.37699118f, 0.42760575f);
        *(float *)(p + 52) = math_random_angle();
        *(int *)(p + 116) = 0;
        return p;
    }
    return 0;
}
