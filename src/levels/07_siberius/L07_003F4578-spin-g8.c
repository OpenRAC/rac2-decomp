#include "common.h"
extern s32 func_002A9640(u8 *, s32, s32);
extern f32 func_002A96A0(u8 *, s32);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern void func_002A7750(u8 *, u8, s32);
extern f32 D_L07_001B0FD0 __attribute__((sda));
typedef struct { u8 pad[0x20]; f32 angle; u8 pad24[12]; u32 flags; } SpinnerState;
/* Starts the homing bomb on its first update. After that it counts its fuse angle down and switches to state 3 when it runs out. */
void func_L07_003F6CF0(u8 *moby)
{
    SpinnerState *vars = *(SpinnerState **)(moby + 0x68);

    if (*(u8 *)(moby + 0x20) == 0) {
        f32 scale;
        vars->flags = 0;
        scale = D_L07_001B0FD0;
        *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24) * scale;
        SetMobyState(moby, 1, -1);
        *(u32 *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        return;
    }
    {
        s32 id = FindOwnedEffectSlot(moby, 0x10000, 0);
        f32 angle = UpdateAimTargetStrength(moby, id);
        ApproachValue(&vars->angle, 0.0f, angle);
    }
    if (vars->angle <= 0.0f)
        SetMobyState(moby, 3, -1);
    *(u8 *)(moby + 0xA8) = 0xFF;
}

