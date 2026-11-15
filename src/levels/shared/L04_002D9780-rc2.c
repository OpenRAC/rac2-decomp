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

extern s8 g_hero_state[];
extern s8 D_0018A070[];
extern f32 ref_L04_002D9780_00(void *, void *, void *, s32);
extern void ref_L04_002D9780_01(void *, f32, f32);
extern void ref_L04_002D9780_02(void *, void *, f32, f32, f32, f32);

/* Sets the hero's turn and tilt speeds for its current state, then eases the camera values toward them. */
void hero_update_turn_tilt_speeds(void) {
    s8 *hero;
    s8 *heroA;
    s8 *heroB;

    s32 stateB;
    s32 stateA;
    s8 *camBlock;
    s8 *heroBase;
    f32 probeValue;

    hero = g_hero_state;
    if ((*(u8 *)((char *)(hero) + (0x22B4))) == 0) {
        (*(f32 *)((char *)(hero) + (0x258))) = 0.8f;
        (*(f32 *)((char *)(hero) + (0x25C))) = 0.7f;
        (*(f32 *)((char *)(hero) + (0x260))) = 0.45f;
    }
    stateB = (*(s32 *)((char *)(hero) + (0x229C)));
    if (stateB == 4) {
        heroA = g_hero_state;
        if ((*(s16 *)((char *)(heroA) + (0x4AC))) < (*(s32 *)((char *)(heroA) + (0x1B8))) && (*(u8 *)((char *)(heroA) + (0x49E))) == 0) {
            (*(f32 *)((char *)(heroA) + (0x25C))) = (*(f32 *)((char *)(heroA) + (0x4B8)));
        }
    } else {
        stateA = (*(s32 *)((char *)(hero) + (0x2294)));
        if (stateA == 6) {
            (*(f32 *)((char *)(hero) + (0x25C))) = 0.5f;
        } else if (stateA == 4) {
            (*(f32 *)((char *)(hero) + (0x258))) = 0.35000002f;
        } else if ((u32)(stateB - 0x11) < 2U) {
            (*(s32 *)((char *)(hero) + (0x25C))) = 0;
            (*(s32 *)((char *)(hero) + (0x258))) = 0;
        } else {
            if ((*(u8 *)((char *)(hero) + (0x1492))) != 0 && (*(s32 *)((char *)(hero) + (0x340))) != 0) {
                (*(f32 *)((char *)(hero) + (0x258))) = 0.8f;
                (*(f32 *)((char *)(hero) + (0x25C))) = 0.9f;
            } else {
                hero = g_hero_state;
                if ((*(s32 *)((char *)(hero) + (0x2294))) == 0x7C) {
                    (*(f32 *)((char *)(hero) + (0x260))) = 0.8f;
                }
            }
        }
    }
    heroB = g_hero_state;
    if ((*(u8 *)((char *)(heroB) + (0x287))) == 0 || (*(s32 *)((char *)(heroB) + (0x22A4))) == 0x12 || (*(s32 *)((char *)(heroB) + (0x22B0))) == 0x12 || ((*(u8 *)((char *)(heroB) + (0x22B4))) == 0 && (*(f32 *)((char *)(heroB) + (0x254))) < 0.53f) || (*(s32 *)((char *)(heroB) + (0x229C))) == 0x11 || (*(u8 *)((char *)(heroB) + (0x1494))) != 0 || ((probeValue = ref_L04_002D9780_00(heroB + 0x240, heroB + 0x80, hero, stateB)), ((*(f32 *)((char *)(heroB) + (0x264))) * 0.5f) < probeValue)) {
        camBlock = D_0018A070;
        heroBase = camBlock - 0x250;
        ref_L04_002D9780_01(camBlock, (*(f32 *)((char *)(heroBase) + (0x258))), 0.02f);
        ref_L04_002D9780_01(camBlock + 4, (*(f32 *)((char *)(heroBase) + (0x25C))), 0.02f);
        ref_L04_002D9780_02(camBlock + 0x14, camBlock + 0x18, (*(f32 *)((char *)(heroBase) + (0x260))), 0.02f, 0.3f, 0.066666670143604278564453125f);
    }
}
