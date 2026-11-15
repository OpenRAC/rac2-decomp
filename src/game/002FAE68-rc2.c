
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
#include "common.h"

/* The resident table already holds the retail label addresses. The unused
 * label list keeps each C branch available; it is not read by the program. */
extern void *D_0026DBE0[];

extern void func_002F88D8(s8 *a);
extern s8 D_001AD468[];
extern s8 D_001AD498[];
extern s8 D_001AD4C0[];
extern s8 D_001AD4E8[];
extern void func_002FADB0(void);

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

extern struct A D_0021F240;
extern struct B D_001393E0;
extern s32 D_001A7A20;

/* Steps through the shop's buy and message states: shows the right line of text for the item
   and moves on to the next step. */
void func_002FAE68(void) {
    {
    static void *volatile rc2_labels[] = {&&rc2_case_0, &&rc2_case_1, &&rc2_case_2, &&rc2_case_3, &&rc2_case_4, &&rc2_case_5, &&rc2_case_6};
    u32 rc2_selector = (u32)(gVendorMenuState.st);
    if (rc2_selector > 6U) goto rc2_default;
goto *D_0026DBE0[rc2_selector];

    rc2_case_0:
    rc2_case_2:
        if (gMemcardState.f15C < 3 && gMemcardState.f164 < 0 && gMemcardState.f8 == 2) {
            if (gMemcardState.f14 != 0) {
                gMemcardState.f164 = 0x18;
                gVendorMenuState.st = 3;
                gMemcardState.f168 = 0;
                goto rc2_switch_end;
            }
        }
        if (gVendorMenuState.st != 0) {
            gVendorMenuState.st = 4;
        } else {
            gVendorMenuState.st = 6;
        }
        goto rc2_switch_end;
    rc2_case_1:
    rc2_case_3:
        if (gMemcardState.f15C < 3 && gMemcardState.f164 < 0) {
            if (D_001A7A20 & 0x80) {
                if (gMemcardState.f1C == 1) {
                    SetShopMessageText(D_001AD468);
                } else if (gMemcardState.f1C >= 3) {
                    SetShopMessageText(D_001AD498);
                } else {
                    SetShopMessageText(D_001AD4C0);
                }
            } else {
                SetShopMessageText(D_001AD4E8);
            }
            MarkBoughtSpecialItemsOwned();
            if (gVendorMenuState.st != 0) {
                gVendorMenuState.st = 4;
            } else {
                gVendorMenuState.st = 6;
            }
        }
        goto rc2_switch_end;
    rc2_case_4:
        if (gMemcardState.f15C < 3 && gMemcardState.f164 < 0 && gMemcardState.fA8 == 2 && gMemcardState.fB4 != 0) {
            gMemcardState.f164 = 0x18;
            gMemcardState.f168 = 1;
            gVendorMenuState.st = 5;
            goto rc2_switch_end;
        }
        gVendorMenuState.st = 6;
        goto rc2_switch_end;
    rc2_case_5:
        if (gMemcardState.f15C < 3 && gMemcardState.f164 < 0) {
            if (D_001A7A20 & 0x80) {
                if (gMemcardState.fBC == 1) {
                    SetShopMessageText(D_001AD468);
                } else if (gMemcardState.fBC >= 3) {
                    SetShopMessageText(D_001AD498);
                } else {
                    SetShopMessageText(D_001AD4C0);
                }
            } else {
                SetShopMessageText(D_001AD4E8);
            }
            MarkBoughtSpecialItemsOwned();
            gVendorMenuState.st = 6;
        }
        goto rc2_switch_end;
    rc2_case_6:
        if (gMemcardState.f15C < 3 && gMemcardState.f164 < 0) {
            if (gMemcardState.f1C == 0) {
                s32 mode = gMemcardState.f8;
                if (mode == 2 && gMemcardState.f14 != 0) {
                    gVendorMenuState.st = mode;
                    goto rc2_switch_end;
                }
            }
            if (gMemcardState.fBC == 0 && gMemcardState.fA8 == 2 && gMemcardState.fB4 != 0) {
                gVendorMenuState.st = 4;
            }
        }
        goto rc2_switch_end;
    rc2_default:
        goto rc2_switch_end;
    
rc2_switch_end: ;
}
}
