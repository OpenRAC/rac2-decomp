/* func_PAL_00309A30, the PAL copy of func_00308768: the same C. */
#include "common.h"
/* Adapted from RAC1 visibomb_and_pyrocitor.c (OpenRAC, GPL-3.0). */
typedef struct { float x,y,z,w; } __attribute__((aligned(16))) BeamVec;
typedef int Q_2B4918 __attribute__((mode(TI)));
typedef struct { float pos[4][4]; unsigned int col[4]; float uv[4][2]; unsigned long tag[4]; } Quad_2B4918;
typedef struct { int a, b; } Ids_2B4918;
typedef struct { float x, y, z; } P3_2B4918;
typedef struct { float u, v; } UV_2B4918;
typedef struct Child_2B4918 { char pad0[0xAA]; short cls; } Child_2B4918;
typedef struct Data_2B4918 { int f0; int f4; Child_2B4918 *child; char padC[0x14]; float f20; char pad24[8]; float f2C; } Data_2B4918;

extern Child_2B4918 *g_beam_child NOT_SDA;
extern Ids_2B4918 g_beam_ids_a NOT_SDA;
extern Ids_2B4918 g_beam_ids_b NOT_SDA;
extern float g_beam_quad_offsets_a[][4] SDATA(D_001AECF0);
extern UV_2B4918 g_beam_quad_uvs[] SDATA(D_001AED70);
/* Retail constructs the V-component address absolutely, the U base through GP. */
extern UV_2B4918 beam_uv_absolute[] __asm__("D_001AED70") MACRO_ADDR;
extern float g_beam_quad_offsets_b[][4] SDATA(D_001AED30);
extern float g_camera_eye_state[];
extern UV_2B4918 g_beam_uvs[];
extern float g_beam_vectors[][4];
extern P3_2B4918 g_beam_glint_points[];
extern int g_beam_colors[];
extern char g_hero_state[];
extern void moby_transform_point_list(void *, int, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void set_identity_matrix(void *);
extern void multiply_matrix(void *, void *, void *);
extern long GetEffectTextureDescriptor(int);
extern void FastVecScale(void *, void *, float);
extern float math_random_float_range(float, float);
extern void draw_world_quad(void *, void *, int);
extern void FastVecAdd(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern void VU1_addGSregister(int, long);
extern void font_queue_vu_state(void);
extern void part_draw_glint_effect(int, void *, void *, void *, int);

/* Draws the moby's beam: orients the moby along its child's two joints, draws three quads and a ribbon of 196 points. */
void draw_joint_aligned_beam_effect_pal(char *moby) {
    Quad_2B4918 packet;
    BeamVec basis[4];
    BeamVec joint_pos[2];
    Ids_2B4918 ids;
    BeamVec up;
    BeamVec world_matrix[4];
    BeamVec offset_matrix[4];
    BeamVec view_dir;
    BeamVec view_right;
    BeamVec view_up;
    BeamVec glow_pos;
    BeamVec glint_pt;
    Child_2B4918 *child = g_beam_child;
    Data_2B4918 *data = (Data_2B4918 *)*(void **)(moby + 0x68);
    int i;
    int j;

    if (child == 0 || (child->cls != 0x260 && child->cls != 0x96C)) {
        return;
    }
    packet.tag[2] = 0xFF9000000260;
    packet.tag[3] = 0x8000000048;
    packet.tag[0] = 0;
    if (data->f4 != 0) {
        ids = g_beam_ids_a;
        moby_transform_point_list(child, 2, &ids, joint_pos);
    } else {
        ids = g_beam_ids_b;
        moby_transform_point_list(child, 2, &ids, joint_pos);
    }
    *(Q_2B4918 *)&up = 0;
    up.y = 1.0f;
    FastVecSub(&basis[2], &joint_pos[0], &joint_pos[1]);
    vec_scale_to_length(&basis[2], &basis[2], 1.0f);
    basis[2].w = 0.0f;
    FastVecCross(&basis[0], &up, &basis[2]);
    vec_scale_to_length(&basis[0], &basis[0], 1.0f);
    basis[0].w = 0.0f;
    FastVecCross(&basis[1], &basis[2], &basis[0]);
    basis[1].w = 0.0f;
    qcopy(&basis[3], &joint_pos[1]);
    basis[3].w = 1.0f;
    qcopy(moby + 0xC0, &basis[0]);
    qcopy(moby + 0xD0, &basis[1]);
    qcopy(moby + 0xE0, &basis[2]);
    qcopy(moby + 0x10, &basis[3]);
    set_identity_matrix(offset_matrix);
    offset_matrix[3].w = 1.0f;
    offset_matrix[3].z = -0.075f;
    offset_matrix[3].x = 0.0f;
    offset_matrix[3].y = 0.0f;
    multiply_matrix(world_matrix, basis, offset_matrix);
    packet.tag[1] = GetEffectTextureDescriptor(0xC);
    for (i = 0; i < 4; i++) {
        packet.col[i] = 0x80808080;
        if (i == 0 || i == 2) {
            FastVecScale(packet.pos[i], g_beam_quad_offsets_a[i], data->f2C);
        } else {
            float *v = packet.pos[i];
            FastVecScale(v, g_beam_quad_offsets_a[i], data->f2C);
            v[2] -= math_random_float_range(0.0f, 0.1f);
        }
        packet.uv[i][0] = g_beam_quad_uvs[i].u;
        packet.uv[i][1] = beam_uv_absolute[i].v;
    }
    draw_world_quad(&packet, world_matrix, 0);
    for (i = 0; i < 4; i++) {
        if (i == 0 || i == 2) {
            FastVecScale(packet.pos[i], g_beam_quad_offsets_b[i], data->f2C);
        } else {
            float *v = packet.pos[i];
            FastVecScale(v, g_beam_quad_offsets_b[i], data->f2C);
            v[2] -= math_random_float_range(0.0f, 0.1f);
        }
    }
    draw_world_quad(&packet, world_matrix, 0);
    packet.tag[1] = GetEffectTextureDescriptor(0xB);
    FastVecScale(&glow_pos, &basis[2], -0.13f);
    FastVecAdd(&glow_pos, &glow_pos, &basis[3]);
    FastVecSub(&view_dir, g_camera_eye_state, &glow_pos);
    vec_scale_to_length(&view_dir, &view_dir, 1.0f);
    FastVecCross(&view_right, &view_dir, g_hero_state + 0x2C0);
    vec_scale_to_length(&view_right, &view_right, -1.0f);
    FastVecCross(&view_up, &view_right, &view_dir);
    packet.col[0] = packet.col[1] = packet.col[2] = packet.col[3] = 0x7F2020FF;
    for (j = 0; j < 4; j++) {
        FastVecScale(packet.pos[j], g_beam_quad_offsets_a[j], 0.1f);
        transform_vector(packet.pos[j], packet.pos[j], &view_dir);
    }
    draw_world_quad(&packet, 0, 0);
    VU1_addGSregister(6, GetEffectTextureDescriptor(0xA));
    VU1_addGSregister(0x42, packet.tag[3]);
    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x14, 0xFF9000000260);
    VU1_addGSregister(0x4A, 0);
    font_queue_vu_state();
    for (i = 0; i < 0xC4; i++) {
        FastVecScale(&glint_pt, g_beam_vectors[i], data->f20);
        transform_vector(&glint_pt, &glint_pt, basis);
        g_beam_glint_points[i].x = glint_pt.x;
        g_beam_glint_points[i].y = glint_pt.y;
        g_beam_glint_points[i].z = glint_pt.z;
        g_beam_uvs[i].v -= 0.025f;
        if (g_beam_uvs[i].v < -7.0f) {
            g_beam_uvs[i].v += 7.0f;
        }
    }
    part_draw_glint_effect(0x94, g_beam_glint_points, g_beam_colors, g_beam_uvs, 1);
    part_draw_glint_effect(0x32, &g_beam_glint_points[0x92], &g_beam_colors[0x92], &g_beam_uvs[0x92], 1);
}
