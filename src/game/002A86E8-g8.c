#include "common.h"
/* Adapted from RAC1's GPL-3.0 moby_ground_collision.c, get_next_moby_in_group. */
extern unsigned char *D_001B1D40 MACRO_ADDR;
extern short *D_001B1D38 MACRO_ADDR;
extern short D_001B1D3C;
extern int D_001B1B5C MACRO_ADDR;
extern int D_001B1B78 MACRO_ADDR;
extern int D_001EE5A0[];

/* Advances the group cursor to the next moby accepted by the state filter. */
int GetNextMobyInGroup(int *out_moby, unsigned char *moby, int includeInactive, int onlyInactive) {
    short *cursor;
    int is_inactive;

    *out_moby = 0;
    if (moby != D_001B1D40) {
        if (D_001B1B78 < moby[0x21]) {
            return -1;
        }
        D_001B1D40 = 0;
        D_001B1D38 = (short *)D_001EE5A0[moby[0x21]];
        if (D_001B1D38 == 0) {
            return -1;
        }
        D_001B1D38--;
        {
            short link;

            do {
                D_001B1D38++;
                cursor = D_001B1D38;
                D_001B1D3C = *(unsigned short *)cursor & 0x7FFF;
                D_001B1D40 = (unsigned char *)(D_001B1B5C + (D_001B1D3C << 8));
                link = *cursor;
            } while (link >= 0 && moby != D_001B1D40);
            if (link < 0) {
                return -1;
            }
        }
    } else {
        short link = *D_001B1D38;

        cursor = D_001B1D38;
        if (link < 0) {
            return -1;
        }
    }
    for (;;) {
        short link;

        D_001B1D38 = cursor + 1;
        D_001B1D3C = *(unsigned short *)D_001B1D38 & 0x7FFF;
        D_001B1D40 = (unsigned char *)(D_001B1B5C + (D_001B1D3C << 8));
        *out_moby = (int)D_001B1D40;
        is_inactive = (signed char)D_001B1D40[0x20] < 0;
        if ((includeInactive == 0 && onlyInactive == 0 && !is_inactive) || (includeInactive != 0 && (onlyInactive == 0 || is_inactive))) {
            return 0;
        }
        link = *D_001B1D38;
        cursor = D_001B1D38;
        if (link < 0) {
            break;
        }
    }
    *out_moby = 0;
    return -1;
}
