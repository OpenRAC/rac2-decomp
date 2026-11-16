#include "names.h"

/* SPDX-License-Identifier: MIT
 * MIT License
 *
 * Copyright (c) 2026 RC2 decomp contributions
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "common.h"

extern void help_unlock_entry();
extern s32 level_validate_item_list();
extern void gfx_run_filter_over_all_slots(s32);
extern s32 moby_handle_request_slot_state();
extern volatile s32 g_menu_choice_table;
extern volatile s32 g_hero_aim_speed_start;
extern s32 g_current_map_index __attribute__((sda));
extern volatile u8 g_starting_items_granted;
extern volatile u8 g_start_grant_flag_a;
extern volatile u8 g_start_grant_flag_b;
extern volatile u8 g_start_grant_flag_c;
extern volatile s8 g_start_grant_value;
extern volatile s8 g_vendor_item_list;
extern volatile s8 g_start_grant_value_next;

/* Gives the starting items when the player does not have them yet, then checks the item list. */
void level_grant_starting_items(void) {
    if (g_start_grant_flag_a == 0) {
        help_unlock_entry(0x1E);
        moby_handle_request_slot_state(0x1E);
        g_vendor_item_list = 0x5E;
        g_menu_choice_table = 0x1E;
    }
    if (g_start_grant_flag_b == 0) {
        help_unlock_entry(0x2A);
        moby_handle_request_slot_state(0x2A);
        g_start_grant_value_next = 0x6A;
    }
    if (g_start_grant_flag_c == 0) {
        help_unlock_entry(0x2F);
        g_hero_aim_speed_start = 0x2F;
    }
    if (g_starting_items_granted == 0) {
        g_start_grant_value = 1;
        g_starting_items_granted = 1;
    }
    level_validate_item_list();
    gfx_run_filter_over_all_slots(g_current_map_index);
}
