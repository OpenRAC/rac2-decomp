/* func_L02_00411D18 is a unit of its own: $s2 holds a TImode value, and retail saves it
   with `sq` in a 16-byte slot below the 8-byte GPR saves (-frac2-wide-saves-below,
   docs/build/compiler-notes.md). The option keys on that mode, and the widened save mode
   carries over to later functions of a unit, so nothing else shares this file. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; } EffectVector;
typedef struct { EffectVector vertex[4]; } EffectQuad;
typedef struct { float uv[8]; } EffectUV;
typedef struct { u32 word[5]; } EffectPalette;
/* The builder and renderer walk 0x90-byte packets, including the last header word. */
typedef struct {
    EffectVector vertex[4];
    u8 header[0x10];
    float uv[4][2];
    u8 tail[0x20];
} EffectPacket;
extern const EffectUV g_energy_gate_primary_uv;
extern const EffectUV g_energy_gate_secondary_uv;
extern const EffectPalette g_energy_gate_palette;
extern const EffectQuad g_energy_gate_primary_quad;
extern const EffectQuad g_energy_gate_left_quad;
extern const EffectQuad g_energy_gate_right_quad;
extern u32 g_energy_gate_primary_packet_flags __attribute__((sda));
extern u32 g_energy_gate_secondary_packet_flags __attribute__((sda));
extern EffectVector g_camera_l02_position;
extern void copy_matrix_rotation(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_transform_by_object_or_given(char *, char *, char *, char *);
extern void FastVecScale(void *, void *, float);
extern float math_fast_sin_or_cos_b(float);
extern u32 FastTweenColor(u32, u32, float);
extern void FillQuadPacket(EffectPacket *, u32, u32, float *, EffectVector *, s32);
extern void *memset(void *, s32, u32);
extern void euler_rotation_basis(void *, void *);
extern void gfx_transform_and_draw_entries(EffectPacket *, s32, void *, s32, void *);
extern void FastVecAdd(void *, void *, void *);

/* Render seven related quads with scrolling UVs and two expanding wave pairs. */
void energy_gate_draw_effect(u8 *object)
{
    EffectUV primary_uv = g_energy_gate_primary_uv;
    EffectUV secondary_uv = g_energy_gate_secondary_uv;
    EffectPalette palette = g_energy_gate_palette;
    EffectQuad primary;
    EffectQuad left;
    EffectQuad right;
    EffectVector context[4];
    EffectVector direction;
    EffectPacket packets[7];
    u32 wave_color[2];
    EffectVector transform_parameters[2];
    EffectVector expansion[2];
    EffectVector zero_expansion[2];
    EffectVector matrix[3];
    u8 *state = *(u8 **)(object + 0x68);
    EffectVector *position = (EffectVector *)(object + 0x10);
    u32 primary_color;
    u32 secondary_color;
    float phase;
    float fade;
    s32 i;
    s32 j;

    primary.vertex[0].quad = g_energy_gate_primary_quad.vertex[0].quad;
    primary.vertex[1].quad = g_energy_gate_primary_quad.vertex[1].quad;
    primary.vertex[2].quad = g_energy_gate_primary_quad.vertex[2].quad;
    primary.vertex[3].quad = g_energy_gate_primary_quad.vertex[3].quad;
    left.vertex[0].quad = g_energy_gate_left_quad.vertex[0].quad;
    left.vertex[1].quad = g_energy_gate_left_quad.vertex[1].quad;
    left.vertex[2].quad = g_energy_gate_left_quad.vertex[2].quad;
    left.vertex[3].quad = g_energy_gate_left_quad.vertex[3].quad;
    right.vertex[0].quad = g_energy_gate_right_quad.vertex[0].quad;
    right.vertex[1].quad = g_energy_gate_right_quad.vertex[1].quad;
    right.vertex[2].quad = g_energy_gate_right_quad.vertex[2].quad;
    right.vertex[3].quad = g_energy_gate_right_quad.vertex[3].quad;
    copy_matrix_rotation(context, object + 0xC0);
    qcopy(&context[3], position);
    context[3].f[3] = 1.0f;
    vec_scale_to_length(context, context, 4.0f);
    vec_scale_to_length(&context[1], &context[1], 10.0f);
    FastVecSub(&direction, &g_camera_l02_position, position);
    vec_transform_by_object_or_given((char *)object, (char *)&direction, (char *)&direction, 0);
    if (direction.f[0] < 0.0f)
        FastVecScale(context, context, -1.0f);
    phase = math_fast_sin_or_cos_b(*(float *)(state + 0x2C)) * 0.5f + 0.5f;
    primary_color = FastTweenColor(palette.word[0], palette.word[1], phase);
    secondary_color = FastTweenColor(palette.word[2], palette.word[3], phase);
    fade = *(float *)(state + 0x20);
    fade = fade >= 0.2f ? fade : 1.0f - fade * 5.0f;
    wave_color[0] = FastTweenColor(palette.word[3], palette.word[3] & 0xFFFFFF, fade);
    fade = *(float *)(state + 0x24);
    fade = fade >= 0.2f ? fade : 1.0f - fade * 5.0f;
    wave_color[1] = FastTweenColor(palette.word[3], palette.word[3] & 0xFFFFFF, fade);
    if (*(float *)(state + 0x1C) < 1.0f) {
        primary_color = FastTweenColor(primary_color & 0xFFFFFF, primary_color, *(float *)(state + 0x1C));
        secondary_color = FastTweenColor(secondary_color & 0xFFFFFF, secondary_color, *(float *)(state + 0x1C));
        wave_color[0] = FastTweenColor(wave_color[0] & 0xFFFFFF, wave_color[0], *(float *)(state + 0x1C));
        wave_color[1] = FastTweenColor(wave_color[1] & 0xFFFFFF, wave_color[1], *(float *)(state + 0x1C));
    }
    FillQuadPacket(packets, g_energy_gate_primary_packet_flags, primary_color, primary_uv.uv, primary.vertex, 1);
    FillQuadPacket(packets + 1, g_energy_gate_secondary_packet_flags, secondary_color, secondary_uv.uv, left.vertex, 1);
    FillQuadPacket(packets + 2, g_energy_gate_secondary_packet_flags, secondary_color, secondary_uv.uv, right.vertex, 1);
    FillQuadPacket(packets + 3, g_energy_gate_secondary_packet_flags, wave_color[0], secondary_uv.uv, left.vertex, 1);
    FillQuadPacket(packets + 4, g_energy_gate_secondary_packet_flags, wave_color[0], secondary_uv.uv, right.vertex, 1);
    FillQuadPacket(packets + 5, g_energy_gate_secondary_packet_flags, wave_color[1], secondary_uv.uv, left.vertex, 1);
    FillQuadPacket(packets + 6, g_energy_gate_secondary_packet_flags, wave_color[1], secondary_uv.uv, right.vertex, 1);
    for (i = 0; i < 4; i++) {
        packets[1].uv[i][0] += *(float *)(state + 0x28);
        packets[2].uv[i][0] += *(float *)(state + 0x28);
        packets[3].uv[i][0] += *(float *)(state + 0x28);
        packets[4].uv[i][0] += *(float *)(state + 0x28);
        packets[5].uv[i][0] += *(float *)(state + 0x28);
        packets[6].uv[i][0] += *(float *)(state + 0x28);
        packets[3].vertex[i].f[2] -= *(float *)(state + 0x20) + *(float *)(state + 0x20);
        packets[4].vertex[i].f[2] += *(float *)(state + 0x20) + *(float *)(state + 0x20);
        packets[5].vertex[i].f[2] -= *(float *)(state + 0x24) + *(float *)(state + 0x24);
        packets[6].vertex[i].f[2] += *(float *)(state + 0x24) + *(float *)(state + 0x24);
    }
    transform_parameters[0].quad = 0;
    transform_parameters[1].quad = 0;
    transform_parameters[0].f[2] = -0.19634955f;
    transform_parameters[1].f[2] = 6.0f;
    memset(zero_expansion, 0, sizeof(zero_expansion));
    zero_expansion[0].f[2] = *(float *)(state + 0x20) + *(float *)(state + 0x20);
    zero_expansion[1].f[2] = *(float *)(state + 0x24) + *(float *)(state + 0x24);
    expansion[0].quad = zero_expansion[0].quad;
    expansion[1].quad = zero_expansion[1].quad;
    euler_rotation_basis(matrix, transform_parameters);
    gfx_transform_and_draw_entries(packets, 7, matrix, 16, context);
    for (j = 0; j < 4; j++) {
        FastVecAdd(&packets[0].vertex[j], &primary.vertex[j], &transform_parameters[1]);
        FastVecAdd(&packets[1].vertex[j], &left.vertex[j], &transform_parameters[1]);
        FastVecAdd(&packets[2].vertex[j], &right.vertex[j], &transform_parameters[1]);
        FastVecAdd(&packets[3].vertex[j], &left.vertex[j], &transform_parameters[1]);
        FastVecAdd(&packets[4].vertex[j], &right.vertex[j], &transform_parameters[1]);
        FastVecAdd(&packets[5].vertex[j], &left.vertex[j], &transform_parameters[1]);
        FastVecAdd(&packets[6].vertex[j], &right.vertex[j], &transform_parameters[1]);
        FastVecSub(&packets[3].vertex[j], &packets[3].vertex[j], &expansion[0]);
        FastVecAdd(&packets[4].vertex[j], &packets[4].vertex[j], &expansion[0]);
        FastVecSub(&packets[5].vertex[j], &packets[5].vertex[j], &expansion[1]);
        FastVecAdd(&packets[6].vertex[j], &packets[6].vertex[j], &expansion[1]);
    }
    euler_rotation_basis(matrix, transform_parameters);
    gfx_transform_and_draw_entries(packets, 7, matrix, 16, context);
}
