/* Decode the compressed one-bit occlusion map into 0x8000 output bytes.
 * Adapted from OpenRAC/rac1-decomp src/game/menu.c:
 * decode_compressed_occlusion_map, GPL-3.0, revision
 * 8bbc6b38d1136b66391241e660043c9136ebb518.
 * The fixed scratchpad work area is 0x2400 bytes, including carry space;
 * packed 0x400-byte chunks are copied out before the expanded window advances.
 * Destination retains the retail 16-byte alignment and 0x8000-byte extent
 * contract; input streams supply valid encoded run/span commands.
 */
#include "common.h"

extern void func_00282A60(void *, unsigned int, int);
extern void func_00282B50(void *, const void *, int);


void func_002977A8(void *dst, const unsigned char *ctrl, const unsigned char *spans) {
    unsigned char *dst_end;
    unsigned char *end;
    const unsigned char *span;
    unsigned char *cursor;
    unsigned char *next_dst;
    unsigned char *next;
    unsigned char *wrapped;
    unsigned char *r;
    unsigned char *w;
    unsigned char *from;
    unsigned char *to;
    int count;
    int n;
    int bit;

    dst_end = (unsigned char *)dst + 0x8000;
    end = (unsigned char *)0x70002000;
    span = spans;
    count = *ctrl >> 1;
    ctrl++;
    func_00282A60((void *)0x70000000, 0, 0x2400);
    bit = 1;
    cursor = (unsigned char *)0x70000000;
    for (;;) {
        next_dst = (unsigned char *)dst + 0x400;
        do {
            cursor += *span++;
            n = *span++;
            if (n != 0) {
                do {
                    n--;
                    next = cursor + 1;
                    if (count == 0) {
                        do {
                            count = *ctrl++;
                            bit = !bit;
                        } while (count == 0);
                    }
                    *cursor = bit;
                    count--;
                    cursor = next;
                } while (n != 0);
            }
        } while (cursor < end);
        r = (unsigned char *)0x70000000;
        w = (unsigned char *)0x70000000;
        do {
            *w = *r++;
            *w |= *r++ << 1;
            *w |= *r++ << 2;
            *w |= *r++ << 3;
            *w |= *r++ << 4;
            *w |= *r++ << 5;
            *w |= *r++ << 6;
            *w |= *r++ << 7;
            w++;
        } while (r < end);
        func_00282B50(dst, (void *)0x70000000, 0x400);
        dst = next_dst;
        if (next_dst == dst_end) {
            return;
        }
        func_00282A60((void *)0x70000000, 0, 0x2000);
        wrapped = cursor - 0x2000;
        from = (unsigned char *)0x70002000;
        to = (unsigned char *)0x70000000;
        if (cursor > end) {
            do {
                *to++ = *from++;
            } while (from < cursor);
        }
        func_00282A60((void *)0x70002000, 0, 0x400);
        cursor = wrapped;
    }
}
