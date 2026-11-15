#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
extern int func_00283CF0(float);
extern void func_L08_00425398(char *);
extern float func_L08_0032EF80(void *, int, int, int, int);
extern void func_L01_003377C8(void *);
extern float func_L08_00425328(void *, float, float, float);
extern int func_L08_003D3D80(void *);
extern void func_0026FEB8(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern int *D_L08_001FE7C0[];
extern char D_L08_001B1BD0[];

/* Fills the 0x68 context with its timing and animation defaults, sets the record's height from
   the sweep below it when the context has none, and updates the shared counters at +0x1F8..+0x200. */
void func_L08_00425AA8(char *moby) {
    float probe[4];
    char *vars = *(char **)(moby + 0x68);
    float floorHeight;
    *(u8 *)(vars + 0x48) = FloatToInt(40.0f);
    *(u8 *)(vars + 0x4A) = FloatToInt(64.0f);
    *(u8 *)(vars + 0x29) = 1;
    qcopy(vars + 0x170, moby + 0x10);
    *(float *)(vars + 0x208) = *(float *)(moby + 0xF8);
    UpdateGroundHeightProbe(moby);
    if (*(u8 *)(moby + 0x21) != 255 && **(int **)(vars + 0x200) != 0x4CB2F) {
        **(int **)(vars + 0x1FC) = 0;
        **(int **)(vars + 0x1F8) = 0;
        **(int **)(vars + 0x200) = 0x4CB2F;
    }
    *(u8 *)(vars + 0x20E) = *(u8 *)(moby + 0x30);
    *(Quad *)probe = *(Quad *)(moby + 0x10);
    floorHeight = ComputePointDepthInVolumes(probe, *(int *)(vars + 0x1D0), -1, *(int *)(vars + 0x1D4), -1);
    if (floorHeight > 0.0f) *(u8 *)(moby + 0x30) = FloatToInt(floorHeight + 2.0f);
    *(u8 *)(vars + 0x20E) = *(u8 *)(vars + 0x20F) = *(u8 *)(moby + 0x30);
    *(Quad *)probe = *(Quad *)(moby + 0x10);
    floorHeight = ComputePointDepthInVolumes(probe, *(int *)(vars + 0x1D8), *(int *)(vars + 0x1E0), *(int *)(vars + 0x1DC), -1);
    if (floorHeight > 0.0f) *(u8 *)(vars + 0x20E) = FloatToInt(floorHeight + 2.0f);
    if (*(int *)(vars + 0x1E4) != -1) ComputePathSegmentLengths_L01(D_L08_001FE7C0[*(int *)(vars + 0x1E4)]);
    *(u8 *)(vars + 0x60) = 5;
    *(int *)(vars + 0x98) = -1;
    *(u8 *)(vars + 0x61) = 8;
    *(u8 *)(vars + 0x62) = 8;
    *(u8 *)(vars + 0x66) = 10;
    *(u8 *)(vars + 0x67) = 11;
    *(float *)(vars + 0x6C) = 0.38333335518836975f;
    *(float *)(vars + 0x70) = 0.23333334922790527f;
    *(float *)(vars + 0x74) = 0.004166666883975267f;
    *(float *)(vars + 0x78) = 0.008333333767950535f;
    *(float *)(vars + 0x7C) = 0.0027777778450399637f;
    *(float *)(vars + 0x80) = 2.75f;
    *(float *)(vars + 0x84) = 0.0f;
    *(float *)(vars + 0x8C) = 0.4f;
    *(u8 *)(vars + 0xBC) = 7;
    *(u8 *)(vars + 0xBD) = 24;
    *(u8 *)(vars + 0xBE) = 6;
    *(u8 *)(vars + 0xBF) = 13;
    *(u8 *)(vars + 0xC2) = 7;
    *(u8 *)(vars + 0xC3) = 14;
    *(u8 *)(vars + 0xC6) = 1;
    *(u8 *)(vars + 0xC4) = 0;
    *(u8 *)(vars + 0xC5) = 0;
    *(u8 *)(vars + 0xC7) = 1;
    *(int *)(vars + 0xCC) = *(int *)(vars + 0x1E4);
    *(u8 *)(vars + 0x2E) = 3;
    *(u8 *)(vars + 0x28) = 1;
    *(float *)(vars + 0x30) = 0.0f;
    *(float *)(vars + 0x1F0) = 1.0f;
    qzero_nc(vars + 0x190);
    qcopy(vars + 0x180, moby + 0x10);
    qzero_nc(vars + 0x1A0);
    if (*(float *)(vars + 0x1C4) == 0.0f) {
        float height = FindGroundHeightWithFloor(moby + 0x10, *(float *)(moby + 0x18) + 20.0f, *(float *)(vars + 0x90), *(float *)(vars + 0x90));
        *(float *)(vars + 0x1C4) = height;
        *(float *)(vars + 0x1C8) = height <= *(float *)(vars + 0x178) ? height : *(float *)(vars + 0x178);
    }
    if (*(float *)(vars + 0x1C4) > 0.0f) *(float *)(moby + 0x18) = *(float *)(vars + 0x1C4) - 0.5f;
    *(int *)(vars + 0x22C) = SpawnLinkedChildMoby2439(moby);
    *(s16 *)(vars + 0x1BE) = 0;
    if (*(u8 *)(vars + 0x20C) == 1 || *(u8 *)(vars + 0x20C) == 4) {
        STUB_printf(D_L08_001B1BD0, *(s16 *)(moby + 0xB2), *(u8 *)(vars + 0x20C), *(u8 *)(vars + 0x20C) + 1);
        *(u8 *)(vars + 0x20C) += 1;
    }
    qcopy(vars + 0x170, moby + 0x10);
    *(u16 *)(moby + 0x34) &= 0xEFFF;
    SetMobyState(moby, 1, -1);
    if (*(u8 *)(moby + 0x43)) StartAnimationBlended(moby, 0, 0, 2);
    *(int *)(moby + 0x98) = 0;
    *(u8 *)(moby + 0x31) = 0;
    *(u16 *)(moby + 0x34) |= 1;
    *(u8 *)(vars + 0x20E) = *(s16 *)(moby + 0x32) < *(u8 *)(vars + 0x20E) ? *(u8 *)(vars + 0x20E) : *(s16 *)(moby + 0x32);
    if (*(u8 *)(moby + 0x21) != 255) {
        if (*(u8 *)(vars + 0x20D) < **(int **)(vars + 0x1FC)) *(u8 *)(vars + 0x20D) = **(u8 **)(vars + 0x1FC);
        **(int **)(vars + 0x1FC) += 1;
    }
}
