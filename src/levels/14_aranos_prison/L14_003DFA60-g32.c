#include "common.h"

/* Own unit: the 32-byte D_L14_001B03B8 table is gp-relative only under -G32. */
typedef int Quad128 __attribute__((mode(TI)));
typedef union { float f[4]; Quad128 q; } Vec;
typedef struct { Vec pos[4]; u32 color[4]; float uv[4][2]; char tail[24]; u64 regs; } DrawPacket;

extern unsigned char *g_moby_l14_pool[] __attribute__((sda));
extern unsigned char D_001A7A44[] __attribute__((sda));
extern float D_L14_001B03BC[];
extern float D_L14_001B03B8[8] __attribute__((sda));
extern int D_L14_001B0394 __attribute__((sda));
extern float D_L14_001B039C __attribute__((sda));
extern float D_L14_001B03A0 __attribute__((sda));
extern float D_L14_001B03A4 __attribute__((sda));
extern float D_L14_001B03A8 __attribute__((sda));
extern int D_L14_001B03AC __attribute__((sda));
extern float D_L14_001B03B0 __attribute__((sda));
extern int moby_get_count_in_state_two(void *);
extern void copy_matrix_rotation(void *, void *);
extern void func_L03_002EFB60(void *, void *, float);
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void vec_scale_to_length(void *, void *, float);
extern void draw_world_quad(void *, void *, int);

/* Draws a four-corner billboard that shows one frame of a strip of pictures. */
void gfx_draw_flipbook_billboard(char *self) {
    float mtx[16] __attribute__((aligned(16)));
    DrawPacket packet __attribute__((aligned(16)));
    int frame, i;
    float angle, u, u_coord;
    float *vertex, *tex_coord, *uv_table, *u_table;
    frame = moby_get_count_in_state_two(g_moby_l14_pool[0] + (*(int *)(*(char **)(self + 0x68) + 4) << 8));
    copy_matrix_rotation(mtx, self + 0xC0);
    func_L03_002EFB60(mtx, mtx, *(float *)(self + 0x2C) / *(float *)(*(char **)(self + 0x24) + 0x24));
    qcopy(mtx + 12, self + 0x10);
    mtx[15] = 1.0f;
    gfx_init_quad_packet_state(packet.pos, D_L14_001B0394, 0, 0x80);
    uv_table = D_L14_001B03BC;
    u_table = D_L14_001B03B8;
    for (i = 0; i < 4; i++, u_table += 2) {
        angle = FastAddRotations(D_L14_001B03A0 * 0.01745329424738884f, (float)i * 1.5707964f);
        packet.pos[i].f[0] = math_fast_sin_or_cos_a(angle) * D_L14_001B03A4;
        packet.pos[i].f[1] = math_fast_sin_or_cos_b(angle) * D_L14_001B03A4;
        packet.pos[i].f[2] = 0;
        qzero_nc(&packet.pos[i]);
        packet.pos[i].f[1] = (i >= 2) ? -1.0f : 1.0f;
        if (i & 1)
            packet.pos[i].f[2] = -1.0f;
        else
            packet.pos[i].f[2] = 1.0f;
        vertex = packet.pos[i].f;
        if (D_001A7A44[0])
            vertex[1] = -vertex[1];
        vec_scale_to_length(vertex, vertex, D_L14_001B03A4);
        vertex[0] = D_L14_001B03A8;
        vertex[3] = 1.0f;
        vertex[2] += D_L14_001B03B0;
        packet.color[i] = D_L14_001B03AC;
        tex_coord = packet.uv[i];
        u = *u_table;
        tex_coord[0] = u;
        if (i < 2)
            u_coord = u + (float)frame / D_L14_001B039C;
        else
            u_coord = u + (float)(frame + 1) / D_L14_001B039C;
        tex_coord[0] = u_coord;
        packet.uv[i][1] = *uv_table;
        uv_table += 2;
    }
    draw_world_quad(&packet, mtx, 0);
}
