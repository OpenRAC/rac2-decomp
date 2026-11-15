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

extern s8 *D_001F2854;
extern s8 D_00262BE0[];
extern void SetupGifPaging(s32);
extern void DoGifPaging(void);
extern int text_draw_centered_small(s32, s32, u64, s32, s32);
extern char *GetLocalizedString(s32);

/* Shows a message in the middle of the screen. With no item chosen it shows one line, otherwise two lines for the chosen item. */
s32 menu_entry_message_draw(s8 *menu) {
    s8 *screen;
    s32 entry_index;

    screen = (*(s8 **)((s8 *)(D_001F2854) + (0xE8)));
    entry_index = (*(s32 *)((s8 *)((*(s8 **)((s8 *)(screen) + (0x34))) + (*(s32 *)((s8 *)(screen) + (0x40))) * 12) + (4)));
    SetupGifPaging(0);
    if (entry_index == -1) {
        text_draw_centered_small((*(s32 *)((s8 *)(menu) + (0x20))) / 2, (*(s32 *)((s8 *)(menu) + (0x24))) / 2 - 8, 0x80FFA888ULL, GetLocalizedString(0x2E65), -1);
    } else {
        s32 entry_offset = entry_index * 12;
        text_draw_centered_small((*(s32 *)((s8 *)(menu) + (0x20))) / 2, (*(s32 *)((s8 *)(menu) + (0x24))) / 3 - 8, 0x80FFA888ULL, GetLocalizedString((*(s32 *)((s8 *)(D_00262BE0 + entry_offset) + (0)))), -1);
        text_draw_centered_small((*(s32 *)((s8 *)(menu) + (0x20))) / 2, (*(s32 *)((s8 *)(menu) + (0x24))) * 2 / 3 - 8, 0x80FFA888ULL, GetLocalizedString((*(s32 *)((s8 *)(D_00262BE0 + entry_offset) + (4)))), -1);
    }
    DoGifPaging();
    return 2;
}
