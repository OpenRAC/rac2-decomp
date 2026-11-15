#include "common.h"
extern void *part_find_owned_effect_slot(u8 *, s32, s32);
extern f32 moby_update_aim_target_strength(u8 *, s32);
extern f32 ApproachValue(f32 *, f32, f32);
extern void moby_set_state(u8 *, u8, s32);
extern f32 D_L07_001B0FD0 __attribute__((sda));
typedef struct { u8 pad[0x20]; f32 angle; u8 pad24[12]; u32 flags; } SpinnerState;
/* Starts the homing bomb on its first update. After that it counts its fuse angle down and switches to state 3 when it runs out. */
void homing_bomb_tick_fuse(u8 *moby)
{
    SpinnerState *vars = *(SpinnerState **)(moby + 0x68);

    if (*(u8 *)(moby + 0x20) == 0) {
        f32 scale;
        vars->flags = 0;
        scale = D_L07_001B0FD0;
        *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24) * scale;
        moby_set_state(moby, 1, -1);
        *(u32 *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        return;
    }
    {
        s32 id = part_find_owned_effect_slot(moby, 0x10000, 0);
        f32 angle = moby_update_aim_target_strength(moby, id);
        ApproachValue(&vars->angle, 0.0f, angle);
    }
    if (vars->angle <= 0.0f)
        moby_set_state(moby, 3, -1);
    *(u8 *)(moby + 0xA8) = 0xFF;
}

