#include "names.h"

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

extern void object_destroy_array(void *, s32);
extern void pool_free_cell(s32, s32);

extern s8 g_object_derived_table_c[];

/* Sets the object type pointer, releases the attached data when it is not in use and runs the shared base cleanup. */
void object_release_unused_data_cleanup(void *obj, s32 flags) {
    s32 attached;

    (*(s32 *)((char *)(obj) + (0x30))) = (s32)g_object_derived_table_c;
    attached = (*(s32 *)((char *)(obj) + (0x2C)));
    if ((attached != 0) && ((*(s32 *)((char *)(obj) + (0x38))) == 0)) {
        pool_free_cell(attached, (*(s32 *)((char *)(obj) + (0x34))));
    }
    object_destroy_array(obj, flags);
}
