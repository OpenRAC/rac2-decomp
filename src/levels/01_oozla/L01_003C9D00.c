#include "common.h"
extern void func_00282F20(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283180(float);
extern int func_00282948(void *);
extern void func_002A8598(int, int);
extern void func_00291450(int);
typedef struct { char pad[0x30]; float position[4]; char rest[0x40]; } L01_003C9D00_PATH;
extern L01_003C9D00_PATH *D_L01_001B264C;
extern char D_L01_001C7640[];
extern float func_00282E48(void *);
extern void func_002A7750(void *, int, int);
extern int func_00283DB8(void *, float);
extern int func_L00_002FCF18(void *, float, float, float, float, float);
extern void func_L00_002E6CF0(void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_L01_003C97D8(void *);

/* Updates the scrolling ribbon moby. It fades in, stays for a while, fades out, and lights up its surroundings while it is visible. */
void func_L01_003C9D00(char *moby)
{
    float vec[4];
    char *vars = *(char **)(moby + 0x68);
    float blend = 0.0f;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(int *)(vars + 0x90) = -1;
        *(int *)(vars + 0x5C) |= 4;
        *(float *)(vars + 0x70) = 0.0f;
        *(int *)(vars + 0x6C) = 0;
        *(float *)(vars + 0x74) = 0.0f;
        *(int *)(moby + 0x98) = 0;
        qcopy(vars + 0x80, moby + 0x10);
        *(float *)(vars + 0x98) = fast_vec_dist(D_L01_001B264C[*(int *)(vars + 0x94)].position);
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (*(unsigned char *)(moby + 0xBC)) {
            *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
            SetMobyState(moby, 2, -1);
        }
        break;
    case 2:
        *(float *)(vars + 0x70) += 1.0f / *(float *)(vars + 0x60);
        if (*(float *)(vars + 0x70) > 1.0f) *(float *)(vars + 0x70) = 1.0f;
        else if (*(float *)(vars + 0x70) < 0.0f) *(float *)(vars + 0x70) = 0.0f;
        blend = (1.0f - FastSinOrCosA(*(float *)(vars + 0x70) * 3.1415927f)) * 0.5f;
        if (*(int *)(vars + 0x94) == -1) {
            vec_scale_to_length(vec, moby + 0xC0, blend * 10.0f);
            FastVecSub(moby + 0x10, vars + 0x80, vec);
        } else {
            FastVecSub(vec, D_L01_001B264C[*(int *)(vars + 0x94)].position, vars + 0x80);
            vec_scale_to_length(vec, vec, *(float *)(vars + 0x98) * blend);
            FastVecAdd(moby + 0x10, vars + 0x80, vec);
        }
        if (*(float *)(vars + 0x70) >= 1.0f) {
            *(int *)(vars + 0x6C) = *(int *)(vars + 0x64);
            SetMobyState(moby, 3, -1);
        }
        break;
    case 3:
        blend = 1.0f;
        if (FastFloatHelperD(vars + 0x6C)) SetMobyState(moby, 4, -1);
        break;
    case 4:
        *(float *)(vars + 0x70) -= 1.0f / *(float *)(vars + 0x60);
        if (*(float *)(vars + 0x70) > 1.0f) *(float *)(vars + 0x70) = 1.0f;
        else if (*(float *)(vars + 0x70) < 0.0f) *(float *)(vars + 0x70) = 0.0f;
        blend = (1.0f - FastSinOrCosA(*(float *)(vars + 0x70) * 3.1415927f)) * 0.5f;
        if (*(int *)(vars + 0x94) == -1) {
            vec_scale_to_length(vec, moby + 0xC0, blend * 10.0f);
            FastVecSub(moby + 0x10, vars + 0x80, vec);
        } else {
            FastVecSub(vec, D_L01_001B264C[*(int *)(vars + 0x94)].position, vars + 0x80);
            vec_scale_to_length(vec, vec, *(float *)(vars + 0x98) * blend);
            FastVecAdd(moby + 0x10, vars + 0x80, vec);
        }
        if (*(float *)(vars + 0x70) <= 0.0f) {
            *(int *)(moby + 0x98) = 0;
            SetByteOnGroupMobys(*(unsigned char *)(moby + 0x21), 0);
            SetMobyState(moby, 1, -1);
        }
        break;
    }
    *(unsigned char *)(moby + 0xBC) = 0;
    if ((unsigned int)(*(unsigned char *)(moby + 0x20) - 2) < 3) {
        AddDrawCallbackToList1(DrawFiveLayerScrollingRibbons, moby);
        vec_scale_to_length(vec, moby + 0xC0, *(float *)(vars + 0x68) * ((float)*(int *)(vars + 0x7C) * 0.016666668f));
        CombineTransformsAndStore(vars + 0x20, vec, moby + 0xF0, moby + 0xF0);
    }
    qcopy(vec, moby + 0x10);
    vec[3] = 10.0f;
    if (*(unsigned char *)(moby + 0x20) >= 2 && (*(unsigned char *)(moby + 0x31) || FastMathHelperA(vec, 255.0f) != -1)) {
        if (*(int *)(vars + 0x90) == -1) {
            *(int *)(vars + 0x90) = AllocateEffectSlot_L00_2(vars + 0x80, 10.0f, 0.0f, blend * 0.8f, blend * 0.9f, blend * 1.1f);
        } else {
            char *light = gDynamicLightTable + *(int *)(vars + 0x90) * 32;
            *(float *)(light + 0) = blend * 0.8f;
            *(float *)(light + 4) = blend * 0.9f;
            *(float *)(light + 8) = blend * 1.1f;
        }
    } else if (*(int *)(vars + 0x90) != -1) {
        FreePointLight(*(int *)(vars + 0x90));
        *(int *)(vars + 0x90) = -1;
    }
}
