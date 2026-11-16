#include "include_asm.h"
#include "common.h"

/* Reward slots: a spawn kind is available while value has not reached limit. */
typedef struct { char pad[16]; int limit, value; char tail[16]; } RewardSlot;
extern RewardSlot g_reward_slot_table[];
/* Spawn counters: [22..27] per kind, [28] the total. */
extern int g_mission_state[];
extern int g_current_map_index __attribute__((sda));
extern int g_map_play_counts[];
extern int math_random_int_below(int);
extern int table_find_last_used_entry(int);
/* The spawners return the new object, or 0. */
extern char *func_L05_003CD1A8(char *);
extern char *moby_spawn_class_a(char *);
extern char *moby_spawn_class_b(char *);
extern char *moby_spawn_class_c(char *);
extern void func_L05_003CFC48(char *);
extern char *pickup_spawn_homing(char *);

/* Drops a reward at the object: one roll in four picks a kind (an unavailable
   kind falls back to another drop). A nonzero bonus adds a second roll whose
   chance in 100 comes from a per-level table, capped at 11. */
void hrugis_drop_reward(char *object, int bonus)
{
    int slot;
    int chance;

    if (math_random_int_below(4) == 0) {
        switch (math_random_int_below(48)) {
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
                func_L05_003CFC48(object);
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
