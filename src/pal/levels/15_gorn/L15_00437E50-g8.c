#include "include_asm.h"

#include "common.h"
typedef int GornQuad __attribute__((mode(TI)));
typedef union { GornQuad q; float f[4]; } GornVector;
extern short D_L15_001B36A8[] MACRO_ADDR, D_L15_001B36B0[] MACRO_ADDR, D_L15_001B36B8[] MACRO_ADDR;
extern GornVector D_L15_00269FE0[4][10] NOT_SDA;
extern float D_L15_001B16B4 __attribute__((sda)), D_L15_001B16B8 __attribute__((sda)), D_L15_001B16C0 __attribute__((sda));
extern int FastDecTimer(short *);
extern float math_random_float_range(float, float), math_random_signed_float_range(float, float);
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *), vec_scale_to_length(void *, void *, float);
extern void math_l00_interpolate_cubic_vector(void *, void *, void *, void *, void *, float);

/* For each of four channels whose timer expired: rearms it and rebuilds its jittered ten-point curves. */
void func_PAL_L15_00437E50(void *obj)
{
    GornVector origin, tangent, point;
    char *state = *(char **)((char *)obj + 0x68);
    int channel;
    for (channel = 0; channel < 4; channel++) {
        if (!FastDecTimer(&D_L15_001B36A8[channel]))
            continue;
        D_L15_001B36B0[channel] = 0;
        D_L15_001B36A8[channel] = ((s32)(D_L15_001B36B8[channel]) * 5 + 2) / 6;
        qcopy(&origin, state + 0x10);
        origin.f[0] += math_random_float_range(-30, 30);
        origin.f[1] += math_random_float_range(-30, 30);
        origin.f[2] += math_random_float_range(-30, 30);
        qcopy(state + 0x20, state + 0x10);
        qcopy(state + 0x30, state + 0x10);
        qcopy(state + 0x40, state + 0x10);
        {
            float positive = 60.0f, negative = -60.0f;
            *(float *)(state + 0x20) += math_random_float_range(negative, positive);
            *(float *)(state + 0x24) += math_random_float_range(negative, positive);
            *(float *)(state + 0x28) += math_random_float_range(negative, positive);
            *(float *)(state + 0x30) += math_random_float_range(negative, positive);
            *(float *)(state + 0x34) += math_random_float_range(negative, positive);
            *(float *)(state + 0x38) += math_random_float_range(negative, positive);
            *(float *)(state + 0x40) += math_random_float_range(negative, positive);
            *(float *)(state + 0x44) += math_random_float_range(negative, positive);
            *(float *)(state + 0x48) += math_random_float_range(negative, positive);
        }
        FastVecSub(&tangent, &origin, state);
        vec_scale_to_length(&tangent, &tangent, D_L15_001B16C0);
        FastVecAdd(&tangent, &origin, &tangent);
        {
            int i;

            for (i = 0; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                math_l00_interpolate_cubic_vector(&point, state, &origin, &tangent, &tangent, t);
                qcopy(&D_L15_00269FE0[channel][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &D_L15_00269FE0[0][i]);
                point.f[0] += math_random_signed_float_range(0, D_L15_001B16B4);
                point.f[1] += math_random_signed_float_range(0, D_L15_001B16B4);
                point.f[2] += math_random_signed_float_range(0, D_L15_001B16B4);
                qcopy(&D_L15_00269FE0[0][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &D_L15_00269FE0[0][i]);
                point.f[0] += math_random_signed_float_range(0, D_L15_001B16B8);
                point.f[1] += math_random_signed_float_range(0, D_L15_001B16B8);
                point.f[2] += math_random_signed_float_range(0, D_L15_001B16B8);
                qcopy(&D_L15_00269FE0[1][i], &point);
            }
        }
        {
            int i;

            for (i = 3; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                math_l00_interpolate_cubic_vector(&point, state, state + 0x20, &tangent, &tangent, t);
                qcopy(&D_L15_00269FE0[channel][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &D_L15_00269FE0[0][i]);
                point.f[0] += math_random_signed_float_range(0, D_L15_001B16B8);
                point.f[1] += math_random_signed_float_range(0, D_L15_001B16B8);
                point.f[2] += math_random_signed_float_range(0, D_L15_001B16B8);
                qcopy(&D_L15_00269FE0[2][i], &point);
            }
        }
        {
            int i;

            for (i = 6; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                math_l00_interpolate_cubic_vector(&point, state, state + 0x30, &tangent, &tangent, t);
                qcopy(&D_L15_00269FE0[channel][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &D_L15_00269FE0[0][i]);
                point.f[0] += math_random_signed_float_range(0, D_L15_001B16B8);
                point.f[1] += math_random_signed_float_range(0, D_L15_001B16B8);
                point.f[2] += math_random_signed_float_range(0, D_L15_001B16B8);
                qcopy(&D_L15_00269FE0[3][i], &point);
            }
        }
        {
            int i;

            for (i = 8; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                math_l00_interpolate_cubic_vector(&point, state, state + 0x40, &tangent, &tangent, t);
                qcopy(&D_L15_00269FE0[channel][i], &point);
            }
        }
    }
}
