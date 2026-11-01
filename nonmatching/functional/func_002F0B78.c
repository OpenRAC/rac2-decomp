/* functional: high. Plain floats in place of VU0 macro code; the test reads the sign bit of the distance difference as retail's qmfc2 does (so -0.0 counts as inside); scratch is typed void * (the parser scratch, only its first four floats are read). */
#include "common.h"

extern char *D_001B2170;            /* the table of 64-byte entries */
extern int D_001B2174;              /* number of entries */

static int negative_002F0B78(float f)
{
    union {
        float f;
        int i;
    } u;
    u.f = f;
    return u.i < 0;
}

/* For every entry whose sphere (centre xyz and radius w at +0, scaled by 1024 on the scratch
   side) touches the sphere at scratch, writes the entry's number at position and stores slot
   number `index` in the first of the four nibbles of the halfword at entry+54 that is not yet
   filled in (tested as 0xFFFF, 0xFFF0, 0xFF00, 0xF000 from the low nibble up; any other value
   takes nothing). Stops when position reaches end. Returns the next position. */
unsigned short *func_002F0B78(unsigned short *position, unsigned short *end, int index, void *scratch)
{
    float *sc = (float *)scratch;
    float cx = sc[0] * 1024.0f, cy = sc[1] * 1024.0f, cz = sc[2] * 1024.0f, cw = sc[3] * 1024.0f;
    int count = D_001B2174;
    int number = -1;
    char *entry = D_001B2170 - 64;

    for (;;) {
        float *e;
        unsigned int bits;
        float dx, dy, dz, rw, d2;

        entry += 64;
        if (count <= 0) {
            break;
        }
        e = (float *)entry;
        bits = *(unsigned short *)(entry + 54);
        dx = cx - e[0];
        dy = cy - e[1];
        dz = cz - e[2];
        number++;
        rw = cw + e[3];
        count--;
        dx = dx * dx;
        dy = dy * dy;
        dz = dz * dz;
        rw = rw * rw;
        d2 = dy + dx;
        d2 = d2 + dz;
        d2 = d2 - rw;
        if (!negative_002F0B78(d2)) {
            continue;
        }
        if ((bits & 0xFFFF) == 0xFFFF) {
            bits = (bits & 0xFFF0) | (unsigned int)index;
        } else if ((bits & 0xFFF0) == 0xFFF0) {
            bits = (bits & 0xFF0F) | ((unsigned int)index << 4);
        } else if ((bits & 0xFF00) == 0xFF00) {
            bits = (bits & 0xF0FF) | ((unsigned int)index << 8);
        } else if ((bits & 0xF000) == 0xF000) {
            bits = (bits & 0x0FFF) | ((unsigned int)index << 12);
        } else {
            continue;
        }
        *position++ = (unsigned short)number;
        *(unsigned short *)(entry + 54) = (unsigned short)bits;
        if (position == end) {
            break;
        }
    }
    return position;
}
