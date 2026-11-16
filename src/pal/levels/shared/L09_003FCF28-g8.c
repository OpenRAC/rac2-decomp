#include "names.h"
/* func_PAL_L09_003FCF28, the PAL copy of func_L09_003F8598: the same C, where the frame count stored at 0x2E0 is scaled for 50 Hz. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern int g_max_l09_group_id __attribute__((sda));

/* An absolute view of the canonical pool pointer; its extent stays unknown. */
extern unsigned char *D_L09_001B285C_base[] __asm__("D_L09_001B285C") __attribute__((sda));

extern unsigned short *g_track_entry_table[];

extern unsigned char *g_path_l09_table[];

extern int g_trooper_spawn_delay_max __attribute__((sda));

extern float vec_distance_xy(void *, void *);

extern int trooper_legs_find_largest_value(unsigned char *);

extern int trooper_legs_count_with_value(unsigned char *, int);

/* Hands this trooper's path settings to the nearest eligible trooper and starts it moving (PAL: 50 Hz timings). */
void transfer_state_to_nearest_eligible_object_pal(unsigned char *object) {
    unsigned char *source_data = *(unsigned char **)(object + 0x68);
    TI128 position;
    unsigned short *list;
    unsigned char *candidate;
    unsigned char *pool;
    unsigned char *candidate_data;
    unsigned char *best;
    unsigned char *best_data;
    int frame;
    int target_index;
    float best_distance;
    float distance;
    int group;

    target_index = *(int *)(source_data + 0x2C0);
    if (target_index == -1)
        return;
    qcopy(&position, g_path_l09_table[target_index] + 0x10);
    list = g_track_entry_table[object[0x21]];
    best = 0;
    best_distance = 100000.0f;
    for (;
         object[0x21] != 0xFF && object[0x21] <= g_max_l09_group_id && list != 0 &&
         ((list != 0 && (short)list[-1] >= 0) || list == g_track_entry_table[object[0x21]]);
         list++) {
        pool = D_L09_001B285C_base[0];
        candidate = pool + ((*list & 0x7FFF) << 8);
        if (candidate == 0)
            break;
        candidate_data = *(unsigned char **)(candidate + 0x68);
        distance = vec_distance_xy(candidate + 0x10, &position);
        if (candidate_data == 0)
            continue;
        if ((candidate_data[0x302] & 1) == 0)
            continue;
        if (*(int *)(source_data + 0x420) != -1) {
            group = trooper_legs_find_largest_value(object) + 1;
            if (group != *(int *)(candidate_data + 0x420))
                continue;
            if (trooper_legs_count_with_value(candidate, group) >= *(int *)(candidate_data + 0x42C))
                continue;
        }
        if (*(int *)(source_data + 0x424) != 0 && *(int *)(source_data + 0x424) != *(int *)(candidate_data + 0x424))
            continue;
        if (distance < best_distance) {
            best_distance = distance;
            best = candidate;
        }
    }
    if (best != 0) {
        best_data = *(unsigned char **)(best + 0x68);
        frame = g_trooper_spawn_delay_max;
        *(int *)(best_data + 0x2B0) = *(int *)(source_data + 0x2B0);
        *(int *)(best_data + 0x2B4) = *(int *)(source_data + 0x2B4);
        *(int *)(best_data + 0x2B8) = *(int *)(source_data + 0x2B8);
        *(int *)(best_data + 0x2BC) = *(int *)(source_data + 0x2BC);
        *(int *)(best_data + 0x2C0) = *(int *)(source_data + 0x2C0);
        *(int *)(best_data + 0x2D0) = *(int *)(source_data + 0x2D0);
        *(int *)(best_data + 0x2D4) = *(int *)(source_data + 0x2D4);
        *(unsigned short *)(best_data + 0x2E0) = ((s32)(frame) * 5 + 2) / 6;
        *(int *)(best_data + 0x2DC) = *(int *)(source_data + 0x2C0);
        best_data[0x2EA] = 1;
        best_data[0x302] = (best_data[0x302] | 2) & 0xFE;
        best_data[0x303] = source_data[0x303];
        *(unsigned short *)(best + 0x34) = *(unsigned short *)(best + 0x34) & 0xFFFD;
        best_data[0x31D] = 1;
        best_data[0x31C] = 1;
    }
}
