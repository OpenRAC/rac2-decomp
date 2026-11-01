#include "include_asm.h"


#include "common.h"
extern int func_0029F840(void *, void *, int, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFDD8(void *, void *, void *, int);
extern void func_0029F6A0(void *, int, void *);

void func_PAL_00273818(char *obj, int mode, int index, void *a, void *b, unsigned char tag, float angle) {
    char *p;
    float local[4];
    *(int *)(obj+0x98) = 0;
    *(unsigned short *)(obj+0x34)|=0x100;
    p = *(char **)(obj+0x68);
    qcopy(p, a);
    qcopy(p+0x10, b);
    *(float *)(p+0x38) = 0.45f;
    *(float *)(p+0x3c) = 0.040000003f;
    *(float *)(p+0x40) = 0.5f;
    *(float *)(p+0x44) = 0.015707966f;
    *(float *)(p+0x48) = angle*0.00040000002f;
    *(float *)(p+0x4c) = 0.0025132746f;
    *(short *)(p+0x34) = 150;
    p[0x5e] = tag;
    p[0x5d] = mode;
    p[0x58] = 0;
    p[0x5c] = 0;
    *(int *)(p+0x30) = 0;
    switch (mode) {
        case 2:
        *(short *)(p+0x36) = index;
        *(short *)(obj+0x7c) = (1<<index)|0x8000;
        p[0x58] = func_0029F840(obj, p+0x20, *(int *)(p+0x30), index);
        func_00282CF0(p+0x20, p+0x20, obj+0x10);
        func_002AFDD8(obj, p+0x20, p+0x20, 0);
        break;
        case 0: case 3:
        func_00282D30(p+0x20, obj, 0.0009765625f);
        *(float *)(p+0x2c) = *(float *)(obj+0xc)*0.0009765625f;
        func_00282CF0(p+0x20, p+0x20, obj+0x10);
        func_002AFDD8(obj, p+0x20, p+0x20, 0);
        break;
        case 1:
        *(short *)(p+0x36) = index;
        *(short *)(obj+0x7c) = (mode<<index)|0x8000;
        func_0029F6A0(obj, index, local);
        func_00282CF0(p+0x20, local, obj+0x10);
        func_002AFDD8(obj, p+0x20, p+0x20, 0);
        break;
    }
}



extern void Fdb046c5d_FUN_002742E8(void *);
extern void Fdb046c5d_FUN_00274128(void *);
extern int Fdb046c5d_FUN_00274500(void *);
extern void Fdb046c5d_FUN_00282F20(float, void *, void *);
extern void Fdb046c5d_FUN_00282DD8(void *, void *, void *);
extern void Fdb046c5d_FUN_00274A88(void *, void *, void *);
extern void Fdb046c5d_FUN_002AFFD8(void *, void *, int);
extern int Fdb046c5d_FUN_00274BA8(void *, void *, void *, float, float);
extern int Fdb046c5d_FUN_002E5CF8(int, int, void *);
extern void Fdb046c5d_FUN_00274768(void *, int, void *);
extern void Fdb046c5d_FUN_002E5F00(int, void *);
extern char Fdb046c5d_D_001BAFC0[];

int func_PAL_00273BB0(char *obj)
{
    float buf[4];
    float out[4];
    char *p;
    char *s1;
    unsigned char k;
    int r;
    int s4;
    int s5;

    p = *(char **)(obj + 104);
    k = *(unsigned char *)(p + 92);
    if (k >= 3)
        return 1;
    if (k != 0)
        Fdb046c5d_FUN_002742E8(obj);
    else
        Fdb046c5d_FUN_00274128(obj);

    s5 = Fdb046c5d_FUN_00274500(obj);
    if (s5 == -1)
        return 0;

    s1 = Fdb046c5d_D_001BAFC0;
    s4 = -1;
    Fdb046c5d_FUN_00282F20(1.0f, s1, s1);
    Fdb046c5d_FUN_00282DD8(buf, s1, p);
    Fdb046c5d_FUN_00274A88(obj, p + 16, buf);
    Fdb046c5d_FUN_002AFFD8(obj + 16, out, 1);
    r = Fdb046c5d_FUN_00274BA8(p, s1, out, *(float *)(p + 56), *(float *)(p + 60));
    if (r == 0) {
        if (*(unsigned char *)(p + 94) != 255 && *(unsigned char *)(p + 92) == 0)
            s4 = Fdb046c5d_FUN_002E5CF8(*(unsigned char *)(p + 94), 0, obj);
        Fdb046c5d_FUN_00274768(obj, s5, out);
    } else {
        if (*(unsigned char *)(p + 94) != 255)
            s4 = Fdb046c5d_FUN_002E5CF8(*(unsigned char *)(p + 94), 0, obj);
    }
    if (s4 != -1)
        Fdb046c5d_FUN_002E5F00(s4, p + 32);
    return 0;
}

