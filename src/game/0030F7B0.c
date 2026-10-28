#include "include_asm.h"

extern char *Ffc961fca_FUN_002AD0B0(char *a1);

extern void Ffc961fca_FUN_00283410(char *dst, char *src);

extern void Ffc961fca_FUN_00282CC0(char *dst, char *src, char *tail);

extern void Ffc961fca_FUN_00282CF0(char *dst, char *src, char *tail);

extern void Ffc961fca_FUN_00283698(char *dst, char *src);

extern void Ffc961fca_FUN_00283098(char *dst, char *src, char *tail);

extern void Ffc961fca_FUN_00283738(char *dst, char *src, char *tail);

typedef struct {
    char pad0[0x20];
    unsigned char state;
} Level16VendorMoby;

extern void Fc936841d_FUN_00282CF0(char *local, char *first, char *second);

extern void Fc936841d_FUN_00282CC0(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif



extern unsigned char D_0018C0DF;
extern int D_L00_002A27F0[];
extern void func_002A7470(void *, int, int, int);
extern void func_0029F338(void *);
extern void func_002A10E8(void *);

void func_00310A40(unsigned char *self)
{
    static void *cases[8] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7};
    unsigned char *peer;
    unsigned char *data;
    int state;

    if (self == 0)
        return;
    data = *(unsigned char **)(self + 0x68);
    if (data == 0)
        return;
    peer = *(unsigned char **)data;
    if (peer == 0 || *(short *)(peer + 0xAA) != 0xD0 || peer[0x20] == 0xFE ||
        peer[0x20] == 0xFD || *(unsigned char **)(*(unsigned char **)(peer + 0x68) + 0x14) != self)
        goto destroy;
    if ((*(unsigned short *)(peer + 0x34) & 1) || D_0018C0DF != 0)
        *(unsigned short *)(self + 0x34) |= 0x41;
    else
        *(unsigned short *)(self + 0x34) &= 0xFFBE;
    state = self[0x20];
    if ((unsigned int)state < 8)
        goto *D_L00_002A27F0[state];
    goto activate_one;
c0:
    if (self[0x60] & 2) {
        if (self[0x43] != 1)
            func_002A7470(self, 1, 0, 10);
        self[0x20] = 1;
        *(float *)(self + 0x48) = 1.0f;
    }
    goto finish;
c1:
    if ((*(unsigned char **)data)[0x20] == 2) {
        if (self[0x43] != 3)
            func_002A7470(self, 3, 0, 10);
        self[0x20] = 3;
        *(float *)(self + 0x48) = 1.0f;
    } else if ((*(unsigned char **)data)[0x20] == 8) {
        if (self[0x43] != 2)
            func_002A7470(self, 2, 0, 10);
        self[0x20] = 2;
        *(float *)(self + 0x48) = 1.0f;
    }
    goto finish;
c2:
    if (!(self[0x60] & 2))
        goto finish;
destroy:
    func_0029F338(self);
    return;
c3:
    if (self[0x60] & 2) {
        if (self[0x43] != 4)
            func_002A7470(self, 4, 0, 10);
        self[0x20] = 4;
    }
    goto finish;
c4:
    if ((unsigned int)((*(unsigned char **)data)[0x20] - 3) < 3) {
        if (self[0x43] != 5)
            func_002A7470(self, 5, 0, 10);
        self[0x20] = 5;
    }
    goto finish;
c5:
    if (self[0x60] & 2)
        *(float *)(self + 0x48) = 0.0f;
    if ((unsigned int)((*(unsigned char **)data)[0x20] - 6) < 2) {
        *(float *)(self + 0x48) = 1.0f;
        if (self[0x43] != 7)
            func_002A7470(self, 7, 0, 10);
        self[0x20] = 7;
    }
    goto finish;
c7:
    if (!(self[0x60] & 2))
        goto finish;
activate_one:
    if (self[0x43] != 1)
        func_002A7470(self, 1, 0, 10);
    self[0x20] = 1;
c6:
finish:
    func_002A10E8(self);
}

extern char *D_001AD7EC __attribute__((sda));
extern float D_001B1690[] __attribute__((sda));
extern void func_00310D78(char *, char *);
extern int func_00273B70(unsigned char *);
extern int func_002A77E0(int);
extern void func_002A7750(unsigned char *, unsigned char, int);
extern void func_0029F338(void *);

void func_00310C88(unsigned char *self)
{
    if (D_001AD7EC != 0)
        func_00310D78((char *)self, D_001AD7EC);
    switch (self[0x20]) {
    case 0:
        if (func_00273B70(self) != 0 ||
            (D_001B1690[0] > 0.949999988079071044921875f && func_002A77E0(10) == 0)) {
            func_002A7750(self, 1, -1);
            *(unsigned short *)(self + 0x34) |= 0x2800;
        }
        break;
    case 1:
        func_00273B70(self);
        if (self[0x23] < 2)
            func_0029F338(self);
        else
            self[0x23] -= 2;
        break;
    }
}


void func_00310D78(char *o0, char *o1)
{
    char b0[64];
    char b1[64];
    char b2[64];
    char *r = Ffc961fca_FUN_002AD0B0(o1);

    if (r == 0)
        return;
    Ffc961fca_FUN_00283410(b0, r);
    Ffc961fca_FUN_00282CC0(o0 + 16, o0 + 16, r + 16);
    Ffc961fca_FUN_00282CF0(o0 + 16, o0 + 16, o1 + 16);
    if ((*(int *)(r + 60) & 2) != 0) {
        Ffc961fca_FUN_00283410(b2, r + 32);
        Ffc961fca_FUN_00283698(b1, b2);
        Ffc961fca_FUN_00283098(o0 + 16, o0 + 16, b1);
        Ffc961fca_FUN_00283098(o0 + 16, o0 + 16, o1 + 192);
    } else {
        Ffc961fca_FUN_00283098(o0 + 16, o0 + 16, b0);
    }
    Ffc961fca_FUN_00282CC0(o0 + 16, o0 + 16, o1 + 16);
    Ffc961fca_FUN_00283738(o0 + 192, b0, o0 + 192);
}

INCLUDE_ASM("asm/game", func_00310E98);

INCLUDE_ASM("asm/game", func_003116E8);

INCLUDE_ASM("asm/game", func_00311F70);

INCLUDE_ASM("asm/game", func_003120C8);


INCLUDE_ASM("asm/game", func_00312600);

int func_00312B58(Level16VendorMoby *moby) {
    return moby->state == 6;
}






int func_00312E10(unsigned char *p) { return p[0x20] == 1; }



/* func_00312EB0 is defined in 00312EB0-qcopy.c. */

INCLUDE_ASM("asm/game", func_00313210);

extern char D_L00_0023A670[][16];
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

typedef struct { char pad[0x30]; char *entries[1]; } SolEmitterData;

void func_00313548(unsigned char *object, float *out, int index)
{
    char local[16];
    char *data = *(char **)(object + 0x68);
    char *entry;
    func_002ACEC0(local, D_L00_0023A670[index], data + 0x20, *(float *)(data + 0x2C));
    entry = ((SolEmitterData *)data)->entries[index];
    if (entry && object[0x20] == 2)
        func_00282F20(local, local, *(float *)(entry + 0x28));
    func_00282CC0(out, data + 0x10, local);
    out[2] += *(float *)data;
}


/* func_00313678 uses the profile in 0030F7B0-qcopy.c. */

INCLUDE_ASM("asm/game", func_003136D0);

INCLUDE_ASM("asm/game", func_003146C0);

INCLUDE_ASM("asm/game", func_00314CF8);


INCLUDE_ASM("asm/game", func_00314FD0);


INCLUDE_ASM("asm/game", func_003158A8);

INCLUDE_ASM("asm/game", func_003159D0);


INCLUDE_ASM("asm/game", func_00315C78);

INCLUDE_ASM("asm/game", func_00315E20);

/* func_00316248 is in 0030F7B0-g8.c. */

INCLUDE_ASM("asm/game", func_00316400);

INCLUDE_ASM("asm/game", func_003166C8);


void func_00316B40(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

/* func_00316BC8 is defined in 00316BC8-qcopy.c. */

void func_00316DA0(Vec16_Fc936841d *object, int index)
{
    char local[16];

    Fc936841d_FUN_00282CF0(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    Fc936841d_FUN_00282CC0((char *)&object[index - 1], (char *)&object[index - 2], local);
}

INCLUDE_ASM("asm/game", func_00316E08);

INCLUDE_ASM("asm/game", func_003172D0);
