#include "include_asm.h"
#include "names.h"

extern unsigned int g_equipment_bits __attribute__((sda));
extern int g_spawn_entry_table[];

/* func_L05_003008C0 is defined in L05_003008C0-quad.c. */

/* func_L05_00302CE8 is defined in L05_00302CE8-g8.c. */

extern int func_002FEF40(int);

typedef struct L05Glyph L05Glyph;
extern int FontPrintWrapped(int, int, int, int, unsigned long long, unsigned char *, int,
                             unsigned long long, L05Glyph *);

extern L05Glyph g_font_glyph_table[];

/* Word-wrapped text in a box with a fresh texture and the shared font; returns the height used. */
int text_print_wrapped_default(int x, int y, int width, int height, unsigned long long color,
                      unsigned char *text, int count)
{
    int step = func_002FEF40(2);

    return FontPrintWrapped(x, y, width, height, color, text, count, step, g_font_glyph_table);
}


extern int g_level_pair_store[];

/* Stores the pair and steps the second half of the counter. */
/* Stores a pair of numbers in a shared block, adding one to the second. */
void level_store_pair_with_increment(int first, int second) {
    int *pair = g_level_pair_store;
    pair[0x11] = second + 1;
    pair[0x10] = first;
}

/* func_L05_00324DB8 is defined in L05_003008C0-g8.c (this unit has no $gp access for it). */








/* func_L05_0033D3A0 is in L05_003008C0-reaction-g8.c. */




/* func_L05_00352B28 lives in L05_00352B28.c:
   its grouped vector copy and debug division labels need a per-file profile. */

/* Fills the slot table from the hero's equipment bits (the word func_002E6178 reads).
 * The table holds 15 entries of 0x28 bytes; each bit group sets the +0x00 and +0x18
 * words of a few entries; bits 7-8, 10-11 and 14-15 are read as two-bit fields. */
void InitSlotFlagsFromEquipment(void)
{
    if (g_equipment_bits & 0x40) {
        g_spawn_entry_table[0x158/4] = 1;
        g_spawn_entry_table[0x140/4] = 1;
        g_spawn_entry_table[0] = 0;
    } else {
        g_spawn_entry_table[0] = 1;
        g_spawn_entry_table[0x140/4] = 0;
    }
    {
        int *state = g_spawn_entry_table;
        int flags;
        state[0x18/4] = 1;
        flags = g_equipment_bits;
        if (flags & 0x100) {
            state[0x1D0/4] = 1;
            state[0x90/4] = 1;
        } else if (flags & 0x80) {
            state[0x1D0/4] = 0;
            state[0x90/4] = 1;
        } else {
            state[0x1D0/4] = 0;
            state[0x90/4] = 0;
        }
    }
    {
        int *state = g_spawn_entry_table;
        int flags = g_equipment_bits;
        state[0x78/4] = 0;
        state[0x1B8/4] = 0;
        if (flags & 0x200) {
            state[0x28/4] = 0;
            state[0x180/4] = 1;
            state[0x168/4] = 1;
        } else {
            state[0x168/4] = 0;
            state[0x28/4] = 1;
        }
    }
    {
        int *state = g_spawn_entry_table;
        int flags;
        state[0x40/4] = 1;
        flags = g_equipment_bits;
        if (flags & 0x800) {
            state[0x1A8/4] = 1;
            state[0x68/4] = 1;
        } else if (flags & 0x400) {
            state[0x1A8/4] = 0;
            state[0x68/4] = 1;
        } else {
            state[0x1A8/4] = 0;
            state[0x68/4] = 0;
        }
    }
    {
        int *state = g_spawn_entry_table;
        int flags = g_equipment_bits;
        state[0x50/4] = 0;
        state[0x190/4] = 0;
        if (flags & 0x1000) state[0xB8/4] = 1;
        else state[0xB8/4] = 0;
    }
    {
        int *state = g_spawn_entry_table;
        int flags = g_equipment_bits;
        state[0xA0/4] = 0;
        if (flags & 0x2000) state[0xE0/4] = 1;
        else state[0xE0/4] = 0;
    }
    {
        int *state = g_spawn_entry_table;
        int flags = g_equipment_bits;
        state[0xC8/4] = 0;
        if (flags & 0x8000) {
            state[0x1E0/4] = 0;
            state[0x230/4] = 1;
            state[0xF0/4] = 0;
            state[0x248/4] = 1;
            state[0x1F8/4] = 1;
        } else if (flags & 0x4000) {
            state[0x1E0/4] = 1;
            state[0x1F8/4] = 1;
            state[0xF0/4] = 0;
            state[0x248/4] = 0;
            state[0x230/4] = 0;
        } else {
            state[0xF0/4] = 1;
            state[0x230/4] = 0;
            state[0x1E0/4] = 0;
            state[0x248/4] = 0;
            state[0x1F8/4] = 0;
        }
    }
    {
        int *state = g_spawn_entry_table;
        int flags;
        state[0x108/4] = 1;
        flags = g_equipment_bits;
        if (flags & 0x10) {
            state[0x118/4] = 0;
            state[0x220/4] = 1;
            state[0x208/4] = 1;
        } else {
            state[0x118/4] = 1;
            state[0x208/4] = 0;
        }
    }
    g_spawn_entry_table[0x130/4] = 1;
}

/* func_L05_00379B60 is defined in L05_00379B60-g8.c. */

extern char *moby_get_motion_data(int, int);

/* Finds an object's state and stores a value in it. */
void level_set_object_state_field(int objectId, int value) {
    char *state = moby_get_motion_data(objectId, value);
    if (state != 0)
        *(int *)(state + 0x150) = value;
}

extern int g_level_object_list[];

/* Returns the live object list. */
int *level_get_object_list(void) {
    return g_level_object_list;
}

/* func_L05_00379ED0 is defined in L05_003008C0-g8.c (this unit has no $gp access for it). */

extern int g_feltzin_challenge_state[];

/* Stores a value in the shared player state. */
void hero_set_state_value_a(int value) {
    g_feltzin_challenge_state[13] = value;
}

/* Stores a value in the shared player state. */
void hero_set_state_value_b(int value) {
    g_feltzin_challenge_state[15] = value;
}

/* Returns a value from the shared player state. */
int hero_get_state_value_b(void) {
    return g_feltzin_challenge_state[15];
}

/* Stores a value in the shared player state. */
void hero_set_state_value_c(int value) {
    g_feltzin_challenge_state[18] = value;
}

/* Returns a value from the shared player state. */
int hero_get_state_value_c(void) {
    return g_feltzin_challenge_state[18];
}

/* Clears a field in each of 128 records of the shared state. */
void level_clear_object_records(void) {
    char *base = (char *)g_feltzin_challenge_state + 0xC0;
    int *entry = (int *)(base + 0x3FD0);
    int i = 0x7F;
    do {
        *entry = 0;
        entry -= 0x20;
        i--;
    } while (i >= 0);
}

/* func_L05_00379FA0 is defined in L05_00379FA0-qcopy.c. */

/* func_L05_0037A218 is defined in L05_0037A218-g8.c. */


typedef struct L05Slot40 {
    int state;      /* 0x00 */
    int next;       /* 0x04, the index the chain moves to */
    int pad08[2];
    int limit;      /* 0x10 */
    int value;      /* 0x14 */
    int pad18[4];
} L05Slot40;

extern L05Slot40 g_slot_value_table[];

extern int func_L05_0037AAC8(int index);


/* Takes a step off the stored value, never below zero. */
void slot_subtract_value_clamped(int index, int step)
{
    int slot = slot_find_active_in_chain(index);

    if (slot < 0)
        slot = func_L05_0037AAC8(index);
    g_slot_value_table[slot].value -= step;
    if (g_slot_value_table[slot].value <= 0)
        g_slot_value_table[slot].value = 0;
}

/* Adds a step to the stored value, never above the stored limit. */
void slot_add_value_clamped(int index, int step)
{
    int slot = slot_find_active_in_chain(index);

    if (slot < 0)
        slot = func_L05_0037AAC8(index);
    g_slot_value_table[slot].value += step;
    if (g_slot_value_table[slot].limit < g_slot_value_table[slot].value)
        g_slot_value_table[slot].value = g_slot_value_table[slot].limit;
}

/* func_L05_0037AC00 is matched in its own unit, src/levels/shared/L05_0037AC00.c (default flags). */

/* func_L05_0037AC40 is matched in its own unit, src/levels/shared/L05_0037AC40.c (default flags). */

/* func_L05_0037AC80 lives in L05_0037AC80.c:
   its state and damage flow are kept in a separate unit. */

/* Add an argument to the stored value and clamp it into [8, 15]. */
/* Adds to the stored value and keeps it between 8 and 15. */
void hero_add_clamped_stat(float amount)
{
    float *values = (float *)g_feltzin_challenge_state;
    float total = values[12] + amount;
    float limit = 15.0f;

    values[12] = total;
    if (total > limit) {
        values[12] = limit;
    } else {
        limit = 8.0f;
        if (total < limit)
            values[12] = limit;
    }
}

/* Returns the stored value that is kept between 8 and 15. */
float hero_get_clamped_stat(void) {
    return ((float *)g_feltzin_challenge_state)[12];
}


extern char *func_L05_00379CA0(char *);

extern void func_L05_0037B838(char *);

/* Hand the object over, then clear its action state and step the shared counter. */
void moby_reset_action_state(char *moby)
{
    char *state = func_L05_00379CA0(moby);

    if (state == 0)
        return;
    func_L05_0037B838(moby);
    *(unsigned short *)(moby + 0x32) = 0;
    *(unsigned short *)(moby + 0x34) = *(unsigned short *)(moby + 0x34) | 3;
    *(unsigned char *)(moby + 0x30) = 0;
    *(int *)(moby + 0x98) = 0;
    *(int *)(state + 0x110) = 0;
    if (g_feltzin_challenge_state[4] != 0)
        g_feltzin_challenge_state[4] = g_feltzin_challenge_state[4] - 1;
}
