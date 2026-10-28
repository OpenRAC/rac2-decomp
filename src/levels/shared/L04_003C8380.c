#include "common.h"
extern float func_00283CE0(int);
extern char *D_L04_001FE340[];
extern void func_002C96F8(void *, void *, void *, void *, float, float);
extern void func_002A05A8(void *);

#include "include_asm.h"

extern int func_002A9640(unsigned char *a0, int a1, int a2);

extern void func_002AB800(unsigned char *a0, unsigned char *a1);

extern void func_002AB8C0(unsigned char *a0, unsigned char *a1);

extern void *func_0029EFD0(void *a0);

extern void func_002A0F48(void *a0);

extern int func_002A8508(void *a0, int a1);

extern int func_002A77E0(int a0);

extern void func_L04_003F9078(unsigned char *a0);

#ifndef RAC2_T_Q16_B0E5D8F83
#define RAC2_T_Q16_B0E5D8F83
typedef int Q16_B0e5d8f83 __attribute__((mode(TI)));
#endif

INCLUDE_ASM("asm/levels", func_L04_003C8380);

extern char D_L04_001B9680[];
extern void func_00282F20(char *, char *, float);
extern float func_002A7878_range(float, float) __asm__("func_002A7878");
extern float func_002A78D8(float, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int func_00283CF0(float);
extern void func_00282CF0(void *, void *, void *);

/* Emits paired particles with opposite spin and randomized velocities. */
void func_L04_003E5830(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    func_00282CF0(direction, (float *)D_L04_001B9680, pos);
    func_00282F20((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878_range(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (!sign) sign--;
        angle = func_002A7878_range(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        func_00282F20((char *)velocity, (char *)velocity, func_002A7878_range(0.05f, 3.0f) * 0.0166666675f);
        velocity[2] = func_002A7878_range(1.0f, 5.0f) * 0.0166666675f;
        func_00282CC0(origin, pos, offset);
        pos[0] += func_002A78D8(0, 0.15f);
        pos[1] += func_002A78D8(0, 0.15f);
        pos[2] += func_002A78D8(0, 0.15f);
        particle = func_002C2210(origin, 60, size * 0.1f, size, 0x80CA00CB, 0, sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
        particle = func_002C2210(origin, 60, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}


void *func_L04_003E5E40(unsigned char *a0, void *a1, float f12) {
    unsigned char *obj = func_0029EFD0(a1);

    if (obj != 0) {
        obj[0x30] = 0xFF;
        obj[0x31] = 1;
        *(unsigned short *)(obj + 0x32) = 0xFF;
        obj[0x20] = 0;
        *(float *)(obj + 0x2C) = *(float *)(*(unsigned char **)(obj + 0x24) + 0x24) * f12;
        *(Q16_B0e5d8f83 *)(obj + 0x10) = *(Q16_B0e5d8f83 *)(a0 + 0x10);
        *(Q16_B0e5d8f83 *)(obj + 0xF0) = *(Q16_B0e5d8f83 *)(a0 + 0xF0);
        obj[0x62] = 1;
        func_002A0F48(obj);
    }
    return obj;
}

INCLUDE_ASM("asm/levels", func_L04_003EDD40);

void func_L04_003EDF80(unsigned char *a0, unsigned char *a1) {
    if (func_002A9640(a0, 0x10000, 0) != 0) {
        a0[0x20] = 2;
        a1[0x57] = 0x78;
        func_002AB800(a0, a1 + 0x50);
    }
    a0[0xA8] = 0xFF;
    func_002AB8C0(a0, a1 + 0x50);
}

/* Stamps byte 0x81 from the per-record lookup, then walks the twenty slots: a slot whose
   object is live (not in either harness state) without the 0xB66 mark raises the count,
   every other slot is remembered in the returned index (-1 when all twenty pass). */
int func_L04_003EDFF0(unsigned char *a0, char *a1)
{
    char *s0 = a1;
    int i;
    int last = -1;

    *(unsigned char *)(s0 + 0x81) = func_002A8508(*(void **)(s0 + 0x84), -1);
    for (i = 0; i < 20; i++) {
        char *e = *(char **)(s0 + 0xA0 + i * 4);

        if (e != 0 && *(short *)(e + 0xAA) == 0xB66
            && *(unsigned char *)(e + 0x20) != 0xFE
            && *(unsigned char *)(e + 0x20) != 0xFD) {
            *(unsigned char *)(s0 + 0x81) = *(unsigned char *)(s0 + 0x81) + 1;
        } else {
            last = i;
        }
    }
    return last;
}

INCLUDE_ASM("asm/levels", func_L04_003EE090);



void func_L04_003F5F30(unsigned char *a0) {
    unsigned char *obj = *(unsigned char **)(a0 + 0x68);
    float *p;
    unsigned int *q;
    unsigned int v;
    int i;
    int j;

    p = (float *)(obj + 0x14);
    for (i = 3; i >= 0; i--) {
        *p++ = (float)func_002A77E0(0xFF);
    }
    *(float *)(obj + 0x24) = -1.0f;
    *(float *)(obj + 0x28) = -2.25f;
    *(float *)(obj + 0x2C) = 1.25f;
    *(float *)(obj + 0x30) = 2.5f;
    j = 3;
    q = (unsigned int *)(obj + 0x40);
    v = 0xFF;
    for (; j >= 0; j--) {
        *q = v;
        q--;
        v -= 0x40;
    }
    *(float *)(obj + 0x44) = 2.0f;
    *(float *)(obj + 0x48) = 2.5f;
    *(float *)(obj + 0x4C) = 2.5f;
    *(float *)(obj + 0x50) = 2.0f;
}


void func_L04_003F8FA0(unsigned char *a0) {
    unsigned char *obj = *(unsigned char **)(a0 + 0x68);
    float *p;
    unsigned int *q;
    unsigned int v;
    int i;
    int j;

    p = (float *)(obj + 0x10);
    for (i = 3; i >= 0; i--) {
        *p++ = (float)func_002A77E0(0xFF);
    }
    *(float *)(obj + 0x20) = -1.0f;
    *(float *)(obj + 0x24) = -2.25f;
    *(float *)(obj + 0x28) = 1.25f;
    *(float *)(obj + 0x2C) = 2.5f;
    j = 3;
    q = (unsigned int *)(obj + 0x3C);
    v = 0xFF;
    for (; j >= 0; j--) {
        *q = v;
        q--;
        v -= 0x40;
    }
    *(float *)(obj + 0x40) = 2.0f;
    *(float *)(obj + 0x44) = 2.5f;
    *(float *)(obj + 0x48) = 2.5f;
    *(float *)(obj + 0x4C) = 2.0f;
}


INCLUDE_ASM("asm/levels", func_L04_003F9320);

INCLUDE_ASM("asm/levels", func_L04_003F9718);

INCLUDE_ASM("asm/levels", func_L04_003F9C60);

INCLUDE_ASM("asm/levels", func_L04_003F9ED0);

/* func_L04_003FA350 is defined in L04_003FA350.c. */

INCLUDE_ASM("asm/levels", func_L04_003FA5A8);

INCLUDE_ASM("asm/levels", func_L04_003FA7E0);

INCLUDE_ASM("asm/levels", func_L04_003FB990);

/* func_L04_003FBD80 is in the sibling file L04_003C8380-g8.c (it stores through $gp). */

INCLUDE_ASM("asm/levels", func_L04_003FBEF8);

typedef struct {
    unsigned char pad0[0x74];
    unsigned char active;
    unsigned char pad75[0x88 - 0x75];
    void *owner;
} L04_C678Slot;
typedef int L04_C678Quad __attribute__((mode(TI)));

typedef struct {
    unsigned char pad0[0x74];
    unsigned char *owner;
    int timer;
    float age;
} L04_C678Vars;

extern int func_00282948(void *);
extern int func_00283CF0(float);
extern void func_0029F338(void *);
extern float func_002AA800(void *, int, float, float);
extern void func_002E59F8(int);
extern void func_L00_002E6DB8(void *, void *);
extern void func_L04_003FB990(unsigned char *, L04_C678Vars *);
extern void func_L04_003FBEF8(void);
extern unsigned char D_00188660[];
extern int D_L04_001B0488 __attribute__((sda));

void func_L04_003FC678(unsigned char *m)
{
    L04_C678Vars *v = *(L04_C678Vars **)(m + 0x68);
    int s;
    L04_C678Slot *e;

    *(L04_C678Quad *)(m + 0x10) = *(L04_C678Quad *)(v->owner + 0x10);
    func_002AA800(m + 0xF8, 0, *(float *)(v->owner + 0xF8), 0.026179943f);
    v->age = v->age + 1.0f;
    if (v->timer != 0 && func_00282948(&v->timer) != 0) {
        s = D_L04_001B0488;
        if (s != -1) {
            e = (L04_C678Slot *)(D_00188660 + s * 0x70);
            if (e->owner == v->owner && e->active != 0) {
                func_002E59F8(s);
            }
        }
        D_L04_001B0488 = -1;
        func_0029F338(m);
        return;
    }
    if (30.0f < v->age && v->timer == 0) {
        v->timer = func_00283CF0(15.0f);
    } else {
        func_L04_003FB990(m, v);
    }
    func_L00_002E6DB8(func_L04_003FBEF8, m);
}

void *func_L04_00400A18(unsigned char *a0, void *a1, float f12) {
    unsigned char *obj = func_0029EFD0(a1);

    if (obj != 0) {
        obj[0x30] = 0xFF;
        *(unsigned short *)(obj + 0x32) = 0xFF;
        obj[0x31] = 1;
        obj[0x20] = 0;
        *(float *)(obj + 0x2C) = *(float *)(*(unsigned char **)(obj + 0x24) + 0x24) * f12;
        *(Q16_B0e5d8f83 *)(obj + 0x10) = *(Q16_B0e5d8f83 *)(a0 + 0x10);
        *(Q16_B0e5d8f83 *)(obj + 0xF0) = *(Q16_B0e5d8f83 *)(a0 + 0xF0);
        func_002A0F48(obj);
    }
    return obj;
}

INCLUDE_ASM("asm/levels", func_L04_00400AB0);

INCLUDE_ASM("asm/levels", func_L04_00400D48);

typedef union { Q16_B0e5d8f83 q; float f[4]; } EffectVector;
typedef struct { EffectVector row[4]; } EffectMatrix4;
extern int func_002A8600(unsigned char **, int, int, int);
extern int func_002A86E8(unsigned char **, unsigned char *, int, int);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00283388(void *);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern float func_00282C48(float);
extern int func_002E5CF8(int, int, char *);
extern float func_002AA2E8(float *, float, float);
extern int func_00282978(short *);

/* Blend the nearby pressure-surface contact using a full64-byte inverse matrix. */
void func_L04_004027B0(unsigned char *object, unsigned char *state) {
    EffectVector delta;
    EffectMatrix4 inverse;
    unsigned char *nearby;
    unsigned char *contact;
    int kind;
    float distance;
    if (*(int *)(state + 0x80) == -1) return;
    func_002A8600(&nearby, *(int *)(state + 0x80), 0, 0);
    while (nearby) {
        kind = *(short *)(nearby + 0xAA);
        if (kind == 0x474 || kind == 0xCEF) {
            func_00282CF0(&delta, nearby + 0x10, object + 0x10);
            distance = func_00282DB0(&delta, &delta);
            if (!(20.0f < distance)) {
                func_00283388(&inverse);
                func_00283698(&inverse, nearby + 0xC0);
                func_002830C0(&delta, &delta, &inverse);
                if (func_00282C48(delta.f[0]) < 2.8f && func_00282C48(delta.f[1]) < 1.25f && func_00282C48(delta.f[2]) < 1.5f) {
                    contact = *(unsigned char **)(nearby + 0x68);
                    if (*(short *)(state + 0x140) == 0 && (*(unsigned char **)(state + 0x164))[0x20] != 3)
                        func_002E5CF8(0, 0, (char *)nearby);
                    *(unsigned short *)(state + 0x140) = *(unsigned short *)contact;
                }
            }
        }
        func_002A86E8(&nearby, nearby, 0, 0);
    }
    if (*(short *)(state + 0x140) != 0) {
        *(short *)(state + 0x142) = 1;
        func_002AA2E8((float *)(state + 0x13C), 0.10000000894069672f, 0.0055555556900799274f);
        if (*(short *)(state + 0x140)) func_00282978((short *)(state + 0x140));
    } else {
        *(short *)(state + 0x142) = 0;
        func_002AA2E8((float *)(state + 0x13C), 0.0f, 0.002777777845039964f);
    }
}

void func_L04_004029D8(unsigned char *m) {
    unsigned char *s = *(unsigned char **)(m + 0x68);
    float f;
    unsigned char *o;
    s[0xA2] = s[0x9C];
    *(Q16_B0e5d8f83 *)(m+0x10) = *(Q16_B0e5d8f83 *)(s+0xB0);
    *(Q16_B0e5d8f83 *)(m+0xF0) = *(Q16_B0e5d8f83 *)(s+0xC0);
    s[0xA0] = 0;
    f = func_00283CE0(s[0xA2]-1);
    *(float *)(s+0x134) = 0.36916667222976685f - f * 0.011666666716337204f - (1.0f - (float)*(int *)(s+0x1A8)*0.1f)*0.03333333507180214f;
    *(int *)(s+0x138)=0;
    *(int *)(s+0x158)=0;
    *(int *)(s+0x13C)=0;
    *(short *)(s+0x142)=0;
    *(short *)(s+0x140)=0;
    *(int *)(s+0x160)=0;
    *(int *)(s+0x24C)=0;
    if (*(int *)(s+0x54)==-1) *(char **)(s+0x110)=D_L04_001FE340[*(int *)(s+0x50)];
    else *(char **)(s+0x110)=D_L04_001FE340[*(int *)(s+0x54)];
    *(float *)(s+0xA8)=5.0f;
    *(float *)(s+0x1F8)=1.0f;
    *(int *)(s+0xAC)=0;
    *(int *)(s+0x114)=0;
    *(int *)(s+0x118)=0;
    *(int *)(s+0x128)=0;
    *(int *)(s+0x12C)=0;
    *(int *)(s+0x130)=0;
    *(int *)(s+0x244)=0;
    *(int *)(s+0x1F4)=0;
    *(int *)(s+0x144)=0;
    s[0xA4]=0; s[0xA5]=0; *(short *)(s+0xA6)=0;
    *(int *)(s+0x154)=0;
    *(int *)(s+0x150)=0;
    *(int *)(s+0x148)=0;
    *(int *)(s+0x178)=0;
    *(int *)(s+0x248)=0;
    *(int *)(s+0x14C)=0;
    *(int *)(s+0x15C)=0;
    s[0xA1]=0;
    qzero(s+0xD0); qzero(s+0xE0); qzero(s+0x100);
    o=*(unsigned char **)(s+0x110);
    func_002C96F8(o,s+0x114,s+0x118,s+0xF0,*(float *)(s+0xA8),*(float *)(o+0x1C));
    *(float *)(s+0x16C)=func_002A7878_range(-1.5f,1.5f);
    *(int *)(s+0x174)=func_00283CF0(func_002A7878_range(3.0f,6.0f)*60.0f);
    *(int *)(s+0x170)=0;
    *(int *)(m+0x98)=*(int *)(*(unsigned char **)(m+0x24)+0x10);
    *(unsigned short *)(m+0x34)=(*(unsigned short *)(m+0x34)&0xFFBE)|0x1400;
    if (!*(void **)(s+0x8C)) {
        *(void **)(s+0x8C)=func_L04_003E5E40(m,(void *)0x8EF,0.25f);
        if (!*(void **)(s+0x8C)) goto done;
    }
    {
    unsigned char *child=*(unsigned char **)(s+0x8C);
    *(unsigned short *)(child+0x34)&=0xFFBE;
    }
    *(Q16_B0e5d8f83 *)(*(unsigned char **)(s+0x8C)+0x10)=*(Q16_B0e5d8f83 *)(m+0x10);
    *(Q16_B0e5d8f83 *)(*(unsigned char **)(s+0x8C)+0xF0)=*(Q16_B0e5d8f83 *)(m+0xF0);
    (*(unsigned char **)(s+0x8C))[0x30]=0;
    func_002A05A8(*(void **)(s+0x8C));
    func_002A0F48(*(void **)(s+0x8C));
done:
    *(short *)(s+0x17E)=0; *(short *)(s+0x17C)=-1;
    *(int *)(s+0x180)=0; m[0x20]=2;
    *(int *)(s+0x120)=-1;
    *(int *)(s+0x240)=*(int *)(s+0x1C0)=*(int *)(s+0x124)=
    *(int *)(s+0x11C)=*(int *)(s+0x1AC)=*(int *)(s+0x1A0)=*(int *)(s+0x19C)=0;
}

extern float func_00282E48(char *arg0, char *arg1);

extern char *D_001FE340[];

void func_L04_00402C88(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *obj;

    {
        int *slot;
        int i;

        slot = (int *)(state + 0x54);
        for (i = 5; i >= 0; i--, slot++) {
            if (*slot != -1) {
                obj = D_001FE340[*slot];
                *(float *)(obj + 0x1C) = func_00282E48(obj + 0x10, obj + 0x20);
            }
        }
    }
    {
        int none = -1;
        int *slot;
        int i;

        slot = (int *)(state + 0x6C);
        for (i = 3; i >= 0; i--, slot++) {
            if (*slot != none) {
                obj = D_001FE340[*slot];
                *(float *)(obj + 0x1C) = func_00282E48(obj + 0x10, obj + 0x20);
            }
        }
    }
    if (*(int *)(state + 0x7C) != -1) {
        obj = D_001FE340[*(int *)(state + 0x7C)];
        *(float *)(obj + 0x1C) = func_00282E48(obj + 0x10, obj + 0x20);
    }
}
