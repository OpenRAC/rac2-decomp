/* Carried from rac3-decomp (src/frontbin/38DED0.c, func_00392FD0): the same instructions.
   Gives group N of the table at D_001B1888 its size (rounded up to 16) once: the
   entries of the group in both entry lists (D_001B1898, D_001B1894) lose their top bit and
   move up by it. func_0028AFE8 undoes it. */

#include "common.h"

typedef struct {
    u8 p0[0x14];
    s32 a[8];
    s32 b[16];
    s32 c[1];
} GroupTable;

typedef struct {
    u32 w;
    u32 x;
} GroupEntry;

extern GroupTable *D_001B1888[];
extern GroupEntry *D_001B1894[];
extern GroupEntry *D_001B1898[];

/* Links the HUD bank group n with the given size, clearing the top bit in the entries of the group. */
void func_0028AE88(s32 n, s32 size) {
    s32 i;
    s32 j;
    s32 end;
    if (D_001B1888[0]->c[n] == 0) {
        size = (size + 0xF) & 0xFFFFFFF0;
        D_001B1888[0]->c[n] = size;
        i = (n != 0) ? D_001B1888[0]->a[n - 1] : 0;
        end = D_001B1888[0]->a[n];
        for (j = i; j < end; j++) {
            D_001B1898[0][j].w &= 0x7FFFFFFF;
            D_001B1898[0][j].w += size;
        }
        i = (n != 0) ? D_001B1888[0]->b[n - 1] : 0;
        end = D_001B1888[0]->b[n];
        for (j = i; j < end; j++) {
            D_001B1894[0][j].w &= 0x7FFFFFFF;
            D_001B1894[0][j].w += size;
        }
    }
}
