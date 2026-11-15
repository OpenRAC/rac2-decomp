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
extern SelectState g_hero_moby_default;
extern SelectTable g_copy_setup_data;
extern s32 D_001BAF30[];
extern unsigned long D_001C4DC0[3];
extern s32 D_001A91E0 __attribute__((sda));
extern void gfx_wait_for_dma_status_bits(s32);
extern s32 func_PAL_002B8838(s32, s32, s32);
extern void tex_relocate_block(s32, s32, void *, s32);

void func_PAL_00292F00(s32 n) {
    SelectTable *b;
    s32 h;
    g_hero_moby_default.f18 = n;
    gfx_wait_for_dma_status_bits(1);
    b = &g_copy_setup_data;
    h = D_001BAF30[0];
    func_PAL_002B8838(h, b->e[n].a + b->base, b->e[n].b);
    D_001C4DC0[0] = g_hero_moby_default.f38;
    D_001C4DC0[1] = 0xFFA0000000E0;
    D_001C4DC0[2] = 0x40000400004000;
    tex_relocate_block(h, 0, &D_001A91E0, -1);
}
