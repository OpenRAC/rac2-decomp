#include "common.h"

extern unsigned int D_L16_001B0C9C __attribute__((sda));
extern unsigned int D_L16_001B0CA0 __attribute__((sda));
extern unsigned int D_L16_001B0C98 __attribute__((sda));
extern unsigned int D_L16_001B0CB0 __attribute__((sda));
extern unsigned int D_L16_001B0CB4 __attribute__((sda));
extern unsigned int D_L16_001B0CB8 __attribute__((sda));
extern unsigned int D_L16_001B0CBC __attribute__((sda));
extern unsigned int D_L16_001B0CC0 __attribute__((sda));
extern unsigned int D_L16_001B0CC4 __attribute__((sda));
extern unsigned int D_L16_001B0CC8 __attribute__((sda));
extern unsigned int D_L16_001B0CCC __attribute__((sda));
extern unsigned int D_L16_001B0CD0 __attribute__((sda));
extern unsigned int D_L16_001B0CD4 __attribute__((sda));
extern unsigned int D_L16_001B0CD8 __attribute__((sda));
extern unsigned int D_L16_001B0CDC __attribute__((sda));
extern unsigned int D_L16_001B0CE0 __attribute__((sda));
extern unsigned int D_L16_001B0CE4 __attribute__((sda));
extern unsigned int D_L16_001B0CE8 __attribute__((sda));
extern unsigned int D_L16_001B0CEC __attribute__((sda));
extern unsigned int D_L16_001B0CF0 __attribute__((sda));
extern float D_L16_001B0C88 __attribute__((sda));
extern float D_L16_001B0C7C __attribute__((sda));
extern float D_L16_001B0C80 __attribute__((sda));
extern float D_L16_001B0C8C __attribute__((sda));
extern float D_L16_001B9B00[];
extern void func_L00_003F1DC8(void *);
extern void func_00281DE8(void *, int, int, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00280B90(void *, int, int);
extern float func_002A7940(void);
extern void func_00281EB8(void *, int, int, int, float, float, float);

/* Draws layered beam quads with scrolling texture coordinates and an end glow. */
/* Draws a glowing beam with scrolling layers towards the camera. */
void func_L16_003E7248(u8 *unused, int ua, float uf, int ub, int uc,
                       float ug, float uh, int ud, u8 *object) {
    struct {
        float v[4][4];
        unsigned color[4];
        float uv[8];
        char pad[32];
    } packet __attribute__((aligned(16)));
    float nearPoint[4], viewDelta[4], beamStep[4], farPoint[4], side[4];
    float *position;
    float *state = *(float **)(object + 0x68);
    int i;
    float *uv;
    float random;

    InitQuadPacketBlockCopy(&packet);
    InitQuadPacketState(&packet, D_L16_001B0C9C, 0, 128);
    /* Separate packing stages preserve the left-associated color operations. */
    {
        unsigned alpha = (D_L16_001B0CC0 << 24);
        unsigned alphaBlue = alpha | (D_L16_001B0CBC << 16);
        unsigned alphaBlueGreen = alphaBlue | (D_L16_001B0CB8 << 8);
        unsigned rgba = alphaBlueGreen | D_L16_001B0CB4;
        packet.color[0] = packet.color[1] = rgba;
    }
    {
        unsigned alpha = (D_L16_001B0CD0 << 24);
        unsigned alphaBlue = alpha | (D_L16_001B0CCC << 16);
        unsigned alphaBlueGreen = alphaBlue | (D_L16_001B0CC8 << 8);
        unsigned rgba = alphaBlueGreen | D_L16_001B0CC4;
        packet.color[2] = packet.color[3] = rgba;
    }
    packet.uv[0] = 0;
    packet.uv[1] = 0;
    packet.uv[2] = 0;
    packet.uv[3] = 1;
    packet.uv[4] = 1;
    packet.uv[5] = 0;
    packet.uv[6] = 1;
    packet.uv[7] = 1;
    for (uv = packet.uv, i = 3; i >= 0; --i, uv += 2) {
        *uv -= state[10];
        if (*uv <= 7.0f)
            *uv += 7.0f;
    }
    state[10] += 0.1f;
    if (state[10] >= 4.0f)
        state[10] -= 4.0f;

    vec_scale_to_length(nearPoint, state, -0.17f);
    position = (float *)(object + 0x10);
    FastVecAdd(nearPoint, position, nearPoint);
    FastVecSub(viewDelta, position, D_L16_001B9B00);
    vec_scale_to_length(beamStep, state, -4.0f);
    FastVecAdd(farPoint, nearPoint, beamStep);
    FastVecCross(side, viewDelta, beamStep);
    vec_scale_to_length(side, side, D_L16_001B0C88);
    FastVecAdd(packet.v[0], position, side);
    FastVecSub(packet.v[1], position, side);
    FastVecAdd(packet.v[2], farPoint, side);
    FastVecSub(packet.v[3], farPoint, side);
    draw_world_quad(&packet, 0, 0);
    packet.color[0] = packet.color[2];
    packet.color[1] = packet.color[3];
    packet.color[2] = packet.color[3] = 0x801010;
    qcopy(packet.v[0], packet.v[2]);
    qcopy(packet.v[1], packet.v[3]);
    FastVecAdd(packet.v[2], packet.v[2], beamStep);
    FastVecAdd(packet.v[3], packet.v[3], beamStep);
    draw_world_quad(&packet, 0, 0);
    InitQuadPacketState(&packet, D_L16_001B0CA0, 1, 128);
    {
        unsigned alpha = (D_L16_001B0CE0 << 24);
        unsigned alphaBlue = alpha | (D_L16_001B0CDC << 16);
        unsigned alphaBlueGreen = alphaBlue | (D_L16_001B0CD8 << 8);
        unsigned rgba = alphaBlueGreen | D_L16_001B0CD4;
        packet.color[1] = rgba;
        packet.color[0] = packet.color[1];
    }
    packet.uv[0] = 0;
    packet.uv[1] = 0;
    packet.uv[2] = 0;
    packet.uv[3] = 1;
    packet.uv[4] = 1;
    packet.uv[5] = 0;
    packet.uv[6] = 1;
    packet.uv[7] = 1;
    {
        unsigned blue = (D_L16_001B0CDC << 16);
        unsigned blueGreen = blue | (D_L16_001B0CD8 << 8);
        unsigned rgb = blueGreen | D_L16_001B0CD4;
        packet.color[3] = rgb;
        packet.color[2] = packet.color[3];
    }
    vec_scale_to_length(side, side, D_L16_001B0C7C);
    FastVecAdd(packet.v[0], position, side);
    FastVecSub(packet.v[1], position, side);
    FastVecAdd(farPoint, position, beamStep);
    FastVecAdd(farPoint, farPoint, beamStep);
    FastVecAdd(packet.v[2], farPoint, side);
    FastVecSub(packet.v[3], farPoint, side);
    draw_world_quad(&packet, 0, 0);
    {
        unsigned alpha = (D_L16_001B0CE0 << 24);
        unsigned alphaBlue = alpha | (D_L16_001B0CDC << 16);
        unsigned alphaBlueGreen = alphaBlue | (D_L16_001B0CD8 << 8);
        unsigned rgba = alphaBlueGreen | D_L16_001B0CD4;
        packet.color[0] = packet.color[1] = rgba;
    }
    {
        unsigned blue = (D_L16_001B0CDC << 16);
        unsigned blueGreen = blue | (D_L16_001B0CD8 << 8);
        unsigned rgb = blueGreen | D_L16_001B0CD4;
        packet.color[2] = packet.color[3] = rgb;
    }
    vec_scale_to_length(side, side, D_L16_001B0C80);
    vec_scale_to_length(nearPoint, state, -0.1f);
    FastVecAdd(nearPoint, position, nearPoint);
    FastVecAdd(packet.v[0], nearPoint, side);
    FastVecSub(packet.v[1], nearPoint, side);
    FastVecAdd(farPoint, nearPoint, beamStep);
    FastVecAdd(farPoint, farPoint, beamStep);
    FastVecAdd(packet.v[2], farPoint, side);
    FastVecSub(packet.v[3], farPoint, side);
    draw_world_quad(&packet, 0, 0);
    {
        unsigned alpha = (D_L16_001B0CF0 << 24);
        unsigned alphaBlue = alpha | (D_L16_001B0CEC << 16);
        unsigned alphaBlueGreen = alphaBlue | (D_L16_001B0CE8 << 8);
        unsigned rgba = alphaBlueGreen | D_L16_001B0CD4;
        packet.color[0] = packet.color[1] = rgba;
    }
    {
        unsigned blue = (D_L16_001B0CEC << 16);
        unsigned blueGreen = blue | (D_L16_001B0CE8 << 8);
        unsigned rgb = blueGreen | D_L16_001B0CE4;
        packet.color[2] = packet.color[3] = rgb;
    }
    vec_scale_to_length(side, side, D_L16_001B0C80);
    vec_scale_to_length(nearPoint, state, -0.1f);
    FastVecAdd(nearPoint, position, nearPoint);
    FastVecAdd(packet.v[0], nearPoint, side);
    FastVecSub(packet.v[1], nearPoint, side);
    FastVecAdd(farPoint, nearPoint, beamStep);
    FastVecAdd(farPoint, farPoint, beamStep);
    FastVecAdd(packet.v[2], farPoint, side);
    FastVecSub(packet.v[3], farPoint, side);
    draw_world_quad(&packet, 0, 0);
    packet.color[0] = packet.color[1] = 0x40FFFFFF;
    {
        unsigned blue = (D_L16_001B0CDC << 16);
        unsigned blueGreen = blue | (D_L16_001B0CD8 << 8);
        unsigned rgb = blueGreen | D_L16_001B0CD4;
        packet.color[2] = packet.color[3] = rgb;
    }
    vec_scale_to_length(side, side, D_L16_001B0C7C);
    FastVecAdd(packet.v[0], position, side);
    FastVecSub(packet.v[1], position, side);
    vec_scale_to_length(beamStep, state, -0.6f);
    FastVecAdd(farPoint, position, beamStep);
    FastVecAdd(farPoint, farPoint, beamStep);
    FastVecAdd(packet.v[2], farPoint, side);
    FastVecSub(packet.v[3], farPoint, side);
    draw_world_quad(&packet, 0, 0);
    random = RandomAngle();
    DrawBillboardQuad_00281EB8(position, D_L16_001B0C98, D_L16_001B0CB0, 1, D_L16_001B0C8C, 0.08f, random);
}
