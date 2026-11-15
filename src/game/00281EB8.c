#include "common.h"

typedef union { int q __attribute__((mode(TI))); f32 f[4]; } Vector;
typedef struct { f32 matrix[16]; u32 color[4]; f32 uv[8]; u64 state[4]; } Packet;
typedef struct { Packet packet; Vector basis[3]; Vector position; Vector euler; Vector rotation[3]; } DrawFrame;
extern void gfx_init_quad_packet_state(Packet *, s32, s32, s32);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecCross(void *, void *, void *);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void FastVecScale(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(Packet *, s32, s32);
extern u8 g_camera_eye_state[];
extern u8 D_0018A0E0[];
extern f32 D_001A9FD0[][4];

/* Draws a camera-facing textured square at a position, with size, offset and an optional spin. */
void gfx_draw_billboard_quad(void *position, s32 texture, u32 color, s32 kind,
                   f32 scale, f32 offset, f32 angle)
{
    DrawFrame frame;
    s32 i;
    gfx_init_quad_packet_state(&frame.packet, texture, kind, 0x80);
    frame.packet.color[3] = color;
    frame.packet.color[2] = color;
    frame.packet.color[1] = color;
    frame.packet.color[0] = color;
    frame.packet.uv[0] = 0.0f;
    frame.packet.uv[1] = 0.0f;
    frame.packet.uv[2] = 0.0f;
    frame.packet.uv[3] = 1.0f;
    frame.packet.uv[4] = 1.0f;
    frame.packet.uv[5] = 0.0f;
    frame.packet.uv[6] = 1.0f;
    frame.packet.uv[7] = 1.0f;
    qcopy(&frame.position, position);
    FastVecSub(&frame.basis[0], g_camera_eye_state, &frame.position);
    vec_scale_to_length(&frame.basis[0], &frame.basis[0], 1.0f);
    FastVecCross(&frame.basis[1], &frame.basis[0], D_0018A0E0);
    vec_scale_to_length(&frame.basis[1], &frame.basis[1], 1.0f);
    FastVecCross(&frame.basis[2], &frame.basis[1], &frame.basis[0]);
    if (angle != 0.0f) {
        frame.euler.q = 0;
        frame.euler.f[0] = angle;
        euler_rotation_basis(frame.rotation, &frame.euler);
        multiply_matrix3x3(frame.basis, frame.basis, frame.rotation);
    }
    FastVecScale(&frame.euler, &frame.basis[0], offset);
    FastVecAdd(&frame.position, &frame.position, &frame.euler);
    for (i = 3; i >= 0; i--) {
        s32 row = 3 - i;
        FastVecScale(frame.packet.matrix + row * 4, D_001A9FD0[row], scale);
        transform_vector(frame.packet.matrix + row * 4, frame.packet.matrix + row * 4, frame.basis);
    }
    draw_world_quad(&frame.packet, 0, 0);
}
