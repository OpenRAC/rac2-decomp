#include "common.h"
typedef unsigned int quadword __attribute__((mode(TI)));
extern void func_002A7750(u8 *, int, int);
extern void func_L00_003294F0(u8 *, int);
extern u8 *D_L03_001B2A20[3] __attribute__((sda));
extern unsigned short D_L03_001B0300 __attribute__((sda));
extern unsigned short D_L03_001B0304 __attribute__((sda));
extern int D_L03_001B2548[3] __attribute__((sda));
extern int D_L03_001B02F8 __attribute__((sda));
extern int D_L03_001B02FC[3] __attribute__((sda));
extern int D_L03_001B0308;
extern float D_L03_001B030C __attribute__((sda));
extern float D_L03_001B0310 __attribute__((sda));
extern float D_L03_001B0314 __attribute__((sda));
extern float D_L03_001B0318 __attribute__((sda));
extern u8 D_L03_001A8F20[16] __attribute__((sda));
extern void func_L03_003CA4B0(void);
extern void func_L00_002E6CF0(void *, void *);
extern float func_00283198(float);
extern int func_00283D38(int, int, float);
extern int func_002A9640(void *, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_003263D0(void *, void *, float, float, float, float, int, int, void *, int, int);
extern void func_002B0A68(void *, int, void *, int, float, float, float, float);
extern int func_002E5CF8(int, int, void *);
/* Updates a breakable object (moby class 2418). It waits to be hit, then bursts into effects and sound and switches to its broken state. */
void func_L03_003CA290(u8 *moby) {
    float burstPos[4] __attribute__((aligned(16)));
    float burstVel[4] __attribute__((aligned(16)));
    switch (moby[0x20]) {
    case 0:
        if ((int)moby < (int)D_L03_001B2A20[0]) {
            *(int *)(moby+0x9c) = 15;
            SetMobyState(moby, 3, -1);
        } else {
            *(unsigned short *)(moby+0x7c) = D_L03_001B0300;
            SetMobyState(moby, 1, -1);
        }
        break;
    case 1:
        if (moby[0x31]) {
            AddDrawCallbackToList1(DrawGadgebotSpawnContainer, moby);
            *(int *)(moby+0x78) = FastTweenColor(D_L03_001B02F8, D_L03_001B02FC[0],
                (FastSinOrCosB((gFrameCounter_L03[0] % 150) * 0.04188786819577217f - 3.14159f) + 1.0f) * 0.5f);
        }
        if (FindOwnedEffectSlot(moby, 0x10000, 0)) {
            *(quadword *)burstPos = 0; *(quadword *)burstVel = 0;
            burstVel[2] = 0.050000004f;
            burstPos[2] = 0.5f;
            FastVecAdd(burstPos, burstPos, moby+0x10);
            SpawnTintedEffects(moby,burstPos,0.333000004f,3.0f,0.5f,1.0f,5,1,burstVel,0x504040c0,0);
            SpawnDebrisForMaskedParts(moby,D_L03_001B0308,D_L03_001A8F20,255,D_L03_001B030C,D_L03_001B0310,D_L03_001B0314,D_L03_001B0318);
            PlayMobySound(0,0,moby);
            *(unsigned short *)(moby+0x7c) = D_L03_001B0304;
            SetObjectFlagBit(moby,1);
            *(int *)(moby+0x9c) = 15;
            *(unsigned short *)(moby+0x34) |= 2;
            SetMobyState(moby,2,-1);
        }
        break;
    }
}
