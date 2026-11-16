#include "common.h"

extern unsigned int ref_L13_0040DFC0_01 __attribute__((sda));
extern unsigned int ref_L13_0040DFC0_02 __attribute__((sda));
extern float g_beam_step_length __attribute__((sda));
extern unsigned int g_beam_outer_red __attribute__((sda));
extern unsigned int g_beam_outer_green __attribute__((sda));
extern unsigned int g_beam_outer_blue __attribute__((sda));
extern unsigned int g_beam_outer_alpha __attribute__((sda));
extern unsigned int g_beam_inner_red __attribute__((sda));
extern unsigned int g_beam_inner_green __attribute__((sda));
extern unsigned int g_beam_inner_blue __attribute__((sda));
extern unsigned int g_beam_inner_alpha __attribute__((sda));
extern unsigned int g_beam_core_red __attribute__((sda));
extern unsigned int g_beam_core_green __attribute__((sda));
extern unsigned int g_beam_core_blue __attribute__((sda));
extern unsigned int g_beam_core_alpha __attribute__((sda));
extern unsigned int g_beam_tip_red __attribute__((sda));
extern unsigned int g_beam_tip_green __attribute__((sda));
extern unsigned int g_beam_tip_blue __attribute__((sda));
extern unsigned int g_beam_tip_alpha __attribute__((sda));
extern float g_beam_l13_side_length_c __attribute__((sda));
extern float g_beam_l13_side_length_a __attribute__((sda));
extern float g_beam_l13_side_length_b __attribute__((sda));
extern int g_beam_l13_quad_texture __attribute__((sda));
extern int g_beam_quad_flags __attribute__((sda));
extern float g_beam_quad_size __attribute__((sda));
extern float g_camera_l13_position[];
extern void ref_L13_0040DFC0_00(void *);
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void draw_world_quad(void *, int, int);
extern float math_random_angle(void);
extern void gfx_draw_billboard_quad(void *, int, int, int, float, float, float);

/* Draws layered beam quads with scrolling texture coordinates and an end glow. */
void gfx_draw_scrolling_beam(u8 *unused, int ua, float uf, int ub, int uc,
                       float ug, float uh, int ud, u8 *object) {
    struct {
        float v[4][4];
        unsigned color[4];
        float uv[8];
        char pad[32];
    } packet __attribute__((aligned(16)));
    float nearPoint[4], viewDelta[4], beamStep[4], farPoint[4], side[4];
    float *position;
    float *state = *(float **)(object + 0x68);
    int i;
    float *uv;
    float random;

    ref_L13_0040DFC0_00(&packet);
    gfx_init_quad_packet_state(&packet, ref_L13_0040DFC0_01, 0, 128);
    {
        unsigned alpha = (g_beam_outer_alpha << 24);
        unsigned alphaBlue = alpha | (g_beam_outer_blue << 16);
        unsigned alphaBlueGreen = alphaBlue | (g_beam_outer_green << 8);
        unsigned rgba = alphaBlueGreen | g_beam_outer_red;
        packet.color[0] = packet.color[1] = rgba;
    }
    {
        unsigned alpha = (g_beam_inner_alpha << 24);
        unsigned alphaBlue = alpha | (g_beam_inner_blue << 16);
        unsigned alphaBlueGreen = alphaBlue | (g_beam_inner_green << 8);
        unsigned rgba = alphaBlueGreen | g_beam_inner_red;
        packet.color[2] = packet.color[3] = rgba;
    }
    packet.uv[0] = 0;
    packet.uv[1] = 0;
    packet.uv[2] = 0;
    packet.uv[3] = 1;
    packet.uv[4] = 1;
    packet.uv[5] = 0;
    packet.uv[6] = 1;
    packet.uv[7] = 1;
    for (uv = packet.uv, i = 3; i >= 0; --i, uv += 2) {
        *uv -= state[10];
        if (*uv <= 7.0f)
            *uv += 7.0f;
    }
    state[10] += 0.1f;
    if (state[10] >= 4.0f)
        state[10] -= 4.0f;

    vec_scale_to_length(nearPoint, state, -0.17f);
    position = (float *)(object + 0x10);
    FastVecAdd(nearPoint, position, nearPoint);
    FastVecSub(viewDelta, position, g_camera_l13_position);
    vec_scale_to_length(beamStep, state, -g_beam_step_length);
    FastVecAdd(farPoint, nearPoint, beamStep);
    FastVecCross(side, viewDelta, beamStep);
    vec_scale_to_length(side, side, g_beam_l13_side_length_c);
    FastVecAdd(packet.v[0], position, side);
    FastVecSub(packet.v[1], position, side);
    FastVecAdd(packet.v[2], farPoint, side);
    FastVecSub(packet.v[3], farPoint, side);
    draw_world_quad(&packet, 0, 0);
    packet.color[0] = packet.color[2];
    packet.color[1] = packet.color[3];
    packet.color[2] = packet.color[3] = 0x801010;
    qcopy(packet.v[0], packet.v[2]);
    qcopy(packet.v[1], packet.v[3]);
    FastVecAdd(packet.v[2], packet.v[2], beamStep);
    FastVecAdd(packet.v[3], packet.v[3], beamStep);
    draw_world_quad(&packet, 0, 0);
    gfx_init_quad_packet_state(&packet, ref_L13_0040DFC0_02, 1, 128);
    {
        unsigned alpha = (g_beam_core_alpha << 24);
        unsigned alphaBlue = alpha | (g_beam_core_blue << 16);
        unsigned alphaBlueGreen = alphaBlue | (g_beam_core_green << 8);
        unsigned rgba = alphaBlueGreen | g_beam_core_red;
        packet.color[1] = rgba;
        packet.color[0] = packet.color[1];
    }
    packet.uv[0] = 0;
    packet.uv[1] = 0;
    packet.uv[2] = 0;
    packet.uv[3] = 1;
    packet.uv[4] = 1;
    packet.uv[5] = 0;
    packet.uv[6] = 1;
    packet.uv[7] = 1;
    {
        unsigned blue = (g_beam_core_blue << 16);
        unsigned blueGreen = blue | (g_beam_core_green << 8);
        unsigned rgb = blueGreen | g_beam_core_red;
        packet.color[3] = rgb;
        packet.color[2] = packet.color[3];
    }
    vec_scale_to_length(side, side, g_beam_l13_side_length_b);
    FastVecAdd(packet.v[0], position, side);
    FastVecSub(packet.v[1], position, side);
    FastVecAdd(farPoint, position, beamStep);
    FastVecAdd(farPoint, farPoint, beamStep);
    FastVecAdd(packet.v[2], farPoint, side);
    FastVecSub(packet.v[3], farPoint, side);
    draw_world_quad(&packet, 0, 0);
    {
        unsigned alpha = (g_beam_core_alpha << 24);
        unsigned alphaBlue = alpha | (g_beam_core_blue << 16);
        unsigned alphaBlueGreen = alphaBlue | (g_beam_core_green << 8);
        unsigned rgba = alphaBlueGreen | g_beam_core_red;
        packet.color[0] = packet.color[1] = rgba;
    }
    {
        unsigned blue = (g_beam_core_blue << 16);
        unsigned blueGreen = blue | (g_beam_core_green << 8);
        unsigned rgb = blueGreen | g_beam_core_red;
        packet.color[2] = packet.color[3] = rgb;
    }
    vec_scale_to_length(side, side, g_beam_l13_side_length_a);
    vec_scale_to_length(nearPoint, state, -0.1f);
    FastVecAdd(nearPoint, position, nearPoint);
    FastVecAdd(packet.v[0], nearPoint, side);
    FastVecSub(packet.v[1], nearPoint, side);
    FastVecAdd(farPoint, nearPoint, beamStep);
    FastVecAdd(farPoint, farPoint, beamStep);
    FastVecAdd(packet.v[2], farPoint, side);
    FastVecSub(packet.v[3], farPoint, side);
    draw_world_quad(&packet, 0, 0);
    {
        unsigned alpha = (g_beam_tip_alpha << 24);
        unsigned alphaBlue = alpha | (g_beam_tip_blue << 16);
        unsigned alphaBlueGreen = alphaBlue | (g_beam_tip_green << 8);
        unsigned rgba = alphaBlueGreen | g_beam_core_red;
        packet.color[0] = packet.color[1] = rgba;
    }
    {
        unsigned blue = (g_beam_tip_blue << 16);
        unsigned blueGreen = blue | (g_beam_tip_green << 8);
        unsigned rgb = blueGreen | g_beam_tip_red;
        packet.color[2] = packet.color[3] = rgb;
    }
    vec_scale_to_length(side, side, g_beam_l13_side_length_a);
    vec_scale_to_length(nearPoint, state, -0.1f);
    FastVecAdd(nearPoint, position, nearPoint);
    FastVecAdd(packet.v[0], nearPoint, side);
    FastVecSub(packet.v[1], nearPoint, side);
    FastVecAdd(farPoint, nearPoint, beamStep);
    FastVecAdd(farPoint, farPoint, beamStep);
    FastVecAdd(packet.v[2], farPoint, side);
    FastVecSub(packet.v[3], farPoint, side);
    draw_world_quad(&packet, 0, 0);
    packet.color[0] = packet.color[1] = 0x40FFFFFF;
    {
        unsigned blue = (g_beam_core_blue << 16);
        unsigned blueGreen = blue | (g_beam_core_green << 8);
        unsigned rgb = blueGreen | g_beam_core_red;
        packet.color[2] = packet.color[3] = rgb;
    }
    vec_scale_to_length(side, side, g_beam_l13_side_length_b);
    FastVecAdd(packet.v[0], position, side);
    FastVecSub(packet.v[1], position, side);
    vec_scale_to_length(beamStep, state, -0.6f);
    FastVecAdd(farPoint, position, beamStep);
    FastVecAdd(farPoint, farPoint, beamStep);
    FastVecAdd(packet.v[2], farPoint, side);
    FastVecSub(packet.v[3], farPoint, side);
    draw_world_quad(&packet, 0, 0);
    random = math_random_angle();
    gfx_draw_billboard_quad(position, g_beam_l13_quad_texture, g_beam_quad_flags, 1, g_beam_quad_size, 0.08f, random);
}
