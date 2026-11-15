#include "names.h"
/* func_L00_0038FE10 draws a joint-aligned beam: three quads and a 196-point scrolling ribbon. RAC1 has the same effect
   as draw_joint_aligned_beam_effect (src/overlays/shared/visibomb_and_pyrocitor.c). D_0018B130 needs NOT_SDA, and the
   UV table is read through both its MACRO_ADDR view and an SDATA view. */
#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vector;
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float math_random_float_range(float, float);
extern Vector g_camera_l00_position;
/* The draw packet has four positions, four packed colors and four UV pairs. */
typedef unsigned long long PacketWord;
typedef struct { int index[2]; } JointPair;
typedef struct { float u, v; } BeamUV;
typedef struct {
    float position[4][4];
    unsigned int color[4];
    BeamUV uv[4];
    PacketWord tag, primitive, texture, blend;
} DrawPacket;
typedef struct { char pad[0xAA]; short kind; } BeamChild;
typedef struct { int first, alternate; char pad08[0x18]; float ribbonScale; char pad24[8]; float quadScale; } BeamState;
typedef struct { char pad00[0x10]; Vector position; char pad20[0x48]; BeamState *state; char pad6C[0x54]; Vector rotation[3]; } BeamObject;
typedef struct { float x, y, z; } BeamPoint;
extern BeamChild *D_0018B130 NOT_SDA;
extern JointPair D_L00_001AF0D0[], D_L00_001AF0D8[];
extern float D_L00_001AF030[4][4] SDATA(D_L00_001AF030);
extern float D_L00_001AF070[4][4] SDATA(D_L00_001AF070);
extern BeamUV D_L00_001AF0B0[4] MACRO_ADDR;
extern BeamUV beamUVGP[4] SDATA(D_L00_001AF0B0);
extern Vector D_0018A0E0;
extern Vector D_L00_00290E00[196];
extern BeamPoint D_L00_00239020[196];
extern float D_L00_00291A40[196][2];
extern unsigned int D_L00_00292060[196];
extern void moby_transform_point_list(void *, int, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void set_identity_matrix(void *);
extern void multiply_matrix(void *, void *, void *);
extern PacketWord GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, void *, int);
extern void transform_vector(void *, void *, void *);
extern void VU1_addGSregister(int, PacketWord);
extern void font_queue_vu_state(void);
extern void part_draw_glint_effect(int, void *, void *, void *, int);

/* Draws the glowing joint-aligned beam effect: a few flat quads and a scrolling ribbon. */
void gfx_draw_joint_beam_effect(BeamObject *object)
{
    DrawPacket packet;
    Vector basis[4], joints[2];
    JointPair jointIndices;
    Vector up, matrix[4], adjustment[4], frame[4], point;
    BeamState *state = object->state;
    int i;
    if (D_0018B130 == 0 ||
        (D_0018B130->kind != 0x260 && D_0018B130->kind != 0x96C))
        return;
    packet.texture = 0xFF9000000260ULL;
    packet.blend = 0x8000000048ULL;
    packet.tag = 0;
    if (state->alternate) {
        jointIndices = D_L00_001AF0D0[0];
        moby_transform_point_list(D_0018B130, 2, &jointIndices, joints);
    } else {
        jointIndices = D_L00_001AF0D8[0];
        moby_transform_point_list(D_0018B130, 2, &jointIndices, joints);
    }
    *(Quadword *)&up = 0;
    up.y = 1.0f;
    FastVecSub(&basis[2], &joints[0], &joints[1]);
    vec_scale_to_length(&basis[2], &basis[2], 1.0f);
    basis[2].w = 0.0f;
    FastVecCross(&basis[0], &up, &basis[2]);
    vec_scale_to_length(&basis[0], &basis[0], 1.0f);
    basis[0].w = 0.0f;
    FastVecCross(&basis[1], &basis[2], &basis[0]);
    basis[1].w = 0.0f;
    qcopy(&basis[3], &joints[1]);
    basis[3].w = 1.0f;
    qcopy(&object->rotation[0], &basis[0]);
    qcopy(&object->rotation[1], &basis[1]);
    qcopy(&object->rotation[2], &basis[2]);
    qcopy(&object->position, &basis[3]);
    set_identity_matrix(adjustment);
    adjustment[3].w = 1.0f;
    adjustment[3].z = -0.075f;
    adjustment[3].x = 0.0f;
    adjustment[3].y = 0.0f;
    multiply_matrix(matrix, basis, adjustment);
    packet.primitive = GetEffectTextureDescriptor(12);
    for (i = 0; i < 4; i++) {
        packet.color[i] = 0x80808080;
        if (i == 0 || i == 2)
            FastVecScale(packet.position[i], D_L00_001AF030[i], state->quadScale);
        else {
            float *v = packet.position[i];
            FastVecScale(v, D_L00_001AF030[i], state->quadScale);
            v[2] -= math_random_float_range(0.0f, 0.1f);
        }
        packet.uv[i].u = beamUVGP[i].u;
        packet.uv[i].v = D_L00_001AF0B0[i].v;
    }
    draw_world_quad(&packet, matrix, 0);
    for (i = 0; i < 4; i++) {
        if (i == 0 || i == 2)
            FastVecScale(packet.position[i], D_L00_001AF070[i], state->quadScale);
        else {
            float *v = packet.position[i];
            FastVecScale(v, D_L00_001AF070[i], state->quadScale);
            v[2] -= math_random_float_range(0.0f, 0.1f);
        }
    }
    draw_world_quad(&packet, matrix, 0);
    packet.primitive = GetEffectTextureDescriptor(11);
    FastVecScale(&frame[3], &basis[2], -0.13f);
    FastVecAdd(&frame[3], &frame[3], &basis[3]);
    FastVecSub(&frame[0], &g_camera_l00_position, &frame[3]);
    vec_scale_to_length(&frame[0], &frame[0], 1.0f);
    FastVecCross(&frame[1], &frame[0], &D_0018A0E0);
    vec_scale_to_length(&frame[1], &frame[1], -1.0f);
    FastVecCross(&frame[2], &frame[1], &frame[0]);
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = 0x7F2020FF;
    {
        int corner;
        for (corner = 0; corner < 4; corner++) {
            FastVecScale(packet.position[corner], D_L00_001AF030[corner], 0.1f);
            transform_vector(packet.position[corner], packet.position[corner], frame);
        }
    }
    draw_world_quad(&packet, 0, 0);
    VU1_addGSregister(6, GetEffectTextureDescriptor(10));
    VU1_addGSregister(0x42, packet.blend);
    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x14, 0xFF9000000260ULL);
    VU1_addGSregister(0x4A, 0);
    font_queue_vu_state();
    for (i = 0; i < 196; i++) {
        FastVecScale(&point, &D_L00_00290E00[i], state->ribbonScale);
        transform_vector(&point, &point, basis);
        D_L00_00239020[i].x = point.x;
        D_L00_00239020[i].y = point.y;
        D_L00_00239020[i].z = point.z;
        D_L00_00291A40[i][1] -= 0.025f;
        if (D_L00_00291A40[i][1] < -7.0f)
            D_L00_00291A40[i][1] += 7.0f;
    }
    part_draw_glint_effect(148, D_L00_00239020, D_L00_00292060, D_L00_00291A40, 1);
    part_draw_glint_effect(50, D_L00_00239020 + 146, D_L00_00292060 + 146, D_L00_00291A40 + 146, 1);
}
