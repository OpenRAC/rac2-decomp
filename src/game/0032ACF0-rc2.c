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

extern s8 g_debris_pieces[];
extern s8 g_hero_state[];
extern s32 math_fast_float_d(s8 *);
extern void FastVecAdd(s8 *, s8 *, s8 *);
extern void vec_scale_to_length(s8 *, s8 *, f32);
extern f32 FastAddRotations(f32, f32);
extern f32 IntToFloat(s32);
extern s32 FloatToInt(f32);
extern void math_apply_axis_rotation_to_quat(s8 *, s8 *, s8 *, f32);
extern void moby_get_facing_direction(s32, s8 *);
extern void part_claim_trail_node(s32, s8 *, s32);

/* Moves the flying debris pieces of an owner, leaves a glowing trail node behind each, and removes a piece when its life runs out. */
void part_update_debris_pieces(s32 owner) {
    s8 target_offset[16];
    s8 trail_pos[16];
    f32 life_now;
    f32 life_ratio;
    s8 *life_ptr;
    s8 *piece;
    s8 *table_end;
    s8 *table;
    s8 *hero;

    table = g_debris_pieces;
    life_ptr = table + 0x18;
    piece = table;
    table_end = piece + 0x240;
    hero = g_hero_state;
    do {
        if ((*(s32 *)((s8 *)(piece) + (0x1C))) == owner) {
            moby_get_facing_direction((*(s32 *)((s8 *)(hero) + (0x2290))) + 0x10, target_offset);
            life_now = IntToFloat((*(s32 *)((s8 *)(piece) + (0x18))));
            life_ratio = life_now / IntToFloat(0x25);
            math_apply_axis_rotation_to_quat(trail_pos, piece, target_offset, (*(f32 *)((s8 *)(piece) + (0x10))));
            part_claim_trail_node(owner, trail_pos, FloatToInt(life_ratio * 128.0f));
            (*(f32 *)((s8 *)(piece) + (0x10))) = FastAddRotations((*(f32 *)((s8 *)(piece) + (0x10))), (*(f32 *)((s8 *)(piece) + (0x14))));
            vec_scale_to_length(target_offset, target_offset, 0.04f);
            FastVecAdd(piece, piece, target_offset);
            if (math_fast_float_d(life_ptr) != 0) {
                (*(s32 *)((s8 *)(piece) + (0x1C))) = 0;
            }
        }
        piece += 0x30;
        life_ptr += 0x30;
    } while ((s32)piece < (s32)table_end);
}
