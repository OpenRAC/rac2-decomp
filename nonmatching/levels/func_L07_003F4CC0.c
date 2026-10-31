/* func_L07_003F4CC0: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections -fno-force-mem.
   Local checks: 1120/1124 bytes, 0/1 in each of USA v1.01, v2.00 and PAL.
   No strict linked match is claimed.

   The full 0x90 draw packet and all surrounding vectors fit the measured
   0x1A0 frame. Matrix/UV loop allocation and scheduling still differ. Default
   -G8 gives 1104 bytes; -g with -fno-force-mem gives 1128, also nonmatching.
*/

#include "common.h"

typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
typedef struct { f32 matrix[16]; u32 color[4]; f32 uv[8]; u64 state[4]; } Packet;
typedef struct { Vector first, second, difference, view, normal, position; Packet packet; Vector cursor, step; } Frame;
extern void func_L07_003F4C18(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00281DE8(void *, s32, s32, s32);
extern u32 func_00283D38(u32, u32, f32);
extern void func_00280B90(void *, void *, s32);
extern f32 func_00282DF0(void *);
extern void func_00281EB8(void *, s32, u32, s32, f32, f32, f32);
extern f32 func_00283B98(f32, f32);
extern void func_00282CC0(void *, void *, void *);
extern u8 D_L07_001B9200[];
extern u32 D_L07_001B0EA8 __attribute__((sda));
extern u32 D_L07_001B0EAC;
extern s32 D_L07_001B0EB0 __attribute__((sda));
extern f32 D_L07_001B0EB8 __attribute__((sda));
extern f32 D_L07_001B0EBC;
extern f32 D_L07_001B0EC0 __attribute__((sda));
extern f32 D_L07_001B0EC8 __attribute__((sda));
extern f32 D_L07_001B0ECC;
extern u32 D_L07_001B0ED0 __attribute__((sda));
extern u32 D_L07_001B0ED4;
extern f32 D_L07_001B0ED8 __attribute__((sda));
extern f32 D_L07_001B0EDC __attribute__((sda));
extern f32 D_L07_001B0EE0[] SDATA(D_L07_001B0EE0);
extern f32 D_L07_001B0EE4[];

/* Draw the connecting quad and the alternating paired effects along its length. */
void func_L07_003F4CC0(u8 *object)
{
    Frame frame;
    u8 *state = *(u8 **)(object + 0x68);
    s32 i;
    u32 color;
    f32 length, count, intensity, angle, scale;

    func_L07_003F4C18(object, &frame.first, &frame.second);
    func_00282CF0(&frame.difference, &frame.second, &frame.first);
    func_00282CF0(&frame.view, D_L07_001B9200, object + 0x10);
    func_00282DD8(&frame.normal, &frame.view, &frame.difference);
    func_00282F20(&frame.normal, &frame.normal, 1.0f);
    qzero(&frame.view);
    qcopy(&frame.position, &frame.first);
    frame.position.f[3] = 1.0f;
    func_00281DE8(&frame.packet, D_L07_001B0EB0, 1, 0x80);
    color = func_00283D38(D_L07_001B0EA8 & 0xFFFFFF, D_L07_001B0EA8, *(f32 *)(state + 0x24));
    for (i = 0; i < 4; i++) {
        frame.packet.uv[i * 2] = D_L07_001B0EE0[i * 2] + 0.0f;
        frame.packet.uv[i * 2 + 1] = D_L07_001B0EE4[i * 2];
        qzero(&frame.packet.matrix[i * 4]);
        frame.packet.matrix[i * 4] = i < 2 ? 0.0f : 1.0f;
        frame.packet.matrix[i * 4 + 2] = D_L07_001B0EB8;
        if (!(i & 1))
            frame.packet.matrix[i * 4 + 2] = -D_L07_001B0EB8;
        frame.packet.matrix[i * 4 + 3] = 1.0f;
        frame.packet.color[i] = color;
    }
    func_00280B90(&frame.packet, &frame.difference, 0);
    color = func_00283D38(D_L07_001B0EAC & 0xFFFFFF, D_L07_001B0EAC, *(f32 *)(state + 0x24));
    for (i = 0; i < 4; i++) {
        frame.packet.matrix[i * 4 + 2] = D_L07_001B0EBC;
        if (!(i & 1))
            frame.packet.matrix[i * 4 + 2] = -D_L07_001B0EBC;
        frame.packet.color[i] = color;
    }
    func_00280B90(&frame.packet, &frame.difference, 0);
    length = func_00282DF0(&frame.difference) / D_L07_001B0EC0;
    angle = *(f32 *)(state + 0x28);
    if (object[0x20] == 0) {
        intensity = 1.0f;
        count = length * *(f32 *)(state + 0x24);
        count = count + count;
        if (count > length + 1.0f)
            count = length + 1.0f;
    } else {
        intensity = *(f32 *)(state + 0x24) * *(f32 *)(state + 0x24);
        count = length + 1.0f;
    }
    qcopy(&frame.cursor, &frame.position);
    func_00282F20(&frame.step, &frame.difference, D_L07_001B0EC0);
    for (i = 0; (f32)i < count; i++) {
        scale = D_L07_001B0EC8;
        if ((f32)i != count - 1.0f && !(i & 1))
            scale = D_L07_001B0ECC;
        color = func_00283D38(D_L07_001B0ED0 & 0xFFFFFF, D_L07_001B0ED0, intensity);
        func_00281EB8(&frame.cursor, 0x31, color, 1, scale, 0.0f, angle);
        color = func_00283D38(D_L07_001B0ED4 & 0xFFFFFF, D_L07_001B0ED4, intensity);
        func_00281EB8(&frame.cursor, 0x31, color, 1, scale, 0.0f,
                     func_00283B98(angle, D_L07_001B0ED8));
        angle = -func_00283B98(angle, D_L07_001B0EDC * 0.017453294f);
        if ((f32)i < length - 1.0f)
            func_00282CC0(&frame.cursor, &frame.cursor, &frame.step);
        else
            qcopy(&frame.cursor, &frame.second);
    }
}
