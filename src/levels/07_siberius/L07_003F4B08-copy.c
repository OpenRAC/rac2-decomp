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
extern u8 *CreateMoby(int);
extern float math_random_angle(void);
extern void matrix_from_basis_rows(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
/* Copy both complete vectors, retaining the new object's support record. */
/* Spawns a beam object (moby class 3624) at the owner, running from the first point to the second and optionally attached to a support object. */
u8 *beam_spawn(u8 *owner, u8 *support, void *first, void *second, float scale)
{
    float inverse[16] __attribute__((aligned(16)));
    u8 *vars;
    u8 *next;
    u8 *supportPosition;
    u8 *beam = CreateMoby(0xE28 /* moby class 3624 */);
    if (beam != 0) {
        qcopy(beam + 0x10, owner + 0x10);
        vars = *(u8 **)(beam + 0x68);
        beam[0x30] = 255;
        *(u8 **)(beam + 0xB8) = owner;
        qcopy(vars, first);
        next = vars + 0x10;
        qcopy(next, second);
        *(u8 **)(vars + 0x20) = support;
        *(u32 *)(vars + 0x24) = 0;
        *(float *)(vars + 0x28) = math_random_angle();
        *(float *)(vars + 0x2C) = scale;
        if (support != 0) {
            matrix_from_basis_rows(inverse, support + 0xC0);
            supportPosition = support + 0x10;
            FastVecSub(vars, vars, supportPosition);
            FastVecSub(next, next, supportPosition);
            matrix_mul_vec3(vars, vars, inverse);
            matrix_mul_vec3(next, next, inverse);
        }
    }
    return beam;
}
