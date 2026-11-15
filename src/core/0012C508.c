#include "common.h"
#include "structs.h"

/* func_0012C508 returns a short: its epilogue sign-extends $v0. */
extern short mpeg_read_ipu_vlc_code(int, int);

extern int r1_D_00132F70[];

extern void r1_func_0012BCC8(int);

typedef struct {
    unsigned char pad0[0x11C];
    int error_flag;
    unsigned char pad120[0x6F8];
    int cmd_info;
    unsigned char pad81C[0x1C];
    int bit_window;
    int bits_left;
    unsigned char pad840[0x18];
    void *cbData;
} MpegVdec;

extern int mpeg_peek_bits(void *, int);

extern void mpeg_skip_bits(void *, int);

extern int mpeg_read_bits(void *, int);

/* rac1-decomp src/core/00125630.c: func_001286E8 */
/* _ipuVdec (libmpeg). Adapted from Lombyte (GPL-3.0) for PAL. */
/* Reads one code from the video stream using one of the chip lookup tables, and sets the error flag if nothing matched. */
short mpeg_read_ipu_vlc_code(int decoder_addr, int tbl) {
    MpegVdec *d = (MpegVdec *)decoder_addr;
    int i;
    int j;
    unsigned int cmd;
    long r;
    long top;
    unsigned int bp;

    i = 0;
    j = 0;
    while ((IPU_CTRL & 0x80004000) == 0x80000000) {
        if (j++ > 5000) {
            r1_func_0012BCC8((int)d->cbData);
            j = 0;
        }
    }
    cmd = (tbl << 26) | 0x30000000;
    IPU_CMD = cmd;
    d->cmd_info = r1_D_00132F70[(int)cmd >> 28];
    r = IPU_CMD64;
    while (r < 0) {
        if (i++ > 5000) {
            r1_func_0012BCC8((int)d->cbData);
            i = 0;
        }
        r = IPU_CMD64;
    }
    bp = IPU_BP;
    top = IPU_TOP;
    d->bit_window = top;
    if (top < 0) {
        d->bits_left = -(bp & 0x1F) & 0x1F;
    } else {
        d->bits_left = 32;
    }
    d->error_flag = (int)r == 0;
    return (short)r;
}
extern int mpeg_peek_bits(void *arg, int count);
extern int mpeg_peek_bits(void *, int);
extern int r1_D_00132F70[];
extern void r1_func_0012BCC8(int);
extern long r1_func_00128638(void *arg0);

/* rac1-decomp src/core/00125630.c: func_0012C680 */
/* _peepBit: return the next count bits of the IPU bit stream without
   consuming them, refilling the 32-bit window from the IPU (FDEC) when
   it runs short and nudging the callback while the IPU stays busy.
   Adapted from Lombyte's project (GPL-3.0) for PAL. */
int mpeg_peek_bits(void *decoder_ptr, int count) {
    char *ctx = decoder_ptr;
    int counter;

    if (*(int *)(ctx + 0x818) == 0 && *(int *)(ctx + 0x83C) >= count) {
        goto done;
    }
    counter = 0;
    if ((IPU_CTRL & 0x80004000) == 0x80000000) {
        do {
            if (counter++ >= 0x1389) {
                r1_func_0012BCC8(*(void **)(ctx + 0x858));
                counter = 0;
            }
        } while ((IPU_CTRL & 0x80004000) == 0x80000000);
    }
    IPU_CMD = 0x40000000;
    *(int *)(ctx + 0x818) = r1_D_00132F70[4];
    *(int *)(ctx + 0x838) = r1_func_00128638(ctx);
    *(int *)(ctx + 0x83C) = 0x20;
done:
    return (unsigned int)*(int *)(ctx + 0x838) >> (0x20 - count);
}

extern void mpeg_skip_bits(void *arg0, int arg1);
extern long r1_func_00128638();




/* rac1-decomp src/core/00125630.c: func_00128968 */
/*
 * IPU command send: r1_func_00128590's wait (IPU_CTRL & 0x80004000 ==
 * 0x80000000, a r1_func_0012BCC8 kick every 5001 spins) inlined, then
 * cmd = arg1 | 0x40000000 to IPU_CMD, s+0x818 = r1_D_00132F70[cmd >> 28]
 * (r1_func_00128560 inlined), s+0x838 = the narrowed r1_func_00128638 result,
 * s+0x83C = 0x20.
 *
 * Written plainly it is exact under 2.9-ee, which rematerialises the
 * MMIO constants inside the loop and keeps only %hi(r1_D_00132F70) in $18,
 * like retail; 2.95.3 hoists them into saved registers (SIZE 252/240).
 * The stores go in source order 0x838 then 0x83C.
 */
/* Skips a given number of bits in the video stream. */
void mpeg_skip_bits(void *decoder_ptr, int bit_count) {
    int counter = 0;
    unsigned int cmd;

    while ((((int)IPU_CTRL) & 0x80004000) == 0x80000000) {
        if (counter++ >= 0x1389) {
            r1_func_0012BCC8(*(int *)((char *)decoder_ptr + 0x858));
            counter = 0;
        }
    }
    cmd = bit_count | 0x40000000;
    IPU_CMD = cmd;
    *(int *)((char *)decoder_ptr + 0x818) = r1_D_00132F70[cmd >> 28];
    *(int *)((char *)decoder_ptr + 0x838) = r1_func_00128638(decoder_ptr);
    *(int *)((char *)decoder_ptr + 0x83C) = 0x20;
}

extern int mpeg_read_bits(void *arg0, int n);




/* rac1-decomp src/core/00125630.c: func_00128A58 */
/* _nextBit (libmpeg.a:mpc.o), Get_Bits: waits for the IPU, refills the
 * bit cache when it is empty or short, returns the top n bits and tells
 * the IPU to consume them. The r1_D_00132F70 index needs its own local,
 * computed before the command store, or the allocator swaps $v1 and $a0.
 */
/* Reads the given number of bits from the video stream and moves past them. */
int mpeg_read_bits(void *decoder_ptr, int n) {
    char *s = (char *)decoder_ptr;
    int counter = 0;
    unsigned int cmd;
    unsigned int idx;
    unsigned int oldBits;
    unsigned int result;

    while ((((int)IPU_CTRL) & 0x80004000) == 0x80000000) {
        if (counter++ >= 0x1389) {
            r1_func_0012BCC8(*(int *)(s + 0x858));
            counter = 0;
        }
    }

    if (*(int *)(s + 0x818) != 0 || *(int *)(s + 0x83C) < n) {
        IPU_CMD = 0x40000000;
        *(int *)(s + 0x818) = r1_D_00132F70[4];
        *(int *)(s + 0x838) = r1_func_00128638(s);
    }

    *(int *)(s + 0x83C) = 0x20;
    oldBits = *(unsigned int *)(s + 0x838);
    cmd = n | 0x40000000;
    idx = cmd >> 28;
    IPU_CMD = cmd;
    result = oldBits >> (0x20 - n);
    *(int *)(s + 0x818) = r1_D_00132F70[idx];
    *(int *)(s + 0x838) = r1_func_00128638(s);
    return result;
}

