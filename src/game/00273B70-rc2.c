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

/* Updates one camera object each frame; returns 1 when it should be removed (for example when it leaves the world). */
s32 func_00273B70(void *arg0) {
    s8 buffer[0x210];
    s8 *vars;
    s32 result;
    u32 camMode;
    f32 coord;

    static void *tgt[] = {&&case02, &&case02, &&case4, &&case5, &&case13, &&case13};

    vars = (*(s8 **)((s8 *)(arg0) + (0x68)));
    result = 0;
    camMode = (*(u8 *)((s8 *)(vars) + (0x5D)));
    if (camMode >= 6) {
        goto done;
    }
    {
        s8 *table = D_0026C550;

        goto *(void *)*(s32 *)(table + camMode * 4);
    }

case02:
    if ((*(u8 *)((s8 *)(vars) + (0x5D))) == 0) {
        (*(s8 *)((s8 *)(vars) + (0x58))) = ConvertPackedPointsToVectors(arg0, buffer, 0x20);
    } else {
        GetMobyJointMatrix(arg0, buffer + 0x200, buffer, (*(s16 *)((s8 *)(vars) + (0x36))));
    }
    (*(s8 **)((s8 *)(vars) + (0x30))) = buffer;
    result = UpdateTargetSeekingMoby(arg0);
    if (!((*(u8 *)((s8 *)(vars) + (0x5C))) == 0 && (gGameTime & 3) != 0)) {
        result = (FastDecTimer(vars + 0x34) != 0) ? 1 : result;
    }
    (*(s8 **)((s8 *)(vars) + (0x30))) = 0;
    goto done;

case4:
    result = ReturnOneStubA(arg0);
    goto done;

case5:
    result = ReturnOneStubB(arg0);
    goto done;

case13:
    result = UpdateCollidingCameraMoby(arg0);
    result = (FastDecTimer(vars + 0x34) != 0) ? 1 : result;
    goto done;

done:
    coord = (*(f32 *)((s8 *)(arg0) + (0x10)));
    if (coord < 2.0f || coord > 1021.0f) {
        return 1;
    }
    coord = (*(f32 *)((s8 *)(arg0) + (0x14)));
    if (coord < 2.0f || coord > 1021.0f) {
        return 1;
    }
    coord = (*(f32 *)((s8 *)(arg0) + (0x18)));
    if (coord < 2.0f || coord > 1021.0f) {
        return 1;
    }
    return result;
}
