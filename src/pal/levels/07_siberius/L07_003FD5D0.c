#include "include_asm.h"

typedef int Q128 __attribute__((mode(TI)));
extern void func_0029FCC0(void *entity, int a, void *out);
extern void func_00282F20(void *, void *, float);
extern void func_L04_0030C4C0(void *, void *, void *, void *, void *, void *, int, int, int);
extern void func_L07_003F6528(char *);
extern char *func_L07_003F65E8(int);

void func_PAL_L07_003FD5D0(char *obj)
{
    char *s2 = *(char **)(obj + 0x68);
    float v10[4];
    float v20[4];
    float v30[4];
    char *p;

    func_0029FCC0(obj, 0, v10);
    *(Q128 *)v30 = 0;
    v30[2] = 5.0f;
    func_00282F20(v20, obj + 0xC0, 2.0f);
    for (;;) {
        p = func_L07_003F65E8(*(int *)(s2 + 0x180));
        if (p == 0) break;
        func_L07_003F6528(p);
        func_L04_0030C4C0(p, v10, v20, p + 0x10, v30, p + 0xF0, 0x4B, 0, 0);
    }
}



#include "common.h"
extern u8 D_L07_001B31AF __attribute__((sda));
extern u8 *D_L07_001B22DC[] __attribute__((sda));
extern s32 D_L07_001B22F8[] __attribute__((sda));
extern s32 func_002A77E0(s32 n);
extern s32 func_00282948(s32 *counter);
extern u8 *func_L07_003F6B88(u8 *a);
extern void func_002A7470(u8 *a0, s32 a1, s32 a2, s32 a3);
extern u8 D_001A7BD0 __attribute__((sda));

void func_PAL_L07_003FD928(u8 *a0)
{
    u8 *p = *(u8 **)(a0 + 0x68);

    if (*(u32 *)(p + 0x420) == 0) {
        if (*(u8 *)(a0 + 0x43) != 2) {
            func_002A7470(a0, 2, 0, 8);
        }
        return;
    }
    if (*(u8 *)(a0 + 0x43) != 8) {
        func_002A7470(a0, 8, 0, 8);
    }
}

void func_PAL_L07_003FD988(u8 *a0)
{
    u8 *p = *(u8 **)(a0 + 0x68);

    if (*(u32 *)(p + 0x420) == 0) {
        if (*(u8 *)(a0 + 0x43) != 3) {
            func_002A7470(a0, 3, 0, 8);
        }
        return;
    }
    if (*(u8 *)(a0 + 0x43) != 9) {
        func_002A7470(a0, 9, 0, 8);
    }
}

