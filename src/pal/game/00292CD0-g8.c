#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 p0[0x18];
    s32 f18;
    u8 p1c[0x1C];
    unsigned long f38;
} SelectState;
typedef struct {
    u8 p0[0x3E24];
    s32 base;
    u8 p3e28[0x48D8 - 0x3E28];
    struct {
        s32 a;
        s32 b;
    } e[1];
} SelectTable;
extern SelectState D_00152C00;
extern SelectTable D_0014B540;
extern s32 D_001BAF30[];
extern unsigned long D_001C4DC0[3];
extern s32 D_001A91E0 __attribute__((sda));
extern void func_002FC3C0(s32);
extern s32 func_PAL_002B8838(s32, s32, s32);
extern void func_002934F8(s32, s32, void *, s32);

void func_PAL_00292F00(s32 n) {
    SelectTable *b;
    s32 h;
    D_00152C00.f18 = n;
    func_002FC3C0(1);
    b = &D_0014B540;
    h = D_001BAF30[0];
    func_PAL_002B8838(h, b->e[n].a + b->base, b->e[n].b);
    D_001C4DC0[0] = D_00152C00.f38;
    D_001C4DC0[1] = 0xFFA0000000E0;
    D_001C4DC0[2] = 0x40000400004000;
    func_002934F8(h, 0, &D_001A91E0, -1);
}
