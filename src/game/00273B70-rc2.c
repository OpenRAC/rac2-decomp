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

extern s8 D_0026C550[];
extern s8 func_00274C90(void *, s8 *, s32);
extern void func_0029F840(void *, s8 *, s8 *, s16);
extern s32 func_00273D10(void *);
extern s32 func_00273E98(void *);
extern s32 func_00274118(void *);
extern s32 func_00274120(void *);
extern s32 func_00282978(void *);
extern s32 D_001B1688;

s32 func_00273B70(void *arg0) {
    s8 loc[0x210];
    s8 *s0;
    s32 s2;
    u32 sel;
    f32 f;

    static void *tgt[] = {&&case02, &&case02, &&case4, &&case5, &&case13, &&case13};

    s0 = (*(s8 **)((s8 *)(arg0) + (0x68)));
    s2 = 0;
    sel = (*(u8 *)((s8 *)(s0) + (0x5D)));
    if (sel >= 6) {
        goto done;
    }
    {
        s8 *tb = D_0026C550;

        goto *(void *)*(s32 *)(tb + sel * 4);
    }

case02:
    if ((*(u8 *)((s8 *)(s0) + (0x5D))) == 0) {
        (*(s8 *)((s8 *)(s0) + (0x58))) = func_00274C90(arg0, loc, 0x20);
    } else {
        func_0029F840(arg0, loc + 0x200, loc, (*(s16 *)((s8 *)(s0) + (0x36))));
    }
    (*(s8 **)((s8 *)(s0) + (0x30))) = loc;
    s2 = func_00273D10(arg0);
    if (!((*(u8 *)((s8 *)(s0) + (0x5C))) == 0 && (D_001B1688 & 3) != 0)) {
        s2 = (FastDecTimer(s0 + 0x34) != 0) ? 1 : s2;
    }
    (*(s8 **)((s8 *)(s0) + (0x30))) = 0;
    goto done;

case4:
    s2 = func_00274118(arg0);
    goto done;

case5:
    s2 = func_00274120(arg0);
    goto done;

case13:
    s2 = func_00273E98(arg0);
    s2 = (FastDecTimer(s0 + 0x34) != 0) ? 1 : s2;
    goto done;

done:
    f = (*(f32 *)((s8 *)(arg0) + (0x10)));
    if (f < 2.0f || f > 1021.0f) {
        return 1;
    }
    f = (*(f32 *)((s8 *)(arg0) + (0x14)));
    if (f < 2.0f || f > 1021.0f) {
        return 1;
    }
    f = (*(f32 *)((s8 *)(arg0) + (0x18)));
    if (f < 2.0f || f > 1021.0f) {
        return 1;
    }
    return s2;
}
