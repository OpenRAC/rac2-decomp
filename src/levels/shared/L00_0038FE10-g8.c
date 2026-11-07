/* func_L00_0038FE10 draws a joint-aligned beam: three quads and a 196-point scrolling ribbon. RAC1 has the same effect
   as draw_joint_aligned_beam_effect (src/overlays/shared/visibomb_and_pyrocitor.c). D_0018B130 needs NOT_SDA, and the
   UV table is read through both its MACRO_ADDR view and an SDATA view. */
#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vector;
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_002A7878(float, float);
extern Vector D_L00_001B8DC0;
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
extern void func_0029FD48(void *, int, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00283388(void *);
extern void func_00283788(void *, void *, void *);
extern PacketWord func_0027C878(int);
extern void func_00280B90(void *, void *, int);
extern void func_002830C0(void *, void *, void *);
extern void func_002FC560(int, PacketWord);
extern void func_00280328(void);
extern void func_00281810(int, void *, void *, void *, int);

void func_L00_0038FE10(BeamObject *object)
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
        func_0029FD48(D_0018B130, 2, &jointIndices, joints);
    } else {
        jointIndices = D_L00_001AF0D8[0];
        func_0029FD48(D_0018B130, 2, &jointIndices, joints);
    }
    *(Quadword *)&up = 0;
    up.y = 1.0f;
    func_00282CF0(&basis[2], &joints[0], &joints[1]);
    func_00282F20(&basis[2], &basis[2], 1.0f);
    basis[2].w = 0.0f;
    func_00282DD8(&basis[0], &up, &basis[2]);
    func_00282F20(&basis[0], &basis[0], 1.0f);
    basis[0].w = 0.0f;
    func_00282DD8(&basis[1], &basis[2], &basis[0]);
    basis[1].w = 0.0f;
    qcopy(&basis[3], &joints[1]);
    basis[3].w = 1.0f;
    qcopy(&object->rotation[0], &basis[0]);
    qcopy(&object->rotation[1], &basis[1]);
    qcopy(&object->rotation[2], &basis[2]);
    qcopy(&object->position, &basis[3]);
    func_00283388(adjustment);
    adjustment[3].w = 1.0f;
    adjustment[3].z = -0.075f;
    adjustment[3].x = 0.0f;
    adjustment[3].y = 0.0f;
    func_00283788(matrix, basis, adjustment);
    packet.primitive = func_0027C878(12);
    for (i = 0; i < 4; i++) {
        packet.color[i] = 0x80808080;
        if (i == 0 || i == 2)
            func_00282D30(packet.position[i], D_L00_001AF030[i], state->quadScale);
        else {
            float *v = packet.position[i];
            func_00282D30(v, D_L00_001AF030[i], state->quadScale);
            v[2] -= func_002A7878(0.0f, 0.1f);
        }
        packet.uv[i].u = beamUVGP[i].u;
        packet.uv[i].v = D_L00_001AF0B0[i].v;
    }
    func_00280B90(&packet, matrix, 0);
    for (i = 0; i < 4; i++) {
        if (i == 0 || i == 2)
            func_00282D30(packet.position[i], D_L00_001AF070[i], state->quadScale);
        else {
            float *v = packet.position[i];
            func_00282D30(v, D_L00_001AF070[i], state->quadScale);
            v[2] -= func_002A7878(0.0f, 0.1f);
        }
    }
    func_00280B90(&packet, matrix, 0);
    packet.primitive = func_0027C878(11);
    func_00282D30(&frame[3], &basis[2], -0.13f);
    func_00282CC0(&frame[3], &frame[3], &basis[3]);
    func_00282CF0(&frame[0], &D_L00_001B8DC0, &frame[3]);
    func_00282F20(&frame[0], &frame[0], 1.0f);
    func_00282DD8(&frame[1], &frame[0], &D_0018A0E0);
    func_00282F20(&frame[1], &frame[1], -1.0f);
    func_00282DD8(&frame[2], &frame[1], &frame[0]);
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = 0x7F2020FF;
    {
        int corner;
        for (corner = 0; corner < 4; corner++) {
            func_00282D30(packet.position[corner], D_L00_001AF030[corner], 0.1f);
            func_002830C0(packet.position[corner], packet.position[corner], frame);
        }
    }
    func_00280B90(&packet, 0, 0);
    func_002FC560(6, func_0027C878(10));
    func_002FC560(0x42, packet.blend);
    func_002FC560(8, 0);
    func_002FC560(0x14, 0xFF9000000260ULL);
    func_002FC560(0x4A, 0);
    func_00280328();
    for (i = 0; i < 196; i++) {
        func_00282D30(&point, &D_L00_00290E00[i], state->ribbonScale);
        func_002830C0(&point, &point, basis);
        D_L00_00239020[i].x = point.x;
        D_L00_00239020[i].y = point.y;
        D_L00_00239020[i].z = point.z;
        D_L00_00291A40[i][1] -= 0.025f;
        if (D_L00_00291A40[i][1] < -7.0f)
            D_L00_00291A40[i][1] += 7.0f;
    }
    func_00281810(148, D_L00_00239020, D_L00_00292060, D_L00_00291A40, 1);
    func_00281810(50, D_L00_00239020 + 146, D_L00_00292060 + 146, D_L00_00291A40 + 146, 1);
}
