/* functional: medium. Written from the assembly, carrying the two parts reached by jumps: func_002A1378 (the fourth-short pass, below as stage B) and func_002A1490 (stage C), so one call does all three; the VU0 sqrt and float-to-int are plain float code (truncating), the pipelined loop of stage B is written per entry. */
#include "common.h"

/* Stage B (retail 0x2A1378): the fourth short of each of the first `count` output entries is the
   w of a unit quaternion whose x, y, z are the first three shorts (/32768): w = sqrt(max(0,
   1 - x*x - y*y - z*z)), scaled by 32768, clamped to 0x7FFF and negated when this entry's bit in
   the flag stream is set (8 bits per byte, low bit first). Returns the stream after the flags. */
static unsigned char *stage_b_002A1130(unsigned char *out, int count, unsigned char *flags)
{
    unsigned int bits = *flags++;
    int left = 8;
    int k;

    for (k = 0; k < count; k++) {
        short *h = (short *)(out + 16 + k * 8);
        float x = (float)h[0] / 32768.0f;
        float y = (float)h[1] / 32768.0f;
        float z = (float)h[2] / 32768.0f;
        float w2, root;
        int val;

        x = x * x;
        y = y * y;
        z = z * z;
        w2 = 1.0f - x;
        w2 = w2 - y;
        w2 = w2 - z;
        if (w2 < 0.0f) {
            w2 = 0.0f;
        }
        root = 0.0f + __builtin_sqrtf(w2);
        val = (int)(root * 32768.0f);
        if (left <= 0) {
            bits = *flags++;
            left = 7;
        } else {
            left--;
        }
        if (val > 0x7FFF) {
            val = 0x7FFF;
        }
        if (bits & 1) {
            val = -val;
        }
        bits = bits >> 1;
        h[3] = (short)val;
    }
    return flags;
}

/* Stage C (retail 0x2A1490): see func_002A1490. */
static void stage_c_002A1130(unsigned char *src, unsigned char *out, int count, unsigned char *s)
{
    unsigned char *at = src + count * 6;
    unsigned char *dst = out + count * 8 + 16;
    int counts[2];
    int pass;

    counts[0] = at[4];
    counts[1] = at[5];
    at += 6;
    for (pass = 0; pass < 2; pass++) {
        int left = counts[pass];

        if (left == 0) {
            continue;
        }
        do {
            int code = *s++;
            int k;

            *(short *)(dst + 6) = *(short *)(at + 6);
            for (k = 0; k < 3; k++) {
                int v = *(short *)(at + k * 2);
                int mode = code & 3;

                if (mode == 1) {
                    int d = *(signed char *)s;

                    s++;
                    v = v + (d << 2);
                } else if (mode == 2) {
                    int hi = *(signed char *)(s + 1);
                    int lo = s[0];

                    s += 2;
                    v = (hi << 8) | lo;
                }
                *(short *)(dst + k * 2) = (short)v;
                code = code >> 2;
            }
            at += 8;
            dst += 8;
            left--;
        } while (left > 0);
    }
}

/* Decodes an animation block at src for `count` joints into out: a header (1/frames as a float at 0,
   then frame count, and sizes), the first `count` entries (three shorts each, 8 bytes apart at
   out+16, each short's low two bits choosing keep, add a signed byte << 2, add a 10-bit packed
   value << 2, or take the next halfword), then the quaternion w pass and the extra entries.
   ref's low 28 bits are the address of the block's second part (its header and packed streams). */
void func_002A1130(void *src, int ref, void *out, int count)
{
    unsigned char *base = (unsigned char *)src;
    unsigned char *part = (unsigned char *)(unsigned int)((unsigned int)ref & 0x0FFFFFFF);
    unsigned char *o = (unsigned char *)out;
    unsigned char *rec = base + count * 6;
    unsigned int frames = *(unsigned short *)part;
    unsigned int word;
    int c1 = rec[4], c2 = rec[5];
    int shift = 22;
    unsigned char *packed, *bytes, *halves;
    unsigned char *in;
    unsigned char *dst;
    int left;

    *(unsigned short *)(o + 4) = *(unsigned short *)(part + 2);
    *(unsigned short *)(o + 8) = (unsigned short)(count * 8);
    *(unsigned short *)(o + 6) = (unsigned short)((count + c1 + c2 + 1) >> 1);
    *(unsigned short *)(o + 10) = (unsigned short)c1;
    *(unsigned short *)(o + 12) = (unsigned short)((c1 + count) * 8);
    *(unsigned short *)(o + 14) = (unsigned short)c2;
    *(int *)o = 0;
    if (frames != 0) {
        *(float *)o = 1.0f / (float)frames;
    }

    word = *(unsigned int *)base;
    packed = part + 4;
    bytes = packed + ((word >> 10) & 0x7FF);
    halves = packed + (word & 0x3FF);
    in = base + 4;
    dst = o + 16;
    left = count;
    do {
        short comp[3];
        int k;

        for (k = 0; k < 3; k++) {
            int v = *(short *)(in + k * 2);
            int mode = v & 3;

            if (mode == 1) {
                int d = *(signed char *)bytes;

                bytes++;
                v = v + (d << 2);
            } else if (mode == 2) {
                int bitsv = (int)(*(unsigned int *)packed << shift) >> 22;

                shift -= 10;
                if (shift <= 0) {
                    shift = 22;
                    packed += 4;
                }
                v = v + (bitsv << 2);
            } else if (mode == 3) {
                v = *(short *)halves;
                halves += 2;
            }
            comp[k] = (short)v;
        }
        *(short *)(dst + 0) = comp[0];
        *(short *)(dst + 2) = comp[1];
        *(short *)(dst + 4) = comp[2];
        in += 6;
        dst += 8;
        left--;
    } while (left > 0);

    /* stage B: the flag stream sits (word >> 21) bytes into the second part's data */
    {
        unsigned char *flags = part + 4 + (word >> 21);

        flags = stage_b_002A1130(o, count, flags);
        stage_c_002A1130(base, o, count, flags);
    }
}
