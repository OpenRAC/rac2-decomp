#include "common.h"

/* func_PAL_L19_00430C78, the PAL copy of func_L19_0042B058: the same C, where the text ids move to 0x132E-0x1334,
   the timers scale to 50 Hz, the two final speeds scale by 1.44, and the price is taken after the movie (states 3
   and 6) instead of at the purchase (states 2 and 5). */
extern int g_hero_l19_mode[] __attribute__((sda));
extern u8 g_unlocked_item_flags[] __attribute__((sda));

extern int text_sum_subtitle_lengths(void);
extern void moby_glow_all_same_class(void *);
extern int game_is_either_mode_two(void);
extern void moby_set_state(void *, int, int);
extern void moby_reset_vars_defaults(void *);
extern int hero_is_reachable_for_count(void *, int, float);
extern void text_print_localized_formatted(int, ...);
extern void level_apply_index_for_key(void *);
extern int req_push_queue(void *, int);
extern int req_launch_queued(void *);
extern void moby_set_byte_on_group(int, int);
extern void moby_mark_spawned(void *);
extern int MemcardSave(int, int);
extern void value_set_entry_by_index(int, int);
extern int subtitle_request_voice_line(int, int);
extern int flag_is_byte_set(void);
extern void func_L00_0030C710(int);
extern int math_random_int_range(int, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void moby_update_eased_node(void *, void *, void *, float, float);

extern int g_frame_l19_counter[] __attribute__((sda));
extern int g_glow_state_flags[] __attribute__((sda));
extern u8 *g_moby_l19_array __attribute__((sda));
extern int g_subtitle_total_length[] __attribute__((sda));
extern int g_player_bolts[] __attribute__((sda));
extern u8 g_price_flags[] __attribute__((sda));
extern u8 g_game_flag_table[];
extern u32 g_glow_class_flags, g_pad_held_flags;
extern int g_item_l19_price_table[];
extern u8 g_request_l19_queue[];

#define H(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define I(p, o) (*(int *)((u8 *)(p) + (o)))
/* The two prices in the level's table, each with a second value used when the flag is set. */

/* Runs a trader's talk. It offers two purchases, plays a short movie after each, then buys the player's leftover items for bolts. (PAL: 50 Hz timings, price taken after the movie) */
void UpdateTwoItemTraderNpc_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *linked_moby;
    int remaining;

    moby_glow_all_same_class(moby);
    if (g_frame_l19_counter[0] == 5)
        text_sum_subtitle_lengths();
    switch (moby[0x20]) {
    case 0:
        if (game_is_either_mode_two())
            break;
        if (g_glow_class_flags & 0x4000000) {
            H(moby, 0x34) = (H(moby, 0x34) & 0xFFBE) | 0x1000;
            I(moby, 0x98) = I(*(u8 **)(moby + 0x24), 0x10);
            if (g_game_flag_table[0x89]) {
                text_sum_subtitle_lengths();
                if (g_player_bolts[9] < 1)
                    moby_set_state(moby, 7, -1);
                else
                    moby_set_state(moby, 8, -1);
            } else if (g_player_bolts[9] < (g_price_flags[0xF] ? g_item_l19_price_table[17] : g_item_l19_price_table[16]))
                moby_set_state(moby, 4, -1);
            else
                moby_set_state(moby, 5, -1);
            moby_reset_vars_defaults(moby);
        } else if (g_glow_class_flags & 0x1000000) {
            text_sum_subtitle_lengths();
            H(moby, 0x34) = (H(moby, 0x34) & 0xFFBE) | 0x1000;
            I(moby, 0x98) = I(*(u8 **)(moby + 0x24), 0x10);
            if (g_player_bolts[9] < (g_price_flags[0xF] ? g_item_l19_price_table[15] : g_item_l19_price_table[14]))
                moby_set_state(moby, 1, -1);
            else
                moby_set_state(moby, 2, -1);
        } else {
            I(moby, 0x98) = 0;
            H(moby, 0x34) = (H(moby, 0x34) | 0x41) & 0xEFFF;
        }
        break;
    case 1:
        if (g_player_bolts[9] >= (g_price_flags[0xF] ? g_item_l19_price_table[15] : g_item_l19_price_table[14]))
            moby_set_state(moby, 2, -1);
        else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            text_print_localized_formatted(0x132E, (g_price_flags[0xF] ? g_item_l19_price_table[15] : g_item_l19_price_table[14]), -1);
            level_apply_index_for_key(moby);
        }
        break;
    case 2:
        if (g_player_bolts[9] < (g_price_flags[0xF] ? g_item_l19_price_table[15] : g_item_l19_price_table[14]))
            moby_set_state(moby, 1, -1);
        else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            text_print_localized_formatted(0x132F, (g_price_flags[0xF] ? g_item_l19_price_table[15] : g_item_l19_price_table[14]), -1);
            level_apply_index_for_key(moby);
            if (g_pad_held_flags & 0x10) {
                req_push_queue(g_request_l19_queue, 0x9A);
                req_launch_queued(g_request_l19_queue);
                moby_set_state(moby, 3, -1);
            }
        }
        break;
    case 3:
        g_glow_state_flags[1] = 1;
        if (g_hero_l19_mode[0] == 2) {
            moby[0x31] = 0;
            H(moby, 0x34) |= 1;
        }
        if (I(vars, 0x80) != -1 && g_hero_l19_mode[0] == 2) {
            linked_moby = g_moby_l19_array;
            H(linked_moby + I(vars, 0x80) * 0x100, 0x34) |= 1;
            (linked_moby + I(vars, 0x80) * 0x100)[0x31] = 0;
        }
        if (!game_is_either_mode_two()) {
            g_glow_state_flags[1] = 0;
            moby[0x31] = 1;
            H(moby, 0x34) &= 0xFFFE;
            g_player_bolts[9] -= (g_price_flags[0xF] ? g_item_l19_price_table[15] : g_item_l19_price_table[14]);
            if (moby[0x21] != 0xFF)
                moby_set_byte_on_group(moby[0x21], 1);
            if (I(vars, 0x80) != -1) {
                moby_mark_spawned(g_moby_l19_array + I(vars, 0x80) * 0x100);
                I(vars, 0x80) = -1;
            }
            MemcardSave(0, -1);
            if ((u32)g_player_bolts[9] <= (g_price_flags[0xF] ? g_item_l19_price_table[17] : g_item_l19_price_table[16]))
                moby_set_state(moby, 4, -1);
            else
                moby_set_state(moby, 5, -1);
        }
        break;
    case 4:
        if (g_player_bolts[9] >= (g_price_flags[0xF] ? g_item_l19_price_table[17] : g_item_l19_price_table[16]))
            moby_set_state(moby, 5, -1);
        else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            text_print_localized_formatted(0x1330, (g_price_flags[0xF] ? g_item_l19_price_table[17] : g_item_l19_price_table[16]), -1);
            level_apply_index_for_key(moby);
        }
        break;
    case 5:
        if (g_player_bolts[9] < (g_price_flags[0xF] ? g_item_l19_price_table[17] : g_item_l19_price_table[16]))
            moby_set_state(moby, 4, -1);
        else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            text_print_localized_formatted(0x1331, (g_price_flags[0xF] ? g_item_l19_price_table[17] : g_item_l19_price_table[16]), -1);
            level_apply_index_for_key(moby);
            if (g_pad_held_flags & 0x10) {
                req_push_queue(g_request_l19_queue, 0x99);
                req_launch_queued(g_request_l19_queue);
                moby_set_state(moby, 6, -1);
            }
        }
        break;
    case 6:
        g_glow_state_flags[1] = 1;
        if (g_hero_l19_mode[0] == 2) {
            moby[0x31] = 0;
            H(moby, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            g_player_bolts[9] -= (g_price_flags[0xF] ? g_item_l19_price_table[17] : g_item_l19_price_table[16]);
            g_glow_state_flags[1] = 0;
            moby[0x31] = 1;
            H(moby, 0x34) &= 0xFFFE;
            if (moby[0x21] != 0xFF)
                moby_set_byte_on_group(moby[0x21], 1);
            g_game_flag_table[0x89] = 1;
            value_set_entry_by_index(0x1294, -1);
            remaining = 2;
            if (g_game_flag_table[0x84])
                remaining--;
            if (g_game_flag_table[0x86])
                remaining--;
            if (remaining > 0)
                subtitle_request_voice_line(0xA0F, 0x66);
            else
                subtitle_request_voice_line(0xA10, 0x67);
            MemcardSave(0, -1);
            if (g_player_bolts[9] < 1)
                moby_set_state(moby, 7, -1);
            else
                moby_set_state(moby, 8, -1);
        }
        break;
    case 7:
        if (g_player_bolts[9] > 0)
            moby_set_state(moby, 8, -1);
        else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            if (!g_subtitle_total_length[0])
                text_print_localized_formatted(0x1334, 0, -1);
            else
                text_print_localized_formatted(0x1332, -1);
            level_apply_index_for_key(moby);
        }
        break;
    case 8:
        if (g_player_bolts[9] < 1)
            moby_set_state(moby, 7, -1);
        else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            if (flag_is_byte_set()) {
                text_print_localized_formatted(0x1333, g_player_bolts[9], g_player_bolts[9] * 30000, -1);
                level_apply_index_for_key(moby);
                if (g_pad_held_flags & 0x10) {
                    text_sum_subtitle_lengths();
                    g_player_bolts[0] += g_player_bolts[9] * 30000;
                    g_player_bolts[9] = 0;
                    func_L00_0030C710(((s32)(180) * 5 + 2) / 6);
                    snd_play_from_class_bank(0, 0, (char *)moby, math_random_int_range(13, 17));
                    moby_set_state(moby, 9, -1);
                }
            } else {
                text_print_localized_formatted(0x1333, g_player_bolts[9], g_player_bolts[9] * 3000, -1);
                level_apply_index_for_key(moby);
                if (g_pad_held_flags & 0x10) {
                    text_sum_subtitle_lengths();
                    g_player_bolts[0] += g_player_bolts[9] * 3000;
                    g_player_bolts[9] = 0;
                    func_L00_0030C710(((s32)(180) * 5 + 2) / 6);
                    moby_set_state(moby, 9, -1);
                }
            }
        }
        break;
    case 9:
        H(moby, 0x96)++;
        if (H(moby, 0x96) > 0x7FF8)
            H(moby, 0x96) = 0x7FF8;
        if (H(moby, 0x96) > ((s32)(40) * 5 + 2) / 6 && H(moby, 0x96) < ((s32)(90) * 5 + 2) / 6 && H(moby, 0x96) % (((s32)(4) * 5 + 2) / 6) == 0)
            snd_play_from_class_bank(0, 0, (char *)moby, math_random_int_range(13, 17));
        if (hero_is_reachable_for_count(moby, 10, 2.5f))
            text_print_localized_formatted(0x1334, g_subtitle_total_length[0], -1);
        else
            moby_set_state(moby, 7, -1);
        break;
    }
    if (g_unlocked_item_flags[0])
        *(float *)(vars + 0x70) = 2.75f;
    moby_update_eased_node(moby, vars, 0, 0.028800001f, 0.43200004f);
}
