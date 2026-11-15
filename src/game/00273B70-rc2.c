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

extern s8 D_0026C550[];
extern s8 coll_convert_packed_points_to_vectors(void *, s8 *, s32);
extern int moby_get_joint_matrix(void *, s8 *, s8 *, s16);
extern s32 target_seeker_update(void *);
extern s32 cam_moby_update_colliding(void *);
extern s32 stub_return_one_a(void *);
extern s32 stub_return_one_b(void *);
extern s32 FastDecTimer(void *);
extern s32 g_game_time;

/* Updates one camera object each frame; returns 1 when it should be removed (for example when it leaves the world). */
s32 cam_moby_update(void *arg0) {
    s8 buffer[0x210];
    s8 *vars;
    s32 result;
    u32 cam_mode;
    f32 coord;

    static void *tgt[] = {&&case02, &&case02, &&case4, &&case5, &&case13, &&case13};

    vars = (*(s8 **)((s8 *)(arg0) + (0x68)));
    result = 0;
    cam_mode = (*(u8 *)((s8 *)(vars) + (0x5D)));
    if (cam_mode >= 6) {
        goto done;
    }
    {
        s8 *table = D_0026C550;

        goto *(void *)*(s32 *)(table + cam_mode * 4);
    }

case02:
    if ((*(u8 *)((s8 *)(vars) + (0x5D))) == 0) {
        (*(s8 *)((s8 *)(vars) + (0x58))) = coll_convert_packed_points_to_vectors(arg0, buffer, 0x20);
    } else {
        moby_get_joint_matrix(arg0, buffer + 0x200, buffer, (*(s16 *)((s8 *)(vars) + (0x36))));
    }
    (*(s8 **)((s8 *)(vars) + (0x30))) = buffer;
    result = target_seeker_update(arg0);
    if (!((*(u8 *)((s8 *)(vars) + (0x5C))) == 0 && (g_game_time & 3) != 0)) {
        result = (FastDecTimer(vars + 0x34) != 0) ? 1 : result;
    }
    (*(s8 **)((s8 *)(vars) + (0x30))) = 0;
    goto done;

case4:
    result = stub_return_one_a(arg0);
    goto done;

case5:
    result = stub_return_one_b(arg0);
    goto done;

case13:
    result = cam_moby_update_colliding(arg0);
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
