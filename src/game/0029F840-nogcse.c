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

extern void scale_vector(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_fast_helper_e(void *, unsigned long long);
extern void FastVecScale(void *, void *, float);
/* Builds a joint's position matrix and optional point list from the moby's animation data. Returns how many points it wrote. */
int moby_get_joint_matrix(char *obj, char *m, char *out, int index) {
    char *class_data = *(char **)(obj + 0x24);
    int cnt = *(short *)(class_data + 0x2E);
    int tab;
    char *rec;
    int n;
    int i;
    int record_offset;
    char *dst;
    float unit_scale;
    float scale;

    if (cnt == 0) {
        goto fail;
    }
    tab = (int)class_data + cnt * 16;
    index += tab;
    record_offset = ((unsigned char *)index)[1];
    class_data = m;
    if (record_offset == 0xFF) {
        do {
fail:
            return 0;
        } while (0);
    }
    do {
        scale = *(float *)(obj + 0x2C);
    } while (0);
    unit_scale = 0.0009765625f;
    do {
        record_offset *= 16;
    } while (0);
    rec = (char *)tab + record_offset;
    scale_vector(class_data, rec, scale * unit_scale);
    rec += 0x10;
    matrix_mul_vec3(m, m, obj + 0xC0);
    FastVecAdd(m, m, obj + 0x10);
    do {
        n = *(short *)(rec + 6);
    } while (0);
    if (out != 0 && n > 0) {
        dst = out;
        for (i = n; i != 0;) {
            i--;
            vec_fast_helper_e(dst, *(unsigned long long *)rec);
            rec += 8;
            FastVecScale(dst, dst, *(float *)(obj + 0x2C) * unit_scale);
            *(float *)(dst + 0xC) = 1.0f;
            dst += 0x10;
        }
    }
    return n;
}
