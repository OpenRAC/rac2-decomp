#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 *D_001B251C[] __attribute__((sda));
extern void func_PAL_L10_003FA370(u8 *);
extern void func_L10_003F61C8(u8 *);
extern void func_L00_00381F78(void);
extern int func_L00_00367720();
extern u8 *func_002ED688(u8 *);
extern void func_L05_00379E60(u8 *, void *, int, int);
extern void func_L05_0037B538(u8 *, int, int, int);
extern f32 func_002A7940(void);
extern f32 func_00283198(f32);
extern f32 func_00283180(f32);
extern f32 func_00283B98(f32, f32);
extern void func_0029FC20(u8 *, int, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, f32);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_L00_002E6EF8(void *, void *);

void func_PAL_L10_003FA158(u8 *a0) {
    f32 v0[4] __attribute__((aligned(16)));
    f32 a[4][4] __attribute__((aligned(16)));
    f32 d[4] __attribute__((aligned(16)));
    f32 e[4] __attribute__((aligned(16)));
    f32 q[12] __attribute__((aligned(16)));
    u8 *s5 = *(u8 **)(a0 + 0x68);
    u8 *s3;
    f32 *s1;
    f32 ang;
    u8 *obj;

    *(TI128 *)v0 = 0;
    v0[2] = 1.0f;
    switch (a0[0x20]) {
    case 0:
        a0[0x30] = 0xFF;
        if (func_L00_00367720() == 0) {
            return;
        }
        func_PAL_L10_003FA370(a0);
        if (*(int *)(s5 + 0x268) != 0) {
            func_L05_00379E60(a0, func_L00_00381F78, 0, 0);
        }
        *(f32 *)(s5 + 0x27C) = func_002A7940();
        break;
    case 1:
        s3 = a0 + 0xC0;
        s1 = (f32 *)(a0 + 0xD0);
        *(int *)(func_002ED688(a0) + 0x14C) = 0;
        ang = func_00283B98(*(f32 *)(s5 + 0x27C), 0.013962637f);
        obj = D_001B251C[0] + (*(int *)(s5 + 0x260) << 8);
        *(f32 *)(s5 + 0x27C) = ang;
        func_0029FC20(obj, *(int *)(s5 + 0x26C), a);
        func_00282F20(d, a[1], 50.0f);
        func_00282CC0(d, a[3], d);
        func_00282F20(s3, a[1], -1.0f);
        func_00282DD8(s1, s3, v0);
        func_00282F20(s1, s1, 1.0f);
        func_00282DD8(a0 + 0xE0, s1, s3);
        func_00282D30(e, s3, func_00283198(*(f32 *)(s5 + 0x27C) * 0.5f));
        e[3] = func_00283180(*(f32 *)(s5 + 0x27C) * 0.5f);
        func_00283958(e, q);
        func_00283738(s3, q, s3);
        qcopy(a0 + 0x10, d);
        func_L05_0037B538(a0, 0, 0, 0);
        break;
    }
    func_L00_002E6EF8(func_L10_003F61C8, a0);
}
