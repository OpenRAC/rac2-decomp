#include "common.h"
typedef float Vector[4];
extern void func_L07_003F67B8(u8 *);
extern void func_002A7750(u8 *, u8, s32);
extern s32 func_002B3868(u8 *);
extern void func_002A7470(void *, int, int, int);
extern void func_L07_003F68F0(s8 *, f32);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern int func_002E5CF8(int, int, char *);
extern void *func_L03_003D9820(void *, void *, void *, s32);
extern f32 D_L07_001B0FA0 __attribute__((sda));
extern s32 D_L07_001B0FA8 __attribute__((sda));
extern Vector D_L07_001B0FB0 __attribute__((sda));
extern f32 D_L07_001B0FC0 __attribute__((sda));
extern s32 D_L07_001B1E08 __attribute__((nosda));

/* Advances the dormant entity through initialization and its firing state. */
/* Updates the turret: sets itself up, plays its shot animation, then fires a projectile at regular intervals. */
void func_L07_003F6328(u8 *moby)
{
    u8 *state;
    Vector position, velocity;
    if (moby[0x20] == 1) return;
    state = *(u8 **)(moby + 0x68);
    TickFuseAndExplode(moby);
    switch (moby[0x20]) {
    case 0:
        *(f32 *)(state + 0x58) = *(f32 *)(moby + 0x18);
        *(f32 *)(state + 0x60) = *(f32 *)(moby + 0xF8);
        *(s32 *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        SetMobyState(moby, 1, -1);
        break;
    case 2:
        if (SetFirstPendingFlag(moby)) {
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
            *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
            if (moby[0x43]) StartAnimationBlended(moby, 0, 0, 1);
        }
        if (moby[0x60] & 2) {
            if (moby[0x43] != 1) StartAnimationBlended(moby, 1, 0, 1);
            SetMobyState(moby, 3, -1);
        }
        break;
    case 3: {
        s32 period, tick;
        UpdateSwingingYaw((s8 *)moby, D_L07_001B0FA0 * 0.0002908882452175f);
        period = D_L07_001B0FA8;
        tick = D_L07_001B1E08;
        if (tick % period == 0) {
            matrix_mul_vec3(position, D_L07_001B0FB0, moby + 0xC0);
            FastVecAdd(position, position, moby + 0x10);
            vec_scale_to_length(velocity, moby + 0xC0, D_L07_001B0FC0 * 0.0166666675359f);
            PlayMobySound(0, 0, (char *)moby);
            SpawnSparkShotMoby(moby, position, velocity, state[0x34]);
        }
        break;
    }
    }
}
