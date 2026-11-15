#include "common.h"


typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float value[4]; } LaunchVector;
typedef struct {
    float f0, f4, f8, f12, f16, f20;
    unsigned char f24, f25; short f26;
    unsigned char f28, f29, f30, f31;
    unsigned char pad32[16];
    short f48, f50; int f52, f56, f60;
} PoolRecord64;
extern void func_0026FEB8(const char *, ...);
extern void func_002A7750(unsigned char *, int, int);
extern void func_002A8598(int, int);
extern int func_002ACBC8(void *, int);
extern int func_00282948(int *);
extern PoolRecord64 *func_L00_002D70A0(int);
extern void func_L00_002D7140(unsigned char *);
extern unsigned char *func_L01_003D25B8(unsigned char *, LaunchVector *, LaunchVector *, int, int);
extern unsigned char *D_L01_001B255C __attribute__((sda));
extern unsigned char *D_L01_001B264C __attribute__((sda));
extern char D_L01_001B0548[], D_L01_001B0580[];
extern int D_L01_00297BF0[];
extern unsigned char D_00189EA0[];
typedef struct { int delay, startId, endId, unused; int first[2], second[2]; int p20, p24, timer, duration; short selection, mode; PoolRecord64 *pool; int event, command; } LaunchState;
#define FIELD(o) (*(int *)(data + (o)))
#define HALF(o) (*(short *)(data + (o)))
#define POOL (*(PoolRecord64 **)(data + 0x34))
/* Launcher that waits for a trigger, then fires shots along its path points on a timer. It shows a glow while the hero is nearby. */
void func_L01_003D2890(unsigned char *moby)
{
    LaunchState *state = *(LaunchState **)(moby + 0x68);
    unsigned char *data = (unsigned char *)state;
    LaunchVector point, target;
    int i, command;
    int *firstIDs, *secondIDs;
    switch (moby[0x20]) {
    case 0:
        POOL = 0;
        for (i = 0; i < 2; i++) {
            if (state->first[i] == -1) {
                STUB_printf(D_L01_001B0548, *(short *)(moby + 0xaa), *(short *)(moby + 0xb2), i);
                SetMobyState(moby, 4, -1);
            }
            if (state->second[i] == -1) {
                STUB_printf(D_L01_001B0580, *(short *)(moby + 0xaa), *(short *)(moby + 0xb2), i);
                SetMobyState(moby, 4, -1);
            }
        }
        if (moby[0x20] == 0) SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (moby[0xbc]) {
            gMobyTable_L01[FIELD(4) * 256 + 0xbc] = 1;
            FIELD(0x28) = 0;
            moby[0xbc] = 0;
            FIELD(0x3c) = 0;
            FIELD(0x2c) = FIELD(0x24);
            SetMobyState(moby, 2, -1);
        }
        break;
    case 2:
        if (FastFloatHelperD((int *)(data + 0x28))) {
            command = D_L01_00297BF0[FIELD(0x3c)];
            switch (command) {
            case 0: HALF(0x30) = 0; HALF(0x32) = 0; break;
            case 1: HALF(0x30) = 1; HALF(0x32) = 1; break;
            case 2: HALF(0x32) = 1; HALF(0x30) = 0; break;
            }
            {
                unsigned char *base = D_L01_001B264C;
                int index;
                int selection = HALF(0x30);
                FIELD(0x3c)++;
                index = state->second[selection];
                qcopy_nc(&point, base + index * 128 + 0x30);
                qcopy_nc(&target, base + index * 128 + 0x70);
                SpawnChildMoby_L01(moby, &point, &target, HALF(0x32) + 0xa9e /* moby class 2718 */, HALF(0x30));
            }
            {
                int triggerIndex = FIELD(8);
                state->timer = FIELD(0);
                gMobyTable_L01[triggerIndex * 256 + 0xbc] = 1;
            }
        }
        if (FIELD(0x28) < FIELD(0) - 40)
            gMobyTable_L01[FIELD(8) * 256 + 0xbc] = 0;
        if (FastFloatHelperD((int *)(data + 0x2c))) SetMobyState(moby, 3, -1);
        break;
    case 3:
        gMobyTable_L01[FIELD(4) * 256 + 0xbc] = 0;
        SetByteOnGroupMobys(moby[0x21], 0);
        SetMobyState(moby, 1, -1);
        break;
    }
    if (moby[0x20] == 2 && FIELD(0x38) != -1 && IsPointInCuboid(gHeroPosition, FIELD(0x38))) {
        if (POOL == 0) {
            POOL = AllocCameraOverrideSlot(5);
            qzero((unsigned char *)POOL + 0x20);
            *(float *)((unsigned char *)POOL + 0x20) = -1.0f;
            POOL->f24 = 1;
            POOL->f4 = 6.0f;
            POOL->f26 = 1;
            POOL->f30 = 1;
        }
    } else if (POOL) {
        EndCameraOverride((unsigned char *)POOL);
        POOL = 0;
    }
}
