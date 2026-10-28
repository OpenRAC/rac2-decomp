#include "include_asm.h"
#include "common.h"

/* Qwen draft (branch qwen/autonomy, c8b09022), checked by tools/check.py */
void func_002B9180(void *);

int func_00282978(short *);

extern int func_00282978_9(char *p);

extern void func_002B9180_13(char *self);

extern float func_00283CE0_2(int v);

extern int func_00283CF0_6(float f);

extern void func_00282CC0_17(char *dst, char *src, char *vec);

extern void func_00300190_4(char *dst, char *src);

extern void func_00282D30_12(char *dst, char *table, float scale);

extern char D_0018A0E0_1[];

extern void Fa2a84657_FUN_00282D48(float *tmp, char *v, float k);

extern void Fa2a84657_FUN_00282CD8(float *tmp, char *a, char *v);

extern int Fa2a84657_FUN_00282978(char *field);

extern void Fa2a84657_FUN_002B9180(unsigned char *p);

typedef struct { unsigned int f0, f4, f8, f12, f16, f20; } T;

extern int func_00282978_12(short *);

extern void func_002B9180_19(char *);

extern float func_00283CE0_5(int);

extern int func_00283D38_6(int, int, float);

struct T {
    float a;
    float b;
    int c;
    int d;
    float e;
};

extern void F15a8b7f0_FUN_00282D30(char *first, char *second, float blend);

extern void F15a8b7f0_FUN_00282CC0(char *first, char *second, char *third);

extern void F15a8b7f0_FUN_002B9180(char *object);


extern void func_00282CC0_19(void *out, void *in, void *src);

extern int func_00282978_11(void *p);

extern void func_002B9180_15(void *self);

extern float func_00283CE0_4(int n);

extern int func_00283D38_3(int handle, int previous, float ratio);

extern char D_00189E20_18[];

extern void Fccb147a4_FUN_002B9180(char *a, char *b);

extern void Fccb147a4_FUN_00300190(char *a, char *b);

extern void Fa03721e9_FUN_00282CC0(char *a, char *b, char *c);

extern void Fa03721e9_FUN_002B9180(char *p);


#ifndef RAC2_T_S16_F570CFB4B
#define RAC2_T_S16_F570CFB4B
typedef short s16_F570cfb4b;
#endif

extern void func_002B9180_7(u8 *);


extern int F7cacd225_FUN_00282978(short *p);

extern void F7cacd225_FUN_002B9180(char *o);

extern float F7cacd225_FUN_00283CE0(int n);

extern int F7cacd225_FUN_00283D38(int a, int b, float q);

#ifndef RAC2_T_OBJ_F7CACD225
#define RAC2_T_OBJ_F7CACD225
typedef struct {
    int pad0;
    int f4;
    short pad8;
    short s10;
    float f12;
    float f16;
    float f20;
    float f24;
    int pad28;
    int f32;
} Obj_F7cacd225;
#endif

extern int func_00282978_6(char *);

extern void func_002B9180_10(char *);

extern void func_00282CC0_21(char *, char *, char *);

extern void func_00300190_2(char *, char *);

#ifndef RAC2_T_VEC16_F9A4B4D8B
#define RAC2_T_VEC16_F9A4B4D8B
typedef struct {
    float f[4];
} Vec16_F9a4b4d8b;
#endif

#ifndef RAC2_T_V4_FC3CB9262
#define RAC2_T_V4_FC3CB9262
typedef int V4_Fc3cb9262 __attribute__((mode(TI)));
#endif

extern void Fc3cb9262_FUN_00282CC0(char *a, char *b, char *c);

extern int Fc3cb9262_FUN_00283CF0(float f);

extern int Fc3cb9262_FUN_00282978(char *a);

extern void Fc3cb9262_FUN_002B9180(char *a);

void func_002BF6F0(void *param_1)
{
  int lVar1;

  lVar1 = func_00282978((short *)((char *)param_1 + 10));
  if (lVar1 != 0) {
    func_002B9180(param_1);
  }
  return;
}

/* func_002BF728 uses the quadword-copy profile in 002BF728-qcopy.c. */

extern int func_002A77E0(int);
extern void func_00282CC0(char *, char *, char *);
extern float func_00282E20(void *);
extern void func_00282F70(char *, char *, float);
extern void func_002AA2E8(float *, float, float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float D_001B5358;

/* Advances one object: the halfword at offset 10 is capped at 12 and, when the
   sub-object's float at 0x30 is below the object's float at 0x18, the word at
   offset 4 is cleared; the packed byte in that word is then rescaled by the
   halfword, the float at offset 12 grows by 840.0f and is limited by the
   sub-object's float at 0x3C, the object's vector is moved by the sub-object's
   motion triple and the last pair of floats is written back from the angle
   kept in the sub-object. */
void func_002BF8F0(char *self)
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
        if (*(short *)(self + 0xA) >= 13) {
            *(short *)(self + 0xA) = 12;
        }
    }
    if (*(float *)(s1 + 0x10) < *(float *)(self + 0x18) + 8.6666667461395263671875e-01f) {
        if (func_002A77E0(20) == 0) {
            if (*(short *)(self + 0xA) >= 13) {
                *(short *)(self + 0xA) = 12;
            }
        }
    }
    if (*(short *)(self + 0xA) < 14) {
        a = *(unsigned int *)(self + 4);
        *(unsigned int *)(self + 4) = (((int)(a >> 24) * (int)*(short *)(self + 0xA) / 14) << 24) | (a & 0xFFFFFF);
    }
    f0 = *(float *)(self + 0xC);
    f0 = f0 + 8.4000006103515625000000e+02f;
    *(float *)(self + 0xC) = f0;
    f1 = *(float *)(s1 + 0xC);
    if (f1 < f0) {
        *(float *)(self + 0xC) = f1;
    }
    vec[0] = *(float *)(s1 + 0);
    vec[1] = *(float *)(s1 + 4);
    vec[2] = *(float *)(s1 + 8);
    f0 = func_00282E20((void *)vec);
    func_00282F70((char *)vec, (char *)vec, f0 * 9.7000002861022949218750e-01f);
    func_00282CC0(self + 0x10, self + 0x10, (char *)vec);
    func_002AA2E8(&vec[2], 2.1666666492819786071777e-02f, 1.3888889225199818611145e-03f);
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


extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern void *func_002C19D8(void *, float, void *, float, int);
extern void func_002C3D80(void *, int, float, float);
typedef union { unsigned char b[0x2600]; int i[0x980]; float f[0x980]; } L_BFC50Hero;
extern char D_00189E20[];
extern void *D_001A9E74 __attribute__((section(".sdata")));
extern float D_001BAF80[];
extern char D_001BAFA0[];

void func_002BFC50(char *self)
{
    char *s1 = self + 0x20;
    float vec[4] __attribute__((aligned(16)));
    int state = *(int *)(s1 + 0x10);

    if (state == 0) {
        func_00282CC0(self + 0x10, self + 0x10, s1);
    } else if (state == 1) {
        func_00282CC0((char *)vec, self + 0x10, s1);
        if (func_002761F8(self + 0x10, vec, 2, 0, 0) == 0) {
            goto copy;
        }
        if (func_00278E78() == 0) {
            func_002C19D8(D_001BAFA0, 0.2f, D_001A9E74, 5250.0f, -1);
        }
        func_002B9180(self);
        return;
    } else if (state == 3) {
        func_00282CC0(self + 0x10, self + 0x10, s1);
        if (*(float *)(self + 0x18) < ((L_BFC50Hero *)D_00189E20)->f[0x330 / 4]) {
            void *t = D_001A9E74;

            *(float *)(self + 0x18) = ((L_BFC50Hero *)D_00189E20)->f[0x330 / 4];
            func_002C19D8(self + 0x10, 0.2f, t, 5250.0f, -1);
            func_002B9180(self);
            return;
        }
    } else {
        func_00282CC0((char *)vec, self + 0x10, s1);
        if (func_002761F8(self + 0x10, vec, 2, 0, 0) == 0) {
            goto copy;
        }
        if (func_00278E78() != 0) {
            D_001BAF80[10] = D_001BAF80[10] + 0.05f;
            func_002C3D80(&D_001BAF80[8], -1, 0.25f, 3150.0f);
        }
        func_002B9180(self);
        return;
copy:
        qcopy(self + 0x10, vec);
    }
    *(float *)(s1 + 8) = *(float *)(s1 + 8) - *(float *)(s1 + 0x1C);
    self[8] = self[8] + 2;
    if (--*(int *)(s1 + 0x14) <= 0 || *(float *)(self + 0x18) < *(float *)(s1 + 0x18)) {
        *(int *)(self + 4) = *(int *)(self + 4) - 0x10000000;
        if (*(int *)(self + 4) < 0) {
            func_002B9180(self);
        }
    }
}

/* func_002BFE80 is defined in 002BFE80-dbg.c. */

extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern int func_L00_0031C998(int, int, float);
extern float D_001B5340[];
extern int abs(int);

void func_002BFFE8(char *self)
{
    char *s1 = self + 0x20;
    float vec[4];
    int d;
    float f;

    if (func_00282978((short *)(self + 0xA)) != 0) {
        func_002B9180(self);
        return;
    }
    func_00282CF0(vec, D_001B5340, s1);
    if (func_00282DF0(vec) > 5.0f) {
        func_00282F20(vec, vec, 1.25f);
    } else {
        func_00282D30((char *)vec, (char *)vec, 0.25f);
    }
    func_00282CC0((char *)(self + 0x10), s1, (char *)vec);
    d = abs(*(short *)(self + 0xA) - *(int *)(s1 + 0x14));
    f = (float)(*(int *)(s1 + 0x14) - d) / (float)*(int *)(s1 + 0x14);
    *(int *)(self + 4) = func_L00_0031C998(0, *(int *)(s1 + 0x10), f);
}


/* func_002C01F8 is in 002BF6F0-c01f8-g8.c. */

/* func_002C02F0 uses the quadword-copy profile in 002C02F0-qcopy.c. */

INCLUDE_ASM("asm/game", func_002C04C0);


/* func_002C0CC0 uses the quadword-copy profile in 002C0CC0-qcopy.c. */

INCLUDE_ASM("asm/game", func_002C0E50);


/* Updates one byte-addressed object by packing a converted short-ratio value with three bytes, applying the bound helper sequence to three stored floats, and accumulating one byte and one float. */
void func_002C1840(char *self)
{
    float vec[4];
    float tmp[4];
    char *s1;
    char *p;
    float f20;
    float t;
    unsigned int v;

    if (func_00282978_9(self + 10)) {
        func_002B9180_13(self);
        return;
    }
    s1 = self + 32;
    f20 = func_00283CE0_2(*(short *)(s1 + 30));
    t = func_00283CE0_2(*(short *)(s1 + 28));
    v = func_00283CF0_6(f20 * ((float)*(short *)(self + 10) / t));
    v = v << 24;
    v = v | (*(unsigned char *)(s1 + 19) << 16);
    v = v | (*(unsigned char *)(s1 + 18) << 8);
    v = v | *(unsigned char *)(s1 + 17);
    *(unsigned int *)(self + 4) = v;
    vec[3] = 0.0f;
    vec[0] = *(float *)(self + 32);
    vec[1] = *(float *)(s1 + 4);
    vec[2] = *(float *)(s1 + 8);
    func_00282CC0_17((char *)self + 16, (char *)self + 16, (char *)vec);
    if (*(float *)(self + 28) != 0.0f) {
        if (*(float *)(self + 28) == 2.0f)
            func_00300190_4((char *)self + 16, (char *)self + 16);
        *(float *)(self + 28) = 2.0f;
    }
    p = (char *)tmp;
    func_00282D30_12(p, D_0018A0E0_1, *(float *)(s1 + 12));
    func_00282CC0_17((char *)vec, (char *)vec, p);
    func_00282D30_12((char *)vec, (char *)vec, *(float *)(s1 + 24));
    *(float *)s1 = vec[0];
    *(float *)(s1 + 4) = vec[1];
    *(float *)(s1 + 8) = vec[2];
    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + *(unsigned char *)(s1 + 16);
    *(float *)(self + 12) = *(float *)(self + 12) + *(float *)(s1 + 20);
}

typedef struct {
    float vx;
    float vy;
    int f8;
    int fC;
    float spin;
    void *owner;
} L_C19D8Payload;
typedef struct {
    unsigned char b0, b1, b2, b3;
    int color;
    unsigned char seed, alpha;
    unsigned short size;
    float life;
    float position[4];
    L_C19D8Payload payload;
} L_C19D8Particle;
extern void *func_002B9030(int);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern int func_001163B0(void);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern unsigned char *D_001F25F4;

void *func_002C19D8(void *position, float size, void *owner, float spin, int color)
{
    L_C19D8Particle *p = (L_C19D8Particle *)func_002B9030(0x2D);
    L_C19D8Payload *out;
    float angle;
    float speed;
    int c;

    if (p) {
        qcopy(p->position, position);
        if (color == -1) {
            c = ((func_002A77E0(6) + 0x14) << 24) | 0x808080;
        } else {
            c = color;
        }
        out = &p->payload;
        p->color = c;
        p->alpha = func_00283CF0(1.0f) + 32;
        p->b3 = 0x48;
        p->b1 = 1;
        p->b2 = *D_001F25F4;
        p->seed = func_001163B0();
        p->size = 4;
        p->life = size * 210000.0f;
        angle = func_002A7940();
        speed = func_002A7878(0.0015f, 0.0025f);
        p->payload.vx = func_00283180(angle) * speed;
        out->vy = func_00283198(angle) * speed;
        out->owner = owner;
        out->spin = spin;
        out->f8 = 0;
    }
    return p;
}

/* func_002C1B38 is in the -G8 sibling. */

extern float func_00282C48(float);

void func_002C1C88(char *self)
{
    char *motion = self + 0x20;
    func_00282CC0_17(self + 0x10, self + 0x10, motion);
    *(float *)(self + 0x0C) += 5880.0f;
    *(float *)(motion + 0x14) *= 0.98f;
    *(float *)(motion + 0x10) += *(float *)(motion + 0x14);
    *(unsigned char *)(self + 8) = func_00283CF0_6(*(float *)(motion + 0x10));
    if (*(float **)(motion + 0x18)) {
        if (func_00282C48(*(float *)(self + 0x18) - **(float **)(motion + 0x18)) < 0.2f)
            *(float *)(self + 0x18) = **(float **)(motion + 0x18) + 0.02f;
    }
    if (--*(short *)(self + 0xA) == 0) {
        *(int *)(self + 4) -= 0x01000000;
        *(short *)(self + 0xA) = 1;
    }
    if ((*(unsigned int *)(self + 4) & 0xFF000000) == 0)
        func_002B9180(self);
}

extern void func_00282D30_fa(void *, void *, float);

void func_002C1DB0(char *a0)
{
    char *p = a0;
    char *q = p + 32;
    int v;

    func_00282D30_fa(q, q, 0.975f);
    func_00282CC0(p + 16, p + 16, q);
    *(float *)(p + 12) = *(float *)(p + 12) + 14700.0f;
    *(u8 *)(p + 8) = *(u8 *)(p + 8) + *(u8 *)(q + 16);
    v = *(int *)(p + 4) + 0xFE000000;
    *(int *)(p + 4) = v;
    if (v < 0) {
        func_002B9180(p);
    }
}

extern void func_00282CC0(char *, char *, char *);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern int func_00283D38(int, int, float);

void func_002C1E50(char *obj) {
    char *tail = obj + 0x20;
    obj[8] += tail[0x1C];
    func_00282CC0(obj + 0x10, obj + 0x10, tail);
    *(int *)(obj + 4) = func_00283D38(*(int *)(tail + 0x18), *(int *)(tail + 0x14),
        func_00282C48(func_00283CE0(*(short *)(obj + 0x0A)) * *(float *)(tail + 0x10) - 1.0f));
    if (func_00282978((short *)(obj + 0x0A)) != 0) {
        func_002B9180(obj);
    }
}


/* func_002C1FC0 is defined in 002BF6F0-g8.c. */

void func_002C2080(unsigned char *p)
{
    float tmp[4];
    char *v;
    int n;

    v = (char *)p + 32;
    Fa2a84657_FUN_00282D48(tmp, v, 9.4999998807907104492188e-01f);
    *(float *)(v + 8) = *(float *)(v + 8) + 1.3888889225199818611145e-03f;
    Fa2a84657_FUN_00282CD8(tmp, (char *)p + 16, v);

    n = *(int *)(p + 4) + (int)0xFE000000;
    *(int *)(p + 4) = n;
    if (((unsigned)(n & 0xFF000000) - 1) > 0x5EFFFFFFu || Fa2a84657_FUN_00282978((char *)p + 10) != 0) {
        Fa2a84657_FUN_002B9180(p);
    } else {
        float f0;
        float f1;

        f1 = *(float *)(p + 12);
        f0 = 2.1000000000000000000000e+05f - f1;
        f0 = f0 * 7.0000000298023223876953e-02f;
        f1 = f1 + f0;
        *(float *)(p + 12) = f1;
        p[8] = p[8] + 1;
    }
}

/* Tests the halfword at offset 10 through a helper; on zero it stores a scaled int at offset 4 and a 210000.0f-scaled interpolation of two floats at offset 12, otherwise calls a second helper. */
void func_002C2170(char *p)
{
    if (func_00282978_12((short *)(p + 10)) != 0) {
        func_002B9180_19(p);
    } else {
        struct T *t = (struct T *)(p + 32);
        float k = func_00283CE0_5(*(short *)(p + 10)) * t->e;

        *(int *)(p + 4) = func_00283D38_6(t->d, t->c, k);
        *(float *)(p + 12) = ((t->a - t->b) * k + t->b) * 210000.0f;
    }
}

INCLUDE_ASM("asm/game", func_002C23B8);

extern void func_002C96F8(float, float, void *, int *, float *, void *);

extern int func_00277F48(float, void *, int, int, int);

extern float func_00283CE0(int);

extern int func_002AAE98(float, float, float, float);

#ifndef RAC2_T_VEC16_F5621621C
#define RAC2_T_VEC16_F5621621C
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_F5621621c;
#endif

extern void func_002A9850(void *a0, Vec16_F5621621c *src, int *p, int n, int t0, int t1, int t2, int t3, float f1, float f2, float f3);

extern int D_001BF000[];

/* Updates one object: it copies its vector into a local, adds the two motion
   floats and hands the result with the motion's third float to a helper, then
   bails out through the second helper when the halfword at offset 10 is
   taken. Otherwise it packs a colour from the halfword and pushes the object
   through a vector helper with the table at D_001BF000. The two words the
   first helper writes (n and f) are the retail's scratch out-parameters: it
   never reads them back. The words at offsets 0x20 and 0x34 are 32-bit in the
   object and the helpers take them as pointers, so they are cast on the way
   out. */
void func_002C2658(char *obj)
{
    char *motion = obj + 0x20;
    char *vec = obj + 0x10;
    V4_Fc3cb9262 local[2];
    int n;
    float f;
    int count;

    local[0] = *(V4_Fc3cb9262 *)(obj + 0x10);
    *(float *)(motion + 4) = *(float *)(motion + 4) + *(float *)(motion + 8);
    func_002C96F8(*(float *)(motion + 4), *(float *)(motion + 0xC),
                  (void *)*(int *)(obj + 0x20), &n, &f, vec);

    if (func_00282978((short *)(obj + 0xA)) != 0) {
        func_002B9180(obj);
        return;
    }

    {
        int index = *(short *)(obj + 0xA);

        if ((float)index < 7.5f)
            *(int *)(obj + 4) = func_002AAE98(0.7f, 0.7f, 0.7f,
                                             func_00283CE0(index) * 0.0106666666f);
    }

    count = func_00277F48(0.15f, vec, 16, *(int *)(motion + 0x14), 0);
    local[1] = *(V4_Fc3cb9262 *)(obj + 0x10);
    func_002A9850((void *)*(int *)(motion + 0x14), (Vec16_F5621621c *)&local[1],
                   D_001BF000, count, 0, 0x810001, 2, 1, 2.0f, 1.0f, 1.0f);
}


void func_002C28F8(char *object)
{
    int count;
    int low;
    int high;

    F15a8b7f0_FUN_00282D30(object + 32, object + 32, 0.975f);
    F15a8b7f0_FUN_00282CC0(object + 16, object + 16, object + 32);
    *(float *)(object + 12) += 6300.0f;
    count = *(unsigned char *)(object + 4) - 4;
    if (count <= 0)
        F15a8b7f0_FUN_002B9180(object);
    else {
        low = (count << 8) | 0x60000000;
        high = (count << 16) | low;
        *(int *)(object + 4) = high | count;
    }
}

extern int func_00283CF0(float);

/* A drifting spark: moves by its velocity, spins, slows its fall and fades over its last
   64 frames; it frees itself when the count runs out. */
void func_002C29A0(char *p)
{
    char *vel = p + 0x20;

    func_00282CC0(p + 0x10, p + 0x10, vel);
    *(float *)(p + 0xC) += 5880.0f;
    *(float *)(vel + 0x14) *= 0.98f;
    *(float *)(vel + 0x10) += *(float *)(vel + 0x14);
    p[8] = func_00283CF0(*(float *)(vel + 0x10));
    if (--*(short *)(p + 0xA) <= 0)
        func_002B9180(p);
    if (*(short *)(p + 0xA) > 0x40)
        *(int *)(p + 4) = ((0x80 - *(short *)(p + 0xA)) << 24) | 0x808080;
    else
        *(int *)(p + 4) = (*(short *)(p + 0xA) << 24) | 0x808080;
}

/* func_002C2A88 uses the quadword-copy profile in 002C2A88-qcopy.c. */

INCLUDE_ASM("asm/game", func_002C2C80);


extern unsigned char *r1_func_00218928(int);
extern int r1_func_001FA898(float);
extern void r1_func_001F9BF0(void *, void *, void *);
extern char D_00189EA0[];
extern unsigned char *r1_D_L00_001B2400[];


/* rac1-decomp src/overlays/shared/alpha_fade_particle_updates.c: func_002C2FD8 */
/* spawns particle type 0x3B from a position, colour index and flags */
unsigned char *func_002C2FD8(float f, void *pos, int a1, unsigned char a2, int idx, int flag, int s, int mode) {
    unsigned char *r = r1_func_00218928(0x3B);
    if (r != 0) {
        char *v = (char *)r + 0x20;
        *(int *)(v + 0x10) = mode;
        if (mode == 1) {
            r1_func_001F9BF0(v, pos, D_00189EA0);
        }
        qcopy(r + 0x10, pos);
        *(int *)(r + 4) = a1;
        r[9] = r1_func_001FA898(1.0f) + 0x20;
        if (flag != 0) {
            r[3] = 0x44;
        } else {
            r[3] = 0x48;
        }
        r[8] = a2;
        r[1] = 0;
        *(float *)(r + 0xC) = f * 210000.0f;
        r[2] = *r1_D_L00_001B2400[idx];
        *(short *)(r + 0xA) = s;
    }
    return r;
}

extern void func_00282CC0(char *, char *, char *);

void func_002C30F8(char *self)
{
    char *part = self + 0x20;
    if (*(int *)(part + 0x10) == 1)
        func_00282CC0(self + 0x10, D_00189EA0, part);
    if (func_00282978((short *)(self + 0xA)) != 0)
        func_002B9180(self);
}

/* func_002C3150 uses the quadword-copy profile in 002C3150-qcopy.c. */

/* advances three floats of a sub-object by a resident offset triple, calls a three-pointer update, subtracts the offsets back out, rejects the result when any coordinate leaves the 2.0..1021.0 band, and otherwise rescales a 24-bit handle by the ratio of two helper lookups over a signed halfword index */
void func_002C3280(u8 *self)
{
    char *s2 = (char *)self + 32;
    int n;
    float a;

    if (*(int *)(s2 + 28) == 1) {
        char *base = D_00189E20_18;
        *(float *)(self + 16) = *(float *)(base + 128) + *(float *)(s2 + 16);
        *(float *)(self + 20) = *(float *)(base + 132) + *(float *)(s2 + 20);
        *(float *)(self + 24) = *(float *)(base + 136) + *(float *)(s2 + 24);
        func_00282CC0_19(self + 16, self + 16, s2);
        *(float *)(s2 + 16) = *(float *)(self + 16) - *(float *)(base + 128);
        *(float *)(s2 + 20) = *(float *)(self + 20) - *(float *)(base + 132);
        *(float *)(s2 + 24) = *(float *)(self + 24) - *(float *)(base + 136);
    } else {
        func_00282CC0_19(self + 16, self + 16, s2);
    }

    if (*(float *)(self + 16) < 2.0f || *(float *)(self + 16) > 1021.0f
        || *(float *)(self + 20) < 2.0f || *(float *)(self + 20) > 1021.0f
        || *(float *)(self + 24) < 2.0f || *(float *)(self + 24) > 1021.0f) {
        func_002B9180_15(self);
        return;
    }

    if (func_00282978_11((char *)self + 10) != 0) {
        func_002B9180_15(self);
        return;
    }

    n = *(int *)(self + 4) & 0xFFFFFF;
    a = func_00283CE0_4(*(short *)(self + 10) - 1);
    /* One statement: retail has no line label between the second call and the
       division, so no division padding (docs/COMPILER-NOTES.md). */
    *(int *)(self + 4) = func_00283D38_3(n, *(int *)(self + 4), a / func_00283CE0_4(*(short *)(self + 10)));
}

INCLUDE_ASM("asm/game", func_002C3430);

void func_002C37E0(char *obj)
{
    char *sub = obj + 32;
    int w;
    int n;

    switch (*(unsigned char *)(sub + 2)) {
    case 2:
        *(float *)(obj + 16) = *(float *)(*(char **)(sub + 4) + 16) + *(float *)(sub + 16);
        *(float *)(obj + 20) = *(float *)(*(char **)(sub + 4) + 20) + *(float *)(sub + 20);
        *(float *)(obj + 24) = *(float *)(*(char **)(sub + 4) + 24) + *(float *)(sub + 24);
        break;
    case 1:
        goto tail;
    }
    w = *(int *)(obj + 4);
    n = (w >> 24);
    n = n - *(short *)(obj + 32);
    if (n <= 0) {
        Fccb147a4_FUN_002B9180(obj, sub);
        return;
    }
    *(int *)(obj + 4) = (w & 0xffffff) | (n << 24);
tail:
    if (*(unsigned char *)(sub + 3) != 0) {
        obj += 16;
        Fccb147a4_FUN_00300190(obj, obj);
    }
}


/* func_002C38E0 is in the -G8 sibling. */

INCLUDE_ASM("asm/game", func_002C3B08);

/* func_002C3D80 uses the quadword-copy profile in 002C3D80-qcopy.c. */

void func_002C3EE8(char *p)
{
    char *q = p + 32;

    Fa03721e9_FUN_00282CC0(p + 16, p + 16, q);
    *(float *)(p + 12) = *(float *)(p + 12) + *(float *)(q + 16);
    *(unsigned char *)(p + 8) = *(unsigned char *)(p + 8) + 1;
    if (--*(short *)(p + 10) == 0) {
        *(unsigned int *)(p + 4) = *(unsigned int *)(p + 4) + 0xff000000;
        *(short *)(p + 10) = 2;
    }
    if ((*(unsigned int *)(p + 4) & 0xff000000) == 0)
        Fa03721e9_FUN_002B9180(p);
}

/* func_002C3F88 uses the quadword-copy profile in 002C3F88-qcopy.c. */

INCLUDE_ASM("asm/game", func_002C4100);


INCLUDE_ASM("asm/game", func_002C4500);

/* decrements a signed short counter and, at zero, rotates a 24-bit identifier beside it and reloads the counter; calls a helper when the identifier's top byte is clear */
void func_002C4788(u8 *a0) {
    s16_F570cfb4b *p = (s16_F570cfb4b *)(a0 + 10);
    if (--*p == 0) {
        *(s32 *)(a0 + 4) += 0xff000000;
        *p = 2;
    }
    if ((*(s32 *)(a0 + 4) & 0xff000000) == 0) {
        func_002B9180_7(a0);
    }
}

INCLUDE_ASM("asm/game", func_002C47E8);

void func_002C4B10(u8 *a0)
{
    f32 value = *(f32 *)(a0 + 0x0C);
    *(u8 *)(a0 + 0x08) = *(u8 *)(a0 + 0x08) + *(u8 *)(a0 + 0x38);
    if (value <= 0.0f) {
        *(f32 *)(a0 + 0x0C) = 0.0f;
        func_002B9180(a0);
    }
}

/* func_002C4B50 is in 002BF6F0-c4b50.c. */

INCLUDE_ASM("asm/game", func_002C4D18);

void func_002C4F08(char *self)
{
    char *motion = self + 0x20;
    float len;
    float f;

    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + *(unsigned char *)(motion + 0x12);
    func_00282CC0_17(self + 0x10, self + 0x10, motion);
    *(float *)(motion + 8) = *(float *)(motion + 8) - 3.0000000260770320892334e-03f;
    len = func_00282E20(motion);
    /* Preserve both retail operations: floating-point rounding means subtracting
       and adding 1.0f cannot generally be simplified away. */
    f = len * 9.7000002861022949218750e-01f - 1.0f + 1.0f;
    f = f / len;
    *(float *)(self + 0x20) = *(float *)(self + 0x20) * f;
    *(float *)(motion + 4) = *(float *)(motion + 4) * f;
    if (func_00282978((short *)(self + 0xA)) == 0) {
        f = *(float *)(self + 0xC) + *(float *)(motion + 0x14) * 2.0f;
        *(float *)(self + 0xC) = f;
        if (f < 15000.0f)
            *(float *)(self + 0xC) = 15000.0f;
    } else {
        if (func_002A8860(self + 4, *(int *)(motion + 0x1C)) != 0) {
            *(int *)(self + 0xC) = 0;
            func_002B9180(self);
        }
    }
}


extern float func_00283CE0_2(int v);
extern int func_00283CF0_6(float f);
extern void func_00282CC0_17(char *dst, char *src, char *vec);
extern int func_00282978_9(char *p);
extern void func_002B9180_13(char *self);


/* The particle update: the quad at 0x20 is copied to the stack, the value of
   the helper at 0xA is divided by the copy's fourth float, the two scaled
   results are packed into the word at 4 and the byte at 8. */
void func_002C5068(char *self)
{
    V4_Fc3cb9262 vec;
    float f3;
    float f21;
    int v;

    vec = *(V4_Fc3cb9262 *)(self + 0x20);
    f3 = ((float *)&vec)[3];
    ((float *)&vec)[3] = 0.0f;
    f21 = func_00283CE0_2(*(short *)(self + 0xA)) / f3;
    v = func_00283CF0_6(f21 * 38.0f);
    *(int *)(self + 4) = (v << 24) | 0x808080;
    v = func_00283CF0_6(f21 * 33.0f);
    *(char *)(self + 8) = (char)v;
    func_00282CC0_17(self + 0x10, self + 0x10, (char *)&vec);
    if (func_00282978_9(self + 0xA) != 0) {
        func_002B9180_13(self);
    }
}

INCLUDE_ASM("asm/game", func_002C5120);


void func_002C5550(Obj_F7cacd225 *o)
{
    int v;

    if (o->f16 < 2.0f || o->f16 > 1021.0f ||
        o->f20 < 2.0f || o->f20 > 1021.0f ||
        o->f24 < 2.0f || o->f24 > 1021.0f ||
        F7cacd225_FUN_00282978(&o->s10) != 0) {
        F7cacd225_FUN_002B9180((char *)o);
        return;
    }
    v = o->f32;
    if (v != 0) {
        o->f12 = o->f12 * 0.99f;
        o->f4 = F7cacd225_FUN_00283D38(0x30FFFFFF, o->f4, F7cacd225_FUN_00283CE0(o->s10 - 1) / F7cacd225_FUN_00283CE0(o->s10));
    } else {
        o->f12 = o->f12 * 0.95f;
        o->f4 = F7cacd225_FUN_00283D38(0x603F1008, o->f4, F7cacd225_FUN_00283CE0(o->s10 - 1) / F7cacd225_FUN_00283CE0(o->s10));
    }
}

/* func_002C56B0 uses the quadword-copy profile in 002C56B0-qcopy.c. */

INCLUDE_ASM("asm/game", func_002C58A8);

/* func_002C5B70 uses the quadword-copy profile in 002C5B70-qcopy.c. */

INCLUDE_ASM("asm/game", func_002C5D00);

/* func_002C6360 is in the -G8 sibling (its two globals are read through $gp). */

extern float func_00283198(float);
extern int func_00283CF0(float);

void func_002C64D8(char *s1)
{
    float f20;
    float t;
    char *s0;

    if (s1 == 0)
        return;
    s0 = s1 + 0x20;
    if (func_00282978((short *)(s1 + 0x24)) != 0) {
        func_002B9180(s1);
        return;
    }
    f20 = func_00283CE0(*(short *)(s0 + 4)) / func_00283CE0(*(short *)(s0 + 6));
    t = func_00283198(f20 * 6.283186f);
    *(int *)(s1 + 4) = (*(int *)(s1 + 4) & 0x00FFFFFF)
                       + (func_00283CF0(func_00282C48(func_00283CE0(*(int *)(s0 + 0xC)) * t)) << 24);
}

/* func_002C65A0 is in 002BF6F0-c65a0.c. */

/* If a probe call on a sub-object returns zero, folds a byte counter into the top byte of a packed word, rebuilds a 16-byte vector from two sub-records for a helper, then clamps a running float against a limit and accumulates two sub-record fields into the object. */
void func_002C6748(char *obj)
{
    Vec16_F9a4b4d8b local;
    char *s1;
    char *s2;
    int a;
    int v1;

    if (func_00282978_6(obj + 10) != 0) {
        func_002B9180_10(obj);
        return;
    }

    a = *(int *)(obj + 4);
    s1 = obj + 32;
    *(int *)(obj + 4) = (a & 0x00ffffff) | (((a >> 24) + *(unsigned char *)(s1 + 20)) << 24);

    s2 = obj + 16;
    local.f[0] = *(float *)(obj + 32);
    local.f[1] = *(float *)(s1 + 4);
    local.f[2] = *(float *)(s1 + 8);
    local.f[3] = 0.0f;
    func_00282CC0_21(s2, s2, (char *)&local);

    *(float *)(s1 + 8) = *(float *)(s1 + 8) - *(float *)(s1 + 12);

    if (*(float *)(obj + 28) != 0.0f) {
        if (*(float *)(obj + 28) == 2.0f)
            func_00300190_2(s2, s2);
        *(float *)(obj + 28) = 2.0f;
    }
    v1 = *(unsigned char *)(s1 + 21);

    *(unsigned char *)(obj + 8) = *(unsigned char *)(obj + 8) + v1;
    *(float *)(obj + 12) += *(float *)(s1 + 16);
}

typedef struct {
    int *colors;
    short *sizes;
    short *times;
    short last_index;
    short reserved0E;
    short lifetime;
    short reserved12;
    float scale;
} ParticleKeyframes;
extern int func_002A9568(int, int, float);

void func_002C6868(char *self)
{
    char *motion = self + 0x20;
    ParticleKeyframes *control = *(ParticleKeyframes **)(motion + 0x10);
    short elapsed;
    float duration, factor;
    func_00282D30_12(motion, motion, (control->scale - 1.0f) + 1.0f);
    func_00282CC0_17(self + 0x10, self + 0x10, motion);
    *(unsigned char *)(self + 8) += *(unsigned char *)(motion + 0x18);
    elapsed = control->lifetime - *(short *)(self + 0xA);
    if (control->times[*(short *)(motion + 0x14) + 1] < elapsed &&
        *(short *)(motion + 0x14) < control->last_index)
        ++*(short *)(motion + 0x14);
    duration = func_00283CE0_2(control->times[*(short *)(motion + 0x14) + 1] -
        control->times[*(short *)(motion + 0x14)]);
    factor = (float)(elapsed -
        control->times[*(short *)(motion + 0x14)]) / duration;
    *(int *)(self + 4) = func_002A9568(
        control->colors[*(short *)(motion + 0x14)],
        control->colors[*(short *)(motion + 0x14) + 1], factor);
    *(float *)(self + 0xC) =
        ((float)control->sizes[*(short *)(motion + 0x14)] +
         factor * (float)(control->sizes[*(short *)(motion + 0x14) + 1] - control->sizes[*(short *)(motion + 0x14)])) * 1000.0f;
    if (func_00282978((short *)(self + 0xA)))
        func_002B9180(self);
}

/* Follows a sound emitter's moby: fades its volume byte (the top byte of +4) up by 4
   toward the target while the moby is visible and active, else down by 4 to zero,
   then places the emitter at the moby (or at its joint, pulled 0.4 of the way toward
   the camera). A dead or dying moby (state 0xFE/0xFD) or none lets the emitter finish
   and frees it. */
typedef int TI128_2C6A08 __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[0x10];
    float pos[4];
    unsigned char state;
    unsigned char pad21[0x10];
    unsigned char visible;
    unsigned char pad32[2];
    unsigned short flags;
} EmitterMoby2C6A08;
typedef struct {
    EmitterMoby2C6A08 *moby;
    unsigned char pad4[2];
    short joint;
    unsigned char pad8[3];
    signed char target;
} EmitterRef2C6A08;
typedef struct {
    unsigned char pad0[4];
    int packed;
    unsigned char ticks;
    unsigned char pad9[7];
    float pos[4];
    EmitterRef2C6A08 ref;
} Emitter2C6A08;
extern float D_001B5340[];
extern int func_002A8860(void *, int);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

void func_002C6A08(Emitter2C6A08 *emitter)
{
    float joint[4];
    float toward[4];
    EmitterMoby2C6A08 *moby;
    int level;
    int target;
    EmitterRef2C6A08 *ref;

    if (emitter == 0)
        return;
    emitter->ticks++;
    ref = &emitter->ref;
    moby = ref->moby;
    if (moby == 0 || moby->state == 0xFE || moby->state == 0xFD) {
        if (func_002A8860(&emitter->packed, 4) != 0)
            func_002B9180(emitter);
        return;
    }
    level = emitter->packed >> 24;
    target = ref->target;
    if (moby->visible != 0 && !(moby->flags & 2)) {
        if (level < target) {
            level += 4;
            if (target < level)
                level = target;
        }
    } else {
        level -= 4;
        if (level < 0)
            level = 0;
    }
    emitter->packed = (emitter->packed & 0xFFFFFF) | (level << 24);
    if (ref->joint == -1) {
        qcopy(emitter->pos, ref->moby->pos);
        return;
    }
    func_0029FCC0(ref->moby, ref->joint, joint);
    func_00282CF0(toward, D_001B5340, joint);
    func_00282F20(toward, toward, 0.4f);
    func_00282CC0((char *)emitter->pos, (char *)joint, (char *)toward);
}

INCLUDE_ASM("asm/game", func_002C6B68);

INCLUDE_ASM("asm/game", func_002C6DD8);


INCLUDE_ASM("asm/game", func_002C7050);

INCLUDE_ASM("asm/game", func_002C72A0);

void func_002C7538(char *a0)
{
    V4_Fc3cb9262 buf;
    char *s0 = a0 + 32;
    float f0;
    float f1;
    float f2;

    f1 = *(float *)(s0 + 16) + 1.0000000474974513053894e-03f;
    f2 = *(float *)(s0 + 8) - 3.0000000260770320892334e-03f;
    *(float *)(s0 + 16) = f1;
    *(float *)(s0 + 8) = f2;
    f0 = *(float *)(s0 + 20) * f1 * 2.1000000000000000000000e+05f;
    buf = *(V4_Fc3cb9262 *)s0;
    *(float *)(a0 + 12) = f0;
    Fc3cb9262_FUN_00282CC0(a0 + 16, a0 + 16, (char *)&buf);
    *(int *)(a0 + 4) = (Fc3cb9262_FUN_00283CF0((float)*(short *)(a0 + 10)) << 24) | 0x00FFD2D2;
    *(unsigned char *)(a0 + 8) = *(unsigned char *)(a0 + 8) + *(unsigned char *)(s0 + 24);
    if (Fc3cb9262_FUN_00282978(a0 + 10) != 0)
        Fc3cb9262_FUN_002B9180(a0);
}
