#include "common.h"

/* func_00308600 is defined in 00308600-spawn.c. */

INCLUDE_ASM("asm/game", func_00308768);

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
extern u8 *func_002BDCE8(V4 *, f32, f32, f32, f32, s32, V4 *, u32, s32);

/* Adapted from RAC1 emit_beam_trail_particles (OpenRAC, GPL-3.0). */
void func_00308DB8(X *x) {
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
            func_002BD8B0(&a, &l0, 0x4F007FFF, 0x1FFFFFFF, 10, 1, 10000.0f);
        }
    } else {
        func_002BD8B0(&a, &l0, 0x4F007FFF, 0x1FFFFFFF, 10, 1, 10000.0f);
    }
    if (g->f0C) {
        s = func_00282E48(&g->v10, &a) * 0.5f;
        func_00282CF0(&d, &g->v10, &a);
        for (i = 1; i < 2; i++) {
            func_00282F20(&t, &d, s * (f32)i);
            func_00282CC0(&t, &a, &t);
            func_002BD8B0(&t, &l0, 0x4F007FFF, 0x1FFFFFFF, 10, 1, 10000.0f);
        }
    }
    g->f00 = func_002A77E0(10);
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
        l0.f[2] -= 0.0833333358f;
    }
    if (D_00189E20.i2294 == 0x7B) {
        col = 0xA0A0A0;
        q = 1.037f;
        l0.f[2] -= 0.0500000045f;
    }
    p = func_002BDCE8(&a, 0.05f, 1.01f, q, 30000.0f, 6, &l0, col, 0);
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
            p = func_002BDCE8(&t, 0.05f, 1.01f, q, 30000.0f, 6, &l0, col, 0);
            if (p) p[3] = 0x44;
        }
    }
    qcopy(&g->v10, &a);
    g->f0C = 1;
}


/* func_003092A0 is defined in 003092A0.c. */


/* func_0030A188 is defined in 0030A188-g8.c. */


/* func_0030BBA0 is defined in 00308600-beam-g8.c. */

/* func_0030C188 is defined in 0030C188-g8.c. */




/* func_0030CAD0 is defined in 0030CAD0-g8.c. */


/* func_0030D430 is matched in its own unit, src/game/0030D430-g8.c. */

/* func_0030D5B8 is defined in 00308600-ribbon-g8.c. */

/* func_0030DB88 is defined in 0030DB88-g8.c. */

/* func_0030DE88 is defined in 0030DE88-g8.c. */



extern char *func_002A9640(char *, int, int);
extern void func_00282948(int *);
extern void func_002E5CF8(int, int, char *);
extern void func_002AB800(char *, char *);
extern void func_002ACB48(float *, float);
/* Integer and float arguments have separate register banks. This interleaving
   preserves the measured argument setup order. */
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void func_002AB8C0(char *, char *);

void func_0030E700(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *hit = func_002A9640(object, 0x30001, 0);
    float direction[4];

    func_00282948((int *)(state + 0x28));
    func_00282948((int *)(state + 0x2C));
    if (hit != 0 && (*(int *)(hit + 0x20) != *(int *)(state + 0x34) ||
                     *(int *)(state + 0x28) == 0)) {
        *(int *)(state + 0x34) = *(int *)(hit + 0x20);
        *(int *)(state + 0x28) = 30;
        if (*(int *)(state + 0x2C) == 0) {
            if (*(unsigned short *)(hit + 0x28) == 0x101 && *(int *)(state + 0x30) == 0) {
                *(int *)(state + 0x2C) = 100;
                *(int *)(state + 0x30) = 1;
            } else {
                *(int *)(state + 0x30) = 0;
            }
        }
        func_002E5CF8(0, 0, object);
        *(float *)(state + 0x24) -= *(float *)(hit + 0x2C);
        func_002AB800(object, state);
        if (*(float *)(state + 0x24) < 0.0f) {
            func_002ACB48(direction, 0.5f);
            func_002ABBB8(object, direction, 0, 0.0f, 0.0f, 0, 0, 0,
                         4.0f, 3.0f, 9.0f, 1.0f, 2, 12.0f, 1, 1, -1, 0, 0x810001);
            object[0x20] = 6;
        }
    }
    ((unsigned char *)object)[0xA8] = 0xFF;
    func_002AB8C0(object, state);
}

/* func_0030E8A8 is defined in 00308600-spring.c. */

/* func_0030ECC8 is defined in 00308600-ammo-g8.c. */

/* func_0030F408 is defined in 00308600-wavy.c. */
