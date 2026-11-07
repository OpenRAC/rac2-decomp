
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

extern s8 *func_00288FB8(s32 id);
extern void func_002F88D8(s8 *a);
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

void func_PAL_L00_0037BEC8(void) {
    {
    static void *rc2_labels[] = {&&rc2_case_0, &&rc2_case_1, &&rc2_case_2, &&rc2_case_3, &&rc2_case_4, &&rc2_case_5, &&rc2_case_6};
    u32 rc2_selector = (u32)(D_0021F240.st);
    if (rc2_selector > 6U) goto rc2_default;
goto *D_0026DBE0[rc2_selector];

    rc2_case_0:
    rc2_case_2:
        if (D_001393E0.f15C < 3 && D_001393E0.f164 < 0 && D_001393E0.f8 == 2) {
            if (D_001393E0.f14 != 0) {
                D_001393E0.f164 = 0x18;
                D_0021F240.st = 3;
                D_001393E0.f168 = 0;
                goto rc2_switch_end;
            }
        }
        if (D_0021F240.st != 0) {
            D_0021F240.st = 4;
        } else {
            D_0021F240.st = 6;
        }
        goto rc2_switch_end;
    rc2_case_1:
    rc2_case_3:
        if (D_001393E0.f15C < 3 && D_001393E0.f164 < 0) {
            if (D_001A7A20 & 0x80) {
                if (D_001393E0.f1C == 1) {
                    func_002F88D8(func_00288FB8(0x1B72));
                } else if (D_001393E0.f1C >= 3) {
                    func_002F88D8(func_00288FB8(0x1B70));
                } else {
                    func_002F88D8(func_00288FB8(0x1B71));
                }
            } else {
                func_002F88D8(func_00288FB8(0x1B6F));
            }
            func_002FADB0();
            if (D_0021F240.st != 0) {
                D_0021F240.st = 4;
            } else {
                D_0021F240.st = 6;
            }
        }
        goto rc2_switch_end;
    rc2_case_4:
        if (D_001393E0.f15C < 3 && D_001393E0.f164 < 0 && D_001393E0.fA8 == 2 && D_001393E0.fB4 != 0) {
            D_001393E0.f164 = 0x18;
            D_001393E0.f168 = 1;
            D_0021F240.st = 5;
            goto rc2_switch_end;
        }
        D_0021F240.st = 6;
        goto rc2_switch_end;
    rc2_case_5:
        if (D_001393E0.f15C < 3 && D_001393E0.f164 < 0) {
            if (D_001A7A20 & 0x80) {
                if (D_001393E0.fBC == 1) {
                    func_002F88D8(func_00288FB8(0x1B72));
                } else if (D_001393E0.fBC >= 3) {
                    func_002F88D8(func_00288FB8(0x1B70));
                } else {
                    func_002F88D8(func_00288FB8(0x1B71));
                }
            } else {
                func_002F88D8(func_00288FB8(0x1B6F));
            }
            func_002FADB0();
            D_0021F240.st = 6;
        }
        goto rc2_switch_end;
    rc2_case_6:
        if (D_001393E0.f15C < 3 && D_001393E0.f164 < 0) {
            if (D_001393E0.f1C == 0) {
                s32 a = D_001393E0.f8;
                if (a == 2 && D_001393E0.f14 != 0) {
                    D_0021F240.st = a;
                    goto rc2_switch_end;
                }
            }
            if (D_001393E0.fBC == 0 && D_001393E0.fA8 == 2 && D_001393E0.fB4 != 0) {
                D_0021F240.st = 4;
            }
        }
        goto rc2_switch_end;
    rc2_default:
        goto rc2_switch_end;
    
rc2_switch_end: ;
}
}
