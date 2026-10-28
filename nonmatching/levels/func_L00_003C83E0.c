/* Nonmatching C reconstruction.
 * Profile: -O2 -G8 -ffunction-sections.
 * Emitted/retail size: 552/552 bytes.
 * us: 0 of 27 places match.
 * pal: 0 of 27 places match.
 * us2: 0 of 27 places match.
 * No strict linked build was run for this draft.
 * The pointer registers, UV-store order and GP matrix-table base differ. The matrix table remains an incomplete array because its complete extent has not been established. Reopen with measured table bounds and allocator evidence.
 */
#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
typedef struct { float matrix[16]; u32 color[4]; float uv[8]; u64 state[4]; } Packet;
typedef struct { Packet packet; Vector velocity, normal, side, origin, temporary; } DrawFrame;
extern u64 func_0027C878(int);
extern int func_00283CF0(float);
extern void func_00282D30(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(Packet *, void *, int);
extern u32 D_L00_001B003C __attribute__((sda));
extern int D_L00_001B2AC0[];
extern float D_L00_001B2A90[];
extern Vector D_L00_001B2A20[];
extern Vector D_L00_001B2A50[];
extern float D_L00_001B2AB0[];
extern Vector D_0018A0E0;
extern Vector D_L00_001B00A0[] __attribute__((sda));

void func_L00_003C83E0(void)
{
    DrawFrame frame;
    u32 rgb;
    int i, j;
    frame.packet.state[1] = func_0027C878(8);
    rgb = D_L00_001B003C & 0xffffff;
    frame.packet.state[3] = 0x8000000048ULL;
    frame.packet.state[2] = 0xff9000000260ULL;
    frame.packet.uv[7] = 1.0f;
    frame.packet.state[0] = 0;
    frame.packet.uv[0] = 0.0f;
    frame.packet.uv[1] = 0.0f;
    frame.packet.uv[2] = 0.0f;
    frame.packet.uv[3] = 1.0f;
    frame.packet.uv[4] = 1.0f;
    frame.packet.uv[5] = 0.0f;
    frame.packet.uv[6] = 1.0f;
    for (i = 0; i < 3; ++i) {
        if (D_L00_001B2AC0[i] != 0) {
            u32 color = rgb | (func_00283CF0(D_L00_001B2A90[i]) << 24);
            frame.packet.color[0] = frame.packet.color[1] = frame.packet.color[2] = frame.packet.color[3] = color;
            qcopy(&frame.origin, &D_L00_001B2A20[i]);
            qcopy(&frame.velocity, &D_L00_001B2A50[i]);
            func_00282D30(&frame.side, &D_0018A0E0, -1.0f);
            func_00282DD8(&frame.normal, &frame.velocity, &frame.side);
            func_00282F20(&frame.normal, &frame.normal, 1.0f);
            func_00282DD8(&frame.side, &frame.normal, &frame.velocity);
            for (j = 0; j < 4; ++j) {
                func_00282D30(&frame.temporary, &D_L00_001B00A0[j], D_L00_001B2AB0[i]);
                func_002830C0(&frame.packet.matrix[j * 4], &frame.temporary, &frame.velocity);
            }
            func_00280B90(&frame.packet, 0, 0);
        }
    }
}
