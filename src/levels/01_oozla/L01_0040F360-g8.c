#include "common.h"


extern int D_L01_001AEC38 SDATA(D_L01_001AEC38);
extern int counter_abs __asm__("D_L01_001AEC38");
extern int active_abs __asm__("D_L01_001B3468");
extern float D_L01_001B208C __attribute__((sda));
extern float D_L01_001B2090 __attribute__((sda));
extern int D_L01_001B15E0 __attribute__((nosda));
extern int D_L01_001B3468 SDATA(D_L01_001B3468);
extern void func_002A7750(char *, int, int);
extern int func_002A9640(char *, int, int);
extern void func_00282D30(char *, char *, float);
extern void func_002B0A68(char *, int, void *, float, float, float, float, int);
extern void func_L00_00326110(char *, float, int);
extern int func_002E5CF8(int, int, char *);
extern int func_002B3868(char *);
extern int func_0029F338(char *);

typedef struct { char pad0[0x31]; u8 active; u16 pad32; u16 flags; char pad36[0x62]; int target; } RetiringObject;
/* Update for a breakable object: counts itself, waits to be hit, bursts with a sound and retires after a timer. */
void func_L01_0040F360(char *mobyArg)
{
    char *moby = mobyArg;
    char *vars = *(char **)(mobyArg + 0x68);
    float offset[4];
    int activeCount;

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        D_L01_001AEC38 = D_L01_001AEC38 + 1;
        SetMobyState(moby, 1, -1);
        return;
    case 1:
        if (FindOwnedEffectSlot(moby, 0x4010000, 0) != 0 && *(int *)vars == 0) {
            D_L01_001AEC38 = counter_abs - 1;
            SetMobyState(moby, 2, -1);
        }
        *(u8 *)(moby + 0xA8) = 0xFF;
        return;
    case 2:
        FastVecScale((char *)offset, moby + 0xD0, -0.06666667f);
        if (*(u8 *)(moby + 0x31) != 0 && D_L01_001B2090 < 0.9f &&
            D_L01_001B208C < 0.9f && (activeCount = D_L01_001B3468, activeCount < D_L01_001B15E0)) {
            SpawnDebrisForMaskedParts(moby, 0x1F, offset, 1.0f, 3.0f, 2.0f, 5.0f, 0xFF);
        } else {
            SpawnDebrisForMaskedParts(moby, 5, offset, 1.0f, 3.0f, 2.0f, 5.0f, 0xFF);
        }
        SpawnScaledBolts(moby, 0.0f, 1);
        PlayMobySound(0, 0, moby);
        SetMobyState(moby, 3, -1);
        return;
    case 3:
        if (SetFirstPendingFlag(moby) != 0) {
            RetiringObject *retiring = (RetiringObject *)moby;
            unsigned int flags = retiring->flags;
            int count;
            retiring->active = 0;
            retiring->target = 0;
            count = active_abs;
            retiring->flags = flags | 1;
            *(int *)(vars + 4) = 0x78;
            active_abs = count + 1;
        }
        if (FastFloatHelperD(vars + 4) != 0) {
            D_L01_001B3468 = D_L01_001B3468 - 1;
            MarkMobySpawned(moby);
        }
        return;
    }
}

