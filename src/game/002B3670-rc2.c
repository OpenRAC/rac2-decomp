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

extern f32 vec_distance_xy(void *, s32);
extern s32 point_in_path_xy(s32, void *, s32);
extern struct { s32 w0; s32 w1; s32 w2; } g_hero_moby;
extern volatile s32 g_current_game_mode;
extern s32 *g_path_table[];

typedef int TI __attribute__((mode(TI)));

/* Checks how close a spot is to the hero and returns 2 for the near zone, 1 for the far zone or 0 for neither. */
s32 hero_check_distance_zones(void *object, s32 *outHero, s32 nearIndex, s32 farIndex, void *posOverride, f32 nearDistance, f32 farDistance) {
    TI position;
    f32 distance;
    s32 hero;
    s32 *nearZone;
    s32 *farZone;

    if (posOverride != 0) {
        position = *(TI *)posOverride;
    } else {
        position = *(TI *)((s8 *)object + 0x10);
    }
    hero = g_hero_moby.w0;
    *outHero = hero;
    if (g_current_game_mode != 0) {
        return 0;
    }
    distance = vec_distance_xy(&position, hero + 0x10);
    if (nearIndex != -1) {
        nearZone = g_path_table[nearIndex];
        if (point_in_path_xy(*outHero + 0x10, (s8 *)nearZone + 0x10, *nearZone) != 0) {
            return 2;
        }
    } else {
        if (distance < nearDistance) {
            return 2;
        }
    }
    if (farIndex != -1) {
        farZone = g_path_table[farIndex];
        if (point_in_path_xy(*outHero + 0x10, (s8 *)farZone + 0x10, *farZone) != 0) {
            return 1;
        }
    } else {
        if (distance < farDistance) {
            return 1;
        }
    }
    return 0;
}
