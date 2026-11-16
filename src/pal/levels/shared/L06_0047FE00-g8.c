#include "include_asm.h"

#include "common.h"
extern s32 *ref_L06_0047AC68_00[] __attribute__((sda));
extern void ref_L06_0047AC68_01(s32);
extern u8 g_screen_mode_flag __attribute__((nosda));
extern s32 g_hero_mode __attribute__((nosda));
typedef struct {
    char pad0[0x34C];
    s16 field34C;
    char pad1[0x24A0 - 0x34E];
    s32 field24A0;
} L06State;
extern L06State g_hero_state __attribute__((nosda));
extern int g_current_map_index;

/* Checks whether a camera volume moby may trigger, from its type and the game state, then runs the shared handler. */
s32 cam_volume_update_pal(s32 moby)
{
    s32 *row;
    s32 *entry;
    char *state;
    u16 tag;

    row = (s32 *)((*(s16 *)(moby + 0x84) << 5) + (s32)ref_L06_0047AC68_00[0]);
    entry = row + 7;
    state = (char *)*entry;

    if (*(s16 *)(state + 0x48) == 1 && *(s16 *)(state + 0x4A) != 0)
        return 0;
    tag = *(u16 *)(state + 0x2C);
    if (*(s16 *)(state + 0x2C) == 11 && g_screen_mode_flag != 2)
        return 0;

    switch ((s16)tag) {
    case 1:
    case 10:
        if (*(s16 *)(state + 0x2E) != 0)
            goto clear;
        if (g_hero_state.field34C != 0) {
            if (g_current_map_index != 14)
                return 0;
            if (g_hero_state.field24A0 != 13)
                return 0;
        }
    }
clear:
    if ((s16)tag != 2)
        goto call;
    if (g_hero_mode == 26)
        goto call;
    *(u16 *)(state + 0x2E) = 0;
    return 0;
call:
    ref_L06_0047AC68_01(moby);
    return 0;
}
