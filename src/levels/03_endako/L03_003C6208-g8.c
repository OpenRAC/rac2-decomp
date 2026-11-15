#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef struct { float u, v; } UV;
typedef struct {
    TI128 pos[4];
    int color[4];
    UV uv[4];
    u64 tag;
    u64 tex;
    u64 regs;
    u64 mode;
} Packet;

extern void copy_matrix_rotation(void *, void *);
extern void func_L03_002EFB60(void *, void *, float);
extern float math_fast_sin_or_cos_b(float);
extern u64 GetEffectTextureDescriptor(int);
extern int FastTweenColor(int, int, float);
extern void euler_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void draw_world_quad(void *, void *, int);
extern int D_L03_001B0070 __attribute__((sda));
extern int D_L03_001B0074 __attribute__((sda));
extern int D_L03_001B0078 __attribute__((sda));
extern int D_L03_001B007C __attribute__((sda));
extern int D_L03_001B0080 __attribute__((sda));
extern float D_L03_001B0060[] SDATA(D_L03_001B0060);
extern float D_L03_001B0088[] SDATA(D_L03_001B0088);
extern float D_L03_001B008C[] MACRO_ADDR;
extern float D_L03_001B00A8[] SDATA(D_L03_001B00A8);
extern float D_L03_001B00AC[] MACRO_ADDR;
extern float D_L03_001B00C8[] SDATA(D_L03_001B00C8);
extern float D_L03_001B00CC[] MACRO_ADDR;
extern int D_L03_001B00E8[] SDATA(D_L03_001B00E8);
extern int D_L03_001B00F8[] SDATA(D_L03_001B00F8);
extern int D_L03_001B0108[] SDATA(D_L03_001B0108);
extern TI128 D_L03_001B0120[] SDATA(D_L03_001B0120);

/* Draws the spinning rotor obj as stacked flat rings, using its spin, wobble and fade values. */
void rotor_draw(char *obj)
{
    Packet quad;
    float rotation[12];
    float world_matrix[16];
    float angle[4];
    float *state = *(float **)(obj + 0x68);
    float blend, intensity;

    copy_matrix_rotation(world_matrix, obj + 0xC0);
    if (state[0] != 1.0f)
        func_L03_002EFB60(world_matrix, world_matrix, state[0]);
    qcopy(&world_matrix[12], obj + 0x10);
    world_matrix[15] = 1.0f;
    blend = math_fast_sin_or_cos_b(state[1]) * 0.5f + 0.5f;
    intensity = math_fast_sin_or_cos_b(state[4]) * 0.5f + 0.5f;
    quad.tex = GetEffectTextureDescriptor(D_L03_001B0070);
    quad.mode = ((u64)D_L03_001B007C << 2) |
        ((u64)D_L03_001B0080 << 6) | ((u64)0x8000 << 24);
    quad.regs = 0x0000FF9000000260ULL;
    quad.tag = 0;
    {
        int i, color, side;
        for (i = 0; i < 4; i++) {
            side = i & 1;
            quad.uv[i].u = D_L03_001B0088[i*2];
            quad.uv[i].v = D_L03_001B008C[i*2];
            color = FastTweenColor(D_L03_001B00E8[side], D_L03_001B00E8[side+2], blend);
            quad.color[i] = color;
            quad.color[i] = FastTweenColor(color & 0xFFFFFF, color, state[5]);
            qcopy(&quad.pos[i], &D_L03_001B0120[side]);
        }
    }
    *(TI128 *)angle = 0;
    angle[0] = 0.19634954631328583f;
    euler_rotation_basis(rotation, angle);
    matrix_mul_vec3(&quad.pos[2], &quad.pos[2], rotation);
    matrix_mul_vec3(&quad.pos[3], &quad.pos[3], rotation);
    multiply_matrix3x3(rotation, rotation, rotation);
    {
        int i, j;
        for (i = 0; (float)i < 32.0f; i++) {
            j = (i & 1) ? 2 : 0;
            matrix_mul_vec3(&quad.pos[j], &quad.pos[j], rotation);
            matrix_mul_vec3(&quad.pos[j+1], &quad.pos[j+1], rotation);
            draw_world_quad(&quad, world_matrix, 1);
        }
    }
    quad.tex = GetEffectTextureDescriptor(D_L03_001B0074);
    angle[0] = 0.5235987901687622f;
    euler_rotation_basis(rotation, angle);
    {
        int i, color, side;
        for (i = 0; i < 4; i++) {
            side = i & 1;
            quad.uv[i].u = D_L03_001B00A8[i*2];
            quad.uv[i].v = D_L03_001B00AC[i*2];
            color = FastTweenColor(D_L03_001B00F8[side], D_L03_001B00F8[side+2], intensity);
            quad.color[i] = color;
            quad.color[i] = FastTweenColor(color & 0xFFFFFF, color, state[5]);
            qcopy(&quad.pos[i], &D_L03_001B0120[0]);
            if (side) ((float *)&quad.pos[i])[2] -= intensity * 0.1f + 0.5f;
            matrix_mul_vec3(&quad.pos[i], &quad.pos[i], rotation);
        }
    }
    angle[0] = -0.06544984877109528f;
    euler_rotation_basis(rotation, angle);
    matrix_mul_vec3(&quad.pos[2], &quad.pos[2], rotation);
    matrix_mul_vec3(&quad.pos[3], &quad.pos[3], rotation);
    multiply_matrix3x3(rotation, rotation, rotation);
    {
        int i, j;
        for (i = 0; i < 16; i++) {
            j = (i & 1) ? 2 : 0;
            matrix_mul_vec3(&quad.pos[j], &quad.pos[j], rotation);
            matrix_mul_vec3(&quad.pos[j+1], &quad.pos[j+1], rotation);
            draw_world_quad(&quad, world_matrix, 1);
        }
    }
    {
        int i;
        for (i = 0; i < 4; i++)
            ((float *)&quad.pos[i])[2] = -((float *)&quad.pos[i])[2];
    }
    {
        int i, j;
        for (i = 0; i < 16; i++) {
            j = (i & 1) ? 0 : 2;
            matrix_mul_vec3(&quad.pos[j], &quad.pos[j], rotation);
            matrix_mul_vec3(&quad.pos[j+1], &quad.pos[j+1], rotation);
            draw_world_quad(&quad, world_matrix, 1);
        }
    }
    quad.tex = GetEffectTextureDescriptor(D_L03_001B0078);
    angle[0] = state[2];
    euler_rotation_basis(rotation, angle);
    {
        int i, color;
        for (i = 0; i < 4; i++) {
            quad.uv[i].u = D_L03_001B00C8[i*2];
            quad.uv[i].v = D_L03_001B00CC[i*2];
            color = D_L03_001B0108[i];
            quad.color[i] = FastTweenColor(color & 0xFFFFFF, color, state[5]);
            qcopy(&quad.pos[i], &D_L03_001B0120[0]);
            ((float *)&quad.pos[i])[2] = D_L03_001B0060[i&1];
            matrix_mul_vec3(&quad.pos[i], &quad.pos[i], rotation);
        }
    }
    angle[0] = 0.15707963705062866f;
    euler_rotation_basis(rotation, angle);
    matrix_mul_vec3(&quad.pos[2], &quad.pos[2], rotation);
    matrix_mul_vec3(&quad.pos[3], &quad.pos[3], rotation);
    multiply_matrix3x3(rotation, rotation, rotation);
    {
        int i, j;
        for (i = 0; i < 20; i++) {
            j = (i & 1) ? 2 : 0;
            matrix_mul_vec3(&quad.pos[j], &quad.pos[j], rotation);
            matrix_mul_vec3(&quad.pos[j+1], &quad.pos[j+1], rotation);
            draw_world_quad(&quad, world_matrix, 1);
        }
    }
    angle[0] = state[3];
    euler_rotation_basis(rotation, angle);
    {
        int i;
        for (i = 0; i < 4; i++) {
            qcopy(&quad.pos[i], &D_L03_001B0120[0]);
            ((float *)&quad.pos[i])[2] = D_L03_001B0060[(i&1)+2];
            matrix_mul_vec3(&quad.pos[i], &quad.pos[i], rotation);
        }
    }
    angle[0] = 0.15707963705062866f;
    euler_rotation_basis(rotation, angle);
    matrix_mul_vec3(&quad.pos[2], &quad.pos[2], rotation);
    matrix_mul_vec3(&quad.pos[3], &quad.pos[3], rotation);
    multiply_matrix3x3(rotation, rotation, rotation);
    {
        int i, j;
        for (i = 0; i < 20; i++) {
            j = (i & 1) ? 2 : 0;
            matrix_mul_vec3(&quad.pos[j], &quad.pos[j], rotation);
            matrix_mul_vec3(&quad.pos[j+1], &quad.pos[j+1], rotation);
            draw_world_quad(&quad, world_matrix, 1);
        }
    }
}
