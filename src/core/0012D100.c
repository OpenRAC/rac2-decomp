#include "common.h"
#include "structs.h"

extern void func_0012C3B0(void *);

extern void r1_func_0012C468(void *, void *);

extern int func_0012C878(void *, int);

extern void func_0012C380(char *, unsigned int);

extern void func_0012D100(void *);

extern char r1_D_001539E8[];

extern char r1_D_00153A10[];

extern void func_0012D1C8(void *);

typedef struct {
    char pad_00[0x13C];
    int  unk_13C;
    char pad_140[0x150 - 0x140];
    int  unk_150;
    char pad_154[0x174 - 0x154];
    int  unk_174;
    int  unk_178;
    char pad_17C[0x184 - 0x17C];
    int  unk_184;
    char pad_188[0x18C - 0x188];
    int  f1[3];
    int  f2[3];
} State;

extern void func_0012D2C0(void *);

extern int func_0012B678(void *);

extern char r1_D_00153A40[];

extern char r1_D_00153A60[];

extern void r1_func_00129E30();

extern void r1_func_00129F40();

extern char r1_D_00153A80[];

extern void r1_func_00116248_4(void *, char *, int, int) __asm__("r1_func_00116248");

extern void r1_func_0012C468_a(void *, void *) __asm__("r1_func_0012C468");

/* rac1-decomp src/core/00125630.c: func_001292E0 */
/* quantMatrixExtension (libmpeg.a:mpc.o): ISO/IEC 13818-2 6.2.3.2
 * quant_matrix_extension(). Unlike the reference decoder's 64-coefficient
 * software copy loops, this hardware-assisted port just flags the IPU to
 * pull the following intra/non-intra matrix straight off the bitstream
 * (waitIpuIdle, sendIpuCommand(0x50000000 / 0x58000000), waitIpuIdle) when
 * load_intra/non_intra_quantizer_matrix is set, storing the flag at
 * +0x840/+0x844 either way. The chroma variants aren't hardware-supported:
 * setting either just logs a warning through r1_func_0012C468.
 */
/* Reads the quantizer matrix flags of an MPEG video header and tells the video chip to load the matrices. */
void func_0012D100(void *decoder) {
    char *dec = (char *)decoder;
    int loadFlag;

    loadFlag = ReadMpegBits(dec, 1);        /* load_intra_quantizer_matrix */
    *(int *)(dec + 0x840) = loadFlag;
    if (loadFlag != 0) {
        WaitIpuIdle(dec);
        SendIpuCommand(dec, 0x50000000);
        WaitIpuIdle(dec);
    }

    loadFlag = ReadMpegBits(dec, 1);        /* load_non_intra_quantizer_matrix */
    *(int *)(dec + 0x844) = loadFlag;
    if (loadFlag != 0) {
        WaitIpuIdle(dec);
        SendIpuCommand(dec, 0x58000000);
        WaitIpuIdle(dec);
    }

    if (ReadMpegBits(dec, 1) != 0) {    /* load_chroma_intra_quantizer_matrix */
        r1_func_0012C468(dec, r1_D_001539E8);
    }

    if (ReadMpegBits(dec, 1) != 0) {    /* load_chroma_non_intra_quantizer_matrix */
        r1_func_0012C468(dec, r1_D_00153A10);
    }
}

/* rac1-decomp src/core/00125630.c: func_001293A8 */
/* Reads the display offsets of an MPEG picture header into the video decoder. */
void func_0012D1C8(void *decoderArg) {
    State *dec = (State *)decoderArg;
    int offsetCount;
    int i;

    if (dec->unk_13C != 0) {
        if (dec->unk_184 == 0) {
            offsetCount = 1;
        } else {
            offsetCount = dec->unk_178 != 0 ? 3 : 2;
        }
    } else {
        if (dec->unk_174 != 3) {
            offsetCount = 1;
        } else {
            offsetCount = dec->unk_184 != 0 ? 3 : 2;
        }
    }

    for (i = 0; i < offsetCount; i++) {
        dec->f1[i] = ReadMpegBits(dec, 0x10);
        ReadMpegBits(dec, 1);
        dec->f2[i] = ReadMpegBits(dec, 0x10);
        ReadMpegBits(dec, 1);
    }
}

/* rac1-decomp src/core/00125630.c: func_001294A0 */
/* copyrightExtension (libmpeg.a:mpc.o) -- ISO/IEC 13818-2 6.2.3.6: skip the
 * copyright_extension() fields with func_0012C878 (nextBit, "get n bits").
 * Reference decoder (mpeg2decode gethdr.c copyright_extension()) assigns
 * each field to a local only used by its VERBOSE printf, which this port
 * drops entirely, so every nextBit's result is a dead store the compiler
 * elides -- the sequence is bare `nextBit(s, width)` calls, and the final
 * one, its value discarded, becomes 2.9-ee's bare tail jump.
 */
/* Skips over the copyright information in an MPEG video header. */
void func_0012D2C0(void *decoder) {
    ReadMpegBits(decoder, 1);   /* copyright_flag */
    ReadMpegBits(decoder, 8);   /* copyright_identifier */
    ReadMpegBits(decoder, 1);   /* original_or_copy */
    ReadMpegBits(decoder, 7);   /* reserved */
    ReadMpegBits(decoder, 1);   /* marker_bit */
    ReadMpegBits(decoder, 20);  /* copyright_number_1 */
    ReadMpegBits(decoder, 1);   /* marker_bit */
    ReadMpegBits(decoder, 22);  /* copyright_number_2 */
    ReadMpegBits(decoder, 1);   /* marker_bit */
    ReadMpegBits(decoder, 22);  /* copyright_number_3 */
}

/* rac1-decomp src/core/00125630.c: func_00129530 */
/*
 * Decoder state step: if the picture state (s+0x174) is 3 and s+0x120 is
 * set, report r1_D_00153A40 through r1_func_0012C468, clear s+0x120 and re-read
 * the state; pick the target pointer by state (3 -> +0x1C0, 1 -> +0x1D0,
 * 2 -> +0x1E0, anything else -> +0x1C0 plus a r1_D_00153A60 report; the
 * field is a POINTER, the target of the final +0x28 write); then
 * r = func_0012B678(s), and if r, target->+0x28 = 1. Exact under both
 * compilers.
 *
 * It is a `switch`, with the case bodies in the order 3, 1, 2, default.
 * GCC's decision tree is fixed (==2, <3, ==1 / ==3), but the body that
 * follows the dispatch is the first case in source order, and jump.c
 * then turns `beq 3,case3; b default` into retail's `bne 3,default` plus
 * fall-through (the nested-if decode was 200 against 204). The state is
 * re-read into the local after the report, as 2.95.3 needs; switching on
 * the memory re-read is exact under 2.9-ee too.
 */
/* Picks the frame buffer for the current MPEG picture, decodes it and marks it ready. */
int func_0012D350(void *decoder) {
    char *dec = decoder;
    int state = *(int *)(dec + 0x174);
    char *target;
    int result;

    if (state == 3 && *(int *)(dec + 0x120) != 0) {
        r1_func_0012C468(dec, r1_D_00153A40);
        *(int *)(dec + 0x120) = 0;
        state = *(int *)(dec + 0x174);
    }
    switch (state) {
    case 3:
        target = *(char **)(dec + 0x1C0);
        break;
    case 1:
        target = *(char **)(dec + 0x1D0);
        break;
    case 2:
        target = *(char **)(dec + 0x1E0);
        break;
    default:
        target = *(char **)(dec + 0x1C0);
        r1_func_0012C468(dec, r1_D_00153A60);
        break;
    }
    result = DecodeMpegPicture(dec);
    if (result != 0) {
        *(int *)(target + 0x28) = 1;
    }
    return result;
}

/* rac1-decomp src/core/00125630.c: func_00129600 */
/* Decodes the pending MPEG picture into its frame buffer and advances the decoder state. */
void func_0012D420(void *decoder, int sliceCount, int doDecode) {
    char *dec = (char *)decoder;
    int bufA, bufB;

    if (doDecode != 0) {
        if (*(int *)(dec + 0x174) == 3) {
            if (*(int *)(dec + 0x150) == 3) {
                bufA = *(int *)(dec + 0x1C4);
            } else {
                bufA = *(int *)(dec + 0x1B8);
            }
            r1_func_00129E30(dec, bufA, sliceCount - 1);
        } else {
            if (*(int *)(dec + 0x150) == 3) {
                bufA = *(int *)(dec + 0x1D4);
                bufB = *(int *)(dec + 0x1E4);
            } else {
                bufA = *(int *)(dec + 0x1C8);
                bufB = *(int *)(dec + 0x1D8);
            }
            r1_func_00129F40(dec, bufA, bufB, sliceCount - 1);
        }
    }
    if (*(int *)(dec + 0xF8) == 1) {
        *(int *)(dec + 0xF8) = 2;
    }
}

#define PI_(o) (*(int *)((char *)p + (o)))
#define PP_(o) (*(char **)((char *)p + (o)))
#define RDY_(o) (*(int *)(PP_(o) + 0x28))

/* rac1-decomp src/core/00125630.c: func_0012D4B0 */
/* Picks and prepares the next MPEG frame buffers, then fills in the picture record. Returns 1 when a picture is ready. */
int func_0012D4B0(void *p, int swapBuffers) {
    char *record;
    int ready;
    int fieldCount;
    char *swapTmp;
    char *curBuf;

    record = 0;
    ready = 0;
    fieldCount = (PI_(0x174) == 3) ? 2 : 4;
    if (PI_(0x150) == 3) {
        PP_(0x1C0) = PP_(0x1C4);
        PP_(0x1D0) = PP_(0x1D4);
        PP_(0x1E0) = PP_(0x1E4);
        if (PI_(0xA0) + PI_(0xA4) >= fieldCount) {
            PI_(0xE8) = 0;
            PI_(0x1A8) = 0;
            PI_(0x1A4) = 0;
        }
        if ((PI_(0xE8) != 0 || PI_(0x1A8) != 0) && PI_(0x1A4) == 0) {
            RDY_(0x1B8) = 0;
            RDY_(0x1C8) = 0;
            RDY_(0x1D8) = 0;
        }
        PI_(0xE8) = 0;
        PI_(0x1A8) = 0;
        if (PI_(0x174) == 3) {
            if (RDY_(0x1B8) == 1 || PI_(0x1A4) != 0) {
                if (RDY_(0x1BC) == 1) {
                    ready = 1;
                }
            }
        } else {
            if ((RDY_(0x1C8) == 1 && RDY_(0x1D8) == 1) || PI_(0x1A4) != 0) {
                if (RDY_(0x1CC) == 1) {
                    if (RDY_(0x1DC) == 1) {
                        ready = 1;
                    }
                }
            }
        }
    } else {
        if (swapBuffers == 0) {
            swapTmp = PP_(0x1B8);
            PP_(0x1B8) = PP_(0x1BC);
            PP_(0x1BC) = swapTmp;
            swapTmp = PP_(0x1C8);
            PP_(0x1C8) = PP_(0x1CC);
            PP_(0x1CC) = swapTmp;
            swapTmp = PP_(0x1D8);
            PP_(0x1D8) = PP_(0x1DC);
            PP_(0x1DC) = swapTmp;
        }
        PP_(0x1C0) = PP_(0x1BC);
        PP_(0x1D0) = PP_(0x1CC);
        PP_(0x1E0) = PP_(0x1DC);
        if (PI_(0x174) == 3) {
            if (PI_(0x150) != 2 || RDY_(0x1B8) == 1) {
                ready = 1;
            }
        } else {
            curBuf = (PI_(0x174) == 1) ? PP_(0x1E0) : PP_(0x1D0);
            if (PI_(0x150) != 2 || (swapBuffers != 0 && *(int *)(curBuf + 0x28) == 1) ||
                (RDY_(0x1C8) == 1 && RDY_(0x1D8) == 1)) {
                ready = 1;
            }
        }
    }
    switch (PI_(0x174)) {
    case 3:
        record = PP_(0x1C0);
        break;
    case 1:
        record = PP_(0x1D0);
        break;
    case 2:
        record = PP_(0x1E0);
        break;
    }
    *(int *)(record + 0x28) = 0;
    *(long *)(record + 0x18) = *(long *)((char *)p + 0x828);
    *(int *)(record + 0x2C) = PI_(0x150);
    *(long *)(record + 0x20) = *(long *)((char *)p + 0x830);
    *(int *)(record + 0x30) = PI_(0x174);
    *(int *)(record + 0x34) = PI_(0x13C);
    *(int *)(record + 0x38) = PI_(0x188);
    *(int *)(record + 0x3C) = PI_(0x178);
    *(int *)(record + 0x40) = PI_(0x184);
    *(int *)(record + 0x44) = PI_(0x18C);
    *(int *)(record + 0x48) = PI_(0x190);
    *(int *)(record + 0x4C) = PI_(0x194);
    *(int *)(record + 0x50) = PI_(0x198);
    *(int *)(record + 0x54) = PI_(0x19C);
    *(int *)(record + 0x58) = PI_(0x1A0);
    *(int *)(record + 0x5C) = PI_(0x148);
    *(int *)(record + 0x60) = PI_(0x14C);
    return ready;
}

/* rac1-decomp src/core/00125630.c: func_00129948 */
/* Does the request at arg1 fit the heap described by arg0? A sized
   request (+0xE0 non-zero) has to fit both the byte budget at +0xDC and
   the entry budget at +0xE0; an unsized one has to fit width * height
   against +0xE4. On a refusal, format the two figures into the message
   at r1_D_00153A80 and report it. Returns whether it fits. */
/* Checks that a picture fits in the decoder memory and reports an error if not. */
int func_0012D768(void *decoder, void *picture) {
    char buf[0x100];
    char *dec = (char *)decoder;
    char *pic = (char *)picture;
    int budget = *(int *)(dec + 0xE0);
    int fits;

    if (budget != 0) {
        fits = *(int *)(dec + 0xDC) >= *(int *)(pic + 0x4) &&
             budget >= *(int *)(pic + 0x8);
    } else {
        fits = *(int *)(dec + 0xE4) >= *(int *)(pic + 0xC) * *(int *)(pic + 0x10);
    }
    if (fits == 0) {
        r1_func_00116248_4(buf, r1_D_00153A80, *(int *)(pic + 0x4),
                        *(int *)(pic + 0x8));
        r1_func_0012C468_a(decoder, buf);
    }
    return fits;
}
