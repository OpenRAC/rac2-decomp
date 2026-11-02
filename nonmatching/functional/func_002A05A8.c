/* functional: high. Written from the assembly with plain floats; the two tail jumps (to 0x2E5CF8 and 0x29F450) are ordinary calls followed by the return, so their result is not passed back. */
#include "common.h"

extern int D_001B1688;              /* the frame counter */
extern int func_002E5CF8(int, int, void *);
extern void func_0029F450(char *);

static int bits_002A05A8(float f)
{
    union {
        float f;
        int i;
    } u;
    u.f = f;
    return u.i;
}

static float float_002A05A8(unsigned int w)
{
    union {
        float f;
        unsigned int i;
    } u;
    u.i = w;
    return u.f;
}

/* UpdateMobyAnimation: steps the moby's animation fraction (float at 0x44) by speed (0x48) * rate
   (0x4C) when the current and next animation numbers (bytes 0x42 and 0x43) agree, else by the
   rate alone. A fraction near or over 1.0 moves to the next frame (bytes 0x40 and 0x41, data
   pointers at 0x58 and 0x5C, the rate at 0x4C refreshed from the animation or the frame), with
   bit 1 of the flags byte (0x60) for a frame step and bit 2 for a wrap round the animation's
   frame count; a negative one steps back. The words at 0x6C (low 24 bits) say whether sounds
   (bits 16 and up: that many events listed in the animation after its frame table, each a time
   in sixteenths of a frame and an id) are due in the stepped range: the first in range plays
   (func_002E5CF8 with the id) and ends; else the loop-sound update func_0029F450 runs at the end
   unless the word says otherwise. */
void func_002A05A8(char *m)
{
    unsigned int speed_bits = *(unsigned int *)(m + 72);
    unsigned int rate_bits = *(unsigned int *)(m + 76);
    float speed = float_002A05A8(speed_bits);
    float rate = float_002A05A8(rate_bits);
    char *cls = *(char **)(m + 36);
    int a66 = *(unsigned char *)(m + 66);
    int a67 = *(unsigned char *)(m + 67);
    float f1 = *(float *)(m + 68);
    float old = f1;
    unsigned int t6 = *(unsigned int *)(m + 108) & 0xFFFFFF;
    int flags = 0;
    int cur, nxt, start;
    char *anim, *a1, *a2;
    unsigned int a0w;
    long b;

    if (rate_bits == 0) {
        goto tail;
    }
    if (a66 == a67) {
        f1 = (0.0f + f1) + speed * rate;
    } else {
        f1 = f1 + rate;
    }
    if (speed_bits == 0) {
        goto tail;
    }
    cur = *(unsigned char *)(m + 64);
    nxt = *(unsigned char *)(m + 65);
    start = cur;
    anim = *(char **)(cls + 72 + a67 * 4);

    b = (long)bits_002A05A8(f1);
    if ((((0x3F808000L - b) | (b - 0x3F7F0000L)) > 0)) {
        f1 = 1.0f;
        goto forward;
    }
    if (b - 0x3F800000L > 0) {
        goto forward;
    }
    if (b < 0) {
        goto backward;
    }
    *(float *)(m + 68) = f1;
    goto stepped;

forward:
    for (;;) {
        int count;

        f1 = f1 - 1.0f;
        cur = nxt;
        nxt = nxt + 1;
        a1 = *(char **)(m + 92);
        if (a66 != a67) {
            *(unsigned char *)(m + 110) = *(unsigned char *)(anim + 18);
            a66 = a67;
            t6 = 0xFFFF;
        }
        f1 = f1 / rate;
        flags |= 1;
        count = *(unsigned char *)(anim + 16);
        a0w = *(unsigned int *)(anim + 24);
        a2 = *(char **)(anim + 28 + nxt * 4);
        if (count - nxt <= 0) {
            nxt = 0;
            flags |= 2;
            a2 = *(char **)(anim + 28);
        }
        if (a0w != 0) {
            rate = float_002A05A8(a0w);
        } else {
            rate = *(float *)a1;
        }
        f1 = f1 * rate;
        *(unsigned char *)(m + 66) = (unsigned char)a66;
        *(unsigned char *)(m + 64) = (unsigned char)cur;
        *(unsigned char *)(m + 65) = (unsigned char)nxt;
        *(char **)(m + 88) = a1;
        *(char **)(m + 92) = a2;
        *(float *)(m + 76) = rate;
        *(float *)(m + 68) = f1;
        if ((long)bits_002A05A8(f1) - 0x3F800000L > 0) {
            continue;
        }
        break;
    }
    goto stepped;

backward:
    for (;;) {
        f1 = f1 / rate;
        nxt = cur;
        cur = cur - 1;
        a2 = *(char **)(m + 88);
        flags |= 1;
        a0w = *(unsigned int *)(anim + 24);
        if (cur < 0) {
            cur = *(unsigned char *)(anim + 16);
            flags |= 2;
            cur = cur - 1;
        }
        a1 = *(char **)(anim + 28 + cur * 4);
        if (a0w != 0) {
            rate = float_002A05A8(a0w);
        } else {
            rate = *(float *)a1;
        }
        f1 = f1 * rate;
        *(char **)(m + 88) = a1;
        *(unsigned char *)(m + 64) = (unsigned char)cur;
        *(unsigned char *)(m + 65) = (unsigned char)nxt;
        f1 = f1 + 1.0f;
        *(char **)(m + 92) = a2;
        *(float *)(m + 76) = rate;
        *(float *)(m + 68) = f1;
        if (bits_002A05A8(f1) < 0) {
            continue;
        }
        break;
    }

stepped:
    *(unsigned char *)(m + 96) = (unsigned char)flags;
    if (t6 == 0xFFFF) {
        return;
    }
    if (a66 != a67) {
        goto tail;
    }
    {
        int events = (int)t6 >> 16;
        int lo, hi, e;
        char *p;

        if (events <= 0) {
            goto tail;
        }
        hi = (cur << 4) + (int)(f1 * 16.0f);
        lo = (start << 4) + (int)(old * 16.0f);
        if (hi - lo <= 0) {
            goto tail;
        }
        lo = lo + 1;
        p = anim + *(unsigned char *)(anim + 16) * 4;
        e = *(unsigned short *)(p + 30);
        for (;;) {
            if (events <= 0) {
                goto tail;
            }
            events--;
            p += 4;
            if (((e - lo) | (hi - e)) < 0) {
                e = *(unsigned short *)(p + 30);
                continue;
            }
            func_002E5CF8(*(unsigned short *)(p + 24), 0, m);
            return;
        }
    }

tail:
    *(unsigned char *)(m + 96) = (unsigned char)flags;
    if ((t6 & 0xFFFF) == 0xFFFF) {
        return;
    }
    if (((t6 >> 8) & 0xFF) != 0xFF) {
        func_0029F450(m);
        return;
    }
    if ((((unsigned int)m >> 8) & 3) != (unsigned int)(D_001B1688 & 3)) {
        return;
    }
    func_0029F450(m);
}
