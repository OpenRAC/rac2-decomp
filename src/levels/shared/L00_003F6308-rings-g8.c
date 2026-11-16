#include "names.h"
/* func_L00_003F6308 (1,524 bytes, 27 level places): draws a beam of quad rings in strips. Twin of
 * func_L00_003A91A0. Own unit: -O2 -G8 -ffunction-sections -frac2-gcse-hash-fp-117 -frac2-giv-pair-init -frac2-cse2-skip-temp-sum
 * (config/cflags.txt; docs/build/compiler-notes.md). `ring` is declared first in the function,
 * which gives retail's PRE (spill-slot) order with -frac2-gcse-hash-fp-117; the other two
 * switches give the strip loops' giv initial values. Owner standard of 12 November 2026.
 */
#include "common.h"

typedef float BeamVector[4] __attribute__((aligned(16)));
typedef struct { BeamVector point[4]; u32 color[4]; float uv[4][2]; long a,b,c,d; } BeamQuad;
typedef struct { BeamVector origin[3], basis[2]; short enabled, timer; float phase, phase2, rate; } BeamRing;
extern float g_vaporizer_ring_vec_scale __attribute__((sda));
extern float g_vaporizer_ring_side_u_offset __attribute__((sda));
extern float g_vaporizer_ring_u_step __attribute__((sda));

extern float g_vaporizer_ring_b_width __attribute__((sda));
extern float g_vaporizer_ring_c_width __attribute__((sda));
extern u32 g_vaporizer_ring_c_color_front __attribute__((sda));
extern int g_vaporizer_ring_c_alpha __attribute__((sda));
extern float g_vaporizer_trail_scale_step __attribute__((sda));
extern float g_vaporizer_spark_spin_min __attribute__((sda));
extern int g_vaporizer_ring_a_alpha __attribute__((sda));
extern int g_vaporizer_ring_b_alpha __attribute__((sda));

extern u32 g_vaporizer_ring_a_color_front __attribute__((sda));
extern u32 g_vaporizer_ring_a_color_back __attribute__((sda));
extern u32 g_vaporizer_ring_b_color_back __attribute__((sda));
extern u32 g_vaporizer_ring_b_color_front __attribute__((sda));
extern u32 g_vaporizer_ring_c_color_back __attribute__((sda));
extern BeamVector g_vaporizer_beam_ring_vertices[];
extern BeamVector g_camera_l00_position;
extern char *level_get_slot_body(int, int);
extern int *level_get_slot_header(int, int);
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void FastVecCross(void *, void *, void *);
extern int FloatToInt(float);
extern void FastVecScale(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, void *, int);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);


/* Draws the bolt's three glowing rings and the flat streaks between them, fading them out over
   time. */
void vaporizer_bolt_draw_beam_rings(unsigned char *object)
{
    int ring;
    BeamQuad quad;
    BeamVector matrix[4];
    BeamVector vertices[3][20];
    BeamVector temp, side;
    unsigned char *vars = *(unsigned char **)(object + 0x68);
    char *base = level_get_slot_body(MOBY_CLASS_VAPORIZER, *(short *)(vars + 0x1a));
    BeamRing *rings = (BeamRing *)(base + *level_get_slot_header(MOBY_CLASS_VAPORIZER, *(short *)(vars + 0x1a)));
    int row, j;
    u32 primary, col, alpha;
    float side_u, fade, phase, u, next, phase2;

    gfx_init_quad_packet_state(&quad, 21, 0, 128);
    for (ring = 0; ring < 3; ring++) {
        if (rings[ring].enabled == 0) continue;
        qcopy(matrix[0], rings[ring].basis[0]);
        qcopy(matrix[2], rings[ring].basis[1]);
        FastVecCross(matrix[1], matrix[0], matrix[2]);
        fade = (float)rings[ring].timer * rings[ring].rate;
        alpha = FloatToInt(fade * (float)g_vaporizer_ring_a_alpha) << 24;
        col = g_vaporizer_ring_a_color_front;
        primary = alpha | col;
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = primary;
        for (row = 0; row < 3; row++) {
            qcopy(matrix[3], rings[ring].origin[row]);
            for (j = 0; j < 20; j++) {
                FastVecScale(temp, g_vaporizer_beam_ring_vertices[j], g_vaporizer_ring_vec_scale);
                transform_vector(vertices[row][j], temp, matrix);
            }
        }
        phase = rings[ring].phase;
        col = g_vaporizer_ring_a_color_back;
        for (j = 1; j < 3; j++) {
            u = 0;
            for (row = 0; row < 20; row++) {
                qcopy(quad.point[0], vertices[j][row]);
                qcopy(quad.point[1], vertices[j][(row + 1) % 20]);
                qcopy(quad.point[2], vertices[j - 1][row]);
                qcopy(quad.point[3], vertices[j - 1][(row + 1) % 20]);
                next = u + g_vaporizer_ring_u_step;
                side_u = phase + g_vaporizer_ring_side_u_offset;
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
                draw_world_quad(&quad, 0, 0);
            }
            col = primary;
        }
        gfx_init_quad_packet_state(&quad, 14, 1, 128);
        alpha = FloatToInt(fade * (float)g_vaporizer_ring_b_alpha) << 24;
        col = g_vaporizer_ring_b_color_back;
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
        col = g_vaporizer_ring_b_color_front;
        FastVecSub(temp, &g_camera_l00_position, rings[ring].origin[0]);
        FastVecCross(matrix[1], matrix[0], temp);
        vec_scale_to_length(side, matrix[1], g_vaporizer_ring_b_width);
        for (j = 0; j < 2; j++) {
            FastVecAdd(quad.point[0], rings[ring].origin[j + 1], side);
            FastVecSub(quad.point[1], rings[ring].origin[j + 1], side);
            FastVecAdd(quad.point[2], rings[ring].origin[j], side);
            FastVecSub(quad.point[3], rings[ring].origin[j], side);
            quad.color[3] = quad.color[2] = col;
            draw_world_quad(&quad, 0, 0);
            col = primary;
            quad.uv[0][0] = quad.uv[1][0] = quad.uv[2][0];
            quad.uv[2][0] = quad.uv[3][0] = 3.0f;
        }
        gfx_init_quad_packet_state(&quad, 23, 1, 128);
        alpha = FloatToInt(fade * (float)g_vaporizer_ring_c_alpha) << 24;
        col = g_vaporizer_ring_c_color_back;
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
        col = g_vaporizer_ring_c_color_front;
        vec_scale_to_length(side, matrix[1], g_vaporizer_ring_c_width);
        for (j = 0; j < 2; j++) {
            FastVecAdd(quad.point[0], rings[ring].origin[j + 1], side);
            FastVecSub(quad.point[1], rings[ring].origin[j + 1], side);
            FastVecAdd(quad.point[2], rings[ring].origin[j], side);
            FastVecSub(quad.point[3], rings[ring].origin[j], side);
            quad.color[3] = quad.color[2] = col;
            draw_world_quad(&quad, 0, 0);
            col = primary;
            quad.uv[0][0] = quad.uv[1][0] = quad.uv[2][0];
            quad.uv[2][0] = quad.uv[3][0] = phase2 + 3.0f;
        }
    }
}
