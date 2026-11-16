#include "include_asm.h"

#include "common.h"
extern int g_oozla_intro_timer __attribute__((sda));
extern int g_oozla_intro_stage MACRO_ADDR;
extern unsigned char g_oozla_intro_done __attribute__((nosda));
extern int g_flying_path_mode MACRO_ADDR;
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern void value_set_entry_by_index_pal(int, int);

/* Once the level's mode word reaches 6 and the timer at D_L01_001AEC38 has run out, raises the
   one-shot flag and starts the sequence (mode 2 first rearms the timer to 0x42). A fresh
   object (state 0) clears its byte at +0x30. */
void oozla_intro_sequence_trigger_pal(char *arg0) {
    if (*(unsigned char *)(arg0 + 0x20) == 0)
        *(unsigned char *)(arg0 + 0x30) = 0xFF;
    if (g_oozla_intro_stage == 2)
        g_oozla_intro_timer = 0x42;
    if (g_oozla_intro_stage < 6)
        return;
    if (g_oozla_intro_timer > 0)
        return;
    if (g_oozla_intro_done != 0)
        return;
    g_oozla_intro_done = 1;
    snd_play_from_global_bank(1, 0, 0);
    value_set_entry_by_index_pal(0x1233, -1);
    g_flying_path_mode = 1;
}
