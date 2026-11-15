#include "common.h"
#include "structs.h"

extern void mpeg_report_error(void *, void *);

extern unsigned int mpeg_alloc_aligned(void *, char *, unsigned int, unsigned int);

extern char r1_D_00153B38[];

extern void mpeg_send_event_one(int);

extern int r1_func_00129690(void *, int);

extern int r1_func_00129530(void *);

extern void r1_func_00129600(void *, int, int);

extern int mpeg_decode_or_skip_frame(void *, int, int);

extern int r1_func_00129530();

extern int r1_func_00129690();

extern void r1_func_00129600();

/* rac1-decomp src/core/0012AC80.c: func_0012BD60 */
/* Bump allocator out of a region {base, size, used}: round `used` up to
   `align`, reserve `size` bytes, and hand back the aligned offset. On
   overflow it reports through func_00130288 and returns 0 WITHOUT
   touching `used`.

   The fitting case is written first (`>=`): 2.9-ee then branches to the
   report on the true side (bnel) and puts the `used` store in the slot
   of the fall-through `b`, as retail. Written overflow-first, as 2.95.3
   needed, 2.9-ee inverts the test and puts the store in a beql slot,
   one instruction short (SIZE 104/108). */
/* Hands out an aligned chunk of memory from a region and reports an error if it is full. */
unsigned int mpeg_alloc_aligned(void *mpeg, char *region, unsigned int size,
                           unsigned int align) {
    unsigned int aligned;
    unsigned int end;

    aligned = ((*(unsigned int *)(region + 0x8) + align - 1) / align) * align;
    end = aligned + size;
    if (*(unsigned int *)(region + 0x0) + *(unsigned int *)(region + 0x4) >= end) {
        *(unsigned int *)(region + 0x8) = end;
        return aligned;
    }
    mpeg_report_error(mpeg, r1_D_00153B38);
    return 0;
}

extern int mpeg_decode_pictures(void *);
extern int r1_func_00128C90(void *);
extern int r1_func_0012C200(void *);
extern int r1_func_0012C058(void *, int, int);
extern void r1_func_0012C430();
extern char r1_D_00153B58[];

/* rac1-decomp src/core/0012AC80.c: func_0012FBF0 */
/*
 * _getpic (libmpeg.a:mpeg.o): fetch and start decoding one picture.
 * The image buffer (inner +0xD8) must be 64-byte aligned; if not, it is
 * reported through _errMessage with the address and the call fails with
 * -1. Otherwise loop: fetch headers (r1_func_00128C90) until one yields no
 * picture (0), the picture counter reaches its target (+0x174 == +0xD4)
 * or the fault flag (+0x848) clears, skipping the fetch when the last
 * decode returned -1. picture_coding_type 1/2/3 call r1_func_0012C058 with
 * that type's running index (+0xA0/+0xA4/+0xA8, I resetting all three)
 * and slot (+0x94/+0x98/+0x9C) and bump the index; type 4 shares the B
 * arm (retail's jump table maps 3 and 4 to one handler); 0 ends the
 * stream through r1_func_0012C200 and sets inner->0; anything above 4 does
 * nothing. Returns 1 once +0x820 or inner->0 is set.
 *
 * pictureType's initializer and lastResult declared first put both in
 * retail's saved registers and hoist lastResult's 0 into the prologue.
 */
/* Reads the video stream and starts decoding pictures until one is ready or the stream ends. */
int mpeg_decode_pictures(void *mpeg) {
    int pictureType = 1;
    int lastResult = 0;
    char *wrapper = (char *)mpeg;
    char *decoder = *(char **)(wrapper + 0x40);

    *(int *)decoder = 0;
    if ((*(int *)(decoder + 0xD8) & 0x3F) != 0) {
        r1_func_0012C430(decoder, r1_D_00153B58, *(int *)(decoder + 0xD8));
        return -1;
    }
    *(int *)(decoder + 0x820) = 0;

    do {
        if (lastResult != -1) {
            for (;;) {
                pictureType = r1_func_00128C90(decoder);
                if (pictureType == 0) break;
                if (*(int *)(decoder + 0x174) == *(int *)(decoder + 0xD4)) break;
                if (*(int *)(decoder + 0x848) == 0) break;
            }
        }

        switch (pictureType) {
        case 0:
            r1_func_0012C200(wrapper);
            *(int *)decoder = 1;
            break;
        case 1:
            *(int *)(decoder + 0xA8) = 0;
            *(int *)(decoder + 0xA4) = 0;
            *(int *)(decoder + 0xA0) = 0;
            lastResult = r1_func_0012C058(wrapper, 0, *(int *)(decoder + 0x94));
            *(int *)(decoder + 0xA0) = *(int *)(decoder + 0xA0) + 1;
            break;
        case 2:
            lastResult = r1_func_0012C058(wrapper, *(int *)(decoder + 0xA4), *(int *)(decoder + 0x98));
            *(int *)(decoder + 0xA4) = *(int *)(decoder + 0xA4) + 1;
            break;
        case 3:
        case 4:
            lastResult = r1_func_0012C058(wrapper, *(int *)(decoder + 0xA8), *(int *)(decoder + 0x9C));
            *(int *)(decoder + 0xA8) = *(int *)(decoder + 0xA8) + 1;
            break;
        }

        if (*(int *)(decoder + 0x820) != 0) {
            return 1;
        }
    } while (*(int *)decoder == 0);

    return 1;
}

/* rac1-decomp src/core/0012AC80.c: func_0012BF40 */
/* _decodeOrSkipFrame (libmpeg): sibling of func_0012FEC0
   (_decodeOrSkipField), for the frame-picture path. Adapted from
   Lombyte (GPL-3.0) for PAL. */
/* Decodes or skips one full video frame and moves the frame counters forward. */
int mpeg_decode_or_skip_frame(void *mpeg, int frameIndex, int frameLimit) {
    Wrapper *wrapper = (Wrapper *)mpeg;
    Obj40 *decoder = wrapper->obj;
    int skipped = 0;
    int decodedOk;
    int result;

    if (frameLimit == -1 || frameIndex < frameLimit) {
        if (decoder->unk008 == 0) {
            wrapper->unk08 = 0;
            decoder->unk008 = 1;
        }
        if (r1_func_00129690(decoder, 0) == 0) {
            decodedOk = 0;
        } else {
            decodedOk = 0;
            decodedOk = r1_func_00129530(decoder) != decodedOk;
        }
        result = decodedOk;
    } else {
        skipped = 1;
        result = r1_func_00129690(decoder, 0);
        mpeg_send_event_one((int)wrapper);
    }
    r1_func_00129600(decoder, decoder->unk118, decoder->unk004);
    if (decoder->unk174 != 3 && skipped == 0) {
        decoder->unk120 = (decoder->unk120 == 0);
    }
    wrapper->unk08 = decoder->unk118 - decoder->unk0AC;
    if (decoder->unk120 == 0) {
        decoder->unk118 = decoder->unk118 + 1;
        decoder->unk004 = decoder->unk004 + 1;
    }
    return result;
}
