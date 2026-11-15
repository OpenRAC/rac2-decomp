#include "common.h"


extern f32 D_L13_001AEBF0 __attribute__((sda));
extern f32 D_L13_001AEBD0 __attribute__((sda));
extern f32 D_L13_001AEBC8 __attribute__((sda));
extern f32 D_L13_001AEBC0 __attribute__((sda));
extern f32 D_L13_001AEBF4 __attribute__((nosda));
extern f32 D_L13_001AEBF8 __attribute__((nosda));
extern s32 func_002A9640(u8 *, s32, s32);
extern s32 func_002A7750(u8 *, s32, s32);
extern s32 func_0029F338(u8 *);
extern void func_L00_0033E220(float, float, void *, u8 *, s32, s32, s32, s32, s32, s32);
extern void func_L00_0032A258(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_L01_0031A278(u8 *, f32 *, f32, f32, f32);
extern void func_0032C700(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                        float, float);

/* Waits for a trigger, then plays a burst of sparks and removes itself. */
void func_L13_0038C578(u8 *moby) {
    s32 *vars = *(s32 **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        SpawnObjectFollowingEffect(210000.0f, 0.75f, &D_L13_001AEBF0, moby, 0x50204040, -1, 1, -1, 0, -1);
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (FindOwnedEffectSlot(moby, 0x4010000, 0) != 0 && *vars == 0)
            SetMobyState(moby, 2, -1);
        moby[0xA8] = 0xFF;
        break;
    case 2: {
        f32 burstPos[4];
        ExplodeObjectIntoPieces(moby, &D_L13_001AEBD0, &D_L13_001AEBC8, &D_L13_001AEBC0,
                    0xFFFF, 0, -1, 0, 0xFFFF, 0xFF, 0);
        {
            f32 first = D_L13_001AEBF8;
            f32 x = D_L13_001AEBF0;
            f32 second = D_L13_001AEBF4;
            ComputeMobyLocalPoint(moby, burstPos, x, second, first);
        }
        SpawnExplosion(burstPos, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1, 1, 0, 0, 0.3f, 20.0f);
        MarkMobySpawned(moby);
        break;
    }
    }
}
