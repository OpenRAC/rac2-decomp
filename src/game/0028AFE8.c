#include "names.h"
/* Carried from rac3-decomp (src/levels/shared/L01_0041C4A0.c, func_L01_0041C4A0): the
   same instructions. Undoes func_0028AE88 for group N: its entries in both lists move
   down by the group's size and get their top bit back, and the size is cleared. Group 0
   also clears the halfword at +4 of every entry of the second list. */

#include "common.h"

typedef struct {
    u8 pad[0x14];
    int a[8];
    int b[16];
    int c[8];
} GroupTable;

extern int D_001B1888[];
extern int D_001B1894[];
extern int D_001B1898[];

void hud_unlink_bank_group(int group) {
    int group_size = ((GroupTable *)D_001B1888[0])->c[group];
    int i;
    int end;
    int start;
    int entry;

    if (group == 0) {
        for (entry = 0; entry < ((GroupTable *)D_001B1888[0])->b[0]; entry++) {
            *(s16 *)(entry * 8 + D_001B1894[0] + 4) = 0;
        }
    }
    start = group != 0 ? ((GroupTable *)D_001B1888[0])->a[group - 1] : 0;
    end = ((GroupTable *)D_001B1888[0])->a[group];
    for (i = start; i < end; i++) {
        *(int *)(i * 8 + D_001B1898[0]) -= group_size;
        *(int *)(i * 8 + D_001B1898[0]) |= 0x80000000;
    }
    start = group != 0 ? ((GroupTable *)D_001B1888[0])->b[group - 1] : 0;
    end = ((GroupTable *)D_001B1888[0])->b[group];
    for (i = start; i < end; i++) {
        *(int *)(i * 8 + D_001B1894[0]) -= group_size;
        *(int *)(i * 8 + D_001B1894[0]) |= 0x80000000;
    }
    ((GroupTable *)D_001B1888[0])->c[group] = 0;
}
