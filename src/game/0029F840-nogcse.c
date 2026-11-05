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

extern void func_00282D60(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283130(void *, unsigned long long);
extern void func_00282D30(void *, void *, float);
int func_0029F840(char *obj, char *m, char *out, int index) {
    char *p = *(char **)(obj + 0x24);
    int cnt = *(short *)(p + 0x2E);
    int tab;
    char *rec;
    int n;
    int i;
    int e;
    char *dst;
    float k;
    float s;

    if (cnt == 0) {
        goto fail;
    }
    tab = (int)p + cnt * 16;
    index += tab;
    e = ((unsigned char *)index)[1];
    p = m;
    if (e == 0xFF) {
        do {
fail:
            return 0;
        } while (0);
    }
    do {
        s = *(float *)(obj + 0x2C);
    } while (0);
    k = 0.0009765625f;
    do {
        e *= 16;
    } while (0);
    rec = (char *)tab + e;
    func_00282D60(p, rec, s * k);
    rec += 0x10;
    func_00283098(m, m, obj + 0xC0);
    func_00282CC0(m, m, obj + 0x10);
    do {
        n = *(short *)(rec + 6);
    } while (0);
    if (out != 0 && n > 0) {
        dst = out;
        for (i = n; i != 0;) {
            i--;
            func_00283130(dst, *(unsigned long long *)rec);
            rec += 8;
            func_00282D30(dst, dst, *(float *)(obj + 0x2C) * k);
            *(float *)(dst + 0xC) = 1.0f;
            dst += 0x10;
        }
    }
    return n;
}
