#include "common.h"

/* func_US2_L11_00399764, the v2.00 copy of func_L11_003983F0: the same two triggers, but the first
   no longer tests D_L11_001AED04 and D_L11_001AED00. The hero's fields 0x2294 and 0x24CC clear or set
   D_US2_001A9050, and while D_US2_001A904C is set each call scans 40 objects from the table for live
   ones of class 0xCF5, 0xCF6 or 0xD07, firing the trigger when a full pass finds none. Built without
   -mno-split-addresses: the hero's address is split, the MACRO_ADDR globals keep their macro loads. */

extern void moby_set_state(u8 *a0, u8 a1, s32 a2);

extern int snd_play_from_global_bank(int a0, unsigned int a1, void *a2);

extern void value_set_entry_by_index(int a0, int a1);

typedef struct {
    char pad0[0x2294];
    int w2294;
    char pad2298[0x24CC - 0x2298];
    int w24CC;
} Hero_00399764;

extern Hero_00399764 g_hero_state;

extern u8 *g_moby_l11_table MACRO_ADDR;

extern u8 *g_moby_table_limit MACRO_ADDR;

extern s32 g_arena_progress_level MACRO_ADDR;

extern s32 g_active_rider_count __attribute__((sda));

extern s32 g_creature_burst_count __attribute__((sda));

extern s32 g_level_cutscene_gate_flag MACRO_ADDR;

extern s32 g_level_event_state MACRO_ADDR;

extern s32 g_level_progress_flag MACRO_ADDR;

extern u8 g_item_enabled_flags[] MACRO_ADDR;

void level_update_progress_flags_us2(u8 *moby) {
    u8 *moby_bytes = moby;
    int state = moby_bytes[0x20];
    int *vars = *(int **)(moby_bytes + 0x68);
    int i;

    if (state != 1) {
        if (state < 2) {
            if (state == 0) {
                moby_bytes[0x30] = 0xFF;
                g_creature_burst_count = 0;
                moby_set_state(moby_bytes, 1, -1);
            }
        }
        return;
    }
    if (g_hero_state.w2294 == 0x74 || g_hero_state.w24CC <= 0) {
        g_level_event_state = 0;
        g_active_rider_count = 0;
    }
    if (g_arena_progress_level >= 6 && g_hero_state.w2294 == 0 && g_hero_state.w24CC <= 0) {
        g_level_event_state = 1;
    }
    if (g_level_cutscene_gate_flag != 0 && g_item_enabled_flags[0x12] == 0) {
        int kind = MOBY_CLASS_JOBIAN_SAUR_BEAST;

        for (i = 0; i < 40; i++) {
            u8 *entry = g_moby_l11_table + (vars[1] << 8);
            u16 class_id = *(u16 *)(entry + 0xAA);
            u8 *item_flags = g_item_enabled_flags;

            if (class_id == MOBY_CLASS_JOBA_TRIBESMAN || class_id == 0xCF6 || (s16)class_id == kind) {
                if (((s8 *)entry)[0x20] >= 0) {
                    vars[0]++;
                }
            }
            vars[1]++;
            if (g_moby_l11_table + (vars[1] << 8) >= g_moby_table_limit) {
                if (vars[0] == 0 && item_flags[0x12] == 0) {
                    item_flags[0x12] = 1;
                    snd_play_from_global_bank(1, 0, 0);
                    value_set_entry_by_index(0x1233, -1);
                    g_level_progress_flag = 1;
                }
                vars[1] = 0;
                vars[0] = 0;
            }
        }
    }
    if (g_creature_burst_count < 12)
        return;
    if (g_item_enabled_flags[0x14] != 0)
        return;
    g_item_enabled_flags[0x14] = 1;
    snd_play_from_global_bank(1, 0, 0);
    value_set_entry_by_index(0x1233, -1);
    g_level_progress_flag = 1;
}
