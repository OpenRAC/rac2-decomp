#include "common.h"

/* func_L08_0032F898 sits in its own unit: it needs common.h's quadword helpers, which the
   parent file L08_002D90C8.c does not include. */

/* The fields of the resident block at D_00189E20 this function reads. */
typedef struct {
    char head[0x2290];
    char *selected;
    int mode;
    int pad;
    int state;
} SelectState;

extern SelectState D_00189E20;
/* A moby index list (count in element 0) and the moby array base: retail reads both
   through the absolute macro form, and the count through $gp in one delay slot. */
extern short D_L08_001B2B30[] __attribute__((sda));
extern char *D_L08_001B29DC[] __attribute__((sda));

extern int func_L08_0032E920(void *, int, int, int, int);
extern float func_00282E80(void *, void *);

/* Picks the listed moby of class 0xCB, 0x76C or 0xEB0 in state 3 nearest to input+0x10
   and closer than `minimum`; one at or beyond `limit` must also pass func_L08_0032E920.
   The starting candidate is the pointer at D_00189E20+0x2290, dropped (result 2) when the
   state word is 0x18, the mode word is 0x6F, or the point at D_00189E20+0x80 fails
   func_L08_0032E920 and lies beyond `limit`. Writes the choice, its position, its +0xF0
   vector and two more vectors to `out` (or clears them) and returns 0 (none), 1 (a
   listed moby) or 2 (the starting candidate dropped). */
int func_L08_0032F898(char *input, char *out, int a, int b, int c, int d, float minimum, float limit)
{
    char *selected = D_00189E20.selected;
    int result = 0;
    int i;

    if (D_00189E20.state == 0x18 || D_00189E20.mode == 0x6F) {
        selected = 0;
        result = 2;
    } else if (!func_L08_0032E920((char *)&D_00189E20 + 0x80, a, b, c, d)) {
        if (limit < vec_distance_xy(input + 0x10, (char *)&D_00189E20 + 0x80)) {
            selected = 0;
            result = 2;
        }
    }
    for (i = 1; i <= D_L08_001B2B30[0]; i++) {
        char *object = D_L08_001B29DC[0] + (D_L08_001B2B30[i] << 8);
        if (object && (*(short *)(object + 0xAA) == 0xCB || *(short *)(object + 0xAA) == 0x76C ||
                       *(short *)(object + 0xAA) == 0xEB0) &&
            *(unsigned char *)(object + 0x20) != 0xFE && *(unsigned char *)(object + 0x20) != 0xFD &&
            *(unsigned char *)(object + 0x20) == 3) {
            float distance = vec_distance_xy(input + 0x10, object + 0x10);
            int valid = 1;
            if (minimum <= distance)
                valid = 0;
            else if (!(distance < limit)) {
                if (!func_L08_0032E920(object + 0x10, a, b, c, d))
                    valid = 0;
            }
            if (valid) {
                selected = object;
                result = 1;
                minimum = distance;
            }
        }
    }
    if (selected) {
        *(char **)(out + 0x40) = selected;
        qcopy(out, selected + 0x10);
        qcopy(out + 0x10, selected + 0xF0);
        if (selected == D_00189E20.selected) {
            qcopy(out + 0x20, (char *)&D_00189E20 + 0xD0);
            qcopy(out + 0x30, (char *)&D_00189E20 + 0xE0);
        } else {
            qcopy(out + 0x30, out);
            *(float *)(out + 0x38) += 0.6f;
            qcopy(out + 0x20, out + 0x30);
        }
    } else {
        *(int *)(out + 0x40) = 0;
        qzero(out);
        qzero(out + 0x10);
        qzero(out + 0x30);
        qzero(out + 0x20);
    }
    *(int *)(out + 0x44) = result;
    return result;
}
