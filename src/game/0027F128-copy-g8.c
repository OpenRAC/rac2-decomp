#include "include_asm.h"

/* -G8 sibling of src/game/0027F128.c. */

typedef unsigned char u8;
typedef struct { u8 pad[0x1c]; int flags; short x, y, w, h; u8 tail[8]; } CopyRegion;
extern CopyRegion D_001B8A10[];
extern int D_001B1658;
extern int D_001B22B4;
extern u8 *D_001B22A0[];
extern void func_00285708(int, int, int, int, void *);
extern void func_001244B8(int, int);
extern void func_00280670(void *, int);

void func_00280710(void) {
    u8 *buffers[2];
    int current, next, i, index;

    if (D_001B1658 == 0) return;
    buffers[0] = D_001B22A0[1 - D_001B22B4];
    buffers[1] = buffers[0] + 0x40000;
    current = 0;
    next = -1;
    /* Region flag 4 selects an entry; flag 1 retires it after its pass, dropping the active count. */
    for (i = 31; i >= 0; i--) {
        if (D_001B8A10[i].flags & 4) {
            next = i;
            func_00285708(D_001B8A10[i].x, D_001B8A10[i].y, D_001B8A10[i].w, D_001B8A10[i].h,
                          buffers[current]);
            func_001244B8(0, 0);
        }
    }
    if (next == -1) return;
    index = next;
    while (index >= 0) {
        current = 1 - current;
        next = -1;
        for (i = index - 1; i >= 0; i--) {
            if (D_001B8A10[i].flags & 4) {
                next = i;
                func_00285708(D_001B8A10[i].x, D_001B8A10[i].y, D_001B8A10[i].w, D_001B8A10[i].h,
                              buffers[current]);
            }
        }
        func_00280670(buffers[1 - current], index);
        if ((D_001B8A10 + index)->flags & 1) {
            (D_001B8A10 + index)->flags &= ~5;
            D_001B1658--;
        }
        if (next >= 0) func_001244B8(0, 0);
        index = next;
    }
}
