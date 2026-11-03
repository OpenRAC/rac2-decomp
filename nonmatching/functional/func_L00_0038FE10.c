/* functional: high. From the 1600-byte near miss (loop scheduling and spill slots differ); read against retail end to end. qcopy asm is plain struct copies, the zeroing por/sq of `up` is four field stores, and the UV table is read through one name. */
/*
 * func_L00_0038FE10 (1600 bytes): draws the joint-aligned beam of the moby in
 * D_0018B130 (class 0x260 or 0x96C): builds a basis between two of its joints
 * (D_L00_001AF0D0 / D_L00_001AF0D8 pairs), writes it to the object's matrix
 * and position, draws the two jittered quads (D_L00_001AF030 / D_L00_001AF070
 * corners, D_L00_001AF0B0 UVs), a camera-facing glow quad, then scrolls and
 * draws the 196-point ribbon (D_L00_00290E00 -> D_L00_00239020, V phase in
 * D_L00_00291A40) with func_00281810.
 */
#include "common.h"
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vector;
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_002A7878(float, float);
extern Vector D_L00_001B8DC0;
/* The draw packet has four positions, four packed colors and four UV pairs. */
typedef unsigned long PacketWord;
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
extern BeamChild *D_0018B130;
extern JointPair D_L00_001AF0D0[], D_L00_001AF0D8[];
extern float D_L00_001AF030[4][4];
extern float D_L00_001AF070[4][4];
extern BeamUV D_L00_001AF0B0[4];
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
/* host_functions: declared as port/game/rac2-ntsc/host/render.c defines it (game addresses as int). */
extern void func_00280B90(int, int, int);
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
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    up.w = 0.0f;
    func_00282CF0(&basis[2], &joints[0], &joints[1]);
    func_00282F20(&basis[2], &basis[2], 1.0f);
    basis[2].w = 0.0f;
    func_00282DD8(&basis[0], &up, &basis[2]);
    func_00282F20(&basis[0], &basis[0], 1.0f);
    basis[0].w = 0.0f;
    func_00282DD8(&basis[1], &basis[2], &basis[0]);
    basis[1].w = 0.0f;
    basis[3] = joints[1];
    basis[3].w = 1.0f;
    object->rotation[0] = basis[0];
    object->rotation[1] = basis[1];
    object->rotation[2] = basis[2];
    object->position = basis[3];
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
        packet.uv[i].u = D_L00_001AF0B0[i].u;
        packet.uv[i].v = D_L00_001AF0B0[i].v;
    }
    func_00280B90((int)&packet, (int)matrix, 0);
    for (i = 0; i < 4; i++) {
        if (i == 0 || i == 2)
            func_00282D30(packet.position[i], D_L00_001AF070[i], state->quadScale);
        else {
            float *v = packet.position[i];
            func_00282D30(v, D_L00_001AF070[i], state->quadScale);
            v[2] -= func_002A7878(0.0f, 0.1f);
        }
    }
    func_00280B90((int)&packet, (int)matrix, 0);
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
    func_00280B90((int)&packet, 0, 0);
    func_002FC560(6, func_0027C878(10));
    func_002FC560(0x42, packet.blend);
    func_002FC560(8, 0);
    func_002FC560(0x14, 0xFF9000000260ULL);
    func_002FC560(0x4A, 0);
    func_00280328();
    {
        int index = 0;
        for (i = 195; i >= 0; i--, index++) {
            BeamPoint *dest = &D_L00_00239020[index];
            float phase;
            func_00282D30(&point, &D_L00_00290E00[index], state->ribbonScale);
            func_002830C0(&point, &point, basis);
            phase = D_L00_00291A40[index][1] - 0.025f;
            dest->x = point.x;
            dest->y = point.y;
            dest->z = point.z;
            D_L00_00291A40[index][1] = phase;
            if (phase < -7.0f)
                D_L00_00291A40[index][1] = phase + 7.0f;
        }
    }
    func_00281810(148, D_L00_00239020, D_L00_00292060, D_L00_00291A40, 1);
    func_00281810(50, D_L00_00239020 + 146, D_L00_00292060 + 146, D_L00_00291A40 + 146, 1);
}
