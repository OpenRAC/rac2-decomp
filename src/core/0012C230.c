#include "common.h"
#include "structs.h"

/* func_0012C508 returns a short: its epilogue sign-extends $v0. */
extern short func_0012C508(int, int);

extern int func_0012C878(void *, int);

extern void func_0012C230(void *, int *, int *, int, int, int, int, int);

extern void func_0012C008(int *, int, int, int, int);

extern void func_0012C380(char *, unsigned int);

extern int r1_D_00132F70[];

extern void func_0012C3B0(void *);

extern void r1_func_0012BCC8(int);

/* rac1-decomp src/core/00125630.c: func_00128410 */
/* motionVector (libmpeg.a:mpc.o): ISO/IEC 13818-2 7.6.3.1 motion_vector(),
 * hardware-VLC variant of mpeg2decode's motion.c. func_0012C508(s, 2) is
 * Get_motion_code (IPU VLC table 2); func_0012B3C0 is Get_dmvector (table
 * 3, already matched in this file). func_0012C008 is decode_motion_vector.
 */
/* Reads one motion vector (horizontal and vertical parts) from the video stream. */
void func_0012C230(void *decoderPtr, int *PMV, int *dmvector, int h_r_size,
                    int v_r_size, int dmv, int mvscale, int full_pel_vector) {
    char *s = (char *)decoderPtr;
    int motion_code;
    int motion_residual;

    motion_code = ReadIpuVlcCode((int)s, 2);
    motion_residual = (h_r_size != 0 && motion_code != 0) ? ReadMpegBits(s, h_r_size) : 0;
    DecodeMpegMotionVector(PMV, h_r_size, motion_code, motion_residual, full_pel_vector);
    if (dmv) {
        dmvector[0] = ReadMpegDualPrimeValue((int)s);
    }

    motion_code = ReadIpuVlcCode((int)s, 2);
    motion_residual = (v_r_size != 0 && motion_code != 0) ? ReadMpegBits(s, v_r_size) : 0;
    if (mvscale) {
        PMV[1] >>= 1;
    }
    DecodeMpegMotionVector(PMV + 1, v_r_size, motion_code, motion_residual, full_pel_vector);
    if (mvscale) {
        PMV[1] <<= 1;
    }
    if (dmv) {
        dmvector[1] = ReadMpegDualPrimeValue((int)s);
    }
}

/* rac1-decomp src/core/00125630.c: func_00128560 */
/* Sends a command to the video decoder chip and remembers how many bits it will use. */
void func_0012C380(char *decoderPtr, unsigned int command) {
    IPU_CMD = command;
    *(int *)(decoderPtr + 0x818) = r1_D_00132F70[command >> 28];
}

/* rac1-decomp src/core/00125630.c: func_00128590 */
/* Spins until the VIF1 DMA channel (D_CHCR 0x10002010) reports idle,
   nudging the IOP via r1_func_0012BCC8 every 5001 spins so a stalled
   stream cannot deadlock. Same wait loop documented on func_0012C680. */
void func_0012C3B0(void *decoderPtr) {
    int counter = 0;

    while ((((int)IPU_CTRL) & 0x80004000) == 0x80000000) {
        if (counter++ >= 0x1389) {
            r1_func_0012BCC8(*(int *)((char *)decoderPtr + 0x858));
            counter = 0;
        }
    }
}

/* rac1-decomp src/core/00125630.c: func_00128638 */
/*
 * IPU wait: the same spin as func_0012C3B0, while IPU_CMD (0x10002000,
 * read as a 64-bit word) is negative (busy) and IPU_CTRL (0x10002010)
 * bit 0x4000 is clear, kicking r1_func_0012BCC8 every 5001 spins. Returns
 * the raw 64-bit IPU_CMD word; func_0012C680 and func_0012C788 narrow it
 * with dsll32/dsra32, so the return type is `long`.
 *
 * Exact under both compilers once BOTH MMIO reads are spelled inline in
 * the condition: both addresses are then loop invariants that loop.c
 * hoists into $17/$16 as retail has them. The old note's
 * `volatile long *chcr` local made the compiler use the constant as an
 * absolute `ld` address instead (160 against 176 bytes).
 */
long func_0012C458(void *decoderPtr) {
    long v;
    int counter = 0;
    while ((v = ((long)IPU_CMD64)) < 0 && (((int)IPU_CTRL) & 0x4000) == 0) {
        if (counter++ >= 0x1389) {
            r1_func_0012BCC8(*(int *)((char *)decoderPtr + 0x858));
            counter = 0;
        }
    }
    return v;
}
