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
extern char g_hero_zero_vector[] MACRO_ADDR;
extern int g_frame_l09_counter MACRO_ADDR;
extern int D_L09_001B2388_gp SDATA(D_L09_001B2388);
extern float g_enemy_sway_speed __attribute__((sda));
extern float g_enemy_sway_random_max __attribute__((sda));
extern float g_enemy_sway_random_min __attribute__((sda));
extern float g_enemy_sway_random_offset __attribute__((sda));
extern float g_enemy_sway_min_distance __attribute__((sda));
extern int g_enemy_sway_byte __attribute__((sda));
extern int g_enemy_sway_threshold __attribute__((sda));
extern int g_enemy_sway_value_a __attribute__((sda));
extern float g_enemy_sway_distance __attribute__((sda));
extern int g_enemy_sway_value_b __attribute__((sda));
extern float g_enemy_sway_blend_divisor __attribute__((sda));
extern float g_enemy_sway_ease_rate __attribute__((sda));
extern float g_enemy_sway_ease_limit __attribute__((sda));

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
        distance /= g_enemy_sway_speed * 0.020000001f;
        distance *= math_random_float_range(g_enemy_sway_random_min, g_enemy_sway_random_max);
        FastVecScale(frame.direction, g_hero_zero_vector, distance);
        vec_add_random_offset(frame.direction, g_enemy_sway_random_offset);
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
            if (distance < 1.0f) distance = g_enemy_sway_min_distance;
            moby_transform_joint_to_world(object, 2, frame.point);
            moby_transform_joint_point(object, 2, frame.joint);
            vec_scale_to_length(frame.direction, frame.joint, g_enemy_sway_speed * 0.020000001f);
            func_PAL_L09_003B20E8(frame.point, object, frame.direction, 1, 1,
                              (float)state[0x34], distance, 1.0f, 1.0f);
            state[0x369]++;
            state[0x368] = (g_enemy_sway_byte * 5 + 2) / 6;
            if (g_enemy_sway_threshold < state[0x369]) {
                state[0x369] = 0;
                *(u16 *)(state + 0x36A) = (g_enemy_sway_value_a * 5 + 2) / 6;
                if (vec_distance_xy(object + 0x10, state + 0x140) < g_enemy_sway_distance)
                    *(u16 *)(state + 0x36A) = (g_enemy_sway_value_b * 5 + 2) / 6;
                if (object[0x43] != 0) anim_start_blended(object, 0, 0, 0);
            }
        }
        blend = IntToFloat(*(u16 *)(object + 0x96)) / g_enemy_sway_blend_divisor;
        if (blend > 1.0f) blend = 1.0f;
        else if (blend < 0.0f) blend = 0.0f;
    } else if (object[0x20] < 3) {
        if (object[0x43] != 0) anim_start_blended(object, 0, 0, 0);
        blend = 0.1f;
        ((AimState *)state)->aim.pitch = math_fast_sin_or_cos_b(math_wrap_angle_to_pi(
            IntToFloat(D_L09_001B2388_gp) * 0.016666668f)) * 0.2617994248867035f;
        ((AimState *)state)->aim.yaw = math_fast_sin_or_cos_b(math_wrap_angle_to_pi(
            IntToFloat(g_frame_l09_counter) * 0.014285714365541935f)) * 0.349065899848938f;
    }
    blend *= 1.44f;
    moby_update_eased_node(object, state + 0x230, 0, g_enemy_sway_ease_rate * blend, g_enemy_sway_ease_limit * 1.44f);
    moby_update_eased_node(object, state + 0x2B0, 1, g_enemy_sway_ease_rate * blend, g_enemy_sway_ease_limit * 1.44f);
}
