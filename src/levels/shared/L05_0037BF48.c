#include "common.h"
extern char *func_379CA0(char *);
extern int func_001163B0(void);
extern int moby_is_in_use(char *);
extern int moby_get_link_value(char *);
extern unsigned short *g_spawn_list_table[];
extern char *g_feltzin_target_mobys MACRO_ADDR;
extern signed char g_group_grid_layout[];
extern float IntToFloat(int);
/* Spreads the listed child objects out in a grid pattern around the parent, picking one of two layouts at random. */
void group_layout_members_in_grid(char *obj)
{
    unsigned short *entry;
    char *child, *parent;
    int off, choice, ordinal, i, count, row;

    short entry_word;
    if (g_spawn_list_table[*(unsigned char *)(obj + 0x21)] == 0) return;
    parent = func_379CA0(obj);
    ordinal = 1;
    choice = func_001163B0() % 2;
    entry = g_spawn_list_table[*(unsigned char *)(obj + 0x21)];
    do {
        off = (*entry & 0x7fff) << 8;
        child = func_379CA0(g_feltzin_target_mobys + off);
        if (moby_is_in_use(g_feltzin_target_mobys + off) &&
            !moby_get_link_value(g_feltzin_target_mobys + off) &&
            *(int *)(child + 0x1c) == *(int *)(parent + 0x1c)) {
            float left = -10.5f, right = 10.5f;
            *(int *)(child + 0x20) = ordinal++;
            count = -1;
            for (i = 0; i < 25; i++) {
                if (g_group_grid_layout[i + choice * 25 + (*(int *)(parent + 0x18) - 3) * 50]) {
                    if (++count == *(int *)(child + 0x20)) {
                        *(int *)(child + 8) = 0;
                        row = i / 5;
                        *(float *)child = IntToFloat(row) * left;
                        *(float *)(child + 4) = IntToFloat(i - (i / 5) * 5 - 2) * right;
                        break;
                    }
                }
            }
        }
        entry_word = *(short *)entry;
        entry++;
        if (entry_word < 0) break;
        if (ordinal == *(int *)(parent + 0x18)) break;
    } while (entry_word >= 0);
}
