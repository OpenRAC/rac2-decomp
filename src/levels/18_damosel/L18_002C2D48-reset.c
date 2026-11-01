#include "common.h"

/* The two arms on 0x340 are one in retail: jump2 cross-jumps them, the branch goes and its load
   stays as a dead lw that also ends the extended block, so the hero address is rebuilt. */

extern char D_00189E20[];

extern void func_00282A88(void *, int);
extern u8 D_L18_001A7B0B MACRO_ADDR;

/* Re-initialises the 16-byte block at 0x1490 and then, from the saved mode in it, raises the matching flags. */
void func_L18_002CA350(void)
{
    char *p = D_00189E20;
    s16 mode = *(s16 *)(p + 0x1490);
    u8 keep = *(u8 *)(p + 0x149D);
    func_00282A88(p + 0x1490, 16);
    *(u8 *)(p + 0x149D) = keep;
    *(s16 *)(p + 0x1490) = mode;
    *(u8 *)(p + 0x22B9) = 0;
    *(s16 *)(p + 0x348) = 0;
    if (*(u8 *)(p + 0x22BD) != 0)
        return;
    if (*(int *)(p + 0x340) != 0) {
        if (mode == -1)
            return;
    } else {
        if (mode == -1)
            return;
    }
    {
        if (mode == 2) {
            char *m = D_00189E20;
            if (*(s16 *)(m + 0x1DE) == 0 && (*(s16 *)(m + 0x34C) == 0 || *(float *)(m + 0x31C) < 2.5f)) {
                *(u8 *)(m + 0x1497) = 1;
                if (*(u8 *)(m + 0x22B4) == 0 && D_L18_001A7B0B != 0)
                    *(s16 *)(m + 0x348) = 1;
            }
        }
        if (mode == 0xE) {
            char *h = D_00189E20;
            *(u8 *)(h + 0x1494) = 1;
            *(float *)(h + 0x24C4) = 0.2f;
            *(float *)(h + 0x330) = *(float *)(h + 0x318) + 0.2f;
        }
        if (mode == 0) {
            float d;
            char *h = D_00189E20;
            d = *(float *)(h + 0x330) - *(float *)(h + 0x318);
            *(float *)(h + 0x24C4) = d;
            if (d < 0.85f && d > 0.25f)
                *(u8 *)(h + 0x22B9) = 1;
            h = D_00189E20;
            *(u8 *)(h + 0x1494) = 1;
        }
        if (mode == 7) {
            char *h = D_00189E20;
            *(u8 *)(h + 0x1492) = 1;
        }
        if (mode == 8) {
            char *h = D_00189E20;
            *(u8 *)(h + 0x149A) = 1;
        }
        if (mode == 0xC) {
            char *h = D_00189E20;
            *(u8 *)(h + 0x149A) = 1;
        }
    }
}
