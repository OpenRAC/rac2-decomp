/* functional: medium. Plain floats and shifts in place of VU0 macro code, MMI byte packing and the jump into func_002A0F48; the order of the float operations follows the assembly, no fcheck verdict is implied by this line. */
#include "common.h"

extern void func_002A0C68(void *moby, int cell);
extern float D_001CD540[][4];

/* What func_002A0F48 and func_002A10E8 share (retail's 0x2A0F80, which both reach by a jump): flag
   0x8000 mirrors the middle row. The class's bounding sphere for the current animation frame,
   blended between frames 0x42 and 0x43 by 0x44 (frame 255 is the entry of the table at D_001CD540
   chosen by 0x40) and cached at 0x80, is scaled by 0x2C and moved to the moby's place in 1/1024
   units, into 0x00. With a grid slot (0x98) the sphere's cell range packs into four bytes, and a
   new in-range one moves the moby in the grid. */
static void moby_bound_002A0F80(char *m, int mirror)
{
    char *cls = *(char **)(m + 0x24);
    float bound[4], scaled[4], *rows = (float *)(m + 0xC0), *from, *to;
    unsigned char frame = *(unsigned char *)(m + 0x42), next = *(unsigned char *)(m + 0x43);
    float scale = *(float *)(m + 0x2C), t;
    int i, x, y, w, old;
    unsigned int cell;

    if (mirror) {
        for (i = 0; i < 3; i++) {
            rows[4 + i] = 0.0f - rows[4 + i];
        }
    }

    if (frame != next) {
        to = *(float **)(cls + 0x48 + next * 4);
        if (frame == 255) {
            from = D_001CD540[*(unsigned char *)(m + 0x40)];
        } else {
            from = *(float **)(cls + 0x48 + frame * 4);
        }
        t = *(float *)(m + 0x44);
        for (i = 0; i < 4; i++) {
            bound[i] = (to[i] * t + from[i]) - from[i] * t;
        }
    } else {
        float *cached = (float *)(m + 0x80);
        if (frame != *(unsigned char *)(m + 0x61)) {
            *(unsigned char *)(m + 0x61) = frame;
            from = *(float **)(cls + 0x48 + frame * 4);
            for (i = 0; i < 4; i++) {
                cached[i] = from[i];
            }
        }
        for (i = 0; i < 4; i++) {
            bound[i] = cached[i];
        }
    }

    for (i = 0; i < 4; i++) {
        scaled[i] = bound[i] * scale;
    }
    for (i = 0; i < 3; i++) {
        float *place = (float *)(m + 0x10);
        float at = rows[i] * scaled[0];
        at = at + rows[4 + i] * scaled[1];
        at = at + rows[8 + i] * scaled[2];
        ((float *)m)[i] = at + place[i] * 1024.0f;
    }
    ((float *)m)[3] = scaled[3];
    *(unsigned short *)(m + 0xAC) += 1;

    if (*(int *)(m + 0x98) == 0) {
        return;
    }
    x = (int)((float *)m)[0];
    y = (int)((float *)m)[1];
    w = (int)scaled[3];
    old = *(int *)(m + 0xA4);
    cell = (((x - w) >> 14) & 0xFF) | ((((y - w) >> 14) & 0xFF) << 8)
         | ((((x + w) >> 14) & 0xFF) << 16) | ((unsigned int)((y + w) >> 14) << 24);
    /* The compare is of 64-bit registers: the packed word is zero-extended, the old one not. */
    if ((int)cell >= 0 && (int)cell == old) {
        return;
    }
    if (cell & 0xC0C0) {
        return;
    }
    func_002A0C68(m, (int)cell);
}

/* A moby's transform for this frame with the rows it has at 0xC0. */
void func_002A10E8(void *object)
{
    char *m = object;

    if (*(signed char *)(m + 0x20) < 0) {
        return;
    }
    moby_bound_002A0F80(m, *(unsigned short *)(m + 0x34) & 0x8000);
}
