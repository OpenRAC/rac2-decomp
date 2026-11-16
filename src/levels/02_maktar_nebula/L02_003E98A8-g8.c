#include "common.h"
extern char *g_moby_l02_pool;
extern char g_tether_local_offset[] SDATA(D_L02_001B0BC0);
extern float g_tether_ribbon_uv_scroll __attribute__((sda));
extern float g_tether_ribbon_scroll_speed __attribute__((sda));
extern int g_tether_ribbon_alpha_core __attribute__((sda));
extern int g_tether_ribbon_alpha_halo __attribute__((sda));
extern int g_tether_ribbon_halo_color __attribute__((sda));
extern int g_tether_ribbon_color_rgb __attribute__((sda));
extern float g_tether_ribbon_width_scale __attribute__((sda));
extern float g_tether_ribbon_param_a __attribute__((sda));
extern float g_tether_ribbon_width_scale_b __attribute__((sda));
extern float g_tether_ribbon_param_b __attribute__((sda));
extern float g_tether_ribbon_end_param_a __attribute__((sda));
extern float g_tether_ribbon_end_param_b __attribute__((sda));
extern char g_tether_strand_points[];
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
    matrix_mul_vec3(state + 0x20, &g_tether_local_offset, actor + 0xC0);
    FastVecAdd(state + 0x20, state + 0x20, actor + 0x10);
    qcopy(state + 0x30, record + 0x10);
    g_tether_ribbon_uv_scroll -= g_tether_ribbon_scroll_speed;
    if (g_tether_ribbon_uv_scroll <= -8.0f) g_tether_ribbon_uv_scroll += 8.0f;
    color0 = (g_tether_ribbon_alpha_core << 24) | g_tether_ribbon_halo_color;
    color1 = (g_tether_ribbon_alpha_halo << 24) | g_tether_ribbon_color_rgb;
    tether_reset_strands(actor);
    tether_animate_strands(actor);
    tether_draw_ribbon(g_tether_ribbon_width_scale, g_tether_strand_points, g_tether_ribbon_param_a, color0, g_tether_ribbon_end_param_a, color1, *(int *)(state + 0x50));
    tether_draw_ribbon(g_tether_ribbon_width_scale_b, g_tether_strand_points + 0x140, g_tether_ribbon_param_b, color0, g_tether_ribbon_end_param_b, color1, *(int *)(state + 0x50));
    matrix_from_basis_rows(inverse, actor + 0xC0);
    for (side = 0; side < 2; side = nextSide) {
        int i = 0;
        int more = i < *(int *)(state + 0x50);
        nextSide = side + 1;
        if (more) do {
            char *point = g_tether_strand_points + side * 0x140 + i*16;
            FastVecSub(point, point, actor + 0x10);
            matrix_mul_vec3(point, point, inverse);
            *(float *)(point + 4) = -*(float *)(point + 4);
            matrix_mul_vec3(point, point, actor + 0xC0);
            FastVecAdd(point, point, actor + 0x10);
        } while (++i < *(int *)(state + 0x50));
    }
    tether_draw_ribbon(g_tether_ribbon_width_scale, g_tether_strand_points, g_tether_ribbon_param_a, color0, g_tether_ribbon_end_param_a, color1, *(int *)(state + 0x50));
    tether_draw_ribbon(g_tether_ribbon_width_scale_b, g_tether_strand_points + 0x140, g_tether_ribbon_param_b, color0, g_tether_ribbon_end_param_b, color1, *(int *)(state + 0x50));
    for (side = 0; side < 2; side = nextSide) {
        int i = 0;
        int more = i < *(int *)(state + 0x50);
        nextSide = side + 1;
        if (more) do {
            char *point = g_tether_strand_points + side * 0x140 + i*16;
            FastVecSub(point, point, actor + 0x10);
            matrix_mul_vec3(point, point, inverse);
            *(float *)(point + 4) = -*(float *)(point + 4);
            matrix_mul_vec3(point, point, actor + 0xC0);
            FastVecAdd(point, point, actor + 0x10);
        } while (++i < *(int *)(state + 0x50));
    }
}
