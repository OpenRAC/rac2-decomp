#include "common.h"
#include "structs.h"

extern void r1_func_0012C468(void *, void *);

extern int func_0012C680(void *, int);

extern void func_0012C788(void *, int);

extern void r1_func_0012C430(void *, char *, int);

extern void func_0012C9C8(void *);

extern int func_0012CA48(void *);

extern char r1_D_00153900[];

extern char r1_D_00153928[];

extern int func_0012B780(void *, int, int *, int *, void *);

extern int func_0012B568(void *);

/* rac1-decomp src/core/00125630.c: func_00127960 */
/* sliceA0 (libmpeg.a:mpc.o): ISO/IEC 13818-2 6.2.4 slice_header(), the
 * hardware-VLC variant. nextStartCode, then peek 32 bits: if it isn't a
 * slice_start_code (0x101..0x1AF), report it (r1_func_0012C430) and return 2.
 * Otherwise consume the 32 bits, run sliceB (IPU setup) and
 * mbAddressIncrement, stash the raw increment at *arg3 (in case of a
 * fault), and if the fault flag (+0x11C, cleared at entry) got set, report
 * it (r1_func_0012C468) and return 1. On full success, compute the starting
 * macroblock address from the slice's row (low byte of the start code)
 * and the picture's mb width (+0x12C), overwrite *arg3 with 1, latch
 * +0x1B0, and zero eight fields of the *arg4 output struct.
 */
/* Reads the header of a slice (a row of macroblocks) and works out the first macroblock to decode. Returns 0 on success, nonzero on a stream error. */
int func_0012B780(void *decoderPtr, int mbCount, int *startMbAddr, int *mbIncOut, void *blockInfo) {
    char *dec = (char *)decoderPtr;
    char *blockInfoBytes = (char *)blockInfo;
    unsigned int code;
    int sliceB_result;
    int mbInc;
    int row;

    *(int *)(dec + 0x11C) = 0;
    SkipToMpegStartCode(dec);
    code = PeekMpegBits(dec, 0x20);

    if ((unsigned int)(code - 0x101) >= 0xAF) {
        r1_func_0012C430(dec, r1_D_00153900, code);
        return 2;
    }

    SkipMpegBits(dec, 0x20);
    sliceB_result = ReadMpegSliceHeaderExtra(dec);
    mbInc = ReadMpegMbAddressIncrement(dec);
    *mbIncOut = mbInc;

    if (*(int *)(dec + 0x11C) != 0) {
        r1_func_0012C468(dec, r1_D_00153928);
        return 1;
    }

    row = (sliceB_result << 7) + (int)(code & 0xFF) - 1;
    *startMbAddr = row * (*(int *)(dec + 0x12C)) + mbInc - 1;
    *mbIncOut = 1;
    *(int *)(dec + 0x1B0) = 1;
    *(int *)(blockInfoBytes + 0x14) = 0;
    *(int *)(blockInfoBytes + 0x10) = 0;
    *(int *)(blockInfoBytes + 0x4) = 0;
    *(int *)(blockInfoBytes + 0x0) = 0;
    *(int *)(blockInfoBytes + 0x1C) = 0;
    *(int *)(blockInfoBytes + 0x18) = 0;
    *(int *)(blockInfoBytes + 0xC) = 0;
    *(int *)(blockInfoBytes + 0x8) = 0;
    return 0;
}
