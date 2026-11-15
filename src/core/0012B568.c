#include "common.h"
#include "structs.h"

/* func_0012C508 returns a short: its epilogue sign-extends $v0. */
extern short func_0012C508(int, int);

extern char r1_D_001538A8[];

extern int func_0012C680(void *, int);

extern void func_0012C788(void *, int);

extern void r1_func_0012C430(void *, char *, int);

extern int func_0012B568(void *);

extern void func_0012C3B0(void *);

extern void r1_func_0012C468(void *, void *);

extern char r1_D_001538E0[];

extern int func_0012B8B0(void *, int);

extern int func_0012B1C0(void *);

extern int r1_func_001263A8(void *, int);

extern int func_0012B678(void *);

/* rac1-decomp src/core/00125630.c: func_00127748 */
/* Reads how many macroblocks to advance, adding 33 for each escape code in the stream. */
int func_0012B568(void *decoderPtr) {
    char *dec = (char *)decoderPtr;
    unsigned int code;
    int val = 0;
    int cont;
    int ret;

    do {
        code = ReadIpuVlcCode((int)dec, 0);
        switch (code) {
        case 35:
            cont = 1;
            val += 33;
            break;
        case 0:
            ret = PeekMpegBits(dec, 11);
            if (*(int *)(dec + 0x848) != 0 && ret == 15) {
                SkipMpegBits(dec, 11);
                cont = 1;
            } else {
                r1_func_0012C430(dec, r1_D_001538A8, code);
                *(int *)(dec + 0x11C) = 1;
                return 1;
            }
            break;
        case 34:
            cont = 1;
            break;
        default:
            val += code;
            cont = 0;
            break;
        }
    } while (cont);

    return val;
}

/* rac1-decomp src/core/00125630.c: func_00127858 */
/* Decodes every macroblock of one picture and returns 1 on success, 0 on a stream error. */
int func_0012B678(void *decoderPtr) {
    char *dec = (char *)decoderPtr;
    int mbCount;
    int ret;

    *(int *)(dec + 0x810) = 0;
    *(int *)(dec + 0x814) = 0;

    mbCount = *(int *)(dec + 0x12C) * *(int *)(dec + 0x130);
    if (*(int *)(dec + 0x174) != 3) {
        mbCount >>= 1;
    }

    do {
        ret = DecodeMpegSliceMacroblocks(dec, mbCount);
    } while (ret == 1 || ret == 3);

    WaitIpuIdle(dec);
    if (WaitMpegBlockDecodeDone(dec) == 0) {
        ret = 2;
    }

    while (((D9_CHCR >> 8) & 1) != 0)
        ;

    if (ret == 0) {
        r1_func_001263A8(dec, (unsigned int)*(int *)(dec + 0x810) < 1);
    }

    if ((unsigned int)(ret - 1) < 2) {
        r1_func_0012C468(dec, r1_D_001538E0);
    }

    return (unsigned int)ret < 1;
}
