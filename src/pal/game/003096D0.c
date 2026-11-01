#include "include_asm.h"



INCLUDE_ASM("asm/pal/game", func_PAL_00309A30);

#include "common.h"
typedef struct { f32 f[4]; } __attribute__((aligned(16))) V4;
typedef struct { s32 f00; u8 p04[8]; s32 f0C; V4 v10; } N;
typedef struct { u8 p00[0x10]; V4 v10; u8 p20[0x48]; N *f68; u8 p6C[0x54]; V4 vC0; } X;
typedef struct { u8 p0[0x150]; V4 v150; u8 p160[0x2294-0x160]; s32 i2294; } TrailHero;
extern TrailHero D_00189E20;
extern s32 D_001B1688 __attribute__((sda));
extern f32 func_002A7940(void), func_00283180(f32), func_00283198(f32);
extern f32 func_002A7878(f32, f32);
extern void func_00283098(V4 *, V4 *, V4 *);
extern void func_00282CC0(V4 *, V4 *, V4 *);
extern void func_00282CF0(V4 *, V4 *, V4 *);
extern void func_00282F20(V4 *, V4 *, f32);
extern f32 func_00282E48(V4 *, V4 *);
extern s32 func_002A77E0(s32);
extern u8 *func_002BD8B0(V4 *, V4 *, s32, s32, s32, s32, f32);
extern u8 *func_PAL_002BE9A8(V4 *, f32, f32, f32, f32, s32, V4 *, u32, s32);

/* Adapted from RAC1 emit_beam_trail_particles (OpenRAC, GPL-3.0). */
void func_PAL_0030A078(X *x) {
    V4 l0;
    V4 a;
    V4 d;
    V4 t;
    N *g;
    f32 s;
    f32 q;
    u32 col;
    s32 i;
    s32 n;
    s32 m;
    u8 *p;

    g = x->f68;
    l0.f[0] = func_00283180(func_002A7940()) * 0.05f;
    l0.f[1] = func_00283198(func_002A7940()) * 0.05f;
    l0.f[2] = 0.0f;
    l0.f[2] = -func_002A7878(0.01f, 0.03f);
    func_00283098(&l0, &l0, &x->vC0);
    func_00282CC0(&l0, &l0, &D_00189E20.v150);
    qcopy(&a, &x->v10);
    if (D_00189E20.i2294 == 0x7B) {
        if (D_001B1688 % 3 == 0) {
            func_002BD8B0(&a, &l0, 0x4F007FFF, 0x1FFFFFFF, 8, 1, 10000.0f);
        }
    } else {
        func_002BD8B0(&a, &l0, 0x4F007FFF, 0x1FFFFFFF, 8, 1, 10000.0f);
    }
    if (g->f0C) {
        s = func_00282E48(&g->v10, &a) * 0.5f;
        func_00282CF0(&d, &g->v10, &a);
        for (i = 1; i < 2; i++) {
            func_00282F20(&t, &d, s * (f32)i);
            func_00282CC0(&t, &a, &t);
            func_002BD8B0(&t, &l0, 0x4F007FFF, 0x1FFFFFFF, 8, 1, 10000.0f);
        }
    }
    g->f00 = func_002A77E0(8);
    q = 1.075f;
    col = 0x808080;
    l0.f[0] = 0.0f;
    l0.f[1] = 0.0f;
    l0.f[2] = -0.3f;
    l0.f[3] = 1.0f;
    func_00283098(&l0, &l0, &x->vC0);
    func_00282CC0(&a, &x->v10, &l0);
    l0.f[3] = 1.0f;
    l0.f[2] = -0.075f;
    l0.f[0] = 0.0f;
    l0.f[1] = 0.0f;
    func_00283098(&l0, &l0, &x->vC0);
    l0.f[2] = 0.025f;
    func_00282CC0(&l0, &l0, &D_00189E20.v150);
    if (D_00189E20.i2294 == 8) {
        col = 0xA0A0A0;
        q = 1.0165f;
        l0.f[2] -= 0.10000001f;
    }
    if (D_00189E20.i2294 == 0x7B) {
        col = 0xA0A0A0;
        q = 1.037f;
        l0.f[2] -= 0.060000002f;
    }
    p = func_PAL_002BE9A8(&a, 0.05f, 1.01f, q, 30000.0f, 6, &l0, col, 0);
    if (p) p[3] = 0x44;
    if (g->f0C) {
        s = func_00282E48(&g->v10, &a) * 0.16667f;
        func_00282CF0(&d, &g->v10, &a);
        m = D_00189E20.i2294;
        n = 4;
        if (m == 8) n = 2;
        if (m == 0x7B) n = 1;
        for (i = 1; i < n; i++) {
            func_00282F20(&t, &d, s * (f32)i);
            func_00282CC0(&t, &a, &t);
            p = func_PAL_002BE9A8(&t, 0.05f, 1.01f, q, 30000.0f, 6, &l0, col, 0);
            if (p) p[3] = 0x44;
        }
    }
    qcopy(&g->v10, &a);
    g->f0C = 1;
}



INCLUDE_ASM("asm/pal/game", func_PAL_0030A9D8);

INCLUDE_ASM("asm/pal/game", func_PAL_0030B4E0);

INCLUDE_ASM("asm/pal/game", func_PAL_0030B6C0);

INCLUDE_ASM("asm/pal/game", func_PAL_0030CE20);
