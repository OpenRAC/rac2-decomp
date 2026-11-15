#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
typedef unsigned int u32;
typedef struct {
    TI128 position[4];
    u32 color[4];
    float uv[4][2];
    unsigned long primitive, texture, mode, registers;
} EffectPacket;
typedef struct {
    EffectPacket packet;
    float a[4];
    float b[4];
    float c[4];
    TI128 dead;
    TI128 axis;
} Frame;

extern unsigned long func_0027C878(int);
extern void ref_00325430_00(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
extern char ref_00325430_01[];

/* Fills an effect packet (texture 14, uv square, corners from the state block's two reference points) and draws it. */
void func_00325430(char *obj)
{
    Frame quad;
    char *vars = *(char **)(obj + 0x68);
    char *p0;
    char *p1;

    quad.packet.texture = GetEffectTextureDescriptor(14);
    p1 = vars + 0x310;
    p0 = vars + 0x300;
    quad.axis = 0;
    quad.packet.mode = 0x0000ff9000000260UL;
    quad.packet.registers = 0x0000008000000048UL;
    quad.packet.primitive = 0;
    quad.packet.color[1] = 0x1F7F7F7F;
    quad.packet.color[0] = 0x1F7F7F7F;
    quad.packet.color[3] = 0x1F7F7F7F;
    ((float *)&quad.axis)[3] = 1.0f;
    quad.packet.color[2] = 0x1F7F7F7F;
    ((float *)&quad.axis)[2] = 0.05000000074505806f;
    ref_00325430_00(&quad.packet);
    quad.packet.uv[0][0] = 0;
    quad.packet.uv[0][1] = 0;
    quad.packet.uv[1][0] = 0;
    quad.packet.uv[1][1] = 1.0f;
    quad.packet.uv[2][0] = 1.0f;
    quad.packet.uv[2][1] = 0;
    quad.packet.uv[3][0] = 1.0f;
    quad.packet.uv[3][1] = 1.0f;
    FastVecSub(quad.a, p1, p0);
    vec_scale_to_length(quad.a, quad.a, 1.0f);
    FastVecSub(quad.b, ref_00325430_01, p0);
    FastVecCross(quad.c, quad.b, quad.a);
    vec_scale_to_length(quad.c, quad.c, 1.0f);
    FastVecCross(quad.b, quad.a, quad.c);
    quad.dead = *(TI128 *)p0;
    quad.packet.position[0] = quad.axis;
    FastVecScale(&quad.packet.position[1], &quad.packet.position[0], -1.0f);
    transform_vector(&quad.packet.position[0], &quad.packet.position[0], quad.a);
    transform_vector(&quad.packet.position[1], &quad.packet.position[1], quad.a);
    quad.dead = *(TI128 *)p1;
    quad.packet.position[2] = quad.axis;
    FastVecScale(&quad.packet.position[3], &quad.packet.position[2], -1.0f);
    transform_vector(&quad.packet.position[2], &quad.packet.position[2], quad.a);
    transform_vector(&quad.packet.position[3], &quad.packet.position[3], quad.a);
    draw_world_quad(&quad.packet, 0, 0);
}
