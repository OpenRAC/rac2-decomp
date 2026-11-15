#include "common.h"
#include "structs.h"

extern void mpeg_report_error(void *, void *);

extern void mpeg_print_error(void *);

extern void mpeg_restore_counter(void *);
extern unsigned int mpeg_alloc_aligned(void *, void *, unsigned int, unsigned int);
/* Fills in nine DMA addresses that point at the three picture buffers and their halves. */
extern void mpeg_fill_buffer_addresses(unsigned int *, unsigned int *, unsigned int *, unsigned int *,
                          unsigned int *, unsigned int *, unsigned int *, unsigned int *,
                          unsigned int *, int, int, int, int, int);

/* rac1-decomp src/core/0012AC80.bufferC: func_0012C468 */
/* Reports bufferA video error through the registered callback, or prints it if there is none. */
void mpeg_report_error(void *mpeg, void *message) {
    char *bytes = (char *)mpeg;
    void *callbackOwner = *(void **)(bytes + 0x858);
    /* the mpeg null test is retail's, after it has already dereferenced
       mpeg -- one of the "dead-looking guards" that must be written out */
    if (callbackOwner != 0 && mpeg != 0 && *(int *)(bytes + 0xC) != 0) {
        int event[4];
        event[0] = 0;
        event[1] = (int)message;
        mpeg_dispatch_callback(callbackOwner, event);
    } else {
        mpeg_print_error(message);
    }
}

/* rac1-decomp src/core/0012AC80.c: func_0012C4C0 */
/* Store the two sizes and their 16-pixel macroblock counts. (An old note
   here recorded 4/32 with the 0x4/0x8 stores swapped; the function is
   exact under both compilers now.) */
/* Stores a picture width and height and the same sizes counted in 16-pixel blocks. */
int mpeg_set_picture_size(void *sizeInfo, int width, int height) {
    char *bytes = (char *)sizeInfo;
    *(int *)(bytes + 0x4) = width;
    *(int *)(bytes + 0x8) = height;
    *(int *)(bytes + 0xC) = width >> 4;
    *(int *)(bytes + 0x10) = height >> 4;
    return 1;
}

extern void r1_func_0012C468();

extern void r1_func_0012C990();

extern char r1_D_00153BE8[];

extern void r1_func_0012C608(void *);

extern void r1_func_0012C990(void *, int, int);

extern int r1_func_00128A58(void *, int);

extern void r1_func_00128E68(void *);

extern void r1_func_00128560(void *, unsigned int);

extern char r1_D_001330C0[];

extern void r1_func_0012C468(void *, void *);

extern void r1_func_0012C468(void *, void *);

extern void r1_func_00128590(void *);

extern char r1_D_00133100[];

/* rac1-decomp src/core/0012AC80.c: func_0012C4E0 */
/*
 * _sequenceHeader (libmpeg.a:init.o): ISO/IEC 13818-2 6.2.2.1
 * sequence_header(), hardware-VLC variant matching mpeg2decode's
 * gethdr.c almost line for line but reading combined bitfields in one
 * Get_Bits (r1_func_00128A58) call each: a 32-bit fetch for
 * horizontal_size/vertical_size/aspect_ratio_information/frame_rate_code
 * (only the two sizes are kept, at +0x124/+0x128; a vertical_size
 * reading >= 0xAF1 is reported through r1_func_0012C468) and a 30-bit fetch
 * for bit_rate_value/marker_bit/vbv_buffer_size/constrained_parameters_
 * flag (bit_rate_value kept at +0x134, vbv_buffer_size at +0x138).
 * load_intra/non_intra_quantizer_matrix (+0x840/+0x844) gate the IPU
 * matrix load (r1_func_00128590/r1_func_00128560) or, when clear, _setDefaultQM
 * (r1_func_0012C990) with the reference decoder's default table. Ends with
 * extensionAndUserData (r1_func_00128E68) and a tail call into _initSeq
 * (r1_func_0012C608) with the object read back from +0x858.
 */
/* Reads the video sequence header: picture size, bit rate and quantizer tables. */
void mpeg_read_sequence_header(void *decoder) {
    char *bytes = (char *)decoder;
    unsigned int bits;
    int height;
    unsigned int hasMatrix;

    *(unsigned int *)(bytes + 0xD4) = 0;

    bits = r1_func_00128A58(bytes, 0x20);
    *(unsigned int *)(bytes + 0x124) = bits >> 20;
    height = (bits >> 8) & 0xFFF;
    *(unsigned int *)(bytes + 0x128) = height;
    if (height >= 0xAF1) {
        r1_func_0012C468(bytes, r1_D_00153BE8);
    }

    bits = r1_func_00128A58(bytes, 0x1E);
    *(unsigned int *)(bytes + 0x134) = bits >> 12;
    *(unsigned int *)(bytes + 0x138) = (bits >> 1) & 0x3FF;

    hasMatrix = r1_func_00128A58(bytes, 1);
    *(unsigned int *)(bytes + 0x840) = hasMatrix;
    if (hasMatrix != 0) {
        r1_func_00128590(bytes);
        r1_func_00128560(bytes, 0x50000000);
        r1_func_00128590(bytes);
    } else {
        r1_func_0012C990(bytes, 0x50000000, (int)r1_D_001330C0);
    }

    hasMatrix = r1_func_00128A58(bytes, 1);
    *(unsigned int *)(bytes + 0x844) = hasMatrix;
    if (hasMatrix != 0) {
        r1_func_00128590(bytes);
        r1_func_00128560(bytes, 0x58000000);
        r1_func_00128590(bytes);
    } else {
        r1_func_0012C990(bytes, 0x58000000, (int)r1_D_00133100);
    }

    r1_func_00128E68(bytes);
    r1_func_0012C608(*(void **)(bytes + 0x858));
}

/* rac1-decomp src/core/0012AC80.c: mpeg_init_seq (func_0012C608) */
/* Works out the picture size in blocks and sets up the picture buffers when the size changes. */
void mpeg_init_seq(void *sizeInfo) {
    int *sizes = (int *)sizeInfo;
    char *decoder = *(char **)((char *)sizeInfo + 0x40);
    int started = *(int *)(decoder + 0x848);
    int blockRows, widthPixels, heightPixels;
    unsigned int bufferSize, rowSize;
    unsigned int *desc0, *desc1, *desc2, *desc3, *desc4, *desc5, *desc6, *desc7, *desc8;

    if (started == 0) {
        *(int *)(decoder + 0x174) = 3;
        *(int *)(decoder + 0x13C) = 1;
        *(int *)(decoder + 0x140) = 1;
        *(int *)(decoder + 0x188) = 1;
        *(int *)(decoder + 0x17C) = 1;
        *(int *)(decoder + 0x144) = 5;
    }
    *(int *)(decoder + 0x12C) = (*(int *)(decoder + 0x124) + 0xF) >> 4;
    if (started != 0 && *(int *)(decoder + 0x13C) == 0)
        blockRows = ((*(int *)(decoder + 0x128) + 0x1F) >> 5) << 1;
    else
        blockRows = (*(int *)(decoder + 0x128) + 0xF) >> 4;
    *(int *)(decoder + 0x130) = blockRows;
    heightPixels = blockRows << 4;
    widthPixels = *(int *)(decoder + 0x12C) << 4;
    {
    unsigned int *outDesc;
    if (widthPixels != sizes[0]) {
        outDesc = (unsigned int *)(decoder + 0x528);
    } else {
        if (heightPixels == sizes[1])
            return;
        outDesc = (unsigned int *)(decoder + 0x528);
    }
    sizes[0] = widthPixels;
    sizes[1] = heightPixels;
    if ((widthPixels & 0xF) && (widthPixels & 0xE))
        outDesc = desc8;
    desc8 = outDesc;
    rowSize = heightPixels * 0x180;
    desc0 = (unsigned int *)(decoder + 0x1E8);
    desc1 = (unsigned int *)(decoder + 0x250);
    desc2 = (unsigned int *)(decoder + 0x2B8);
    desc3 = (unsigned int *)(decoder + 0x320);
    desc4 = (unsigned int *)(decoder + 0x388);
    desc5 = (unsigned int *)(decoder + 0x3F0);
    desc6 = (unsigned int *)(decoder + 0x458);
    desc7 = (unsigned int *)(decoder + 0x4C0);
    bufferSize = (widthPixels * rowSize) >> 8;
    mpeg_restore_counter(decoder + 0x108);
    *(unsigned int *)(decoder + 0xFC) = mpeg_alloc_aligned(decoder, decoder + 0x108, bufferSize, 0x40);
    *(unsigned int *)(decoder + 0x100) = mpeg_alloc_aligned(decoder, decoder + 0x108, bufferSize, 0x40);
    *(unsigned int *)(decoder + 0x104) = mpeg_alloc_aligned(decoder, decoder + 0x108, bufferSize, 0x40);
    mpeg_fill_buffer_addresses(desc0, desc1, desc2,
                  desc3, desc4, desc5,
                  desc6, desc7, desc8,
                  *(int *)(decoder + 0xFC), *(int *)(decoder + 0x100), *(int *)(decoder + 0x104), widthPixels, heightPixels);
    mpeg_set_picture_size(desc0, widthPixels, heightPixels);
    mpeg_set_picture_size(desc1, widthPixels, heightPixels);
    mpeg_set_picture_size(desc2, widthPixels, heightPixels);
    mpeg_set_picture_size(desc3, widthPixels, heightPixels >> 1);
    mpeg_set_picture_size(desc4, widthPixels, heightPixels >> 1);
    mpeg_set_picture_size(desc5, widthPixels, heightPixels >> 1);
    mpeg_set_picture_size(desc6, widthPixels, heightPixels >> 1);
    mpeg_set_picture_size(desc7, widthPixels, heightPixels >> 1);
    mpeg_set_picture_size(desc8, widthPixels, heightPixels >> 1);
    }
}



/* rac1-decomp src/core/0012AC80.c: func_001306D0 */
void mpeg_fill_buffer_addresses(unsigned int *o0, unsigned int *o1, unsigned int *o2, unsigned int *o3,
                   unsigned int *o4, unsigned int *o5, unsigned int *o6, unsigned int *o7,
                   unsigned int *o8, int a, int b, int c, int w, int h) {
    unsigned int x = (a & 0xFFFFFFF) | 0x20000000;
    unsigned int y = (b & 0xFFFFFFF) | 0x20000000;
    unsigned int z = (c & 0xFFFFFFF) | 0x20000000;
    int q = (w * h) / 512;
    int s6, s7, s8;
    s6 = q * 384; s6 += a;
    s7 = q * 384; s7 += b;
    s8 = q * 384; s8 += c;
    *o0 = x; *o1 = y; *o2 = z; *o3 = x; *o4 = y; *o5 = z;
    *o6 = (s6 & 0xFFFFFFF) | 0x20000000;
    *o7 = (s7 & 0xFFFFFFF) | 0x20000000;
    *o8 = (s8 & 0xFFFFFFF) | 0x20000000;
}

extern int r1_func_0011D960(void);
extern void r1_func_0011D9A8(void);
extern void r1_func_00128590(void *);
extern void r1_func_00128560(void *, unsigned int);
extern void mpeg_load_default_quant_matrix(void *, int, int);

/* rac1-decomp src/core/0012AC80.c: func_001307B0 */
/* _setDefaultQM: tell the callback (type 2) that the default quantiser
   matrix load starts, then with the IPU idle and reset, DMA the matrix
   at addr to IPU_TO (tag 4 qwords, chcr 0x101) with interrupts held
   off, send command cmd and wait, and report type 3. Adapted from
   Lombyte's project (GPL-3.0) for PAL. */
void mpeg_load_default_quant_matrix(void *decoder, int cmd, int addr) {
    char *bytes = decoder;
    int event[8];
    int interruptsWereOn;

    event[0] = 2;
    r1_func_0012BC78(*(void **)(bytes + 0x858), event);
    r1_func_00128590(bytes);
    IPU_CMD = 0;
    r1_func_00128590(bytes);
    interruptsWereOn = r1_func_0011D960();
    D4_MADR = addr & 0x0FFFFFFF;
    D4_QWC = 4;
    D4_CHCR = 0x101;
    if (interruptsWereOn != 0) {
        r1_func_0011D9A8();
    }
    r1_func_00128560(bytes, cmd);
    r1_func_00128590(bytes);
    event[0] = 3;
    r1_func_0012BC78(*(void **)(bytes + 0x858), event);
}
