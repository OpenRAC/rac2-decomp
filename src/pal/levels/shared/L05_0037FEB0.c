#include "include_asm.h"
#include "common.h"

/* func_PAL_L05_0037FEB0, the PAL copy of func_L05_0037D6E8: the same C, where two f14 values
   are scaled to 50 Hz. */

struct S_L05_002A1800 {
    char pad0[0xC];
    int f0C;
    int f10;
    int f14;
    char pad1[0x10];
};

extern struct S_L05_002A1800 g_spawn_entry_table[];

extern int table_find_last_used_entry(int);

void func_PAL_L05_0037FEB0(void)
{
    int i;

    for (i = 0; i < 15; i++)
        g_spawn_entry_table[i].f14 = g_spawn_entry_table[i].f0C;
    g_spawn_entry_table[7].f14 = ((s32)g_spawn_entry_table[7].f0C * 5 + 2) / 6;
    g_spawn_entry_table[13].f14 = ((s32)g_spawn_entry_table[13].f0C * 5 + 2) / 6;
    i = table_find_last_used_entry(6);
    g_spawn_entry_table[i].f14 = g_spawn_entry_table[i].f10;
}
