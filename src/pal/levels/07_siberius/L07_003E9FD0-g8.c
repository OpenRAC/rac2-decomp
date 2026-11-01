#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
extern void func_PAL_002A7650(void *, int, int);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F70(void *, void *, float);
extern void *func_PAL_L00_003FB330(void *, s32, s32, s32, s32, s32, s32, s32, float, float, s32, s32, s32, s32);
extern void func_002AD330(void *, void *, void *, void *);
extern void func_PAL_002B15D8(void *, int, void *, float, float, float, float, int);
extern void func_002A7750(u8 *, int, int);
extern void func_0029F338(void *);
extern u8 D_00188660[];
extern u8 D_00189EA0[];
extern float D_L07_001B0AAC __attribute__((sda));

void func_PAL_L07_003E9FD0(u8 *obj) {
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
        func_PAL_002A7650(obj, 0, 1);
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
    func_PAL_L00_003FB330(&a, 0, 0, 0, 0, 0x14, 0x2D, 1, D_L07_001B0AAC, 20.0f, 1, 0, 0, *(s32 *)(st + 0x260));
    func_00282CF0(b, pos, D_00189EA0);
    b[2] = 0.0f;
    func_00282F70(b, b, 0.080000006f);
    toward = *(u8 **)(st + 0x260);
    if (toward != 0) {
        func_002AD330(obj, toward, pos, c);
        func_00282CC0(b, b, c);
    }
    func_PAL_002B15D8(obj, 3, b, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
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

extern int func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern void func_002A7A00(void *, float, float);
extern int func_002A7820(int, int);
extern void func_00283098(void *, void *, void *);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void *func_002C3150(void *, void *, int, float, unsigned char, unsigned char, int);
extern float D_L07_001B0AD8 __attribute__((sda));
extern float D_L07_001B0AB0 __attribute__((sda));
extern float D_L07_001B0AB4[] __attribute__((sda));
extern int D_L07_001B0AD0[] __attribute__((sda));
extern float D_L07_001B0AC0[] __attribute__((sda));
extern int D_L07_001B0AC8 __attribute__((sda));

/* Emit two particles at opposite local offsets, including platform motion. */
void func_PAL_L07_003EA1F8(char *arg)
{
    float carryDelta[4] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    char *state = *(char **)(arg + 0x68);
    int side;

    qzero_nc(angles);
    if (*(void **)(state + 0x260)) {
        func_002AD0E0(arg, *(void **)(state + 0x260), arg + 0x10, angles, carryDelta, angles);
        func_00282CF0(carryDelta, carryDelta, arg + 0x10);
    } else {
        qzero_nc(carryDelta);
    }
    for (side = 0; side < 2; side++) {
        int randomValue, randomByte;
        float scale;

        qzero_nc(position);
        position[2] = D_L07_001B0AD8;
        if (!side)
            position[2] = -position[2];
        func_002A7A00(velocity, D_L07_001B0AB0 * (0.020000001f),
                      D_L07_001B0AB4[0] * (0.020000001f));
        func_00282CC0(velocity, velocity, carryDelta);
        randomValue = ((s32)(func_002A7820(D_L07_001B0AD0[0], D_L07_001B0AD0[1])) * 5 + 2) / 6;
        func_00283098(position, position, arg + 0xC0);
        randomValue = (unsigned char)randomValue;
        func_00282CC0(position, position, arg + 0x10);
        scale = func_002A7878(D_L07_001B0AC0[0], D_L07_001B0AC0[1]);
        randomByte = func_002A77E0(255);
        func_002C3150(position, velocity, D_L07_001B0AC8, scale, randomValue, (unsigned char)randomByte, 0);
    }
}
