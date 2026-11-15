#include "common.h"
#include "structs.h"

extern int r1_func_0012AAA8(void *, int);

extern int r1_func_0012AB60(void *arg0, int arg1);

extern int mpeg_skip_system_header();

extern void r1_func_0012C468_a(void *, void *) __asm__("func_00130288");

extern void r1_func_0012ABB0(void *arg0);

extern void r1_func_0012ABF8(void *arg0, int n);

extern char r1_D_00153AC8[];

extern char r1_D_00153AD8[];

struct PES_BS {
    unsigned char pad_0[0x18];
    long stamp;
};

struct PES_HDR {
    long unk0;
    int unk8;
    int unkC;
    long unk10;
    long unk18;
    int unk20;
    int unk24;
    int unk28;
};

struct PES_TBL {
    unsigned char v[16];
} __attribute__((packed));

extern void mpeg_report_error(void *, void *);

extern int r1_func_0011D960(void);

extern void r1_func_0011D9A8(void);

extern void r1_func_0012D068(void);

extern void r1_func_001153FC(void *, int, int);

/* memset returns its pointer: the unused return moves the first temporary
   after the call from $v0 to $v1. */
extern void *r1_func_001153FC_p(void *, int, unsigned int) __asm__("r1_func_001153FC");

extern char r1_D_00153B10[];

extern void mpeg_init_counters(void *, int, int);

extern unsigned int mpeg_alloc_aligned(void *, char *, unsigned int, unsigned int);

extern void mpeg_set_scratchpad_buffers(void *);

extern void sceMpegReset(void *);

extern int mpeg_clear_buffer_flags(void *);

extern void mpeg_copy_counter(void *);

extern void r1_func_0012CC70(void);

extern void r1_func_0012CC80(void);

/* rac1-decomp src/core/0012AC80.c: func_0012B250 */
/* Skips the system header of a movie stream. Returns 1. */
int mpeg_skip_system_header(void *stream) {
    r1_func_0012AB60(stream, 0x38);
    r1_func_0012AB60(stream, 0x28);
    while (r1_func_0012AAA8(stream, 1) == 1) {
        r1_func_0012AB60(stream, 0x18);
    }
    return 1;
}

/* rac1-decomp src/core/0012AC80.c: func_0012B2C0 */
/* Parse one MPEG-2 PES packet header from the bit stream into hdr (libmpeg _PES_packet).
   Adapted from Lombyte (GPL-3.0) for PAL: src/sdk/library/_PES_packet.c, _PES_packet. */
/* Reads one packet header of a movie stream and records its type, length and timestamps. */
int mpeg_read_pes_packet_header(int mpeg, struct PES_BS *bs, struct PES_HDR *hdr) {
    struct PES_TBL tbl;
    int mpegCtx;
    int flag1;
    int len;         /* PES_header_data_length */
    int base;        /* (int)bs->stamp, captured before the header fields */
    long now;         /* the same stamp, re-read at the sync point */
    int v7;          /* PTS_DTS_flags */
    int v8;          /* 4-bit length, indexes tbl */
    int v5;          /* PES_extension_flag */

    mpegCtx = mpeg;
    hdr->unk28 = (int)bs->stamp;
    tbl = *(struct PES_TBL *)r1_D_00153AC8;
    r1_func_0012AB60(bs, 0x18);
    hdr->unk0 = (long)r1_func_0012AB60(bs, 8) << 0x20;
    hdr->unk8 = r1_func_0012AB60(bs, 0x10);
    hdr->unk18 = -1;
    hdr->unk10 = -1;
    if (hdr->unk0 != ((unsigned long)0xBC00 << 0x18) &&
        hdr->unk0 != ((unsigned long)0xBE00 << 0x18) &&
        hdr->unk0 != ((unsigned long)0xBF00 << 0x18) &&
        hdr->unk0 != ((unsigned long)0xF000 << 0x18) &&
        hdr->unk0 != ((unsigned long)0xF100 << 0x18) &&
        hdr->unk0 != ((unsigned long)0xFF00 << 0x18) &&
        hdr->unk0 != ((unsigned long)0xF200 << 0x18) &&
        hdr->unk0 != ((unsigned long)0xF800 << 0x18)) {
        r1_func_0012AB60(bs, 2);
        hdr->unkC = r1_func_0012AB60(bs, 2);
        r1_func_0012AB60(bs, 4);
        v7 = r1_func_0012AB60(bs, 2);
        flag1 = r1_func_0012AB60(bs, 1);
        v8 = r1_func_0012AB60(bs, 4);
        v5 = r1_func_0012AB60(bs, 1);
        len = r1_func_0012AB60(bs, 8);
        base = bs->stamp;
        if (v7 & 2) {
            unsigned int a, b, c;
            r1_func_0012AB60(bs, 4);
            a = r1_func_0012AB60(bs, 3);
            r1_func_0012ABB0(bs);
            b = r1_func_0012AB60(bs, 0xF);
            r1_func_0012ABB0(bs);
            c = r1_func_0012AB60(bs, 0xF);
            r1_func_0012ABB0(bs);
            hdr->unk10 = ((long)((a >> 2) & 1) << 0x20) | (long)(unsigned int)(a << 30 | b << 15 | c);
        }
        if (v7 == 3) {
            unsigned int a, b, c;
            r1_func_0012AB60(bs, 4);
            a = r1_func_0012AB60(bs, 3);
            r1_func_0012ABB0(bs);
            b = r1_func_0012AB60(bs, 0xF);
            r1_func_0012ABB0(bs);
            c = r1_func_0012AB60(bs, 0xF);
            r1_func_0012ABB0(bs);
            hdr->unk18 = ((long)((a >> 2) & 1) << 0x20) | (long)(unsigned int)(a << 30 | b << 15 | c);
        }
        if (flag1 == 1) {
            r1_func_0012AB60(bs, 0x30);
        }
        if (v8 != 0) {
            r1_func_0012AB60(bs, tbl.v[v8]);
        }
        if (v5 == 1) {
            int a1;
            int a2;
            int a3;
            int a4;
            int a5;
            a1 = r1_func_0012AB60(bs, 1);
            a2 = r1_func_0012AB60(bs, 1);
            a3 = r1_func_0012AB60(bs, 1);
            a4 = r1_func_0012AB60(bs, 1);
            r1_func_0012AB60(bs, 3);
            a5 = r1_func_0012AB60(bs, 1);
            if (a1 == v5) {
                r1_func_0012AB60(bs, 0x30);
                r1_func_0012AB60(bs, 0x30);
                r1_func_0012AB60(bs, 0x20);
            }
            if (a2 == v5) {
                r1_func_0012C468_a(mpegCtx, r1_D_00153AD8);
                return 0;
            }
            if (a3 == v5) {
                r1_func_0012AB60(bs, 0x10);
            }
            if (a4 == v5) {
                r1_func_0012AB60(bs, 0x10);
            }
            if (a5 == v5) {
                unsigned int i;
                unsigned int n;
                r1_func_0012ABB0(bs);
                n = r1_func_0012AB60(bs, 7);
                for (i = 0; i < n; i++) {
                    r1_func_0012AB60(bs, 8);
                }
            }
        }
        now = bs->stamp;
        {
        int delta = len - (int)((now - base) >> 3);
        if (delta != 0) {
            r1_func_0012ABF8(bs, delta);
        }
        }
        {
        int n = hdr->unk8 - len;
        int m;
        hdr->unk24 = n - 3;
        hdr->unk20 = (int)bs->stamp;
        if (hdr->unk0 == ((unsigned long)0xBD00 << 0x18)) {
            hdr->unk0 |= (unsigned long)(unsigned int)r1_func_0012AB60(bs, 0x20);
            m = n - 7;
        } else {
            m = n - 3;
        }
        if (m != 0) {
            r1_func_0012ABF8(bs, m);
        }
        }
    } else if (hdr->unk0 == ((unsigned long)0xBC00 << 0x18) ||
               hdr->unk0 == ((unsigned long)0xBF00 << 0x18) ||
               hdr->unk0 == ((unsigned long)0xF000 << 0x18) ||
               hdr->unk0 == ((unsigned long)0xF100 << 0x18) ||
               hdr->unk0 == ((unsigned long)0xFF00 << 0x18) ||
               hdr->unk0 == ((unsigned long)0xF200 << 0x18) ||
               hdr->unk0 == ((unsigned long)0xF800 << 0x18)) {
        int n = hdr->unk8;
        if (hdr->unk0 == ((unsigned long)0xBF00 << 0x18)) {
            n -= 4;
            hdr->unk0 |= (unsigned long)(unsigned int)r1_func_0012AB60(bs, 0x20);
        }
        if (n != 0) {
            r1_func_0012ABF8(bs, n);
        }
    } else if (hdr->unk0 == ((unsigned long)0xBE00 << 0x18)) {
        if (hdr->unk8 != 0) {
            r1_func_0012ABF8(bs, hdr->unk8);
        }
    }
    return 1;
}

/* rac1-decomp src/core/0012AC80.c: func_0012B870 */
/*
 * sceMpegInit (libmpeg.a:mpeg.o): one-time IOP/EE SIF hardware bring-up.
 * r1_func_0011D960 presumably queries the DMA/SIF state, gating whether
 * r1_func_0011D9A8 (a kick) runs; the SIF flag register at 0x1000F590 is set
 * then cleared (bit 0x10000, re-reading 0x1000F520 fresh each time), two
 * DMA channel control registers (0x1000B000/0x1000B400) have bit 0x100
 * masked off, and two more (0x1000B020/0x1000B420) are zeroed before the
 * tail call into r1_func_0012D068.
 */
/* Starts up the movie player by resetting its DMA channels. */
void sceMpegInit(void) {
    int intrState = r1_func_0011D960();

    D_ENABLEW =
        D_ENABLER | 0x10000;
    D3_CHCR &= ~0x100;
    D4_CHCR &= ~0x100;
    D_ENABLEW =
        D_ENABLER & ~0x10000;

    if (intrState != 0) {
        r1_func_0011D9A8();
    }

    D3_QWC = 0;
    D4_QWC = 0;
    r1_func_0012D068();
}

/* rac1-decomp src/core/0012AC80.c: func_0012B918 */
/*
 * sceMpegCreate (libmpeg.a:mpeg.o): clear the caller's work area
 * (memset), align it up to 4 and carve the decoder object out of it. Less
 * than 0x10C0 usable bytes is reported through func_00130288 and returns
 * 0. Otherwise: wrapper->0x40 = the object; a heap descriptor at +0x108
 * (func_0012FB48) covers the space past 0x10C0; the fields are reset
 * (-1 "unset" sentinels or 0); 0x600 bytes are allocated from that heap
 * (func_0012FB80) into +0x44; handler slots +0x1C/+0x24 get the two
 * callback trampolines (r1_func_0012CC70/r1_func_0012CC80); func_00130118,
 * sceMpegReset (func_0012F9C8) and func_0012FA18 run; the three 0x10-byte
 * entries at +0x1B8 get pointers into nine 0x68-byte regions; and
 * func_0012FB60 closes the heap. Success falls off the end (retail
 * leaves 0x70003600 in $v0).
 *
 * The trampoline store at +0x24 is written before the allocation so it
 * fills that call's delay slot, and the last four stores are in the
 * order that schedules as retail's.
 */
/* Sets up a movie player in a work area. Returns 0 if the area is too small. */
int sceMpegCreate(void *mpeg, void *workarea, int size) {
    char *mpegPtr = (char *)mpeg;
    unsigned int workAddr = (unsigned int)workarea;
    char *decoder;
    char *heap;
    unsigned int availBytes;
    int neg1;

    r1_func_001153FC_p(workarea, 0, size);

    decoder = (char *)(((workAddr + 3) >> 2) << 2);
    availBytes = (unsigned int)size - ((unsigned int)decoder - workAddr);

    if (availBytes < 0x10C0) {
        mpeg_report_error(decoder, r1_D_00153B10);
        return 0;
    }

    heap = decoder + 0x108;
    *(int *)(mpegPtr + 0x40) = (int)decoder;
    availBytes -= 0x10C0;
    mpeg_init_counters(heap, (int)(decoder + 0x10C0), (int)availBytes);
    neg1 = -1;

    *(int *)(mpegPtr + 0x0) = 0;
    *(int *)(mpegPtr + 0x4) = 0;
    *(int *)(mpegPtr + 0x8) = 0;
    *(long *)(mpegPtr + 0x10) = -1;
    *(long *)(mpegPtr + 0x18) = -1;
    *(long *)(mpegPtr + 0x20) = 0;
    *(long *)(mpegPtr + 0x28) = -1;
    *(long *)(mpegPtr + 0x30) = -1;
    *(long *)(mpegPtr + 0x38) = 0;

    *(int *)(decoder + 0xB4) = 0;
    *(int *)(decoder + 0xB8) = 0;
    *(int *)(decoder + 0xBC) = 0;
    *(int *)(decoder + 0xC0) = 0;
    *(int *)(decoder + 0xC4) = 0;
    *(int *)(decoder + 0xC8) = 0;
    *(int *)(decoder + 0xCC) = 0;
    *(int *)(decoder + 0xD0) = 0;
    *(int *)(decoder + 0xD4) = 0;
    *(int *)(decoder + 0xD8) = 0;
    *(int *)(decoder + 0xDC) = 0;
    *(int *)(decoder + 0xE0) = 0;
    *(int *)(decoder + 0xE4) = 0;
    *(int *)(decoder + 0xE8) = 0;
    *(int *)(decoder + 0xF8) = 0;
    *(int *)(decoder + 0xC) = 0;
    *(int *)(decoder + 0x14) = 0;
    *(int *)(decoder + 0x2C) = 0;
    *(int *)(decoder + 0x34) = 0;
    *(int *)(decoder + 0x3C) = 0;
    *(long *)(decoder + 0xF0) = -1;
    *(int *)(decoder + 0x1C) = (int)r1_func_0012CC70;
    *(int *)(decoder + 0x24) = (int)r1_func_0012CC80;

    *(int *)(decoder + 0x44) = (int)mpeg_alloc_aligned(decoder, heap, 0x600, 8);

    *(int *)(decoder + 0x48) = 0;
    *(int *)(decoder + 0xFC) = 0;
    *(int *)(decoder + 0x100) = 0;
    *(int *)(decoder + 0x104) = 0;
    *(int *)(decoder + 0x70) = 0;
    *(long *)(decoder + 0x78) = 0;
    *(int *)(decoder + 0x80) = neg1;
    *(long *)(decoder + 0x88) = 0;
    *(int *)(decoder + 0x90) = 0;
    *(int *)(decoder + 0xAC) = 0;
    *(int *)(decoder + 0x94) = neg1;
    *(int *)(decoder + 0x98) = neg1;
    *(int *)(decoder + 0x9C) = neg1;
    *(int *)(decoder + 0x858) = (int)mpegPtr;
    *(int *)(decoder + 0xB0) = 1;

    mpeg_set_scratchpad_buffers(decoder);
    sceMpegReset(mpegPtr);
    mpeg_clear_buffer_flags(mpegPtr);

    *(int *)(decoder + 0x1B8) = (int)(decoder + 0x1E8);
    *(int *)(decoder + 0x1BC) = (int)(decoder + 0x250);
    *(int *)(decoder + 0x1C4) = (int)(decoder + 0x2B8);
    *(int *)(decoder + 0x1C8) = (int)(decoder + 0x320);
    *(int *)(decoder + 0x1CC) = (int)(decoder + 0x388);
    *(int *)(decoder + 0x1D4) = (int)(decoder + 0x3F0);
    *(int *)(decoder + 0x1D8) = (int)(decoder + 0x458);
    *(int *)(decoder + 0x1DC) = (int)(decoder + 0x4C0);
    *(int *)(decoder + 0x1E4) = (int)(decoder + 0x528);

    mpeg_copy_counter(heap);

    *(int *)(decoder + 0x850) = neg1;
    *(int *)(decoder + 0x84C) = 0;
    *(int *)(decoder + 0x81C) = 0x70003600;
    *(int *)(decoder + 0x854) = 0;
}
