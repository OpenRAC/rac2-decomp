#include "include_asm.h"

/* func_PAL_00343690, the PAL copy of func_00341610: the same C, where the second
   record's 1.0f and 8 become 0.0f and 7, the child object moves to 0x238, the records
   to 0x310 and the stored index to 0x31C, and the three ids passed to func_00288FB8 differ. */
extern int D_001AE0C8 __attribute__((sda));
extern char D_002652F0[];
extern void func_PAL_0034A2E0(void *, int);
extern void func_PAL_0034A230(unsigned char *, float *);
extern int func_00288FB8(int);
extern void func_00336A38(void *, unsigned int);
extern void func_003363C0(void *, float);

void func_PAL_00343690(char *self, int idx)
{
    float *records;
    float f;
    unsigned char *child;
    if ((unsigned int)idx > 2) return;
    *(int *)(self + 0x1C4) = ((int *)&D_001AE0C8)[idx];
    *(int *)(self + 0x1C8) = (int)(D_002652F0 + idx * 0x20);
    *(int *)(self + 0x1CC) = (idx == 0) ? 7 : ((idx == 1) ? 7 : 6);
    if (idx == 2) f = 2.0f;
    else f = 0.0f;
    child = (unsigned char *)self + 0x238;
    {
        int *p = (int *)(self + idx * 4);
        func_PAL_0034A2E0(child, p[0x6E]);
    }
    records = (idx == 0) ? *(float **)(self + 0x310) : ((idx == 1) ? *(float **)(self + 0x314) : *(float **)(self + 0x318));
    func_PAL_0034A230(child, records);
    func_00336A38(self + 0x1D0, func_00288FB8((idx == 0) ? 0xb66 : ((idx == 1) ? 0xb67 : 0x1110)));
    func_003363C0(self, f);
    func_003363C0(self + 0x4C, f);
    func_003363C0(self + 0xE4, f);
    *(int *)(self + 0x31c) = idx;
}
