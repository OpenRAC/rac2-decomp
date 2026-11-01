#include "include_asm.h"

#include "common.h"
typedef s32 Quadword __attribute__((mode(__TI__)));
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, s32, s32, s32, s32, s32, u8, void *);
extern void func_L00_00324F18(void *, void *, f32, f32, f32);
extern void *func_PAL_L00_003FB330(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);
extern s32 func_00282948(void *);
extern void func_002A7750(void *, s32, s32);
extern void func_00283098(void *, void *, void *);
extern s32 func_002A7820(s32, s32);
extern void func_PAL_L00_002ED7E8(void *, void *, void *, f32, f32, s32, s32, f32, f32, f32);
extern f32 D_L12_001B1FD0[8] SDATA(D_L12_001B1FD0) __attribute__((sda));
extern f32 D_L12_001B1FC8[2] __attribute__((sda));
extern f32 D_L12_001B1FC0[2] __attribute__((sda));
extern s32 D_L12_001B2000 __attribute__((sda));
extern f32 D_L12_001B1FF0[] __attribute__((sda));
extern f32 D_L12_001B1FF0_gp SDATA(D_L12_001B1FF0) __attribute__((sda));

void func_PAL_L12_00426674(u8 *self) {
    s32 *st = *(s32 **)(self + 0x68);
    f32 vec[4];
    switch (self[0x20]) {
    case 0:
        func_PAL_L00_0032C328(self, D_L12_001B1FD0, D_L12_001B1FC8, D_L12_001B1FC0, 65535, 0, D_L12_001B2000, 0, 65535, 255, 0);
        *(s16 *)(self + 0x7c) = 0;
        func_L00_00324F18(self, vec, D_L12_001B1FF0_gp, D_L12_001B1FF0[1], D_L12_001B1FF0[2]);
        func_PAL_L00_003FB330(vec, 0, 25, 20, 20, 20, 45, 0, 1, 1, 1, 0, *(f32 *)(self + 0x2c)*7.0f, 20.0f);
        st[0] = 17;
        func_002A7750(self, 1, -1);
        break;
    case 1:
        if (func_00282948(st)) {
            func_L00_00324F18(self, vec, D_L12_001B1FF0_gp, D_L12_001B1FF0[1], D_L12_001B1FF0[2]);
            func_PAL_L00_003FB330(vec, 0, 25, 20, 20, 20, 45, 0, 0, 0, 0, 0, *(f32 *)(self + 0x2c)*3.5f, 20.0f);
            st[1] = 100;
            func_002A7750(self, 2, -1);
        }
        break;
    case 2:
        if (func_00282948(st + 1) || st[1] >= 76) {
            *(Quadword *)vec = 0;
            vec[1] = -0.020000001f;
            vec[2] = 0.060000002f;
            func_00283098(vec, vec, self + 0xc0);
            func_PAL_L00_002ED7E8(self, &D_L12_001B1FF0_gp, vec, 0.0f, 0.040000003f, func_002A7820(3, 6), 0, 0.5f, 15.0f, 2.0f);
            func_PAL_L00_002ED7E8(self, &D_L12_001B1FF0_gp, vec, 0.0f, 0.040000003f, func_002A7820(3, 6), 1, 0.5f, 15.0f, 2.0f);
            st[1] = ((s32)(func_002A7820(45, 90)) * 5 + 2) / 6;
        }
        break;
    }
}
