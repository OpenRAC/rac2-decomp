/* func_L07_003B72E8: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections -g -frac2-zero-ti-por.
   Two complete draw packets, four-vector basis and explicit reused UV/color scratch union. The corrected catalogue entry starts at +8. Packet-loop allocation and scheduling remain.
   No linked match is claimed.
*/

#include "common.h"
typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
typedef struct { f32 matrix[16]; u32 color[4]; f32 uv[8]; u64 state[4]; } Packet;
typedef struct {
    Vector basis[4];
    Packet packets[2];
    f32 scroll[2];
    Vector points[2];
    union { Vector uv[2]; u32 colors[2]; } scratch;
} Frame;
extern f32 func_002A7878(f32, f32), func_002A7940(void), func_00283CE0(s32);
extern u32 func_00283D38(u32, u32, f32);
extern void func_00281EB8(void *, s32, u32, s32, f32, f32, f32);
extern void func_00282C98(void *), func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32), func_00282DD8(void *, void *, void *);
extern void func_00281DE8(void *, s32, s32, s32), func_00280B90(void *, void *, s32);
extern u8 D_L07_001B9200[];
extern f32 D_L07_001AFF00[] SDATA(D_L07_001AFF00), D_L07_001AFF04[];
extern s32 D_L07_001AFF20 __attribute__((sda));
extern f32 D_L07_001AFF24 __attribute__((sda)), D_L07_001AFF28 __attribute__((sda));
extern u32 D_L07_001AFF30 __attribute__((sda)), D_L07_001AFF34;

void func_L07_003B72E8(u8 *object)
{
    Frame frame;
    u8 *state = *(u8 **)(object + 0x68);
    u32 color;
    f32 angle, inverse, alpha, nextAlpha;
    s32 i, j, k;
    color = func_00283D38(0x50103080, 0x60103080, func_002A7878(0.0f, 1.0f));
    angle = func_002A7940();
    func_00281EB8(object + 0x10, 0x31, color, 1, 1.0f, 0.0f, angle);
    color = func_00283D38(0x50FFFFFF, 0x60FFFFFF, func_002A7878(0.0f, 1.0f));
    angle = func_002A7940();
    func_00281EB8(object + 0x10, 0x31, color, 1, 0.6f, 0.0f, angle);
    color = func_00283D38(0x08803010, 0x18803010, func_002A7878(0.0f, 1.0f));
    angle = func_002A7940();
    func_00281EB8(object + 0x10, 11, color, 1, 1.4f, 0.0f, angle);
    color = func_00283D38(0x20803010, 0x40803010, func_002A7878(0.0f, 1.0f));
    angle = func_002A7940();
    func_00281EB8(object + 0x10, 11, color, 1, 0.9f, 0.0f, angle);
    qcopy(&frame.basis[3], object + 0x10);
    frame.basis[3].f[3] = 1.0f;
    func_00282C98(&frame.basis[2]);
    func_00282CF0(&frame.basis[1], D_L07_001B9200, object + 0x10);
    frame.basis[1].f[2] = 0.0f;
    func_00282F20(&frame.basis[1], &frame.basis[1], 1.0f);
    func_00282DD8(&frame.basis[0], &frame.basis[1], &frame.basis[2]);
    func_00281DE8(&frame.packets[0], 0x2F, 1, 0x80);
    func_00281DE8(&frame.packets[1], 0x2F, 1, 0x80);
    frame.scroll[0] = *(f32 *)(state + 0x30);
    frame.scroll[1] = *(f32 *)(state + 0x30) + 0.5f;
    if (frame.scroll[1] > 1.0f) frame.scroll[1] -= 1.0f;
    frame.scratch.uv[1].q = 0;
    frame.scratch.uv[0].q = 0;
    frame.scratch.uv[1].f[3] = 1.0f;
    frame.scratch.uv[0].f[3] = 1.0f;
    frame.scratch.uv[0].f[0] = D_L07_001AFF28 * frame.scroll[0];
    frame.scratch.uv[1].f[0] = D_L07_001AFF28 * frame.scroll[1];
    qcopy(&frame.points[0], &frame.scratch.uv[0]);
    qcopy(&frame.points[1], &frame.scratch.uv[1]);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            qcopy(frame.packets[j].matrix + i * 4, &frame.points[j]);
            if (i & 1) frame.packets[j].matrix[i * 4] = -frame.packets[j].matrix[i * 4];
            frame.packets[j].uv[i * 2] = D_L07_001AFF00[i * 2] + (*(f32 *)(state + 0x2C) + (f32)j * 0.5f);
            frame.packets[j].uv[i * 2 + 1] = D_L07_001AFF04[i * 2];
        }
    }
    inverse = 1.0f / func_00283CE0(D_L07_001AFF20);
    frame.scratch.colors[0] = func_00283D38(D_L07_001AFF30, D_L07_001AFF34, frame.scroll[0]);
    frame.scratch.colors[1] = func_00283D38(D_L07_001AFF30, D_L07_001AFF34, frame.scroll[1]);
    if (*(f32 *)(state + 0x34) < 1.0f) {
        frame.scratch.colors[0] = func_00283D38(frame.scratch.colors[0] & 0xFFFFFF, frame.scratch.colors[0], *(f32 *)(state + 0x34));
        frame.scratch.colors[1] = func_00283D38(frame.scratch.colors[1] & 0xFFFFFF, frame.scratch.colors[1], *(f32 *)(state + 0x34));
    }
    alpha = 1.0f;
    for (k = 0; k < D_L07_001AFF20; k++) {
        nextAlpha = alpha - inverse;
        for (j = 0; j < 2; j++) {
            Packet *packet = &frame.packets[j];
            packet->matrix[10] -= D_L07_001AFF24;
            packet->matrix[14] -= D_L07_001AFF24;
            color = func_00283D38(frame.scratch.colors[j] & 0xFFFFFF, frame.scratch.colors[j], alpha);
            packet->color[0] = color; packet->color[1] = color;
            color = func_00283D38(frame.scratch.colors[j] & 0xFFFFFF, frame.scratch.colors[j], nextAlpha);
            packet->color[2] = color; packet->color[3] = color;
            func_00280B90(packet, frame.basis, 0);
            packet->matrix[2] -= D_L07_001AFF24;
            packet->matrix[6] -= D_L07_001AFF24;
        }
        alpha = nextAlpha;
    }
}
