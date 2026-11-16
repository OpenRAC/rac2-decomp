#include "include_asm.h"
#include "names.h"

extern int ref_L01_00320AE8_00 __attribute__((sda));

/* Store the observed raw 32-bit input in the GP-relative cell.
   The original owner and semantic value remain unknown. */
extern unsigned int g_pad_raw_input_value;

extern int ref_L04_0034E130_00 __attribute__((sda));

extern int ref_L01_00320B20_00;

/* Tells whether the counter is above zero. */
int level_is_counter_positive(void)
{
    return ref_L01_00320AE8_00 > 0;
}

/* Stores a raw input value. */
void pad_set_raw_input_value(unsigned int value)
{
    g_pad_raw_input_value = value;
}

/* Counts a timer down by one and keeps it from going below zero. */
void level_decrement_counter_clamped(void)
{
    int value = (int)((unsigned int)ref_L04_0034E130_00 - 1u);
    ref_L04_0034E130_00 = value;
    if (value < 0)
        ref_L04_0034E130_00 = 0;
}

/* Stores a value in a global setting. */
void level_set_global_setting_value(int value)
{
    ref_L01_00320B20_00 = value;
}

extern int g_game_l00_mode;
extern int g_input_reset_value;
extern int g_input_lock_state;
extern int g_pad_reset_flag_a __attribute__((sda));
extern int g_pad_reset_flag_b __attribute__((sda));

/* records the raw input in the absolute state block, parks a -2 marker beside it
   and clears the two small-data cells that follow.  The two identical stores are
   written in the order this cc1 emits them (it swaps them otherwise). */
/* Resets the input state with a new value. */
void pad_reset_input_state(int value)
{
    g_game_l00_mode = value;
    g_input_lock_state = -2;
    g_input_reset_value = value;
    g_pad_reset_flag_a = 0;
    g_pad_reset_flag_b = 0;
}



/* The record at 0x88 of the second argument decides: arm it with the four
   sub-addresses and light bit 0x40 on the record's 0x94 word when it takes. */
extern int ref_L00_00320DE0_00();

/* Starts the attachment on the object when it has one, and marks it as started. */
void moby_start_attachment(char *object, char *owner)
{
    char *record = owner;

    if (*(int *)(record + 0x88) != 0) {
        if (ref_L00_00320DE0_00(object, *(int *)(record + 0x88), object + 0x10, object + 0xF0,
                                object + 0x10, object + 0xF0) != 0)
            *(int *)(record + 0x94) = *(int *)(record + 0x94) | 0x40;
    }
}
