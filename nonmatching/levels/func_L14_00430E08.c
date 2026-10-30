/* func_L14_00430E08: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections -g -frac2-qcopy.
   924/920 bytes; local checks reject every carrying release.
   Full 0x90 draw packet and four complete 16-byte vectors reconstructed. A cached age scalar initially gave 900 bytes; measured fresh age reads across the transform calls give 924. Grouped TI copy ties the helper variant. Allocation keeps one extra FP constant, grows the frame to 0x150 rather than 0x140, and schedules addresses differently.
   No linked match is claimed.
*/

#include "common.h"
typedef s32 Quad __attribute__((mode(TI)));
typedef struct { f32 matrix[16]; u32 color[4]; f32 uv[8]; u64 state[4]; } Packet;
typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
extern f32 D_L14_00260270[], D_L14_002602F0[];
extern u8 D_L14_001B9500[], D_0018A0E0[];
extern f32 func_002A7878(f32, f32);
extern void func_00281DE8(void *, s32, s32, s32);
extern void func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, f32);
extern u32 func_00283D38(u32, u32, f32);
extern void func_002ACEC0(void *, void *, void *, f32), func_00282DD8(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *), func_00280B90(void *, void *, s32);
extern void func_002FC560(s32, u64);

void func_L14_00430E08(u8 *object)
{
    Packet packet;
    Vector difference, rotated, width, up;
    u8 *state = *(u8 **)(object + 0x68);
    f32 taper;
    u32 color;
    s32 i, j;
    for (i = 0; i < 32; i++) {
        D_L14_002602F0[i] += 1.0f / (f32)*(s32 *)(state + 0xA8);
        if (D_L14_002602F0[i] > 1.0f) {
            D_L14_002602F0[i] = 0.0f;
            D_L14_00260270[i] = func_002A7878(-1.5707964f, 1.5707964f);
        }
    }
    func_00281DE8(&packet, *(s32 *)(state + 0xB0), 1, 0x80);
    packet.state[0] = 5;
    packet.uv[0] = 0.0f; packet.uv[1] = 0.0f; packet.uv[2] = 0.0f; packet.uv[3] = 1.0f;
    packet.uv[4] = 1.0f; packet.uv[5] = 0.0f; packet.uv[6] = 1.0f; packet.uv[7] = 1.0f;
    func_00282CF0(&difference, D_L14_001B9500, object + 0x10);
    func_00282F20(&difference, &difference, *(f32 *)(state + 0x80) * 0.5f);
    func_00282F20(&up, D_0018A0E0, -1.0f);
    for (i = 0; i < 32; i++) {
        if (D_L14_002602F0[i] > *(f32 *)(state + 0xAC)) color = *(u32 *)(state + 0x98);
        else color = func_00283D38(*(u32 *)(state + 0x94), *(u32 *)(state + 0x98), D_L14_002602F0[i] / *(f32 *)(state + 0xAC));
        packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
        func_002ACEC0(&rotated, &up, &difference, D_L14_00260270[i]);
        func_00282DD8(&width, &up, &rotated);
        func_00282F20(&width, &width, *(f32 *)(state + 0xB4) * (1.0f - D_L14_002602F0[i]));
        taper = *(f32 *)(state + 0xA4) + D_L14_002602F0[i] * (*(f32 *)(state + 0xA0) - *(f32 *)(state + 0xA4));
        if (taper > 1.0f) taper = 1.0f;
        func_002FC560(0x47, 0x53001UL);
        for (j = 0; j < 4; j++) {
            *(Quad *)(packet.matrix + j * 4) = *(Quad *)(object + 0x10);
            if (j >= 2) func_00282CC0(packet.matrix + j * 4, packet.matrix + j * 4, &width);
            else func_00282CF0(packet.matrix + j * 4, packet.matrix + j * 4, &width);
            if (!(j & 1)) func_00282F20(&rotated, &rotated, *(f32 *)(state + 0x80) * (1.0f - taper));
            else func_00282F20(&rotated, &rotated, *(f32 *)(state + 0x80));
            func_00282CC0(packet.matrix + j * 4, packet.matrix + j * 4, &rotated);
            packet.color[j] = *(u32 *)(state + 0xC);
            func_00282CC0(packet.matrix + j * 4, packet.matrix + j * 4, &difference);
        }
        func_00280B90(&packet, 0, 0);
    }
    func_002FC560(0x47, 0x5360BUL);
}
