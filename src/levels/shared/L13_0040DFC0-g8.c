#include "common.h"

extern unsigned int ref_L13_0040DFC0_01 __attribute__((sda));
extern unsigned int ref_L13_0040DFC0_02 __attribute__((sda));
extern float D_L13_001B12FC __attribute__((sda));
extern unsigned int D_L13_001B1318 __attribute__((sda));
extern unsigned int D_L13_001B131C __attribute__((sda));
extern unsigned int D_L13_001B1320 __attribute__((sda));
extern unsigned int D_L13_001B1324 __attribute__((sda));
extern unsigned int D_L13_001B1328 __attribute__((sda));
extern unsigned int D_L13_001B132C __attribute__((sda));
extern unsigned int D_L13_001B1330 __attribute__((sda));
extern unsigned int D_L13_001B1334 __attribute__((sda));
extern unsigned int D_L13_001B1338 __attribute__((sda));
extern unsigned int D_L13_001B133C __attribute__((sda));
extern unsigned int D_L13_001B1340 __attribute__((sda));
extern unsigned int D_L13_001B1344 __attribute__((sda));
extern unsigned int D_L13_001B1348 __attribute__((sda));
extern unsigned int D_L13_001B134C __attribute__((sda));
extern unsigned int D_L13_001B1350 __attribute__((sda));
extern unsigned int D_L13_001B1354 __attribute__((sda));
extern float D_L13_001B12DC __attribute__((sda));
extern float D_L13_001B12D0 __attribute__((sda));
extern float D_L13_001B12D8 __attribute__((sda));
extern int D_L13_001B12E0 __attribute__((sda));
extern int D_L13_001B12E8 __attribute__((sda));
extern float D_L13_001B12E4 __attribute__((sda));
extern float D_L13_001B98C0[];
extern void ref_L13_0040DFC0_00(void *);
extern void func_00281DE8(void *, int, int, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00280B90(void *, int, int);
extern float func_002A7940(void);
extern void func_00281EB8(void *, int, int, int, float, float, float);

/* Draws layered beam quads with scrolling texture coordinates and an end glow. */
void func_L13_0040DFC0(u8 *unused, int ua, float uf, int ub, int uc,
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

    ref_L13_0040DFC0_00(&packet);
    func_00281DE8(&packet, ref_L13_0040DFC0_01, 0, 128);
    {
        unsigned alpha = (D_L13_001B1324 << 24);
        unsigned alphaBlue = alpha | (D_L13_001B1320 << 16);
        unsigned alphaBlueGreen = alphaBlue | (D_L13_001B131C << 8);
        unsigned rgba = alphaBlueGreen | D_L13_001B1318;
        packet.color[0] = packet.color[1] = rgba;
    }
    {
        unsigned alpha = (D_L13_001B1334 << 24);
        unsigned alphaBlue = alpha | (D_L13_001B1330 << 16);
        unsigned alphaBlueGreen = alphaBlue | (D_L13_001B132C << 8);
        unsigned rgba = alphaBlueGreen | D_L13_001B1328;
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

    func_00282F20(nearPoint, state, -0.17f);
    position = (float *)(object + 0x10);
    func_00282CC0(nearPoint, position, nearPoint);
    func_00282CF0(viewDelta, position, D_L13_001B98C0);
    func_00282F20(beamStep, state, -D_L13_001B12FC);
    func_00282CC0(farPoint, nearPoint, beamStep);
    func_00282DD8(side, viewDelta, beamStep);
    func_00282F20(side, side, D_L13_001B12DC);
    func_00282CC0(packet.v[0], position, side);
    func_00282CF0(packet.v[1], position, side);
    func_00282CC0(packet.v[2], farPoint, side);
    func_00282CF0(packet.v[3], farPoint, side);
    func_00280B90(&packet, 0, 0);
    packet.color[0] = packet.color[2];
    packet.color[1] = packet.color[3];
    packet.color[2] = packet.color[3] = 0x801010;
    qcopy(packet.v[0], packet.v[2]);
    qcopy(packet.v[1], packet.v[3]);
    func_00282CC0(packet.v[2], packet.v[2], beamStep);
    func_00282CC0(packet.v[3], packet.v[3], beamStep);
    func_00280B90(&packet, 0, 0);
    func_00281DE8(&packet, ref_L13_0040DFC0_02, 1, 128);
    {
        unsigned alpha = (D_L13_001B1344 << 24);
        unsigned alphaBlue = alpha | (D_L13_001B1340 << 16);
        unsigned alphaBlueGreen = alphaBlue | (D_L13_001B133C << 8);
        unsigned rgba = alphaBlueGreen | D_L13_001B1338;
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
        unsigned blue = (D_L13_001B1340 << 16);
        unsigned blueGreen = blue | (D_L13_001B133C << 8);
        unsigned rgb = blueGreen | D_L13_001B1338;
        packet.color[3] = rgb;
        packet.color[2] = packet.color[3];
    }
    func_00282F20(side, side, D_L13_001B12D8);
    func_00282CC0(packet.v[0], position, side);
    func_00282CF0(packet.v[1], position, side);
    func_00282CC0(farPoint, position, beamStep);
    func_00282CC0(farPoint, farPoint, beamStep);
    func_00282CC0(packet.v[2], farPoint, side);
    func_00282CF0(packet.v[3], farPoint, side);
    func_00280B90(&packet, 0, 0);
    {
        unsigned alpha = (D_L13_001B1344 << 24);
        unsigned alphaBlue = alpha | (D_L13_001B1340 << 16);
        unsigned alphaBlueGreen = alphaBlue | (D_L13_001B133C << 8);
        unsigned rgba = alphaBlueGreen | D_L13_001B1338;
        packet.color[0] = packet.color[1] = rgba;
    }
    {
        unsigned blue = (D_L13_001B1340 << 16);
        unsigned blueGreen = blue | (D_L13_001B133C << 8);
        unsigned rgb = blueGreen | D_L13_001B1338;
        packet.color[2] = packet.color[3] = rgb;
    }
    func_00282F20(side, side, D_L13_001B12D0);
    func_00282F20(nearPoint, state, -0.1f);
    func_00282CC0(nearPoint, position, nearPoint);
    func_00282CC0(packet.v[0], nearPoint, side);
    func_00282CF0(packet.v[1], nearPoint, side);
    func_00282CC0(farPoint, nearPoint, beamStep);
    func_00282CC0(farPoint, farPoint, beamStep);
    func_00282CC0(packet.v[2], farPoint, side);
    func_00282CF0(packet.v[3], farPoint, side);
    func_00280B90(&packet, 0, 0);
    {
        unsigned alpha = (D_L13_001B1354 << 24);
        unsigned alphaBlue = alpha | (D_L13_001B1350 << 16);
        unsigned alphaBlueGreen = alphaBlue | (D_L13_001B134C << 8);
        unsigned rgba = alphaBlueGreen | D_L13_001B1338;
        packet.color[0] = packet.color[1] = rgba;
    }
    {
        unsigned blue = (D_L13_001B1350 << 16);
        unsigned blueGreen = blue | (D_L13_001B134C << 8);
        unsigned rgb = blueGreen | D_L13_001B1348;
        packet.color[2] = packet.color[3] = rgb;
    }
    func_00282F20(side, side, D_L13_001B12D0);
    func_00282F20(nearPoint, state, -0.1f);
    func_00282CC0(nearPoint, position, nearPoint);
    func_00282CC0(packet.v[0], nearPoint, side);
    func_00282CF0(packet.v[1], nearPoint, side);
    func_00282CC0(farPoint, nearPoint, beamStep);
    func_00282CC0(farPoint, farPoint, beamStep);
    func_00282CC0(packet.v[2], farPoint, side);
    func_00282CF0(packet.v[3], farPoint, side);
    func_00280B90(&packet, 0, 0);
    packet.color[0] = packet.color[1] = 0x40FFFFFF;
    {
        unsigned blue = (D_L13_001B1340 << 16);
        unsigned blueGreen = blue | (D_L13_001B133C << 8);
        unsigned rgb = blueGreen | D_L13_001B1338;
        packet.color[2] = packet.color[3] = rgb;
    }
    func_00282F20(side, side, D_L13_001B12D8);
    func_00282CC0(packet.v[0], position, side);
    func_00282CF0(packet.v[1], position, side);
    func_00282F20(beamStep, state, -0.6f);
    func_00282CC0(farPoint, position, beamStep);
    func_00282CC0(farPoint, farPoint, beamStep);
    func_00282CC0(packet.v[2], farPoint, side);
    func_00282CF0(packet.v[3], farPoint, side);
    func_00280B90(&packet, 0, 0);
    random = func_002A7940();
    func_00281EB8(position, D_L13_001B12E0, D_L13_001B12E8, 1, D_L13_001B12E4, 0.08f, random);
}
