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

extern s32 func_00288FB8();
extern s32 func_00335E20();
extern s32 func_00335F88(s32, f32, f32, f32, f32);
extern s32 func_003361E0();
extern s32 func_00336390();
extern s32 func_00336408();
extern s32 func_00336498();
extern s32 func_003364B0();
extern s32 func_00336710();
extern s32 func_003369A8();
extern s32 func_00336A30();
extern s32 func_00336A38();
extern s32 func_00336B90();
extern s32 func_00336B98();
extern s32 func_00336CC0();
extern s32 func_00336CC8();
extern s32 func_00336CE0();
extern s32 func_00336DA8();
extern s32 func_00336E40();
extern s32 func_00346C60();
extern s32 D_001A8CFC;
extern s8 D_001AE4D8[];
extern s8 D_001ADFC0[];
extern s8 D_001ADFA0[];
extern s8 D_001ADFD8[];
extern s8 D_001ADC18[];
extern s8 D_001ADC10[];
extern s8 D_001ADFC8[];
extern s8 D_001ADC28[];
extern s8 D_001ADFD0[];
extern s8 D_001AE4D0[];
extern s8 D_001AE040[];
extern s8 D_001ADC30[];
extern s8 D_001AE4E8[];
extern s8 D_001AE4F8[];

/* Sets up the item grid menu: creates all its texts, icons and bars, gives them colors and places them in the grid. */
void func_00346710(s32 menu, s32 context) {
    s32 widget4C;
    s32 widget130;
    s32 widget98;
    s32 widget400;
    s32 widget44C;
    s32 widgetE4;
    s32 widget17C;
    s32 iconWidget;
    s32 text210;
    s32 text258;
    s32 text2A0;
    s32 text2E8;
    s32 text330;
    s32 *colorSlot;
    s32 *colorSlot2;
    s32 barWidget;
    s32 backdropWidget;
    s32 positionData;

    (*(s32 *)((s8 *)(menu) + (0x49C))) = context;
    if (context != 0) {
        positionData = ReturnSecondArgument(0x10, AllocPoolCell(context));
        (*(s32 *)((s8 *)(menu) + (0x498))) = positionData;
        (*(s32 *)((s8 *)(positionData) + (4))) = 0;
        (*(s32 *)((s8 *)(positionData) + (8))) = 0;
        (*(s32 *)((s8 *)(positionData) + (0xC))) = 0;
        (*(s32 *)((s8 *)(positionData) + (0))) = 0;
    }
    (*(s32 *)((s8 *)(menu) + (0x4F8))) = 1;
    (*(f32 *)((s8 *)((*(s32 *)((s8 *)(menu) + (0x498)))) + (0))) = 250.0f;
    widget4C = menu + 0x4C;
    barWidget = menu + 0x1C8;
    widget130 = menu + 0x130;
    widget98 = menu + 0x98;
    (*(f32 *)((s8 *)((*(s32 *)((s8 *)(menu) + (0x498)))) + (4))) = 207.0f;
    widget400 = menu + 0x400;
    InitDerivedArrays(menu, D_001ADC10, context);
    widget44C = menu + 0x44C;
    InitDerivedArrays(widget4C, D_001ADC18, context);
    InitDerivedArrays(widget130, D_001ADFC8, context);
    widgetE4 = menu + 0xE4;
    InitDerivedArrays(widget98, D_001ADC28, context);
    widget17C = menu + 0x17C;
    InitDerivedArrays(widget400, D_001ADFD0, context);
    InitDerivedArrays(widget44C, D_001AE4D0, context);
    InitDerivedObjectB(barWidget, 0x20, 0, D_001AE040, context);
    SetWidgetPositionY(barWidget, 5);
    SetMeterMaximum(barWidget, 0x64);
    SetMeterValue(barWidget, 0);
    SetFirstPair(barWidget, 0x6049C1FF, 0x60001EFF);
    SetSecondPair(barWidget, 0x50F0C070, 0x50F0C070);
    iconWidget = menu + 0x378;
    SetTextAlignment(barWidget, 0x80000000);
    SetWidgetField38(barWidget, 0);
    backdropWidget = menu + 0x3B4;
    InitDerivedArrays(widgetE4, D_001ADFC0, context);
    text210 = menu + 0x210;
    InitDerivedArrays(widget17C, D_001AE4D8, context);
    text2A0 = menu + 0x2A0;
    text258 = menu + 0x258;
    colorSlot = GetFieldC(menu);
    text2E8 = menu + 0x2E8;
    *colorSlot = 0x60442D00;
    colorSlot2 = GetFieldC(widget4C);
    text330 = menu + 0x330;
    *colorSlot2 = 0x55F0C070;
    *(s32 *)GetFieldC(widget130) = 0x80FFDE8D;
    *(s32 *)GetFieldC(widget98) = 0x55F0C070;
    *(s32 *)GetFieldC(widgetE4) = 0x80FFDE8D;
    *(s32 *)GetFieldC(widget17C) = 0x60241700;
    *(s32 *)GetFieldC(widget400) = 0x60442D00;
    *(s32 *)GetFieldC(widget44C) = 0x55F0C070;
    SetFieldAt40(menu, D_001A8CFC + 0x8710, 0x21);
    SetFieldAt40(widget4C, D_001A8CFC + 0x8710, 0x22);
    SetFieldAt40(widget130, D_001A8CFC + 0x8710, 0x28);
    SetFieldAt40(widget98, D_001A8CFC + 0x8710, 0x23);
    SetFieldAt40(widgetE4, D_001A8CFC + 0x8710, 0x27);
    SetFieldAt40(widget17C, D_001A8CFC + 0x8710, 0x2A);
    SetFieldAt40(widget400, D_001A8CFC + 0x8710, 0x2C);
    SetFieldAt40(widget44C, D_001A8CFC + 0x8710, 0x2B);
    (*(s32 *)((s8 *)(menu) + (0x4FC))) = 0;
    (*(s32 *)((s8 *)(menu) + (0x500))) = 0;
    InitDerivedObjectC(iconWidget, D_001ADFD8, context);
    *(s32 *)GetFieldC(iconWidget) = 0x60F0F0B0;
    SetSecondFloat4(iconWidget, 32.0f, 32.0f, 0.0f, 0.0f);
    InitDerivedArrays(backdropWidget, D_001ADFA0, context);
    *(s32 *)GetFieldC(backdropWidget) = 0x60241700;
    SetFieldAt40(backdropWidget, D_001A8CFC + 0x8710, 0x29);
    SetSecondFloat4(backdropWidget, 1.0f, 1.0f, 0.0f, 0.0f);
    InitWidgetDefaults(text210, D_001ADC30, context);
    InitWidgetDefaults(text258, D_001ADC30, context);
    SetWidgetField44(text258, 1);
    InitWidgetDefaults(text2A0, D_001ADC30, context);
    SetWidgetField44(text2A0, 1);
    InitWidgetDefaults(text2E8, D_001AE4E8, context);
    SetWidgetField44(text2E8, 1);
    InitWidgetDefaults(text330, D_001AE4F8, context);
    SetWidgetField44(text330, 1);
    *(s32 *)GetFieldC(text210) = 0x80F0F0F0;
    *(s32 *)GetFieldC(text258) = 0x80F0F0F0;
    *(s32 *)GetFieldC(text2A0) = 0x80F0F0F0;
    *(s32 *)GetFieldC(text2E8) = 0x80F0F0F0;
    *(s32 *)GetFieldC(text330) = 0x80F0F0F0;
    SetWidgetField40(text210, GetLocalizedString(0x2D51));
    SetWidgetField40(text258, menu + 0x4A0);
    SetWidgetField40(text2A0, menu + 0x4B8);
    UpdateItemGridMenu(menu, 0);
}
