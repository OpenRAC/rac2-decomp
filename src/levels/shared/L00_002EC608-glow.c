/* Draws a camera-facing glow quad three times at a position with the tint. */
#include "common.h"

typedef struct {
    float point[4][4];
    u32 color[4];
    float uv[4][2];
    u64 state[4];
} GlowQuad;
typedef struct { float basis[3][4], position[4]; } GlowTransform;
typedef struct { char pad[0x140]; float position[4]; } GlowCamera;
extern GlowCamera D_L00_001B8C80[];
extern void func_00281DE8(void *, int, int, int);
extern int func_002A7820(int, int);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern float func_002A7940(void);
extern void func_00283410(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_002A7878(float, float);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);

void func_L00_002EC608(float *position, int tint)
{
    GlowQuad quad;
    GlowTransform transform;
    float rotation[4];
    float offset[4];
    u32 color, white;
    float scale;
    float dx, dy;

    quad.point[0][2] = -2.0f;
    quad.point[1][2] = 2.0f;
    quad.point[2][2] = -2.0f;
    quad.point[3][2] = 2.0f;
    quad.point[0][1] = -2.0f;
    quad.point[2][1] = 2.0f;
    quad.point[1][1] = -2.0f;
    quad.point[3][1] = 2.0f;
    quad.point[0][3] = 1.0f;
    quad.point[1][3] = 1.0f;
    quad.point[2][3] = 1.0f;
    quad.point[3][3] = 1.0f;
    quad.point[0][0] = 0;
    quad.point[1][0] = 0;
    quad.point[2][0] = 0;
    quad.point[3][0] = 0;
    func_00281DE8(&quad, 44, 1, 128);
    color = (u32)func_002A7820(48, 64) << 24;
    dx = D_L00_001B8C80[0].position[0] - position[0];
    dy = D_L00_001B8C80[0].position[1] - position[1];
    quad.uv[0][0] = 0;
    quad.uv[0][1] = 0;
    color |= (u32)(tint >> 17) << 16;
    color |= (tint >> 9) & 0xFF00;
    color |= (tint >> 1) & 0xFF;
    quad.uv[1][1] = 1;
    quad.uv[2][0] = 1;
    quad.uv[3][0] = 1;
    quad.uv[3][1] = 1;
    quad.color[3] = color;
    quad.color[2] = color;
    quad.color[1] = color;
    quad.color[0] = color;
    quad.uv[1][0] = 0;
    quad.uv[2][1] = 0;
    rotation[3] = 0;
    rotation[2] = func_00283248(dx, dy);
    rotation[1] = -func_00283248(func_00282E80(position, D_L00_001B8C80[0].position),
                                D_L00_001B8C80[0].position[2] - position[2]);
    rotation[0] = func_002A7940();
    func_00283410(&transform, rotation);
    func_00282CF0(offset, D_L00_001B8C80[0].position, position);
    func_00282F20(offset, offset, 0.25f);
    transform.position[0] = position[0] + offset[0];
    transform.position[1] = position[1] + offset[1];
    transform.position[2] = position[2] + offset[2];
    transform.position[3] = 1.0f;
    scale = func_002A7878(0.3f, 0.4f);
    func_00282D30(quad.point[0], quad.point[0], scale);
    func_00282D30(quad.point[1], quad.point[1], scale);
    func_00282D30(quad.point[2], quad.point[2], scale);
    func_00282D30(quad.point[3], quad.point[3], scale);
    func_00280B90(&quad, &transform, 0);
    func_00282D30(quad.point[0], quad.point[0], 0.5f);
    func_00282D30(quad.point[1], quad.point[1], 0.5f);
    func_00282D30(quad.point[2], quad.point[2], 0.5f);
    func_00282D30(quad.point[3], quad.point[3], 0.5f);
    tint += (u32)func_002A7820(64, 127) << 24;
    color = tint;
    quad.color[3] = color; quad.color[2] = color;
    quad.color[1] = color; quad.color[0] = color;
    func_00280B90(&quad, &transform, 0);
    func_00282D30(quad.point[0], quad.point[0], 0.5f);
    func_00282D30(quad.point[1], quad.point[1], 0.5f);
    func_00282D30(quad.point[2], quad.point[2], 0.5f);
    func_00282D30(quad.point[3], quad.point[3], 0.5f);
    white = ((u32)func_002A7820(64, 127) << 24) + 0x7F7F7F;
    quad.color[3] = white; quad.color[2] = white;
    quad.color[1] = white; quad.color[0] = white;
    func_00280B90(&quad, &transform, 0);
}
