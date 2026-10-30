/* Reconstruction retained 30 October 2026; not a linked match.
 * Profile: -O2 -G8 -ffunction-sections.
 * 1440/1524 bytes; full 0x560 frame retained, but long render-loop pointer and FP allocation differ.
 * Reopen with a render-record/source-loop witness; retain complete matrix and ring buffers.
 * ABI/bounds: Quad is 0x90 bytes on EE (long is 64-bit); basis is four complete rows; vertices are three arrays of twenty 16-byte vectors.
 * Local checks and release presence are recorded in the shared NMC index.
 * Semantic equivalence has not been validated by the functional gate.
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

/* Draws three twenty-point rings and two crossed billboard pairs per enabled
 * beam slot. All 0x90 bytes of the quad and the complete 4-row basis are kept. */
void func_L00_003A91A0(unsigned char *object)
{
    BeamQuad quad;
    BeamVector matrix[4];
    BeamVector vertices[3][20];
    BeamVector temp, side;
    unsigned char *vars = *(unsigned char **)(object + 0x68);
    char *base = func_L00_0032A088(0x5cb, *(short *)(vars + 0x1a));
    BeamRing *rings = (BeamRing *)(base + *func_L00_0032A0B8(0x5cb, *(short *)(vars + 0x1a)));
    int ring, row, j, alpha;
    u32 primary, secondary, col;
    float fade, phase, u, next;
    func_00281DE8(&quad, 21, 0, 128);
    for (ring = 0; ring < 3; ++ring) {
        BeamRing *r = &rings[ring];
        if (!r->enabled) continue;
        qcopy(matrix[0], r->basis[0]);
        qcopy(matrix[2], r->basis[1]);
        func_00282DD8(matrix[1], matrix[0], matrix[2]);
        fade = (float)r->timer * r->rate;
        alpha = func_00283CF0(fade * (float)D_L00_001AF76C);
        primary = ((u32)alpha << 24) | D_L00_001AF764;
        for (row = 0; row < 3; ++row) {
            quad.color[3] = quad.color[2] = quad.color[1] = quad.color[0] = primary;
            qcopy(matrix[3], r->origin[row]);
            for (j = 0; j < 20; ++j) {
                func_00282D30(temp, D_L00_00294B60[j], D_L00_001AF75C);
                func_002830C0(vertices[row][j], temp, matrix);
            }
        }
        phase = r->phase;
        secondary = D_L00_001AF768;
        for (row = 0; row < 2; ++row) {
            u = 0;
            col = secondary;
            for (j = 0; j < 20; ++j) {
                qcopy(quad.point[0], vertices[row + 1][j]);
                qcopy(quad.point[1], vertices[row + 1][(j + 1) % 20]);
                qcopy(quad.point[2], vertices[row][j]);
                qcopy(quad.point[3], vertices[row][(j + 1) % 20]);
                next = u + D_L00_001AF758;
                quad.uv[2][1] = quad.uv[0][1] = u;
                quad.uv[3][0] = quad.uv[2][0] = phase + D_L00_001AF754;
                quad.uv[0][0] = quad.uv[1][0] = phase;
                quad.uv[1][1] = quad.uv[3][1] = next;
                quad.color[2] = quad.color[3] = col;
                func_00280B90(&quad, 0, 0);
                u = next;
            }
            secondary = primary;
        }
        func_00281DE8(&quad, 14, 1, 128);
        primary = ((u32)func_00283CF0(fade * (float)D_L00_001AF784) << 24) | D_L00_001AF780;
        quad.uv[0][0] = quad.uv[0][1] = quad.uv[1][0] = quad.uv[2][1] = 0;
        quad.uv[1][1] = quad.uv[3][1] = 1;
        quad.uv[2][0] = quad.uv[3][0] = 0.5f;
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = primary;
        func_00282CF0(temp, &D_L00_001B8DC0, r->origin);
        func_00282DD8(matrix[1], matrix[0], temp);
        func_00282F20(side, matrix[1], D_L00_001AF778);
        col = D_L00_001AF77C;
        for (j = 0; j < 2; ++j) {
            func_00282CC0(quad.point[0], r->origin[j + 1], side);
            func_00282CF0(quad.point[1], r->origin[j + 1], side);
            func_00282CC0(quad.point[2], r->origin[j], side);
            func_00282CF0(quad.point[3], r->origin[j], side);
            quad.color[2] = quad.color[3] = col;
            func_00280B90(&quad, 0, 0);
            col = primary;
            quad.uv[0][0] = quad.uv[1][0] = quad.uv[2][0];
            quad.uv[2][0] = quad.uv[3][0] = 3;
        }
        func_00281DE8(&quad, 23, 1, 128);
        primary = ((u32)func_00283CF0(fade * (float)D_L00_001AF794) << 24) | D_L00_001AF790;
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = primary;
        quad.uv[0][0] = quad.uv[0][1] = quad.uv[1][0] = quad.uv[2][1] = 0;
        quad.uv[1][1] = quad.uv[3][1] = 1;
        quad.uv[2][0] = quad.uv[3][0] = r->phase2 + 0.5f;
        func_00282F20(side, matrix[1], D_L00_001AF788);
        col = D_L00_001AF78C;
        for (j = 0; j < 2; ++j) {
            func_00282CC0(quad.point[0], r->origin[j + 1], side);
            func_00282CF0(quad.point[1], r->origin[j + 1], side);
            func_00282CC0(quad.point[2], r->origin[j], side);
            func_00282CF0(quad.point[3], r->origin[j], side);
            quad.color[2] = quad.color[3] = col;
            func_00280B90(&quad, 0, 0);
            col = primary;
            quad.uv[0][0] = quad.uv[1][0] = quad.uv[2][0];
            quad.uv[2][0] = quad.uv[3][0] = r->phase2 + 3.0f;
        }
    }
}
