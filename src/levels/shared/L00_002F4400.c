#include "include_asm.h"
#include "names.h"

typedef struct {
    int f0;
    char pad_04[0x34];
    short f38;
    char pad_3A[2];
    int f3C;
} Entry_r002F46C8;

extern Entry_r002F46C8 g_tutorial_prompt_state[];

extern char g_subtitle_history[];

extern short g_level_second_table[];

extern void func_2F4490(int, int);

extern int r1_func_0011CC38();

/* Does nothing. */
void level_no_op_hook(void)
{
}


/* Clears the top bit in the same field of each of 161 entries in a table. */
void level_clear_entry_top_bits(void) {
    char *base = g_subtitle_history;
    int *field = (int *)(base + 8);
    unsigned int mask = 0x7FFFFFFF;
    int i = 0xA0;

    for (; i >= 0; i--) {
        *field &= mask;
        field += 3;
    }
}


/* Sets the first entry of a level table to zero. */
void level_clear_second_table_entry(void) {
    g_level_second_table[0] = 0;
}

/* Does nothing. */
void level_no_op_hook_b(void)
{
}

/* Only the second mode triggers the spawn. */
void level_spawn_on_second_mode(int mode) {
    if (mode == 2)
        func_2F4490(0xA01, 0x58);
}

/* func_L00_002F59A8 is matched in its own unit, src/levels/shared/L00_002F59A8.c (default flags). */


/* func_L00_002F6B90 is matched in L00_002F6B90.c. */


typedef struct { unsigned int fields[25]; int key; unsigned int busy; int tail[9]; } UpdateRecord_2F7298;
extern UpdateRecord_2F7298 g_update_record_table[13];

/* The func_0028B6C8 table search: raises a free record's peak to VALUE; 1 when the key is
   missing or the record busy. */
int level_raise_record_peak(int key, int value)
{
    int i;
    for (i = 0; i < 13; i++) {
        if (g_update_record_table[i].key == key) break;
    }
    if (i < 13) {
        if (g_update_record_table[i].busy == 0) {
            UpdateRecord_2F7298 *r = &g_update_record_table[i];
            int peak = r->tail[4];
            if (value >= peak)
                peak = value;
            r->tail[4] = peak;
            return 0;
        }
    }
    return 1;
}


/* rac1-decomp src/core/00119D88.c: func_0011CCB0 */
/* Returns its callee's value: retail keeps the frame and calls, and
   2.9-ee would tail-call it (a bare `j`) if it were void. */
int level_call_helper_a(void) {
    return r1_func_0011CC38();
}

/* Always answers zero. */
int level_return_zero_a(void) {
    return 0;
}

/* Always answers zero. */
int level_return_zero_b(void) {
    return 0;
}
