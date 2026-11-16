#include "include_asm.h"
#include "names.h"

typedef struct {
    char b[8];
} CdClock;
extern int sceCdReadClock(CdClock *);
extern void clock_to_local_time(unsigned char *);
extern void save_build_packet(int);
extern unsigned char g_cd_clock_buffer[8] __attribute__((sda));
extern unsigned char g_memcard_state[];
extern void save_load_game_data_reset_menu(int, int);

/* Clears the chosen slot, then starts saving the game into it. */
void save_clear_slot_and_start_pal(int value, int mode)
{
    unsigned char *state;
    save_load_game_data_reset_menu(value, mode);
    sceCdReadClock((CdClock *)g_cd_clock_buffer);
    clock_to_local_time(g_cd_clock_buffer);
    save_build_packet(value);
    state = g_memcard_state;
    *(int *)(state + 0x148) = 0;
    *(short *)(state + 0x18) = mode;
    *(int *)(state + mode * 0x1C + 0x30) = 0;
    *(int *)(state + 0x174) = value;
    if (*(int *)(state + 0x164) < 0) {
        *(int *)(state + 0x168) = 0;
        *(int *)(state + 0x164) = 0x13;
    }
}


#include "common.h"
typedef struct {
    short f0;
    short f2;
    char pad4[8];
} Slot;
extern Slot g_unlock_entry_slots[];
extern int g_unlock_text_ids[4] MACRO_ADDR;
extern int g_menu_object_flag MACRO_ADDR;
extern int save_count_nonzero_flags(void);
extern int save_count_entries_above_threshold(void);

/* Unlock levels for the counts the player has collected. */
void menu_update_unlock_entries_pal(void)
{
    int unlock_15 = save_count_nonzero_flags() >= 15;
    int unlock_30 = save_count_nonzero_flags() >= 30;
    int unlock_10 = save_count_entries_above_threshold() >= 10;
    g_unlock_entry_slots[5].f2 = unlock_15 ? 3 : 2;
    g_unlock_entry_slots[6].f2 = unlock_30 ? 3 : 2;
    g_unlock_entry_slots[7].f2 = unlock_10 ? 10 : 2;
    g_unlock_entry_slots[8].f2 = unlock_10 ? 3 : 2;
    g_unlock_text_ids[0] = unlock_15 ? 0xC2F : 0xC35;
    g_unlock_text_ids[1] = unlock_30 ? 0xC30 : 0xC36;
    g_unlock_text_ids[2] = unlock_10 ? 0xC33 : 0xC37;
    g_unlock_text_ids[3] = unlock_10 ? 0xC34 : 0xC37;
    if (g_menu_object_flag) g_unlock_entry_slots[8].f0 = 0;
}

