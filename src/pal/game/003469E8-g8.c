/* func_PAL_003469E8, the PAL copy of func_00344938: the same C with the PAL field offsets and string ids, where
 * the language byte D_PAL_001A7C3C picks string 0xAD3 for language 2, func_00336A78 is PAL's own func_PAL_00338770,
 * and cases 1 to 3 lose the 16.0f and pass an int local holding 0 instead of 0.0f. */
#include "include_asm.h"

extern char *func_00288FB8(int);
extern void func_00336A38(void *, char *);
extern void func_00115DA8(char *, const char *, ...);
extern void func_00336A30(void *, int);
extern void func_PAL_00338770(void *);
extern int func_002B0DB8(void);
extern int func_002B0D60(void);
extern int func_002B0D70(void);
extern float *func_00335E10(void *);
extern void func_00335E38(void *, float, float, float, float);
extern void func_00335E68(void *, int);
extern void func_0028FC48(int, int, int, int, unsigned long, int);
extern char D_001ADBC8[], D_001ADF98[], D_001AE2F8[];
extern unsigned char D_PAL_001A7C3C;
extern short D_001A7A1A;
extern int D_001A7A1C;
extern int D_001A79FC;
extern int D_001AE2F0 __attribute__((sda));
extern int D_001AE2E0 __attribute__((sda));
extern int D_001AE2E4;
extern int D_001AE2E8 __attribute__((sda));
extern int D_001AE2EC;

void func_PAL_003469E8(char *self)
{
    int sel = 0;
    float zero;
    int off;

    if (*(int *)(self + 0x4B8) == 3)
        sel = *(int *)(self + 0x4AC) + *(int *)(self + 0x4B0) * 2;
    self[0x480] = 0;
    self[0x490] = 0;
    if (D_PAL_001A7C3C == 2)
        func_00336A38(self + 0x310, func_00288FB8(0xAD3));
    else
        func_00336A38(self + 0x310, func_00288FB8(0xAD2));
    off = 0;
    switch (sel) {
    case 0:
        func_00336A38(self + 0x220, func_00288FB8(0xAD2));
        zero = 0.0f;
        func_00115DA8(self + 0x470, D_001ADBC8, func_00288FB8(0xBCC));
        func_00336A30(self + 0x368, 0);
        func_PAL_00338770(self + 0x368);
        func_00115DA8(self + 0x470, D_001ADF98, func_002B0DB8());
        func_00335E38(self + 0x368, func_00335E10(self + 0x368)[0] + (float)D_001AE2F0,
                      func_00335E10(self + 0x368)[1], zero, zero);
        func_00336A30(self + 0x368, 2);
        func_PAL_00338770(self + 0x368);
        func_00115DA8(self + 0x480, D_001ADBC8, func_00288FB8(0xBCD));
        func_00336A30(self + 0x3C0, 0);
        func_PAL_00338770(self + 0x3C0);
        func_00115DA8(self + 0x480, D_001ADF98, func_002B0D60());
        func_00335E38(self + 0x3C0, func_00335E10(self + 0x3C0)[0] + (float)D_001AE2F0,
                      func_00335E10(self + 0x3C0)[1], zero, zero);
        func_00336A30(self + 0x3C0, 2);
        func_PAL_00338770(self + 0x3C0);
        func_00115DA8(self + 0x490, D_001ADBC8, func_00288FB8(0xBCE));
        func_00336A30(self + 0x418, 0);
        func_PAL_00338770(self + 0x418);
        func_00115DA8(self + 0x490, D_001ADF98, func_002B0D70());
        func_00335E38(self + 0x418, func_00335E10(self + 0x418)[0] + (float)D_001AE2F0,
                      func_00335E10(self + 0x418)[1], zero, zero);
        func_00336A30(self + 0x418, 2);
        func_PAL_00338770(self + 0x418);
        break;
    case 1:
        func_00115DA8(self + 0x470, D_001ADBC8, func_00288FB8(0xBCC));
        func_00336A30(self + 0x368, 0);
        func_PAL_00338770(self + 0x368);
        func_00115DA8(self + 0x470, D_001ADF98, D_001A7A1A);
        func_00335E38(self + 0x368, func_00335E10(self + 0x368)[0] + (float)D_001AE2F0,
                      func_00335E10(self + 0x368)[1], off, off);
        func_00336A30(self + 0x368, 2);
        func_PAL_00338770(self + 0x368);
        func_00336A38(self + 0x310, func_00288FB8(0xAD1));
        func_00336A38(self + 0x220, func_00288FB8(0xAD1));
        break;
    case 2:
        func_00115DA8(self + 0x470, D_001ADBC8, func_00288FB8(0xBCC));
        func_00336A30(self + 0x368, 0);
        func_PAL_00338770(self + 0x368);
        func_00115DA8(self + 0x470, D_001ADF98, D_001A7A1C);
        func_00335E38(self + 0x368, func_00335E10(self + 0x368)[0] + (float)D_001AE2F0,
                      func_00335E10(self + 0x368)[1], off, off);
        func_00336A30(self + 0x368, 2);
        func_PAL_00338770(self + 0x368);
        func_00336A38(self + 0x310, func_00288FB8(0xAD0));
        func_00336A38(self + 0x220, func_00288FB8(0xAD0));
        break;
    case 3:
        func_00115DA8(self + 0x470, D_001ADBC8, func_00288FB8(0xBCC));
        func_00336A30(self + 0x368, 0);
        func_PAL_00338770(self + 0x368);
        func_00115DA8(self + 0x470, D_001ADF98, D_001A79FC);
        func_00335E38(self + 0x368, func_00335E10(self + 0x368)[0] + (float)D_001AE2F0,
                      func_00335E10(self + 0x368)[1], off, off);
        func_00336A30(self + 0x368, 2);
        func_PAL_00338770(self + 0x368);
        func_00115DA8(self + 0x470, D_001AE2F8, func_00288FB8(0xBCC), D_001A79FC);
        func_00336A38(self + 0x310, func_00288FB8(0xACF));
        func_00336A38(self + 0x220, func_00288FB8(0xACF));
        break;
    }
    func_PAL_00338770(self + 0x310);
    if (*(int *)(self + 0x4B4) == sel) {
        func_00335E68(self + 0x220, 1);
        func_00335E38(self + 0x220, (*(float **)(self + 0x4A0))[0] + -117.0f,
                      (*(float **)(self + 0x4A0))[1] + 3.0f, 0.0f, 0.0f);
        func_PAL_00338770(self + 0x220);
    }
    if (sel == 0) {
        int x = (*(float **)(self + 0x4A0))[0];
        int y = (*(float **)(self + 0x4A0))[1];
        func_0028FC48(x + D_001AE2E0, y + D_001AE2E4, x + D_001AE2E8, y + D_001AE2EC,
                      0x55F0C070, 0);
    }
}
