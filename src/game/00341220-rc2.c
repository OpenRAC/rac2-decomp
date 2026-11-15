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

extern void func_00115484(s8 *, s32, s32);
extern s32 func_00288FB8(s32);
extern s32 *func_00335E20(s8 *);
extern void func_00335F88(s8 *, f32, f32, f32, f32);
extern void func_003361E0(s8 *, s8 *, s8 *);
extern void func_00336390(s8 *, s32, s32);
extern void func_003363C0(s8 *, f32);
extern void func_00336710(s8 *, s8 *, s8 *);
extern void func_00336920(s8 *, s32, s32);
extern void func_003369A8(s8 *, s8 *, s8 *);
extern void func_00336A38(s8 *, s32);
extern s8 *func_00336DA8(s32, s32);
extern s32 func_00336E40(s8 *);
extern void func_00347EC8(s8 *, s8 *);
extern s32 D_001A8CFC;
extern s8 D_001ADC10[];
extern s8 D_001ADC18[];
extern s8 D_001ADC20[];
extern s8 D_001ADC28[];
extern s8 D_001ADC30[];
extern s8 D_001ADFC0[];
extern s8 D_001AE0C0[];

/* Sets up the parts of a tabbed menu: panels, frame, cursor, label and icon. */
void func_00341220(s8 *self, s8 *parent) {
    s8 *allocation;
    s8 *cursor;
    s8 *panelOne;
    s8 *panelTwo;
    s8 *frame;
    s8 *icon;
    s8 *label;

    (*(s8 **)((s8 *)(self) + (0x21C))) = parent;
    if (parent != 0) {
        allocation = ReturnSecondArgument(0x10, AllocPoolCell(parent));
        (*(s8 **)((s8 *)(self) + (0x218))) = allocation;
        (*(s32 *)((s8 *)(allocation) + (4))) = 0;
        (*(s32 *)((s8 *)(allocation) + (8))) = 0;
        (*(s32 *)((s8 *)(allocation) + (0xC))) = 0;
        (*(s32 *)((s8 *)(allocation) + (0))) = 0;
    }
    (*(s32 *)((s8 *)(self) + (0x220))) = 1;
    (*(f32 *)((s8 *)((*(s8 **)((s8 *)(self) + (0x218)))) + (0))) = 251.0f;
    cursor = self + 0x98;
    panelOne = self + 0x4C;
    panelTwo = self + 0xE4;
    (*(f32 *)((s8 *)((*(s8 **)((s8 *)(self) + (0x218)))) + (4))) = 170.0f;
    frame = self + 0x130;
    InitDerivedArrays(self, D_001ADC10, parent);
    icon = self + 0x17C;
    label = self + 0x1D0;
    InitDerivedArrays(cursor, D_001ADC18, parent);
    InitDerivedArrays(panelOne, D_001ADC20, parent);
    InitDerivedArrays(panelTwo, D_001ADC28, parent);
    InitDerivedArrays(frame, D_001ADFC0, parent);
    InitWidgetDefaults(label, D_001ADC30, parent);
    InitDerivedObjectC(icon, D_001AE0C0, parent);
    InitListMenu_00347EC8(self + 0x228, parent);
    *GetFieldC(self) = 0x60442D00;
    *GetFieldC(cursor) = 0x80FFDE8D;
    *GetFieldC(panelOne) = 0x55F0C070;
    *GetFieldC(panelTwo) = 0x55F0C070;
    *GetFieldC(frame) = 0x70FFFEED;
    *GetFieldC(label) = 0x80F0F0F0;
    *GetFieldC(icon) = 0x60F0F0B0;
    SetFloatAt38(self, 1.0f);
    SetFloatAt38(panelOne, 1.0f);
    SetFloatAt38(panelTwo, 1.0f);
    SetFieldAt40(self, D_001A8CFC + 0x8710, 0x91);
    SetFieldAt40(cursor, D_001A8CFC + 0x8710, 0x94);
    SetFieldAt40(panelOne, D_001A8CFC + 0x8710, 0x92);
    SetFieldAt40(panelTwo, D_001A8CFC + 0x8710, 0x93);
    SetFieldAt40(frame, D_001A8CFC + 0x8710, 0x95);
    SetSecondFloat4(frame, 1.0f, 1.05f, 0.0f, 0.0f);
    SetWidgetField40(label, GetLocalizedString(0x2D55));
    SetWidgetValuePair(icon, 0xEA9D, 0);
    memset(self + 0x1B8, 0, 12);
    SetSecondFloat4(icon, 32.0f, 32.0f, 0.0f, 0.0f);
}
