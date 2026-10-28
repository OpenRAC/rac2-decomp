#include "common.h"

typedef union { int q __attribute__((mode(TI))); f32 f[4]; } Vector;
typedef struct { f32 matrix[16]; u32 color[4]; f32 uv[8]; u64 state[4]; } Packet;
typedef struct { Packet packet; Vector basis[3]; Vector position; Vector euler; Vector rotation[3]; } DrawFrame;
extern void func_00281DE8(Packet *, s32, s32, s32);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282DD8(void *, void *, void *);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00282D30(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(Packet *, s32, s32);
extern u8 D_001B5340[];
extern u8 D_0018A0E0[];
extern f32 D_001A9FD0[][4];

void func_00281EB8(void *position, s32 texture, u32 color, s32 kind,
                   f32 scale, f32 offset, f32 angle)
{
    DrawFrame frame;
    s32 i;
    func_00281DE8(&frame.packet, texture, kind, 0x80);
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
    func_00282CF0(&frame.basis[0], D_001B5340, &frame.position);
    func_00282F20(&frame.basis[0], &frame.basis[0], 1.0f);
    func_00282DD8(&frame.basis[1], &frame.basis[0], D_0018A0E0);
    func_00282F20(&frame.basis[1], &frame.basis[1], 1.0f);
    func_00282DD8(&frame.basis[2], &frame.basis[1], &frame.basis[0]);
    if (angle != 0.0f) {
        frame.euler.q = 0;
        frame.euler.f[0] = angle;
        func_002833F0(frame.rotation, &frame.euler);
        func_00283738(frame.basis, frame.basis, frame.rotation);
    }
    func_00282D30(&frame.euler, &frame.basis[0], offset);
    func_00282CC0(&frame.position, &frame.position, &frame.euler);
    for (i = 3; i >= 0; i--) {
        s32 row = 3 - i;
        func_00282D30(frame.packet.matrix + row * 4, D_001A9FD0[row], scale);
        func_002830C0(frame.packet.matrix + row * 4, frame.packet.matrix + row * 4, frame.basis);
    }
    func_00280B90(&frame.packet, 0, 0);
}
