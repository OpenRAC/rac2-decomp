#include "names.h"
/* func_PAL_L00_002D6408: the PAL copy of func_L00_002D5EB8 (src/levels/shared/L00_002D3798-g8.c).
 * The same C with the 50 Hz duration 0x12C (300 frames) where v1.01 passes 0x168 (360), and
 * the callees that are the release's own functions:
 * func_00288508 is func_PAL_00288E20,
 * func_L00_0030C7F8 is func_PAL_L00_0030E648,
 * func_002B0A18 is func_PAL_002B1588.
 */
#include "common.h"

/* The hero block: the two fields the loop tests. */
typedef struct {
    char pad0000[0x340];
    int f340;                   /* 0x0340 */
    char pad0344[0xF04];
    int weapon;                 /* 0x1248 */
} Hero5940;

extern Hero5940 g_hero_state;
extern int g_frame_l00_counter[] __attribute__((sda));
extern int g_collection_progress_table[];
extern unsigned char g_player_stats[] __attribute__((sda));
extern int g_request_enabled_flag[];
extern unsigned char g_collection_progress_flags[] MACRO_ADDR;
extern unsigned char g_item_slot_to_record[];
extern int g_collection_progress_flag;
extern unsigned short g_subtitle_history __attribute__((section(".data")));
extern int g_help_entry_state[];
extern int g_menu_choice_table[] MACRO_ADDR;
extern unsigned char g_item_owned_flags[] MACRO_ADDR;

/* One 0xE0-byte entry of D_L00_00262570, indexed through D_00139568. */
typedef struct {
    int exists;                 /* 0x00 */
    unsigned char state;        /* 0x04 */
    char pad05[0x7];
    int index;                  /* 0x0C */
    char pad10[0x3A];
    short value;                /* 0x4A */
    char pad4C[0x20];
    int limit;                  /* 0x6C */
    char pad70[0x70];
} Entry1269;

extern Entry1269 g_weapon_l00_table[];
extern int math_sum_table_entries_under_limit(int *, int *, int *);
extern void hud_queue_hint_message(int, int);
extern void effect_controller_spawn(void);
extern void module_l00_call_handler_with_arg_4_pal(int);
extern void value_set_entry_by_index_pal(int, int);
extern int snd_play_from_global_bank(int, int, void *);
extern int flag_is_byte_set(void);
extern int menu_count_chain_entries_after_head(int);
extern void gfx_set_screen_pair_run_effect(int, int);
extern void menu_advance_chain_entry(int);
extern void help_show_message_for_id_pal(int);
extern int ref_PAL_L00_002D6408_00 __attribute__((sda));

static inline int special(int i)
{
    int r = 0;

    switch (i) {
    case 12:
    case 14:
    case 17:
    case 18:
    case 53:
        r = 1;
        break;
    }
    return r;
}

static inline int unlocked(Entry1269 *e, int i)
{
    if (e->state >= 2 || (e->state == 1 && special(i)))
        return 1;
    return 0;
}

static inline int owned(int i)
{
    if (g_weapon_l00_table[g_item_slot_to_record[i]].exists) {
        int n = menu_count_chain_entries_after_head(i);
        if (n >= 2 || (n == 1 && special(i)))
            return 1;
    }
    return 0;
}

void hero_update_collection_progress_pal(void)
{
    int count, i, j, ok;

    if ((g_frame_l00_counter[0] & 15) == 1 && g_frame_l00_counter[0] != 1)
        return;
    count = 4;
    {
        int *p = g_collection_progress_table;
        math_sum_table_entries_under_limit(p, p - 1, &count);
    }
    for (j = 0; j < 10; j++)
        if (g_collection_progress_flags[j])
            count++;
    if (*(int *)g_player_stats != count) {
        if (ref_PAL_L00_002D6408_00 >= 11 && *(int *)g_player_stats < count) {
            if (!g_subtitle_history)
                hud_queue_hint_message(0x9A9, 0);
            effect_controller_spawn();
            module_l00_call_handler_with_arg_4_pal(0x12C);
            value_set_entry_by_index_pal(0x1235, -1);
            snd_play_from_global_bank(6, 0, 0);
        }
        g_request_enabled_flag[0] = count;
        *(int *)g_player_stats = count;
    }

    for (i = 0; i < 56; i++) {
        if ((g_weapon_l00_table + g_item_slot_to_record[i])->state) {
            if (!flag_is_byte_set())
                continue;
            if (menu_count_chain_entries_after_head(i) == 1)
                continue;
        }
        {
            Entry1269 *e = &g_weapon_l00_table[g_item_slot_to_record[i]];
            int sel = 0;
            if (e->exists)
                sel = e->state == 3;
            if (sel)
                continue;
        }
        if (menu_count_chain_entries_after_head(i) <= 0)
            continue;
        {
            Entry1269 *e = &g_weapon_l00_table[g_item_slot_to_record[i]];
            if ((g_help_entry_state[i] >> 5) < e->limit || e->limit <= 0)
                continue;
            if (i == 31 || i == 9 || i == 45) {
                gfx_set_screen_pair_run_effect(i, g_weapon_l00_table[g_item_slot_to_record[i]].value);
                continue;
            }
            if (g_hero_state.weapon == i) {
                if (!g_hero_state.f340)
                    continue;
                if (g_menu_choice_table[e->index] != i)
                    continue;
                gfx_set_screen_pair_run_effect(i, e->value);
                continue;
            }
        }
        if (flag_is_byte_set()) {
            Entry1269 *e = &g_weapon_l00_table[g_item_slot_to_record[i]];
            if (!e->exists)
                continue;
            if (unlocked(e, i)) {
                if (owned(i)) {
                    menu_advance_chain_entry(i);
                    help_show_message_for_id_pal(i);
                }
            }
        } else {
            menu_advance_chain_entry(i);
            help_show_message_for_id_pal(i);
        }
    }

    if ((g_frame_l00_counter[0] & 127) || g_player_stats[0x7A])
        return;
    ok = 1;
    for (i = 0; i < 56; i++) {
        int ex = g_weapon_l00_table[g_item_slot_to_record[i]].exists;
        if (ex && i == 10)
            continue;
        if (ex && i == 9)
            continue;
        if (ex) {
            if (!g_item_owned_flags[i]) {
                ok = 0;
                break;
            }
            if (i == 14 || i == 12 || i == 17 || i == 18 || i == 53)
                continue;
            if (menu_count_chain_entries_after_head(i) <= 0)
                continue;
            if (!g_weapon_l00_table[g_item_slot_to_record[i]].state) {
                ok = 0;
                break;
            }
        }
    }
    if (ok && !g_player_stats[0x7A]) {
        g_player_stats[0x7A] = 1;
        snd_play_from_global_bank(1, 0, 0);
        value_set_entry_by_index_pal(0x1233, -1);
        g_collection_progress_flag = 1;
    }
}
