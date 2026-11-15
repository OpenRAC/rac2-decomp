#include "common.h"

typedef struct { float x, y, z, w; } RingVertex;
typedef struct { RingVertex vertex[4]; unsigned int color[4]; float uv[4][2]; unsigned long long state[4]; } RingPacket __attribute__((aligned(16)));
extern int D_L13_001B16E8[4] __attribute__((sda));
extern int D_L13_001B16F8 __attribute__((sda));
extern unsigned int D_L13_001B16FC __attribute__((sda));
extern float D_L13_001B1700[4][2] __attribute__((sda));
extern float D_L13_001B1704[] __attribute__((sda));
extern float D_L13_001B1720 __attribute__((sda));
extern unsigned char D_0018C0D5[];
extern void copy_matrix_rotation(void *, void *);
extern unsigned long long GetEffectTextureDescriptor(int);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void draw_world_quad(void *, void *, int);

/* Draws the growing glowing ring effect of the warp ring as a circle of flat strips. */
void DrawMobyRadiusRing(void *opaque) {
    char *object = opaque;
    int uvIndex;
    RingPacket packet;
    float matrix[16] __attribute__((aligned(16)));
    char *private = *(char **)(object + 0x68);
    float thickness;
    float radius;
    float fade;
    float angle;
    int i;
    int j;
    int next;
    RingVertex *vertex;
    copy_matrix_rotation(matrix, object + 0xC0);
    qcopy(matrix + 12, object + 0x10);
    packet.state[1] = GetEffectTextureDescriptor(D_L13_001B16F8);
    {
        long long state = D_L13_001B16E8[0];
        state |= (long long)D_L13_001B16E8[1] << 2;
        state |= (long long)D_L13_001B16E8[2] << 4;
        state |= (long long)D_L13_001B16E8[3] << 6;
        packet.state[3] = state | 0x8000000000ULL;
    }
    packet.state[2] = 0xFF9000000260ULL;
    packet.state[0] = 0;
    for (uvIndex = 0; uvIndex < 4; uvIndex++) {
        packet.uv[uvIndex][0] = D_L13_001B1700[uvIndex][0];
        packet.uv[uvIndex][1] = D_L13_001B1704[uvIndex * 2];
        packet.color[uvIndex] = D_L13_001B16FC;
    }
    thickness = 0.1f;
    {
        float delta = *(float *)(private + 0x34);
        float maximum = 1.15f;
        if (delta < maximum) {
            radius = delta;
            delta = maximum - radius;
            maximum = 1.0f;
            fade = delta + delta;
            if (fade > maximum) fade = maximum;
            else if (fade < 0.0f) fade = 0.0f;
            thickness = fade + 0.1f;
            if (radius < 0.65f) D_0018C0D5[0] = 1;
            else D_0018C0D5[0] = 0;
        }
    }
    for (i = 0; i < 32; i = next) {
        j = 0;
        next = i + 1;
        vertex = packet.vertex;
        for (; j < 4; j++, vertex++) {
            angle = (float)(i + j / 2) * 0.19637252f - 3.14159f;
            vertex->x = math_fast_sin_or_cos_a(angle) * *(float *)(private + 0x34);
            vertex->y = math_fast_sin_or_cos_b(angle) * *(float *)(private + 0x34);
            vertex->z = 0.0f;
            vertex->z = (j & 1) ? D_L13_001B1720 + thickness : D_L13_001B1720 - thickness;
            vertex->w = 1.0f;
        }
        draw_world_quad(&packet, matrix, 0);
    }
}
