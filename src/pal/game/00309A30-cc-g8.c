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
void func_PAL_00309A30(char *m) {
    Quad_2B4918 pk;
    BeamVec mtx[4];
    BeamVec out[2];
    Ids_2B4918 ids;
    BeamVec up;
    BeamVec res[4];
    BeamVec idm[4];
    BeamVec a;
    BeamVec b;
    BeamVec c;
    BeamVec d;
    BeamVec e;
    Child_2B4918 *child = g_beam_child;
    Data_2B4918 *data = (Data_2B4918 *)*(void **)(m + 0x68);
    int i;
    int j;

    if (child == 0 || (child->cls != 0x260 && child->cls != 0x96C)) {
        return;
    }
    pk.tag[2] = 0xFF9000000260;
    pk.tag[3] = 0x8000000048;
    pk.tag[0] = 0;
    if (data->f4 != 0) {
        ids = g_beam_ids_a;
        moby_transform_point_list(child, 2, &ids, out);
    } else {
        ids = g_beam_ids_b;
        moby_transform_point_list(child, 2, &ids, out);
    }
    *(Q_2B4918 *)&up = 0;
    up.y = 1.0f;
    FastVecSub(&mtx[2], &out[0], &out[1]);
    vec_scale_to_length(&mtx[2], &mtx[2], 1.0f);
    mtx[2].w = 0.0f;
    FastVecCross(&mtx[0], &up, &mtx[2]);
    vec_scale_to_length(&mtx[0], &mtx[0], 1.0f);
    mtx[0].w = 0.0f;
    FastVecCross(&mtx[1], &mtx[2], &mtx[0]);
    mtx[1].w = 0.0f;
    qcopy(&mtx[3], &out[1]);
    mtx[3].w = 1.0f;
    qcopy(m + 0xC0, &mtx[0]);
    qcopy(m + 0xD0, &mtx[1]);
    qcopy(m + 0xE0, &mtx[2]);
    qcopy(m + 0x10, &mtx[3]);
    set_identity_matrix(idm);
    idm[3].w = 1.0f;
    idm[3].z = -0.075f;
    idm[3].x = 0.0f;
    idm[3].y = 0.0f;
    multiply_matrix(res, mtx, idm);
    pk.tag[1] = GetEffectTextureDescriptor(0xC);
    for (i = 0; i < 4; i++) {
        pk.col[i] = 0x80808080;
        if (i == 0 || i == 2) {
            FastVecScale(pk.pos[i], g_beam_quad_offsets_a[i], data->f2C);
        } else {
            float *v = pk.pos[i];
            FastVecScale(v, g_beam_quad_offsets_a[i], data->f2C);
            v[2] -= math_random_float_range(0.0f, 0.1f);
        }
        pk.uv[i][0] = g_beam_quad_uvs[i].u;
        pk.uv[i][1] = beam_uv_absolute[i].v;
    }
    draw_world_quad(&pk, res, 0);
    for (i = 0; i < 4; i++) {
        if (i == 0 || i == 2) {
            FastVecScale(pk.pos[i], g_beam_quad_offsets_b[i], data->f2C);
        } else {
            float *v = pk.pos[i];
            FastVecScale(v, g_beam_quad_offsets_b[i], data->f2C);
            v[2] -= math_random_float_range(0.0f, 0.1f);
        }
    }
    draw_world_quad(&pk, res, 0);
    pk.tag[1] = GetEffectTextureDescriptor(0xB);
    FastVecScale(&d, &mtx[2], -0.13f);
    FastVecAdd(&d, &d, &mtx[3]);
    FastVecSub(&a, g_camera_eye_state, &d);
    vec_scale_to_length(&a, &a, 1.0f);
    FastVecCross(&b, &a, g_hero_state + 0x2C0);
    vec_scale_to_length(&b, &b, -1.0f);
    FastVecCross(&c, &b, &a);
    pk.col[0] = pk.col[1] = pk.col[2] = pk.col[3] = 0x7F2020FF;
    for (j = 0; j < 4; j++) {
        FastVecScale(pk.pos[j], g_beam_quad_offsets_a[j], 0.1f);
        transform_vector(pk.pos[j], pk.pos[j], &a);
    }
    draw_world_quad(&pk, 0, 0);
    VU1_addGSregister(6, GetEffectTextureDescriptor(0xA));
    VU1_addGSregister(0x42, pk.tag[3]);
    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x14, 0xFF9000000260);
    VU1_addGSregister(0x4A, 0);
    font_queue_vu_state();
    for (i = 0; i < 0xC4; i++) {
        FastVecScale(&e, g_beam_vectors[i], data->f20);
        transform_vector(&e, &e, mtx);
        g_beam_glint_points[i].x = e.x;
        g_beam_glint_points[i].y = e.y;
        g_beam_glint_points[i].z = e.z;
        g_beam_uvs[i].v -= 0.025f;
        if (g_beam_uvs[i].v < -7.0f) {
            g_beam_uvs[i].v += 7.0f;
        }
    }
    part_draw_glint_effect(0x94, g_beam_glint_points, g_beam_colors, g_beam_uvs, 1);
    part_draw_glint_effect(0x32, &g_beam_glint_points[0x92], &g_beam_colors[0x92], &g_beam_uvs[0x92], 1);
}
