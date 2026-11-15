/* Updates contact state, retaining the separate attached-owner pointer lifetime.
 * Position and fallback vectors are complete sixteen-byte transfers. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B2418 __attribute__((sda));

extern u32 D_00189E20[] __attribute__((nosda));

extern void func_002A7750(char *, int, int);

extern void *func_002A9640(char *, int, int);

extern float func_002A96A0(char *, char *);

extern int func_002B3BA8(char *, int, void *, int, float, float);
extern float func_002AA2E8(float *, float, float);

extern void func_L20_0044AB68(char *);

/* Handles the turret's health and aim target: sets it up on the first frame, takes damage from hits, and blows up when its health reaches zero. */
void func_L20_0044A658(char *moby) {
    char *state;
    char *hit;
    u32 *hitter;
    short hitClass;
    float damage;

    state = *(char **)(moby + 0x68);
    if (*(u8 *)(moby + 0x20) == 0) {
        SetMobyState(moby, 1, -1);
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        *(int *)(moby + 0x98) = 0;
        qcopy((state + 0x180), (moby + 0x10));
        *(float *)(moby + 0x2C) =
            *(float *)(*(u32 *)(moby + 0x24) + 0x24) * D_L20_001B2418;
        *(int *)(state + 0x1B8) = -1;
    }
    if (*(u8 *)(moby + 0x20) == 1) {
        return;
    }
    hit = FindOwnedEffectSlot(moby, 0x10000, 0);
    if (hit != 0) {
        hitter = *(u32 **)(hit + 0x20);
        if (hitter != 0) {
            hitClass = *(short *)((char *)hitter + 0xAA);
            if (hitClass == 0x12F2 /* moby class 4850 */ || hitClass == 0x12EF /* moby class 4847 */) {
                hit = 0;
            }
        }
    }
    damage = UpdateAimTargetStrength(moby, hit);
    ApproachValue((float *)(state + 0x20), 0.0f, damage);
    *(u8 *)(moby + 0xA8) = 0xFF;
    if (*(float *)(state + 0x20) == 0.0f) {
        PlayTurretDeathBurst(moby);
        *(u8 *)(moby + 0xA8) = 0xFF;
        SetMobyState(moby, 1, -1);
        *(int *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
    }
    if (*(u8 *)(moby + 0x20) == 5) {
        return;
    }
    {
    char *owner = *(char **)(state + 0x1B0);
    if (owner != 0) {
        *(u32 *)(state + 0x150) = (u32)owner;
        qcopy((state + 0x140), (owner + 0x10));
        *(float *)(state + 0x148) = *(float *)(state + 0x148) + 0.5f;
        return;
    }
    }
    SelectAimTarget_002B3BA8(moby, *(int *)(state + 0x160), 0, 0, 1024.0f, 37.0f);
    if (*(u32 *)(state + 0x150) != 0) {
        return;
    }
    {
        u32 *base = (u32 *)gHeroState;
        *(u32 *)(state + 0x150) = base[0x8A4];
        qcopy((state + 0x140), ((char *)base + 0xD0));
    }
}
