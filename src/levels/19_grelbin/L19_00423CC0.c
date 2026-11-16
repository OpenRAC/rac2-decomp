#include "common.h"

extern void moby_mark_spawned(void *);

extern int IsPointInCuboid(char *, int);

extern void moby_set_state(char *, int, int);

extern int g_current_map_index[] MACRO_ADDR;
extern int D_001A79F0_gp SDATA(D_001A79F0);

extern unsigned char g_hero_position[];

extern unsigned char g_moby_nibble_table[];

/* The state table has an unknown trailing extent. */
extern struct {
    unsigned char pad[0x464];
    unsigned char state[0];
} D_L19_0021EA30;

/* Waits for the player to come near, then marks the object as used in the level's saved data and moves to its finished state. */
void UpdateRegionTriggeredObject(char *moby)
{
    char *class_info_a, *class_info_b;
    int vars = *(int *)(moby + 0x68);

    if (vars == 0) {
        moby_mark_spawned(moby);
        return;
    }
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(int *)(moby + 0x98) = 0;
        *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(moby, 1, -1);
        *(unsigned char *)(moby + 0x30) = 0xFF;
        break;
    case 2:
    default:
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position, *(int *)vars) != 0) {
            int uid = *(unsigned short *)(moby + 0xB2);
            if (uid & 1) {
                unsigned char *counter_byte = &g_moby_nibble_table[((short)uid >> 1) + (D_001A79F0_gp << 10)];
                if (((*counter_byte >> 4) & 7) != 7) {
                    *counter_byte += 0x10;
                }
            } else {
                unsigned char *counter_byte = &g_moby_nibble_table[((short)uid >> 1) + (D_001A79F0_gp << 10)];
                if ((*counter_byte & 7) != 7) {
                    *counter_byte += 1;
                }
            }
            *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
            class_info_a = *(char **)(moby + 0x24);
            *(int *)(moby + 0x98) = *(int *)(class_info_a + 0x10);
            *(int *)(moby + 0x98) = *(int *)(class_info_a + 0x10);
            moby_set_state(moby, 2, -1);
        }
        {
            int uid = *(unsigned short *)(moby + 0xB2);

            if (g_trigger_active_table.state[(short)uid] == 0) {
                int saved_count = g_moby_nibble_table[((short)uid >> 1) + (g_current_map_index[0] << 10)];

                if (!((uid & 1) ? ((saved_count >> 4) & 7) : (saved_count & 7)))
                    return;
            }
        }
        *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
        class_info_b = *(char **)(moby + 0x24);
        *(int *)(moby + 0x98) = *(int *)(class_info_b + 0x10);
        *(int *)(moby + 0x98) = *(int *)(class_info_b + 0x10);
        moby_set_state(moby, 2, -1);
        break;
    }
}
