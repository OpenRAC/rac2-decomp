/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Near miss (mid-16): 400/424 bytes. Retail keeps self+0xA8 in $a0 as base+index addressing (no offset folding), copies the s1 line-table pointer to s4, and keeps the const 1 stored to +0x1B0 apart from the flag.
   Needs the unit flags: default (-O2 -G0 -ffunction-sections) */
#include "common.h"

extern void func_00115484(void *, int, int);
extern int func_0027F178(void *, int);

void func_00337E98(unsigned char *self, int a1, int a2, float f12, float f13)
{
    unsigned char buf[0x100];
    unsigned char **lines = (unsigned char **)(self + 0x1D8);
    int i = 0;
    int j = 0;
    int flag = 1;
    int w;

    *(float *)(*(int *)self) = f12;
    *(float *)(*(int *)self + 4) = f13;
    *(int *)(self + 0x1B8) = a2;
    self[0x1A7] = 0;
    *(int *)(self + 0x1D4) = 0;
    *(int *)(self + 0x1B0) = 1;
    func_00115484(buf, 0, 0x100);
    func_00115484(lines, 0, 0x78);
    lines[*(int *)(self + 0x1B0) - 1] = self + 0xA8;
    if (self[0xA8] != 0) {
        unsigned char *next = self + 0xA9;
        do {
            if (self[0xA8 + i] == 1) {
                buf[j] = 0;
                self[0xA8 + i] = 0;
                flag = 0;
                j = 0;
                lines[*(int *)(self + 0x1B0)] = next;
                *(int *)(self + 0x1B0) = *(int *)(self + 0x1B0) + 1;
                w = func_0027F178(buf, -1);
                if (*(int *)(self + 0x1D4) < w)
                    *(int *)(self + 0x1D4) = w;
            } else {
                buf[j] = self[0xA8 + i];
                j++;
            }
            i++;
            next++;
        } while (i < 0xFF && self[0xA8 + i] != 0);
    }
    if (flag)
        *(int *)(self + 0x1D4) = func_0027F178(self + 0xA8, -1);
    else {
        w = func_0027F178(buf, -1);
        if (*(int *)(self + 0x1D4) < w)
            *(int *)(self + 0x1D4) = w;
    }
    *(float *)(*(int *)(self + 4)) = 1.0f;
}
