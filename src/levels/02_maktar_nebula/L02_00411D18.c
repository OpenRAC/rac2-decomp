/* func_L02_00411D18 is a unit of its own: $s2 holds a TImode value, and retail saves it
   with `sq` in a 16-byte slot below the 8-byte GPR saves (-frac2-wide-saves-below,
   docs/COMPILER-NOTES.md). The option keys on that mode, and the widened save mode
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
extern const EffectUV D_L02_001B1AE0;
extern const EffectUV D_L02_001B1B00;
extern const EffectPalette D_L02_001B1B20;
extern const EffectQuad D_L02_001B1B40;
extern const EffectQuad D_L02_001B1B80;
extern const EffectQuad D_L02_001B1BC0;
extern u32 D_L02_001B1C00 __attribute__((sda));
extern u32 D_L02_001B1C04 __attribute__((sda));
extern EffectVector D_L02_001BA500;
extern void func_00283658(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFDD8(char *, char *, char *, char *);
extern void func_00282D30(void *, void *, float);
extern float func_00283198(float);
extern u32 func_00283D38(u32, u32, float);
extern void func_L02_002EF968(EffectPacket *, u32, u32, float *, EffectVector *, s32);
extern void *func_00115484(void *, s32, u32);
extern void func_002833F0(void *, void *);
extern void func_L01_002E1510(EffectPacket *, s32, void *, s32, void *);
extern void func_00282CC0(void *, void *, void *);

/* Render seven related quads with scrolling UVs and two expanding wave pairs. */
void func_L02_00411D18(u8 *object)
{
    EffectUV primary_uv = D_L02_001B1AE0;
    EffectUV secondary_uv = D_L02_001B1B00;
    EffectPalette palette = D_L02_001B1B20;
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

    primary.vertex[0].quad = D_L02_001B1B40.vertex[0].quad;
    primary.vertex[1].quad = D_L02_001B1B40.vertex[1].quad;
    primary.vertex[2].quad = D_L02_001B1B40.vertex[2].quad;
    primary.vertex[3].quad = D_L02_001B1B40.vertex[3].quad;
    left.vertex[0].quad = D_L02_001B1B80.vertex[0].quad;
    left.vertex[1].quad = D_L02_001B1B80.vertex[1].quad;
    left.vertex[2].quad = D_L02_001B1B80.vertex[2].quad;
    left.vertex[3].quad = D_L02_001B1B80.vertex[3].quad;
    right.vertex[0].quad = D_L02_001B1BC0.vertex[0].quad;
    right.vertex[1].quad = D_L02_001B1BC0.vertex[1].quad;
    right.vertex[2].quad = D_L02_001B1BC0.vertex[2].quad;
    right.vertex[3].quad = D_L02_001B1BC0.vertex[3].quad;
    func_00283658(context, object + 0xC0);
    qcopy(&context[3], position);
    context[3].f[3] = 1.0f;
    func_00282F20(context, context, 4.0f);
    func_00282F20(&context[1], &context[1], 10.0f);
    func_00282CF0(&direction, &D_L02_001BA500, position);
    func_002AFDD8((char *)object, (char *)&direction, (char *)&direction, 0);
    if (direction.f[0] < 0.0f)
        func_00282D30(context, context, -1.0f);
    phase = func_00283198(*(float *)(state + 0x2C)) * 0.5f + 0.5f;
    primary_color = func_00283D38(palette.word[0], palette.word[1], phase);
    secondary_color = func_00283D38(palette.word[2], palette.word[3], phase);
    fade = *(float *)(state + 0x20);
    fade = fade >= 0.2f ? fade : 1.0f - fade * 5.0f;
    wave_color[0] = func_00283D38(palette.word[3], palette.word[3] & 0xFFFFFF, fade);
    fade = *(float *)(state + 0x24);
    fade = fade >= 0.2f ? fade : 1.0f - fade * 5.0f;
    wave_color[1] = func_00283D38(palette.word[3], palette.word[3] & 0xFFFFFF, fade);
    if (*(float *)(state + 0x1C) < 1.0f) {
        primary_color = func_00283D38(primary_color & 0xFFFFFF, primary_color, *(float *)(state + 0x1C));
        secondary_color = func_00283D38(secondary_color & 0xFFFFFF, secondary_color, *(float *)(state + 0x1C));
        wave_color[0] = func_00283D38(wave_color[0] & 0xFFFFFF, wave_color[0], *(float *)(state + 0x1C));
        wave_color[1] = func_00283D38(wave_color[1] & 0xFFFFFF, wave_color[1], *(float *)(state + 0x1C));
    }
    func_L02_002EF968(packets, D_L02_001B1C00, primary_color, primary_uv.uv, primary.vertex, 1);
    func_L02_002EF968(packets + 1, D_L02_001B1C04, secondary_color, secondary_uv.uv, left.vertex, 1);
    func_L02_002EF968(packets + 2, D_L02_001B1C04, secondary_color, secondary_uv.uv, right.vertex, 1);
    func_L02_002EF968(packets + 3, D_L02_001B1C04, wave_color[0], secondary_uv.uv, left.vertex, 1);
    func_L02_002EF968(packets + 4, D_L02_001B1C04, wave_color[0], secondary_uv.uv, right.vertex, 1);
    func_L02_002EF968(packets + 5, D_L02_001B1C04, wave_color[1], secondary_uv.uv, left.vertex, 1);
    func_L02_002EF968(packets + 6, D_L02_001B1C04, wave_color[1], secondary_uv.uv, right.vertex, 1);
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
    func_00115484(zero_expansion, 0, sizeof(zero_expansion));
    zero_expansion[0].f[2] = *(float *)(state + 0x20) + *(float *)(state + 0x20);
    zero_expansion[1].f[2] = *(float *)(state + 0x24) + *(float *)(state + 0x24);
    expansion[0].quad = zero_expansion[0].quad;
    expansion[1].quad = zero_expansion[1].quad;
    func_002833F0(matrix, transform_parameters);
    func_L01_002E1510(packets, 7, matrix, 16, context);
    for (j = 0; j < 4; j++) {
        func_00282CC0(&packets[0].vertex[j], &primary.vertex[j], &transform_parameters[1]);
        func_00282CC0(&packets[1].vertex[j], &left.vertex[j], &transform_parameters[1]);
        func_00282CC0(&packets[2].vertex[j], &right.vertex[j], &transform_parameters[1]);
        func_00282CC0(&packets[3].vertex[j], &left.vertex[j], &transform_parameters[1]);
        func_00282CC0(&packets[4].vertex[j], &right.vertex[j], &transform_parameters[1]);
        func_00282CC0(&packets[5].vertex[j], &left.vertex[j], &transform_parameters[1]);
        func_00282CC0(&packets[6].vertex[j], &right.vertex[j], &transform_parameters[1]);
        func_00282CF0(&packets[3].vertex[j], &packets[3].vertex[j], &expansion[0]);
        func_00282CC0(&packets[4].vertex[j], &packets[4].vertex[j], &expansion[0]);
        func_00282CF0(&packets[5].vertex[j], &packets[5].vertex[j], &expansion[1]);
        func_00282CC0(&packets[6].vertex[j], &packets[6].vertex[j], &expansion[1]);
    }
    func_002833F0(matrix, transform_parameters);
    func_L01_002E1510(packets, 7, matrix, 16, context);
}
