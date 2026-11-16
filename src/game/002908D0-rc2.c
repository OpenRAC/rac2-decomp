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

extern s32 help_is_id_in_mapping_table(s32 a0);
extern s8 g_vendor_item_list[];
extern s8 g_item_list_end[];

/* Walks the item list, clears every entry that is not allowed, and tells whether all were fine. */
s32 level_validate_item_list(void) {
    s32 entry;
    s32 list_end;
    s32 all_valid;
    u8 raw;
    s32 item_id;

    s32 skip_id = 0x1E;
    entry = (s32)g_vendor_item_list;
    list_end = (s32)g_item_list_end;
    all_valid = 1;
    do {
        raw = *(u8 *)entry;
        if (raw == 0xFF) {
            entry++;
            continue;
        }
        item_id = raw & 0x3F;
        if (item_id == skip_id) {
            entry++;
            continue;
        }
        if (help_is_id_in_mapping_table(item_id) == 0 || item_id == 0) {
            *(u8 *)entry = 0xFF;
            all_valid = 0;
        }
        entry++;
    } while (entry < list_end);
    return all_valid;
}
