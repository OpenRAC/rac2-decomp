/* Nonmatching C reconstruction.
 * Profile: -O2 -G8 -ffunction-sections -frac2-zero-ti-por.
 * Emitted/retail size: 584/576 bytes.
 * us: 0 of 12 places match.
 * pal: 0 of 12 places match.
 * us2: 0 of 12 places match.
 * No strict linked build was run for this draft.
 * The honest incomplete matrix table does not produce the retail GP base, and pointer allocation differs. The real zero quadword and its following float writes are preserved. Reopen with an independently established table extent and allocation evidence.
 */
#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
typedef struct { float matrix[16]; u32 color[4]; float uv[8]; u64 state[4]; } Packet;
typedef struct { Packet packet; Vector up, axis, cross1, cross2, position, offset; } DrawFrame;
extern u64 func_0027C878(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(Packet *, void *, int);
extern Vector D_L00_001B8DC0;
extern Vector D_001AA310[] __attribute__((sda));

void func_L00_00325CC0(int count, Vector *points, u32 *colors, float scale, float displacement)
{
    DrawFrame frame;
    int i, j;
    u32 color;
    frame.up.q = 0;
    frame.up.f[2] = 1.0f;
    frame.up.f[3] = 1.0f;
    frame.packet.state[1] = func_0027C878(11);
    color = colors[0];
    frame.packet.state[3] = 0x8000000048ULL;
    frame.packet.state[2] = 0xff9000000260ULL;
    frame.packet.state[0] = 5;
    frame.packet.uv[0] = 0.0f;
    frame.packet.uv[1] = 0.0f;
    frame.packet.uv[2] = 0.0f;
    frame.packet.uv[3] = 1.0f;
    frame.packet.uv[4] = 1.0f;
    frame.packet.uv[5] = 0.0f;
    frame.packet.uv[6] = 1.0f;
    frame.packet.uv[7] = 1.0f;
    frame.packet.color[0] = frame.packet.color[1] = frame.packet.color[2] = frame.packet.color[3] = color;
    for (i = 0; i < count; ++i) {
        qcopy(&frame.position, &points[i]);
        func_00282CF0(&frame.axis, &D_L00_001B8DC0, &frame.position);
        func_00282F20(&frame.axis, &frame.axis, 1.0f);
        func_00282DD8(&frame.cross1, &frame.axis, &frame.up);
        func_00282F20(&frame.cross1, &frame.cross1, 1.0f);
        func_00282DD8(&frame.cross2, &frame.cross1, &frame.axis);
        func_00282D30(&frame.offset, &frame.axis, displacement);
        func_00282CC0(&frame.position, &frame.position, &frame.offset);
        if (colors[i] != color) {
            color = colors[i];
            frame.packet.color[0] = frame.packet.color[1] = frame.packet.color[2] = frame.packet.color[3] = color;
        }
        for (j = 0; j < 4; ++j) {
            func_00282D30(&frame.packet.matrix[j * 4], &D_001AA310[j], scale);
            func_002830C0(&frame.packet.matrix[j * 4], &frame.packet.matrix[j * 4], &frame.axis);
        }
        func_00280B90(&frame.packet, 0, 0);
    }
}
