#include "include_asm.h"
#include "common.h"

extern s32 g_pickup_spawn_budget __attribute__((sda));
extern s32 g_pickup_counts[3] __attribute__((sda));
extern s32 g_pickup_slot_table[3][60];
extern s32 g_pickup_entry_table[4];
extern s32 *g_space_ship_pickup_slots __attribute__((sda));

/* Clears the counts and rows of spawned pickups and sets the starting limits from the ship. */
void pickup_reset_tables(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    s32 i, j;
    s32 *q;
    s32 a, b;

    g_pickup_spawn_budget = 0;
    for (i = 0; i < 3; i++) {
        s32 *row;

        g_pickup_counts[i] = 0;
        row = g_pickup_slot_table[i];
        for (j = 0x31; j >= 0; j--)
            row[j] = 0;
    }
    q = g_space_ship_pickup_slots;
    b = *(s16 *)(vars + 0x32E);
    g_pickup_entry_table[3] = b;
    q[3] = b;
    a = *(s16 *)(vars + 0x32A);
    g_pickup_entry_table[2] = a;
    q[2] = a;
    g_pickup_entry_table[0] = 0;
    q[0] = 0;
    g_pickup_entry_table[1] = 0;
    q[1] = 0;
}
