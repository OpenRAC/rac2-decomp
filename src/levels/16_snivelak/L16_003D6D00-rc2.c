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

extern const s32 D_001A7A00;
extern s8 g_hero_position[];
extern s32 ref_L16_003D6D00_00;
extern struct { s32 w0; s32 w1; s32 w2; } ref_L16_003D6D00_01;
extern s32 ref_L16_003D6D00_02(s8 *, s32);
extern void ref_L16_003D6D00_03(s8 *, s32, s8 *);
extern void ref_L16_003D6D00_04(s8 *, s8 *, f32);
extern void ref_L16_003D6D00_05(s8 *, s8 *, s8 *);
extern s32 ref_L16_003D6D00_06(s8 *, s8 *, s32, s32, s32);
extern s32 ref_L16_003D6D00_07();
extern void ref_L16_003D6D00_08(s8 *, s32, s32);
extern void ref_L16_003D6D00_09(s32, s32);

/* Pulls the hero to this object and hurts him when he is in range. */
void hero_pull_and_hurt_on_contact(s8 *moby) {
    s32 *vars;
    s8 *hero;
    s8 *hero_base;
    s8 *hero_pos;
    s8 offset[0x10];

    vars = (*(s32 **)((s8 *)(moby) + (0x68)));
    if ((*(u8 *)((s8 *)(moby) + (0x20))) == 0) {
        (*(u8 *)((s8 *)(moby) + (0x30))) = 0xFF;
        (*(u8 *)((s8 *)(moby) + (0x20))) = 1;
    }
    hero = g_hero_position;
    if (ref_L16_003D6D00_02(hero, *vars) != 0) {
        hero_base = hero - 0x80;
        if ((*(s32 *)((s8 *)(hero_base) + (0x229C))) != 0xF) {
            hero_pos = hero + 0x270;
            ref_L16_003D6D00_03(hero_pos, ref_L16_003D6D00_00 + (*vars << 7) + 0x30, hero);
            ref_L16_003D6D00_04(hero_pos, hero_pos, 1.0f);
            (*(f32 *)((s8 *)(hero_base) + (0x2FC))) = 2.0f;
            (*(s16 *)((s8 *)(hero_base) + (0x218))) = 5;
            (*(s32 *)((s8 *)(hero_base) + (0x2F8))) = 0;
            if ((*(s32 *)((s8 *)(hero_base) + (0x340))) != 0 && (*(s32 *)((s8 *)(hero_base) + (0x2294))) != 0x38) {
                ref_L16_003D6D00_05(offset, hero, hero_pos);
                if (ref_L16_003D6D00_06(hero + 0x60, offset, 0, (*(s32 *)((s8 *)(hero_base) + (0x2290))), 0) != 0 && ref_L16_003D6D00_07() != 2 && ref_L16_003D6D00_01.w0 == 0) {
                    ref_L16_003D6D00_08(hero + 0x244C, 0, (s32)((f32)D_001A7A00 * 0.333f));
                    if ((*(s32 *)((s8 *)(hero_base) + (0x24CC))) != 0) {
                        ref_L16_003D6D00_09(0x38, 1);
                    }
                }
            }
        }
    }
}
