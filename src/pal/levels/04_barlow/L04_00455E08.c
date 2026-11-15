#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
typedef float f32;
extern u8 D_L04_001395C7;
extern u8 D_L04_002CA518;
extern u8 D_001A7B00[] __attribute__((sda));
extern u8 D_001395B8[];
extern u8 *D_L04_001B25CC[] __attribute__((sda));
extern u8 g_hero_position[];
extern u8 D_0019B2E8[];
extern u8 D_L04_001BF880[];
extern u8 D_L04_001B9680[];
extern f32 fast_vec_dist(void *, void *);
extern f32 IntToFloat(int);
extern f32 math_fabs(f32);
extern u8 g_hero_position[];
extern u8 D_L04_001B1218[];
extern u8 D_L04_001B1230[];
extern u8 D_L04_001B12B0[] __attribute__((sda));
extern u8 D_L04_001B12E8[] __attribute__((sda));
extern u8 D_L04_001B1300[] __attribute__((sda));
extern u8 D_L04_001B1330[] __attribute__((sda));
extern u8 D_L04_001B1348[] __attribute__((sda));
extern u8 D_L04_001B3280[] __attribute__((sda));
extern u8 D_L04_001B32B0[] __attribute__((sda));
extern u8 D_L04_001B32E0[] __attribute__((sda));
extern u8 D_L04_001B3300[] __attribute__((sda));
extern u8 D_L04_001B3320[] __attribute__((sda));
extern u8 D_L04_001B3330[] __attribute__((sda));
extern u8 D_L04_001B3360[] __attribute__((sda));
extern u8 D_L04_001B3378[] __attribute__((sda));
extern u8 D_L04_001B33A0[] __attribute__((sda));
extern u8 D_L04_001B33B0[] __attribute__((sda));
extern u8 D_L04_001B33B8[] __attribute__((sda));
extern u8 D_L04_001B33D8[] __attribute__((sda));
extern u8 D_L04_001B33E8[] __attribute__((sda));
extern u8 D_L04_001B3418[] __attribute__((sda));
extern u8 D_L04_001B3430[] __attribute__((sda));
extern u8 D_L04_001B3458[] __attribute__((sda));
extern u8 D_L04_001B3468[] __attribute__((sda));
extern u8 D_L04_001B3470[] __attribute__((sda));
extern u8 D_L04_001B3474[] __attribute__((sda));
extern u8 D_L04_001B3478[] __attribute__((sda));
extern u8 D_L04_001B347C[] __attribute__((sda));
extern u8 D_L04_001B3480[] __attribute__((sda));
extern u8 D_L04_001B3484[] __attribute__((sda));
extern u8 D_L04_001B3488[] __attribute__((sda));
extern u8 D_L04_0026D370[];
extern u8 D_L04_0026D3E0[];
extern u8 D_L04_0026D490[];
extern u8 D_L04_0026D4F0[];
extern u8 D_L04_002CA3E0[];
extern u8 D_L04_002CA438[];
extern f32 func_30F468(f32 a, f32 b);
extern f32 func_30FE88(f32 a, f32 b);
extern f32 func_30FE40(f32 a, f32 b);
extern float FastVecLength(void *);
extern void FastVecSub(void *, void *, void *);
extern void ComputeRegionRouteHeading(void *, void *, void *, void *, int, void *, void *, f32, f32);
extern void math_approach_target_with_direction_mode(void *, f32, f32, f32, f32, void *, int);
extern f32 FastDiffRots(f32, f32);
extern void math_step_value_toward_target(void *, void *, f32, f32, f32, f32);
extern f32 ApproachValue(f32 *, f32, f32);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern int moby_move_over_ground(void *, void *, void *, f32, f32, f32, f32, int);

int func_PAL_L04_00456890(u8 *object, void *target, f32 desiredHeading, f32 speed, f32 stopDistance, f32 margin) {
    f32 delta[4], displacement[4], destination[4];
    f32 angle, frameSpeed = 0.0f;
    u8 *data = *(u8 **)(object + 0x68);
    int done = 0;
    f32 distance, acceleration;
    FastVecSub(delta, target, object + 0x10);
    delta[2] = 0.0f;
    distance = FastVecLength(delta);
    acceleration = speed * 0.0012f;
    if (stopDistance < distance) {
        int collision = *(int *)(data + 0x540);
        angle = 0.0f;
        ComputeRegionRouteHeading(object + 0x10, target, &angle, data + 0x340, collision, data + 0x550, data + 0x554, margin, 0.4f);
        math_approach_target_with_direction_mode(object + 0xF8, angle, 0.010053098f, 0.005026549f, 0.25132746f, data + 0x28C, 0);
        if (FastDiffRots(*(f32 *)(object + 0xF8), angle) < 0.523598849773407f) {
            math_step_value_toward_target(&frameSpeed, data + 0x558, distance, acceleration, acceleration, speed * 0.020000001f);
        } else {
            *(f32 *)(data + 0x558) = 0.0f;
        }
    } else {
        math_approach_target_with_direction_mode(object + 0xF8, desiredHeading, 0.010053098f, 0.28800002f, 0.25132746f, data + 0x28C, 0);
        ApproachValue((f32 *)(data + 0x558), 0.0f, acceleration);
        if (*(f32 *)(data + 0x558) == 0.0f && FastDiffRots(*(f32 *)(object + 0xF8), desiredHeading) < 0.0872664749622345f) {
            *(f32 *)(data + 0x28C) = 0.0f;
            done = 1;
        }
    }
    vec_scale_to_length(displacement, object + 0xC0, *(f32 *)(data + 0x558));
    FastVecAdd(destination, displacement, object + 0x10);
    if (!moby_move_over_ground(object, object + 0x10, destination, 0.75f, 0.75f, 0.4f, 0.523598849773407f, 0))
        *(int *)(data + 0x55C) += 1;
    if (*(int *)(data + 0x55C) >= 30) {
        *(int *)(data + 0x55C) = 0;
        done = 1;
    }
    return done;
}


typedef unsigned short u16;
typedef signed int s32;
extern void FastDecTimer(void *a0);
extern void func_PAL_002AC3C0(void *a0, void *a1);
extern void moby_update_eased_node(void *a0, void *a1, s32 a2, f32 f12, f32 f13);
extern void func_PAL_002B14F8(void *a0, void *a1, s32 a2, s32 a3, f32 f12);
extern s32 D_L04_001B2008[] __attribute__((sda));
extern s32 func_342228(void *a0, void *a1);
extern s32 req_push_queue(u8 *a0, s32 a1);
extern s32 req_launch_queued(void *a0);
extern u16 *g_moby_l04_group_lists[];

void func_PAL_L04_00456B58(char *a0) {
    char *s0 = *(char **)(a0 + 0x68);
    u16 v;

    func_PAL_002AC3C0(a0, s0 + 0x50);
    FastDecTimer(s0 + 0x270);
    FastDecTimer(s0 + 0x272);
    FastDecTimer(s0 + 0x26);
    v = *(u16 *)(a0 + 0x96);
    if (v <= 0xFFFE) {
        *(u16 *)(a0 + 0x96) = v + 1;
    }
    s0 += 0x2C0;
    moby_update_eased_node(a0, s0, 4, 0.0432f, 0.43200004f);
    func_PAL_002B14F8(a0, s0, 4, 1, 2.5f);
}

