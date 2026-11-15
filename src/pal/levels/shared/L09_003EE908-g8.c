#include "common.h"
/* func_PAL_L09_003EE908, the PAL copy of func_L09_003EA360: the same C, where the frame time
 * 0.016666668f becomes 0.020000001f, the three int cooldown settings are scaled by 5/6 and the
 * two aim channel values by 1.44f, and the projectile spawner is the PAL function. */
extern void moby_transform_joint_point(void *,int,void *);
extern void moby_transform_joint_to_world(void *,int,void *);
extern float fast_vec_dist(void *,void *),vec_distance_xy(void *,void *),vec_length_xy(void *);
extern float mat_fast_helper_a(float,float),fast_subtract_rotations(float,float),math_random_float_range(float,float);
extern float IntToFloat(int),math_wrap_angle_to_pi(float),math_fast_sin_or_cos_b(float);
extern void FastVecScale(void *,void *,float),vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *),FastVecSub(void *,void *,void *);
extern void vec_add_random_offset(void *,float),anim_start_blended(void *,int,int,int);
extern void moby_update_eased_node(void *,void *,int,float,float);
extern void *func_PAL_L09_003B20E8(void *,void *,void *,int,int,float,float,float,float);
extern char D_00189F30[] MACRO_ADDR;
extern int D_L09_001B2388 MACRO_ADDR;
extern int D_L09_001B2388_gp SDATA(D_L09_001B2388);
extern float D_L09_001B0BD4 __attribute__((sda));
extern float D_L09_001B0C30 __attribute__((sda));
extern float D_L09_001B0C2C __attribute__((sda));
extern float D_L09_001B0C34 __attribute__((sda));
extern float D_L09_001B0C24 __attribute__((sda));
extern int D_L09_001B0BDC __attribute__((sda));
extern int D_L09_001B0BD8 __attribute__((sda));
extern int D_L09_001B0BE0 __attribute__((sda));
extern float D_L09_001B0BE8 __attribute__((sda));
extern int D_L09_001B0BE4 __attribute__((sda));
extern float D_L09_001B0BEC __attribute__((sda));
extern float D_L09_001B0C38 __attribute__((sda));
extern float D_L09_001B0C3C __attribute__((sda));

typedef union { u8 pad[0x318]; struct { u8 pad0[0x298]; float yaw; u8 pad1[0x314 - 0x29C]; float pitch; } aim; } AimState;

/* Tracks a shot direction in active states and drives the two aim channels.
 * The joint transform is a complete 64-byte matrix, not one vector.
 */
void func_PAL_L09_003EE908(u8 *object)
{
    struct { float point[4], direction[4], joint[16]; } frame;
    u8 *state = *(u8 **)(object + 0x68);
    float blend = 1.0f, distance, angle;
    if ((unsigned)(object[0x20] - 3) < 3) {
        moby_transform_joint_to_world(object, 0, frame.point);
        distance = fast_vec_dist(frame.point, state + 0x140) - 1.0f;
        distance /= D_L09_001B0BD4 * 0.020000001f;
        distance *= math_random_float_range(D_L09_001B0C2C, D_L09_001B0C30);
        FastVecScale(frame.direction, D_00189F30, distance);
        vec_add_random_offset(frame.direction, D_L09_001B0C34);
        frame.direction[2] = 0.0f;
        FastVecAdd(frame.direction, frame.direction, state + 0x140);
        FastVecSub(frame.point, frame.direction, frame.point);
        *(float *)(state + 0x298) = fast_subtract_rotations(
            mat_fast_helper_a(frame.point[0], frame.point[1]), *(float *)(object + 0xF8));
        moby_transform_joint_to_world(object, 1, frame.point);
        FastVecSub(frame.point, frame.direction, frame.point);
        angle = fast_subtract_rotations(-mat_fast_helper_a(vec_length_xy(frame.point), frame.point[2]),
                              *(float *)(object + 0xF4));
        if (angle > 0.349065899848938f) angle = 0.349065899848938f;
        else if (angle < -0.349065899848938f) angle = -0.349065899848938f;
        *(float *)(state + 0x314) = angle;
    }
    if (object[0x20] == 4) {
        if ((*(u64 *)(state + 0x368) & 0xFFFF00FFULL) == 0) {
            if (object[0x42] != 1 && object[0x43] != 1)
                anim_start_blended(object, 1, 0, 0);
            distance = *(float *)(state + 0x384);
            if (distance < 1.0f) distance = D_L09_001B0C24;
            moby_transform_joint_to_world(object, 2, frame.point);
            moby_transform_joint_point(object, 2, frame.joint);
            vec_scale_to_length(frame.direction, frame.joint, D_L09_001B0BD4 * 0.020000001f);
            func_PAL_L09_003B20E8(frame.point, object, frame.direction, 1, 1,
                              (float)state[0x34], distance, 1.0f, 1.0f);
            state[0x369]++;
            state[0x368] = (D_L09_001B0BDC * 5 + 2) / 6;
            if (D_L09_001B0BD8 < state[0x369]) {
                state[0x369] = 0;
                *(u16 *)(state + 0x36A) = (D_L09_001B0BE0 * 5 + 2) / 6;
                if (vec_distance_xy(object + 0x10, state + 0x140) < D_L09_001B0BE8)
                    *(u16 *)(state + 0x36A) = (D_L09_001B0BE4 * 5 + 2) / 6;
                if (object[0x43] != 0) anim_start_blended(object, 0, 0, 0);
            }
        }
        blend = IntToFloat(*(u16 *)(object + 0x96)) / D_L09_001B0BEC;
        if (blend > 1.0f) blend = 1.0f;
        else if (blend < 0.0f) blend = 0.0f;
    } else if (object[0x20] < 3) {
        if (object[0x43] != 0) anim_start_blended(object, 0, 0, 0);
        blend = 0.1f;
        ((AimState *)state)->aim.pitch = math_fast_sin_or_cos_b(math_wrap_angle_to_pi(
            IntToFloat(D_L09_001B2388_gp) * 0.016666668f)) * 0.2617994248867035f;
        ((AimState *)state)->aim.yaw = math_fast_sin_or_cos_b(math_wrap_angle_to_pi(
            IntToFloat(D_L09_001B2388) * 0.014285714365541935f)) * 0.349065899848938f;
    }
    blend *= 1.44f;
    moby_update_eased_node(object, state + 0x230, 0, D_L09_001B0C38 * blend, D_L09_001B0C3C * 1.44f);
    moby_update_eased_node(object, state + 0x2B0, 1, D_L09_001B0C38 * blend, D_L09_001B0C3C * 1.44f);
}
