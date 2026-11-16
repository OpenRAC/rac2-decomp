#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef struct { u8 pad[0x70]; long f70, f78, f80, f88; } QuadPacket;
typedef struct { float vertex[4][4]; unsigned int color[4]; float uv[4][2]; long registers[4]; } EffectQuad;
extern float g_camera_l00_position[4];
extern short g_screen_adjust_offsets[];
extern float g_beam_ring_radius_scale __attribute__((sda));
extern float g_beam_ring_spoke_length __attribute__((sda));
extern float g_beam_ring_spoke_target __attribute__((sda));
extern float g_beam_ring_scale_end __attribute__((sda));
extern float g_beam_ring_scale_start __attribute__((sda));
extern float g_beam_ring_first_angle_deg __attribute__((sda));
extern float g_beam_ring_step_angle_deg __attribute__((sda));
extern float g_beam_ring_quad_length __attribute__((sda));
extern float g_beam_l00_ring_alpha_scale __attribute__((sda));
extern void cam_compute_view_direction(char *, char *, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float IntToFloat(int);
extern void gfx_init_quad_packet_state(QuadPacket *, int, int, int);
extern int FloatToInt(float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void draw_world_quad(void *, int, int);
extern float FastAddRotations(float, float);
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void gfx_draw_colored_rectangle(int, int, int, int, int);

/* Draw the beam's ring, crossing core planes and terminal flash. */
void beam_draw_ring_and_core(char *moby)
{
    EffectQuad quad;
    float position[4], normal[4], view[4], radius[4], center[4], rotation[4];
    float spoke[4], side[4], up[4], horizontal[4], vertical[4], corner[4], temporary[4];
    char *state = *(char **)(moby + 0x68);
    float alpha, scale;
    unsigned int color;
    int i;
    qcopy(position, state + 0x10);
    cam_compute_view_direction((char *)position, (char *)normal, 1);
    FastVecSub(view, g_camera_l00_position, position);
    vec_scale_to_length(view, view, 1.0f);
    if (*(short *)(state + 8)) {
        float ringAlpha = IntToFloat(*(short *)(state + 8)) * *(float *)(state + 0x20);
        gfx_init_quad_packet_state((QuadPacket *)&quad, 11, 1, 0x80);
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = (FloatToInt(ringAlpha * 255.0f) << 24) | 0x2040FF;
        quad.uv[0][0] = 0.5f; quad.uv[0][1] = 0.0f;
        quad.uv[1][0] = 0.5f; quad.uv[1][1] = 1.0f;
        quad.uv[2][0] = 1.0f; quad.uv[2][1] = 0.0f;
        quad.uv[3][0] = 1.0f; quad.uv[3][1] = 1.0f;
        FastVecScale(radius, normal, g_beam_ring_radius_scale);
        FastVecAdd(center, position, radius);
        math_build_axis_angle_quat(rotation, view, *(float *)(state + 0xC));
        vec_rotate_by_quaternion(radius, radius, rotation);
        for (i = 0; i < 8; i++) {
            FastVecCross(spoke, view, radius);
            vec_scale_to_length(spoke, spoke, g_beam_ring_spoke_length);
            FastVecAdd(quad.vertex[0], position, spoke);
            FastVecSub(quad.vertex[1], position, spoke);
            FastVecScale(spoke, spoke, g_beam_ring_spoke_target / g_beam_ring_spoke_length);
            FastVecAdd(side, position, radius);
            FastVecAdd(quad.vertex[2], side, spoke);
            FastVecSub(quad.vertex[3], side, spoke);
            draw_world_quad(&quad, 0, 0);
            if (i < 7) {
                math_build_axis_angle_quat(rotation, view, 0.7853981853f);
                vec_rotate_by_quaternion(radius, radius, rotation);
            }
        }
    }
    alpha = IntToFloat(*(short *)(state + 10)) * *(float *)(state + 0x24);
    {
        float first = FastAddRotations(*(float *)(state + 0x28), g_beam_ring_first_angle_deg * 0.017453294f);
        float secondStep = g_beam_ring_step_angle_deg * 0.017453294f;
        *(float *)(state + 0x28) = first;
        *(float *)(state + 0x2C) = FastAddRotations(*(float *)(state + 0x2C), secondStep);
    }
    gfx_init_quad_packet_state((QuadPacket *)&quad, 0x38, 1, 0x80);
    quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = (FloatToInt(alpha * 20.0f) << 24) | 0x8080FF;
    quad.uv[0][0] = 0.0f; quad.uv[0][1] = 0.0f;
    quad.uv[1][0] = 0.0f; quad.uv[1][1] = 1.0f;
    quad.uv[2][0] = 1.0f; quad.uv[2][1] = 0.0f;
    quad.uv[3][0] = 1.0f; quad.uv[3][1] = 1.0f;
    FastVecScale(radius, state + 0x30, alpha * -16.0f + 16.0f);
    FastVecAdd(center, position, radius);
    FastVecSub(rotation, g_camera_l00_position, center);
    vec_scale_to_length(rotation, rotation, 1.0f);
    math_build_axis_angle_quat(spoke, rotation, *(float *)(state + 0x28));
    FastVecCross(side, rotation, normal);
    FastVecCross(up, side, rotation);
    vec_rotate_by_quaternion(horizontal, up, spoke);
    scale = g_beam_ring_scale_start + (g_beam_ring_scale_end - g_beam_ring_scale_start) * alpha;
    vec_scale_to_length(horizontal, horizontal, scale);
    FastVecCross(vertical, rotation, horizontal);
    vec_scale_to_length(vertical, vertical, scale);
    FastVecAdd(corner, center, horizontal);
    FastVecAdd(quad.vertex[0], corner, vertical);
    FastVecSub(quad.vertex[1], corner, vertical);
    FastVecSub(corner, center, horizontal);
    FastVecAdd(quad.vertex[2], corner, vertical);
    FastVecSub(quad.vertex[3], corner, vertical);
    draw_world_quad(&quad, 0, 0);
    math_build_axis_angle_quat(spoke, rotation, *(float *)(state + 0x2C));
    vec_rotate_by_quaternion(horizontal, up, spoke);
    FastVecScale(horizontal, horizontal, scale);
    FastVecCross(vertical, rotation, horizontal);
    vec_scale_to_length(vertical, vertical, scale);
    FastVecAdd(corner, center, horizontal);
    FastVecAdd(quad.vertex[0], corner, vertical);
    FastVecSub(quad.vertex[1], corner, vertical);
    FastVecSub(corner, center, horizontal);
    FastVecAdd(quad.vertex[2], corner, vertical);
    FastVecSub(quad.vertex[3], corner, vertical);
    draw_world_quad(&quad, 0, 0);
    if (*(int *)(state + 0x40)) {
        alpha = IntToFloat(*(int *)(state + 0x40)) * *(float *)(state + 0x44);
        gfx_init_quad_packet_state((QuadPacket *)&quad, 11, 4, 0x80);
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = (FloatToInt(alpha * 255.0f) << 24) | 0x808080;
        FastVecScale(temporary, view, -0.1f);
        FastVecAdd(center, g_camera_l00_position, temporary);
        FastVecCross(vertical, view, normal);
        vec_scale_to_length(vertical, vertical, g_beam_ring_quad_length);
        FastVecCross(horizontal, vertical, view);
        vec_scale_to_length(horizontal, horizontal, g_beam_ring_quad_length);
        FastVecAdd(corner, center, horizontal);
        FastVecAdd(quad.vertex[0], corner, vertical);
        FastVecSub(quad.vertex[1], corner, vertical);
        FastVecSub(corner, center, horizontal);
        FastVecAdd(quad.vertex[2], corner, vertical);
        FastVecSub(quad.vertex[3], corner, vertical);
        draw_world_quad(&quad, 0, 0);
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = (FloatToInt(g_beam_l00_ring_alpha_scale * alpha) << 24) | 0x808080;
        VU1_addGSregister(0x42, 0x48ULL);
        gfx_draw_colored_rectangle(0, g_screen_adjust_offsets[0xA9], 0, g_screen_adjust_offsets[0xA8], quad.color[0]);
    }
}
