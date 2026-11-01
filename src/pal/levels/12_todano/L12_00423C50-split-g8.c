#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern void func_002A7750(void *, int, int);
extern s32 func_002E5CF8(s32, s32, s32);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002ACBC8(void *, int);
extern char D_00189EA0[];
extern char D_L12_001B9E00[];
extern float func_00282E80(void *, void *);
extern int func_00282948(void *);
extern float func_002AA548(void *, void *, float, float, float, float);
extern void func_00282D30(float, void *, void *);

void func_PAL_L12_00424110(u8 *a0)
{
    s32 *s = *(s32 **)(a0 + 0x68);
    int state = a0[0x20];
    f32 v[4];

    switch (state) {
    case 0:
        qcopy((u8 *)s + 0x10, a0 + 0x10);
        func_002A7750(a0, 1, -1);
        a0[0x30] = 0x7F;
        break;
    case 1:
        if (func_00282E80(a0 + 0x10, D_L12_001B2E9C + (s[0] << 8) + 0x10) < 5.0f) {
            s[0xB] = state;
            s[8] = 0x32;
        } else if ((func_002ACBC8(D_00189EA0, s[1]) && s[0xB] != 0) ||
                   (func_002ACBC8(D_L12_001B9E00, s[1]) && s[0xB] != 0)) {
            s[8] = 0x32;
        }
        if (func_00282948((u8 *)s + 0x20))
            func_002AA548((u8 *)s + 0x24, (u8 *)s + 0x28, 0.0f, 0.00080000004f, 0.00080000004f, 0.080000006f);
        else
            func_002AA548((u8 *)s + 0x24, (u8 *)s + 0x28, 1.0f, 0.00080000004f, 0.00080000004f, 0.080000006f);
        if (*(f32 *)((u8 *)s + 0x28) != 0.0f) {
            *(TI128 *)v = 0;
            v[0] = 1.0f;
            v[2] = 3.0f;
            func_00283098(v, v, a0 + 0xC0);
            func_00282D30(*(f32 *)((u8 *)s + 0x24), v, v);
            func_00282CC0(a0 + 0x10, (u8 *)s + 0x10, v);
            if (s[0xC] % 120 == 0)
                func_002E5CF8(0, 0, (s32)a0);
            s[0xC]++;
        } else {
            s[0xC] = 0;
        }
        break;
    }
}
