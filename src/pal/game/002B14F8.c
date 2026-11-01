#include "include_asm.h"

typedef unsigned char u8;
extern u8 D_00139648;
extern u8 D_001A7A47 __attribute__((sda));
extern void func_002AEC48(void *a0, void *a1, int a2, float f12, float f13);
extern u8 D_00139568[];
extern u8 D_00239BA0[];
extern u8 D_001A7A60[] __attribute__((sda));

/* Stores the third argument (or 1.0f) in the object's float at 0x70, and, when the fifth argument
   is set and that float differs from the one at 0x20, calls func_002AEC48 with the object's two
   first arguments, the fourth argument and the pair 0.03f, 0.3f. */
void func_PAL_002B14F8(void *a0, float *a1, float f12, int a2, int a3)
{
    if (D_001A7A47 != 0) {
        a1[28] = f12;
    } else {
        a1[28] = 1.0f;
    }
    if (a3 != 0) {
        if (a1[28] != a1[8]) {
            func_002AEC48(a0, a1, a2, 0.0432f, 0.43200004f);
        }
    }
}


INCLUDE_ASM("asm/pal/game", func_PAL_002B1570);

void func_PAL_002B1588(int first, int second)
{
    extern int func_00288FB8(int);
    extern void func_0029CC98(int, int);
    func_0029CC98(func_00288FB8(first), second);
}

extern void func_0029CC50(int, int, int);

void func_PAL_002B15B8(int first, int second, int third) {
    func_0029CC50(first, second, third);
}

extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00283098(float *dst, float *src, char *table);
extern void func_00282CC0(float *dst, float *src, float *arg);
extern int D_L00_001A8FF0_1 __attribute__((sda));
extern void func_PAL_002735D0(char *self, int a1, int a2, int a3, char *p4, char *p5,
                    float *buf, int b3, float fa, float fb);

/* Walks selected mask bits, evaluates three stored curve components, optionally transforms the vector, and dispatches one object operation per selected bit. */
void func_PAL_002B15D8(char *self, int mask, float *arg2,
                                        unsigned char arg3,
                                        float f0, float f1, float f2, float f3)
{
    /* Vector primitives read/write all 16 bytes; retail initializes only xyz. */
    float buf[4] __attribute__((aligned(16)));
    float v;
    float k;
    float fa;
    float fb;
    int i;

    for (i = 0; i < 15; i++) {
        if (((mask >> i) ^ 1) & 1)
            continue;
        v = func_002A7940();
        k = func_002A7878(f0, f1) * (0.020000001f);
        buf[0] = func_00283180(v) * k;
        buf[1] = func_00283198(v) * k;
        buf[2] = 0.0f;
        buf[2] = func_002A7878(f2, f3) * (0.020000001f);
        if (D_L00_001A8FF0_1 != 0)
            func_00283098(buf, buf, self + 192);
        func_00282CC0(buf, buf, arg2);
        fa = func_002A7878(90.0f, 270.0f);
        fb = func_002A7878(10.0f, 20.0f);
        func_PAL_002735D0(self, 2, *(short *)(self + 170), i, self + 16, self + 240,
                buf, arg3, fa, fb);
    }
}

