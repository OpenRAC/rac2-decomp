#include "common.h"

typedef struct { float x, y, z; } BallVec3;
typedef struct {
    u32 points[4][4];
    u32 colors[4];
    float texcoords[8];
    u64 texture[4];
} __attribute__((aligned(16))) BallQuad;
extern float g_nanotech_pulse_amp __attribute__((sda));
extern float g_nanotech_ball_inner_scale __attribute__((sda));
extern float g_nanotech_ball_normalize_length __attribute__((sda));
extern float g_nanotech_ball_scale_factor __attribute__((sda));
extern int g_ball_texture_word_a __attribute__((sda));
extern int g_ball_texture_word_b __attribute__((sda));
extern int g_ball_texture_word_c __attribute__((sda));
extern int g_nanotech_ball_tex_bits_low __attribute__((sda));
extern int g_nanotech_ball_tex_bits_high __attribute__((sda));
extern u32 g_nanotech_ball_texture_id __attribute__((sda));
extern u32 g_nanotech_ball_color_a __attribute__((sda));
extern u32 g_nanotech_ball_color_b __attribute__((sda));
extern u32 g_nanotech_ball_alpha_color_a __attribute__((sda));
extern u32 g_nanotech_ball_alpha_color_b __attribute__((sda));
extern u32 g_nanotech_ball_texture_id_alt __attribute__((sda));
extern char g_camera_eye_state[];
extern char g_ball_center_offset[] MACRO_ADDR;
extern char g_nanotech_ball_vertices[];
extern char g_nanotech_ball_uvs[];
extern char g_nanotech_ball_scales[];
extern char g_nanotech_ball_indices[];
extern char g_nanotech_env_corners_a[];
extern char g_nanotech_env_corners_b[];
extern char g_nanotech_ball_points[];
extern short g_nanotech_ball_rows[] SDATA(D_001AF210);
extern int g_ball_color_offset;
extern s64 GetEffectTextureDescriptor(int);
extern void VU1_addGSregister(int,u64);
extern void FastVecAdd(void *,void *,void *), FastVecSub(void *,void *,void *), FastVecCross(void *,void *,void *), transform_vector(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float), FastVecScale(void *,void *,float), vec_fast_normalize_helper(void *,void *,float);
extern void font_queue_vu_state(void), part_draw_glint_effect(int,void *,void *,void *,int), draw_world_quad(void *,void *,int);
extern int FloatToInt(float), moby_is_state_one(unsigned char *);
extern float fast_fmod(float,float);
extern void gravity_offset_position(void *,void *,void *,float);
/* Adapted from RAC1 draw_nanotech_ball (GPL-3.0); RAC2 selects alternate colors and owner geometry. */
/* Draws a nanotech ball: a glowing sphere with a pulsing halo and a shiny environment reflection. */
void draw_nanotech_ball(unsigned char *moby) {
    BallQuad quad;
    float basis[4] __attribute__((aligned(16)));
    float *forward;
    float side[4] __attribute__((aligned(16)));
    float up[4] __attribute__((aligned(16)));
    float center[4] __attribute__((aligned(16)));
    float view_dir[4] __attribute__((aligned(16)));
    float to_camera[4] __attribute__((aligned(16)));
    float vertex[4] __attribute__((aligned(16)));
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    unsigned char *owner;
    float pulse = *(float *)vars / g_nanotech_pulse_amp;
    u32 sphere_colors[290];
    int i, j, color;
    short *indices;
    short *row;
    short *rows;
    char *corner;
    char *env_corners;
    char *outer, *inner;
    float *u, *v;

    quad.texture[1] = GetEffectTextureDescriptor(g_nanotech_ball_texture_id);
    quad.texture[2] = 0xff9000000260ULL;
    quad.texture[3] = (u64)g_ball_texture_word_a;
    quad.texture[3] |= (u64)g_ball_texture_word_b << 2;
    quad.texture[3] |= (u64)g_ball_texture_word_c << 4;
    quad.texture[3] |= (u64)g_nanotech_ball_tex_bits_low << 6;
    quad.texture[3] |= (u64)g_nanotech_ball_tex_bits_high << 32;
    quad.texture[0] = 0;
    VU1_addGSregister(0x47, 0x53001);
    if (moby[0x20] == 1) {
        unsigned char *parent = *(unsigned char **)(moby + 0xB8);
        qcopy(moby + 0x10, parent + 0x10);
        qcopy(vars + 0x10, parent + 0x10);
        gravity_offset_position(moby + 0x10, vars + 0x10, vars + 0x10, -0.5f);
    }
    forward = basis;
    center[0] = *(float *)(moby + 0x10);
    center[1] = *(float *)(moby + 0x14);
    center[2] = *(float *)(moby + 0x18);
    gravity_offset_position(moby + 0x10, center, center, -0.5f - *(float *)vars);
    center[3] = 1.0f;
    FastVecAdd(&center, &center, g_ball_center_offset);
    FastVecSub(&to_camera, g_camera_eye_state, &center);
    vec_scale_to_length(forward, &to_camera, 1.0f);
    owner = *(unsigned char **)(moby + 0xB8);
    FastVecCross(&side, forward, owner + 0xE0);
    vec_scale_to_length(&side, &side, 1.0f);
    FastVecCross(&up, &side, forward);
    if (vars[0x57]) {
        quad.colors[3] = g_nanotech_ball_color_b;
        quad.colors[2] = g_nanotech_ball_color_b;
        quad.colors[1] = g_nanotech_ball_color_b;
        quad.colors[0] = g_nanotech_ball_color_b;
    } else {
        quad.colors[3] = g_nanotech_ball_color_a;
        quad.colors[2] = g_nanotech_ball_color_a;
        quad.colors[1] = g_nanotech_ball_color_a;
        quad.colors[0] = g_nanotech_ball_color_a;
    }
    VU1_addGSregister(6, GetEffectTextureDescriptor(g_nanotech_ball_texture_id));
    VU1_addGSregister(0x42, 0x8000000044ULL);
    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x14, 0xff9000000260ULL);
    VU1_addGSregister(0x4a, 0);
    font_queue_vu_state();
    for (j = 0; j < 0x122; j++) {
        transform_vector(&vertex, g_nanotech_ball_vertices + j * 16, basis);
        {
            float x = vertex[0], y = vertex[1], z = vertex[2];
            ((BallVec3 *)g_nanotech_ball_points)[j].x = x;
            ((BallVec3 *)g_nanotech_ball_points)[j].y = y;
            ((BallVec3 *)g_nanotech_ball_points)[j].z = z;
            sphere_colors[j] = quad.colors[0];
        }
    }
    part_draw_glint_effect(0x94, g_nanotech_ball_points, sphere_colors, g_nanotech_ball_uvs, 1);
    part_draw_glint_effect(0x6d, g_nanotech_ball_points + 0x6d8, sphere_colors + 0x92, g_nanotech_ball_uvs + 0x490, 1);
    part_draw_glint_effect(0x24, g_nanotech_ball_points + 0xbe8, sphere_colors + 0xFE, g_nanotech_ball_uvs + 0x7f0, 1);
    quad.texture[1] = GetEffectTextureDescriptor(0xb);
    quad.texture[3] = 0x8000000048ULL;
    color = FloatToInt(pulse * 64.0f + 128.0f);
    color += g_ball_color_offset;
    if (vars[0x57]) {
        quad.colors[1] = ((u32)color << 24) | g_nanotech_ball_alpha_color_b;
        quad.colors[0] = quad.colors[1];
    } else {
        quad.colors[1] = ((u32)color << 24) | g_nanotech_ball_alpha_color_a;
        quad.colors[0] = quad.colors[1];
    }
    quad.colors[3] = 0;
    quad.colors[2] = 0;
    for (i = 0; i < 32; i++) {
        indices = (short *)(g_nanotech_ball_indices + i * 8);
        j = 0;
        inner = (char *)quad.points;
        outer = (char *)quad.points;
        for (; j < 4; j++) {
            short index = *indices;
            if (j >= 2)
                FastVecScale(outer, g_nanotech_ball_scales + index * 16,
                             g_nanotech_ball_inner_scale * g_nanotech_ball_scale_factor);
            else
                FastVecScale(inner, g_nanotech_ball_scales + index * 16, g_nanotech_ball_inner_scale);
            inner += 16;
            outer += 16;
            indices++;
        }
        quad.texcoords[0] = 0.5f;
        quad.texcoords[1] = 0.5f;
        quad.texcoords[2] = 0.5f;
        quad.texcoords[3] = 0.5f;
        quad.texcoords[4] = 0.5f;
        quad.texcoords[5] = 1.0f;
        quad.texcoords[6] = 0.5f;
        quad.texcoords[7] = 1.0f;
        draw_world_quad(&quad, basis, 0);
    }
    if (moby_is_state_one(moby)) {
        unsigned char *surface_owner;
        quad.texture[1] = GetEffectTextureDescriptor(g_nanotech_ball_texture_id_alt);
        quad.colors[3] = 0x107f7f7f;
        quad.colors[2] = 0x107f7f7f;
        quad.colors[1] = 0x107f7f7f;
        quad.colors[0] = 0x107f7f7f;
        quad.texture[3] = 0x8000000044ULL;
        {
            surface_owner = *(unsigned char **)(moby + 0xB8);
            qcopy(basis, surface_owner + 0xC0);
            qcopy(&side, surface_owner + 0xD0);
            qcopy(&up, surface_owner + 0xE0);
        }
        center[2] = *(float *)(moby + 0x18);

        rows = (short *)g_nanotech_ball_rows;
        if (*(short *)(surface_owner + 0xAA) == MOBY_CLASS_NANOTECH_CRATE)
            env_corners = g_nanotech_env_corners_b;
        else
            env_corners = g_nanotech_env_corners_a;
        /* Taking the first texcoord's address before the loop makes gcse insert its
         * base ahead of the second one's (retail's preheader and stack-slot order). */
        v = &quad.texcoords[0];
        for (i = 0; i < 4; i++) {
            u = &quad.texcoords[1];
            v = &quad.texcoords[0];
            row = (short *)(i * 8 + (u32)rows);
            corner = (char *)quad.points;
            for (j = 3; j >= 0; j--) {
                transform_vector(corner, env_corners + (*row++) * 16, basis);
                FastVecSub(view_dir, corner, g_camera_eye_state);
                corner += 16;
                view_dir[1] = view_dir[2];
                vec_fast_normalize_helper(view_dir, view_dir, g_nanotech_ball_normalize_length);
                *v = view_dir[0] * 0.5f + 0.5f;
                *v = fast_fmod(*v, 8.0f);
                v += 2;
                *u = view_dir[1] * 0.5f + 0.5f;
                *u = fast_fmod(*u, 8.0f);
                u += 2;
            }
            draw_world_quad(&quad, 0, 0);
        }
    }
    VU1_addGSregister(0x47, 0x5360b);
}
