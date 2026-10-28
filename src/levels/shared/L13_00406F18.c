#include "common.h"

extern void func_00282D30(void *dst, void *src, float value);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(char *, char *, float);

extern void func_00282DD8(char *, char *, char *);

extern float func_00282DF0(float *);

extern float func_00282C10(float);

extern void func_00283958(char *, char *);

extern void func_00283738(char *, char *, char *);

extern void func_00282AB0(void *, void *, int);

extern int func_00282948(void *);

extern int func_002AD0E0(void *, void *, void *, void *, void *, void *);

extern int func_002B0990(void *, void *, int, int, float);

extern void func_L13_004094D0(char *a0, char *a1, char *a2);

extern int ref_L13_0040A480_00(void *);

extern char D_00189EA0[];

extern void func_002AFFD8(void *, void *, int);

extern float func_002B0360(void *);

extern void func_00282C88(void *);

extern void func_00282CC0(char *, char *, char *);

extern int func_002761F8(void *, void *, int, void *, int);

extern int func_00277258(void *, int, void *, float);

extern void func_00283098(char *, char *, char *);

extern char D_L13_001BFD00[];

INCLUDE_ASM("asm/levels", func_L13_00409008);

void func_L13_004094D0(char *a0, char *a1, char *a2)
{
    float out[12];
    float v[4];
    float m[4];
    float x;

    func_00282F20((char *)m, a1, 1.0f);
    func_00282DD8((char *)v, (char *)m, a0 + 0x20);
    func_00282D30(v, v, 0.05f);
    x = func_00282DF0(v);
    v[3] = -func_00282C10(1.0f - x * x);
    func_00283958((char *)v, (char *)out);
    func_00283738(a0, (char *)out, a0);
    if (a2 != 0) {
        func_00282AB0(a2, out, 0x30);
    }
}

void func_L13_004095A8(void *self, void *base, void *arg)
{
    float tmp[4];
    func_00282D30(tmp, base, -1.0f);
    func_L13_004094D0(self, tmp, arg);
}

INCLUDE_ASM("asm/levels", func_L13_004095F8);

extern int func_L13_004094C0(char *, char *);

extern void func_003357C8(char *, char *, int, int);

extern void func_L13_004095F8(char *, char *);

extern float func_002F8938(char *, char *);

extern int D_001A79F0;

INCLUDE_ASM("asm/levels", func_L13_00409840);


void func_L13_00409AB8(char *a0, char *a1)
{
    if (*(int *)(a1 + 0x88) != 0) {
        if (func_002AD0E0(a0, *(int *)(a1 + 0x88), a0 + 0x10, a0 + 0xF0, a0 + 0x10,
                         a0 + 0xF0) != 0) {
            *(int *)(a1 + 0x94) |= 0x40;
        }
    }
}

void func_L13_00409B08(char *a0, char *a1)
{
    float tmp[4];
    float va[4];
    float vb[4];
    float f;
    char *base;
    char *q;

    func_002AFFD8(a0 + 0x10, (char *)tmp, 1);
    func_00282F20((char *)va, (char *)tmp, *(float *)(a1 + 8) + 0.1f);
    func_00282F20((char *)vb, (char *)tmp, -*(float *)(a1 + 0xC) - 0.1f);
    func_00282CC0((char *)va, (char *)va, a0 + 0x10);
    func_00282CC0((char *)vb, (char *)vb, a0 + 0x10);
    if (func_002761F8(va, vb, 0, a0, 0) != 0) {
        base = D_L13_001BFD00 + 0x20;
        f = func_002B0360(base);
        q = base - 0x20;
        *(float *)(a1 + 0x90) = f;
        *(int *)(a1 + 0x88) = *(int *)(q + 0x18);
        *(int *)(a1 + 0x8C) = *(int *)(q + 0x1C);
        func_00282F20(a1 + 0x50, base + 0x20, 1.0f);
    } else {
        *(float *)(a1 + 0x90) = 0.0f;
        *(int *)(a1 + 0x88) = 0;
        *(int *)(a1 + 0x8C) = 0;
        func_00282C88(a1 + 0x50);
    }
}

INCLUDE_ASM("asm/levels", func_L13_00409C40);

INCLUDE_ASM("asm/levels", func_L13_00409EE8);

/* func_L13_0040A0A0 is defined in L13_0040A0A0.c. */

INCLUDE_ASM("asm/levels", func_L13_0040A2C8);

extern float func_0032E870(char *, void *, char *);

extern float func_003281B8(void *, char *, int, float, float, float, float);

extern void func_002F8FA0(void *, void *);

extern void func_002F92E8(char *, char *, void *);

extern float func_002F86B0(float);

typedef int TI128 __attribute__((mode(TI)));

/* func_L13_0040A3B0 is matched in L13_0040A3B0.c (built with -frac2-zero-ti-barrier). */


void func_L13_0040A480(char *a0)
{
    char tmp[16];
    func_00282CF0(tmp, D_00189EA0, a0 + 0x10);
    func_L13_0040A3B0(a0, (void *)ref_L13_0040A480_00(a0), tmp, 0);
}

void func_L13_0040A4D0(char *a0)
{
    char *p = *(char **)(a0 + 0x68);
    u16 value;

    func_00282948(p + 0x240);
    func_00282948(p + 0x244);
    value = *(u16 *)(a0 + 0x96);
    if (value <= 0xFFFEu) {
        *(u16 *)(a0 + 0x96) = value + 1;
    }
    func_002B0990(a0, p + 0x2E0, 1, 1, 2.5f);
}

typedef struct L13State {
    char pad[0x244];
    int f244;
    int pad2;
    int f24C;
} L13State;

/* The per-entity state: the index at 0x2C0, the kind at 0x2C4 and the partner kind at 0x2CC. */
typedef struct L13EntState {
    u8 pad0[0x2C0];
    s32 f2C0;
    s32 f2C4;
    u8 pad1[4];
    s32 f2CC;
} L13EntState;

extern u16 *D_L13_001FB420[];
extern u8 *D_L13_001B291C __attribute__((section(".sdata")));
extern int D_L13_001B2938 __attribute__((section(".sdata")));

/* Raises the +0x24C flag of each entity of kind 0xEA3 or 0xEA4 in the object's group, and the
   +0x244 flag of kind 0xF35. The kinds are tested one by one, as retail's separate branches show. */
void func_L13_0040A540(u8 *a0)
{
    u16 *q;
    u16 *p;
    u8 *e;

    if (a0[0x21] == 0xFF)
        return;
    q = D_L13_001FB420[a0[0x21]];
    if (q == 0)
        return;
    for (p = q; a0[0x21] != 0xFF && a0[0x21] <= D_L13_001B2938 && p != 0 &&
           ((p != 0 && (s16)p[-1] >= 0) || p == D_L13_001FB420[a0[0x21]]);
         p++) {
        e = D_L13_001B291C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (*(s16 *)(e + 0xAA) == 0xEA3) {
            ((L13State *)*(u8 **)(e + 0x68))->f24C = 1;
        } else if (*(s16 *)(e + 0xAA) == 0xEA4) {
            ((L13State *)*(u8 **)(e + 0x68))->f24C = 1;
        } else if (*(s16 *)(e + 0xAA) == 0xF35) {
            ((L13State *)*(u8 **)(e + 0x68))->f244 = 1;
        }
    }
}

/* Compares the kind at +0x2C4 of the object's state with the kind the pointed-at entity's
   state carries (+0x2CC for a 0xEA3 entity, +0x2C4 for a 0xEA4 one): 1 when the second is the
   successor of the first in 0,1,2, 0 when it is the predecessor, and 2 otherwise. */
s32 func_L13_0040A638(u8 *a0)
{
    L13EntState *st = *(L13EntState **)(a0 + 0x68);
    u8 *e = D_L13_001B291C + (st->f2C0 << 8);
    s32 kind = *(s16 *)(e + 0xAA);
    s32 y, x;

    if (kind == 0xEA3) {
        y = st->f2C4;
        x = ((L13EntState *)*(u8 **)(e + 0x68))->f2CC;
    } else if (kind == 0xEA4) {
        y = st->f2C4;
        x = ((L13EntState *)*(u8 **)(e + 0x68))->f2C4;
    } else {
        x = st->f2C4;
        y = x;
    }
    if (y == x)
        return 2;
    if (y == 0) {
        if (x == 1)
            return 1;
    }
    if (y == 1) {
        if (x == 2)
            return 1;
    }
    if (y == 2) {
        if (x == 0)
            return 1;
    }
    if (y == 0) {
        if (x == 2)
            return 0;
    }
    if (y == 1) {
        if (x == 0)
            return 0;
    }
    if (y == 2) {
        if (x == 1)
            return 0;
    }
    return 2;
}

INCLUDE_ASM("asm/levels", func_L13_0040C3A0);

void func_L13_0040CA00(char *a0)
{
    char *p = *(char **)(a0 + 0x68);
    u16 value;

    func_00282948(p + 0x240);
    func_00282948(p + 0x244);
    value = *(u16 *)(a0 + 0x96);
    if (value <= 0xFFFEu) {
        *(u16 *)(a0 + 0x96) = value + 1;
    }
    func_002B0990(a0, p + 0x2D0, 4, 1, 2.5f);
}

/* Raises the +0x24C flag of each entity of kind 0xEA3 or 0xEA4 in the object's group, tested one
   by one as in func_L13_0040A540. */
void func_L13_0040CA70(u8 *a0)
{
    u16 *q;
    u16 *p;
    u8 *e;

    if (a0[0x21] == 0xFF)
        return;
    q = D_L13_001FB420[a0[0x21]];
    if (q == 0)
        return;
    for (p = q; a0[0x21] != 0xFF && a0[0x21] <= D_L13_001B2938 && p != 0 &&
           ((p != 0 && (s16)p[-1] >= 0) || p == D_L13_001FB420[a0[0x21]]);
         p++) {
        e = D_L13_001B291C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (*(s16 *)(e + 0xAA) == 0xEA3) {
            ((L13State *)*(u8 **)(e + 0x68))->f24C = 1;
        } else if (*(s16 *)(e + 0xAA) == 0xEA4) {
            ((L13State *)*(u8 **)(e + 0x68))->f24C = 1;
        }
    }
}

INCLUDE_ASM("asm/levels", func_L13_0040D930);

INCLUDE_ASM("asm/levels", func_L13_0040DC20);


INCLUDE_ASM("asm/levels", func_L13_0040DFC0);

INCLUDE_ASM("asm/levels", func_L13_00412748);

INCLUDE_ASM("asm/levels", func_L13_00412C18);

INCLUDE_ASM("asm/levels", func_L13_0041AB30);

INCLUDE_ASM("asm/levels", func_L13_0041AD00);
