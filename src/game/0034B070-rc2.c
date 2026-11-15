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

extern s32 func_00335AC8();
extern s32 func_003361A8();
extern s32 func_003366D0();
extern s32 func_00336968();
extern s32 func_00349498();
extern s32 func_00349918();
extern s32 func_00349CB8();

extern s8 D_001AD928[];
extern s8 D_001AD908[];
/* Builds the empty HUD object: starts every text, sprite, meter and animation part so the HUD can be filled in later. */
s32 func_0034B070(s32 hud) {
    s32 anim14D4;
    s32 fade1160;
    s32 fade1288;
    s32 fade13B0;
    s32 fadeF1C;
    s32 fade1044;
    s32 fade11F4;
    s32 fade131C;
    s32 link1444;
    s32 animE0C;
    s32 link1448;
    s32 fadeFB0;
    s32 anim144C;
    s32 anim10D8;
    s32 animE94;
    s32 slotPtr;
    s32 iconPtr;
    s32 slotLeft;
    s32 iconLeft;

    slotLeft = 7;
    slotPtr = hud + 0x358;
    ConstructDerivedObjectA(hud);
    ConstructDerivedObjectA(hud + 0x4C);
    ConstructDerivedObjectA(hud + 0x98);
    ConstructWidgetBase(hud + 0x100);
    ConstructDerivedObjectC(hud + 0x148);
    ConstructDerivedObjectA(hud + 0x184);
    ConstructDerivedObjectA(hud + 0x1D0);
    ConstructWidgetBase(hud + 0x238);
    ConstructDerivedObjectC(hud + 0x280);
    ConstructDerivedObjectA(hud + 0x2C0);
    ConstructDerivedObjectA(hud + 0x30C);
    do {
        slotLeft -= 1;
        ConstructDerivedObjectA(slotPtr);
        slotPtr += 0x4C;
    } while (slotLeft != -1);
    iconPtr = hud + 0x604;
    ConstructDerivedObjectA(hud + 0x5B8);
    iconLeft = 7;
    animE0C = hud + 0xE0C;
    animE94 = hud + 0xE94;
    fadeF1C = hud + 0xF1C;
    fadeFB0 = hud + 0xFB0;
    fade1044 = hud + 0x1044;
    anim10D8 = hud + 0x10D8;
    fade1160 = hud + 0x1160;
    fade11F4 = hud + 0x11F4;
    fade1288 = hud + 0x1288;
    fade131C = hud + 0x131C;
    fade13B0 = hud + 0x13B0;
    link1444 = hud + 0x1444;
    link1448 = hud + 0x1448;
    anim144C = hud + 0x144C;
    anim14D4 = hud + 0x14D4;
    do {
        iconLeft -= 1;
        ConstructDerivedObjectC(iconPtr);
        iconPtr += 0x3C;
    } while (iconLeft != -1);
    InitMeterScreenParts(hud + 0x7E8);
    ClearSixteenWords(hud + 0xBEC);
    ClearSixteenWords(hud + 0xC74);
    ClearSixteenWords(hud + 0xCFC);
    ClearSixteenWords(hud + 0xD84);
    ClearSixteenWords(animE0C);
    ClearSixteenWords(animE94);
    ClearEffectRowGroups(fadeF1C);
    ClearEffectRowGroups(fadeFB0);
    ClearEffectRowGroups(fade1044);
    ClearSixteenWords(anim10D8);
    ClearEffectRowGroups(fade1160);
    ClearEffectRowGroups(fade11F4);
    ClearEffectRowGroups(fade1288);
    ClearEffectRowGroups(fade131C);
    ClearEffectRowGroups(fade13B0);
    InitObjectTypePointer(link1444);
    (*(s32 *)((s8 *)(hud) + (0x1444))) = ((s32)D_001AD928);
    InitObjectTypePointer(link1448);
    (*(s32 *)((s8 *)(hud) + (0x1448))) = ((s32)D_001AD908);
    ClearSixteenWords(anim144C);
    ClearSixteenWords(anim14D4);
    return hud;
}
