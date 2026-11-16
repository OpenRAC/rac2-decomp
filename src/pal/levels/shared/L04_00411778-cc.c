/* func_PAL_L04_00411778, the PAL copy of func_L04_0040D148: the same C. */
#include "common.h"

typedef unsigned int B1202Quad __attribute__((mode(TI)));
typedef union {
    B1202Quad bits;
    float f[4];
} RenderVector;
typedef struct {
    RenderVector vertex[4];
    unsigned int color[4];
    float uv[4][2];
    unsigned long long primitive, texture, mode, flags;
} B1202Packet;

extern int g_game_tick_counter[] __attribute__((sda));
extern float IntToFloat(int);
extern float fast_fmod(float, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_float_g(float);
extern float FastAddRotations(float, float);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern void euler_to_matrix(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern unsigned long long GetEffectTextureDescriptor(int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void draw_world_quad(void *, void *, int);
extern void gfx_l04_draw_billboard_sprite(void *, int, unsigned int, int, float, float, float, float);
/* Integer and float arguments keep their order within each EE register bank. */
extern void gfx_draw_flash_quad(void *, int, int, float, float, float, float, float);

/* Draws the pulsing glow sphere around the bike: a colour-cycling textured sphere, three spinning
   billboard rings and a flash quad on top. alpha is -1 for full opacity (PAL). */
/* This unit is built with -g: retail's nops before the two latitude divisions
 * are the assembler's div.s floor after a line label, so keep one statement per
 * line. rows and cols must stay variables: as constants the loops' zero-trip
 * tests fold before gcse, which then hoists the vertex addresses into spill
 * slots. t is one local on purpose: its use in the inner loop, where $f12 is
 * already loaded for the next call, keeps it out of $f12 at the blend calls. */
void draw_pulsing_glow_sphere_pal(unsigned char *moby, int alpha)
{
    B1202Packet packet;
    float matrix[4][4] __attribute__((aligned(16)));
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float t, offset, lat0, lat1, lon0, lon1, u0, v0, v1, cos0, cos1;
    unsigned int color, a, c;
    int i, j;
    int rows = 10, cols = 10;

    t = math_fast_sin_or_cos_b(fast_fmod(IntToFloat(g_game_tick_counter[0]), 150.33334f) * 0.0066518844f * 6.283186f);
    t = (t + 1.0f) * 0.5f;
    if (alpha == -1) {
        color = FastTweenColor(0x1fb43264, 0x1f502800, t);
    } else {
        if (alpha < 0) {
            alpha = 0;
        }
        color = FastTweenColor(0x1fb43264, ((unsigned int)alpha << 24) | 0x502800, t);
    }
    offset = fast_fmod(IntToFloat(g_game_tick_counter[0]), 25.333334f) * 0.039473683f;
    euler_to_matrix(matrix, moby + 0xf0);
    *(B1202Quad *)(matrix[3]) = *(B1202Quad *)(moby + 0x10);
    vec_scale_to_length(matrix[0], matrix[0], 0.4f);
    vec_scale_to_length(matrix[1], matrix[1], 0.35f);
    vec_scale_to_length(matrix[2], matrix[2], 0.35f);
    packet.texture = GetEffectTextureDescriptor(21);
    packet.mode = 0xff9000000260ULL;
    packet.flags = 0x8000000048ULL;
    packet.primitive = 0;
    for (i = 0; i < rows; i++) {
        lat0 = IntToFloat(i) * 3.141593f / IntToFloat(rows) - 1.5707965f;
        lat1 = IntToFloat(i + 1) * 3.141593f / IntToFloat(rows) - 1.5707965f;
        v0 = (math_fast_sin_or_cos_b(lat0) + 1.0f) * 0.5f;
        v1 = (math_fast_sin_or_cos_b(lat1) + 1.0f) * 0.5f;
        for (j = 0; j < cols; j++) {
            lon0 = math_fast_float_g(IntToFloat(j) * 6.283186f / IntToFloat(cols));
            lon1 = math_fast_float_g(IntToFloat(j + 1) * 6.283186f / IntToFloat(cols));
            cos0 = math_fast_sin_or_cos_a(lon0);
            cos1 = math_fast_sin_or_cos_a(lon1);
            u0 = offset + (cos0 + 1.0f) * 0.5f;
            t = offset + (cos1 + 1.0f) * 0.5f;
            packet.uv[1][1] = v0;
            packet.uv[0][1] = v0;
            packet.uv[3][1] = v1;
            packet.uv[2][1] = v1;
            packet.color[3] = color;
            packet.color[2] = color;
            packet.color[1] = color;
            packet.color[0] = color;
            packet.uv[0][0] = u0;
            packet.uv[1][0] = t;
            packet.uv[2][0] = u0;
            packet.uv[3][0] = t;
            vec_build_spherical_offset(packet.vertex[0].f, 1.0f, lon0, lat0);
            vec_build_spherical_offset(packet.vertex[1].f, 1.0f, lon1, lat0);
            vec_build_spherical_offset(packet.vertex[2].f, 1.0f, lon0, lat1);
            vec_build_spherical_offset(packet.vertex[3].f, 1.0f, lon1, lat1);
            packet.vertex[0].f[3] = 1.0f;
            packet.vertex[1].f[3] = 1.0f;
            packet.vertex[2].f[3] = 1.0f;
            packet.vertex[3].f[3] = 1.0f;
            draw_world_quad(&packet, matrix, 0);
        }
    }
    *(float *)(vars + 0x4b4) = FastAddRotations(*(float *)(vars + 0x4b4), 0.01f);
    *(float *)(vars + 0x4b8) = FastAddRotations(*(float *)(vars + 0x4b8), -0.007f);
    *(float *)(vars + 0x4bc) = FastAddRotations(*(float *)(vars + 0x4bc), 0.007f);
    *(float *)(vars + 0x4c0) = FastAddRotations(*(float *)(vars + 0x4c0), *(float *)(vars + 0x30c) * 0.1f);
    if (alpha == -1) {
        gfx_l04_draw_billboard_sprite(moby + 0x10, *(int *)(vars + 0x648), 0x0fc8c8c8, 1, 0.495f, 0.35f, *(float *)(vars + 0x4b4), *(float *)(moby + 0xf4));
        gfx_l04_draw_billboard_sprite(moby + 0x10, *(int *)(vars + 0x648), 0x0fc8c8c8, 1, 0.495f, 0.35f, *(float *)(vars + 0x4b8), *(float *)(moby + 0xf4));
        gfx_l04_draw_billboard_sprite(moby + 0x10, 54, 0x28969600, 1, 0.385f, 0.35f, *(float *)(vars + 0x4bc), *(float *)(moby + 0xf4));
    } else {
        if (alpha < 0) {
            alpha = 0;
        }
        a = (unsigned int)alpha << 24;
        c = a | 0xc8c8c8;
        gfx_l04_draw_billboard_sprite(moby + 0x10, *(int *)(vars + 0x648), c, 1, 0.495f, 0.35f, *(float *)(vars + 0x4b4), *(float *)(moby + 0xf4));
        gfx_l04_draw_billboard_sprite(moby + 0x10, *(int *)(vars + 0x648), c, 1, 0.495f, 0.35f, *(float *)(vars + 0x4b8), *(float *)(moby + 0xf4));
        gfx_l04_draw_billboard_sprite(moby + 0x10, 54, a | 0x969600, 1, 0.385f, 0.35f, *(float *)(vars + 0x4bc), *(float *)(moby + 0xf4));
    }
    gfx_draw_flash_quad(moby + 0x10, *(int *)(vars + 0x644), 0, 0.32f, 0.5f, *(float *)(vars + 0x4c0), 0.0f, 0.0f);
}
