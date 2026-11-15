#include "common.h"

extern float D_L06_001B234C __attribute__((sda));

extern float D_001B2350 __attribute__((sda));

extern int func_0035CBA0(char *, int, int);

extern void func_L06_0045BE30(char *, int, float, float, float, float);

extern int func_003A0948(int, int, char *);

extern void func_00350388(char *);

extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_L06_0037E6B0(void *, void *, int, float, float);
extern float D_L06_001B1AC0 __attribute__((sda));
extern float D_L06_001B1AC4 __attribute__((sda));
extern float D_L06_001B1AC8 __attribute__((sda));
extern float D_L06_001B1ACC __attribute__((sda));
extern float D_L06_001B1AD0 __attribute__((sda));
extern float D_L06_001B1AD4 __attribute__((sda));
extern float D_L06_001B1AD8 __attribute__((sda));
extern float D_L06_001B1ADC __attribute__((sda));
extern int D_L06_001B1AE0 __attribute__((sda));
extern int D_L06_001B1AE4 __attribute__((sda));
extern int D_L06_001B1AE8 __attribute__((sda));

extern u8 *D_L06_001B281C MACRO_ADDR;
extern char D_00188660[];
extern void func_003514C8(void *, int, void *);
extern void func_00282CF0(float *, const float *, const float *);
extern float func_00282DF0(void *);
extern float func_00282C48(float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern void func_L06_004583A8(char *);
extern int func_002E59B0(char *, int);
extern void func_002E59F8(int);

extern u8 *D_L06_001B290C MACRO_ADDR;
extern char D_L06_001B1990[];
extern char D_L06_001B19C8[];
extern char D_L06_001B1A00[];
extern char D_L06_001B1A30[];
extern u8 *D_L06_001FE500[];

extern void func_0026FEB8(char *, ...);
extern int func_001163B0(void);
extern void func_L06_00459B18(char *a0);
extern int func_L06_00459BA8(char *a0, char *a1);
extern void func_L06_00459C38(unsigned char *a0, u8 *a1);

/* Turns this part to follow the progress value of the object it is linked to, and plays a sound while it moves. */
void func_L06_00458568(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *other;
    float tmp[4];
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(float *)(vars + 8) = *(float *)(moby + 0xF8);
        *(float *)(vars + 0x18) = *(float *)(moby + 0xF4);
        *(int *)(vars + 0x10) = 0;
        func_003514C8(moby, 0, tmp);
        FastVecSub(tmp, tmp, (float *)(moby + 0x10));
        {
            float length = FastVecLength(tmp);
            *(float *)(vars + 4) -= length;
            *(float *)(vars + 0x1C) = length;
        }
        if (*(float *)(vars + 0xC) == 0.0f) *(float *)(vars + 0xC) = 1.0f;
        SpawnChainedSegment(moby);
        *(float *)(vars + 0x24) = 0;
        moby[0x20] = 1;
        break;
    case 1:
        if (*(int *)vars != -1) {
            other = D_L06_001B281C + *(int *)vars * 256;
            if (other) {
                char *linkVars = *(char **)(other + 0x68);
                if (FloatAbs(*(float *)(vars + 0xC)) > 0.0f)
                    *(float *)(vars + 0x14) = *(float *)linkVars * (*(float *)(vars + 0xC) * 3.1415927f);
                else *(float *)(vars + 0x14) = 0;
                *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(vars + 8), *(float *)(vars + 0x14));
                if (*(float *)linkVars > 0.6f)
                    *(float *)(moby + 0xF4) = fast_subtract_rotations(*(float *)(vars + 0x18), (*(float *)linkVars - 0.6f) * 0.13089971244335175f);
                if (*(int *)(vars + 0x10) == 0) {
                    if (*(float *)linkVars != *(float *)(vars + 0x24) && *(float *)linkVars != 1.0f && *(float *)linkVars != 0.0f) {
                        if (!IsVoicePlayingForOwner(moby, *(int *)(vars + 0x20)))
                            *(int *)(vars + 0x20) = func_003A0948(0, 4, moby);
                    } else if (IsVoicePlayingForOwner(moby, *(int *)(vars + 0x20))) {
                        if (*(int *)(vars + 0x20) != -1) {
                        char *sound = gSoundState + *(int *)(vars + 0x20) * 0x70;
                        if (*(char **)(sound + 0x88) == moby && *(unsigned char *)(sound + 0x74)) StopSoundVoice(*(int *)(vars + 0x20));
                        }
                        *(int *)(vars + 0x20) = -1;
                    }
                }
                *(float *)(vars + 0x24) = *(float *)linkVars;
            }
        }
        if (*(int *)(vars + 0x10)) func_003514C8((void *)*(int *)(vars + 0x10), 0, moby + 0x10);
        break;
    }
}

/* Resolves the table entries a spawn record names; returns 1 after reporting a missing one. */
int func_L06_00459D08(u8 *moby, u8 *vars)
{
    s32 pathIdxA, pathIdxB, anchorIdx, homeIdx;
    u8 *pathA, *pathB;

    pathIdxA = *(s32 *)(vars + 0x100);
    if (pathIdxA == -1) {
        STUB_printf(D_L06_001B1990, (moby - D_L06_001B281C) >> 8);
        return 1;
    }
    pathA = gPathList[pathIdxA];
    *(u8 **)(vars + 0x118) = pathA;
    ComputePathSegmentLengths_L06((char *)pathA);
    pathIdxB = *(s32 *)(vars + 0x134);
    if (pathIdxB == -1) {
        STUB_printf(D_L06_001B19C8, (moby - D_L06_001B281C) >> 8);
        return 1;
    }
    pathB = gPathList[pathIdxB];
    *(u8 **)(vars + 0x138) = pathB;
    ComputePathSegmentLengths_L06((char *)pathB);
    anchorIdx = *(s32 *)(vars + 0x108);
    if (anchorIdx == -1) {
        STUB_printf(D_L06_001B1A00, (moby - D_L06_001B281C) >> 8);
        return 1;
    }
    *(u8 **)(vars + 0x11C) = D_L06_001B281C + (anchorIdx << 8) + 0x18;
    moby[0xBC] = ClassifyHeadroomSize((char *)moby, (char *)vars);
    homeIdx = *(s32 *)(vars + 0x104);
    if (homeIdx == -1) {
        STUB_printf(D_L06_001B1A30, (moby - D_L06_001B281C) >> 8);
        return 1;
    }
    qcopy(vars + 0xE0, D_L06_001B290C + 0x30 + (homeIdx << 7));
    qcopy(vars + 0xD0, moby + 0x10);
    StartAnimationForSizeClass(moby, vars);
    *(s32 *)(vars + 0x124) = Rand() % 120;
    if (Rand() & 1)
        *(f32 *)(vars + 0x130) = 0.3490659f;
    else
        *(f32 *)(vars + 0x130) = -0.3490659f;
    *(s32 *)(vars + 0x13C) = 0;
    vars[0x29] = 1;
    return 0;
}

/* Spits out a few small particles in front of the object, along the direction it is facing. */
void func_L06_0045C6D0(char *moby) {
    float velocity[4], pos[4], offset[4];
    qcopy(pos, moby + 0x10);
    pos[2] += 3.3f + RandomFloatRange(-0.05f, 0.05f);
    pos[0] += RandomFloatRange(-0.1f, 0.1f);
    pos[1] += RandomFloatRange(-0.1f, 0.1f);
    offset[0] = FastSinOrCosA(*(float *)(moby + 0xF8)) * 1.5f;
    offset[1] = FastSinOrCosB(*(float *)(moby + 0xF8)) * 1.5f;
    offset[2] = 0;
    FastVecAdd(pos, pos, offset);
    velocity[0] = FastSinOrCosA(*(float *)(moby + 0xF8)) * RandomFloatRange(D_L06_001B1AC0 * 0.0166666675f, D_L06_001B1AC4 * 0.0166666675f);
    velocity[1] = FastSinOrCosB(*(float *)(moby + 0xF8)) * RandomFloatRange(D_L06_001B1AC0 * 0.0166666675f, D_L06_001B1AC4 * 0.0166666675f);
    velocity[2] = 0;
    velocity[2] = RandomFloatRange(D_L06_001B1AC8 * 0.0166666675f, D_L06_001B1ACC * 0.0166666675f);
    SpawnSpinningEffectRecord(pos, velocity, D_L06_001B1AE4, 0.5f, 50.4f);
    SpawnSpinningEffectRecord(pos, velocity, D_L06_001B1AE4, 0.5f, 50.4f);
    if (RandomIntBelow(D_L06_001B1AE8) != 1) {
    velocity[0] = FastSinOrCosA(*(float *)(moby + 0xF8)) * RandomFloatRange(D_L06_001B1AC0 * 0.0166666675f, D_L06_001B1AC4 * 0.0166666675f);
    velocity[1] = FastSinOrCosB(*(float *)(moby + 0xF8)) * RandomFloatRange(D_L06_001B1AC0 * 0.0166666675f, D_L06_001B1AC4 * 0.0166666675f);
    velocity[2] = 0;
    velocity[2] = RandomFloatRange(D_L06_001B1AC8 * 0.0166666675f, D_L06_001B1ACC * 0.0166666675f);
        SpawnSpinningEffectRecord(pos, velocity, D_L06_001B1AE0, 0.5f, 50.4f);
    }
    if (RandomIntBelow(D_L06_001B1AE8) != 1) {
    velocity[0] = FastSinOrCosA(*(float *)(moby + 0xF8)) * RandomFloatRange(D_L06_001B1AD0 * 0.0166666675f, D_L06_001B1AD4 * 0.0166666675f);
    velocity[1] = FastSinOrCosB(*(float *)(moby + 0xF8)) * RandomFloatRange(D_L06_001B1AD0 * 0.0166666675f, D_L06_001B1AD4 * 0.0166666675f);
    velocity[2] = 0;
    velocity[2] = RandomFloatRange(D_L06_001B1AD8 * 0.0166666675f, 0.0300000012f);
        SpawnSpinningEffectRecord(pos, velocity, D_L06_001B1AE0, 0.75f, 50.4f);
    }
    if (RandomIntBelow(D_L06_001B1AE8) == 1) {
    velocity[0] = FastSinOrCosA(*(float *)(moby + 0xF8)) * RandomFloatRange(D_L06_001B1AD0 * 0.0166666675f, D_L06_001B1AD4 * 0.0166666675f);
    velocity[1] = FastSinOrCosB(*(float *)(moby + 0xF8)) * RandomFloatRange(D_L06_001B1AD0 * 0.0166666675f, D_L06_001B1AD4 * 0.0166666675f);
    velocity[2] = 0;
    velocity[2] = RandomFloatRange(D_L06_001B1AD8 * 0.0166666675f, D_L06_001B1ADC * 0.0166666675f);
        SpawnSpinningEffectRecord(pos, velocity, D_L06_001B1AE0, 0.75f, 50.4f);
    }
}
