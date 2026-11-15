/* Second spawner state machine: waits for the player, then emits while its target is alive and
   the level counter (D_L08_001B3AA0) is below 10. */

#include "common.h"


extern s32 D_L08_001B29DC __attribute__((sda));
extern f32 D_L08_001B250C __attribute__((sda));
extern s32 D_L08_001B3AA0 __attribute__((sda));
extern char D_L08_001A8F20[] MACRO_ADDR;
extern char *func_002A9640(s32 a, s32 b, s32 c);
extern void func_002A7750(char *a0, s32 a1, s32 a2);
extern void func_002B0A68(char *a0, f32 f12, f32 f13, s32 a1, char *a2,
                        f32 f14, f32 f15, s32 a3);
extern void func_L00_00326110(char *a0, s32 a1, f32 f12);
extern void func_002E5CF8(s32 a0, s32 a1, char *a2);
extern s32 func_002B3868(char *a0);
extern s32 func_00282948(char *a0);
extern void func_0029F338(char *a0);

/* Waits for the player, then fires its burst of particles and counts itself in the level counter
   until its timer runs out. */
void func_L08_0042FAC0(char *spawner) {
    char *vars = *(char **)(spawner + 0x68);
    u8 state = *(u8 *)(spawner + 0x20);
    char *hit;
    s32 childIndex;
    u8 childState;

    switch (state) {
    case 0:
        SetMobyState(spawner, 1, -1);
        return;
    case 1:
        hit = FindOwnedEffectSlot((s32)spawner, 0x04010000, 0);
        if (hit != 0 && *(s32 *)vars == 0) {
            SetMobyState(spawner, 2, -1);
            return;
        }
        *(u8 *)(spawner + 0xA8) = 0xFF;
        childIndex = *(s32 *)(vars + 4);
        if (childIndex > 0) {
            char *child = (char *)(D_L08_001B29DC + (childIndex << 8));

            if (child == 0) {
                return;
            }
            childState = *(u8 *)(child + 0x20);
            if (childState == 0xFE || (childState == 0xFD || childState == 3)) {
                SetMobyState(spawner, 2, -1);
            }
        }
        return;
    case 2:
        if (*(u8 *)(spawner + 0x31) != 0 && D_L08_001B250C < 0.9f &&
            gActiveEmitterCount < 10) {
            SpawnDebrisForMaskedParts(spawner, 3.0f, 6.0f, 15, D_L08_001A8F20, 3.0f, 6.0f, 0xFF);
        } else {
            SpawnDebrisForMaskedParts(spawner, 3.0f, 6.0f, 1, D_L08_001A8F20, 3.0f, 6.0f, 0xFF);
        }
        SpawnScaledBolts(spawner, 1, 0.0f);
        PlayMobySound(0, 0, spawner);
        SetMobyState(spawner, 3, -1);
        return;
    case 3:
        if (SetFirstPendingFlag(spawner) != 0) {
            s32 count;
            *(u8 *)(spawner + 0x31) = 0;
            count = gActiveEmitterCount;
            *(u16 *)(spawner + 0x34) |= 1;
            *(s32 *)(spawner + 0x98) = 0;
            gActiveEmitterCount = count + 1;
            *(s32 *)(vars + 8) = 0x78;
        }
        if (FastFloatHelperD(vars + 8) != 0) {
            gActiveEmitterCount = gActiveEmitterCount - 1;
            MarkMobySpawned(spawner);
        }
        return;
    }
}
