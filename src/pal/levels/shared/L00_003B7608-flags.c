#include "include_asm.h"

#include "common.h"
typedef int Quadword_L00_003B3E78 __attribute__((mode(TI)));
typedef union {
    Quadword_L00_003B3E78 bits;
    float f[4];
} Vec4_L00_003B3E78;
typedef struct {
    unsigned char pad0[4];
    int w4;
    unsigned char pad8[2];
    unsigned char ba;
    unsigned char bb;
} Sub_L00_003B3E78;
extern float D_001AF908 __attribute__((sda));
extern int D_001AF918 __attribute__((sda));
extern unsigned short D_001AF91C __attribute__((sda));
extern float D_001AF920 __attribute__((sda));
extern float D_001AF924 __attribute__((sda));
extern int D_001AF928 __attribute__((sda));
extern unsigned char D_001AF92C __attribute__((sda));
extern float D_001AF930 __attribute__((sda));
extern float D_L00_001B8DC0[];
extern void func_00282CF0(void *, void *, void *);
extern float func_00283CE0(int);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern int func_002A77E0(int);
extern u8 *func_PAL_002BE9A8(u8 *p, float fa, float fb, float fc, float fd, int v, void *local, int a3, int t0);

void func_PAL_L00_003B7870(u8 *obj)
{
    Vec4_L00_003B3E78 axis;
    Vec4_L00_003B3E78 w;
    Vec4_L00_003B3E78 a;
    Vec4_L00_003B3E78 b;
    float step;
    int i;

    axis.bits = 0;
    axis.f[2] = D_001AF908;
    func_00282CF0(&w, D_L00_001B8DC0, obj + 0x10);
    step = 6.2831855f / func_00283CE0(D_001AF918);
    for (i = 0; i < D_001AF918; i++) {
        u8 *e;
        int r;
        func_002ACEC0(&a, &axis, &w, (float)i * step);
        func_00282F20(&b, &a, D_001AF920 * 0.020000001f);
        r = func_002A77E0(16);
        if (func_002A77E0(2) != 0) {
            r = -r;
        }
        e = func_PAL_002BE9A8(obj + 0x10, 0.5f, 1.0f, D_001AF930, D_001AF924 * 210000.0f, r, &b, D_001AF928, 0);
        if (e != 0) {
            Sub_L00_003B3E78 *q = (Sub_L00_003B3E78 *)(e + 0x20);
            *(unsigned short *)(e + 0xA) = D_001AF91C;
            q->w4 = 2;
            q->ba = D_001AF92C;
            q->bb = e[0xA];
        }
    }
}
