#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
extern float math_random_float_range(float, float);
extern void FastVecAdd(void *, void *, void *);
extern int weapon_select_aim_target(void *, u32, float, float, int, int);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void moby_transform_joint_point(void *, int, void *);
extern void vec_clear_128(void *);
extern void transform_vector(void *, void *, void *);
extern void *part_find_owned_effect_slot(void *, int, int);
extern int moby_apply_damage_to_object_pal(void *, void *, int);
extern char g_camera_l02_position[];
extern void flamethrower_robot_knock_out_pal(u8 *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern u8 g_unlock_flag_c __attribute__((sda));
extern u8 g_message_sequence_flags[];
extern u8 g_message_queue[];
extern u8 g_moby_group_flags[];
extern u16 g_beam_emitter_id;
extern int math_random_int_below(int);
extern float fast_vec_dist(void *, void *);
extern void *part_find_owned_effect_slot(void *, int, int);
extern int math_random_int_below(int);
extern void vec_clear_128(void *);
extern u8 g_moby_nibble_table[];

/* Sets up the actor and refreshes its three effect tracks. In state 0 it points the sub-object's
   record at +0x100, draws two byte values and a turn rate (15 to 40 degrees, negated half of the
   time) for +0x2D8, may set bit 0x8000 of the halfword at +0x34, fills the sub-object's tuning
   floats and arms it (func_PAL_L02_00410598). In every state it then, when the actor is shown (+0x31)
   and within 24.0 of D_L02_001BA500, starts func_002A93B0, rebuilds the tracks at +0x290, +0x2A0
   and +0x2B0 from the matrix func_0029FC20 returns, and, from state 3 on, clears the carried
   record's word at +0x2C filtering by class, tests func_PAL_002B1A50 against 5 and refreshes the
   +0x2E0 handle. Retail passes the actor to func_002B60B0 (a0 is reloaded before the call), which
   the four-float declaration at the top of the file leaves out: the second name carries the
   five-argument prototype. */
void flamethrower_robot_update_common_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    float matrix[16];
    float turn_rate;
    u8 *track;
    u8 *hit;
    u8 *target;
    short target_class;

    if (moby[0x20] == 0) {
        *(u8 **)(vars + 0x18) = vars + 0x100;
        vars[0x48] = FloatToInt(15.0f);
        vars[0x4A] = FloatToInt(12.0f);
        turn_rate = math_random_float_range(15.0f, 40.0f) * 0.01745329424738884f;
        if (math_random_int_below(2) != 0)
            turn_rate = -turn_rate;
        *(float *)(vars + 0x2D8) = turn_rate;
        if (math_random_int_below(2) == 1)
            *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) | 0x8000;
        vars[0x60] = 8;
        *(float *)(vars + 0x80) = 0.5f;
        *(float *)(vars + 0x84) = 0.5f;
        *(float *)(vars + 0x8C) = 0.4f;
        *(int *)(vars + 0x98) = 4;
        *(float *)(vars + 0x100) = 0.8f;
        *(float *)(vars + 0x104) = 0.5f;
        *(float *)(vars + 0x108) = 0.4f;
        *(float *)(vars + 0x10C) = 0.4f;
        *(float *)(vars + 0x110) = 1.5707965f;
        *(float *)(vars + 0x130) = 0.52359885f;
        *(float *)(vars + 0x12C) = 0.008f;
        moby_set_controller_speed_limits(moby, 0.0064000003f, 0.16000001f,
                        0.0016755164f, 0.12566373f);
        vars[0x28] = 3;
        flamethrower_robot_knock_out_pal(moby);
    }
    if (moby[0x31] != 0) {
        if (fast_vec_dist(moby + 0x10, g_camera_l02_position) < 24.0f) {
            moby_update_ground_check(moby);
            moby[0x6F] = 0x16;
        }
    }
    moby_transform_joint_to_world(moby, 1, vars + 0x290);
    track = vars + 0x2B0;
    moby_transform_joint_to_world(moby, 2, vars + 0x2A0);
    moby_transform_joint_point(moby, 3, matrix);
    vec_clear_128(track);
    *(float *)(vars + 0x2B0) = 0.25f;
    *(int *)(vars + 0x2B8) = 0;
    transform_vector(track, track, matrix);
    FastVecAdd(track, track, matrix + 12);
    if (moby[0x31] != 0 && moby[0x20] >= 3) {
        hit = part_find_owned_effect_slot(moby, 0x10000, 1);
        if (hit != 0) {
            target = *(u8 **)(hit + 0x20);
            if (target != 0 && moby[0x31] == 0) {
                target_class = *(short *)(target + 0xAA);
                if (target_class == 0xA03 || target_class == 0xB89)
                    *(int *)(hit + 0x2C) = 0;
            }
        }
        if (moby_apply_damage_to_object_pal(moby, vars + 0x50, 0) == 5) {
            *(int *)(vars + 0xE0) = 0;
            *(float *)(vars + 0xE4) = 1.0053098f;
        }
        if (moby[0x20] >= 2 && vars[0x2E] == 2)
            flamethrower_robot_knock_out_pal(moby);
        *(s16 *)(vars + 0x2E0) = weapon_select_aim_target(moby, *(u32 *)(vars + 0x2DC), 100.0f, 100.0f, 0, 0);
        *(int *)(vars + 0x2D4) = *(int *)(vars + 0x200);
    }
}

