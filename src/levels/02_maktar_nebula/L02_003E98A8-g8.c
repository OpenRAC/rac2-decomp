#include "common.h"
extern char *g_moby_l02_pool;
extern char D_L02_001B0BC0[] SDATA(D_L02_001B0BC0);
extern float D_L02_001B0C68 __attribute__((sda));
extern float D_L02_001B0C6C __attribute__((sda));
extern int D_L02_001B0C50 __attribute__((sda));
extern int D_L02_001B0C58 __attribute__((sda));
extern int D_L02_001B0C74 __attribute__((sda));
extern int D_L02_001B0C78 __attribute__((sda));
extern float D_L02_001B0C80 __attribute__((sda));
extern float D_L02_001B0C84 __attribute__((sda));
extern float D_L02_001B0C90 __attribute__((sda));
extern float D_L02_001B0C94 __attribute__((sda));
extern float D_L02_001B0CB4 __attribute__((sda));
extern float D_L02_001B0CB8 __attribute__((sda));
extern char D_L02_00249090[];
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern void tether_reset_strands(void *);
extern void tether_animate_strands(void *);
extern void tether_draw_ribbon(float, void *, float, int, float, int, int);

/* Draws the two strips, mirrors their points across the actor's local Y axis, and draws them
   again. The floats and integers of func_L02_003E9BB0 travel in separate register banks, so the
   interleaved declaration keeps its real interface (points a0, colours a1/a2, count a3,
   f12-f14). Each pass tests its count before computing the next side: combine folds the known
   i = 0 into that test, which leaves i without a constant note, so global allocation sees its
   real live length and gives it $s1 ahead of the hoisted actor + 0x10. */
void DrawMirroredRibbons(char *actor) {
    char *state = *(char **)(actor + 0x68);
    char *record = g_moby_l02_pool + *(int *)state * 0x100;
    float inverse[16];
    int color0, color1;
    int side, nextSide;
    *(char **)(state + 0x4C) = record;
    matrix_mul_vec3(state + 0x20, &D_L02_001B0BC0, actor + 0xC0);
    FastVecAdd(state + 0x20, state + 0x20, actor + 0x10);
    qcopy(state + 0x30, record + 0x10);
    D_L02_001B0C68 -= D_L02_001B0C6C;
    if (D_L02_001B0C68 <= -8.0f) D_L02_001B0C68 += 8.0f;
    color0 = (D_L02_001B0C50 << 24) | D_L02_001B0C74;
    color1 = (D_L02_001B0C58 << 24) | D_L02_001B0C78;
    tether_reset_strands(actor);
    tether_animate_strands(actor);
    tether_draw_ribbon(D_L02_001B0C80, D_L02_00249090, D_L02_001B0C84, color0, D_L02_001B0CB4, color1, *(int *)(state + 0x50));
    tether_draw_ribbon(D_L02_001B0C90, D_L02_00249090 + 0x140, D_L02_001B0C94, color0, D_L02_001B0CB8, color1, *(int *)(state + 0x50));
    matrix_from_basis_rows(inverse, actor + 0xC0);
    for (side = 0; side < 2; side = nextSide) {
        int i = 0;
        int more = i < *(int *)(state + 0x50);
        nextSide = side + 1;
        if (more) do {
            char *point = D_L02_00249090 + side * 0x140 + i*16;
            FastVecSub(point, point, actor + 0x10);
            matrix_mul_vec3(point, point, inverse);
            *(float *)(point + 4) = -*(float *)(point + 4);
            matrix_mul_vec3(point, point, actor + 0xC0);
            FastVecAdd(point, point, actor + 0x10);
        } while (++i < *(int *)(state + 0x50));
    }
    tether_draw_ribbon(D_L02_001B0C80, D_L02_00249090, D_L02_001B0C84, color0, D_L02_001B0CB4, color1, *(int *)(state + 0x50));
    tether_draw_ribbon(D_L02_001B0C90, D_L02_00249090 + 0x140, D_L02_001B0C94, color0, D_L02_001B0CB8, color1, *(int *)(state + 0x50));
    for (side = 0; side < 2; side = nextSide) {
        int i = 0;
        int more = i < *(int *)(state + 0x50);
        nextSide = side + 1;
        if (more) do {
            char *point = D_L02_00249090 + side * 0x140 + i*16;
            FastVecSub(point, point, actor + 0x10);
            matrix_mul_vec3(point, point, inverse);
            *(float *)(point + 4) = -*(float *)(point + 4);
            matrix_mul_vec3(point, point, actor + 0xC0);
            FastVecAdd(point, point, actor + 0x10);
        } while (++i < *(int *)(state + 0x50));
    }
}
