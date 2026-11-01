#include "include_asm.h"

#include "common.h"
typedef int qword __attribute__((mode(TI)));
extern float D_L12_001B0B10 __attribute__((sda));
extern u8 D_L12_001FEAC0[];
extern void func_00282CF0(float *, const float *, const float *);
extern float func_00282DF0(float *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern float func_002A89A8(void *, int, float);

int func_PAL_L12_003E6198(u8 *a0, u8 *a1) {
    u8 *st = *(u8 **)(a0 + 0x68);
    u8 *e = *(u8 **)(D_L12_001FEAC0 + (*(s32 *)(st + 0x158) << 2));
    float entry[4];
    float dir[4];
    float rot[4];
    float len;
    u8 *src;

    if (*(s32 *)(st + 0x168) > 0) {
        src = (u8 *)(*(s32 *)(st + 0x168) << 4);
        src += (s32)a1;
        src += 0x10;
    }
    else
        src = e + 0x10;
    qcopy(entry, src);
    if (*(s32 *)(st + 0x168) > 0) {
        func_00282CF0(rot, a1 + ((*(s32 *)(st + 0x168) << 4) + 0x10),
                      a1 + (*(s32 *)(st + 0x168) << 4));
        *(qword *)dir = *(qword *)rot;
        len = func_00282DF0(dir);
        if (D_L12_001B0B10 * 0.020000001f < len)
            func_00282F20(dir, dir, D_L12_001B0B10 * 0.020000001f);
        func_00282CC0(a0 + 0x10, a0 + 0x10, dir);
    } else {
        func_00282CF0(rot, e + 0x10, a1 + (*(s32 *)a1 << 4));
        *(qword *)dir = *(qword *)rot;
        len = func_00282DF0(dir);
        if (D_L12_001B0B10 * 0.020000001f < len)
            func_00282F20(dir, dir, D_L12_001B0B10 * 0.020000001f);
        func_00282CC0(a0 + 0x10, a0 + 0x10, dir);
    }
    if (func_00282E48(a0 + 0x10, entry) <= 0.5f) {
        s32 c = *(s32 *)(st + 0x168);

        if (c == -1)
            return 1;
        if (*(s32 *)a1 - 1 == c) {
            float f;

            *(s32 *)(st + 0x168) = -1;
            f = func_002A89A8(e + 0x10, 0, 0.5f);
            if (*(float *)(e + 0x18) - f < 10.0f)
                *(float *)(e + 0x18) = f + 0.5f;
        } else {
            *(s32 *)(st + 0x168) = c + 1;
        }
    }
    return 0;
}
