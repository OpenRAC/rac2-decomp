#include "ps2_hw.h"
#include "names.h"


typedef int s32;

typedef unsigned char u8;

typedef unsigned int u32;

/* Mechanical source-first reuse of Lombyte SDK/library/cpr8.c and its
 * project-owned type header. Current upstream2c4452dd/source snapshot/object
 * proofs are retained in the private source packet. All original source
 * expressions, goto/loop order, field widths and hardware operations remain.
 * Type/function identifiers are namespaced, and existing EE scalar types are
 * reused. Four original helper calls use independently full-byte-identified
 * RAC2 targets; these privileged helpers remain original, with zero C credit.
 * RAC2 acceptance requires an independent current whole-unit qualification.
 */
/*
MIT License

Copyright (c) 2026 Mateusz Kłysz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/


struct Rac1Cpr8Input {
    u8 pad_0[0xD8];
    s32 unkD8;
};

struct Rac1Cpr8Output {
    s32 unk0;
    u8 pad_4[0x8];
    s32 unkC;
    s32 unk10;
};

struct Rac1Cpr8InputView {
    u8 pad_0[0xE0];
    s32 unkE0;
    s32 unkE4;
    u8 pad_E8[0x8C];
    s32 unk174;
};

extern s32 DIntr();

extern s32 func_0011F628();

/* Copies a decoded video picture to the screen buffer in chunks using two DMA channels. */
void mpeg_copy_picture_to_screen(struct Rac1Cpr8Input *input, struct Rac1Cpr8Output *output) {
    struct Rac1Cpr8InputView *view;
    s32 passCount;
    s32 srcBase;
    s32 intrState2;
    s32 intrState1;
    s32 chromaSize;
    s32 row;
    s32 srcAddr;
    s32 dstAddr;
    s32 qwCount;
    s32 dstStep;
    s32 srcStep;
    s32 chromaSizeUsed;
    s32 pass;

    view = (struct Rac1Cpr8InputView *)input;
    dstAddr = output->unk0 & 0x0FFFFFFF;
    srcBase = input->unkD8 & 0x0FFFFFFF;
    if (view->unk174 == 3) {
        goto block_3;
    }
    chromaSize = view->unkE0;
    chromaSizeUsed = chromaSize;
    if (chromaSize != 0) {
        goto block_8;
    }
    goto block_4;
block_3:
    chromaSizeUsed = view->unkE0;
block_4:
    dstStep = output->unk10 * 0x180;
    qwCount = dstStep >> 4;
    if (chromaSizeUsed == 0) {
        goto block_6;
    }
    srcStep = (chromaSizeUsed >> 4) * 0x180;
    goto block_7;
block_6:
    srcStep = dstStep;
block_7:
    passCount = 1;
    goto block_9;
block_8:
    srcStep = (chromaSize >> 4) * 0xC0;
    dstStep = ((s32) output->unk10 >> 1) * 0x180;
    passCount = 2;
    qwCount = dstStep >> 4;
block_9:
    pass = 0;
    while (pass < passCount) {
        srcAddr = srcBase;
        for (row = 0; row < output->unkC; row++) {
            intrState1 = DIntr();
            D9_SADR = 0;
            D9_MADR = dstAddr;
            D9_QWC = qwCount;
            D9_CHCR = 0x101;
            if (intrState1 == 0) {
                goto block_15;
            }
            func_0011F628();
        block_15:
            while (D9_CHCR & 0x100) {
            }
            intrState2 = DIntr();
            D8_SADR = 0;
            D8_MADR = srcAddr;
            D8_QWC = qwCount;
            D8_CHCR = 0x100;
            if (intrState2 == 0) {
                goto block_19;
            }
            func_0011F628();
        block_19:
            while (D8_CHCR & 0x100) {
            }
            while (D8_QWC != 0) {
            }
            srcAddr += srcStep;
            dstAddr += dstStep;
        }
        pass++;
        srcBase += view->unkE4 * 0xC0;
    }
    return;
}
