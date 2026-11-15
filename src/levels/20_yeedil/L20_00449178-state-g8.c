#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F449178;

extern s32 D_L20_001B23A0 __attribute__((sda));
extern s32 D_L20_001B23A8 __attribute__((sda));
extern s32 D_L20_001B23B0 __attribute__((sda));

extern void func_002A7750(char *, s32, s32);
extern s32 func_002A9640(char *, s32, s32);
extern void func_L00_0033E220(void *, char *, s32, s32, float, float, s32, s32, s32, s32);
extern s32 func_L00_0032A258(char *, s32 *, s32 *, s32 *, s32, s32, s32, s32, s32, s32, s32);
extern void func_L01_0031A278(char *, void *, float, float, float);
extern void func_0032C700(void *, s32, s32, s32, float, float, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_L00_00326620(char *, s32, s32);
extern void func_0029F338(char *);

/* Three-state effect object: arms its emitter, waits for the trigger, then plays the burst and retires. */
/* Update handler for moby class 4713: it arms itself, waits for a trigger, then plays a burst effect and removes itself. */
void func_L20_00449178(char *moby)
{
    V4_F449178 burstPos;
    s32 *vars = *(s32 **)(moby + 0x68);

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        burstPos.q = 0;
        burstPos.f[2] = 2.0f;
        SpawnObjectFollowingEffect(&burstPos, moby, 0x40204080, -1, 420000.0f, 1.0f, 1, -1, 0, -1);
        SetMobyState(moby, 1, -1);
        return;
    case 1:
        if (FindOwnedEffectSlot(moby, 0x04010000, 0) != 0 && *vars == 0)
            SetMobyState(moby, 2, -1);
        *(u8 *)(moby + 0xA8) = 0xFF;
        return;
    case 2:
        ExplodeObjectIntoPieces(moby, &D_L20_001B23B0, &D_L20_001B23A8, &D_L20_001B23A0, 0xFFFF, 0, -1, 0, 0xFFFF, 0xFF, 0);
        ComputeMobyLocalPoint(moby, &burstPos, 0.0f, 0.0f, 2.0f);
        SpawnExplosion(&burstPos, 0, 0x19, 0x14, 0.5f, 20.0f, 0x14, 0x14, 0x2D, 1, 1, 1, 0, 0);
        SpawnChildMoby_L00(moby, 0x126A, 0);
        MarkMobySpawned(moby);
        return;
    }
}
