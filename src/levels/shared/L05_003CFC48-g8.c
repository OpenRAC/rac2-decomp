#include "common.h"

typedef struct { char pad[16]; int limit,value; char tail[16]; } RewardSlot;
extern RewardSlot g_spawn_entry_table[];
extern int g_feltzin_challenge_state[];
extern int table_find_last_used_entry(int);
extern char *pickup_spawn_homing(char *);
extern char *pickup_spawn_homing_variant(char *);

/* Drops a reward, choosing a different kind if the first kind is already full, and counts it. */
void func_L05_003CFC48(char *object)
{
    int slot=table_find_last_used_entry(1);
    if(slot<0 || g_spawn_entry_table[slot].value==g_spawn_entry_table[slot].limit) {
        pickup_spawn_homing(object);
        g_feltzin_challenge_state[23]++;
        g_feltzin_challenge_state[28]++;
    } else {
        pickup_spawn_homing_variant(object);
        g_feltzin_challenge_state[25]++;
        g_feltzin_challenge_state[28]++;
    }
}
