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

extern f32 ref_L30_004185E0_00 __attribute__((sda));
extern s8 ref_L30_004185E0_01[];
extern void ref_L30_004185E0_02(s32, s8 *, f32);
extern void ref_L30_004185E0_03(s32, s32, s8 *);
extern void ref_L30_004185E0_04(s8 *);

/* Updates the helper effect object this object owns and runs the effect's own update callback if it has one. */
void museum_effect_holder_update(s8 *moby) {
    s8 *vars;
    s8 *effect;
    s8 *holder;
    s32 effect_pos;
    s8 *table;

    table = ref_L30_004185E0_01;
    vars = *(s8 **)(moby + 0x68);
    effect = *(s8 **)(vars + 0x50);
    effect_pos = (s32)(effect + 0x10);
    ref_L30_004185E0_02(effect_pos, table, ref_L30_004185E0_00);
    ref_L30_004185E0_03(effect_pos, effect_pos, table - 0x230);
    if (*(void **)(effect + 0x64) != 0) {
        holder = *(s8 **)(vars + 0x50);
        (*(void (**)(s8 *))(holder + 0x64))(effect);
    }
    ref_L30_004185E0_04(*(s8 **)(vars + 0x50));
}
