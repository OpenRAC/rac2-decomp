#include "include_asm.h"

#include "common.h"
extern u8 g_item_owned_flags[] __attribute__((sda));
extern u8 g_dobbo_setting_flag_a[];
extern u8 g_dobbo_setting_flag_b[];
typedef struct { char pad[0x5c]; int state; int flags; } DobboPlayerFlags;
extern DobboPlayerFlags g_request_flag_table;
extern char g_hero_position[];
extern u8 g_moby_group_flags[];
extern int g_pad_held_flags;
extern char g_str_dobbo_setting_a[], g_str_dobbo_setting_b[], g_str_dobbo_setting_c[], g_str_dobbo_setting_d[], g_str_dobbo_setting_e[], g_str_dobbo_setting_f[], g_str_dobbo_setting_g[], g_str_dobbo_setting_h[];
extern char g_request_l09_queue[], g_dobbo_record_template[];
extern int g_player_bolts SDATA(D_001A79F8);
extern int g_current_map_index SDATA(D_001A79F0);
extern char *g_dobbo_point_table SDATA(D_L09_001B294C);
extern int g_game_l09_mode[] __attribute__((sda));
extern int g_dobbo_setting_flags[] __attribute__((sda));
extern int g_dobbo_prices[];
extern int g_dobbo_currency_limit_low, g_dobbo_currency_limit_high;
extern void STUB_printf(char *, ...);
extern void moby_set_state(char *, int, int);
extern void moby_reset_vars_defaults(char *);
extern int IsPointInCuboid(char *, int);
extern int req_push_queue(char *, int);
extern void level_apply_index_for_key(char *);
extern s32 req_launch_queued(char *);
extern int game_is_either_mode_two(void);
extern void hero_reset_position_and_direction(char *, char *, int, int);
extern int flag_is_third_pending_set(char *);
extern void game_set_slowdown_factor(void);
extern int hero_is_reachable_for_count(char *, int, float);
extern void text_print_localized_formatted(int, int, int);
extern void moby_mark_flag_and_append_to_list(int);
extern void snd_play_indexed_us2(int);
extern void record_add_or_update_entry(char *, int, char *, int, char *);
extern void moby_mark_table_entry_flagged(int);
extern void level_capture_checkpoint_state(char *, char *);
extern int MemcardSave(int, int);

void func_US2_L09_00409904(u8 *obj)
{
    char *p = *(char **)(obj + 0x68);
    char *entry;
    int startCurrency;
    int offerCurrency;
    int currency;
    int balance;
    int remaining;

    switch (obj[0x20]) {
    case 0:
        if (g_item_owned_flags[0xDA]) {
            moby_set_state(obj, 9, -1);
            break;
        }
        if (g_request_flag_table.flags & 1) {
            STUB_printf(g_str_dobbo_setting_a);
            startCurrency = g_player_bolts;
            if (g_item_owned_flags[0x197]) {
                if (startCurrency < g_dobbo_currency_limit_high)
                    goto start_six;
                else
                    moby_set_state(obj, 7, 1);
            } else {
                if (startCurrency < g_dobbo_currency_limit_low) {
                start_six:
                    moby_set_state(obj, 6, 1);
                } else
                    moby_set_state(obj, 7, 1);
            }
        } else if (g_request_flag_table.state < 0) {
            STUB_printf(g_str_dobbo_setting_b);
            if (g_dobbo_setting_flag_a[0]) {
                obj[0x30] = 0xff;
                STUB_printf(g_str_dobbo_setting_c);
                moby_set_state(obj, 4, 1);
            } else {
                obj[0x30] = 0xff;
                STUB_printf(g_str_dobbo_setting_d);
                moby_set_state(obj, 3, 0);
            }
        } else {
            STUB_printf(g_str_dobbo_setting_e);
            moby_set_state(obj, 1, 0);
        }
        moby_reset_vars_defaults(obj);
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position, *(int *)p)) {
            STUB_printf(g_str_dobbo_setting_f);
            if (req_push_queue(g_request_l09_queue, 0x5f)) {
                level_apply_index_for_key(obj);
                req_launch_queued(g_request_l09_queue);
                moby_set_state(obj, 2, -1);
            }
        }
        break;
    case 2:
        g_dobbo_setting_flags[2] = 1;
        if (g_game_l09_mode[0] == 2) {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        }
        if (game_is_either_mode_two())
            break;
        g_dobbo_setting_flags[2] = 0;
        if (*(int *)(p + 8) != -1) {
            entry = g_dobbo_point_table;
            entry += *(int *)(p + 8) << 7;
            hero_reset_position_and_direction(entry + 0x30, entry + 0x70, 0, 1);
        }
        obj[0x31] = 1;
        *(u16 *)(obj + 0x34) &= 0xfffe;
        moby_set_state(obj, 3, -1);
        break;
    case 3:
        obj[0x30] = 0xff;
        if (flag_is_third_pending_set(obj)) {
            g_dobbo_setting_flag_a[0] = 1;
            moby_set_state(obj, 4, 1);
        }
        break;
    case 4:
        obj[0x30] = 0xff;
        if (IsPointInCuboid(g_hero_position, *(int *)p)) {
            STUB_printf(g_str_dobbo_setting_g);
            if (req_push_queue(g_request_l09_queue, 0x60)) {
                req_launch_queued(g_request_l09_queue);
                game_set_slowdown_factor();
                moby_set_state(obj, 5, -1);
            }
        }
        break;
    case 5:
        obj[0x30] = 0x40;
        if (g_game_l09_mode[0] == 2) {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        }
        g_dobbo_setting_flags[2] = 1;
        if (game_is_either_mode_two())
            break;
        g_dobbo_setting_flags[2] = 0;
        if (*(int *)(p + 8) != -1) {
            entry = g_dobbo_point_table;
            entry += *(int *)(p + 8) << 7;
            hero_reset_position_and_direction(entry + 0x30, entry + 0x70, 0, 1);
        }
        obj[0x31] = 1;
        *(u16 *)(obj + 0x34) &= 0xfffe;
        g_dobbo_setting_flag_b[0] = 1;
        offerCurrency = g_player_bolts;
        if (g_item_owned_flags[0x197]) {
            if (offerCurrency < g_dobbo_currency_limit_high)
                goto offer_six;
            else
                moby_set_state(obj, 7, -1);
        } else {
            if (offerCurrency < g_dobbo_currency_limit_low) {
            offer_six:
                moby_set_state(obj, 6, -1);
            } else
                moby_set_state(obj, 7, -1);
        }
        break;
    case 6:
        currency = g_player_bolts;
        if (g_item_owned_flags[0x197]) {
            if (g_dobbo_prices[5] < currency)
                goto change_seven;
        } else {
            if (g_dobbo_prices[4] < currency) {
            change_seven:
                moby_set_state(obj, 7, -1);
                break;
            }
        }
        if (hero_is_reachable_for_count(obj, 10, 2.5f)) {
            text_print_localized_formatted(0x1323, g_item_owned_flags[0x197] ? g_dobbo_prices[5] : g_dobbo_prices[4], -1);
            level_apply_index_for_key(obj);
        }
        break;
    case 7:
        currency = g_player_bolts;
        if (g_item_owned_flags[0x197]) {
            if (currency < g_dobbo_prices[5])
                goto change_six;
        } else {
            if (currency < g_dobbo_prices[4]) {
            change_six:
                moby_set_state(obj, 6, -1);
                break;
            }
        }
        if (hero_is_reachable_for_count(obj, 10, 2.5f)) {
            text_print_localized_formatted(0x1324, g_item_owned_flags[0x197] ? g_dobbo_prices[5] : g_dobbo_prices[4], -1);
            level_apply_index_for_key(obj);
            if ((g_pad_held_flags & 0x10) && req_push_queue(g_request_l09_queue, 10)) {
                STUB_printf(g_str_dobbo_setting_h);
                balance = g_player_bolts;
                if (g_item_owned_flags[0x197])
                    remaining = balance - g_dobbo_prices[5];
                else
                    remaining = balance - g_dobbo_prices[4];
                g_player_bolts = remaining;
                req_push_queue(g_request_l09_queue, 0x61);
                req_push_queue(g_request_l09_queue, 0x62);
                req_launch_queued(g_request_l09_queue);
                moby_set_state(obj, 8, -1);
            }
        }
        break;
    case 8:
        g_dobbo_setting_flags[2] = 1;
        if (g_game_l09_mode[0] == 2) {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        }
        if (game_is_either_mode_two())
            break;
        g_dobbo_setting_flags[2] = 0;
        obj[0x31] = 1;
        *(u16 *)(obj + 0x34) &= 0xfffe;
        moby_mark_flag_and_append_to_list(10);
        snd_play_indexed_us2(10);
        moby_set_state(obj, 9, -1);
        record_add_or_update_entry(obj + 0x20, 1, obj, 1, g_dobbo_record_template);
        if (obj[0xb0] != 0xff) {
            if (!(g_moby_group_flags[obj[0xb0] + (g_current_map_index << 4)] & 0x80))
                moby_mark_table_entry_flagged(obj[0xb0]);
            level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
        } else
            MemcardSave(0, -1);
        break;
    }
}
