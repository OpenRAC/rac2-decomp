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

extern Child_2B4918 *D_0018B130 NOT_SDA;
extern Ids_2B4918 D_001AED90 NOT_SDA;
extern Ids_2B4918 D_001AED98 NOT_SDA;
extern float D_001AECF0[][4] SDATA(D_001AECF0);
extern UV_2B4918 D_001AED70[] SDATA(D_001AED70);
/* Retail constructs the V-component address absolutely, the U base through GP. */
extern UV_2B4918 beam_uv_absolute[] __asm__("D_001AED70") MACRO_ADDR;
extern float D_001AED30[][4] SDATA(D_001AED30);
extern float g_camera_eye_state[];
extern UV_2B4918 D_00265FA0[];
extern float D_00265360[][4];
extern P3_2B4918 D_00228840[];
extern int D_002665C0[];
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
void draw_joint_aligned_beam_effect(char *moby) {
    Quad_2B4918 quad;
    BeamVec basis[4];
    BeamVec joint_points[2];
    Ids_2B4918 ids;
    BeamVec up;
    BeamVec world_matrix[4];
    BeamVec offset_matrix[4];
    BeamVec a;
    BeamVec b;
    BeamVec c;
    BeamVec d;
    BeamVec e;
    Child_2B4918 *child = D_0018B130;
    Data_2B4918 *data = (Data_2B4918 *)*(void **)(moby + 0x68);
    int i;
    int j;

    if (child == 0 || (child->cls != 0x260 /* moby class 608 */ && child->cls != 0x96C /* moby class 2412 */)) {
        return;
    }
    quad.tag[2] = 0xFF9000000260;
    quad.tag[3] = 0x8000000048;
    quad.tag[0] = 0;
    if (data->f4 != 0) {
        ids = D_001AED90;
        moby_transform_point_list(child, 2, &ids, joint_points);
    } else {
        ids = D_001AED98;
        moby_transform_point_list(child, 2, &ids, joint_points);
    }
    *(Q_2B4918 *)&up = 0;
    up.y = 1.0f;
    FastVecSub(&basis[2], &joint_points[0], &joint_points[1]);
    vec_scale_to_length(&basis[2], &basis[2], 1.0f);
    basis[2].w = 0.0f;
    FastVecCross(&basis[0], &up, &basis[2]);
    vec_scale_to_length(&basis[0], &basis[0], 1.0f);
    basis[0].w = 0.0f;
    FastVecCross(&basis[1], &basis[2], &basis[0]);
    basis[1].w = 0.0f;
    qcopy(&basis[3], &joint_points[1]);
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
    quad.tag[1] = GetEffectTextureDescriptor(0xC);
    for (i = 0; i < 4; i++) {
        quad.col[i] = 0x80808080;
        if (i == 0 || i == 2) {
            FastVecScale(quad.pos[i], D_001AECF0[i], data->f2C);
        } else {
            float *v = quad.pos[i];
            FastVecScale(v, D_001AECF0[i], data->f2C);
            v[2] -= math_random_float_range(0.0f, 0.1f);
        }
        quad.uv[i][0] = D_001AED70[i].u;
        quad.uv[i][1] = beam_uv_absolute[i].v;
    }
    draw_world_quad(&quad, world_matrix, 0);
    for (i = 0; i < 4; i++) {
        if (i == 0 || i == 2) {
            FastVecScale(quad.pos[i], D_001AED30[i], data->f2C);
        } else {
            float *v = quad.pos[i];
            FastVecScale(v, D_001AED30[i], data->f2C);
            v[2] -= math_random_float_range(0.0f, 0.1f);
        }
    }
    draw_world_quad(&quad, world_matrix, 0);
    quad.tag[1] = GetEffectTextureDescriptor(0xB);
    FastVecScale(&d, &basis[2], -0.13f);
    FastVecAdd(&d, &d, &basis[3]);
    FastVecSub(&a, g_camera_eye_state, &d);
    vec_scale_to_length(&a, &a, 1.0f);
    FastVecCross(&b, &a, g_hero_state + 0x2C0);
    vec_scale_to_length(&b, &b, -1.0f);
    FastVecCross(&c, &b, &a);
    quad.col[0] = quad.col[1] = quad.col[2] = quad.col[3] = 0x7F2020FF;
    for (j = 0; j < 4; j++) {
        FastVecScale(quad.pos[j], D_001AECF0[j], 0.1f);
        transform_vector(quad.pos[j], quad.pos[j], &a);
    }
    draw_world_quad(&quad, 0, 0);
    VU1_addGSregister(6, GetEffectTextureDescriptor(0xA));
    VU1_addGSregister(0x42, quad.tag[3]);
    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x14, 0xFF9000000260);
    VU1_addGSregister(0x4A, 0);
    font_queue_vu_state();
    for (i = 0; i < 0xC4; i++) {
        FastVecScale(&e, D_00265360[i], data->f20);
        transform_vector(&e, &e, basis);
        D_00228840[i].x = e.x;
        D_00228840[i].y = e.y;
        D_00228840[i].z = e.z;
        D_00265FA0[i].v -= 0.025f;
        if (D_00265FA0[i].v < -7.0f) {
            D_00265FA0[i].v += 7.0f;
        }
    }
    part_draw_glint_effect(0x94, D_00228840, D_002665C0, D_00265FA0, 1);
    part_draw_glint_effect(0x32, &D_00228840[0x92], &D_002665C0[0x92], &D_00265FA0[0x92], 1);
}
