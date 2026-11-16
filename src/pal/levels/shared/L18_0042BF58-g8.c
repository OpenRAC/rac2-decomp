#include "include_asm.h"
#include "names.h"

/* func_PAL_L18_0042BF58, the PAL copy of func_L18_004273F0: unit of its own, -G8 and -frac2-qcopy as the template. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef int TI128 __attribute__((mode(TI)));

extern unsigned int g_condition_target_lists[];
extern char *g_moby_l18_table;
extern char *D_L18_001B281C_sda __attribute__((sda));
extern int g_max_l18_group_index __attribute__((sda));
extern int g_enemy_timer_max __attribute__((sda));
extern int g_frame_l18_counter;
extern char g_str_spawner_debug[];
extern char g_hero_position[];
extern char *g_path_pointer_table[];

extern void STUB_printf(char *fmt, int a1, int a2);
extern float path_find_best_point_by_id(void *a0, void *a1, void *a2, int a3, float f12);
extern void moby_set_state(u8 *a0, int a1, int a2);
extern void moby_wake_linked_enemy_pal(u8 *a0);
extern float vec_distance_xy(void *a0, void *a1);

void func_PAL_L18_0042BF58(u8 *obj)
{
    u8 *state = *(u8 **)(obj + 0x68);
    u8 *best = 0;
    int found = 0;
    float best_d = 100000.0f;
    float vec[4];
    u16 *q;
    u8 *e;
    u8 *es;
    float d;

    if (*(int *)(state + 0x378) == -1) {
        if (*(int *)(state + 0x368) == -1) {
            STUB_printf(g_str_spawner_debug, *(s16 *)(obj + 0xB2), g_frame_l18_counter);
        } else {
            path_find_best_point_by_id(vec, obj + 0x10, g_hero_position, *(int *)(state + 0x368), 0.0f);
            found = 1;
        }
    } else {
        *(TI128 *)vec = *(TI128 *)(g_path_pointer_table[*(int *)(state + 0x378)] + 0x10);
    }

    q = (u16 *)g_condition_target_lists[obj[0x21]];
    while (obj[0x21] != 0xFF && obj[0x21] <= g_max_l18_group_index && q != 0 &&
           ((q != 0 && (s16)q[-1] >= 0) || q == (u16 *)g_condition_target_lists[obj[0x21]])) {
        e = (u8 *)(g_moby_l18_table + ((*q & 0x7FFF) << 8));
        if (e == 0)
            break;
        es = *(u8 **)(e + 0x68);
        d = vec_distance_xy(e + 0x10, vec);
        if (es != 0 && (es[0x399] & 1) != 0 && d < best_d) {
            best_d = d;
            best = e;
        }
        q++;
    }

    if (best != 0) {
        u8 *bs;
        int hw;
        best[0x31] = 1;
        hw = g_enemy_timer_max;
        *(u16 *)(best + 0x34) &= 0xFFFE;
        bs = *(u8 **)(best + 0x68);
        *(int *)(bs + 0x36C) = *(int *)(state + 0x36C);
        *(int *)(bs + 0x370) = *(int *)(state + 0x370);
        *(int *)(bs + 0x374) = *(int *)(state + 0x374);
        *(int *)(bs + 0x378) = *(int *)(state + 0x378);
        *(int *)(bs + 0x360) = *(int *)(state + 0x360);
        *(int *)(bs + 0x364) = *(int *)(state + 0x364);
        *(u16 *)(bs + 0x390) = ((s32)(hw) * 5 + 2) / 6;
        *(int *)(bs + 0x38C) = *(int *)(state + 0x378);
        bs[0x39A] = 1;
        bs[0x399] = 2;
        *(u16 *)(bs + 0x392) = state[0x398];
        if (found) {
            moby_set_state(best, 0, 4);
        } else if (bs[0x3EA] != 0 && *(int *)(bs + 0x3B4) != -1 &&
                   ((u8 *)((*(int *)(bs + 0x3B4) << 8) + (int)D_L18_001B281C_sda))[0x20] != 0xFE &&
                   ((u8 *)((*(int *)(bs + 0x3B4) << 8) + (int)D_L18_001B281C_sda))[0x20] != 0xFD) {
            moby_wake_linked_enemy_pal(best);
        } else {
            moby_set_state(best, 0, 3);
        }
    }
}
