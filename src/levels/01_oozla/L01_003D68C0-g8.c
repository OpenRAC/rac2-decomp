#include "common.h"

typedef struct {
    int active;
    int timer;
} OozlaCountdown;

typedef struct {
    u8 pad0[0x20];
    u8 state;
    u8 pad21[0x10];
    u8 visible;
    u16 field32;
    u16 flags;
    u8 pad36[0x32];
    OozlaCountdown *vars;
    u8 pad6c[0x2C];
    int collisionDisable;
    u8 pad9c[12];
    u8 hitSlot;
} OozlaStateMoby;

extern int D_L01_001AEC38 MACRO_ADDR;
extern float D_L01_001B2090, D_L01_001B208C;
extern int D_L01_001B3468 MACRO_ADDR;
extern int D_L01_001B15E0 MACRO_ADDR;
extern void *func_002A9640(void *, int, int);
extern void func_002A7750(void *, int, int);
extern void func_L01_003D6B00(void *, int, float, float, float, float);
extern void func_002E5CF8(int, int, void *);
extern void func_L00_00326110(void *, int, float);
extern void func_L00_00326620(void *, int, int);
extern int func_002B3868(void *);
extern int func_00282948(void *);
extern void func_0029F338(void *);

/* Breakable object. When something hits it, it breaks into pieces, hides, and removes itself after a short wait. */
void func_L01_003D68C0(OozlaStateMoby *moby)
{
    OozlaCountdown *vars = moby->vars;

    switch (moby->state) {
    case 0: {
        D_L01_001AEC38++;
        moby->flags |= 0x800;
        SetMobyState(moby, 1, -1);
        break;
    }
    case 1:
        if (FindOwnedEffectSlot(moby, 0x4010000, 0) && !vars->active) {
            D_L01_001AEC38 = D_L01_001AEC38 - 1;
            SetMobyState(moby, 2, -1);
        }
        moby->hitSlot = 255;
        break;
    case 2:
        if (moby->visible && D_L01_001B2090 < 0.9f && D_L01_001B208C < 0.9f &&
            D_L01_001B3468 < D_L01_001B15E0)
            SpawnRingOfSparks_L01(moby, 15, 1.5f, 6.5f, 1.5f, 0.06666667f);
        else
            SpawnRingOfSparks_L01(moby, 6, 1.5f, 6.5f, 1.5f, 0.06666667f);
        PlayMobySound(0, 0, moby);
        SpawnScaledBolts(moby, 1, 0.0f);
        SpawnChildMoby_L00(moby, 0xF94, 0);
        SetMobyState(moby, 3, -1);
        break;
    case 3:
        if (SetFirstPendingFlag(moby)) {
            moby->flags |= 1;
            moby->visible = 0;
            moby->collisionDisable = 0;
            vars->timer = 120;
            D_L01_001B3468++;
        }
        if (FastFloatHelperD(&vars->timer)) {
            D_L01_001B3468--;
            MarkMobySpawned(moby);
        }
        break;
    }
}
