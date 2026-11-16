#include "include_asm.h"
#include "names.h"
/* func_US2_L19_0042C4E0, the USA v2.00 copy of func_L19_0042B058: the same C, plus
 * `self[0x30] = 0xFF;` in case 0 and a call to func_US2_L19_0042BBF8 after the switch. Each
 * purchase now takes the price when its movie ends (states 3 and 6) instead of at the sale, and
 * the text ids moved from 0x27DC-0x27E2 to 0x132E-0x1334. */
#include "common.h"

/* One entity of the group: the kind word is at 0xAA. */
typedef struct L19Thing {
    u8 pad[0xAA];
    s16 kind;
} L19Thing;

extern s32 g_hero_l19_mode[] __attribute__((sda));
extern u8 g_unlocked_item_flags[] MACRO_ADDR;

extern int text_sum_subtitle_lengths(void);
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

extern void moby_glow_all_same_class(L19Thing *a0);
extern int func_US2_L19_0042BBF8(void);

#define H(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define I(p, o) (*(int *)((u8 *)(p) + (o)))

/* An interaction state machine at byte 0x20, a larger cousin of func_L08_00435A78: offers two
   purchases for the quantity at D_001A79F8[9] (states 1-2 and 4-5, each followed by a movie in
   state 3 or 6), then buys the remaining quantity back at 30000 or 3000 each (states 7-8). */
void func_US2_L19_0042C4E0(u8 *self)
{
    u8 *data = *(u8 **)(self + 0x68);
    u8 *companion;
    int remaining;

    moby_glow_all_same_class((L19Thing *)self);
    if (g_frame_l19_counter[0] == 5)
        text_sum_subtitle_lengths();
    switch (self[0x20]) {
    case 0:
        self[0x30] = 0xFF;
        if (game_is_either_mode_two())
            break;
        if (g_glow_class_flags & 0x4000000) {
            H(self, 0x34) = (H(self, 0x34) & 0xFFBE) | 0x1000;
            I(self, 0x98) = I(*(u8 **)(self + 0x24), 0x10);
            if (g_game_flag_table[0x89]) {
                text_sum_subtitle_lengths();
                if (g_player_bolts[9] < 1)
                    moby_set_state(self, 7, -1);
                else
                    moby_set_state(self, 8, -1);
            } else if (g_player_bolts[9] < (g_price_flags[0xF] ? g_item_l19_price_table[17] : g_item_l19_price_table[16]))
                moby_set_state(self, 4, -1);
            else
                moby_set_state(self, 5, -1);
            moby_reset_vars_defaults(self);
        } else if (g_glow_class_flags & 0x1000000) {
            text_sum_subtitle_lengths();
            H(self, 0x34) = (H(self, 0x34) & 0xFFBE) | 0x1000;
            I(self, 0x98) = I(*(u8 **)(self + 0x24), 0x10);
            if (g_player_bolts[9] < (g_price_flags[0xF] ? g_item_l19_price_table[15] : g_item_l19_price_table[14]))
                moby_set_state(self, 1, -1);
            else
                moby_set_state(self, 2, -1);
        } else {
            I(self, 0x98) = 0;
            H(self, 0x34) = (H(self, 0x34) | 0x41) & 0xEFFF;
        }
        break;
    case 1:
        if (g_player_bolts[9] >= (g_price_flags[0xF] ? g_item_l19_price_table[15] : g_item_l19_price_table[14]))
            moby_set_state(self, 2, -1);
        else if (hero_is_reachable_for_count(self, 10, 2.5f)) {
            text_print_localized_formatted(0x132E, (g_price_flags[0xF] ? g_item_l19_price_table[15] : g_item_l19_price_table[14]), -1);
            level_apply_index_for_key(self);
        }
        break;
    case 2:
        if (g_player_bolts[9] < (g_price_flags[0xF] ? g_item_l19_price_table[15] : g_item_l19_price_table[14]))
            moby_set_state(self, 1, -1);
        else if (hero_is_reachable_for_count(self, 10, 2.5f)) {
            text_print_localized_formatted(0x132F, (g_price_flags[0xF] ? g_item_l19_price_table[15] : g_item_l19_price_table[14]), -1);
            level_apply_index_for_key(self);
            if (g_pad_held_flags & 0x10) {
                req_push_queue(g_request_l19_queue, 0x9A);
                req_launch_queued(g_request_l19_queue);
                moby_set_state(self, 3, -1);
            }
        }
        break;
    case 3:
        g_glow_state_flags[1] = 1;
        if (g_hero_l19_mode[0] == 2) {
            self[0x31] = 0;
            H(self, 0x34) |= 1;
        }
        if (I(data, 0x80) != -1 && g_hero_l19_mode[0] == 2) {
            companion = g_moby_l19_array;
            H(companion + I(data, 0x80) * 0x100, 0x34) |= 1;
            (companion + I(data, 0x80) * 0x100)[0x31] = 0;
        }
        if (!game_is_either_mode_two()) {
            g_glow_state_flags[1] = 0;
            self[0x31] = 1;
            H(self, 0x34) &= 0xFFFE;
            g_player_bolts[9] -= (g_price_flags[0xF] ? g_item_l19_price_table[15] : g_item_l19_price_table[14]);
            if (self[0x21] != 0xFF)
                moby_set_byte_on_group(self[0x21], 1);
            if (I(data, 0x80) != -1) {
                moby_mark_spawned(g_moby_l19_array + I(data, 0x80) * 0x100);
                I(data, 0x80) = -1;
            }
            MemcardSave(0, -1);
            if ((u32)g_player_bolts[9] <= (g_price_flags[0xF] ? g_item_l19_price_table[17] : g_item_l19_price_table[16]))
                moby_set_state(self, 4, -1);
            else
                moby_set_state(self, 5, -1);
        }
        break;
    case 4:
        if (g_player_bolts[9] >= (g_price_flags[0xF] ? g_item_l19_price_table[17] : g_item_l19_price_table[16]))
            moby_set_state(self, 5, -1);
        else if (hero_is_reachable_for_count(self, 10, 2.5f)) {
            text_print_localized_formatted(0x1330, (g_price_flags[0xF] ? g_item_l19_price_table[17] : g_item_l19_price_table[16]), -1);
            level_apply_index_for_key(self);
        }
        break;
    case 5:
        if (g_player_bolts[9] < (g_price_flags[0xF] ? g_item_l19_price_table[17] : g_item_l19_price_table[16]))
            moby_set_state(self, 4, -1);
        else if (hero_is_reachable_for_count(self, 10, 2.5f)) {
            text_print_localized_formatted(0x1331, (g_price_flags[0xF] ? g_item_l19_price_table[17] : g_item_l19_price_table[16]), -1);
            level_apply_index_for_key(self);
            if (g_pad_held_flags & 0x10) {
                req_push_queue(g_request_l19_queue, 0x99);
                req_launch_queued(g_request_l19_queue);
                moby_set_state(self, 6, -1);
            }
        }
        break;
    case 6:
        g_glow_state_flags[1] = 1;
        if (g_hero_l19_mode[0] == 2) {
            self[0x31] = 0;
            H(self, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            g_player_bolts[9] -= (g_price_flags[0xF] ? g_item_l19_price_table[17] : g_item_l19_price_table[16]);
            g_glow_state_flags[1] = 0;
            self[0x31] = 1;
            H(self, 0x34) &= 0xFFFE;
            if (self[0x21] != 0xFF)
                moby_set_byte_on_group(self[0x21], 1);
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
                moby_set_state(self, 7, -1);
            else
                moby_set_state(self, 8, -1);
        }
        break;
    case 7:
        if (g_player_bolts[9] > 0)
            moby_set_state(self, 8, -1);
        else if (hero_is_reachable_for_count(self, 10, 2.5f)) {
            if (!g_subtitle_total_length[0])
                text_print_localized_formatted(0x1334, 0, -1);
            else
                text_print_localized_formatted(0x1332, -1);
            level_apply_index_for_key(self);
        }
        break;
    case 8:
        if (g_player_bolts[9] < 1)
            moby_set_state(self, 7, -1);
        else if (hero_is_reachable_for_count(self, 10, 2.5f)) {
            if (flag_is_byte_set()) {
                text_print_localized_formatted(0x1333, g_player_bolts[9], g_player_bolts[9] * 30000, -1);
                level_apply_index_for_key(self);
                if (g_pad_held_flags & 0x10) {
                    text_sum_subtitle_lengths();
                    g_player_bolts[0] += g_player_bolts[9] * 30000;
                    g_player_bolts[9] = 0;
                    func_L00_0030C710(180);
                    snd_play_from_class_bank(0, 0, (char *)self, math_random_int_range(13, 17));
                    moby_set_state(self, 9, -1);
                }
            } else {
                text_print_localized_formatted(0x1333, g_player_bolts[9], g_player_bolts[9] * 3000, -1);
                level_apply_index_for_key(self);
                if (g_pad_held_flags & 0x10) {
                    text_sum_subtitle_lengths();
                    g_player_bolts[0] += g_player_bolts[9] * 3000;
                    g_player_bolts[9] = 0;
                    func_L00_0030C710(180);
                    moby_set_state(self, 9, -1);
                }
            }
        }
        break;
    case 9:
        H(self, 0x96)++;
        if (H(self, 0x96) > 0x7FF8)
            H(self, 0x96) = 0x7FF8;
        if (H(self, 0x96) > 40 && H(self, 0x96) < 90 && H(self, 0x96) % 4 == 0)
            snd_play_from_class_bank(0, 0, (char *)self, math_random_int_range(13, 17));
        if (hero_is_reachable_for_count(self, 10, 2.5f))
            text_print_localized_formatted(0x1334, g_subtitle_total_length[0], -1);
        else
            moby_set_state(self, 7, -1);
        break;
    }
    func_US2_L19_0042BBF8();
    if (g_unlocked_item_flags[0])
        *(float *)(data + 0x70) = 2.75f;
    moby_update_eased_node(self, data, 0, 0.02f, 0.3f);
}
