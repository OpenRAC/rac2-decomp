#include "common.h"

/* func_L09_003FE3B0 of L09_002F8BA0.c, in a unit of its own: retail's gcse ran on the unsplit
   flow graph here (-frac2-gcse-unsplit-edges, config/cflags.txt). With the critical edge from the
   peeled first comparison into the scan loop split, PRE puts the next-track-pointer add at the end
   of both peeled arms and the two successful-search exits no longer cross-jump. */

extern unsigned short *D_L09_001FB560[];
extern unsigned char *D_L09_001B285C_1[3] __attribute__((sda));
extern int D_L09_00257110[];
extern char D_L09_001B9A00[];

extern float func_00282E80(void *, void *);

/* Walks the record's track while its signed halfwords stay non-negative and returns the
   entry whose measured value is largest, skipping the entries whose field 0xB2 is in the
   twenty-value screen table. */
void *func_L09_003FE3B0(int index, int *table)
{
    unsigned short *q = D_L09_001FB560[index];
    char *r;
    void *best = 0;
    float bestf = 0.0f;
    int found;
    int i;

    if (q == 0)
        return 0;
    do {
        found = 0;
        r = (char *)D_L09_001B285C_1[0] + ((q[0] & 0x7FFF) << 8);
        for (i = 0; i < 20; i++) {
            if (*(short *)(r + 0xB2) == D_L09_00257110[i]) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
            float f = func_00282E80(D_L09_001B9A00, r + 0x10);
            if (bestf < f) {
                bestf = f;
                best = r;
            }
        }
    } while ((short)*q++ >= 0);
    return best;
}
