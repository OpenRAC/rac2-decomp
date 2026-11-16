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

extern s16 g_menu_item_table_first[];
extern s16 g_menu_item_table_second[];

/* Returns 1 when the help id appears in either of the two help id tables, otherwise 0. */
s32 help_is_id_in_either_table(s32 help_id) {
    s16 *table_a;
    s16 *table_b;
    s16 *id_ptr;

    table_a = g_menu_item_table_first;
    if (table_a[3] != -1) {
        id_ptr = table_a + 3;
        do {
            if (help_id == *id_ptr) {
                return 1;
            }
            id_ptr += 5;
        } while (*id_ptr != -1);
    }
    table_b = g_menu_item_table_second;
    if (table_b[3] != -1) {
        id_ptr = table_b + 3;
        do {
            if (help_id == *id_ptr) {
                return 1;
            }
            id_ptr += 5;
        } while (*id_ptr != -1);
    }
    return 0;
}
