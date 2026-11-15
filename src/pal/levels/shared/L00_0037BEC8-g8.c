#include "names.h"

/* SPDX-License-Identifier: MIT
 * MIT License
 * 
 * Copyright (c) 2026 Forja contributors
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
/* func_PAL_L00_0037BEC8, the PAL copy of func_002FAE68: the same C, where each string pointer passed to
 * func_002F88D8 becomes a func_00288FB8(id) lookup (ids 0x1B72, 0x1B70, 0x1B71, 0x1B6F). The level twin
 * of func_PAL_002FBEB4 in src/pal/game/002FBEB4-g8.c. */
#include "common.h"

/* The resident table already holds the retail label addresses. The unused
 * label list keeps each C branch available; it is not read by the program. */
extern void *D_0026DBE0[];

extern s8 *GetLocalizedString(s32 id);
extern void shop_set_message_text(s8 *a);
extern void shop_mark_bought_special_items_owned(void);

struct A { s8 pad[0x38]; s32 st; };
struct B {
    s8 p0[0x8]; s32 f8;
    s8 p1[0x8]; s32 f14;
    s8 p2[0x4]; s32 f1C;
    s8 p3[0x88]; s32 fA8;
    s8 p4[0x8]; s32 fB4;
    s8 p5[0x4]; s32 fBC;
    s8 p6[0x9C]; s32 f15C;
    s8 p7[0x4]; s32 f164;
    s32 f168;
};

extern struct A g_vendor_menu_state;
extern struct B g_memcard_state;
extern s32 D_001A7A20;

void func_PAL_L00_0037BEC8(void) {
    {
    static void *rc2_labels[] = {&&rc2_case_0, &&rc2_case_1, &&rc2_case_2, &&rc2_case_3, &&rc2_case_4, &&rc2_case_5, &&rc2_case_6};
    u32 rc2_selector = (u32)(g_vendor_menu_state.st);
    if (rc2_selector > 6U) goto rc2_default;
goto *D_0026DBE0[rc2_selector];

    rc2_case_0:
    rc2_case_2:
        if (g_memcard_state.f15C < 3 && g_memcard_state.f164 < 0 && g_memcard_state.f8 == 2) {
            if (g_memcard_state.f14 != 0) {
                g_memcard_state.f164 = 0x18;
                g_vendor_menu_state.st = 3;
                g_memcard_state.f168 = 0;
                goto rc2_switch_end;
            }
        }
        if (g_vendor_menu_state.st != 0) {
            g_vendor_menu_state.st = 4;
        } else {
            g_vendor_menu_state.st = 6;
        }
        goto rc2_switch_end;
    rc2_case_1:
    rc2_case_3:
        if (g_memcard_state.f15C < 3 && g_memcard_state.f164 < 0) {
            if (D_001A7A20 & 0x80) {
                if (g_memcard_state.f1C == 1) {
                    shop_set_message_text(GetLocalizedString(0x1B72));
                } else if (g_memcard_state.f1C >= 3) {
                    shop_set_message_text(GetLocalizedString(0x1B70));
                } else {
                    shop_set_message_text(GetLocalizedString(0x1B71));
                }
            } else {
                shop_set_message_text(GetLocalizedString(0x1B6F));
            }
            shop_mark_bought_special_items_owned();
            if (g_vendor_menu_state.st != 0) {
                g_vendor_menu_state.st = 4;
            } else {
                g_vendor_menu_state.st = 6;
            }
        }
        goto rc2_switch_end;
    rc2_case_4:
        if (g_memcard_state.f15C < 3 && g_memcard_state.f164 < 0 && g_memcard_state.fA8 == 2 && g_memcard_state.fB4 != 0) {
            g_memcard_state.f164 = 0x18;
            g_memcard_state.f168 = 1;
            g_vendor_menu_state.st = 5;
            goto rc2_switch_end;
        }
        g_vendor_menu_state.st = 6;
        goto rc2_switch_end;
    rc2_case_5:
        if (g_memcard_state.f15C < 3 && g_memcard_state.f164 < 0) {
            if (D_001A7A20 & 0x80) {
                if (g_memcard_state.fBC == 1) {
                    shop_set_message_text(GetLocalizedString(0x1B72));
                } else if (g_memcard_state.fBC >= 3) {
                    shop_set_message_text(GetLocalizedString(0x1B70));
                } else {
                    shop_set_message_text(GetLocalizedString(0x1B71));
                }
            } else {
                shop_set_message_text(GetLocalizedString(0x1B6F));
            }
            shop_mark_bought_special_items_owned();
            g_vendor_menu_state.st = 6;
        }
        goto rc2_switch_end;
    rc2_case_6:
        if (g_memcard_state.f15C < 3 && g_memcard_state.f164 < 0) {
            if (g_memcard_state.f1C == 0) {
                s32 a = g_memcard_state.f8;
                if (a == 2 && g_memcard_state.f14 != 0) {
                    g_vendor_menu_state.st = a;
                    goto rc2_switch_end;
                }
            }
            if (g_memcard_state.fBC == 0 && g_memcard_state.fA8 == 2 && g_memcard_state.fB4 != 0) {
                g_vendor_menu_state.st = 4;
            }
        }
        goto rc2_switch_end;
    rc2_default:
        goto rc2_switch_end;
    
rc2_switch_end: ;
}
}
