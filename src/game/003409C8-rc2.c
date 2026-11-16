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

extern s32 snd_play_from_global_bank(s32 a, s32 b, s32 c);
extern void AddMenuItemToRing(void *o, void *p, s32 n);
extern s16 g_menu_item_table_first[][5];

struct Obj {
    s8 pad[0x814];
    s32 column;  /* 0x814 */
    s32 page;  /* 0x818 */
    s32 flag;  /* 0x81C */
    s32 value;  /* 0x820 */
};

/* Moves the selection around the four-column item grid and remembers the selected value. */
void radial_menu_move_grid_selection(struct Obj *o, s32 flags) {
    if (flags & 0x1000) {
        s32 minus_one;
        s32 new_page;
        s32 next_value;
        snd_play_from_global_bank(3, 0, 0);
        minus_one = -1;
        next_value = o->page - 1;
        new_page = (minus_one < next_value) ? next_value : 5;
        o->page = new_page;
    } else if (flags & 0x4000) {
        s32 next_value;
        snd_play_from_global_bank(3, 0, 0);
        next_value = o->page + 1;
        next_value = (5 < next_value) ? 0 : next_value;
        o->page = next_value;
    } else if (flags & 0x8000) {
        s32 next_value;
        s32 saved_page;
        s32 page_offset;
        snd_play_from_global_bank(3, 0, 0);
        next_value = o->column - 1;
        o->column = next_value;
        if (next_value < 0) {
            saved_page = o->page;
            o->column = 3;
            page_offset = saved_page - 4;
            if ((u32)page_offset < 2) {
                o->column = 2;
                o->page = page_offset;
                o->flag = 1;
            }
        }
    } else if (flags & 0x2000) {
        s32 next_value;
        s32 current_page;
        snd_play_from_global_bank(3, 0, 0);
        next_value = o->column + 1;
        o->column = next_value;
        if (next_value >= 4) {
            o->column = 0;
            current_page = o->page;
            if (current_page == 4) {
                o->page = 0;
                o->flag = 1;
            } else if (current_page == 5) {
                o->column = 1;
                o->page = 1;
                o->flag = 1;
            }
        }
    } else if (flags & 0x40) {
        AddMenuItemToRing(o, g_menu_item_table_first, 4);
    }
    o->value = g_menu_item_table_first[o->column + o->page * 4][3];
}
