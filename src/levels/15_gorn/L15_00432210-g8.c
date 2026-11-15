#include "common.h"
typedef int GornQuad __attribute__((mode(TI)));
typedef union { GornQuad q; float f[4]; } GornVector;
extern short D_L15_001B36A8[] MACRO_ADDR, D_L15_001B36B0[] MACRO_ADDR, D_L15_001B36B8[] MACRO_ADDR;
extern GornVector D_L15_00269FE0[4][10] NOT_SDA;
extern float D_L15_001B16B4 __attribute__((sda)), D_L15_001B16B8 __attribute__((sda)), D_L15_001B16C0 __attribute__((sda));
extern int func_00282978(short *);
extern float func_002A7878(float, float), func_002A78D8(float, float);
extern void func_00282CF0(void *, void *, void *), func_00282CC0(void *, void *, void *), func_00282F20(void *, void *, float);
extern void func_L00_0031AA28(void *, void *, void *, void *, void *, float);
/* For each of four channels whose timer expired: rearms it and rebuilds its jittered ten-point curves. */
void func_L15_00432210(void *moby)
{
    GornVector origin, tangent, point;
    char *vars = *(char **)((char *)moby + 0x68);
    int channel;
    for (channel = 0; channel < 4; channel++) {
        if (!FastDecTimer(&D_L15_001B36A8[channel]))
            continue;
        D_L15_001B36B0[channel] = 0;
        D_L15_001B36A8[channel] = D_L15_001B36B8[channel];
        qcopy(&origin, vars + 0x10);
        origin.f[0] += RandomFloatRange(-30, 30);
        origin.f[1] += RandomFloatRange(-30, 30);
        origin.f[2] += RandomFloatRange(-30, 30);
        qcopy(vars + 0x20, vars + 0x10);
        qcopy(vars + 0x30, vars + 0x10);
        qcopy(vars + 0x40, vars + 0x10);
        {
            float positive = 60.0f, negative = -60.0f;
            *(float *)(vars + 0x20) += RandomFloatRange(negative, positive);
            *(float *)(vars + 0x24) += RandomFloatRange(negative, positive);
            *(float *)(vars + 0x28) += RandomFloatRange(negative, positive);
            *(float *)(vars + 0x30) += RandomFloatRange(negative, positive);
            *(float *)(vars + 0x34) += RandomFloatRange(negative, positive);
            *(float *)(vars + 0x38) += RandomFloatRange(negative, positive);
            *(float *)(vars + 0x40) += RandomFloatRange(negative, positive);
            *(float *)(vars + 0x44) += RandomFloatRange(negative, positive);
            *(float *)(vars + 0x48) += RandomFloatRange(negative, positive);
        }
        FastVecSub(&tangent, &origin, vars);
        vec_scale_to_length(&tangent, &tangent, D_L15_001B16C0);
        FastVecAdd(&tangent, &origin, &tangent);
        {
            int i;

            for (i = 0; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                InterpolateCubicVector_L00(&point, vars, &origin, &tangent, &tangent, t);
                qcopy(&D_L15_00269FE0[channel][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &D_L15_00269FE0[0][i]);
                point.f[0] += RandomSignedFloatRange(0, D_L15_001B16B4);
                point.f[1] += RandomSignedFloatRange(0, D_L15_001B16B4);
                point.f[2] += RandomSignedFloatRange(0, D_L15_001B16B4);
                qcopy(&D_L15_00269FE0[0][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &D_L15_00269FE0[0][i]);
                point.f[0] += RandomSignedFloatRange(0, D_L15_001B16B8);
                point.f[1] += RandomSignedFloatRange(0, D_L15_001B16B8);
                point.f[2] += RandomSignedFloatRange(0, D_L15_001B16B8);
                qcopy(&D_L15_00269FE0[1][i], &point);
            }
        }
        {
            int i;

            for (i = 3; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                InterpolateCubicVector_L00(&point, vars, vars + 0x20, &tangent, &tangent, t);
                qcopy(&D_L15_00269FE0[channel][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &D_L15_00269FE0[0][i]);
                point.f[0] += RandomSignedFloatRange(0, D_L15_001B16B8);
                point.f[1] += RandomSignedFloatRange(0, D_L15_001B16B8);
                point.f[2] += RandomSignedFloatRange(0, D_L15_001B16B8);
                qcopy(&D_L15_00269FE0[2][i], &point);
            }
        }
        {
            int i;

            for (i = 6; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                InterpolateCubicVector_L00(&point, vars, vars + 0x30, &tangent, &tangent, t);
                qcopy(&D_L15_00269FE0[channel][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &D_L15_00269FE0[0][i]);
                point.f[0] += RandomSignedFloatRange(0, D_L15_001B16B8);
                point.f[1] += RandomSignedFloatRange(0, D_L15_001B16B8);
                point.f[2] += RandomSignedFloatRange(0, D_L15_001B16B8);
                qcopy(&D_L15_00269FE0[3][i], &point);
            }
        }
        {
            int i;

            for (i = 8; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                InterpolateCubicVector_L00(&point, vars, vars + 0x40, &tangent, &tangent, t);
                qcopy(&D_L15_00269FE0[channel][i], &point);
            }
        }
    }
}
