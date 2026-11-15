#include "common.h"

extern u8 *D_L03_001B2A1C __attribute__((sda));
extern s32 g_current_map_index[] __attribute__((sda));
extern u8 D_001395B8[];
extern void moby_set_state(u8 *, s32, s32);
extern void moby_set_flag_bit(u8 *, s32);
extern void moby_draw_marker_sprite(u8 *);

/* Waits until the objects linked to this one are gone, then frees its helpers, records progress for the level and finishes. */
void linked_l03_door_update(u8 *object)
{
    u8 *vars = *(u8 **)(object + 0x68);
    u8 *other;
    s32 index;
    s32 state;
    if (*(s32 *)(vars + 0x14) != 0)
        *(s32 *)(object + 0x98) = 0;
    state = object[0x20];
    switch (state) {
    case 0:
        if (*(s32 *)(vars + 0x14) != 0)
            *(u16 *)(object + 0x34) |= 0x41;
        if (*(s32 *)(vars + 8) == -1 || *(s32 *)(vars + 0xC) == -1)
            moby_set_state(object, 2, -1);
        else
            moby_set_state(object, 1, -1);
    case 1:
        index = *(s32 *)(vars + 8);
        if (index != -1) {
            other = D_L03_001B2A1C + (index << 8);
            if (other != 0 && other[0x20] != 0xFE && other[0x20] != 0xFD)
                break;
        }
        index = *(s32 *)(vars + 0xC);
        if (index != -1) {
            other = D_L03_001B2A1C + (index << 8);
            if (other != 0 && other[0x20] != 0xFE && other[0x20] != 0xFD)
                break;
        }
        moby_set_state(object, 2, -1);
        break;
    case 3:
        other = *(u8 **)(vars + 0x1C);
        if (other == 0)
            break;
        if (other[0x20] == 0xFE)
            goto owner_finished;
        if (other[0x20] != 0xFD)
            break;
owner_finished:
        index = *(s32 *)(vars + 0);
        if (index != -1)
            moby_set_flag_bit(D_L03_001B2A1C + (index << 8), 1);
        index = *(s32 *)(vars + 4);
        if (index != -1)
            moby_set_flag_bit(D_L03_001B2A1C + (index << 8), 1);
        if (g_current_map_index[0] == state)
            D_001395B8[0x78] |= 1;
        if (g_current_map_index[0] == 0xE)
            D_001395B8[0x78] |= 2;
        moby_set_state(object, 4, -1);
        break;
    }
    if (*(s32 *)(vars + 0x10) != 0 && object[0x31] != 0)
        moby_draw_marker_sprite(object);
}
