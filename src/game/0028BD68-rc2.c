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

extern s32 g_weapon_menu_slots[];
extern s32 *g_radial_menu_pages;

/* Copies the eight weapon slot ids from the menu entries back into the weapon list. */
void weapon_menu_sync_slots(void) {
    s32 i;
    s32 *slot;
    s32 offset;
    s32 newValue;
    s32 oldValue;

    offset = 0;
    slot = g_weapon_menu_slots;
    for (i = 0; i < 8; i++) {
        newValue = *(s32 *)((s8 *)(offset + *g_radial_menu_pages) + 0x18);
        oldValue = *slot;
        if (oldValue != newValue) {
            *slot = newValue;
        }
        offset += 0x1C;
        slot += 1;
    }
}
