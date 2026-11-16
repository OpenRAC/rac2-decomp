#include "include_asm.h"

#include "common.h"

/* func_L07_003F4CC0 (DrawSegmentedBeam) reads its parameters through $gp and
   needs -g, so it has a -G8 -g unit of its own (config/cflags.txt).
   D_L07_001B0EC8[], D_L07_001B0EBC[], D_L07_001B0EAC[] and D_L07_001B0ED4[] are
   incomplete sda arrays: retail reads [0] through $gp and [1] (or the whole
   word) through lui. */

extern void beam_get_end_points(void *a, void *start, void *end);
extern void FastVecSub(void *out, void *a, void *b);
extern void FastVecCross(void *out, void *a, void *b);
extern void vec_scale_to_length(void *out, void *a, f32 scale);
extern void FastVecAdd(void *out, void *a, void *b);
extern f32 FastVecLength(void *v);
extern f32 FastAddRotations(f32 a, f32 b);
extern s32 FastTweenColor(s32 from, s32 to, f32 t);
extern void gfx_init_quad_packet_state(void *packet, s32 a, s32 b, s32 c);
extern void draw_world_quad(void *packet, void *a, s32 b);
extern void gfx_draw_billboard_quad(void *pos, s32 id, s32 color, s32 a, f32 size, f32 b, f32 rotation);
extern u8 g_hero_position_block[] NOT_SDA;
extern s32 g_beam_texture_param __attribute__((sda));
extern s32 g_beam_l07_core_color __attribute__((sda));
extern s32 g_beam_l07_glow_color __attribute__((sda));
extern s32 g_beam_color_pair[] __attribute__((sda));
extern s32 g_beam_edge_color_pair[] __attribute__((sda));
extern f32 g_beam_vertex_depth __attribute__((sda));
extern f32 g_beam_segment_length __attribute__((sda));
extern f32 g_beam_rotation_offset __attribute__((sda));
extern f32 g_beam_rotation_rate __attribute__((sda));
extern f32 g_beam_depth_pair[] __attribute__((sda));
extern f32 g_beam_width_pair[] __attribute__((sda));
extern f32 g_beam_l07_uv_u_table[] SDATA(D_L07_001B0EE0);
extern f32 g_beam_l07_uv_v_table[] __attribute__((sda));

#define F(p, o) (*(f32 *)((p) + (o)))

/* Draws the glowing beam between its two end points: a flat strip along it plus a string of sprites that spin and fade with the beam's strength. */
void DrawSegmentedBeam(u8 *moby)
{
    f32 start[4], end[4], delta[4], side[4], normal[4], base[4];
    struct Vec4 { f32 x, y, z, w; };
    struct {
        struct Vec4 vertices[4];
        s32 colors[4];
        f32 uv[4][2];
        u8 rest[32];
    } draw;
    f32 current[4], step[4];
    u8 *vars = *(u8 **)(moby + 0x68);
    s32 i, color;
    f32 length, count, alpha, rotation, width;
    f32 uvOffset;

    beam_get_end_points(moby, start, end);
    FastVecSub(delta, end, start);
    FastVecSub(side, g_hero_position_block, moby + 0x10);
    FastVecCross(normal, side, delta);
    vec_scale_to_length(normal, normal, 1);
    qzero_nc(side);
    qcopy_nc(base, start);
    base[3] = 1;
    gfx_init_quad_packet_state(&draw, g_beam_texture_param, 1, 128);
    uvOffset = 0.0f;
    color = FastTweenColor(g_beam_l07_core_color & 0xffffff, g_beam_l07_core_color, F(vars, 0x24));
    {
        s32 i;

        for (i = 0; i < 4; i++) {
            struct Vec4 *v;

            draw.uv[i][0] = g_beam_l07_uv_u_table[i * 2] + uvOffset;
            draw.uv[i][1] = g_beam_l07_uv_v_table[i * 2];
            qzero_nc(&draw.vertices[i]);
            v = &draw.vertices[i];
            if (i < 2)
                v->x = 0;
            else
                v->x = 1;
            v->z = g_beam_vertex_depth;
            if (!(i & 1))
                v->z = -v->z;
            v->w = 1;
            draw.colors[i] = color;
        }
    }
    draw_world_quad(&draw, delta, 0);
    color = FastTweenColor(g_beam_color_pair[0] & 0xffffff, g_beam_color_pair[0], F(vars, 0x24));
    {
        s32 i;

        for (i = 0; i < 4; i++) {
            struct Vec4 *v = &draw.vertices[i];

            v->z = g_beam_depth_pair[0];
            if (!(i & 1))
                v->z = -g_beam_depth_pair[0];
            draw.colors[i] = color;
        }
    }
    draw_world_quad(&draw, delta, 0);
    length = FastVecLength(delta) / g_beam_segment_length;
    rotation = F(vars, 0x28);
    if (moby[0x20] == 0) {
        alpha = 1;
        count = (length * F(vars, 0x24)) * 2.0f;
        if (count > length + 1)
            count = length + 1;
    } else {
        alpha = F(vars, 0x24) * F(vars, 0x24);
        count = length + 1;
    }
    qcopy(current, base);
    vec_scale_to_length(step, delta, g_beam_segment_length);
    for (i = 0; (f32)i < count; i++) {
        f32 *pos;

        /* The last point and odd points take the first width, even points the second. */
        if ((f32)i == count - 1)
            width = g_beam_width_pair[0];
        else if (i & 1)
            width = g_beam_width_pair[0];
        else
            width = g_beam_width_pair[1];
        color = FastTweenColor(g_beam_l07_glow_color & 0xffffff, g_beam_l07_glow_color, alpha);
        pos = current;
        gfx_draw_billboard_quad(pos, 49, color, 1, width, 0, rotation);
        color = FastTweenColor(g_beam_edge_color_pair[0] & 0xffffff, g_beam_edge_color_pair[0], alpha);
        gfx_draw_billboard_quad(pos, 49, color, 1, width, 0, FastAddRotations(rotation, g_beam_rotation_offset));
        rotation = -FastAddRotations(rotation, g_beam_rotation_rate * 0.017453294f);
        if ((f32)i < length - 1)
            FastVecAdd(current, current, step);
        else
            qcopy(current, end);
    }
}
