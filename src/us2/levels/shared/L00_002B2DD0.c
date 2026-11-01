#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad0[476];
    short f1dc;
    unsigned char pad1de[62];
    short f21c;
    unsigned char pad21e[1136];
    short f68e;
    unsigned char pad690[52];
    int f6c4;
    unsigned char pad6c8[3535];
    unsigned char f1497;
    unsigned char pad1498[104];
    int f1500;
    unsigned char pad1504[3468];
    char *f2290;
    int f2294;
    unsigned char pad2298[4];
    int f229c;
    unsigned char pad22a0[20];
    unsigned char f22b4;
    unsigned char pad22b5[487];
    char *f249c;
    unsigned char pad24a0[44];
    int f24cc;
} Root;
extern Root D_00189E20;
extern char D_L00_001C3480[];
extern int D_L00_001A8F00 __attribute__((sda));
extern unsigned char D_001A7A33 __attribute__((sda));
extern unsigned char D_001A7A32 __attribute__((sda));
extern float func_L00_0037E668(void);
extern float func_L00_0037E5F0(float);
extern void func_L00_002A6708(void);
extern void func_00282CF0(void *, void *, void *);
extern void func_L00_002D36E0(void *, int, float, float, float);
extern void ref_L00_002B2CC8_0(int, int);
extern void *func_002A9640(void *, int, int);
extern int func_00283CF0(float);
extern void func_US2_L00_002A4EF8(int);
extern void func_L00_002B9B88(int, int);
extern void func_L00_002B2C58(void *, int, float, float);
extern void func_L00_002D3C68(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
#define SI(o) (*(int *)(slot + (o)))
#define SF(o) (*(float *)(slot + (o)))

int func_US2_L00_002B2DD0(int apply)
{
    float v[4] __attribute__((aligned(16)));
    char *obj, *slot, *p;
    int special;
    float scale;

    if (D_00189E20.f229c == 20)
        return 0;
    if (D_00189E20.f229c == 7)
        return 0;
    if (D_00189E20.f2294 == 49)
        return 0;
    if (D_00189E20.f1dc)
        return 0;
    if (D_L00_001A8F00)
        return 0;
    D_00189E20.f249c = 0;
    obj = D_00189E20.f2290;
    if ((unsigned char)obj[0xa8] == 255)
        return 0;
    slot = D_L00_001C3480 + (unsigned char)obj[0xa8] * 64;
    if (*(char **)(slot + 0x38) != obj || !(SI(0x24) & 9))
        return 0;
    if (SF(0x2c) != 0.0f) {
        D_001A7A33 = 0;
        D_001A7A32 = 1;
    }
    if (func_L00_0037E668() != 0.0f && !D_00189E20.f22b4) {
        SF(0x2c) = func_L00_0037E5F0(SF(0x2c));
        if (SF(0x2c) == 0.0f)
            return 0;
    }
    D_00189E20.f249c = SI(0x20);
    if (D_00189E20.f229c == 15) {
        D_00189E20.f6c4 = (int)slot;
        D_00189E20.f68e = 1;
        return 0;
    }
    if (!apply)
        return 1;
    func_L00_002A6708();
    special = 0;
    if (SI(0x30) & 1) {
        qcopy(v, slot + 0x10);
        if (SF(0x1c) == 5627.925f)
            special = 1;
    } else if (SI(0x20)) {
        func_00282CF0(v, (char *)&D_00189E20 + 0x80,
                     *(char **)(slot + 0x20) + 0x10);
    } else {
        func_L00_002D36E0(v, 0, -1.0f, 0.0f, 0.0f);
    }
    switch (D_00189E20.f22b4) {
    case 0: {
        p = D_00189E20.f249c;
        if (p && (*(short *)(p + 0xaa) == 1259 || *(short *)(p + 0xaa) == 1368)) {
            ref_L00_002B2CC8_0(125, 1);
            return 1;
        }
        if ((D_00189E20.f2294 == 1 || D_00189E20.f2294 == 29 || D_00189E20.f1500) &&
            !(SI(0x24) & 8)) {
            p = func_002A9640(D_00189E20.f2290, 1, 0);
            if (p)
                func_US2_L00_002A4EF8(func_00283CF0(*(float *)(p + 0x2c)));
            if (!D_00189E20.f24cc)
                ref_L00_002B2CC8_0(22, 1);
            D_00189E20.f1dc = 77;
            if (!D_00189E20.f21c)
                D_00189E20.f21c = 18;
            func_L00_002B9B88(20, 0);
            return 0;
        }
        if (D_00189E20.f229c == 18)
            ref_L00_002B2CC8_0(114, 1);
        else if (D_00189E20.f229c == 17)
            ref_L00_002B2CC8_0(115, 1);
        else if (SI(0x24) & 8)
            ref_L00_002B2CC8_0(140, 1);
        else
            ref_L00_002B2CC8_0(22, 1);
        if (D_00189E20.f2294 == 140) {
            qzero(v);
        } else {
            scale = 0.055000003f;
            if (D_00189E20.f1497)
                scale = 0.0f;
            func_L00_002B2C58(v, special, scale, 0.028333336f);
            if (special && (unsigned char)slot[0x28] == 4)
                func_L00_002D3C68(v, v, 2.0f);
        }
        break;
    }
    case 1: {
        ref_L00_002B2CC8_0(66, 1);
        func_L00_002B2C58(v, special, 0.083333336f, 0.050000004f);
        break;
    }
    }
    func_00282CC0((char *)&D_00189E20 + 0xf0, (char *)&D_00189E20 + 0xf0, v);
    func_00282CC0((char *)&D_00189E20 + 0x110, (char *)&D_00189E20 + 0x110, v);
    return 1;
}

