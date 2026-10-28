#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));

extern void func_002A6C58(void *, int, int);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F70(void *, void *, float);
extern void *func_0032C700(void *, s32, s32, s32, s32, s32, s32, s32, float, float, s32, s32, s32, s32);
extern void func_002AD330(void *, void *, void *, void *);
extern void func_002B0A68(void *, int, void *, float, float, float, float, int);
extern void func_002A7750(u8 *, int, int);
extern void func_0029F338(void *);
extern u8 D_00188660[];
extern u8 D_00189EA0[];
extern float D_L07_001B0AAC __attribute__((sda));

void func_L07_003E5D80(u8 *obj) {
    u8 *st = *(u8 **)(obj + 0x68);
    int slot;
    u8 *rec;
    u8 *pos;
    u8 *toward;
    union { Quad q; f32 f[4]; } a;
    f32 b[4] __attribute__((aligned(16)));
    f32 c[4] __attribute__((aligned(16)));
    int count;

    if (st[0x2E] != 2) {
        func_002A6C58(obj, 0, 1);
    }
    slot = *(s32 *)(st + 0x264);
    if (slot != -1) {
        rec = D_00188660 + slot * 0x70;
        if (*(u8 **)(rec + 0x88) == obj && rec[0x74] != 0) {
            func_002E59F8(slot);
        }
    }
    *(s32 *)(st + 0x264) = -1;
    func_002E5CF8(0, 0, obj);
    pos = obj + 0x10;
    a.q = 0;
    a.f[2] = 0.5f;
    func_00282CC0(&a, &a, pos);
    func_0032C700(&a, 0, 0, 0, 0, 0x14, 0x2D, 1, D_L07_001B0AAC, 20.0f, 1, 0, 0, *(s32 *)(st + 0x260));
    func_00282CF0(b, pos, D_00189EA0);
    b[2] = 0.0f;
    func_00282F70(b, b, 0.06666667f);
    toward = *(u8 **)(st + 0x260);
    if (toward != 0) {
        func_002AD330(obj, toward, pos, c);
        func_00282CC0(b, b, c);
    }
    func_002B0A68(obj, 3, b, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    count = *(u16 *)(st + 0x21A) - 1;
    *(u16 *)(st + 0x21A) = count;
    if ((s16)count != -1) {
        *(s16 *)(st + 0x88) = 0;
        *(s32 *)(obj + 0x98) = 0;
        *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) | 0x41) & 0xEFFF;
        func_002A7750(obj, 8, 4);
        st[0x2E] = 1;
        *(f32 *)(st + 0x20) = *(s16 *)(st + 0x24);
    } else {
        func_0029F338(obj);
    }
}
