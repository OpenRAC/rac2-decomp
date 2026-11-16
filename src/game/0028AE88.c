#include "names.h"
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

extern GroupTable *g_hud_group_size_table[];
extern GroupEntry *g_hud_group_entries_a[];
extern GroupEntry *g_hud_group_entries_b[];

void LinkHudBank(s32 group, s32 size) {
    s32 first;
    s32 index;
    s32 end;
    if (g_hud_group_size_table[0]->c[group] == 0) {
        size = (size + 0xF) & 0xFFFFFFF0;
        g_hud_group_size_table[0]->c[group] = size;
        first = (group != 0) ? g_hud_group_size_table[0]->a[group - 1] : 0;
        end = g_hud_group_size_table[0]->a[group];
        for (index = first; index < end; index++) {
            g_hud_group_entries_b[0][index].w &= 0x7FFFFFFF;
            g_hud_group_entries_b[0][index].w += size;
        }
        first = (group != 0) ? g_hud_group_size_table[0]->b[group - 1] : 0;
        end = g_hud_group_size_table[0]->b[group];
        for (index = first; index < end; index++) {
            g_hud_group_entries_a[0][index].w &= 0x7FFFFFFF;
            g_hud_group_entries_a[0][index].w += size;
        }
    }
}
