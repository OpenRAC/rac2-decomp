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
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern int math_random_int_range(int, int);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(void *, void *);
extern float math_random_angle(void);
extern void euler_to_matrix(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_random_float_range(float, float);
extern void FastVecScale(void *, void *, float);
extern void draw_world_quad(void *, void *, int);

void part_draw_glow_quad(float *position, int tint)
{
    GlowQuad quad;
    GlowTransform transform;
    float rotation[4];
    float offset[4];
    u32 color, white;
    float scale;
    float deltaX, deltaY;

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
    gfx_init_quad_packet_state(&quad, 44, 1, 128);
    color = (u32)math_random_int_range(48, 64) << 24;
    deltaX = D_L00_001B8C80[0].position[0] - position[0];
    deltaY = D_L00_001B8C80[0].position[1] - position[1];
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
    rotation[2] = mat_fast_helper_a(deltaX, deltaY);
    rotation[1] = -mat_fast_helper_a(vec_distance_xy(position, D_L00_001B8C80[0].position),
                                D_L00_001B8C80[0].position[2] - position[2]);
    rotation[0] = math_random_angle();
    euler_to_matrix(&transform, rotation);
    FastVecSub(offset, D_L00_001B8C80[0].position, position);
    vec_scale_to_length(offset, offset, 0.25f);
    transform.position[0] = position[0] + offset[0];
    transform.position[1] = position[1] + offset[1];
    transform.position[2] = position[2] + offset[2];
    transform.position[3] = 1.0f;
    scale = math_random_float_range(0.3f, 0.4f);
    FastVecScale(quad.point[0], quad.point[0], scale);
    FastVecScale(quad.point[1], quad.point[1], scale);
    FastVecScale(quad.point[2], quad.point[2], scale);
    FastVecScale(quad.point[3], quad.point[3], scale);
    draw_world_quad(&quad, &transform, 0);
    FastVecScale(quad.point[0], quad.point[0], 0.5f);
    FastVecScale(quad.point[1], quad.point[1], 0.5f);
    FastVecScale(quad.point[2], quad.point[2], 0.5f);
    FastVecScale(quad.point[3], quad.point[3], 0.5f);
    tint += (u32)math_random_int_range(64, 127) << 24;
    color = tint;
    quad.color[3] = color; quad.color[2] = color;
    quad.color[1] = color; quad.color[0] = color;
    draw_world_quad(&quad, &transform, 0);
    FastVecScale(quad.point[0], quad.point[0], 0.5f);
    FastVecScale(quad.point[1], quad.point[1], 0.5f);
    FastVecScale(quad.point[2], quad.point[2], 0.5f);
    FastVecScale(quad.point[3], quad.point[3], 0.5f);
    white = ((u32)math_random_int_range(64, 127) << 24) + 0x7F7F7F;
    quad.color[3] = white; quad.color[2] = white;
    quad.color[1] = white; quad.color[0] = white;
    draw_world_quad(&quad, &transform, 0);
}
