#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef struct { u8 pad[0x70]; long f70, f78, f80, f88; } QuadPacket;
typedef struct { float vertex[4][4]; unsigned int color[4]; float uv[4][2]; long registers[4]; } EffectQuad;
extern float D_L00_001B8DC0[4];
extern short D_001A6480[];
extern float D_L00_001AF694 __attribute__((sda));
extern float D_L00_001AF698 __attribute__((sda));
extern float D_L00_001AF69C __attribute__((sda));
extern float D_L00_001AF6A0 __attribute__((sda));
extern float D_L00_001AF6A4 __attribute__((sda));
extern float D_L00_001AF6A8 __attribute__((sda));
extern float D_L00_001AF6AC __attribute__((sda));
extern float D_L00_001AF6B0 __attribute__((sda));
extern float D_L00_001AF6B8 __attribute__((sda));
extern void func_002AFFD8(char *, char *, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283CE0(int);
extern void func_00281DE8(QuadPacket *, int, int, int);
extern int func_00283CF0(float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00280B90(void *, int, int);
extern float func_00283B98(float, float);
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_0027DE50(int, int, int, int, int);

/* Draw the beam's ring, crossing core planes and terminal flash. */
void func_L00_003A6538(char *moby)
{
    EffectQuad quad;
    float position[4], normal[4], view[4], radius[4], center[4], rotation[4];
    float spoke[4], side[4], up[4], horizontal[4], vertical[4], corner[4], temporary[4];
    char *state = *(char **)(moby + 0x68);
    float alpha, scale;
    unsigned int color;
    int i;
    qcopy(position, state + 0x10);
    func_002AFFD8((char *)position, (char *)normal, 1);
    func_00282CF0(view, D_L00_001B8DC0, position);
    func_00282F20(view, view, 1.0f);
    if (*(short *)(state + 8)) {
        float ringAlpha = func_00283CE0(*(short *)(state + 8)) * *(float *)(state + 0x20);
        func_00281DE8((QuadPacket *)&quad, 11, 1, 0x80);
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = (func_00283CF0(ringAlpha * 255.0f) << 24) | 0x2040FF;
        quad.uv[0][0] = 0.5f; quad.uv[0][1] = 0.0f;
        quad.uv[1][0] = 0.5f; quad.uv[1][1] = 1.0f;
        quad.uv[2][0] = 1.0f; quad.uv[2][1] = 0.0f;
        quad.uv[3][0] = 1.0f; quad.uv[3][1] = 1.0f;
        func_00282D30(radius, normal, D_L00_001AF694);
        func_00282CC0(center, position, radius);
        func_002AB668(rotation, view, *(float *)(state + 0xC));
        func_002ACDE8(radius, radius, rotation);
        for (i = 0; i < 8; i++) {
            func_00282DD8(spoke, view, radius);
            func_00282F20(spoke, spoke, D_L00_001AF698);
            func_00282CC0(quad.vertex[0], position, spoke);
            func_00282CF0(quad.vertex[1], position, spoke);
            func_00282D30(spoke, spoke, D_L00_001AF69C / D_L00_001AF698);
            func_00282CC0(side, position, radius);
            func_00282CC0(quad.vertex[2], side, spoke);
            func_00282CF0(quad.vertex[3], side, spoke);
            func_00280B90(&quad, 0, 0);
            if (i < 7) {
                func_002AB668(rotation, view, 0.7853981853f);
                func_002ACDE8(radius, radius, rotation);
            }
        }
    }
    alpha = func_00283CE0(*(short *)(state + 10)) * *(float *)(state + 0x24);
    {
        float first = func_00283B98(*(float *)(state + 0x28), D_L00_001AF6A8 * 0.017453294f);
        float secondStep = D_L00_001AF6AC * 0.017453294f;
        *(float *)(state + 0x28) = first;
        *(float *)(state + 0x2C) = func_00283B98(*(float *)(state + 0x2C), secondStep);
    }
    func_00281DE8((QuadPacket *)&quad, 0x38, 1, 0x80);
    quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = (func_00283CF0(alpha * 20.0f) << 24) | 0x8080FF;
    quad.uv[0][0] = 0.0f; quad.uv[0][1] = 0.0f;
    quad.uv[1][0] = 0.0f; quad.uv[1][1] = 1.0f;
    quad.uv[2][0] = 1.0f; quad.uv[2][1] = 0.0f;
    quad.uv[3][0] = 1.0f; quad.uv[3][1] = 1.0f;
    func_00282D30(radius, state + 0x30, alpha * -16.0f + 16.0f);
    func_00282CC0(center, position, radius);
    func_00282CF0(rotation, D_L00_001B8DC0, center);
    func_00282F20(rotation, rotation, 1.0f);
    func_002AB668(spoke, rotation, *(float *)(state + 0x28));
    func_00282DD8(side, rotation, normal);
    func_00282DD8(up, side, rotation);
    func_002ACDE8(horizontal, up, spoke);
    scale = D_L00_001AF6A4 + (D_L00_001AF6A0 - D_L00_001AF6A4) * alpha;
    func_00282F20(horizontal, horizontal, scale);
    func_00282DD8(vertical, rotation, horizontal);
    func_00282F20(vertical, vertical, scale);
    func_00282CC0(corner, center, horizontal);
    func_00282CC0(quad.vertex[0], corner, vertical);
    func_00282CF0(quad.vertex[1], corner, vertical);
    func_00282CF0(corner, center, horizontal);
    func_00282CC0(quad.vertex[2], corner, vertical);
    func_00282CF0(quad.vertex[3], corner, vertical);
    func_00280B90(&quad, 0, 0);
    func_002AB668(spoke, rotation, *(float *)(state + 0x2C));
    func_002ACDE8(horizontal, up, spoke);
    func_00282D30(horizontal, horizontal, scale);
    func_00282DD8(vertical, rotation, horizontal);
    func_00282F20(vertical, vertical, scale);
    func_00282CC0(corner, center, horizontal);
    func_00282CC0(quad.vertex[0], corner, vertical);
    func_00282CF0(quad.vertex[1], corner, vertical);
    func_00282CF0(corner, center, horizontal);
    func_00282CC0(quad.vertex[2], corner, vertical);
    func_00282CF0(quad.vertex[3], corner, vertical);
    func_00280B90(&quad, 0, 0);
    if (*(int *)(state + 0x40)) {
        alpha = func_00283CE0(*(int *)(state + 0x40)) * *(float *)(state + 0x44);
        func_00281DE8((QuadPacket *)&quad, 11, 4, 0x80);
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = (func_00283CF0(alpha * 255.0f) << 24) | 0x808080;
        func_00282D30(temporary, view, -0.1f);
        func_00282CC0(center, D_L00_001B8DC0, temporary);
        func_00282DD8(vertical, view, normal);
        func_00282F20(vertical, vertical, D_L00_001AF6B0);
        func_00282DD8(horizontal, vertical, view);
        func_00282F20(horizontal, horizontal, D_L00_001AF6B0);
        func_00282CC0(corner, center, horizontal);
        func_00282CC0(quad.vertex[0], corner, vertical);
        func_00282CF0(quad.vertex[1], corner, vertical);
        func_00282CF0(corner, center, horizontal);
        func_00282CC0(quad.vertex[2], corner, vertical);
        func_00282CF0(quad.vertex[3], corner, vertical);
        func_00280B90(&quad, 0, 0);
        quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = (func_00283CF0(D_L00_001AF6B8 * alpha) << 24) | 0x808080;
        func_002FC560(0x42, 0x48ULL);
        func_0027DE50(0, D_001A6480[0xA9], 0, D_001A6480[0xA8], quad.color[0]);
    }
}
