#include "include_asm.h"
#include "names.h"

/* func_PAL_L00_003A3FC8 is defined in L00_003A3FC8-tile.c. */

extern int g_game_mode;
extern char *g_moby_l00_list_head[] __attribute__((sda));
extern char *g_object_pointer_table[];
extern int g_visibomb_watcher_flag __attribute__((sda));
extern char g_visibomb_script_data[];
extern int point_in_path_xy(char *a, char *b, int c);
extern int IsPointInCuboid(char *a, int b);
extern void ref_L00_003A0C00_00(char *a, char *b);
extern void tether_release(char *a, char *b);

/* Marks the object not drawable, finds the first object of the global list with id 0xAC and
   counts one more frame in the object's state; checks the sixteen-byte regions of the state
   against the target's position and releases the count as soon as one holds. */
void visibomb_missile_watcher_update_pal(char *object)
{
    char *state;
    char *target = 0;
    char *p;
    char *e;
    char *pos;
    int none;

    *(unsigned char *)(object + 0x30) = 0xFF;
    state = *(char **)(object + 0x68);
    if (g_game_mode != 0x1C)
        goto reset;
    for (p = g_moby_l00_list_head[0]; p != 0; p = *(char **)(p + 0x28)) {
        if (*(short *)(p + 0xAA) == 0xAC) {
            target = p;
            break;
        }
    }
    if (target == 0 || *(short *)(target + 0xAA) != 0xAC) {
reset:
        *(int *)(state + 0x140) = 0;
        return;
    }
    pos = target + 0x10;
    none = -1;
    *(int *)(state + 0x140) = *(int *)(state + 0x140) + 1;
    e = state;
    do {
        if (*(int *)e != none && *(float *)(target + 0x18) > *(float *)(e + 4) &&
            *(float *)(target + 0x18) < *(float *)(e + 8)) {
            char *t = g_object_pointer_table[*(int *)e];
            if (point_in_path_xy(pos, t + 0x10, *(int *)t) != 0) {
                *(int *)(state + 0x140) = 0;
                break;
            }
        }
        if (IsPointInCuboid(pos, *(int *)(e + 0xC)) != 0) {
            *(int *)(state + 0x140) = 0;
            break;
        }
        e += 0x10;
    } while ((int)e < (int)state + 0x140);
    if (*(int *)(state + 0x140) > 0) {
        if (g_visibomb_watcher_flag != 0)
            ref_L00_003A0C00_00(g_visibomb_script_data, object);
        if (*(int *)(state + 0x140) >= 0x4C)
            tether_release(target, *(char **)(target + 0x68));
    }
}

