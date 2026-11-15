#include "include_asm.h"

#include "common.h"
extern u8 g_item_owned_flags[] __attribute__((sda));
extern u8 D_001395D7[];
extern u8 D_001395D8[];
typedef struct { char pad[0x5c]; int state; int flags; } DobboPlayerFlags;
extern DobboPlayerFlags D_00139768;
extern char g_hero_position[];
extern u8 D_0019B2E8[];
extern int D_00138324;
extern char D_L09_001B1458[], D_L09_001B1480[], D_L09_001B1498[], D_L09_001B14C0[], D_L09_001B14E8[], D_L09_001B14F8[], D_L09_001B1518[], D_L09_001B1540[];
extern char D_L09_001BFC00[], D_L09_0021DDE0[];
extern int g_player_bolts SDATA(D_001A79F8);
extern int g_current_map_index SDATA(D_001A79F0);
extern char *D_L09_001B294C SDATA(D_L09_001B294C);
extern int D_L09_001A8F00[] __attribute__((sda));
extern int D_L09_001B25A0[] __attribute__((sda));
extern int D_L09_0028E350[];
extern int D_L09_0028E360, D_L09_0028E364;
extern void STUB_printf(char *, ...);
extern void moby_set_state(char *, int, int);
extern void moby_reset_vars_defaults(char *);
extern int IsPointInCuboid(char *, int);
extern int req_push_queue(char *, int);
extern void level_apply_index_for_key(char *);
extern void req_launch_queued(char *);
extern int game_is_either_mode_two(void);
extern void hero_reset_position_and_direction(char *, char *, int, int);
extern int flag_is_third_pending_set(char *);
extern void game_set_slowdown_factor(void);
extern int hero_is_reachable_for_count(char *, int, float);
extern void text_print_localized_formatted(int, int, int);
extern void moby_mark_flag_and_append_to_list(int);
extern void func_US2_002AFF10(int);
extern void record_add_or_update_entry(char *, int, char *, int, char *);
extern void moby_mark_table_entry_flagged(int);
extern void level_capture_checkpoint_state(char *, char *);
extern void MemcardSave(int, int);

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
        if (D_00139768.flags & 1) {
            STUB_printf(D_L09_001B1458);
            startCurrency = g_player_bolts;
            if (g_item_owned_flags[0x197]) {
                if (startCurrency < D_L09_0028E364)
                    goto start_six;
                else
                    moby_set_state(obj, 7, 1);
            } else {
                if (startCurrency < D_L09_0028E360) {
                start_six:
                    moby_set_state(obj, 6, 1);
                } else
                    moby_set_state(obj, 7, 1);
            }
        } else if (D_00139768.state < 0) {
            STUB_printf(D_L09_001B1480);
            if (D_001395D7[0]) {
                obj[0x30] = 0xff;
                STUB_printf(D_L09_001B1498);
                moby_set_state(obj, 4, 1);
            } else {
                obj[0x30] = 0xff;
                STUB_printf(D_L09_001B14C0);
                moby_set_state(obj, 3, 0);
            }
        } else {
            STUB_printf(D_L09_001B14E8);
            moby_set_state(obj, 1, 0);
        }
        moby_reset_vars_defaults(obj);
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position, *(int *)p)) {
            STUB_printf(D_L09_001B14F8);
            if (req_push_queue(D_L09_001BFC00, 0x5f)) {
                level_apply_index_for_key(obj);
                req_launch_queued(D_L09_001BFC00);
                moby_set_state(obj, 2, -1);
            }
        }
        break;
    case 2:
        D_L09_001B25A0[2] = 1;
        if (D_L09_001A8F00[0] == 2) {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        }
        if (game_is_either_mode_two())
            break;
        D_L09_001B25A0[2] = 0;
        if (*(int *)(p + 8) != -1) {
            entry = D_L09_001B294C;
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
            D_001395D7[0] = 1;
            moby_set_state(obj, 4, 1);
        }
        break;
    case 4:
        obj[0x30] = 0xff;
        if (IsPointInCuboid(g_hero_position, *(int *)p)) {
            STUB_printf(D_L09_001B1518);
            if (req_push_queue(D_L09_001BFC00, 0x60)) {
                req_launch_queued(D_L09_001BFC00);
                game_set_slowdown_factor();
                moby_set_state(obj, 5, -1);
            }
        }
        break;
    case 5:
        obj[0x30] = 0x40;
        if (D_L09_001A8F00[0] == 2) {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        }
        D_L09_001B25A0[2] = 1;
        if (game_is_either_mode_two())
            break;
        D_L09_001B25A0[2] = 0;
        if (*(int *)(p + 8) != -1) {
            entry = D_L09_001B294C;
            entry += *(int *)(p + 8) << 7;
            hero_reset_position_and_direction(entry + 0x30, entry + 0x70, 0, 1);
        }
        obj[0x31] = 1;
        *(u16 *)(obj + 0x34) &= 0xfffe;
        D_001395D8[0] = 1;
        offerCurrency = g_player_bolts;
        if (g_item_owned_flags[0x197]) {
            if (offerCurrency < D_L09_0028E364)
                goto offer_six;
            else
                moby_set_state(obj, 7, -1);
        } else {
            if (offerCurrency < D_L09_0028E360) {
            offer_six:
                moby_set_state(obj, 6, -1);
            } else
                moby_set_state(obj, 7, -1);
        }
        break;
    case 6:
        currency = g_player_bolts;
        if (g_item_owned_flags[0x197]) {
            if (D_L09_0028E350[5] < currency)
                goto change_seven;
        } else {
            if (D_L09_0028E350[4] < currency) {
            change_seven:
                moby_set_state(obj, 7, -1);
                break;
            }
        }
        if (hero_is_reachable_for_count(obj, 10, 2.5f)) {
            text_print_localized_formatted(0x1323, g_item_owned_flags[0x197] ? D_L09_0028E350[5] : D_L09_0028E350[4], -1);
            level_apply_index_for_key(obj);
        }
        break;
    case 7:
        currency = g_player_bolts;
        if (g_item_owned_flags[0x197]) {
            if (currency < D_L09_0028E350[5])
                goto change_six;
        } else {
            if (currency < D_L09_0028E350[4]) {
            change_six:
                moby_set_state(obj, 6, -1);
                break;
            }
        }
        if (hero_is_reachable_for_count(obj, 10, 2.5f)) {
            text_print_localized_formatted(0x1324, g_item_owned_flags[0x197] ? D_L09_0028E350[5] : D_L09_0028E350[4], -1);
            level_apply_index_for_key(obj);
            if ((D_00138324 & 0x10) && req_push_queue(D_L09_001BFC00, 10)) {
                STUB_printf(D_L09_001B1540);
                balance = g_player_bolts;
                if (g_item_owned_flags[0x197])
                    remaining = balance - D_L09_0028E350[5];
                else
                    remaining = balance - D_L09_0028E350[4];
                g_player_bolts = remaining;
                req_push_queue(D_L09_001BFC00, 0x61);
                req_push_queue(D_L09_001BFC00, 0x62);
                req_launch_queued(D_L09_001BFC00);
                moby_set_state(obj, 8, -1);
            }
        }
        break;
    case 8:
        D_L09_001B25A0[2] = 1;
        if (D_L09_001A8F00[0] == 2) {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        }
        if (game_is_either_mode_two())
            break;
        D_L09_001B25A0[2] = 0;
        obj[0x31] = 1;
        *(u16 *)(obj + 0x34) &= 0xfffe;
        moby_mark_flag_and_append_to_list(10);
        func_US2_002AFF10(10);
        moby_set_state(obj, 9, -1);
        record_add_or_update_entry(obj + 0x20, 1, obj, 1, D_L09_0021DDE0);
        if (obj[0xb0] != 0xff) {
            if (!(D_0019B2E8[obj[0xb0] + (g_current_map_index << 4)] & 0x80))
                moby_mark_table_entry_flagged(obj[0xb0]);
            level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
        } else
            MemcardSave(0, -1);
        break;
    }
}
