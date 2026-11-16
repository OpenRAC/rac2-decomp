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

extern s32 func_00115544(s32, s32);
extern s32 func_001157AC(s32);
extern unsigned char *eh_read_uleb128(s32, s32);
extern unsigned char *eh_read_sleb128(s32, s32);

extern s8 g_str_eh_cie_augmentation_a[];
extern s8 g_str_eh_cie_augmentation_b[];

typedef struct {
    s32 v;
} __attribute__((packed)) UA32;

/* Reads the shared header of a frame record and gives back where its instructions start. */
s8 *eh_extract_cie_info(s32 fde, s32 info) {
    s32 uleb_value[4];
    s32 cie_ptr;
    s32 aug_end;
    s32 read_ptr;

    cie_ptr = (fde - *(s32 *)(fde + 4)) + 0xD;
    *(s32 *)info = cie_ptr;
    if (func_00115544(cie_ptr, (s32) g_str_eh_cie_augmentation_a) != 0 && func_00115544(*(s32 *)info, (s32) g_str_eh_cie_augmentation_b) != 0 && *(s8 *)*(s32 *)info != 0x7A) {
        return 0;
    }
    aug_end = *(s32 *)info + func_001157AC(*(s32 *)info);
    read_ptr = aug_end + 1;
    if (func_00115544(*(s32 *)info, (s32) g_str_eh_cie_augmentation_b) == 0) {
        *(s32 *)(info + 4) = ((UA32 *)read_ptr)->v;
        read_ptr = aug_end + 5;
    } else {
        *(s32 *)(info + 4) = 0;
    }
    read_ptr = eh_read_sleb128(eh_read_uleb128(read_ptr, info + 8), info + 0xC);
    *(s32 *)(info + 0x10) = *(u8 *)read_ptr;
    read_ptr = read_ptr + 1;
    if (*(s8 *)*(s32 *)info == 0x7A) {
        read_ptr = eh_read_uleb128(read_ptr, (s32) uleb_value) + uleb_value[0];
    }
    return (s8 *) read_ptr;
}
