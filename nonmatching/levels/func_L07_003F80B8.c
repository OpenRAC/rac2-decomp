/* func_L07_003F80B8: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections -mno-split-addresses -frac2-qcopy.
   Local checks: 888/888 bytes, 0/1 in each of USA v1.01 and v2.00.
   No strict linked match is claimed.

   Equal size is not a match: the first failure is at +0x40, with different
   branch-slot/address setup, followed by different hero-field load order.
   The four complete vectors and real floating return contracts are preserved.
   The typed float/integer interleaving of func_002AAA00 preserves both EE
   argument banks, all seven parameters and its floating return.
*/

#include "common.h"

typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
typedef s32 Quad __attribute__((mode(TI)));
extern void func_L07_003F8430(u8 *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern s32 func_002AD0B0(u8 *);
extern void func_002AC9F8(void *, f32);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283248(f32, f32);
extern f32 func_002AAA00(f32 *, f32 *, f32, f32, f32, f32, s32);
extern void func_00282CF0(void *, void *, void *);
extern f32 func_00282DF0(void *);
extern f32 func_00282C10(f32);
extern void func_00282F20(void *, void *, f32);
extern f32 func_00282DB0(void *, void *);
extern f32 func_002AA548(f32 *, f32 *, f32, f32, f32, f32);
typedef struct { u8 prefix[0x80]; f32 position[4]; } Hero;
extern Hero D_00189E20[];
extern f32 D_L07_001B1070 __attribute__((sda));
extern f32 D_L07_001B1074 __attribute__((sda));
extern f32 D_L07_001B1078 __attribute__((sda));
extern f32 D_L07_001B107C __attribute__((sda));
extern f32 D_L07_001B1080 __attribute__((sda));
extern f32 D_L07_001B1084 __attribute__((sda));
extern f32 D_L07_001B1088 __attribute__((sda));
extern f32 D_L07_001B108C __attribute__((sda));

/* Follow the sampled target, limiting movement and smoothing the two angles. */
void func_L07_003F80B8(u8 *object, f32 limit)
{
    Vector target, delta, movement, correction;
    u8 *state = *(u8 **)(object + 0x68);
    u8 *support;
    f32 rate, speed, distance, step, angle, roll;

    func_L07_003F8430(object);
    if (object[0x95] == 0) {
        func_00283098(&target, state + 0x3E0, *(u8 **)(state + 0x418) + 0xC0);
        func_00282CC0(&target, &target, *(u8 **)(state + 0x418) + 0x10);
        support = (u8 *)func_002AD0B0(*(u8 **)(state + 0x418));
        if (limit >= 0.0f) {
            qcopy(&delta, support + 0x10);
            func_002AC9F8(&delta, limit);
            func_00282CC0(object + 0x10, object + 0x10, &delta);
        } else {
            func_00282CC0(object + 0x10, object + 0x10, support + 0x10);
        }
        *(f32 *)(object + 0xF8) = func_00283B98(*(f32 *)(*(u8 **)(state + 0x418) + 0xF8), 3.1415927f);
    } else {
        f32 *heading = (f32 *)(object + 0xF8);
        qcopy(&target, state + 0x3E0);
        angle = func_00283248(D_00189E20[0].position[0] - *(f32 *)(object + 0x10),
                              D_00189E20[0].position[1] - *(f32 *)(object + 0x14));
        func_002AAA00(heading, (f32 *)(state + 0x424),
                     angle, 0.003490659f, 0.003490659f, 0.20943955f, 0);
    }
    func_00282CF0(&delta, &target, object + 0x10);
    rate = (object[0x95] ? D_L07_001B1078 : D_L07_001B1070) * 0.00027777778f;
    speed = (object[0x95] ? D_L07_001B107C : D_L07_001B1074) * (1.0f / 60.0f);
    distance = func_00282DF0(&delta);
    step = func_00282C10(distance * rate * 0.5f);
    if (limit >= 0.0f && limit < speed)
        speed = limit;
    if (speed < step)
        step = speed;
    if (step < distance)
        func_00282F20(&movement, &delta, step);
    else
        qcopy(&movement, &delta);
    func_00282CF0(&correction, &movement, state + 0x3F0);
    func_002AC9F8(&correction, rate);
    func_00282CC0(state + 0x3F0, state + 0x3F0, &correction);
    func_00282CC0(object + 0x10, object + 0x10, state + 0x3F0);
    angle = func_00282DB0(object + 0xD0, state + 0x3F0) * D_L07_001B1080;
    if (angle > 1.5707965f)
        angle = 1.5707965f;
    else if (angle < -1.5707965f)
        angle = -1.5707965f;
    func_002AA548((f32 *)(object + 0xF0), (f32 *)(state + 0x428), angle,
                 D_L07_001B1084 * 0.0000048481374f,
                 D_L07_001B1084 * 0.0000048481374f,
                 D_L07_001B1088 * 0.00029088825f);
    roll = *(f32 *)(object + 0xF0) * D_L07_001B108C;
    if (object[0x43] >= 8)
        *(f32 *)(state + 0x2C0) = roll;
    else
        *(f32 *)(state + 0x2C4) = roll;
}
