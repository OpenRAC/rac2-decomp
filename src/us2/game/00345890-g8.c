/* func_US2_00345890, the USA v2.00 copy of func_00344938: the same C with the text elements moved, new
   string ids, a local row offset in place of 16.0f, and the highlight offsets read from data. */
#include "include_asm.h"

extern char *func_00288FB8(int);
extern void func_00336A38(void *, char *);
extern void func_00115DA8(char *, const char *, ...);
extern void func_00336A30(void *, int);
extern void func_US2_003378A0(void *);
extern int func_US2_002B1C20(void);
extern int func_002B0D60(void);
extern int func_002B0D70(void);
extern float *func_00335E10(void *);
extern void func_00335E38(void *, float, float, float, float);
extern void func_00335E68(void *, int);
extern void func_0028FC48(int, int, int, int, unsigned long, int);
extern char D_001ADBC8[], D_001ADF98[], D_001AE2F8[];
extern short D_001A7A1A;
extern int D_001A7A1C;
extern int D_001A79FC;
extern int D_001AE2F0 __attribute__((sda));
extern int D_001AE2E0 __attribute__((sda));
extern int D_001AE2E4;
extern int D_001AE2E8 __attribute__((sda));
extern int D_001AE2EC;
extern int D_US2_001AE2E8 __attribute__((sda));
extern int D_US2_001AE2EC;

void func_US2_00345890(char *self)
{
    int sel = 0;
    int yoff;
    float zero;

    if (*(int *)(self + 0x4B8) == 3)
        sel = *(int *)(self + 0x4AC) + *(int *)(self + 0x4B0) * 2;
    self[0x480] = 0;
    self[0x490] = 0;
    yoff = 16;
    func_00336A38(self + 0x310, func_00288FB8(0x333E));
    switch (sel) {
    case 0:
        func_00336A38(self + 0x220, func_00288FB8(0x333E));
        zero = 0.0f;
        func_00115DA8(self + 0x470, D_001ADBC8, func_00288FB8(0x2C51));
        func_00336A30(self + 0x368, 0);
        func_US2_003378A0(self + 0x368);
        func_00115DA8(self + 0x470, D_001ADF98, func_US2_002B1C20());
        func_00335E38(self + 0x368, func_00335E10(self + 0x368)[0] + (float)D_001AE2F0,
                      func_00335E10(self + 0x368)[1], zero, zero);
        func_00336A30(self + 0x368, 2);
        func_US2_003378A0(self + 0x368);
        func_00115DA8(self + 0x480, D_001ADBC8, func_00288FB8(0x2C52));
        func_00336A30(self + 0x3C0, 0);
        func_US2_003378A0(self + 0x3C0);
        func_00115DA8(self + 0x480, D_001ADF98, func_002B0D60());
        func_00335E38(self + 0x3C0, func_00335E10(self + 0x3C0)[0] + (float)D_001AE2F0,
                      func_00335E10(self + 0x3C0)[1], zero, zero);
        func_00336A30(self + 0x3C0, 2);
        func_US2_003378A0(self + 0x3C0);
        func_00115DA8(self + 0x490, D_001ADBC8, func_00288FB8(0x2C53));
        func_00336A30(self + 0x418, 0);
        func_US2_003378A0(self + 0x418);
        func_00115DA8(self + 0x490, D_001ADF98, func_002B0D70());
        func_00335E38(self + 0x418, func_00335E10(self + 0x418)[0] + (float)D_001AE2F0,
                      func_00335E10(self + 0x418)[1], zero, zero);
        func_00336A30(self + 0x418, 2);
        func_US2_003378A0(self + 0x418);
        break;
    case 1:
        func_00115DA8(self + 0x470, D_001ADBC8, func_00288FB8(0x2C51));
        func_00336A30(self + 0x368, 0);
        func_US2_003378A0(self + 0x368);
        func_00115DA8(self + 0x470, D_001ADF98, D_001A7A1A);
        func_00335E38(self + 0x368, func_00335E10(self + 0x368)[0] + (float)D_001AE2F0,
                      func_00335E10(self + 0x368)[1] + (float)yoff, 0.0f, 0.0f);
        func_00336A30(self + 0x368, 2);
        func_US2_003378A0(self + 0x368);
        func_00336A38(self + 0x310, func_00288FB8(0x333C));
        func_00336A38(self + 0x220, func_00288FB8(0x333C));
        break;
    case 2:
        func_00115DA8(self + 0x470, D_001ADBC8, func_00288FB8(0x2C51));
        func_00336A30(self + 0x368, 0);
        func_US2_003378A0(self + 0x368);
        func_00115DA8(self + 0x470, D_001ADF98, D_001A7A1C);
        func_00335E38(self + 0x368, func_00335E10(self + 0x368)[0] + (float)D_001AE2F0,
                      func_00335E10(self + 0x368)[1] + (float)yoff, 0.0f, 0.0f);
        func_00336A30(self + 0x368, 2);
        func_US2_003378A0(self + 0x368);
        func_00336A38(self + 0x310, func_00288FB8(0x333B));
        func_00336A38(self + 0x220, func_00288FB8(0x333B));
        break;
    case 3:
        func_00115DA8(self + 0x470, D_001ADBC8, func_00288FB8(0x2C51));
        func_00336A30(self + 0x368, 0);
        func_US2_003378A0(self + 0x368);
        func_00115DA8(self + 0x470, D_001ADF98, D_001A79FC);
        func_00335E38(self + 0x368, func_00335E10(self + 0x368)[0] + (float)D_001AE2F0,
                      func_00335E10(self + 0x368)[1] + (float)yoff, 0.0f, 0.0f);
        func_00336A30(self + 0x368, 2);
        func_US2_003378A0(self + 0x368);
        func_00115DA8(self + 0x470, D_001AE2F8, func_00288FB8(0x2C51), D_001A79FC);
        func_00336A38(self + 0x310, func_00288FB8(0x333A));
        func_00336A38(self + 0x220, func_00288FB8(0x333A));
        break;
    }
    func_US2_003378A0(self + 0x310);
    if (*(int *)(self + 0x4B4) == sel) {
        func_00335E68(self + 0x220, 1);
        func_00335E38(self + 0x220, (float)D_US2_001AE2E8 + (*(float **)(self + 0x4A0))[0],
                      (float)D_US2_001AE2EC + (*(float **)(self + 0x4A0))[1], 0.0f, 0.0f);
        func_US2_003378A0(self + 0x220);
    }
    if (sel == 0) {
        int x = (*(float **)(self + 0x4A0))[0];
        int y = (*(float **)(self + 0x4A0))[1];
        func_0028FC48(x + D_001AE2E0, y + D_001AE2E4, x + D_001AE2E8, y + D_001AE2EC,
                      0x55F0C070, 0);
    }
}
