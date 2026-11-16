#include "include_asm.h"
#include "common.h"

/* -G8 unit for func_00325DA0, which reads D_001B1688 and D_001B1B5C absolutely and
   D_001B1B78 through $gp (0031F210-g8.c declares D_001B1B5C sda). func_00325D30, its
   neighbour in retail, must stay in front of it: this cc1's combine does not reset
   mem_last_set before its nonzero-bits scan, so the previous function's last store or
   call leaves the group byte's first load unproven, and the loop test keeps retail's
   `andi $v1,$a3,0xFF`. Compiled alone, the mask folds away and the body is 4 bytes short. */

extern void moby_mark_spawned(void *);

/* Removes the two attached part objects of the given entries. */
void group_destroy_attached_parts(char *object, char *entries)
{
    int count = 1;
    do {
        char *child = *(char **)entries;
        count--;
        entries += 4;
        if (child != 0 && *(short *)(child + 0xAA) == 0xAA2 /* moby class 2722 */)
            moby_mark_spawned(child);
    } while (count >= 0);
}

extern int g_game_time;
extern char *g_moby_pool_start;
extern int g_moby_group_count MACRO_ADDR;
extern unsigned short *g_moby_group_lists[];
extern void group_draw_joint_glows(char *);
extern void gfx_register_overlay_draw_callback(void (*)(char *), char *);

/* Copies a shared counter value to every member of the object's group that has the same kind. It then schedules the group's glow effects. */
void group_sync_counter(unsigned char *object, int *field)
{
    unsigned short *p;
    unsigned char *e;
    int offset;

    if (*field != g_game_time) {
        if (object[0x21] == 0xFF) {
            *field = g_game_time;
        } else {
            offset = (char *)field - *(char **)(object + 0x68);
            for (p = g_moby_group_lists[object[0x21]];
                 object[0x21] != 0xFF && object[0x21] <= g_moby_group_count && p != 0 &&
                 ((p != 0 && (short)p[-1] >= 0) || p == g_moby_group_lists[object[0x21]]);
                 p++) {
                e = (unsigned char *)g_moby_pool_start + ((*p & 0x7FFF) << 8);
                if (e == 0)
                    break;
                if (*(short *)(e + 0xAA) == *(short *)(object + 0xAA))
                    *(int *)(*(char **)(e + 0x68) + ((offset >> 2) << 2)) = g_game_time;
            }
        }
        gfx_register_overlay_draw_callback(group_draw_joint_glows, (char *)object);
    }
}
