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

extern void ref_L09_003F0378_00(void);
extern s32 ref_L09_003F0378_01(f32);
extern void ref_L09_003F0378_02(void *, s32, s32, s32);
extern void ref_L09_003F0378_03(void *, s32, s32);
extern s32 ref_L09_003F0378_04(void *, s32, s32);
extern f32 ref_L09_003F0378_05(void *, s32);
extern void ref_L09_003F0378_06(void *, void *);
extern void ref_L09_003F0378_07(void *, s32);
extern void ref_L09_003F0378_08(void *, s32, s32, s32, f32, f32);

/* Handles damage to a Dobbo moby: when hit it loses health, flashes and reacts, or dies when health runs out. */
void func_L09_003F0378(void *moby) {
    void *vars;
    s32 hitDamage;
    s32 hitResult;
    s32 canTakeHit ;
    void *vars70;
    f32 newHealth;
    f32 damage;

    vars = *(void **)((s8 *)moby + 0x68);
    if (*(u8 *)((s8 *)moby + 0x95) == 0) {
        vars70 = (s8 *)vars + 0x70;
        ref_L09_003F0378_00();
    } else {
        vars70 = (s8 *)vars + 0x70;
        hitDamage = 0;
        hitResult = ref_L09_003F0378_04(moby, 0x10000, 0);
        canTakeHit = *(s16 *)((s8 *)vars + 0x26) < 1;
        hitDamage = canTakeHit ? hitResult : hitDamage;
        damage = ref_L09_003F0378_05(moby, hitDamage);
        if (hitDamage != 0) {
            if (damage > 0.0f) {
                newHealth = *(f32 *)((s8 *)vars + 0x20) - damage;
                *(f32 *)((s8 *)vars + 0x20) = newHealth;
                if (newHealth <= 0.0f) {
                    ref_L09_003F0378_03(moby, 6, 4);
                } else {
                    *(s8 *)((s8 *)vars + 0x77) = (s8)(ref_L09_003F0378_01(damage * 20.0f) + 0x64);
                    ref_L09_003F0378_06(moby, vars70);
                    if (*(u8 *)((s8 *)moby + 0x43) != 4) {
                        ref_L09_003F0378_02(moby, 4, 0, 1);
                    }
                    ref_L09_003F0378_03(moby, 5, -1);
                }
            }
        }
        *(u8 *)((s8 *)moby + 0xA8) = 0xFF;
    }
    ref_L09_003F0378_07(moby, (s32)vars70);
    ref_L09_003F0378_08(moby, *(s32 *)((s8 *)vars + 0x8C), 0, 0, 0.0f, 0.0f);
}
