#include "common.h"
/* Adapted from RAC1 walloper_and_beam_effects.c (OpenRAC, GPL-3.0). */
extern long long GetEffectTextureDescriptor(int);
extern void FastVecSub(void*,void*,void*), FastVecCross(void*,void*,void*), FastVecAdd(void*,void*,void*);
extern float FastVecLength(void*);
extern void FastVecScale(void*,void*,float), draw_world_quad(void*,void*,int), VU1_addGSregister(int,long);
extern float g_camera_eye_state[];
extern int g_beam_core_texture __attribute__((sda));
extern int g_beam_core_color __attribute__((sda));
extern int g_beam_halo_texture __attribute__((sda));
extern int g_beam_halo_color __attribute__((sda));
extern float g_beam_core_uv_offset __attribute__((sda));
extern int g_beam_normal_scale __attribute__((sda));
typedef float RW_2BBDE8[4] __attribute__((aligned(16)));
typedef struct { float v[4]; } P_2BBDE8;
typedef struct {
    int c[4];
    float f[8];
    long z4, q0, q1, q2;
} RT_2BBDE8;

/* The EE ABI independently orders integer and floating-point arguments.
 * This interleaving preserves a0-a3 and f12-f14. */
// Draws a ribbon of quads along a polyline, in two passes with edge colouring and a scrolled texture (colours from globals).
void DrawBeamAndArcTwoPassQuads(void *points, int alpha_a, int alpha_b, float sx, float width, int count, float extend) {
    RW_2BBDE8 core_quad[4];
    RT_2BBDE8 core_packet;
    RW_2BBDE8 q2[4];
    RT_2BBDE8 halo_packet;
    RW_2BBDE8 normal, halo_offset, eye_ray, tangent, first_point, last_point, first_ray, last_ray, to_eye, extension;
    int i, core_color, halo_color;
    float length, initial_length, halo_length, first_length, last_length;
    core_packet.q0 = GetEffectTextureDescriptor(*(int *)&g_beam_core_texture);
    core_color = *(int *)&g_beam_core_color | (alpha_a << 24);
    core_packet.q2 = 0x8000000048L;
    core_packet.q1 = 0xFF9000000260L;
    core_packet.z4 = 0;
    core_packet.c[3] = core_color;
    core_packet.c[2] = core_color;
    core_packet.c[1] = core_color;
    core_packet.c[0] = core_color;
    halo_packet.q0 = GetEffectTextureDescriptor(*(int *)&g_beam_halo_texture);
    halo_color = *(int *)&g_beam_halo_color | (alpha_b << 24);
    halo_packet.q2 = core_packet.q2;
    halo_packet.q1 = core_packet.q1;
    halo_packet.z4 = core_packet.z4;
    halo_packet.c[3] = halo_color;
    halo_packet.c[2] = halo_color;
    halo_packet.c[1] = halo_color;
    halo_packet.c[0] = halo_color;
    halo_packet.f[0] = 0; halo_packet.f[1] = 0; halo_packet.f[2] = 0; halo_packet.f[3] = 1.0f; halo_packet.f[4] = 1.0f; halo_packet.f[5] = 0; halo_packet.f[6] = 1.0f; halo_packet.f[7] = 1.0f;
    core_packet.f[0] = g_beam_core_uv_offset;
    core_packet.f[1] = 0;
    core_packet.f[2] = g_beam_core_uv_offset;
    core_packet.f[3] = 1.0f;
    core_packet.f[4] = 1.0f + g_beam_core_uv_offset;
    core_packet.f[5] = 0;
    core_packet.f[6] = 1.0f + g_beam_core_uv_offset;
    core_packet.f[7] = 1.0f;
    FastVecSub(eye_ray, points, g_camera_eye_state);
    FastVecSub(tangent, &((P_2BBDE8 *)points)[1], points);
    FastVecCross(normal, tangent, eye_ray);
    initial_length = FastVecLength(normal);
    if (initial_length != 0) initial_length = 1.0f / initial_length;
    FastVecScale(normal, normal, *(float *)&g_beam_normal_scale * initial_length);
    FastVecAdd(core_quad[0], points, normal);
    FastVecSub(core_quad[1], points, normal);
    for (i = 1; i < count - 1; i++) {
        FastVecSub(eye_ray, &((P_2BBDE8 *)points)[i], g_camera_eye_state);
        FastVecSub(tangent, &((P_2BBDE8 *)points)[i + 1], &((P_2BBDE8 *)points)[i]);
        FastVecCross(normal, tangent, eye_ray);
        length = FastVecLength(normal);
        if (length != 0) length = 1.0f / length;
        FastVecScale(normal, normal, *(float *)&g_beam_normal_scale * length);
        FastVecAdd(core_quad[2], &((P_2BBDE8 *)points)[i], normal);
        FastVecSub(core_quad[3], &((P_2BBDE8 *)points)[i], normal);
        if (i == 1) {
            core_packet.c[1] = *(int *)&g_beam_core_color;
            core_packet.c[0] = *(int *)&g_beam_core_color;
        } else if (i == count - 2) {
            core_packet.c[3] = *(int *)&g_beam_core_color;
            core_packet.c[2] = *(int *)&g_beam_core_color;
        } else if (i == 2) {
            core_packet.c[1] = core_color;
            core_packet.c[0] = core_color;
        }
        draw_world_quad(core_quad, 0, 0);
        qcopy(core_quad[0], core_quad[2]);
        qcopy(core_quad[1], core_quad[3]);
    }
    for (i = 0; i < count - 1; i++) {
        FastVecSub(first_ray, &((P_2BBDE8 *)points)[i], g_camera_eye_state);
        FastVecSub(last_ray, &((P_2BBDE8 *)points)[i + 1], g_camera_eye_state);
        first_length = FastVecLength(first_ray);
        last_length = FastVecLength(last_ray);
        if (last_length < first_length) {
            if (last_length == 0) qcopy(last_ray, first_ray);
            else FastVecScale(last_ray, last_ray, first_length / last_length);
        } else {
            if (first_length == 0) qcopy(first_ray, last_ray);
            else FastVecScale(first_ray, first_ray, last_length / first_length);
        }
        FastVecAdd(first_point, g_camera_eye_state, first_ray);
        FastVecAdd(last_point, g_camera_eye_state, last_ray);
        FastVecSub(tangent, last_point, first_point);
        FastVecScale(extension, tangent, extend);
        FastVecSub(first_point, first_point, extension);
        FastVecAdd(last_point, last_point, extension);
        FastVecSub(to_eye, g_camera_eye_state, first_point);
        FastVecCross(normal, to_eye, tangent);
        halo_length = FastVecLength(normal);
        if (halo_length != 0) halo_length = 1.0f / halo_length;
        FastVecScale(halo_offset, normal, width * halo_length);
        FastVecAdd(q2[0], first_point, halo_offset);
        FastVecSub(q2[1], first_point, halo_offset);
        FastVecAdd(q2[2], last_point, halo_offset);
        FastVecSub(q2[3], last_point, halo_offset);
        if (i == 0) {
            halo_packet.c[1] = *(int *)&g_beam_halo_color;
            halo_packet.c[0] = *(int *)&g_beam_halo_color;
        } else if (i == count - 2) {
            halo_packet.c[3] = *(int *)&g_beam_halo_color;
            halo_packet.c[2] = *(int *)&g_beam_halo_color;
        } else if (i == 1) {
            halo_packet.c[1] = halo_color;
            halo_packet.c[0] = halo_color;
        }
        draw_world_quad(q2, 0, 0);
    }
    VU1_addGSregister(0x47, 0x5360B);
}
