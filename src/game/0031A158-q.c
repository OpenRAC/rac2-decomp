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

extern unsigned long GetEffectTextureDescriptor(int);
extern void ref_0031A158_00(void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, void *, int);
extern char ref_0031A158_01[];

/* Fills an effect packet (texture 14, corners from the state block's two reference points) and draws it. */
void gfx_draw_beam_between_points(char *obj)
{
    Frame f;
    char *st = *(char **)(obj + 0x68);
    char *p0;
    char *p1;

    f.packet.texture = GetEffectTextureDescriptor(14);
    p1 = st + 0x300;
    p0 = st + 0x2F0;
    f.axis = 0;
    f.packet.mode = 0x0000ff9000000260UL;
    f.packet.registers = 0x0000008000000048UL;
    f.packet.primitive = 0;
    f.packet.color[1] = 0x1F7F7F7F;
    f.packet.color[0] = 0x1F7F7F7F;
    f.packet.color[3] = 0x1F7F7F7F;
    ((float *)&f.axis)[3] = 1.0f;
    f.packet.color[2] = 0x1F7F7F7F;
    ((float *)&f.axis)[2] = 0.05000000074505806f;
    ref_0031A158_00(&f.packet);
    FastVecSub(f.a, p1, p0);
    vec_scale_to_length(f.a, f.a, 1.0f);
    FastVecSub(f.b, ref_0031A158_01, p0);
    FastVecCross(f.c, f.b, f.a);
    vec_scale_to_length(f.c, f.c, 1.0f);
    FastVecCross(f.b, f.a, f.c);
    f.dead = *(TI128 *)p0;
    f.packet.position[0] = f.axis;
    FastVecScale(&f.packet.position[1], &f.packet.position[0], -1.0f);
    transform_vector(&f.packet.position[0], &f.packet.position[0], f.a);
    transform_vector(&f.packet.position[1], &f.packet.position[1], f.a);
    f.dead = *(TI128 *)p1;
    f.packet.position[2] = f.axis;
    FastVecScale(&f.packet.position[3], &f.packet.position[2], -1.0f);
    transform_vector(&f.packet.position[2], &f.packet.position[2], f.a);
    transform_vector(&f.packet.position[3], &f.packet.position[3], f.a);
    draw_world_quad(&f.packet, 0, 0);
}
