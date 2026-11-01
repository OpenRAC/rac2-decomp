#include "include_asm.h"

#include "common.h"
extern int F3c007b59_FUN_00282978(void *p);
extern void F3c007b59_FUN_002B9180(void *p);
extern unsigned int F3c007b59_FUN_00283CF0(float x);
typedef struct {
    unsigned char pad0[4];
    unsigned int w04;
    unsigned char c08;
    unsigned char c09;
    unsigned char c10;
    unsigned char c11;
    float f12;
    unsigned char pad16[8];
    float f24;
    unsigned char pad28[4];
    float f36;
    float f40;
    float f44;
} OBJ_F3c007b59;

void func_PAL_002BE040(OBJ_F3c007b59 *o)
{
    float *p = (float *)((char *)o + 32);
    float f;
    float y;

    f = p[1] + p[3] * 0.0156000005f;
    p[1] = f;
    if (f <= 0.0f || F3c007b59_FUN_00282978(&o->c10) != 0) {
        F3c007b59_FUN_002B9180(o);
    } else {
        f = p[1];
        if (2.1999999880790710449219e-01f <= f) {
            y = p[3];
            y = -y;
            p[3] = y;
            p[1] = f + y * 0.0156000005f;
        }
        o->f12 = o->f12 + 9828.0f;
        o->w04 = (o->w04 & 0xFFFFFFu) |
                 (F3c007b59_FUN_00283CF0(p[1] * 2.5500000000000000000000e+02f) << 24);
        p[2] = p[2] + 0.014400001f;
        if (p[2] > 1.0f)
            p[2] = p[2] - 1.0f;
        o->c08 = (unsigned char)(p[2] * 2.5500000000000000000000e+02f);
        o->f24 = o->f24 - 1.9999999552965164184570e-02f;
    }
}

