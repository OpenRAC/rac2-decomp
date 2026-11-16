#include "include_asm.h"
#include "common.h"

/* Reward slots: a spawn kind is available while value has not reached limit. */
typedef struct { char pad[16]; int limit, value; char tail[16]; } RewardSlot;
extern RewardSlot g_spawn_entry_table[];
/* Spawn counters: [22..27] per kind, [28] the total. */
extern int g_feltzin_challenge_state[];
extern int g_current_map_index __attribute__((sda));
extern int g_map_play_counts[];
extern int func_332AB8(int);
extern int func_L05_0037AAC8(int);
/* The spawners return the new object, or 0. */
extern char *func_L05_003CD1A8(char *);
extern char *moby_spawn_class_a(char *);
extern char *moby_spawn_class_b(char *);
extern char *moby_spawn_class_c(char *);
extern void moby_spawn_and_count(char *);
extern char *pickup_spawn_homing(char *);

/* Drops a reward at the object: one roll in four picks a kind (an unavailable
   kind falls back to another drop). A nonzero bonus adds a second roll whose
   chance in 100 comes from a per-level table, capped at 22. */
/* Drops a random reward where the object was, with a possible bonus drop. */
void func_L05_00421908(char *object, int bonus)
{
    int slot;
    int chance;

    if (func_332AB8(4) == 0) {
        switch (func_332AB8(48)) {
        case 0: case 1: case 2: case 3:
            slot = func_L05_0037AAC8(6);
            if (slot < 0 || g_spawn_entry_table[slot].value == g_spawn_entry_table[slot].limit)
                goto ordinary;
            func_L05_003CD1A8(object);
            g_feltzin_challenge_state[24]++;
            g_feltzin_challenge_state[28]++;
            break;
        case 5:
            slot = func_L05_0037AAC8(2);
            if (slot < 0 || g_spawn_entry_table[slot].value == g_spawn_entry_table[slot].limit)
                goto fallback;
            moby_spawn_class_a(object);
            g_feltzin_challenge_state[26]++;
            g_feltzin_challenge_state[28]++;
            break;
        case 6:
            slot = func_L05_0037AAC8(3);
            if (slot < 0 || g_spawn_entry_table[slot].value == g_spawn_entry_table[slot].limit)
                goto fallback;
            moby_spawn_class_b(object);
            g_feltzin_challenge_state[22]++;
            g_feltzin_challenge_state[28]++;
            break;
        case 7:
            slot = func_L05_0037AAC8(4);
            if (slot < 0 || g_spawn_entry_table[slot].value == g_spawn_entry_table[slot].limit) {
        case 4:
        fallback:
                moby_spawn_and_count(object);
                break;
            }
            moby_spawn_class_c(object);
            g_feltzin_challenge_state[27]++;
            g_feltzin_challenge_state[28]++;
            break;
        default:
        ordinary:
            pickup_spawn_homing(object);
            g_feltzin_challenge_state[23]++;
            g_feltzin_challenge_state[28]++;
            break;
        }
    }
    if (bonus) {
        chance = g_map_play_counts[g_current_map_index] * 2;
        if (chance > 22)
            chance = 22;
        if (chance >= func_332AB8(100)) {
            func_L05_003CD1A8(object);
            g_feltzin_challenge_state[24]++;
            g_feltzin_challenge_state[28]++;
        }
    }
}
