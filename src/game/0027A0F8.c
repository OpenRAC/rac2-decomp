#include "include_asm.h"
#include "names.h"

extern unsigned char D_L06_001B23C0[];

/* The nested lookup table is bound independently in each program. */
/* Finds the visibility data for a grid cell using three nested lookups. Returns 0 if the cell has none. */
int vis_find_cell_data(int a0, int a1, int a2)
{
    unsigned char *base = *(unsigned char **)D_L06_001B23C0;
    unsigned char *end = base + *(int *)base;
    unsigned short *node = (unsigned short *)(base + 4);
    int i2;
    int i1;
    int i0;

    i2 = a2 - node[0];
    if (i2 < 0) return 0;
    if (!(i2 < node[1])) return 0;
    if (!node[i2 + 2]) return 0;
    node = (unsigned short *)(base + node[i2 + 2] * 4);
    i1 = a1 - node[0];
    if (i1 < 0) return 0;
    if (!(i1 < node[1])) return 0;
    if (!node[i1 + 2]) return 0;
    node = (unsigned short *)(base + node[i1 + 2] * 4);
    i0 = a0 - node[0];
    if (i0 < 0 || !(i0 < node[1])) return 0;
    if (node[i0 + 2] == 0xFFFF) return 0;
    return (int)(end + node[i0 + 2] * 128);
}
