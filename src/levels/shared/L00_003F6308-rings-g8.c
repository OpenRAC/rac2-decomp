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
extern float D_L00_001B0984 __attribute__((sda));
extern float D_L00_001B097C __attribute__((sda));
extern float D_L00_001B0980 __attribute__((sda));

extern float D_L00_001B09A0 __attribute__((sda));
extern float D_L00_001B09B0 __attribute__((sda));
extern u32 D_L00_001B09B4 __attribute__((sda));
extern int D_L00_001B09BC __attribute__((sda));
extern float D_L00_001B09C0 __attribute__((sda));
extern float D_L00_001B09CC __attribute__((sda));
extern int D_L00_001B0994 __attribute__((sda));
extern int D_L00_001B09AC __attribute__((sda));

extern u32 D_L00_001B098C __attribute__((sda));
extern u32 D_L00_001B0990 __attribute__((sda));
extern u32 D_L00_001B09A8 __attribute__((sda));
extern u32 D_L00_001B09A4 __attribute__((sda));
extern u32 D_L00_001B09B8 __attribute__((sda));
extern BeamVector D_L00_0029F0D0[];
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
    char *base = level_get_slot_body(0xc04 /* Vaporizer */, *(short *)(vars + 0x1a));
    BeamRing *rings = (BeamRing *)(base + *level_get_slot_header(0xc04 /* Vaporizer */, *(short *)(vars + 0x1a)));
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
        alpha = FloatToInt(fade * (float)D_L00_001B0994) << 24;
        col = D_L00_001B098C;
        primary = alpha | col;
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = primary;
        for (row = 0; row < 3; row++) {
            qcopy(matrix[3], rings[ring].origin[row]);
            for (j = 0; j < 20; j++) {
                FastVecScale(temp, D_L00_0029F0D0[j], D_L00_001B0984);
                transform_vector(vertices[row][j], temp, matrix);
            }
        }
        phase = rings[ring].phase;
        col = D_L00_001B0990;
        for (j = 1; j < 3; j++) {
            u = 0;
            for (row = 0; row < 20; row++) {
                qcopy(quad.point[0], vertices[j][row]);
                qcopy(quad.point[1], vertices[j][(row + 1) % 20]);
                qcopy(quad.point[2], vertices[j - 1][row]);
                qcopy(quad.point[3], vertices[j - 1][(row + 1) % 20]);
                next = u + D_L00_001B0980;
                side_u = phase + D_L00_001B097C;
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
        alpha = FloatToInt(fade * (float)D_L00_001B09AC) << 24;
        col = D_L00_001B09A8;
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
        col = D_L00_001B09A4;
        FastVecSub(temp, &g_camera_l00_position, rings[ring].origin[0]);
        FastVecCross(matrix[1], matrix[0], temp);
        vec_scale_to_length(side, matrix[1], D_L00_001B09A0);
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
        alpha = FloatToInt(fade * (float)D_L00_001B09BC) << 24;
        col = D_L00_001B09B8;
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
        col = D_L00_001B09B4;
        vec_scale_to_length(side, matrix[1], D_L00_001B09B0);
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
