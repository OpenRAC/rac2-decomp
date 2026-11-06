#include "include_asm.h"

extern char D_001ADBC8[];
extern char D_US2_001ADF70[]; /* "%d/%d": sits where v1.01 has "%d" (D_001ADF98), but plain "%d" is elsewhere in v2.00 */
extern int D_001ADF90 __attribute__((sda));
extern char D_001C4FA0[];
extern const char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern void func_00336A30(char *, int);
extern void func_US2_003378A0(char *);
extern int func_US2_002B1C90(int);
extern int func_US2_002B1D18(int);
extern float *func_00335E10(char *);
extern void func_00335E38(char *, float, float, float, float);

/* func_US2_0033FDD8, reduced from func_0033ED88's first row: while the entry at +0x230 is 1 to 20, formats message
 * 0x2C51 and two values derived from it into the buffer at +0x6C0, places the text object at +0x470 and draws it,
 * then draws the object at +0x578. */
void func_US2_0033FDD8(char *self)
{
    float zero = 0.0f;
    char *base = D_001C4FA0;

    if ((unsigned int)(*(int *)(base + 0x230) - 1) < 20) {
        func_00115DA8(self + 0x6C0, D_001ADBC8, func_00288FB8(0x2C51));
        func_00336A30(self + 0x470, 0);
        func_US2_003378A0(self + 0x470);
        func_00115DA8(self + 0x6C0, D_US2_001ADF70, func_US2_002B1C90(*(int *)(base + 0x230)),
                      func_US2_002B1D18(*(int *)(base + 0x230)));
        func_00335E38(self + 0x470, func_00335E10(self + 0x470)[0] + (float)D_001ADF90,
                      func_00335E10(self + 0x470)[1], zero, zero);
        func_00336A30(self + 0x470, 2);
        func_US2_003378A0(self + 0x470);
        func_US2_003378A0(self + 0x578);
    }
}
