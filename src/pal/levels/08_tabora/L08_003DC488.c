/* func_PAL_L08_003DC488, the PAL copy of func_L08_003D8348: the same C, where f6C 0.25f becomes 0.3f,
   f70 0.116667f becomes 0.14000001f (x6/5), f78 0.00833333f becomes 0.012f (x36/25) and f74/f7C 0.00416667f
   becomes 0.006f (x36/25). */
#include "common.h"

extern int func_00283CF0(float);
extern void func_L08_003D82F0(void *);
extern void func_0029F338(void *);
extern float func_L08_0032EF80(void *, int, int, int, int);
extern void func_L01_003377C8(void *);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_001163B0(void);
extern void func_00282CC0(void *, void *, void *);
extern int D_001A79F0 __attribute__((sda));
extern char D_0019B4A8[];

typedef int InitVector __attribute__((mode(TI)));
typedef struct {
    int f0;
    char pad4[8];
    int fC;
    char pad10[0x18];
    float f28;
    char pad2C[12];
    float f38;
} InitContext;
extern InitContext D_L08_001CA080;
typedef struct {
    u8 pad0[0x464];
    u8 flags[0];
} InitFlags;
extern InitFlags D_L08_0021EAF0;
typedef struct {
    u8 pad0[0xB0];
    u8 fB0;
    u8 padB1;
    u16 fB2;
    u8 tail[0x4C];
} InitEntry;
extern u32 D_L08_001B29DC __attribute__((sda));
extern void *D_L08_001FE7BC __attribute__((section(".data")));

typedef struct {
    u8 pad0[0x10];
    void *f10;
    u8 pad14[0x14];
    u8 f28;
    u8 f29;
    u8 pad2a[0x6];
    float f30;
    u8 pad34[0x14];
    u8 f48;
    u8 pad49[0x1];
    u8 f4A;
    u8 pad4b[0x15];
    u8 f60;
    u8 f61;
    u8 f62;
    u8 pad63[0x3];
    u8 f66;
    u8 f67;
    u8 pad68[0x2];
    u8 f6A;
    u8 pad6b[0x1];
    float f6C;
    float f70;
    float f74;
    float f78;
    float f7C;
    float f80;
    float f84;
    u16 f88;
    u8 pad8a[0x2];
    float f8C;
    u8 pad90[0x8];
    int f98;
    u8 pad9c[0xC];
    float fA8;
    float fAC;
    u8 padb0[0xC];
    u8 fBC;
    u8 fBD;
    u8 fBE;
    u8 fBF;
    u8 padc0[0x2];
    u8 fC2;
    u8 fC3;
    u8 fC4;
    u8 padc5[0x1];
    u8 fC6;
    u8 padc7[0x31];
    float fF8;
    u8 padfc[0x24];
    float f120;
    u8 pad124[0xC];
    float f130;
    u8 pad134[0x1C];
    float f150;
    u8 pad154[0x8];
    int f15C;
    u8 pad160[0x2A4];
    int f404;
    u16 f408;
    u16 f40A;
    u8 f40C;
    u8 pad40d[0x3];
    int f410;
    int f414;
    int f418;
    int f41C;
    int f420;
    int f424;
    int f428;
    int f42C;
    int f430;
    float f434;
    u8 pad438[0x18];
    int f450;
} InitState;
typedef struct {
    u8 pad0[0x18];
    float f18;
    u8 pad1c[0x8];
    char *f24;
    u8 pad28[0x4];
    float f2C;
    u8 f30;
    u8 f31;
    u8 pad32[0x2];
    u16 f34;
    u8 pad36[0xD];
    u8 f43;
    u8 pad44[0x24];
    InitState *f68;
    u8 pad6c[0x2C];
    int f98;
    u8 pad9c[0x16];
    u16 fB2;
} InitObject;

void func_PAL_L08_003DC488(InitObject *object)
{
    InitState *s = object->f68;
    float position[4], value;
    int handle;
    unsigned short flag;
    int bits;
    s->f48 = func_00283CF0(15.0f);
    s->f4A = func_00283CF0(9.6f);
    s->f29 = 1;
    if (D_L08_001CA080.fC) {
        if (object->f18 < D_L08_001CA080.f28 && D_L08_001CA080.f0 == 1)
            return;
        if (object->f18 > D_L08_001CA080.f28 && D_L08_001CA080.f0 == 0)
            return;
        if (D_L08_001CA080.fC == 2) {
            if (object->f18 > D_L08_001CA080.f38 && D_L08_001CA080.f0 == 1)
                return;
            if (object->f18 < D_L08_001CA080.f38 && D_L08_001CA080.f0 == 2)
                return;
        }
    }
    handle = s->f404;
    if (handle != -1) {
        /* Entries are 0x100 bytes; the global holds their base address. */
        handle = D_L08_001B29DC + (handle << 8);
        if (((InitEntry *)handle)->fB0 != 255) {
            flag = ((InitEntry *)handle)->fB2;
            if (D_L08_0021EAF0.flags[(short)flag] ||
                ((bits = (u8)D_0019B4A8[((short)flag >> 1) + (D_001A79F0 << 10)]),
                 (flag & 1) ? (bits >> 4) & 7 : bits & 7)) {
                unsigned short objectFlag = object->fB2;
                bits = (u8)D_0019B4A8[((short)objectFlag >> 1) + (D_001A79F0 << 10)];
                if ((objectFlag & 1) ? (bits >> 4) & 7 : bits & 7) {
                    func_0029F338(object);
                    return;
                }
            }
        }
    }
    qcopy_nc((char *)s + 0x3E0, (char *)object + 0x10);
    func_L08_003D82F0(object);
    s->f408 = object->f30;
    *(InitVector *)position = *(InitVector *)((char *)object + 0x10);
    value = func_L08_0032EF80(position, s->f410, s->f418, s->f414, -1);
    if (value > 0)
        object->f30 = func_00283CF0(value + 2.0f);
    s->f408 = s->f40A = object->f30;
    *(InitVector *)position = *(InitVector *)((char *)object + 0x10);
    value = func_L08_0032EF80(position, s->f41C, s->f424, s->f420, -1);
    if (value > 0)
        s->f408 = func_00283CF0(value + 2.0f);
    if (s->f428 == -1)
        func_L01_003377C8(D_L08_001FE7BC);
    s->f88 = 0;
    s->f6A = 0;
    s->f98 = -1;
    s->f10 = (char *)s + 0x50;
    s->f60 = 9;
    s->f62 = s->f61 = 12;
    s->f66 = 13;
    s->f67 = 10;
    s->f6C = 0.3f;
    s->f70 = 0.14000001f;
    s->f78 = 0.012f;
    s->f7C = s->f74 = 0.006f;
    s->f84 = s->f80 = 0.8f;
    s->f8C = 0.4f;
    s->fBE = s->fBC = 2;
    s->fBF = s->fBD = 8;
    s->fC2 = 4;
    s->fC3 = 14;
    s->fA8 = 0.1f;
    s->fAC = 0.3f;
    s->fF8 = 0;
    s->f28 = 1;
    s->f30 = 0.2f;
    s->fC6 = 0;
    s->fC4 = 0;
    s->f430 = 0;
    if (s->f42C != -1)
        s->f15C = s->f42C;
    else
        s->f15C = s->f428;
    s->f150 = 0.0872664749622345f;
    s->f120 = 0.7f;
    s->f130 = 0.7853982448577881f;
    qcopy((char *)s + 0x3F0, (char *)object + 0x10);
    s->f450 = 0;
    switch (s->f40C) {
    case 0:
        object->f18 = s->f434;
        qcopy_nc((char *)s + 0x3E0, (char *)object + 0x10);
        qzero_nc((char *)s + 0x1C0);
        if (object->f43 != 11)
            func_002A7470(object, 11, 0, 2);
        func_002A7750(object, 1, -1);
        object->f31 = 0;
        object->f98 = 0;
        object->f34 = (object->f34 & 0xEFFF) | 1;
        break;
    case 1:
    case 3:
        object->f18 = s->f434;
        qcopy_nc((char *)s + 0x3E0, (char *)object + 0x10);
        qzero_nc((char *)s + 0x1C0);
        if (object->f43 != (func_001163B0() & 1))
            func_002A7470(object, func_001163B0() & 1, 0, 2);
        func_002A7750(object, 6, -1);
        object->f31 = 1;
        object->f34 = (object->f34 | 0x1000) & 0xFFFE;
        break;
    case 2:
        qzero_nc((char *)s + 0x1C0);
        func_00282CC0((char *)object + 0x10, (char *)object + 0x10, (char *)s + 0xD0);
        qcopy_nc((char *)s + 0x3E0, (char *)object + 0x10);
        if (object->f43 != 14)
            func_002A7470(object, 14, 0, 2);
        object->f2C = *(float *)(object->f24 + 0x24) * 0.5f;
        object->f31 = 1;
        object->f34 = (object->f34 | 0x1000) & 0xFFFE;
        func_002A7750(object, 4, -1);
        break;
    }
}
