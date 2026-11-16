#include "names.h"
/* func_PAL_L04_002D9718, the PAL copy of func_L04_002D9780: the same C, where lit 0.024f becomes 0.0288f. */

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
extern s8 g_hero_camera_block[];
extern f32 ref_L04_002D9780_00(void *, void *, void *, s32);
extern void ref_L04_002D9780_01(void *, f32, f32);
extern void ref_L04_002D9780_02(void *, void *, f32, f32, f32, f32);

/* Sets the hero's turn and tilt speeds for the current state and eases the camera block towards them (PAL: 50 Hz rate). */
void hero_update_turn_tilt_speeds_pal(void) {
    s8 *hero;
    s8 *hero_a;
    s8 *hero_b;

    s32 state_a;
    s32 state_b;
    s8 *camera_block;
    s8 *hero_base;
    f32 reach;

    hero = g_hero_state;
    if ((*(u8 *)((char *)(hero) + (0x22B4))) == 0) {
        (*(f32 *)((char *)(hero) + (0x258))) = 0.8f;
        (*(f32 *)((char *)(hero) + (0x25C))) = 0.7f;
        (*(f32 *)((char *)(hero) + (0x260))) = 0.45f;
    }
    state_a = (*(s32 *)((char *)(hero) + (0x229C)));
    if (state_a == 4) {
        hero_a = g_hero_state;
        if ((*(s16 *)((char *)(hero_a) + (0x4AC))) < (*(s32 *)((char *)(hero_a) + (0x1B8))) && (*(u8 *)((char *)(hero_a) + (0x49E))) == 0) {
            (*(f32 *)((char *)(hero_a) + (0x25C))) = (*(f32 *)((char *)(hero_a) + (0x4B8)));
        }
    } else {
        state_b = (*(s32 *)((char *)(hero) + (0x2294)));
        if (state_b == 6) {
            (*(f32 *)((char *)(hero) + (0x25C))) = 0.5f;
        } else if (state_b == 4) {
            (*(f32 *)((char *)(hero) + (0x258))) = 0.35000002f;
        } else if ((u32)(state_a - 0x11) < 2U) {
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
    hero_b = g_hero_state;
    if ((*(u8 *)((char *)(hero_b) + (0x287))) == 0 || (*(s32 *)((char *)(hero_b) + (0x22A4))) == 0x12 || (*(s32 *)((char *)(hero_b) + (0x22B0))) == 0x12 || ((*(u8 *)((char *)(hero_b) + (0x22B4))) == 0 && (*(f32 *)((char *)(hero_b) + (0x254))) < 0.53f) || (*(s32 *)((char *)(hero_b) + (0x229C))) == 0x11 || (*(u8 *)((char *)(hero_b) + (0x1494))) != 0 || ((reach = ref_L04_002D9780_00(hero_b + 0x240, hero_b + 0x80, hero, state_a)), ((*(f32 *)((char *)(hero_b) + (0x264))) * 0.5f) < reach)) {
        camera_block = g_hero_camera_block;
        hero_base = camera_block - 0x250;
        ref_L04_002D9780_01(camera_block, (*(f32 *)((char *)(hero_base) + (0x258))), 0.024f);
        ref_L04_002D9780_01(camera_block + 4, (*(f32 *)((char *)(hero_base) + (0x25C))), 0.024f);
        ref_L04_002D9780_02(camera_block + 0x14, camera_block + 0x18, (*(f32 *)((char *)(hero_base) + (0x260))), 0.028800001f, 0.43200004f, 0.080000006f);
    }
}
