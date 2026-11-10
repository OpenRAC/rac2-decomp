#include "common.h"

/*
 * Counterpart of RAC1's draw_pokitaru_ocean (homing_missile_and_water_sheet.c): a fading edge
 * strip, a far quad, and two scrolling layers of grid cells around the camera. As in RAC1, the
 * scroll table is declared in .sdata, so its address is one `la` macro instruction rather than a
 * split %hi/%lo pair; that makes the loop optimizer hoist both per-layer scroll pointers. This
 * unit needs -g for the measured division padding (docs/build/compiler-notes.md).
 */

typedef unsigned int Quadword __attribute__((mode(TI)));
typedef union { float v[4]; Quadword q; } Vector;
typedef struct {
    int color0, color1, color2, color3, color4;
    float threshold, spacing;
    int texture;
    u32 unused;
    float altitude, depth;
} GridSettings;
typedef struct {
    Vector points[4];
    u32 colors[4];
    u32 zero[8];
    u64 state[4];
} SurfacePacket;
typedef struct { char prefix[0x2294]; int state; } WaterHero;
extern WaterHero D_00189E20;
extern int D_L01_001A8A48 __attribute__((section(".sdata")));
typedef struct { unsigned char prefix[0x228]; float scale0, scale1; } RenderScales;
extern RenderScales D_L01_001BD9C0;
extern float D_L01_001B96F0[16], D_L01_001B94C0[4];
typedef struct { char prefix[0x140]; float pos[3]; } WaterCamera;
extern WaterCamera D_L01_001B9380;
extern float D_L01_001AFE18 __attribute__((sda));
extern float D_L01_001AFDF0[2] __attribute__((sda));
typedef struct { float u, v; } WaterUV;
extern WaterUV D_L01_001B2FD0[] __attribute__((section(".sdata")));
typedef struct { float x, y, z; } WaterPos;
extern WaterPos D_L01_00240260[], D_L01_00240660[];
extern u32 D_L01_00240560[], D_L01_00240960[];
extern WaterUV D_L01_00240A60[], D_L01_00240C60[];
extern void func_002FC560(u32, u64);
extern unsigned long func_0027C878(int);
extern void func_00280328(void);
extern void func_00283098(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00283CE0(int);
extern int func_00283D38(int, int, float);
extern void func_00281810(int, void *, void *, void *, int);
extern void func_00280B90(void *, int, int);
extern float func_00282E20(void *);
extern void func_00282A28(void);
void func_L01_003BAFB8(char *object)
{
    Vector point, scratch, right, up;
    Vector corners[4], along_left, along_right;
    SurfacePacket packet;
    GridSettings *settings = *(GridSettings **)(object + 0x68);
    float saved1, saved0;
    float x, y, t, factor;
    float grid_start;
    int i, layer, count, start;
    int color, lower_color, upper_color;
    saved0 = D_L01_001BD9C0.scale0;
    saved1 = D_L01_001BD9C0.scale1;
    if (D_00189E20.state != 28 && D_L01_001A8A48 == 0) {
        D_L01_001BD9C0.scale0 = 255.0f;
        D_L01_001BD9C0.scale1 = 249.9f;
    }
    func_002FC560(0x42, 0x3200000044ULL);
    func_002FC560(8, 0);
    func_002FC560(0x14, 0xFF9000000260ULL);
    func_002FC560(0x47, 0x513F1);
    func_002FC560(6, func_0027C878(0x16));
    func_00280328();
    right.v[0] = 1.0f; right.v[1] = 0.0f;
    right.v[2] = 0.0f; right.v[3] = 1.0f;
    func_00283098(&right, &right, D_L01_001B96F0);
    up.v[0] = 0.0f; up.v[1] = 1.0f;
    up.v[2] = 0.0f; up.v[3] = 1.0f;
    func_00283098(&up, &up, D_L01_001B96F0);
    right.v[2] = 0.0f;
    func_00282F20(&right, &right, 1.0f);
    up.v[2] = 0.0f;
    func_00282F20(&up, &up, 1.0f);
    func_00282F20(&point, &right, -75.0f);
    func_00282F20(&scratch, &up, -87.0f);
    func_00282CC0(&corners[0], &point, &scratch);
    func_00282F20(&scratch, &up, 87.0f);
    func_00282CC0(&corners[2], &point, &scratch);
    func_00282F20(&point, &right, settings->depth);
    func_00282F20(&scratch, &up, -750.0f);
    func_00282CC0(&corners[1], &point, &scratch);
    func_00282F20(&scratch, &up, 750.0f);
    func_00282CC0(&corners[3], &point, &scratch);
    for (i = 0; i < 4; ++i) {
        func_00282CC0(&corners[i], &corners[i], D_L01_001B94C0);
        corners[i].v[2] = D_L01_001AFE18;
    }
    func_00282CF0(&along_left, &corners[1], &corners[0]);
    func_00282CF0(&along_right, &corners[3], &corners[2]);
    t = 10.0f;
    for (i = 0; i < 12; i += 2) {
        factor = func_00283CE0(i) * 0.1f;
        color = func_00283D38(settings->color0, settings->color1, func_00283CE0(i) / t);
        func_00282D30(&point, &along_left, factor);
        D_L01_00240560[i] = color;
        D_L01_00240A60[i].u = 0.0f;
        D_L01_00240A60[i].v = 0.0f;
        func_00282CC0(&point, &point, &corners[0]);
        D_L01_00240260[i].x = point.v[0];
        D_L01_00240260[i].y = point.v[1];
        D_L01_00240260[i].z = point.v[2];
        func_00282D30(&point, &along_right, factor);
        D_L01_00240560[i+1] = color;
        D_L01_00240A60[i+1].u = 0.0f;
        D_L01_00240A60[i+1].v = 0.0f;
        func_00282CC0(&point, &point, &corners[2]);
        D_L01_00240260[i+1].x = point.v[0];
        D_L01_00240260[i+1].y = point.v[1];
        D_L01_00240260[i+1].z = point.v[2];
    }
    func_00281810(12, D_L01_00240260, D_L01_00240560, D_L01_00240A60, 1);
    packet.state[1] = func_0027C878(0x16);
    packet.state[2] = 0xFF9000000260ULL;
    packet.state[3] = 0x8000000044ULL;
    packet.state[0] = 0;
    if (settings->threshold < D_L01_001B9380.pos[2] - settings->altitude &&
        D_00189E20.state != 28 && D_L01_001A8A48 == 0) {
        packet.zero[0] = 0;
        packet.zero[1] = 0;
        packet.zero[2] = 0;
        packet.zero[3] = 0;
        packet.zero[4] = 0;
        packet.zero[5] = 0;
        packet.zero[6] = 0;
        packet.zero[7] = 0;
        packet.colors[0] = settings->color1;
        packet.colors[1] = settings->color2;
        packet.colors[2] = packet.colors[0];
        packet.colors[3] = packet.colors[1];
        packet.points[0].q = corners[1].q;
        packet.points[1].q = corners[1].q;
        packet.points[1].v[2] = D_L01_001B9380.pos[2] - settings->altitude;
        packet.points[2].q = corners[3].q;
        packet.points[3].q = corners[3].q;
        packet.points[3].v[2] = D_L01_001B9380.pos[2] - settings->altitude;
        func_00280B90(&packet, 0, 0);
    }
    func_002FC560(0x42, 0x8000000048ULL);
    func_002FC560(8, 0);
    grid_start = -2.0f;
    func_002FC560(0x14, 0xFF9000000260ULL);
    func_002FC560(0x47, 0x513F0);
    lower_color = settings->color3;
    upper_color = settings->color4;
    t = 1.0f;
    lower_color = func_00283D38(0, lower_color, t);
    upper_color = func_00283D38(0, upper_color, t);
    for (layer = 0; layer < 2; ++layer) {
        int texture_id = layer + 0x3F;
        func_002FC560(6, func_0027C878(settings->texture + texture_id));
        for (y = settings->spacing * grid_start; y < settings->spacing * 2.0f;
             y += settings->spacing) {
            count = 0;
            for (x = settings->spacing * grid_start; x < settings->spacing * 2.0f;
                 x += settings->spacing) {
                start = count;
                D_L01_00240C60[count].u = x / (settings->spacing * 2.0f) * D_L01_001AFDF0[layer] + D_L01_001B2FD0[layer].u;
                D_L01_00240C60[count].v = y / (settings->spacing * 2.0f) * D_L01_001AFDF0[layer] + D_L01_001B2FD0[layer].v;
                D_L01_00240660[count].x = x + D_L01_001B9380.pos[0] + 1.0f;
                D_L01_00240660[count].y = y + D_L01_001B9380.pos[1] + 1.0f;
                D_L01_00240660[count].z = D_L01_001AFE18;
                i = count + 1;
                D_L01_00240C60[i].u = x / (settings->spacing * 2.0f) * D_L01_001AFDF0[layer] + D_L01_001B2FD0[layer].u;
                D_L01_00240C60[i].v = (y + settings->spacing) / (settings->spacing * 2.0f) * D_L01_001AFDF0[layer] + D_L01_001B2FD0[layer].v;
                D_L01_00240660[i].x = x + D_L01_001B9380.pos[0] + 1.0f;
                D_L01_00240660[i].y = y + settings->spacing + D_L01_001B9380.pos[1] + 1.0f;
                D_L01_00240660[i].z = D_L01_001AFE18;
                i = count + 2;
                D_L01_00240C60[i].u = (x + settings->spacing) / (settings->spacing * 2.0f) * D_L01_001AFDF0[layer] + D_L01_001B2FD0[layer].u;
                D_L01_00240C60[i].v = y / (settings->spacing * 2.0f) * D_L01_001AFDF0[layer] + D_L01_001B2FD0[layer].v;
                D_L01_00240660[i].x = x + settings->spacing + D_L01_001B9380.pos[0] + 1.0f;
                D_L01_00240660[i].y = y + D_L01_001B9380.pos[1] + 1.0f;
                D_L01_00240660[i].z = D_L01_001AFE18;
                i = count + 3;
                D_L01_00240C60[i].u = (x + settings->spacing) / (settings->spacing * 2.0f) * D_L01_001AFDF0[layer] + D_L01_001B2FD0[layer].u;
                D_L01_00240C60[i].v = (y + settings->spacing) / (settings->spacing * 2.0f) * D_L01_001AFDF0[layer] + D_L01_001B2FD0[layer].v;
                D_L01_00240660[i].x = x + settings->spacing + D_L01_001B9380.pos[0] + 1.0f;
                D_L01_00240660[i].y = y + settings->spacing + D_L01_001B9380.pos[1] + 1.0f;
                D_L01_00240660[i].z = D_L01_001AFE18;
                for (i = start; i < start + 4; ++i) {
                    point.v[0] = D_L01_00240660[i].x - D_L01_001B9380.pos[0];
                    point.v[1] = D_L01_00240660[i].y - D_L01_001B9380.pos[1];
                    point.v[2] = D_L01_00240660[i].z - D_L01_001B9380.pos[2];
                    point.v[3] = 1.0f;
                    t = func_00282E20(&point) / (settings->spacing * 2.0f);
                    if (t > 1.0f) t = 1.0f;
                    D_L01_00240960[i] = func_00283D38(lower_color, upper_color, t);
                }
                count += 4;
                if (count >= 64) func_00282A28();
            }
            func_00281810(count, D_L01_00240660, D_L01_00240960, D_L01_00240C60, 1);
        }
    }
    D_L01_001BD9C0.scale0 = saved0; D_L01_001BD9C0.scale1 = saved1;
    func_002FC560(0x47, 0x5360A);
}
