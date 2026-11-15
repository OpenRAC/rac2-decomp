#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern u64 func_0027C878(int);
extern int D_L17_001B02D8 __attribute__((sda)), D_L17_001B02DC __attribute__((sda)), D_L17_001B02E0 __attribute__((sda)), D_L17_001B02E4 __attribute__((sda)), D_L17_001B02E8 __attribute__((sda));
extern int D_L17_001B0310 __attribute__((sda));
extern float D_L17_001B0290 __attribute__((sda));
extern char *D_L17_001B2C1C MACRO_ADDR;
extern char D_L17_001B9BC0[];
extern void func_00283098(void *, void *, void *);
extern void func_00282CD8(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00280B90(void *, int, int);

/* Draws successive textured ribbon segments from the indexed anchor. */
void func_L17_003C5200(char *obj)
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
    u64 blend = (u64)D_L17_001B02D8 | ((u64)D_L17_001B02DC << 2);
    blend |= (u64)D_L17_001B02E0 << 4;
    blend |= (u64)D_L17_001B02E4 << 6;
    blend |= (u64)D_L17_001B02E8 << 32;
    frame.color3 = D_L17_001B0310;
    frame.color2 = D_L17_001B0310;
    frame.color1 = D_L17_001B0310;
    frame.color0 = D_L17_001B0310;
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
    offset.f[2] = D_L17_001B0290;
    matrix_mul_vec3(&offset, &offset, obj + 0xC0);
    add_vectors(&world, &offset, obj + 0x10);
    {
        unsigned int index = *(int *)(state + 0x10);
        unsigned int address = index << 8;
        address += (unsigned int)D_L17_001B2C1C;
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
        FastVecSub(&camera, D_L17_001B9BC0, &current);
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
