/* Retained bounded near miss, 2026-10-28: 644/648 bytes, six forms.
 * The original direct-array form has retail0x150 frame; named persistent
 * loop cursors spill count and enlarge it to0x160. Natural loops, guarded
 * do/while and phase-local cursors still tie644 bytes. -fno-regmove ties.
 * Reopen on a measured cursor lifetime model that avoids count spill and
 * preserves the separate segment/cross/side address generations.
 * Complete packet144 bytes: vertices64, colors16, UV32 and state32. The
 * initializer writes all state bytes; wrapper fills every remaining packet
 * byte before each renderer call. Five real16-byte vectors follow it.
 * Pointer/count/texture fields are real loop state exposed to packet calls,
 * not stack padding or scheduling-only accesses. No aliases or volatile.
 */
#include "common.h"

typedef struct { float v[4]; } RibbonPoint;
typedef struct {
    float vertex[4][4]; unsigned int color[4]; float uv[8]; u64 state[4];
} RibbonPacket;
typedef struct {
    RibbonPacket packet;
    float camera[4], cross[4], side[4], camera_delta[4], segment[4];
    int middle_texture, changed;
    RibbonPoint *next;
    float *out0, *out1;
} RibbonFrame;
extern char D_L04_001B9680[];
extern void func_00281DE8(void *, int, int, int);
extern void func_00280B90(void *, void *, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

/* Complete144-byte renderer packet and five16-byte vector locals. The first
 * point and its successor are consumed before the count-controlled loop,
 * exactly as in retail; callers must supply at least two initialized points. */
void func_L04_0030C948(RibbonPoint *points, int first_texture, int middle_texture,
                     int last_texture, int count, unsigned int color)
{
    RibbonFrame f;
    int i;
    RibbonPoint *current_next;
    f.middle_texture = middle_texture;
    f.changed = 0;
    qcopy(f.camera, D_L04_001B9680);
    f.next = points + 1;
    func_00281DE8(&f.packet, first_texture, 0, 0x80);
    f.packet.color[3] = color;
    f.packet.color[2] = color;
    f.packet.color[1] = color;
    f.packet.color[0] = color;
    f.packet.uv[0] = 0.0f;
    f.packet.uv[1] = 0.0f;
    f.packet.uv[2] = 1.0f;
    f.packet.uv[3] = 0.0f;
    f.packet.uv[4] = 0.0f;
    f.packet.uv[5] = 1.0f;
    f.packet.uv[6] = 1.0f;
    f.packet.uv[7] = 1.0f;
    func_00282CF0(f.camera_delta, points, f.camera);
    func_00282CF0(f.segment, f.next, points);
    func_00282DD8(f.cross, f.segment, f.camera_delta);
    func_00282F20(f.side, f.cross, points->v[3]);
    func_00282CC0(f.packet.vertex[0], points, f.side);
    func_00282CF0(f.packet.vertex[1], points, f.side);
    i = 1;
    if (i < count) {
    float *segment = f.segment, *cross = f.cross, *side = f.side;
    current_next = f.next;
    f.out0 = f.packet.vertex[2];
    f.out1 = f.packet.vertex[3];
    do {
        func_00282CF0(f.camera_delta, current_next, f.camera);
        func_00282CF0(segment, current_next, points);
        func_00282DD8(cross, segment, f.camera_delta);
        func_00282F20(side, cross, current_next->v[3]);
        func_00282CC0(f.packet.vertex[2], current_next, side);
        func_00282CF0(f.packet.vertex[3], current_next, side);
        func_00280B90(&f.packet, 0, 0);
        if (!f.changed) {
            if (i == count-2) func_00281DE8(&f.packet, last_texture, 0, 0x80);
            else func_00281DE8(&f.packet, f.middle_texture, 0, 0x80);
            f.changed = 1;
        } else if (i == count-2) func_00281DE8(&f.packet, last_texture, 0, 0x80);
        qcopy(f.packet.vertex[0], f.out0);
        qcopy(f.packet.vertex[1], f.out1);
        ++points;
        ++current_next;
        ++i;
    } while (i < count);
    }
}
