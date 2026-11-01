#include "include_asm.h"

typedef int s32;
typedef unsigned char u8;
extern int func_002ED688(unsigned char *);
typedef struct { float lim; char pad[0x2c]; float v[4]; char pad2[0x40]; } Rec128;
extern Rec128 *D_001B1C54[] __attribute__((sda));
extern int D_00214F90[];
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DF0(void *);
extern void func_00283028(void *, void *, void *);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
extern void func_002C2210(void *, unsigned int, unsigned int, unsigned int, s32, float *, float, float, float, s32);
extern unsigned int func_002ED870(void);
extern int func_002EE6A8();

void func_PAL_002EE5C0(u8 *a0)
{
    u8 *s2;
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    float r;
    float f;
    float lim;
    int i;
    Rec128 *s0;
    float *s3;

    s2 = (u8 *)func_002ED688(a0);
    if (s2 != 0 && !func_002ED870() && func_002EE6A8(a0) != 2) {
        s0 = &D_001B1C54[0][D_00214F90[0]];
        s3 = s0->v;
        func_00282CF0(v, a0 + 0x10, s3);
        f = func_00282DF0(v);
        r = *(float *)(a0 + 0xC) * 0.00097656f;
        f = f + r;
        lim = s0->lim;
        if (lim < f) {
            func_00282F20(v, v, lim - r);
            func_00282CC0(a0 + 0x10, v, s3);
        }
        if (*(int *)(s2 + 0x15C) >= 7) {
            func_00283028(s2 + 0x90, s2 + 0x90, s2 + 0xD0);
            *(int *)(s2 + 0x15C) = 0;
            for (i = 0x13; i >= 0; i--) {
                float a = func_002A7940();
                float b = func_002A7940();
                func_002AF000(w, 0.20000002f, a, b);
                func_002C2210(a0 + 0x10, 0x32, 0x4000FF7F, 0, 2, w, 0.2f, 1.25f, 0.0f, 0);
            }
        }
    }
}

