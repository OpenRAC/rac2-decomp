#include "include_asm.h"


extern unsigned char D_0018C0DF;
extern int D_L00_002A27F0[];
extern void func_002A7470(void *, int, int, int);
extern void func_0029F338(void *);
extern void func_002A10E8(void *);
extern void func_0029F338(void *);

void func_PAL_00311E78(unsigned char *self)
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
            func_002A7470(self, 1, 0, 8);
        self[0x20] = 1;
        *(float *)(self + 0x48) = 1.0f;
    }
    goto finish;
c1:
    if ((*(unsigned char **)data)[0x20] == 2) {
        if (self[0x43] != 3)
            func_002A7470(self, 3, 0, 8);
        self[0x20] = 3;
        *(float *)(self + 0x48) = 1.0f;
    } else if ((*(unsigned char **)data)[0x20] == 8) {
        if (self[0x43] != 2)
            func_002A7470(self, 2, 0, 8);
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
            func_002A7470(self, 4, 0, 8);
        self[0x20] = 4;
    }
    goto finish;
c4:
    if ((unsigned int)((*(unsigned char **)data)[0x20] - 3) < 3) {
        if (self[0x43] != 5)
            func_002A7470(self, 5, 0, 8);
        self[0x20] = 5;
    }
    goto finish;
c5:
    if (self[0x60] & 2)
        *(float *)(self + 0x48) = 0.0f;
    if ((unsigned int)((*(unsigned char **)data)[0x20] - 6) < 2) {
        *(float *)(self + 0x48) = 1.0f;
        if (self[0x43] != 7)
            func_002A7470(self, 7, 0, 8);
        self[0x20] = 7;
    }
    goto finish;
c7:
    if (!(self[0x60] & 2))
        goto finish;
activate_one:
    if (self[0x43] != 1)
        func_002A7470(self, 1, 0, 8);
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

void func_PAL_003120C0(unsigned char *self)
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

