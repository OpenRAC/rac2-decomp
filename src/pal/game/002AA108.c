#include "include_asm.h"

typedef int s32;
typedef unsigned char u8;
typedef float f32;
extern s32 func_001163B0(void);
extern f32 func_002A7940_5(void);
extern f32 func_002A7878_10(f32, f32);
extern f32 func_00283180_3 (f32);
extern s32 D_001BAF80[];
typedef struct Rec_002A96A0 {
    char pad0[4];
    short s4;
    char pad6[0x11];
    u8 b17;
    u8 *p18;
    short s1C;
} Rec_002A96A0;
typedef struct Src_002A96A0 {
    char pad0[0x20];
    u8 *p20;
    int f24;
    u8 b28;
    float f2C;
} Src_002A96A0;
extern Rec_002A96A0 *func_002AB1F0(s32);
extern u8 *func_002AB220(s32);
extern u8 func_002AD980(u8 *);

f32 func_PAL_002AA108(s32 a0, Src_002A96A0 *a1) {
    Rec_002A96A0 *p = func_002AB1F0(a0);
    f32 f = 0.0f;
    if (p != 0) {
        u8 *q = p->p18;
        if (q != 0) {
            u8 c = q[0x20];
            if (c != 0xFE) {
                if (c == 0xFD) {
                    p->s1C = 0;
                    p->p18 = 0;
                }
            } else {
                p->s1C = 0;
                p->p18 = 0;
            }
        }
        {
            short t = p->s1C;
            if (t != 0) {
                p->s1C = (unsigned short)p->s1C + 1;
                if (t >= 0x65) {
                    p->p18 = 0;
                    p->s1C = 0;
                }
            }
        }
        if (a1 != 0) {
            u8 *x = a1->p20;
            f = a1->f2C;
            if (x != 0) {
                if (p->p18 != x) {
                    p->p18 = x;
                    p->b17 = func_002AD980(a1->p20);
                    p->s1C = 1;
                } else {
                    if (a1->b28 == 9) {
                        if (p->s1C < 0x32) f = 0.0f;
                        else p->s1C = 1;
                    } else {
                        if (p->s1C < 8) f = 0.0f;
                        p->s1C = 1;
                    }
                }
            }
            if ((f32)p->s4 <= 1.0f && f > 0.0f && f < 1.0f) f = 1.0f;
            if (a1->f24 & 0x100000) {
                u8 *o = func_002AB220(a0);
                if (o != 0) o[0x18] = 1;
            } else {
                u8 *o = func_002AB220(a0);
                if (o != 0) o[0x18] = 0;
            }
        }
    }
    return f;
}

