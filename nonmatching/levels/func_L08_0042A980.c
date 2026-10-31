/* func_L08_0042A980: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections.
   Full 0x90 packet plus a complete 64-byte transform: its position is the fourth row, not a separate undersized object. Explicit four-color stores reduced 1316 to 1212 bytes. Loop/allocation differences remain; GS state and texture values retain 64 bits.
   No linked match is claimed.
*/

#include "common.h"
typedef struct { f32 matrix[16]; u32 color[4]; f32 uv[8]; u64 state[4]; } Packet;
typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
typedef struct { Packet packet; f32 matrix[16]; Vector jitter; } Frame;
extern u8 D_L08_00260410[], D_L08_001B9B00[], D_0018A0E0[], D_L08_001B3A70[];
extern f32 D_L08_001B1CE0[][4] SDATA(D_L08_001B1CE0);
extern void func_00282CF0(void *, void *, void *), func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, f32), func_00282D30(void *, void *, f32);
extern void func_002830C0(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern u64 func_0027C878(s32);
extern f32 func_002A7878(f32, f32), func_002A78D8(f32, f32);
extern s32 func_L02_002F1658(void);
extern void func_00280B90(void *, void *, s32);

/* The position is the fourth row of the complete transform consumed below. */
void func_L08_0042A980(void *entry, s32 index)
{
    Frame frame;
    f32 scale;
    s32 i;
    qcopy(frame.matrix + 12, D_L08_00260410 + index * 0x40);
    frame.matrix[15] = 1.0f;
    func_00282CF0(frame.matrix, D_L08_001B9B00, frame.matrix + 12);
    func_00282F20(frame.matrix, frame.matrix, 1.0f);
    func_00282DD8(frame.matrix + 4, frame.matrix, D_0018A0E0);
    func_00282F20(frame.matrix + 4, frame.matrix + 4, -1.0f);
    func_00282DD8(frame.matrix + 8, frame.matrix + 4, frame.matrix);
    frame.packet.state[1] = func_0027C878(11);
    frame.packet.state[3] = 0xFF00000044UL;
    frame.packet.state[2] = 0xFF9000000260UL;
    frame.packet.state[0] = 5;
    frame.packet.color[0] = frame.packet.color[1] = frame.packet.color[2] = frame.packet.color[3] = -1;
    frame.packet.uv[0] = 0.0f; frame.packet.uv[1] = 0.0f;
    frame.packet.uv[2] = 0.0f; frame.packet.uv[3] = 1.0f;
    frame.packet.uv[4] = 1.0f; frame.packet.uv[5] = 0.0f;
    frame.packet.uv[6] = 1.0f; frame.packet.uv[7] = 1.0f;
    scale = func_002A7878(0.3f, 0.325f);
    if (!func_L02_002F1658()) scale = 0.3125f;
    frame.jitter.f[0] = func_002A78D8(0.0f, 0.05f);
    frame.jitter.f[1] = func_002A78D8(0.0f, 0.05f);
    frame.jitter.f[2] = func_002A78D8(0.0f, 0.05f);
    if (!func_L02_002F1658()) {
        frame.jitter.f[2] = 0.025f;
        frame.jitter.f[0] = 0.025f;
        frame.jitter.f[1] = 0.025f;
    }
    for (i = 3; i >= 0; i--) {
        s32 row = 3 - i;
        func_00282D30(frame.packet.matrix + row * 4, D_L08_001B1CE0[row], scale);
        func_002830C0(frame.packet.matrix + row * 4, frame.packet.matrix + row * 4, frame.matrix);
        func_00282CC0(frame.packet.matrix + row * 4, frame.packet.matrix + row * 4, &frame.jitter);
    }
    func_00280B90(&frame.packet, 0, 0);
    frame.packet.state[3] = 0xFF00000048UL;
    frame.packet.color[0] = frame.packet.color[1] = frame.packet.color[2] = frame.packet.color[3] = 0x60FF10FF;
    for (i = 3; i >= 0; i--) {
        s32 row = 3 - i;
        func_00282D30(frame.packet.matrix + row * 4, D_L08_001B1CE0[row], scale * 3.0f);
        func_002830C0(frame.packet.matrix + row * 4, frame.packet.matrix + row * 4, frame.matrix);
    }
    func_00280B90(&frame.packet, 0, 0);
    qcopy(frame.matrix + 12, D_L08_001B3A70 + index * 0x10);
    func_00282CF0(frame.matrix, D_L08_001B9B00, frame.matrix + 12);
    func_00282F20(frame.matrix, frame.matrix, 1.0f);
    func_00282DD8(frame.matrix + 4, frame.matrix, D_0018A0E0);
    func_00282F20(frame.matrix + 4, frame.matrix + 4, -1.0f);
    func_00282DD8(frame.matrix + 8, frame.matrix + 4, frame.matrix);
    scale = func_002A7878(0.2f, 0.225f);
    if (!func_L02_002F1658()) scale = 0.2225f;
    frame.packet.state[3] = 0xFF00000044UL;
    frame.packet.color[0] = frame.packet.color[1] = frame.packet.color[2] = frame.packet.color[3] = -1;
    for (i = 3; i >= 0; i--) {
        s32 row = 3 - i;
        func_00282D30(frame.packet.matrix + row * 4, D_L08_001B1CE0[row], scale);
        func_002830C0(frame.packet.matrix + row * 4, frame.packet.matrix + row * 4, frame.matrix);
        func_00282CC0(frame.packet.matrix + row * 4, frame.packet.matrix + row * 4, &frame.jitter);
    }
    func_00280B90(&frame.packet, 0, 0);
    frame.packet.state[3] = 0xFF00000048UL;
    frame.packet.color[0] = frame.packet.color[1] = frame.packet.color[2] = frame.packet.color[3] = 0x60FF10FF;
    for (i = 3; i >= 0; i--) {
        s32 row = 3 - i;
        func_00282D30(frame.packet.matrix + row * 4, D_L08_001B1CE0[row], scale * 3.0f);
        func_002830C0(frame.packet.matrix + row * 4, frame.packet.matrix + row * 4, frame.matrix);
    }
    func_00280B90(&frame.packet, 0, 0);
}
