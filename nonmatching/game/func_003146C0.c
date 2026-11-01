/* Closer B, 2026-11-01: MACRO_ADDR on D_001B24C0 fixes both call setups: 1588/1588, 4 words, the s1/s2 swap
 * of the v and u iterators. Allocno priorities: v 14 refs over 42 insns, u 14 over 41, so u wins; retail
 * needs v first, with v still read first (swapping the sets also swaps which address gets the spill).
 * Ties: declaration order, increment order, v++ pairs, a scoped pointer copy for the second store.
 */
/* Tier: sol-high, task v1099.
 * Best: 1588/1588 bytes, 0/28 USA v1.01 places; first difference +0x108.
 * Profile: -O2 -G8 -ffunction-sections -g (current pinned toolchain).
 * Fifteen instruction words differ outside relocation fields: +0x108, +0x110,
 * +0x118, +0x140, +0x144, +0x148, +0x14C, +0x518, +0x520, +0x598,
 * +0x59C, +0x5A4, +0x5B4, +0x5C0, +0x5C8. These are call setup for the
 * second func_002B00D8/center add and swapped s1/s2 UV iterators.
 * Improvements over the earlier draft: sequential texture[3] |= expressions
 * recover GS packing without the unavailable no-reduce-tree-depth option;
 * separate color branches recover color-store order and sphere allocation.
 * A distinct surface_owner reused for the class test recovers qcopy operands;
 * UV bases formed inside the loop recover spill slots; SDATA names the actual
 * GP-relative index array. All declarations required are retained below.
 * Tied: typed Moby fields, a position temporary, two FP argument interleavings,
 * a displacement temporary and UV declaration order. Repeated center setup in
 * both state branches grows to 1668 bytes; indexed UVs shrink to 1568 bytes.
 * Next: evidence for a different center-copy expression or UV pointer lifetime.
 * No linked build attempted. Adapted from RAC1 draw_nanotech_ball (GPL-3.0).
 */
#include "common.h"
typedef struct { float x,y,z; } BallVec3;
typedef struct { u32 points[4][4]; u32 colors[4]; float texcoords[8]; u64 texture[4]; } __attribute__((aligned(16))) BallQuad;
extern float D_001AF12C __attribute__((sda));
extern float D_001AF250 __attribute__((sda));
extern float D_001AF260 __attribute__((sda));
extern float D_001AF264 __attribute__((sda));
extern int D_001AF230 __attribute__((sda));
extern int D_001AF234 __attribute__((sda));
extern int D_001AF238 __attribute__((sda));
extern int D_001AF23C __attribute__((sda));
extern int D_001AF240 __attribute__((sda));
extern u32 D_001AF244 __attribute__((sda));
extern u32 D_001AF248 __attribute__((sda));
extern u32 D_001AF24C __attribute__((sda));
extern u32 D_001AF254 __attribute__((sda));
extern u32 D_001AF258 __attribute__((sda));
extern u32 D_001AF25C __attribute__((sda));
extern char D_001B5340[];
extern char D_001B24C0[] MACRO_ADDR;
extern char D_002668D0[];
extern char D_00267AF0[];
extern char D_00268410[];
extern char D_00268A10[];
extern char D_00268B10[];
extern char D_00268C10[];
extern char D_00229C70[];
extern short D_001AF210[] SDATA(D_001AF210);
extern int D_001B24D0;
extern s64 func_0027C878(int);
extern void func_002FC560(int,u64);
extern void func_00282CC0(void *,void *,void *), func_00282CF0(void *,void *,void *), func_00282DD8(void *,void *,void *), func_002830C0(void *,void *,void *);
extern void func_00282F20(void *,void *,float), func_00282D30(void *,void *,float), func_00282F70(void *,void *,float);
extern void func_00280328(void), func_00281810(int,void *,void *,void *,int), func_00280B90(void *,void *,int);
extern int func_00283CF0(float), func_00312E10(unsigned char *);
extern float func_00283D00(float,float);
extern void func_002B00D8(void *,void *,void *,float);
/* Adapted from RAC1 draw_nanotech_ball (GPL-3.0); RAC2 selects alternate colors and owner geometry. */
void func_003146C0(unsigned char *moby) {
    BallQuad quad;
    float basis[4] __attribute__((aligned(16)));
    float *forward;
    float side[4] __attribute__((aligned(16)));
    float up[4] __attribute__((aligned(16)));
    float center[4] __attribute__((aligned(16)));
    float view_dir[4] __attribute__((aligned(16)));
    float to_camera[4] __attribute__((aligned(16)));
    float vertex[4] __attribute__((aligned(16)));
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    unsigned char *owner;
    float pulse = *(float *)vars / D_001AF12C;
    u32 sphere_colors[290];
    int i, j, color;
    short *indices;
    short *row;
    short *rows;
    char *corner;
    char *env_corners;
    char *outer, *inner;
    float *u, *v;
    float *v_base, *u_base;

    quad.texture[1] = func_0027C878(D_001AF244);
    quad.texture[2] = 0xff9000000260ULL;
    quad.texture[3] = (u64)D_001AF230;
    quad.texture[3] |= (u64)D_001AF234 << 2;
    quad.texture[3] |= (u64)D_001AF238 << 4;
    quad.texture[3] |= (u64)D_001AF23C << 6;
    quad.texture[3] |= (u64)D_001AF240 << 32;
    quad.texture[0] = 0;
    func_002FC560(0x47, 0x53001);
    if (moby[0x20] == 1) {
        unsigned char *owner = *(unsigned char **)(moby + 0xB8);
        qcopy(moby + 0x10, owner + 0x10);
        qcopy(vars + 0x10, owner + 0x10);
        func_002B00D8(moby + 0x10, vars + 0x10, vars + 0x10, -0.5f);
    }
    forward = basis;
    center[0] = *(float *)(moby + 0x10);
    center[1] = *(float *)(moby + 0x14);
    center[2] = *(float *)(moby + 0x18);
    func_002B00D8(moby + 0x10, center, center, -0.5f - *(float *)vars);
    center[3] = 1.0f;
    func_00282CC0(&center, &center, D_001B24C0);
    func_00282CF0(&to_camera, D_001B5340, &center);
    func_00282F20(forward, &to_camera, 1.0f);
    owner = *(unsigned char **)(moby + 0xB8);
    func_00282DD8(&side, forward, owner + 0xE0);
    func_00282F20(&side, &side, 1.0f);
    func_00282DD8(&up, &side, forward);
    if (vars[0x57]) {
        quad.colors[3] = D_001AF24C;
        quad.colors[2] = D_001AF24C;
        quad.colors[1] = D_001AF24C;
        quad.colors[0] = D_001AF24C;
    } else {
        quad.colors[3] = D_001AF248;
        quad.colors[2] = D_001AF248;
        quad.colors[1] = D_001AF248;
        quad.colors[0] = D_001AF248;
    }
    func_002FC560(6, func_0027C878(D_001AF244));
    func_002FC560(0x42, 0x8000000044ULL);
    func_002FC560(8, 0);
    func_002FC560(0x14, 0xff9000000260ULL);
    func_002FC560(0x4a, 0);
    func_00280328();
    for (j = 0; j < 0x122; j++) {
        func_002830C0(&vertex, D_002668D0 + j * 16, basis);
        {
            float x = vertex[0], y = vertex[1], z = vertex[2];
            ((BallVec3 *)D_00229C70)[j].x = x;
            ((BallVec3 *)D_00229C70)[j].y = y;
            ((BallVec3 *)D_00229C70)[j].z = z;
            sphere_colors[j] = quad.colors[0];
        }
    }
    func_00281810(0x94, D_00229C70,
                                sphere_colors, D_00267AF0, 1);
    func_00281810(0x6d, D_00229C70 + 0x6d8,
                                sphere_colors + 0x92,
                                D_00267AF0 + 0x490, 1);
    func_00281810(0x24, D_00229C70 + 0xbe8,
                                sphere_colors + 0xFE,
                                D_00267AF0 + 0x7f0, 1);
    quad.texture[1] = func_0027C878(0xb);
    quad.texture[3] = 0x8000000048ULL;
    color = func_00283CF0(pulse * 64.0f + 128.0f);
    color += D_001B24D0;
    if (vars[0x57]) {
        quad.colors[1] = ((u32)color << 24) | D_001AF258;
        quad.colors[0] = quad.colors[1];
    } else {
        quad.colors[1] = ((u32)color << 24) | D_001AF254;
        quad.colors[0] = quad.colors[1];
    }
    quad.colors[3] = 0;
    quad.colors[2] = 0;
    for (i = 0; i < 32; i++) {
        indices = (short *)(D_00268A10 + i * 8);
        j = 0;
        inner = (char *)quad.points;
        outer = (char *)quad.points;
        for (; j < 4; j++) {
            short index = *indices;
            if (j >= 2)
                func_00282D30(outer, D_00268410 + index * 16,
                             D_001AF250 * D_001AF264);
            else
                func_00282D30(inner, D_00268410 + index * 16, D_001AF250);
            inner += 16;
            outer += 16;
            indices++;
        }
        quad.texcoords[0] = 0.5f;
        quad.texcoords[1] = 0.5f;
        quad.texcoords[2] = 0.5f;
        quad.texcoords[3] = 0.5f;
        quad.texcoords[4] = 0.5f;
        quad.texcoords[5] = 1.0f;
        quad.texcoords[6] = 0.5f;
        quad.texcoords[7] = 1.0f;
        func_00280B90(&quad, basis, 0);
    }
    if (func_00312E10((u8 *)moby)) {
        unsigned char *surface_owner;
        quad.texture[1] = func_0027C878(D_001AF25C);
        quad.colors[3] = 0x107f7f7f;
        quad.colors[2] = 0x107f7f7f;
        quad.colors[1] = 0x107f7f7f;
        quad.colors[0] = 0x107f7f7f;
        quad.texture[3] = 0x8000000044ULL;
        {
            surface_owner = *(unsigned char **)(moby + 0xB8);
            qcopy(basis, surface_owner + 0xC0);
            qcopy(&side, surface_owner + 0xD0);
            qcopy(&up, surface_owner + 0xE0);
        }
        center[2] = *(float *)(moby + 0x18);

        rows = (short *)D_001AF210;
        if (*(short *)(surface_owner + 0xAA) == 0x1F5)
            env_corners = D_00268C10;
        else
            env_corners = D_00268B10;
        for (i = 0; i < 4; i++) {
            v = &quad.texcoords[0];
            u = &quad.texcoords[1];
            row = (short *)(i * 8 + (u32)rows);
            corner = (char *)quad.points;
            for (j = 3; j >= 0; j--) {
                func_002830C0(corner, env_corners + (*row++) * 16,
                                       basis);
                func_00282CF0(view_dir, corner, D_001B5340);
                corner += 16;
                view_dir[1] = view_dir[2];
                func_00282F70(view_dir, view_dir, D_001AF260);
                *v = view_dir[0] * 0.5f + 0.5f;
                *v = func_00283D00(*v, 8.0f);
                v += 2;
                *u = view_dir[1] * 0.5f + 0.5f;
                *u = func_00283D00(*u, 8.0f);
                u += 2;
            }
            func_00280B90(&quad, 0, 0);
        }
    }
    func_002FC560(0x47, 0x5360b);
}
