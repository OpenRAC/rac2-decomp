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
#ifndef NULL
#define NULL 0
#endif

extern s8 D_002359E0[];
extern s8 g_hero_state[];
extern f32 D_001B0594 __attribute__((sda));
extern f32 D_001B0598 __attribute__((sda));
extern void vec_clear_128(void *);
extern s32 math_random_int_range(s32, s32);
extern void *part_spawn_ground_effect(void *, s32, s32, s32, s32, void *, s32, f32, f32, f32);
extern s32 FloatToInt(f32);
extern void moby_get_facing_direction(s32, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);

/* Sets up 50 pairs of glowing sprites (one reddish, one red) along a trail that drifts toward the player's aim point. */
void part_init_trail_sparkle_pairs(void) {
    s8 zero_vec[16];
    s8 drift[16];
    s32 index;
    s32 alpha;
    s8 *point;
    s8 *sprite;
    s8 *hero;
    f32 red_size;

    index = 0;
    vec_clear_128(zero_vec);
    do {
        alpha = math_random_int_range(0, 0x6F) << 24;
        point = D_002359E0 + index * 16;
        sprite = part_spawn_ground_effect(point, 0xC, alpha | 0x7F2020, 0, 1, zero_vec, 0, D_001B0594 * 0.5f, D_001B0594, 0.0f);
        if (sprite != NULL) {
            *(s8 *)(sprite + 9) = (s8)(FloatToInt(4.0f) + 0x70);
        }
        red_size = D_001B0598;
        sprite = part_spawn_ground_effect(point, 0xC, alpha | 0xFF4040, 1, 1, zero_vec, 0, red_size * 0.5f, red_size, 0.0f);
        if (sprite != NULL) {
            *(s8 *)(sprite + 9) = (s8)(FloatToInt(4.0f) + 0x70);
        }
        index += 1;
        hero = g_hero_state;
        moby_get_facing_direction(*(s32 *)(hero + 0x2290) + 0x10, drift);
        vec_scale_to_length(drift, drift, -0.00277777785f);
        FastVecAdd(point, point, drift);
    } while (index < 0x32);
}
