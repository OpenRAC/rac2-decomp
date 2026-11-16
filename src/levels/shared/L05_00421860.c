#include "names.h"
/* func_L05_00421860, in a unit of its own (default flags). Retail's allocation in the two
   counter blocks follows from the two callees returning a value (the unused $v0 at the call)
   and from each block taking the counter table in a pointer of its own. */
#include "common.h"

/* The 0x28-byte slots of D_L05_002A1800 (L05_0037AC80.c names the same fields). */
typedef struct {
    int state, next, pad08[2];
    int limit;
    int value;
    int pad18[4];
} L05Slot40_00421860;

extern L05Slot40_00421860 g_spawn_entry_table[];
extern int g_feltzin_challenge_state[] MACRO_ADDR;
extern int table_find_last_used_entry(int);
extern char *pickup_spawn_homing(char *);
extern char *pickup_spawn_homing_variant(char *);

/* Runs one of two spawners, depending on whether slot 1 is missing or its value still equals
   its limit, and counts the spawn in the game's counters (its own one and the total). */
void moby_spawn_and_count(char *object)
{
    int slot = table_find_last_used_entry(1);

    if (slot < 0 || g_spawn_entry_table[slot].value == g_spawn_entry_table[slot].limit) {
        int *counts;

        pickup_spawn_homing(object);
        counts = g_feltzin_challenge_state;
        counts[0x5C / 4]++;
        counts[0x70 / 4]++;
    } else {
        int *counts;

        pickup_spawn_homing_variant(object);
        counts = g_feltzin_challenge_state;
        counts[0x64 / 4]++;
        counts[0x70 / 4]++;
    }
}
