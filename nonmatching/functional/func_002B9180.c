/* functional: high. Plain C for the same bitmap and counter updates; pminw becomes a signed minimum on the low word. */
#include "common.h"

extern char *D_001B1D90;            /* the particle pool's first slot (64 bytes each) */
extern int D_001B1D94;              /* lowest slot in use */
extern int D_001B1D98;              /* highest slot in use */
extern int D_001B1D9C;              /* live count */
extern unsigned char D_001F1D40[];  /* in-use bitmap; a second bitmap 256 bytes on */

/* FreeParticle: clears the slot's bits, drops the live count, walks the high-water mark down
   when this was the highest slot, marks the particle freed (byte 1 = 0x80) and lowers the
   low-water mark to this slot if it is below it. */
void func_002B9180(char *p)
{
    unsigned char *bm = D_001F1D40;
    int index = (int)((unsigned int)(p - D_001B1D90) >> 6);
    int low = D_001B1D94;
    int high = D_001B1D98;

    D_001B1D9C = D_001B1D9C - 1;
    if (*(unsigned char *)(p + 1) & 0x40) {
        bm[(index >> 3) + 256] = (unsigned char)(bm[(index >> 3) + 256] & ~(1 << (index & 7)));
    }
    bm[index >> 3] = (unsigned char)(bm[index >> 3] & ~(1 << (index & 7)));

    if (index == high) {
        high = high - 1;
        while (high >= 0 && (bm[high >> 3] & (1 << (high & 7))) == 0) {
            high = high - 1;
        }
        D_001B1D98 = high;
    }
    *(unsigned char *)(p + 1) = 0x80;
    if (index < low) {
        low = index;
    }
    D_001B1D94 = low;
}
