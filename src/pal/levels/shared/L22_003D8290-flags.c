#include "include_asm.h"

typedef unsigned char u8;
extern int func_002E5CF8(int index, int a1, char *a2);
extern u8 D_001A63A8_4[];
extern int func_002A77E0(int a0);
extern u8 D_00189E20[];
extern void func_0029F338(void *);
extern void *func_002A9640(void *a0, int a1, int a2);
extern int func_002A77E0(int a0);
extern int func_002E5DA0(int index, int value, char *object, int kind);
extern void func_PAL_002AD288(void *a0, void *a1, int a2, float f12, float f13);
extern int func_002E5CF8(int index, int a1, char *a2);
extern void func_00282F20(float *a0, void *a1, float f12);
extern void func_PAL_002B15D8(void *a0, int a1, void *a2, unsigned char a3,
                           float f12, float f13, float f14, float f15);
extern void func_0029F338(void *object);
extern void func_L22_003D4320(u8 *a0, int a1, int a2);

void func_PAL_L22_003D8290(u8 *a0, int a1, int a2) {
    u8 *s0 = a0;
    void *s3;
    int s2;
    int s1;
    float buf[4];

    s3 = func_002A9640(a0, -1, 0);
    if (s3 == 0)
        return;
    if (*(short *)(s0 + 0xAA) == 0x1213) {
        s2 = 0xB;
        s1 = 0xF7F;
    } else {
        s2 = 0xC;
        s1 = 0xE0B;
    }
    func_002E5DA0(s2 + func_002A77E0(3), 0, s0, s1);
    func_PAL_002AD288(s0, s0 + 0x10, -1, 2.0f, 13.0f);
    func_002E5CF8(0, 0, s0);
    func_00282F20(buf, s3 + 0x10, 0.28000003f);
    func_PAL_002B15D8(s0, 3, buf, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
    func_0029F338(s0);
}
