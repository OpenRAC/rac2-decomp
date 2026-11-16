#include "common.h"
/* Adapted from RAC1's GPL-3.0 moby_ground_collision.c, get_next_moby_in_group. */
extern unsigned char *g_moby_group_current MACRO_ADDR;
extern short *g_moby_group_cursor MACRO_ADDR;
extern short g_moby_group_index;
extern int g_moby_pool_start MACRO_ADDR;
extern int g_moby_group_count MACRO_ADDR;
extern int g_moby_group_lists[];

/* Advances the group cursor to the next moby accepted by the state filter. */
int GetNextMobyInGroup(int *out_moby, unsigned char *moby, int includeInactive, int onlyInactive) {
    short *cursor;
    int is_inactive;

    *out_moby = 0;
    if (moby != g_moby_group_current) {
        if (g_moby_group_count < moby[0x21]) {
            return -1;
        }
        g_moby_group_current = 0;
        g_moby_group_cursor = (short *)g_moby_group_lists[moby[0x21]];
        if (g_moby_group_cursor == 0) {
            return -1;
        }
        g_moby_group_cursor--;
        {
            short link;

            do {
                g_moby_group_cursor++;
                cursor = g_moby_group_cursor;
                g_moby_group_index = *(unsigned short *)cursor & 0x7FFF;
                g_moby_group_current = (unsigned char *)(g_moby_pool_start + (g_moby_group_index << 8));
                link = *cursor;
            } while (link >= 0 && moby != g_moby_group_current);
            if (link < 0) {
                return -1;
            }
        }
    } else {
        short link = *g_moby_group_cursor;

        cursor = g_moby_group_cursor;
        if (link < 0) {
            return -1;
        }
    }
    for (;;) {
        short link;

        g_moby_group_cursor = cursor + 1;
        g_moby_group_index = *(unsigned short *)g_moby_group_cursor & 0x7FFF;
        g_moby_group_current = (unsigned char *)(g_moby_pool_start + (g_moby_group_index << 8));
        *out_moby = (int)g_moby_group_current;
        is_inactive = (signed char)g_moby_group_current[0x20] < 0;
        if ((includeInactive == 0 && onlyInactive == 0 && !is_inactive) || (includeInactive != 0 && (onlyInactive == 0 || is_inactive))) {
            return 0;
        }
        link = *g_moby_group_cursor;
        cursor = g_moby_group_cursor;
        if (link < 0) {
            break;
        }
    }
    *out_moby = 0;
    return -1;
}
