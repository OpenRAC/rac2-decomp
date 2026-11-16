#include "include_asm.h"
#include "names.h"
#include "moby_classes.h"
#include "names.h"

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
void visibomb_missile_watcher_update(char *object)
{
    char *state;
    char *target = 0;
    char *node;
    char *slot;
    char *pos;
    int none;

    *(unsigned char *)(object + 0x30) = 0xFF;
    state = *(char **)(object + 0x68);
    if (g_game_mode != 0x1C)
        goto reset;
    for (node = g_moby_l00_list_head[0]; node != 0; node = *(char **)(node + 0x28)) {
        if (*(short *)(node + 0xAA) == MOBY_CLASS_VISIBOMB_MISSILE) {
            target = node;
            break;
        }
    }
    if (target == 0 || *(short *)(target + 0xAA) != MOBY_CLASS_VISIBOMB_MISSILE) {
reset:
        *(int *)(state + 0x140) = 0;
        return;
    }
    pos = target + 0x10;
    none = -1;
    *(int *)(state + 0x140) = *(int *)(state + 0x140) + 1;
    slot = state;
    do {
        if (*(int *)slot != none && *(float *)(target + 0x18) > *(float *)(slot + 4) &&
            *(float *)(target + 0x18) < *(float *)(slot + 8)) {
            char *other = g_object_pointer_table[*(int *)slot];
            if (point_in_path_xy(pos, other + 0x10, *(int *)other) != 0) {
                *(int *)(state + 0x140) = 0;
                break;
            }
        }
        if (IsPointInCuboid(pos, *(int *)(slot + 0xC)) != 0) {
            *(int *)(state + 0x140) = 0;
            break;
        }
        slot += 0x10;
    } while ((int)slot < (int)state + 0x140);
    if (*(int *)(state + 0x140) > 0) {
        if (g_visibomb_watcher_flag != 0)
            ref_L00_003A0C00_00(g_visibomb_script_data, object);
        if (*(int *)(state + 0x140) >= 0x5B)
            tether_release(target, *(char **)(target + 0x68));
    }
}
