#include "common.h"

extern void moby_mark_spawned(void *);

extern int IsPointInCuboid(char *, int);

extern void moby_set_state(char *, int, int);

extern int g_current_map_index[] MACRO_ADDR;
extern int D_001A79F0_gp SDATA(D_001A79F0);

extern unsigned char g_hero_position[];

extern unsigned char D_0019B4A8[];

/* The state table has an unknown trailing extent. */
extern struct {
    unsigned char pad[0x464];
    unsigned char state[0];
} D_L19_0021EA30;

/* Waits for the player to come near, then marks the object as used in the level's saved data and moves to its finished state. */
void UpdateRegionTriggeredObject(char *moby)
{
    char *classInfoA, *classInfoB;
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
                unsigned char *counterByte = &D_0019B4A8[((short)uid >> 1) + (D_001A79F0_gp << 10)];
                if (((*counterByte >> 4) & 7) != 7) {
                    *counterByte += 0x10;
                }
            } else {
                unsigned char *counterByte = &D_0019B4A8[((short)uid >> 1) + (D_001A79F0_gp << 10)];
                if ((*counterByte & 7) != 7) {
                    *counterByte += 1;
                }
            }
            *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
            classInfoA = *(char **)(moby + 0x24);
            *(int *)(moby + 0x98) = *(int *)(classInfoA + 0x10);
            *(int *)(moby + 0x98) = *(int *)(classInfoA + 0x10);
            moby_set_state(moby, 2, -1);
        }
        {
            int uid = *(unsigned short *)(moby + 0xB2);

            if (D_L19_0021EA30.state[(short)uid] == 0) {
                int savedCount = D_0019B4A8[((short)uid >> 1) + (g_current_map_index[0] << 10)];

                if (!((uid & 1) ? ((savedCount >> 4) & 7) : (savedCount & 7)))
                    return;
            }
        }
        *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
        classInfoB = *(char **)(moby + 0x24);
        *(int *)(moby + 0x98) = *(int *)(classInfoB + 0x10);
        *(int *)(moby + 0x98) = *(int *)(classInfoB + 0x10);
        moby_set_state(moby, 2, -1);
        break;
    }
}
