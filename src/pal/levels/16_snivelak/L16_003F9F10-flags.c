#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int math_fast_float_d(void *);
extern void snivelak_sync_child(u8 *);
extern void AttachManipulator(u8 *, s32, void *);
extern void build_axis_rotation_quaternion(void *, s32, float);
extern float fast_subtract_rotations(float, float);
extern void make_hit_descriptor(void *, u8 *, s32, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_fabs(float);
extern void QueueMobyImpact(s32, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern u8 D_L16_00189E20[];

void func_PAL_L16_00409AD0(u8 *arg)
{
    float delta[4];
    float pos[4];
    u8 query[0x30];
    u8 *state;
    u8 *hero;
    state = *(u8 **)(arg + 0x68);
    math_fast_float_d(state + 0x258);
    if (*(u16 *)(arg + 0x96) < 0xFFFF) ++*(u16 *)(arg + 0x96);
    snivelak_sync_child(arg);
    if (!state[0x211]) AttachManipulator(arg, 7, state + 0x210);
    build_axis_rotation_quaternion(state + 0x220, 2, *(float *)(state + 0x26C));
    *(float *)(state + 0x26C) = fast_subtract_rotations(*(float *)(state + 0x26C), 0.49916422f);
    if (*(s32 *)(state + 0x2AC)) {
        make_hit_descriptor(query, arg, 1, arg + 0xE0, 10.0f);
        *(u16 *)(query + 0x1A) = *(u16 *)(arg + 0xAA);
        *(TI128 *)pos = *(TI128 *)(arg + 0x10);
        pos[2] += 3.5f;
        vec_scale_to_length(delta, arg + 0xC0, -1.3f);
        FastVecAdd(pos, delta, pos);
        hero = D_L16_00189E20;
        if (math_fabs(*(float *)(hero + 0x88) - pos[2]) < 0.1f &&
            vec_distance_xy(pos, hero + 0x80) < 9.1f)
            QueueMobyImpact(*(s32 *)(hero + 0x2290), query);
    }
}
