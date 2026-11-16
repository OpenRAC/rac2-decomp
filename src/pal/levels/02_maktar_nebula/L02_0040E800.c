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
extern int func_PAL_002B1A50(void *, void *, int);
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
void func_PAL_L02_0040FD10(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0x68);
    float m[16];
    float f;
    u8 *p;
    u8 *rec;
    u8 *other;
    short cls;

    if (a0[0x20] == 0) {
        *(u8 **)(s1 + 0x18) = s1 + 0x100;
        s1[0x48] = FloatToInt(15.0f);
        s1[0x4A] = FloatToInt(12.0f);
        f = math_random_float_range(15.0f, 40.0f) * 0.01745329424738884f;
        if (math_random_int_below(2) != 0)
            f = -f;
        *(float *)(s1 + 0x2D8) = f;
        if (math_random_int_below(2) == 1)
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) | 0x8000;
        s1[0x60] = 8;
        *(float *)(s1 + 0x80) = 0.5f;
        *(float *)(s1 + 0x84) = 0.5f;
        *(float *)(s1 + 0x8C) = 0.4f;
        *(int *)(s1 + 0x98) = 4;
        *(float *)(s1 + 0x100) = 0.8f;
        *(float *)(s1 + 0x104) = 0.5f;
        *(float *)(s1 + 0x108) = 0.4f;
        *(float *)(s1 + 0x10C) = 0.4f;
        *(float *)(s1 + 0x110) = 1.5707965f;
        *(float *)(s1 + 0x130) = 0.52359885f;
        *(float *)(s1 + 0x12C) = 0.008f;
        moby_set_controller_speed_limits(a0, 0.0064000003f, 0.16000001f,
                        0.0016755164f, 0.12566373f);
        s1[0x28] = 3;
        flamethrower_robot_knock_out_pal(a0);
    }
    if (a0[0x31] != 0) {
        if (fast_vec_dist(a0 + 0x10, g_camera_l02_position) < 24.0f) {
            moby_update_ground_check(a0);
            a0[0x6F] = 0x16;
        }
    }
    moby_transform_joint_to_world(a0, 1, s1 + 0x290);
    p = s1 + 0x2B0;
    moby_transform_joint_to_world(a0, 2, s1 + 0x2A0);
    moby_transform_joint_point(a0, 3, m);
    vec_clear_128(p);
    *(float *)(s1 + 0x2B0) = 0.25f;
    *(int *)(s1 + 0x2B8) = 0;
    transform_vector(p, p, m);
    FastVecAdd(p, p, m + 12);
    if (a0[0x31] != 0 && a0[0x20] >= 3) {
        rec = part_find_owned_effect_slot(a0, 0x10000, 1);
        if (rec != 0) {
            other = *(u8 **)(rec + 0x20);
            if (other != 0 && a0[0x31] == 0) {
                cls = *(short *)(other + 0xAA);
                if (cls == 0xA03 || cls == 0xB89)
                    *(int *)(rec + 0x2C) = 0;
            }
        }
        if (func_PAL_002B1A50(a0, s1 + 0x50, 0) == 5) {
            *(int *)(s1 + 0xE0) = 0;
            *(float *)(s1 + 0xE4) = 1.0053098f;
        }
        if (a0[0x20] >= 2 && s1[0x2E] == 2)
            flamethrower_robot_knock_out_pal(a0);
        *(s16 *)(s1 + 0x2E0) = weapon_select_aim_target(a0, *(u32 *)(s1 + 0x2DC), 100.0f, 100.0f, 0, 0);
        *(int *)(s1 + 0x2D4) = *(int *)(s1 + 0x200);
    }
}

