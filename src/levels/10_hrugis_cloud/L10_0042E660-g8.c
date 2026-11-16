#include "common.h"

typedef struct { char pad[16]; int limit, value; char tail[16]; } RewardSlot;
extern RewardSlot g_reward_slot_table[];
extern int g_mission_state[];
extern int g_current_map_index __attribute__((sda));
extern int g_map_play_counts[];
extern int math_random_int_below(int);
extern int table_find_last_used_entry(int);
extern char *func_L05_003CD1A8(char *);
extern char *moby_spawn_class_a(char *);
extern char *moby_spawn_class_b(char *);
extern char *moby_spawn_class_c(char *);
extern void func_L10_0042E5B8(char *);
extern char *pickup_spawn_homing(char *);
extern int g_cloud_reward_dropped __attribute__((sda));

/* Select an available reward kind, update the per-kind and total spawn counts,
 * and optionally roll an additional reward using the current level chance. */
void cloud_drop_reward(char *object, int bonus)
{
    int slot;
    int chance;

    if (math_random_int_below(*(int *)(*(char **)(object + 0x68) + 0x14)) == 0 || !g_cloud_reward_dropped) {
        slot = math_random_int_below(48);
        g_cloud_reward_dropped = 1;
        switch (slot) {
        case 0: case 1: case 2: case 3:
            slot = table_find_last_used_entry(6);
            if (slot < 0 || g_reward_slot_table[slot].value == g_reward_slot_table[slot].limit)
                goto ordinary;
            func_L05_003CD1A8(object);
            g_mission_state[24]++;
            g_mission_state[28]++;
            break;
        case 5:
            slot = table_find_last_used_entry(2);
            if (slot < 0 || g_reward_slot_table[slot].value == g_reward_slot_table[slot].limit)
                goto fallback;
            moby_spawn_class_a(object);
            g_mission_state[26]++;
            g_mission_state[28]++;
            break;
        case 6:
            slot = table_find_last_used_entry(3);
            if (slot < 0 || g_reward_slot_table[slot].value == g_reward_slot_table[slot].limit)
                goto fallback;
            moby_spawn_class_b(object);
            g_mission_state[22]++;
            g_mission_state[28]++;
            break;
        case 7:
            slot = table_find_last_used_entry(4);
            if (slot < 0 || g_reward_slot_table[slot].value == g_reward_slot_table[slot].limit) {
        case 4:
        fallback:
                func_L10_0042E5B8(object);
                break;
            }
            moby_spawn_class_c(object);
            g_mission_state[27]++;
            g_mission_state[28]++;
            break;
        default:
        ordinary:
            pickup_spawn_homing(object);
            g_mission_state[23]++;
            g_mission_state[28]++;
            break;
        }
    }
    if (bonus) {
        chance = g_map_play_counts[g_current_map_index] * 2;
        if (chance > 11)
            chance = 11;
        if (chance >= math_random_int_below(100)) {
            func_L05_003CD1A8(object);
            g_mission_state[24]++;
            g_mission_state[28]++;
        }
    }
}
