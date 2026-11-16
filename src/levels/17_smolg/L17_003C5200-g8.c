#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern u64 GetEffectTextureDescriptor(int);
extern int g_blend_field_a __attribute__((sda)), g_blend_field_b __attribute__((sda)), g_blend_field_c __attribute__((sda)), g_blend_field_d __attribute__((sda)), g_blend_field_e __attribute__((sda));
extern int g_frame_color __attribute__((sda));
extern float g_carrier_height_offset_c __attribute__((sda));
extern char *g_moby_l17_pool MACRO_ADDR;
extern char g_tether_origin_pos[];
extern void matrix_mul_vec3(void *, void *, void *);
extern void add_vectors(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void draw_world_quad(void *, int, int);

/* Draws successive textured ribbon segments from the indexed anchor. */
void DrawIndexedRibbonSegments(char *obj)
{
    struct {
        Vec vertices[4];
        int color0, color1, color2, color3;
        union { float f; u32 bits; } uv[8];
        u64 primitive, texture, flags, blend;
    } frame;
    Vec start, current, offset, delta, camera, side, world;
    char *state = *(char **)(obj + 0x68);
    float along, length, amount;
    u64 texture = GetEffectTextureDescriptor(15);
    u64 blend = (u64)g_blend_field_a | ((u64)g_blend_field_b << 2);
    blend |= (u64)g_blend_field_c << 4;
    blend |= (u64)g_blend_field_d << 6;
    blend |= (u64)g_blend_field_e << 32;
    frame.color3 = g_frame_color;
    frame.color2 = g_frame_color;
    frame.color1 = g_frame_color;
    frame.color0 = g_frame_color;
    frame.texture = texture;
    frame.flags = 0xFF9000000260ULL;
    frame.primitive = 5;
    frame.blend = blend;
    frame.uv[0].bits = 0;
    frame.uv[1].bits = 0;
    frame.uv[2].f = 1.0f;
    frame.uv[3].bits = 0;
    frame.uv[4].bits = 0;
    frame.uv[5].f = 1.0f;
    frame.uv[6].f = 1.0f;
    frame.uv[7].f = 1.0f;
    qzero_nc(&offset);
    offset.f[2] = g_carrier_height_offset_c;
    matrix_mul_vec3(&offset, &offset, obj + 0xC0);
    add_vectors(&world, &offset, obj + 0x10);
    {
        unsigned int index = *(int *)(state + 0x10);
        unsigned int address = index << 8;
        address += (unsigned int)g_moby_l17_pool;
        start.q = *(Quad *)(address + 0x10);
    }
    qcopy(&current, &start);
    FastVecSub(&delta, &offset, &start);
    along = 0;
    length = FastVecLength(&delta);
    qcopy(&frame.vertices[0], &start);
    qcopy(&frame.vertices[2], &start);
    while (along < length) {
        amount = 0.3f;
        if (length - along < amount) amount = length - along;
        along += amount;
        vec_scale_to_length(&delta, &delta, amount);
        FastVecAdd(&current, &current, &delta);
        qcopy(&frame.vertices[1], &current);
        qcopy(&frame.vertices[3], &current);
        FastVecSub(&camera, g_tether_origin_pos, &current);
        FastVecCross(&side, &camera, &delta);
        vec_scale_to_length(&side, &side, 0.1f);
        FastVecAdd(&frame.vertices[1], &frame.vertices[1], &side);
        FastVecSub(&frame.vertices[3], &frame.vertices[3], &side);
        draw_world_quad(&frame, 0, 1);
        qcopy(&start, &current);
        qcopy(&frame.vertices[0], &frame.vertices[1]);
        qcopy(&frame.vertices[2], &frame.vertices[3]);
    }
}
