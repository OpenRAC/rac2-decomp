#include "include_asm.h"
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct { float vertex[4][4]; unsigned int color[4]; float uv[4][2]; unsigned long long state[4]; } Packet __attribute__((aligned(16)));
extern int D_L02_001B30C8;
extern char *D_L02_001B359C;
extern unsigned short *D_L02_001FC060[];
extern int D_L02_001B0A68[] __attribute__((sda)), D_L02_001B0A98[] __attribute__((sda));
extern int D_L02_001B0A68_gp SDATA(D_L02_001B0A68), D_L02_001B0A98_gp SDATA(D_L02_001B0A98);
extern float D_L02_001B0A78[][2] SDATA(D_L02_001B0A78);
extern float D_L02_001B0AB0[][4] MACRO_ADDR;
extern float D_L02_001B0AB0_gp[][4] SDATA(D_L02_001B0AB0);
extern float D_L02_001B0AF0_gp[][4] SDATA(D_L02_001B0AF0);
extern int D_L02_001B0B30 __attribute__((sda));
extern unsigned int D_L02_001B0B38[] SDATA(D_L02_001B0B38);
extern float D_L02_001B0B40 __attribute__((sda));
extern float D_L02_001B0B48[][2] MACRO_ADDR;
extern float D_L02_001B0B48_gp[][2] SDATA(D_L02_001B0B48);
extern char D_L02_001BA500[];
extern float func_00283CE0(int);
extern void func_00283410(void *, void *), func_0029FC20(void *, int, void *), func_002830C0(void *, void *, void *);
extern int func_00283DB8(void *, float);
extern void func_00283788(void *, void *, void *);
extern void func_L02_002EF968(void *, int, int, void *, void *, int);
extern void func_00282C88(void *), func_002833F0(void *, void *), func_00283098(void *, void *, void *);
extern void func_00283738(void *, void *, void *), func_00280B90(void *, void *, int);
extern unsigned long long func_0027C878(int);
extern void func_00283388(void *), func_00282CF0(void *, void *, void *), func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float), func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float), func_002A7940(void);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern void func_00281EB8(void *, int, unsigned int, int, float, float, float);

/* Draws the actor's object group as rotating quads, then a mirrored quad and three effects per
 * visible object. Each bound of the first vertex loop is built in two steps beside its test:
 * loop.c moves such a pair out of the loop after the copy of offsetAddress, while a single load
 * would stay ahead of that copy. */
void func_L02_003E80F8(char *actor) {
    float matrices[32][16] __attribute__((aligned(16)));
    float rotation[16] __attribute__((aligned(16)));
    unsigned int visible[32];
    float tilt[12] __attribute__((aligned(16)));
    float probe[4] __attribute__((aligned(16)));
    Packet packet[2];
    float angles[4] __attribute__((aligned(16))), point[4] __attribute__((aligned(16)));
    float doubled[12] __attribute__((aligned(16))), identity[16] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16))), offset[4] __attribute__((aligned(16)));
    unsigned short *entry;
    unsigned short id;
    float frame;
    int count = 0, i = 0, layer, pass, nextLayer, nextPass;
    int uvIndex;
    int draw;
    float *offsetAddress;
    unsigned int color;
    *(Quad *)probe = 0;
    probe[0] = 30.0f;
    probe[3] = 1.0f;
    *(Quad *)point = 0;
    frame = IntToFloat(gFrameCounter_L02 % 600);
    point[0] = (frame * 0.0016666667f + frame * 0.0016666667f) * 3.1415927f - 3.1415927f;
    *(Quad *)angles = *(Quad *)point;
    euler_to_matrix(rotation, angles);
    entry = gEntityGroupLists[*(unsigned char *)(actor + 0x21)];
    while (count < 32) {
        char *object;
        id = *entry;
        object = gMobyPool_L02 + (id & 0x7FFF) * 0x100;
        visible[count] = (*(unsigned short *)(object + 0x7C) >> 15) ^ 1;
        TransformMobyJointPoint(object, 0, matrices[count]);
        transform_vector(point, probe, matrices[count]);
        point[3] = 30.0f;
        if (FastMathHelperA(point, 512.0f) != -1) {
            multiply_matrix(matrices[count], matrices[count], rotation);
            count++;
        }
        if ((short)*entry++ < 0) break;
    }
    FillQuadPacket(packet, D_L02_001B0A68_gp, D_L02_001B0A98_gp, D_L02_001B0A78, D_L02_001B0AB0_gp, 1);
    FillQuadPacket(packet + 1, D_L02_001B0A68[1], D_L02_001B0A98[2], D_L02_001B0A78, D_L02_001B0AF0_gp, 1);
    packet[0].color[1] = packet[0].color[3] = D_L02_001B0A98[1];
    packet[1].color[1] = packet[1].color[3] = D_L02_001B0A98[3];
    ClearVector128(angles);
    angles[0] = 0.3926991f;
    euler_rotation_basis(tilt, angles);
    for (i = 0; i < 2; i++) {
        matrix_mul_vec3(packet[i].vertex[2], packet[i].vertex[2], tilt);
        matrix_mul_vec3(packet[i].vertex[3], packet[i].vertex[3], tilt);
    }
    multiply_matrix3x3(doubled, tilt, tilt);
    for (pass = 0; pass < 16; pass = nextPass) {
        int pair = (pass & 1) ? 2 : 0;
        nextPass = pass + 1;
        for (layer = 0; layer < 1; layer = nextLayer) {
            nextLayer = layer + 1;
            matrix_mul_vec3(packet[layer].vertex[pair], packet[layer].vertex[pair], doubled);
            matrix_mul_vec3(packet[layer].vertex[pair + 1], packet[layer].vertex[pair + 1], doubled);
            for (draw = 0; draw < count; draw++) {
                if (visible[draw]) draw_world_quad(packet + layer, matrices[draw], 1);
            }
        }
    }
    packet[0].state[1] = GetEffectTextureDescriptor(D_L02_001B0B30);
    for (uvIndex = 0; uvIndex < 4; uvIndex++) {
        packet[0].uv[uvIndex][0] = D_L02_001B0B48_gp[uvIndex][0];
        packet[0].uv[uvIndex][1] = D_L02_001B0B48[uvIndex][1];
        packet[0].color[uvIndex] = D_L02_001B0B38[uvIndex & 1];
    }
    set_identity_matrix(identity);
    {
    int objectIndex;
    for (objectIndex = 0; objectIndex < count; objectIndex++) {
        int vertex;
        float *geometry;
        if (!visible[objectIndex]) continue;
        FastVecSub(point, gCameraPosition_L02, matrices[objectIndex] + 12);
        FastVecCross(normal, matrices[objectIndex], point);
        normal[3] = 1.0f;
        qcopy(identity + 12, matrices[objectIndex] + 12);
        geometry = (float *)D_L02_001B0AB0_gp;
        {
            float *g = geometry;
            float (*v)[4] = packet[0].vertex;
            float (*lowerEnd)[4], (*allEnd)[4];
            do {
                float extent = g[2];
                offsetAddress = offset;
                lowerEnd = D_L02_001B0AB0;
                lowerEnd += 2;
                if ((int)g < (int)lowerEnd) extent += D_L02_001B0B40;
                else extent -= D_L02_001B0B40;
                vec_scale_to_length(*v, normal, extent);
                vec_scale_to_length(offset, matrices[objectIndex], g[0]);
                g += 4;
                FastVecAdd(*v, *v, offset);
                v++;
                allEnd = D_L02_001B0AB0;
                allEnd += 4;
            } while ((int)g < (int)allEnd);
        }
        draw_world_quad(packet, identity, 0);
        for (vertex = 0; vertex < 4; vertex++) {
            float extent = geometry[vertex * 4 + 2];
            if (vertex < 2) extent += D_L02_001B0B40;
            else extent -= D_L02_001B0B40;
            vec_scale_to_length(offset, normal, extent * -2.0f);
            FastVecAdd(packet[0].vertex[vertex], packet[0].vertex[vertex], offset);
        }
        draw_world_quad(packet, identity, 0);
        *(Quad *)offset = 0;
        offset[0] = 2.666f;
        offset[3] = 1.0f;
        transform_vector(offset, offsetAddress, matrices[objectIndex]);
        frame = RandomFloatRange(0.0f, 1.0f);
        color = FastTweenColor(D_L02_001B0A98_gp, D_L02_001B0A98[1], frame);
        frame = RandomAngle();
        DrawBillboardQuad_00281EB8(offset, 11, color, 1, 2.0f, 0.0f, frame);
        frame = RandomFloatRange(0.0f, 1.0f);
        color = FastTweenColor(D_L02_001B0A98[2], D_L02_001B0A98[3], frame);
        frame = RandomAngle();
        DrawBillboardQuad_00281EB8(offset, 11, color, 1, 2.75f, 0.0f, frame);
        frame = RandomAngle();
        DrawBillboardQuad_00281EB8(offset, 49, color, 1, 2.75f, 0.0f, frame);
    }
    }
}
