#include "names.h"
/* Adapted from OpenRAC rac1-decomp, GPL-3.0, heavy_interceptor_and_turrets.c,
 * Revision a23a07114bae7547adffb442b0f23fc295a48238,
 * draw_blarg_heavy_interceptor_light_ring. The four-row frame, 82 XYZ
 * vertices, 84 colors and temporary vector agree with the measured RAC2
 * frame; source tables retain incomplete outer extents.
 */
#include "common.h"
extern void beam_draw_tip_glow(char *);
extern char g_camera_l09_position[];
extern int g_light_ring_point_count __attribute__((sda));
extern float g_light_ring_points[][3];
extern u32 g_color_pulse_colors[];
extern char g_light_ring_uvs[];
extern u64 GetEffectTextureDescriptor(int);
extern void VU1_addGSregister(int,u64);
extern void font_queue_vu_state(void);
extern void part_draw_glint_effect(int,void *,void *,void *,int);
extern void FastVecSub(void *,void *,void *), FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float), FastVecScale(void *,void *,float);
extern void transform_vector(void *,void *,void *);

/* Draws the object's ring of lights facing the camera, once on each side. */
void light_ring_draw(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    struct {
        float mat[4][4]; /* camera-facing frame */
        float verts[82][3]; /* ring vertices transformed by mat */
    } frame;
    u32 colors[84];
    float point[4];
    int i;
    int j;

    beam_draw_tip_glow(moby);
    qcopy(frame.mat[0], vars + 0x340);
    FastVecSub(frame.mat[2], vars + 0x370, g_camera_l09_position);
    FastVecCross(frame.mat[1], frame.mat[0], frame.mat[2]);
    vec_scale_to_length(frame.mat[1], frame.mat[1], 1.0f);
    FastVecCross(frame.mat[2], frame.mat[1], frame.mat[0]);
    qcopy(frame.mat[3], vars + 0x370);
    frame.mat[3][3] = 1.0f;
    VU1_addGSregister(6, GetEffectTextureDescriptor(0x16));
    VU1_addGSregister(0x42, 0x8000000048);
    VU1_addGSregister(8, 5);
    VU1_addGSregister(0x14, 0xFF9000000260);
    VU1_addGSregister(0x47, 0x51001);
    VU1_addGSregister(0x4A, 0);
    font_queue_vu_state();
    for (i = 0; i < g_light_ring_point_count; i++) {
        float *src = g_light_ring_points[i];
        float *out = frame.verts[i];
        point[0] = src[0];
        point[1] = src[1];
        point[2] = src[2];
        point[3] = 1.0f;
        transform_vector(point, point, frame.mat);
        out[0] = point[0];
        out[1] = point[1];
        out[2] = point[2];
        if (*(short *)(vars + 0x422) != 0) {
            colors[i] = g_color_pulse_colors[i] & 0xFF0000FF;
        }
    }
    if (*(short *)(vars + 0x422) != 0) {
        part_draw_glint_effect(g_light_ring_point_count, frame.verts, colors, g_light_ring_uvs, 1);
    } else {
        part_draw_glint_effect(g_light_ring_point_count, frame.verts, g_color_pulse_colors, g_light_ring_uvs, 1);
    }
    FastVecScale(frame.mat[1], frame.mat[1], -1.0f);
    FastVecScale(frame.mat[2], frame.mat[2], -1.0f);
    for (j = 0; j < g_light_ring_point_count; j++) {
        float *out = frame.verts[j];
        float *src = g_light_ring_points[j];
        point[0] = src[0];
        point[1] = src[1];
        point[2] = src[2];
        point[3] = 1.0f;
        transform_vector(point, point, frame.mat);
        out[0] = point[0];
        out[1] = point[1];
        out[2] = point[2];
    }
    if (*(short *)(vars + 0x422) != 0) {
        part_draw_glint_effect(g_light_ring_point_count, frame.verts, colors, g_light_ring_uvs, 1);
    } else {
        part_draw_glint_effect(g_light_ring_point_count, frame.verts, g_color_pulse_colors, g_light_ring_uvs, 1);
    }
}
