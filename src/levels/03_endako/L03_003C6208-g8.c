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

extern void func_00283658(void *, void *);
extern void func_L03_002EFB60(void *, void *, float);
extern float func_00283198(float);
extern u64 func_0027C878(int);
extern int func_00283D38(int, int, float);
extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
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

void func_L03_003C6208(char *object)
{
    Packet packet;
    float rot[12];
    float world[16];
    float angle[4];
    float *state = *(float **)(object + 0x68);
    float blend, intensity;

    copy_matrix_rotation(world, object + 0xC0);
    if (state[0] != 1.0f)
        func_L03_002EFB60(world, world, state[0]);
    qcopy(&world[12], object + 0x10);
    world[15] = 1.0f;
    blend = func_00283198(state[1]) * 0.5f + 0.5f;
    intensity = func_00283198(state[4]) * 0.5f + 0.5f;
    packet.tex = GetEffectTextureDescriptor(D_L03_001B0070);
    packet.mode = ((u64)D_L03_001B007C << 2) |
        ((u64)D_L03_001B0080 << 6) | ((u64)0x8000 << 24);
    packet.regs = 0x0000FF9000000260ULL;
    packet.tag = 0;
    {
        int i, color, side;
        for (i = 0; i < 4; i++) {
            side = i & 1;
            packet.uv[i].u = D_L03_001B0088[i*2];
            packet.uv[i].v = D_L03_001B008C[i*2];
            color = FastTweenColor(D_L03_001B00E8[side], D_L03_001B00E8[side+2], blend);
            packet.color[i] = color;
            packet.color[i] = FastTweenColor(color & 0xFFFFFF, color, state[5]);
            qcopy(&packet.pos[i], &D_L03_001B0120[side]);
        }
    }
    *(TI128 *)angle = 0;
    angle[0] = 0.19634954631328583f;
    euler_rotation_basis(rot, angle);
    matrix_mul_vec3(&packet.pos[2], &packet.pos[2], rot);
    matrix_mul_vec3(&packet.pos[3], &packet.pos[3], rot);
    multiply_matrix3x3(rot, rot, rot);
    {
        int i, j;
        for (i = 0; (float)i < 32.0f; i++) {
            j = (i & 1) ? 2 : 0;
            matrix_mul_vec3(&packet.pos[j], &packet.pos[j], rot);
            matrix_mul_vec3(&packet.pos[j+1], &packet.pos[j+1], rot);
            draw_world_quad(&packet, world, 1);
        }
    }
    packet.tex = GetEffectTextureDescriptor(D_L03_001B0074);
    angle[0] = 0.5235987901687622f;
    euler_rotation_basis(rot, angle);
    {
        int i, color, side;
        for (i = 0; i < 4; i++) {
            side = i & 1;
            packet.uv[i].u = D_L03_001B00A8[i*2];
            packet.uv[i].v = D_L03_001B00AC[i*2];
            color = FastTweenColor(D_L03_001B00F8[side], D_L03_001B00F8[side+2], intensity);
            packet.color[i] = color;
            packet.color[i] = FastTweenColor(color & 0xFFFFFF, color, state[5]);
            qcopy(&packet.pos[i], &D_L03_001B0120[0]);
            if (side) ((float *)&packet.pos[i])[2] -= intensity * 0.1f + 0.5f;
            matrix_mul_vec3(&packet.pos[i], &packet.pos[i], rot);
        }
    }
    angle[0] = -0.06544984877109528f;
    euler_rotation_basis(rot, angle);
    matrix_mul_vec3(&packet.pos[2], &packet.pos[2], rot);
    matrix_mul_vec3(&packet.pos[3], &packet.pos[3], rot);
    multiply_matrix3x3(rot, rot, rot);
    {
        int i, j;
        for (i = 0; i < 16; i++) {
            j = (i & 1) ? 2 : 0;
            matrix_mul_vec3(&packet.pos[j], &packet.pos[j], rot);
            matrix_mul_vec3(&packet.pos[j+1], &packet.pos[j+1], rot);
            draw_world_quad(&packet, world, 1);
        }
    }
    {
        int i;
        for (i = 0; i < 4; i++)
            ((float *)&packet.pos[i])[2] = -((float *)&packet.pos[i])[2];
    }
    {
        int i, j;
        for (i = 0; i < 16; i++) {
            j = (i & 1) ? 0 : 2;
            matrix_mul_vec3(&packet.pos[j], &packet.pos[j], rot);
            matrix_mul_vec3(&packet.pos[j+1], &packet.pos[j+1], rot);
            draw_world_quad(&packet, world, 1);
        }
    }
    packet.tex = GetEffectTextureDescriptor(D_L03_001B0078);
    angle[0] = state[2];
    euler_rotation_basis(rot, angle);
    {
        int i, color;
        for (i = 0; i < 4; i++) {
            packet.uv[i].u = D_L03_001B00C8[i*2];
            packet.uv[i].v = D_L03_001B00CC[i*2];
            color = D_L03_001B0108[i];
            packet.color[i] = FastTweenColor(color & 0xFFFFFF, color, state[5]);
            qcopy(&packet.pos[i], &D_L03_001B0120[0]);
            ((float *)&packet.pos[i])[2] = D_L03_001B0060[i&1];
            matrix_mul_vec3(&packet.pos[i], &packet.pos[i], rot);
        }
    }
    angle[0] = 0.15707963705062866f;
    euler_rotation_basis(rot, angle);
    matrix_mul_vec3(&packet.pos[2], &packet.pos[2], rot);
    matrix_mul_vec3(&packet.pos[3], &packet.pos[3], rot);
    multiply_matrix3x3(rot, rot, rot);
    {
        int i, j;
        for (i = 0; i < 20; i++) {
            j = (i & 1) ? 2 : 0;
            matrix_mul_vec3(&packet.pos[j], &packet.pos[j], rot);
            matrix_mul_vec3(&packet.pos[j+1], &packet.pos[j+1], rot);
            draw_world_quad(&packet, world, 1);
        }
    }
    angle[0] = state[3];
    euler_rotation_basis(rot, angle);
    {
        int i;
        for (i = 0; i < 4; i++) {
            qcopy(&packet.pos[i], &D_L03_001B0120[0]);
            ((float *)&packet.pos[i])[2] = D_L03_001B0060[(i&1)+2];
            matrix_mul_vec3(&packet.pos[i], &packet.pos[i], rot);
        }
    }
    angle[0] = 0.15707963705062866f;
    euler_rotation_basis(rot, angle);
    matrix_mul_vec3(&packet.pos[2], &packet.pos[2], rot);
    matrix_mul_vec3(&packet.pos[3], &packet.pos[3], rot);
    multiply_matrix3x3(rot, rot, rot);
    {
        int i, j;
        for (i = 0; i < 20; i++) {
            j = (i & 1) ? 2 : 0;
            matrix_mul_vec3(&packet.pos[j], &packet.pos[j], rot);
            matrix_mul_vec3(&packet.pos[j+1], &packet.pos[j+1], rot);
            draw_world_quad(&packet, world, 1);
        }
    }
}
