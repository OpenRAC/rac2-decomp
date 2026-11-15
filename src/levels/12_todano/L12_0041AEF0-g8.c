/* Three animated ring packets, rendered in twelve rotated copies. */
#include "common.h"

typedef unsigned int u128 __attribute__((mode(TI)));
typedef union { u128 quad; float value[4]; } RingVector;
typedef struct { RingVector vertex[4]; unsigned int color[4]; float uv[4][2]; u64 tag[4]; } RingPacket;
typedef struct { RingVector column[4]; } RingMatrix;
extern void copy_matrix_rotation(RingMatrix *, void *);
extern void euler_to_matrix(RingMatrix *, RingVector *);
extern void multiply_matrix3x3(RingMatrix *, RingMatrix *, RingMatrix *);
extern void draw_world_quad(RingPacket *, RingMatrix *, int);
extern int FloatToInt(float);
extern u64 GetEffectTextureDescriptor(int);
extern float FastAddRotations(float, float), math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern int FastTweenColor(unsigned int, unsigned int, float);
extern float D_L12_001B1C80 __attribute__((sda));
extern unsigned int D_L12_001B1C90 __attribute__((sda)), D_L12_001B1C8C __attribute__((sda));
extern int D_L12_001B1CB8 __attribute__((sda));
extern int D_L12_001B1CBC __attribute__((sda)), D_L12_001B1CC0 __attribute__((sda));
extern float D_L12_001B1CC4 __attribute__((sda));
extern float D_L12_001B1CD0[][2] SDATA(D_L12_001B1CD0);
/* Retail walks X through $gp and Y through an absolute cursor. */
extern float D_L12_001B1CD4[] NOT_SDA;
void DrawAnimatedRings(unsigned char *self)
{
    RingPacket packets[3];
    RingMatrix matrix, rotation;
    RingVector angles, first, second;
    unsigned char *data = *(unsigned char **)(self + 0x68);
    float alpha, fraction, radius, angle, nextAngle, z;
    int i, j, n;
    int color;
    angles.quad = 0;
    angles.value[2] = 0.52359885f;
    copy_matrix_rotation(&matrix, self + 0xc0);
    qcopy(&matrix.column[3], self + 0x10);
    matrix.column[3].value[3] = 1.0f;
    euler_to_matrix(&rotation, &angles);
    fraction = *(float *)(data + 0x70) - (float)FloatToInt(*(float *)(data + 0x70));
    alpha = (D_L12_001B1C80 - *(float *)(data + 0x6c)) * 0.5f;
    if (alpha > 1.0f) alpha = 1.0f;
    else if (alpha < 0.0f) alpha = 0.0f;
    for (i = 0; i < 3; i++) {
        packets[i].tag[1] = GetEffectTextureDescriptor(D_L12_001B1CB8);
        packets[i].tag[2] = 0xff9000000260UL;
        packets[i].tag[0] = 5;
        packets[i].tag[3] = ((u64)D_L12_001B1CBC << 2) | ((u64)D_L12_001B1CC0 << 6) | 0x8000000000UL;
        radius = *(float *)(data + 0x6c) - (float)i * 0.05f;
        angle = (float)i * 0.17453295f;
        nextAngle = FastAddRotations(angle, 0.52359885f);
        first.value[0] = math_fast_sin_or_cos_a(angle) * radius;
        first.value[1] = math_fast_sin_or_cos_b(angle) * radius;
        first.value[2] = 0.0f; first.value[3] = 1.0f;
        second.value[0] = math_fast_sin_or_cos_a(nextAngle) * radius;
        second.value[1] = math_fast_sin_or_cos_b(nextAngle) * radius;
        second.value[2] = 0.0f; second.value[3] = 1.0f;
        z = fraction * D_L12_001B1CC4;
        qcopy(&packets[i].vertex[0], &first);
        packets[i].vertex[0].value[2] = z;
        qcopy(&packets[i].vertex[1], &first);
        packets[i].vertex[1].value[2] = -z;
        qcopy(&packets[i].vertex[2], &second);
        packets[i].vertex[2].value[2] = z;
        qcopy(&packets[i].vertex[3], &second);
        packets[i].vertex[3].value[2] = -z;
        color = FastTweenColor(D_L12_001B1C90, D_L12_001B1C8C, (1.0f - fraction) * alpha);
        for (j = 0; j < 4; j++) {
            packets[i].color[j] = color;
            packets[i].uv[j][0] = D_L12_001B1CD0[j][0];
            packets[i].uv[j][1] = D_L12_001B1CD4[j * 2];
        }
        fraction = fraction >= 0.666f ? fraction + -0.666f : fraction + 0.333f;
    }
    for (n = 11; n >= 0; n--) {
        multiply_matrix3x3(&matrix, &matrix, &rotation);
        draw_world_quad(&packets[0], &matrix, 1);
        draw_world_quad(&packets[1], &matrix, 1);
        draw_world_quad(&packets[2], &matrix, 1);
    }
}
