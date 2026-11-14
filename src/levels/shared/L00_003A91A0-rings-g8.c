/* func_L00_003A91A0 (1,524 bytes, 27 level places): draws a beam of quad rings in strips. Twin of
 * func_L00_003F6308. Own unit: -O2 -G8 -ffunction-sections -frac2-gcse-hash-fp-117 -frac2-giv-pair-init -frac2-cse2-skip-temp-sum
 * (config/cflags.txt; docs/build/compiler-notes.md). `ring` is declared first in the function,
 * which gives retail's PRE (spill-slot) order with -frac2-gcse-hash-fp-117; the other two
 * switches give the strip loops' giv initial values. Owner standard of 12 November 2026.
 */
#include "common.h"

typedef float BeamVector[4] __attribute__((aligned(16)));
typedef struct { BeamVector point[4]; u32 color[4]; float uv[4][2]; long a,b,c,d; } BeamQuad;
typedef struct { BeamVector origin[3], basis[2]; short enabled, timer; float phase, phase2, rate; } BeamRing;
extern float D_L00_001AF75C __attribute__((sda));
extern float D_L00_001AF754 __attribute__((sda));
extern float D_L00_001AF758 __attribute__((sda));

extern float D_L00_001AF778 __attribute__((sda));
extern float D_L00_001AF788 __attribute__((sda));
extern u32 D_L00_001AF78C __attribute__((sda));
extern int D_L00_001AF794 __attribute__((sda));
extern float D_L00_001AF798 __attribute__((sda));
extern float D_L00_001AF7A4 __attribute__((sda));
extern int D_L00_001AF76C __attribute__((sda));
extern int D_L00_001AF784 __attribute__((sda));

extern u32 D_L00_001AF764 __attribute__((sda));
extern u32 D_L00_001AF768 __attribute__((sda));
extern u32 D_L00_001AF780 __attribute__((sda));
extern u32 D_L00_001AF77C __attribute__((sda));
extern u32 D_L00_001AF790 __attribute__((sda));
extern BeamVector D_L00_00294B60[];
extern BeamVector D_L00_001B8DC0;
extern char *func_L00_0032A088(int, int);
extern int *func_L00_0032A0B8(int, int);
extern void func_00281DE8(void *, int, int, int);
extern void func_00282DD8(void *, void *, void *);
extern int func_00283CF0(float);
extern void func_00282D30(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);


void func_L00_003A91A0(unsigned char *object)
{
    int ring;
    BeamQuad quad;
    BeamVector matrix[4];
    BeamVector vertices[3][20];
    BeamVector temp, side;
    unsigned char *vars = *(unsigned char **)(object + 0x68);
    char *base = func_L00_0032A088(0x5cb, *(short *)(vars + 0x1a));
    BeamRing *rings = (BeamRing *)(base + *func_L00_0032A0B8(0x5cb, *(short *)(vars + 0x1a)));
    int row, j;
    u32 primary, col, alpha;
    float side_u, fade, phase, u, next, phase2;

    func_00281DE8(&quad, 21, 0, 128);
    for (ring = 0; ring < 3; ring++) {
        if (rings[ring].enabled == 0) continue;
        qcopy(matrix[0], rings[ring].basis[0]);
        qcopy(matrix[2], rings[ring].basis[1]);
        func_00282DD8(matrix[1], matrix[0], matrix[2]);
        fade = (float)rings[ring].timer * rings[ring].rate;
        alpha = func_00283CF0(fade * (float)D_L00_001AF76C) << 24;
        col = D_L00_001AF764;
        primary = alpha | col;
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = primary;
        for (row = 0; row < 3; row++) {
            qcopy(matrix[3], rings[ring].origin[row]);
            for (j = 0; j < 20; j++) {
                func_00282D30(temp, D_L00_00294B60[j], D_L00_001AF75C);
                func_002830C0(vertices[row][j], temp, matrix);
            }
        }
        phase = rings[ring].phase;
        col = D_L00_001AF768;
        for (j = 1; j < 3; j++) {
            u = 0;
            for (row = 0; row < 20; row++) {
                qcopy(quad.point[0], vertices[j][row]);
                qcopy(quad.point[1], vertices[j][(row + 1) % 20]);
                qcopy(quad.point[2], vertices[j - 1][row]);
                qcopy(quad.point[3], vertices[j - 1][(row + 1) % 20]);
                next = u + D_L00_001AF758;
                side_u = phase + D_L00_001AF754;
                quad.color[3] = quad.color[2] = col;
                quad.uv[0][0] = phase;
                quad.uv[0][1] = u;
                quad.uv[1][0] = phase;
                quad.uv[1][1] = next;
                quad.uv[2][0] = side_u;
                quad.uv[2][1] = u;
                quad.uv[3][0] = side_u;
                quad.uv[3][1] = next;
                u = next;
                func_00280B90(&quad, 0, 0);
            }
            col = primary;
        }
        func_00281DE8(&quad, 14, 1, 128);
        alpha = func_00283CF0(fade * (float)D_L00_001AF784) << 24;
        col = D_L00_001AF780;
        quad.uv[0][0] = 0;
        quad.uv[0][1] = 0;
        quad.uv[1][0] = 0;
        quad.uv[1][1] = 1;
        quad.uv[2][1] = 0;
        quad.uv[3][1] = 1;
        primary = alpha | col;
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = primary;
        quad.uv[3][0] = 0.5f;
        quad.uv[2][0] = 0.5f;
        col = D_L00_001AF77C;
        func_00282CF0(temp, &D_L00_001B8DC0, rings[ring].origin[0]);
        func_00282DD8(matrix[1], matrix[0], temp);
        func_00282F20(side, matrix[1], D_L00_001AF778);
        for (j = 0; j < 2; j++) {
            func_00282CC0(quad.point[0], rings[ring].origin[j + 1], side);
            func_00282CF0(quad.point[1], rings[ring].origin[j + 1], side);
            func_00282CC0(quad.point[2], rings[ring].origin[j], side);
            func_00282CF0(quad.point[3], rings[ring].origin[j], side);
            quad.color[3] = quad.color[2] = col;
            func_00280B90(&quad, 0, 0);
            col = primary;
            quad.uv[0][0] = quad.uv[1][0] = quad.uv[2][0];
            quad.uv[2][0] = quad.uv[3][0] = 3.0f;
        }
        func_00281DE8(&quad, 23, 1, 128);
        alpha = func_00283CF0(fade * (float)D_L00_001AF794) << 24;
        col = D_L00_001AF790;
        primary = alpha | col;
        quad.uv[2][0] = 1;
        quad.uv[3][0] = 1;
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = primary;
        quad.uv[0][0] = 0;
        quad.uv[0][1] = 0;
        quad.uv[1][0] = 0;
        quad.uv[1][1] = 1;
        quad.uv[2][1] = 0;
        quad.uv[3][1] = 1;
        phase2 = rings[ring].phase2;
        quad.uv[2][0] = quad.uv[3][0] = phase2 + 0.5f;
        col = D_L00_001AF78C;
        func_00282F20(side, matrix[1], D_L00_001AF788);
        for (j = 0; j < 2; j++) {
            func_00282CC0(quad.point[0], rings[ring].origin[j + 1], side);
            func_00282CF0(quad.point[1], rings[ring].origin[j + 1], side);
            func_00282CC0(quad.point[2], rings[ring].origin[j], side);
            func_00282CF0(quad.point[3], rings[ring].origin[j], side);
            quad.color[3] = quad.color[2] = col;
            func_00280B90(&quad, 0, 0);
            col = primary;
            quad.uv[0][0] = quad.uv[1][0] = quad.uv[2][0];
            quad.uv[2][0] = quad.uv[3][0] = phase2 + 3.0f;
        }
    }
}
