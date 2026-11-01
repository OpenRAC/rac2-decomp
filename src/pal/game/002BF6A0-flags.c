#include "include_asm.h"

#include "common.h"
void func_002B9180(void *);
int func_00282978(short *);

void func_PAL_002C03F0(void *param_1)
{
  int lVar1;

  lVar1 = func_00282978((short *)((char *)param_1 + 10));
  if (lVar1 != 0) {
    func_002B9180(param_1);
  }
  return;
}

extern int func_002A77E0(int);
extern void func_00282CC0(char *, char *, char *);
extern float func_00282E20(void *);
extern void func_00282F70(char *, char *, float);
extern void func_002AA2E8(float *, float, float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float D_001B5358;
extern int func_002A77E0(int);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282CC0(char *, char *, char *);
extern float func_00283198(float);

/* Advances one object: the halfword at offset 10 is capped at 12 and, when the
   sub-object's float at 0x30 is below the object's float at 0x18, the word at
   offset 4 is cleared; the packed byte in that word is then rescaled by the
   halfword, the float at offset 12 grows by 840.0f and is limited by the
   sub-object's float at 0x3C, the object's vector is moved by the sub-object's
   motion triple and the last pair of floats is written back from the angle
   kept in the sub-object. */
void func_PAL_002C05F0(char *self)
{
    char *s1 = self + 0x20;
    float vec[3];
    float f0;
    float f1;
    float f2;
    float f3;
    float g;
    unsigned int a;

    if (func_00282978((short *)(self + 0xA)) != 0) {
        func_002B9180(self);
        return;
    }
    f1 = *(float *)(self + 0x18);
    if (*(float *)(s1 + 0x10) < f1) {
        *(int *)(s1 + 8) = 0;
        if (*(short *)(self + 0xA) >= 11) {
            *(short *)(self + 0xA) = 10;
        }
    }
    if (*(float *)(s1 + 0x10) < *(float *)(self + 0x18) + 1.04f) {
        if (func_002A77E0(20) == 0) {
            if (*(short *)(self + 0xA) >= 11) {
                *(short *)(self + 0xA) = 10;
            }
        }
    }
    if (*(short *)(self + 0xA) < 12) {
        a = *(unsigned int *)(self + 4);
        *(unsigned int *)(self + 4) = (((int)(a >> 24) * (int)*(short *)(self + 0xA) / 12) << 24) | (a & 0xFFFFFF);
    }
    f0 = *(float *)(self + 0xC);
    f0 = f0 + 1008.0001f;
    *(float *)(self + 0xC) = f0;
    f1 = *(float *)(s1 + 0xC);
    if (f1 < f0) {
        *(float *)(self + 0xC) = f1;
    }
    vec[0] = *(float *)(s1 + 0);
    vec[1] = *(float *)(s1 + 4);
    vec[2] = *(float *)(s1 + 8);
    f0 = func_00282E20((void *)vec);
    func_00282F70((char *)vec, (char *)vec, f0 * 0.96400005f);
    func_00282CC0(self + 0x10, self + 0x10, (char *)vec);
    func_002AA2E8(&vec[2], 0.026f, 0.002f);
    *(float *)(s1 + 4) = vec[1];
    *(float *)(s1 + 0) = vec[0];
    *(float *)(s1 + 8) = vec[2];
    f0 = func_00283B98(*(float *)(s1 + 0x14), *(float *)(s1 + 0x18));
    *(float *)(s1 + 0x14) = f0;
    g = func_00283B98(D_001B5358, 1.5707964897155761718750e+00f);
    f3 = func_00283198(*(float *)(s1 + 0x14));
    f2 = f3 * *(float *)(s1 + 0x1C);
    f0 = func_00283180(g);
    vec[0] = f0 * f2;
    vec[1] = func_00283198(g) * f2;
    vec[2] = 0.0f;
    func_00282CC0(self + 0x10, self + 0x10, (char *)vec);
}

typedef struct {
    u8 pos[16];
    s32 kind;
    s32 life;
    f32 z;
    f32 rate;
} Spark2BFB38;
typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
    u32 color;
    u8 f8;
    u8 f9;
    u8 padA[2];
    f32 fC;
    f32 pos[4];
    Spark2BFB38 s;
} Effect2BFB38;
extern u8 *D_001F25CC[];
extern Effect2BFB38 *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);

Effect2BFB38 *func_PAL_002C0838(void *pos, void *dir, s32 kind, s32 life) {
    Effect2BFB38 *e;
    Spark2BFB38 *s;

    e = func_002B9030(0x23);
    if (e != 0) {
        qcopy(e->pos, pos);
        s = &e->s;
        e->color = 0x80808080;
        e->f9 = func_00283CF0(2.0f) + 0x10;
        e->f1 = 0;
        e->f3 = 0x44;
        e->fC = func_002A7878(10500.0f, 16800.0f);
        e->f2 = *D_001F25CC[0];
        qcopy(s->pos, dir);
        s->life = life;
        s->kind = kind;
        s->z = e->pos[2];
        if (kind == 2) {
            s->z = 0;
        }
        s->rate = func_002A7878(0.0042000003f, 0.0072000003f);
    }
    return e;
}
