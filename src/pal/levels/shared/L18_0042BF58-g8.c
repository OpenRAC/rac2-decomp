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

/* Picks the closest idle enemy to this spawner's target point and wakes it up with the spawner's settings (PAL). */
void spawner_activate_nearest_enemy_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *best_moby = 0;
    int found_path_point = 0;
    float best_dist = 100000.0f;
    float target_pos[4];
    u16 *group_list;
    u8 *cand;
    u8 *cand_vars;
    float dist;

    if (*(int *)(vars + 0x378) == -1) {
        if (*(int *)(vars + 0x368) == -1) {
            STUB_printf(g_str_spawner_debug, *(s16 *)(moby + 0xB2), g_frame_l18_counter);
        } else {
            path_find_best_point_by_id(target_pos, moby + 0x10, g_hero_position, *(int *)(vars + 0x368), 0.0f);
            found_path_point = 1;
        }
    } else {
        *(TI128 *)target_pos = *(TI128 *)(g_path_pointer_table[*(int *)(vars + 0x378)] + 0x10);
    }

    group_list = (u16 *)g_condition_target_lists[moby[0x21]];
    while (moby[0x21] != 0xFF && moby[0x21] <= g_max_l18_group_index && group_list != 0 &&
           ((group_list != 0 && (s16)group_list[-1] >= 0) || group_list == (u16 *)g_condition_target_lists[moby[0x21]])) {
        cand = (u8 *)(g_moby_l18_table + ((*group_list & 0x7FFF) << 8));
        if (cand == 0)
            break;
        cand_vars = *(u8 **)(cand + 0x68);
        dist = vec_distance_xy(cand + 0x10, target_pos);
        if (cand_vars != 0 && (cand_vars[0x399] & 1) != 0 && dist < best_dist) {
            best_dist = dist;
            best_moby = cand;
        }
        group_list++;
    }

    if (best_moby != 0) {
        u8 *best_vars;
        int timer_max;
        best_moby[0x31] = 1;
        timer_max = g_enemy_timer_max;
        *(u16 *)(best_moby + 0x34) &= 0xFFFE;
        best_vars = *(u8 **)(best_moby + 0x68);
        *(int *)(best_vars + 0x36C) = *(int *)(vars + 0x36C);
        *(int *)(best_vars + 0x370) = *(int *)(vars + 0x370);
        *(int *)(best_vars + 0x374) = *(int *)(vars + 0x374);
        *(int *)(best_vars + 0x378) = *(int *)(vars + 0x378);
        *(int *)(best_vars + 0x360) = *(int *)(vars + 0x360);
        *(int *)(best_vars + 0x364) = *(int *)(vars + 0x364);
        *(u16 *)(best_vars + 0x390) = ((s32)(timer_max) * 5 + 2) / 6;
        *(int *)(best_vars + 0x38C) = *(int *)(vars + 0x378);
        best_vars[0x39A] = 1;
        best_vars[0x399] = 2;
        *(u16 *)(best_vars + 0x392) = vars[0x398];
        if (found_path_point) {
            moby_set_state(best_moby, 0, 4);
        } else if (best_vars[0x3EA] != 0 && *(int *)(best_vars + 0x3B4) != -1 &&
                   ((u8 *)((*(int *)(best_vars + 0x3B4) << 8) + (int)D_L18_001B281C_sda))[0x20] != 0xFE &&
                   ((u8 *)((*(int *)(best_vars + 0x3B4) << 8) + (int)D_L18_001B281C_sda))[0x20] != 0xFD) {
            moby_wake_linked_enemy_pal(best_moby);
        } else {
            moby_set_state(best_moby, 0, 3);
        }
    }
}
