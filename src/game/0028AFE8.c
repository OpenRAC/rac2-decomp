/* Carried from rac3-decomp (src/levels/shared/L01_0041C4A0.c, func_L01_0041C4A0): the
   same instructions. Undoes LinkHudBank for group N: its entries in both lists move
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

/* Resets the entries of HUD group n in the group table. */
void func_0028AFE8(int n) {
    int off = ((GroupTable *)D_001B1888[0])->c[n];
    int i;
    int end;
    int start;
    int j;

    if (n == 0) {
        for (j = 0; j < ((GroupTable *)D_001B1888[0])->b[0]; j++) {
            *(s16 *)(j * 8 + D_001B1894[0] + 4) = 0;
        }
    }
    start = n != 0 ? ((GroupTable *)D_001B1888[0])->a[n - 1] : 0;
    end = ((GroupTable *)D_001B1888[0])->a[n];
    for (i = start; i < end; i++) {
        *(int *)(i * 8 + D_001B1898[0]) -= off;
        *(int *)(i * 8 + D_001B1898[0]) |= 0x80000000;
    }
    start = n != 0 ? ((GroupTable *)D_001B1888[0])->b[n - 1] : 0;
    end = ((GroupTable *)D_001B1888[0])->b[n];
    for (i = start; i < end; i++) {
        *(int *)(i * 8 + D_001B1894[0]) -= off;
        *(int *)(i * 8 + D_001B1894[0]) |= 0x80000000;
    }
    ((GroupTable *)D_001B1888[0])->c[n] = 0;
}
