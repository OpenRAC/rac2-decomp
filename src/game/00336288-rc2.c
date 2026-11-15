
/* SPDX-License-Identifier: MIT
 * MIT License
 * 
 * Copyright (c) 2026 Forja contributors
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

extern void func_003360F8(void *, s32);
extern void func_00336ED0(s32, s32);

extern s8 D_001ADA58[];

/* Sets the object type pointer, releases the attached data when each part is not in use and runs the shared base cleanup. */
void func_00336288(void *obj, s32 flags) {
    s32 attached;

    (*(s32 *)((char *)(obj) + (0x30))) = (s32)D_001ADA58;
    attached = (*(s32 *)((char *)(obj) + (0x2C)));
    if (attached != 0) {
        if ((*(s32 *)((char *)(obj) + (0x44))) == 0) {
            FreePoolCell(attached, (*(s32 *)((char *)(obj) + (0x34))));
        }
        if ((*(s32 *)((char *)(obj) + (0x48))) == 0) {
            FreePoolCell((*(s32 *)((char *)(obj) + (0x2C))), (*(s32 *)((char *)(obj) + (0x38))));
        }
    }
    DestroyArrayObject(obj, flags);
}
