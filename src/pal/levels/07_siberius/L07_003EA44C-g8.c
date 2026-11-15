/* func_PAL_L07_003EA44C, the PAL copy of func_L07_003E61E0: the same C, where the three
 * retimed 0x344 stores (480..600 and 580..600, twice) take PAL's 50 Hz scale. */
#include "common.h"
#define I(p, o) (*(int *)((p)+(o)))
#define H(p, o) (*(unsigned short *)((p)+(o)))
#define B(p, o) (*(unsigned char *)((p)+(o)))
#define F(p, o) (*(float *)((p)+(o)))
extern int D_L07_001B1E08 MACRO_ADDR;
extern int D_L07_001C9780 NOT_SDA;
extern float D_L07_001B0AE8 __attribute__((sda));
extern float D_L07_001B0AEC __attribute__((sda));
extern float D_L07_001B0AF0 __attribute__((sda));
extern float D_L07_001B0AF4 __attribute__((sda));
extern float D_L07_001B0AF8 __attribute__((sda));
extern float D_L07_001B0AFC __attribute__((sda));
extern float D_L07_001B0B00 __attribute__((sda));
extern struct Choice61 {int a, b, c, d;} D_L07_001B0B08;
extern int func_PAL_L07_003EAC48(void *);
extern void func_PAL_L07_003EB508(void *);
extern void func_PAL_L07_003EB0C8(void *);
extern void moby_set_state(void *, int, int);
extern int math_random_int_range(int, int);
extern void follow_camera_set_distance(int, float, float);
extern void follow_camera_set_height(float, float);
extern int flag_set_second_pending(void *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int moby_dispatch_action_by_kind(void *, void *);
extern void moby_mark_spawned(void *);
extern int flag_set_first_pending(void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern int func_PAL_L01_00323068(void *, void *);
extern int math_random_int_below(int);
extern int moby_check_target_point_from_offset(void *, void *);
extern float mat_fast_helper_a(float, float);
extern int func_PAL_L02_00333638(void *, void *, int, float, float, float);
extern int func_PAL_002B5BA8(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern float moby_get_anim_value(void *);
extern int moby_start_effect_from_entry(void *, float);
extern int coll_sweep_from_object(void *, void *, int, float, float, int, float, int, int);
extern float FastDiffRots(float, float);
extern int moby_count_group_not_in_state(int, int);

/* Update the entity's submode, movement target and timed attack actions. */
void func_PAL_L07_003EA44C(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    float time;
    int result;
    int choices[4];
    if (D_L07_001B1E08 >= 2 && D_L07_001C9780 != I(state, 0x350)) return;
    if (func_PAL_L07_003EAC48(actor)) goto cleanup;
    {
        switch (B(actor, 0x95)) {
        case 0:
            if (I(state, 0x2D4) == 1) {moby_set_state(actor, 6, 2); break;}
            if (I(state, 0x2D0)) {
                moby_set_state(actor, 3, 1);
                I(state, 0x2D0) = 0;
                if (I(state, 0x344) < 250) I(state, 0x344) = ((s32)(math_random_int_range(480, 600)) * 5 + 2) / 6;
            }
            break;
        case 1:
            if (I(state, 0x2D4) == 1) moby_set_state(actor, 6, 2);
            break;
        case 2:
            follow_camera_set_distance(0, D_L07_001B0AFC, 0.003f);
            follow_camera_set_height(D_L07_001B0B00, 0.003f);
            if (flag_set_second_pending(actor))
                moby_set_controller_speed_limits(actor, D_L07_001B0AEC*0.00040000002f, D_L07_001B0AF0*0.020000001f, D_L07_001B0AF4*6.981318e-06f, D_L07_001B0AF8*0.0003490659f);
            if (I(state, 0x2D4) != 1 && B(actor, 0x20) != 7) {
                if (I(state, 0x338)) moby_set_state(actor, 3, 1);
                else moby_set_state(actor, 4, 1);
                I(state, 0x344) = ((s32)(math_random_int_range(580, 600)) * 5 + 2) / 6;
            }
            break;
        case 3:
            result = moby_dispatch_action_by_kind(actor, state + 0x140);
            if (result & 1) {
                func_PAL_L07_003EB508(actor);
cleanup:
                /* The initialization helper also reaches this shared cleanup. */
                moby_mark_spawned(actor);
                return;
            }
            if (result & 2) {moby_set_state(actor, 7, 2);I(state, 0x344) = ((s32)(math_random_int_range(580, 600)) * 5 + 2) / 6;}
            break;
        }
    }
    switch (B(actor, 0x20)) {
    case 1:
        if (flag_set_first_pending(actor) && B(actor, 0x43) != 2) func_PAL_002A7E68(actor, 2, 0, 17);
        if ((B(actor, 0x60) & 2) && !I(state, 0x338)) moby_set_state(actor, 2, -1);
        break;
    case 2: {
        float radius, angle;
        if (flag_set_first_pending(actor)) {
            if (B(actor, 0x43) != 8) func_PAL_002A7E68(actor, 8, 0, 17);
            radius = math_random_float_range(0, 5);
            angle = math_random_angle();
            F(state, 0x300) = math_fast_sin_or_cos_a(angle)*radius;
            F(state, 0x304) = math_fast_sin_or_cos_b(angle)*radius;
            F(state, 0x308) = 0;
            FastVecAdd(state + 0x300, state + 0x300, state + 0x2F0);
        }
        result = func_PAL_L01_00323068(actor, state + 0x300);
        if (result == 128 || (I(state, 0xD0) && H(actor, 0x96) > 33) || H(actor, 0x96) > 150) moby_set_state(actor, 1, -1);
        break;
    }
    case 3:
        if (flag_set_first_pending(actor)) {
            *(struct Choice61 *)choices = D_L07_001B0B08;
            if (B(actor, 0x43) != choices[math_random_int_below(4)]) func_PAL_002A7E68(actor, choices[math_random_int_below(4)], 0, 17);
        }
        if ((B(actor, 0x60) & 2) && !I(state, 0x338)) moby_set_state(actor, 4, -1);
        break;
    case 4: {
        float radius, angle;
        if (flag_set_first_pending(actor)) {
            if (B(actor, 0x43) != 8) func_PAL_002A7E68(actor, 8, 0, 17);
            radius = math_random_float_range(0, 3);
            angle = math_random_angle();
            F(state, 0x300) = math_fast_sin_or_cos_a(angle)*radius;
            F(state, 0x304) = math_fast_sin_or_cos_b(angle)*radius;
            F(state, 0x308) = 0;
            FastVecAdd(state + 0x300, state + 0x300, state + 0x2F0);
        }
        moby_check_target_point_from_offset(actor, state + 0x210);
        angle = mat_fast_helper_a(F(state, 0x300)-F(actor, 0x10), F(state, 0x304)-F(actor, 0x14));
        result = func_PAL_L02_00333638(actor, state + 0x300, 16, angle, -1, -1);
        if (result == 128 || (I(state, 0xD0) && H(actor, 0x96) > 33) || H(actor, 0x96) > 150) moby_set_state(actor, 3, -1);
        break;
    }
    case 6:
        if (flag_set_first_pending(actor) && B(actor, 0x43) != 11) func_PAL_002A7E68(actor, 11, 0, 17);
        func_PAL_002B5BA8(actor, state + 0x210, 0);
        if (vec_distance_xy(actor + 0x10, state + 0x210) < D_L07_001B0AE8) moby_set_state(actor, 7, -1);
        break;
    case 7:
        if (flag_set_first_pending(actor) && B(actor, 0x43) != 12) func_PAL_002A7E68(actor, 12, 5, 8);
        time = moby_get_anim_value(actor);
        if (time < 19) moby_start_effect_from_entry(actor, mat_fast_helper_a(F(state, 0x210)-F(actor, 0x10), F(state, 0x214)-F(actor, 0x14)));
        else if (time<=22) {
            coll_sweep_from_object(actor, *(char **)(state + 0x330)+0x10, 1, 0.333f, (float)B(state, 0x34), 0, 1.0f, 1, 0);
            coll_sweep_from_object(actor, *(char **)(state + 0x334)+0x10, 1, 0.333f, (float)B(state, 0x34), 0, 1.0f, 1, 0);
        }
        if (B(actor, 0x60) & 2) {
            time = vec_distance_xy(actor + 0x10, state + 0x210);
            if (D_L07_001B0AE8+0.5f < time ||
                FastDiffRots(F(actor, 0xF8), mat_fast_helper_a(F(state, 0x210)-F(actor, 0x10), F(state, 0x214)-F(actor, 0x14))) > 0.349065899848938f)
                moby_set_state(actor, 6, -1);
        }
        break;
    case 9:
        if (!moby_count_group_not_in_state(I(state, 0x2B8), -1) || F(state, 0x20) < *(short *)(state + 0x24)) moby_set_state(actor, 10, -1);
        break;
    case 10:
        if (flag_set_first_pending(actor) && B(actor, 0x43) != 1) func_PAL_002A7E68(actor, 1, 0, 2);
        if (B(actor, 0x60) & 2) moby_set_state(actor, 6, -1);
        break;
    }
    func_PAL_L07_003EB0C8(actor);
}
