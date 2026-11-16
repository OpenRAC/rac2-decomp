#include "common.h"

extern int g_hud_timer_table_base[] __attribute__((sda));
extern int g_feltzin_intro_done __attribute__((sda));
extern int g_feltzin_menu_opened __attribute__((sda));
extern int g_feltzin_needs_reset __attribute__((sda));
extern int g_feltzin_selected_entry __attribute__((sda));
extern int g_feltzin_challenge_data __attribute__((sda));
extern int D_L05_001B1350_4[] MACRO_ADDR;
/* The pad state; through a pointer view, so each use forms the base from the shared high half. */
typedef struct { char pad_000[0x1A0]; union { unsigned long long held; unsigned int word[2]; } pad; } PadView;
extern char g_pad_state[];
#define PAD ((PadView *)D_00138180)
extern void ref_L05_0041ED18_00(void);
extern void level_store_value_pair(int, void *);
extern int snd_play_from_global_bank(int, int, int);
extern int request_begin_slot(int, int, int, int, int);

/* A four-entry menu: up and down move the cursor (wrapping); accepting an entry needs the flags of
   every entry before it and returns its index, otherwise -2. The words after the first flag are
   read at an offset from the block's absolute name, so they never fill a delay slot; each test
   stands as `if (!flag) break;`, so the tail test of the three cases cross-jumps into one. */
/* Runs a four-entry menu: up and down move the cursor, and accepting returns the chosen entry (only if the earlier ones are unlocked), or -2 if nothing was chosen. */
int LockedEntryMenuInput(void)
{
    unsigned int buttons;

    if (g_hud_timer_table_base[0] && !g_feltzin_menu_opened) {
        level_store_value_pair(0, ref_L05_0041ED18_00);
        g_feltzin_intro_done = 0;
        g_feltzin_menu_opened = 1;
    }
    buttons = PAD->pad.word[1];
    if (buttons & 0x8000) {
        snd_play_from_global_bank(3, 0, 0);
        if (--g_feltzin_selected_entry < 0)
            g_feltzin_selected_entry = 3;
    } else if (buttons & 0x2000) {
        snd_play_from_global_bank(3, 0, 0);
        if (++g_feltzin_selected_entry > 3)
            g_feltzin_selected_entry = 0;
    }
    if (PAD->pad.word[1] & 0x10)
        request_begin_slot(3, 1, 4, 0, 0);
    if (PAD->pad.word[1] & 0x40) {
        switch (g_feltzin_selected_entry) {
        case 1:
            if (!g_feltzin_challenge_data)
                break;
            goto accept;
        case 2:
            if (!g_feltzin_challenge_data)
                break;
            if (!D_L05_001B1350_4[1])
                break;
            goto accept;
        case 3:
            if (!g_feltzin_challenge_data)
                break;
            if (!D_L05_001B1350_4[1])
                break;
            if (!D_L05_001B1350_4[2])
                break;
        case 0:
        accept:
            g_feltzin_needs_reset = 0;
            snd_play_from_global_bank(4, 0, 0);
            return g_feltzin_selected_entry;
        }
        snd_play_from_global_bank(5, 0, 0);
        g_feltzin_needs_reset = 1;
    }
    if (PAD->pad.held & 0xA000000000ULL)
        snd_play_from_global_bank(5, 0, 0);
    return -2;
}
