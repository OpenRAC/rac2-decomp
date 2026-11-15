#include "common.h"
#include "structs.h"

extern void r1_func_0012C468(void *, void *);

extern int func_0012C680(void *, int);

extern int func_0012B8B0(void *, int);

extern int func_0012B1C0(void *);

extern int r1_func_001263A8(void *, int);

extern int func_0012B780(void *, int, int *, int *, void *);

extern int func_0012B568(void *);

extern char r1_D_00153948[];

extern int func_0012BB60(void *, int *, int *, int *, void *, void *, void *);

extern int r1_func_00125630(void *, int, int, int, int, void *, void *, void *);

extern char r1_D_00153968[];

/* rac1-decomp src/core/00125630.c: func_00127A90 */
/* slice0 (libmpeg.a:mpc.o): the per-picture macroblock loop -- sliceA0
 * (func_0012B780) parses the first slice header and starting mb address
 * (local "mbAddr"/"mbInc" pair, plus the zeroed 8-word block-info struct
 * at local0); then while mbAddr < mbCount: waitBdecOut (func_0012B1C0)
 * must succeed; if this macroblock doesn't already have a pending
 * mbAddressIncrement (mbInc==0, i.e. a fresh slice), peek 23 bits looking
 * for the next slice_start_code prefix, and if found read the next
 * mbAddressIncrement (func_0012B568) -- both faulting through +0x11C;
 * decode (decMB0, func_0012BB60) when mbInc==1, else skip (skipMB0,
 * func_0012BAA0) the run of skipped macroblocks; run motion compensation
 * (motionComp0, r1_func_00125630) on the result; for every macroblock after
 * the first, run the previous macroblock's IPU motion-comp dispatch
 * (doMC, r1_func_001263A8) using the alternating +0x810 buffer index before
 * flipping it; advance mbAddr and consume one mbInc, looping until the
 * picture's macroblocks are exhausted (return 0) or a fault (1/2/3)
 * happens along the way.
 */
/* Decodes the macroblocks of one picture in order. Returns 0 when done, or a nonzero code if the stream is damaged. */
int func_0012B8B0(void *decoderPtr, int mbCount) {
    char *dec = (char *)decoderPtr;
    int mbAddr = 0;
    int mbInc = 0;
    int mbType, motionType, dctType;
    int pmv[8];
    int mvfs[4];
    int dmvector[4];
    int r;

    r = ReadMpegSliceHeader(dec, mbCount, &mbAddr, &mbInc, pmv);
    if (r != 0) {
        return r;
    }
    *(int *)(dec + 0x11C) = 0;

    for (;;) {
        int mbIdx;
        char *entry;

        if (!(mbAddr < mbCount)) {
            return 0;
        }

        mbIdx = *(int *)(dec + 0x810);
        entry = dec + mbIdx * 0x140;
        *(int *)(entry + 0x6CC) = 0;
        r = WaitMpegBlockDecodeDone(dec);
        if (r == 0) {
            return 2;
        }

        if (mbInc == 0) {
            int peeked = PeekMpegBits(dec, 0x17);
            if (peeked == 0) {
                *(int *)(dec + 0x11C) = 0;
                return 3;
            }
            if (*(int *)(dec + 0x11C) != 0) {
                *(int *)(dec + 0x11C) = 0;
                return 3;
            }

            mbInc = ReadMpegMbAddressIncrement(dec);
            if (*(int *)(dec + 0x11C) != 0) {
                *(int *)(dec + 0x11C) = 0;
                return 1;
            }
        }

        if (!(mbAddr < mbCount)) {
            r1_func_0012C468(dec, r1_D_00153948);
            return 2;
        }

        if (mbInc == 1) {
            r = DecodeMpegMacroblockModes(dec, &mbType, &motionType, &dctType, pmv,
                               mvfs, dmvector);
            if (r == 0) {
                *(int *)(dec + 0x11C) = 0;
                return 1;
            }
        } else {
            r = HandleMpegSkippedMacroblock(dec, pmv, &motionType, mvfs, &mbType);
            if (r == 0) {
                *(int *)(dec + 0x11C) = 0;
                return 2;
            }
        }

        r = r1_func_00125630(dec, mbAddr, mbInc, mbType, motionType, pmv,
                           mvfs, dmvector);
        if (r == 0) {
            *(int *)(dec + 0x11C) = 0;
            return 2;
        }

        if (mbAddr != 0) {
            int curSlot = *(int *)(dec + 0x810);
            r1_func_001263A8(dec, curSlot ^ 1);
        }

        mbAddr = mbAddr + 1;
        *(int *)(dec + 0x810) ^= 1;
        mbInc = mbInc - 1;
    }
}

/* rac1-decomp src/core/00125630.c: func_00127C80 */
/* arg0 is a moby/entity-ish struct: a table index at +0x810 selects a
 * +0x140-strided sub-entry whose +0x6CC field gets set, and several
 * other struct-pointer outputs get filled from +0x150/+0x174 flags.
 * Ends by clearing bit 0 of *a4, reporting through r1_func_0012C468 (an
 * already-matched "log to r1_D_00153968" family member) first when
 * +0x150 == 1. The r1_func_0012C468 call takes arg0 -- the moby struct,
 * still live in $4 -- not a4/s0, which is a common trap here. */
/* Handles a skipped macroblock by setting default motion data and clearing its intra flag. Returns 0 on a stream error. */
int func_0012BAA0(void *decoderPtr, int *pmv, int *motionType, int *mvfs, int *mbType) {
    int idx;
    char *entry;
    int ret = 1;
    int c;
    int mask;

    idx = *(int *)((char *)decoderPtr + 0x810);
    entry = (char *)decoderPtr + idx * 0x140;
    *(int *)(entry + 0x6CC) = 1;
    *(int *)((char *)decoderPtr + 0x1B0) = 1;

    if (*(int *)((char *)decoderPtr + 0x150) == 2) {
        *(int *)((char *)pmv + 0x14) = 0;
        *(int *)((char *)pmv + 0x10) = 0;
        *(int *)((char *)pmv + 0x4) = 0;
        *(int *)((char *)pmv + 0x0) = 0;
    }

    if (*(int *)((char *)decoderPtr + 0x174) == 3) {
        *motionType = 2;
    } else {
        *motionType = 1;
        c = (*(int *)((char *)decoderPtr + 0x174) == 2);
        mvfs[1] = c;
        *mvfs = c;
    }

    if (*(int *)((char *)decoderPtr + 0x150) == 1) {
        r1_func_0012C468(decoderPtr, r1_D_00153968);
        ret = 0;
    }
    mask = *mbType;
    mask &= ~1;
    *mbType = mask;
    return ret;
}
