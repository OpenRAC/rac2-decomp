#include "include_asm.h"
#include "common.h"

/* func_L00_003C4B98 needs -fno-sched-interblock (config/cflags.txt): retail's inner-loop
   arms keep the index load common to both and the increments at the join. The basis pointer
   is taken before the first vector call: a frame address first used after a call is
   anchored behind it. */

extern int g_glow_sphere_texture __attribute__((sda));
extern float g_glow_sphere_scale __attribute__((sda));
extern float g_glow_sphere_inner_scale __attribute__((sda));
extern float g_glow_sphere_outer_ratio __attribute__((sda));
extern unsigned int g_glow_sphere_color __attribute__((sda));
extern char g_camera_l00_position[];
extern char g_hero_state_block[];
extern float g_glow_sphere_points[][3];
extern float g_glow_sphere_unit_points[][4];
extern float g_glow_sphere_glint_uvs[][2];
extern float g_glow_sphere_quad_points[][4];
extern short g_glow_sphere_quad_indices[][4];
extern unsigned long GetEffectTextureDescriptor(int);
extern void VU1_addGSregister(unsigned int, unsigned long);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void font_queue_vu_state(void);
extern void part_draw_glint_effect(int, void *, void *, void *, int);
extern void draw_world_quad(void *, void *, int);

/* The quad func_00280B90 draws: four corners, their colours and texture coordinates, then the
   four GS register values it is drawn with. */
typedef struct {
    float corners[4][4];
    unsigned int colors[4];
    float uvs[4][2];
    unsigned long regs[4];
} Quad4B98;

/* The record the owner points to at 0x68. */
typedef struct {
    char pad_00[8];
    unsigned int color;
    char pad_0C[0x24];
    float position[4];
} Context4B98;

/* Builds a basis that faces the point at D_L00_001B8DC0 from the owner's record, transforms the
   290 points of D_L00_00292370 through it and draws them as three strips in the record's
   colour, then draws 32 quads whose corners are D_L00_00293EB0 points picked by D_L00_002944B0,
   corners 0-1 scaled by D_L00_001AFF30 and corners 2-3 by that times D_L00_001AFF34. */
/* Draws the glowing sphere effect: a ring of lit points facing the camera, then 32 soft quads around it. */
void gfx_draw_glow_sphere(char *owner)
{
    struct {
        Quad4B98 quad;
        float basis[3][4];
        float position[4], delta[4], up[4], point[4];
        unsigned int colors[290];
    } frame __attribute__((aligned(16)));
    Context4B98 *ctx = *(Context4B98 **)(owner + 0x68);
    float (*basis)[4];
    unsigned int rgba, rim;
    int i, j, k;
    short *indices;
    float scale, scale2;

    frame.quad.regs[1] = GetEffectTextureDescriptor(g_glow_sphere_texture);
    frame.quad.regs[2] = 0xFF9000000260UL;
    frame.quad.regs[3] = 0x8000000044UL;
    frame.quad.regs[0] = 0;
    VU1_addGSregister(0x47, 0x53001);
    qcopy(frame.position, ctx->position);
    frame.position[3] = 1.0f;
    basis = frame.basis;
    FastVecSub(frame.delta, g_camera_l00_position, frame.position);
    vec_scale_to_length(basis[0], frame.delta, 1.0f);
    FastVecScale(frame.up, g_hero_state_block, -1.0f);
    FastVecCross(basis[1], basis[0], frame.up);
    vec_scale_to_length(basis[1], basis[1], 1.0f);
    FastVecCross(basis[2], basis[1], basis[0]);
    FastVecScale(basis[0], basis[0], g_glow_sphere_scale);
    FastVecScale(basis[1], basis[1], g_glow_sphere_scale);
    FastVecScale(basis[2], basis[2], g_glow_sphere_scale);
    rgba = g_glow_sphere_color | ctx->color;
    frame.quad.colors[3] = rgba;
    frame.quad.colors[2] = rgba;
    frame.quad.colors[1] = rgba;
    frame.quad.colors[0] = rgba;
    VU1_addGSregister(6, GetEffectTextureDescriptor(g_glow_sphere_texture));
    VU1_addGSregister(0x42, 0x8000000044UL);
    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x14, 0xFF9000000260UL);
    VU1_addGSregister(0x4A, 0);
    font_queue_vu_state();
    for (j = 0; j < 290; j++) {
        transform_vector(frame.point, g_glow_sphere_unit_points[j], frame.basis);
        g_glow_sphere_points[j][0] = frame.point[0];
        g_glow_sphere_points[j][1] = frame.point[1];
        g_glow_sphere_points[j][2] = frame.point[2];
        frame.colors[j] = frame.quad.colors[0];
    }
    part_draw_glint_effect(148, g_glow_sphere_points[0], &frame.colors[0], g_glow_sphere_glint_uvs[0], 1);
    part_draw_glint_effect(109, g_glow_sphere_points[146], &frame.colors[146], g_glow_sphere_glint_uvs[146], 1);
    part_draw_glint_effect(36, g_glow_sphere_points[254], &frame.colors[254], g_glow_sphere_glint_uvs[254], 1);

    frame.quad.regs[1] = GetEffectTextureDescriptor(11);
    frame.quad.regs[3] = 0x8000000048UL;
    scale = g_glow_sphere_inner_scale;
    rim = ctx->color | 0x40000000;
    scale2 = scale * g_glow_sphere_outer_ratio;
    frame.quad.colors[3] = 0;
    frame.quad.colors[1] = rim;
    frame.quad.colors[0] = rim;
    frame.quad.colors[2] = 0;
    for (i = 0; i < 32; i++) {
        indices = g_glow_sphere_quad_indices[i];
        for (j = 0; j < 4; j++) {
            k = indices[j];
            if (j >= 2)
                FastVecScale(frame.quad.corners[j], g_glow_sphere_quad_points[k], scale2);
            else
                FastVecScale(frame.quad.corners[j], g_glow_sphere_quad_points[k], scale);
        }
        frame.quad.uvs[0][0] = 0.5f;
        frame.quad.uvs[0][1] = 0.5f;
        frame.quad.uvs[1][0] = 0.5f;
        frame.quad.uvs[1][1] = 0.5f;
        frame.quad.uvs[2][0] = 0.5f;
        frame.quad.uvs[2][1] = 1.0f;
        frame.quad.uvs[3][0] = 0.5f;
        frame.quad.uvs[3][1] = 1.0f;
        draw_world_quad(&frame.quad, frame.basis, 0);
    }
}

extern char g_spark_slot_records[] __attribute__((nosda));

extern void lightning_draw_curve(char *a0, char *a1);

extern int math_random_int_range(int a, int b);

extern float math_random_angle(void);

extern void gfx_draw_billboard_quad(char *a, int b, unsigned int c, int d, float e, float f, float g);

/* Walks the level's table of records and draws the two sprites of the record the owner
   holds, when that record is still free. The record's own field is the owner, the one
   after it says whether it is free. Without interblock scheduling the two skips stay likely
   branches. Each sprite's colour is its own local: one shared variable dies twice, becomes a
   global pseudo, and the shifted alpha no longer ties to its saved register. */
/* Draws two small sprites for each effect slot that belongs to this owner and is still active. */
void effect_draw_slot_sprites(char *owner)
{
    unsigned int firstRGB = 0x103080;
    unsigned int secondRGB = 0xFFFFFF;
    char *base = g_spark_slot_records;
    char *p = base + 0x30;
    char *q = base;
    int i;
    int first_color;
    int second_color;
    float scroll;

    for (i = 29; i >= 0; p += 0xA0, i--, q += 0xA0) {
        if (*(int *)(p + 0x5C) == (int)owner) {
            lightning_draw_curve(owner, q);
            if (*(int *)(p + 0x64) == 0) {
                first_color = math_random_int_range(0x50, 0x60);
                first_color = (int)(first_color << 24) | firstRGB;
                scroll = math_random_angle();
                gfx_draw_billboard_quad(p, 0x31, first_color, 1, 0.5f, 0.15f, scroll);
                second_color = math_random_int_range(0x50, 0x60);
                second_color = (int)(second_color << 24) | secondRGB;
                scroll = math_random_angle();
                gfx_draw_billboard_quad(p, 0x31, second_color, 1, 0.3f, 0.151f, scroll);
            }
        }
    }
}
