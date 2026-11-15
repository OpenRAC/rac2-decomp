#include "include_asm.h"
#include "common.h"

/* func_L02_003E2150 needs -g (its two division pads) besides -G8: config/cflags.txt. */

typedef int Quad2150 __attribute__((mode(TI)));

/* The 144-byte quad packet func_L02_002EF968 fills (L02_002EF968-helpers.c). */
struct RingPacket {
    union {
        Quad2150 q;
        float f[4];
    } vertices[4];
    int colors[4];
    float uv[4][2];
    long state[4];
};

extern void copy_matrix_rotation(void *, void *);
extern void euler_rotation_basis(void *, void *);
/* (a, b, phase) with its float first: the EE passes each bank in order. */
extern u32 PulseColor(float, u32, u32);
extern void FillQuadPacket(struct RingPacket *, int, u32, float (*)[2], void *, int);
extern void gfx_transform_and_draw_entries(struct RingPacket *, int, float *, int, float *);
extern float math_fast_sin_or_cos_b(float);
extern u32 FastTweenColor(u32, u32, float);
extern void draw_world_quad(struct RingPacket *, float *, int);
extern void multiply_matrix3x3(float *, float *, float *);

/* Level data, at its level-02 addresses. */
extern u32 ref_L02_003E2150_00[] __attribute__((sda)); /* 001B0808: the two pulse colors */
extern float ref_L02_003E2150_01[][2] SDATA(ref_L02_003E2150_01); /* 001B0798 */
extern char ref_L02_003E2150_02[];                     /* 002985C0: two quads' vertices */
extern float ref_L02_003E2150_03 __attribute__((sda)); /* 001B0810: height scale */
extern float ref_L02_003E2150_04 __attribute__((sda)); /* 001B0814: height base */
extern int ref_L02_003E2150_05 __attribute__((sda)); /* 001B07B8: ring repeat count */
extern int ref_L02_003E2150_06 __attribute__((sda)); /* 001B07BC: ring texture */
extern float ref_L02_003E2150_07[][2] SDATA(ref_L02_003E2150_07); /* 001B07C0 */
extern char ref_L02_003E2150_08[] SDATA(ref_L02_003E2150_08);     /* 001B0820 */
extern int ref_L02_003E2150_09 __attribute__((sda)); /* 001B07E0: glow texture */
extern float ref_L02_003E2150_10[][2] SDATA(ref_L02_003E2150_10); /* 001B07E8 */
extern char ref_L02_003E2150_11[] SDATA(ref_L02_003E2150_11);     /* 001B0860 */

/* Draws a pulsing ring around the object: two quads turned 32 times, a ring of quads
   raised by a sine bob and turned ref_05 times, then three passes of two glow quads. */
void DrawPulsingRingEffect(char *obj) {
    struct RingPacket packets[3];
    float rotate[12], first[16], angles[4], second[16];
    char *data = *(char **)(obj + 0x68);
    u32 color;
    int i, j;

    copy_matrix_rotation(first, obj + 0xC0);
    qcopy(first + 12, obj + 0x10);
    *(Quad2150 *)angles = 0;
    first[15] = 1.0f;
    angles[2] = 0.1963495463f;
    euler_rotation_basis(rotate, angles);
    color = PulseColor(*(float *)(data + 0x18), ref_L02_003E2150_00[0], ref_L02_003E2150_00[1]);
    FillQuadPacket(&packets[0], 5, color, ref_L02_003E2150_01, ref_L02_003E2150_02, 1);
    FillQuadPacket(&packets[1], 5, color, ref_L02_003E2150_01, ref_L02_003E2150_02 + 0x40, 1);
    gfx_transform_and_draw_entries(&packets[0], 2, rotate, 32, first);

    copy_matrix_rotation(second, obj + 0xC0);
    qcopy(second + 12, obj + 0x10);
    second[15] = 1.0f;
    second[14] += ref_L02_003E2150_04 + ref_L02_003E2150_03 * math_fast_sin_or_cos_b(*(float *)(data + 0x1C));
    angles[2] = 6.283185482f / ref_L02_003E2150_05;
    euler_rotation_basis(rotate, angles);
    color = PulseColor(*(float *)(data + 0x18), *(u32 *)(data + 0x28), *(u32 *)(data + 0x2C));
    color = FastTweenColor(color & 0xFFFFFF, color, *(float *)(data + 0x20));
    FillQuadPacket(&packets[0], ref_L02_003E2150_06, color, ref_L02_003E2150_07, ref_L02_003E2150_08, 1);
    gfx_transform_and_draw_entries(&packets[0], 1, rotate, ref_L02_003E2150_05, second);

    angles[2] = 2.09439516f;
    euler_rotation_basis(rotate, angles);
    FillQuadPacket(&packets[0], ref_L02_003E2150_09, color, ref_L02_003E2150_10, ref_L02_003E2150_11, 1);
    FillQuadPacket(&packets[1], ref_L02_003E2150_09, color, ref_L02_003E2150_10, ref_L02_003E2150_11, 1);
    for (j = 0; j < 4; j++)
        packets[1].vertices[j].f[2] += 0.1f;
    for (i = 2; i >= 0; i--) {
        draw_world_quad(&packets[0], second, 1);
        draw_world_quad(&packets[1], second, 1);
        multiply_matrix3x3(second, second, rotate);
    }
}
