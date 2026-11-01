#include "include_asm.h"

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
void func_PAL_L15_00437E50(void *obj)
{
    GornVector origin, tangent, point;
    char *state = *(char **)((char *)obj + 0x68);
    int channel;
    for (channel = 0; channel < 4; channel++) {
        if (!func_00282978(&D_L15_001B36A8[channel]))
            continue;
        D_L15_001B36B0[channel] = 0;
        D_L15_001B36A8[channel] = ((s32)(D_L15_001B36B8[channel]) * 5 + 2) / 6;
        qcopy(&origin, state + 0x10);
        origin.f[0] += func_002A7878(-30, 30);
        origin.f[1] += func_002A7878(-30, 30);
        origin.f[2] += func_002A7878(-30, 30);
        qcopy(state + 0x20, state + 0x10);
        qcopy(state + 0x30, state + 0x10);
        qcopy(state + 0x40, state + 0x10);
        {
            float positive = 60.0f, negative = -60.0f;
            *(float *)(state + 0x20) += func_002A7878(negative, positive);
            *(float *)(state + 0x24) += func_002A7878(negative, positive);
            *(float *)(state + 0x28) += func_002A7878(negative, positive);
            *(float *)(state + 0x30) += func_002A7878(negative, positive);
            *(float *)(state + 0x34) += func_002A7878(negative, positive);
            *(float *)(state + 0x38) += func_002A7878(negative, positive);
            *(float *)(state + 0x40) += func_002A7878(negative, positive);
            *(float *)(state + 0x44) += func_002A7878(negative, positive);
            *(float *)(state + 0x48) += func_002A7878(negative, positive);
        }
        func_00282CF0(&tangent, &origin, state);
        func_00282F20(&tangent, &tangent, D_L15_001B16C0);
        func_00282CC0(&tangent, &origin, &tangent);
        {
            int i;

            for (i = 0; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                func_L00_0031AA28(&point, state, &origin, &tangent, &tangent, t);
                qcopy(&D_L15_00269FE0[channel][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &D_L15_00269FE0[0][i]);
                point.f[0] += func_002A78D8(0, D_L15_001B16B4);
                point.f[1] += func_002A78D8(0, D_L15_001B16B4);
                point.f[2] += func_002A78D8(0, D_L15_001B16B4);
                qcopy(&D_L15_00269FE0[0][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &D_L15_00269FE0[0][i]);
                point.f[0] += func_002A78D8(0, D_L15_001B16B8);
                point.f[1] += func_002A78D8(0, D_L15_001B16B8);
                point.f[2] += func_002A78D8(0, D_L15_001B16B8);
                qcopy(&D_L15_00269FE0[1][i], &point);
            }
        }
        {
            int i;

            for (i = 3; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                func_L00_0031AA28(&point, state, state + 0x20, &tangent, &tangent, t);
                qcopy(&D_L15_00269FE0[channel][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &D_L15_00269FE0[0][i]);
                point.f[0] += func_002A78D8(0, D_L15_001B16B8);
                point.f[1] += func_002A78D8(0, D_L15_001B16B8);
                point.f[2] += func_002A78D8(0, D_L15_001B16B8);
                qcopy(&D_L15_00269FE0[2][i], &point);
            }
        }
        {
            int i;

            for (i = 6; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                func_L00_0031AA28(&point, state, state + 0x30, &tangent, &tangent, t);
                qcopy(&D_L15_00269FE0[channel][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &D_L15_00269FE0[0][i]);
                point.f[0] += func_002A78D8(0, D_L15_001B16B8);
                point.f[1] += func_002A78D8(0, D_L15_001B16B8);
                point.f[2] += func_002A78D8(0, D_L15_001B16B8);
                qcopy(&D_L15_00269FE0[3][i], &point);
            }
        }
        {
            int i;

            for (i = 8; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                func_L00_0031AA28(&point, state, state + 0x40, &tangent, &tangent, t);
                qcopy(&D_L15_00269FE0[channel][i], &point);
            }
        }
    }
}
