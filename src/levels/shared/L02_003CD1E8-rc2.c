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

typedef int TI __attribute__((mode(TI)));

extern f32 ref_L02_003CD1E8_00(f32);
extern f32 ref_L02_003CD1E8_01(f32);
extern void ref_L02_003CD1E8_02(void *, void *, void *);
extern f32 ref_L02_003CD1E8_03(f32, f32);
extern f32 ref_L02_003CD1E8_04(void);
extern s32 ref_L02_003CD1E8_05(void *, void *, void *, s32, f32);

/* Picks a random sideways direction and speed, then turns it to match the object facing and stores it as a velocity. */
void moby_set_random_spread_velocity(void *moby, void *out_velocity) {
    f32 angle;
    f32 vel_y;
    f32 speed;
    void *vars;
    TI home_copy;
    TI home_raw ;

    vars = (*(void **)((s8 *)(moby) + (0x68)));
    speed = ref_L02_003CD1E8_03(2.0f, 5.0f);
    angle = ref_L02_003CD1E8_04();
    (*(f32 *)((s8 *)(out_velocity) + (0))) = ref_L02_003CD1E8_00(angle) * speed;
    vel_y = ref_L02_003CD1E8_01(angle) * speed;
    (*(s32 *)((s8 *)(out_velocity) + (8))) = 0;
    (*(f32 *)((s8 *)(out_velocity) + (4))) = vel_y;
    ref_L02_003CD1E8_02(out_velocity, out_velocity, vars + 0x340);
    home_raw = *(volatile TI *)((char *)vars + 0x340);
    home_copy = home_raw;
    ref_L02_003CD1E8_05(&home_copy, out_velocity, out_velocity, (*(s32 *)((s8 *)(vars) + (0x318))), (*(f32 *)((s8 *)(vars) + (0x100))));
}
