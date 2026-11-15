#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct PoolRecord64 PoolRecord64;
extern Vector D_00189EA0;
extern unsigned char D_00188660[];
extern void func_002A7750(unsigned char *, unsigned char, int);
extern unsigned char *func_0029EFD0(int);
extern void func_002B37E8(void *, void *);
extern int func_002B3868(unsigned char *);
extern int func_00282948(int *);
extern float func_00283B98(float, float);
extern int func_002E5CF8(int, int, char *);
extern void func_002E59F8(int);
extern int func_L00_00324120(int);
extern PoolRecord64 *func_L00_002D70A0(int);
extern void func_L00_002D7140(unsigned char *);
extern void func_L20_0043D470(char *);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_002AD6F0(void *, const void *, const void *, const void *);
extern void func_L01_003208D0(void *, float *, int);
extern void func_0029F338(void *);
extern void func_00282D30(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_002A0F48(void *);
extern Vector D_L20_001B9FC0;

/* Updates moby class 4464: a rotating object that turns for a set time, plays a sound while turning, and keeps a copy of itself and any riders moving with it. */
void func_L20_0043D4D8(unsigned char *moby) {
    Vector oldPosition, oldRotation, delta, offset;
    unsigned char *state = *(unsigned char **)(moby + 0x68);
    unsigned char *child;
    unsigned char *slot;
    int index;
    oldPosition.q = *(Quadword *)(moby + 0x10);
    oldRotation.q = *(Quadword *)(moby + 0xF0);
    switch (moby[0x20]) {
    case 0: {
        float speed = *(float *)(state + 0x74) * 0.017453294f;
        float range = 6.2831854820251465f;
        float one = 1.0f;
        unsigned int savedValue;
        *(int *)(state + 0x5C) |= 1;
        *(float *)(state + 0x70) = range;
        *(float *)(state + 0x74) = speed;
        savedValue = moby[0xBC];
        *(int *)(state + 0x60) = 0;
        *(int *)(state + 0x68) = 0;
        *(int *)(state + 0x80) = 0;
        *(unsigned int *)(state + 0x7C) = savedValue;
        *(float *)(state + 0x64) = one;
        *(float *)(state + 0x6C) = one;
        SetMobyState(moby, 1, -1);
        break;
    }
    case 1:
        if ((unsigned)moby[0xBC] != *(unsigned int *)(state + 0x7C)) {
            if (!*(unsigned char **)(state + 0x88)) {
                if (!(*(unsigned char **)(state + 0x88) = CreateMoby(*(short *)(moby + 0xAA))))
                    goto clone_failed;
            }
            {
                InitChildObjectFromParent(*(unsigned char **)(state + 0x88), 0);
                *(unsigned short *)(*(unsigned char **)(state + 0x88) + 0x34) |= 2;
                *(int *)(*(unsigned char **)(state + 0x88) + 0x98) = 0;
                (*(unsigned char **)(state + 0x88))[0x23] = 0;
            }
clone_failed:
            {
                float sign = -1.0f;
                if (gHeroPosition.f[1] <= *(float *)(moby + 0x14)) sign = 1.0f;
                *(float *)(state + 0x64) = sign;
            }
            SetMobyState(moby, 2, -1);
        }
        break;
    case 2:
        if (SetFirstPendingFlag(moby)) *(int *)(state + 0x78) = (int)(*(float *)(state + 0x70) / *(float *)(state + 0x74));
        if (!FastFloatHelperD((int *)(state + 0x78))) {
            *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(moby + 0xF8), *(float *)(state + 0x74));
            slot = *(int *)(state + 0x90) * 0x70 + gSoundState;
            if (*(unsigned char **)(slot + 0x88) != moby || !slot[0x74])
                *(int *)(state + 0x90) = PlayMobySound(1, 4, (char *)moby);
        } else {
            moby[0xBC] = *(unsigned char *)(state + 0x7C);
            SetMobyState(moby, 1, -1);
            index = *(int *)(state + 0x90);
            if (index != -1) {
                unsigned char *stoppedSlot = index * 0x70 + gSoundState;
                if (*(unsigned char **)(stoppedSlot + 0x88) == moby && stoppedSlot[0x74])
                    StopSoundVoice(index);
            }
            *(int *)(state + 0x90) = -1;
        }
        break;
    }
    if (IsCurrentSelectedId((int)moby) && !*(int *)(state + 0x80)) {
        *(PoolRecord64 **)(state + 0x84) = AllocCameraOverrideSlot(5);
        *(int *)(state + 0x80) = 1;
        FillObjectSettingsBlock((char *)moby);
    } else if (!IsCurrentSelectedId((int)moby) && *(int *)(state + 0x80)) {
        EndCameraOverride(*(unsigned char **)(state + 0x84));
        *(int *)(state + 0x80) = 0;
    }
    FastVecSub(&delta, moby + 0x10, &oldPosition);
    CombineTransformsAndStore(state + 0x20, &delta, &oldRotation, moby + 0xF0);
    child = *(unsigned char **)(state + 0x88);
    if (child) {
        UpdateFlickeringGlow(child, (float *)(state + 0x8C), moby[0x20] == 2);
        child = *(unsigned char **)(state + 0x88);
        if (!child[0x23]) {
            MarkMobySpawned(child);
            *(unsigned char **)(state + 0x88) = 0;
        } else {
            *(Quadword *)(child + 0xF0) = *(Quadword *)(moby + 0xF0);
            FastVecSub(&offset, &D_L20_001B9FC0, moby + 0x10);
            FastVecScale(&offset, &offset, 0.01f);
            FastVecAdd(*(unsigned char **)(state + 0x88) + 0x10, &offset, moby + 0x10);
            func_002A0F48(*(unsigned char **)(state + 0x88));
        }
    }
}
