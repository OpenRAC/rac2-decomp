/* func_PAL_L02_003D18D8, the PAL copy of func_L02_003CD970: the same C at 50 Hz, with the speeds and
 * turn rates scaled by 6/5 or 36/25, the random timers by 5/6 and the frame counts rescaled. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));

#define U8(p, o) (*(unsigned char *)((p) + (o)))
#define U16(p, o) (*(unsigned short *)((p) + (o)))
#define S(p, o) (*(short *)((p) + (o)))
#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))

extern char D_0018A0E0[], g_hero_position[];
extern int g_hero_moby __attribute__((nosda));
extern int g_frame_l02_counter;

/* The distance bound is read absolutely in state 3 and through GP in state 4.
 * Both symbols resolve to the same word in each of the three programs. */
extern float D_L02_001B00F8[] __attribute__((sda));
extern float D_L02_001B00F8_abs MACRO_ADDR;

extern void func_PAL_L02_003D24B8(void *);
extern void func_PAL_L02_003D2A10(void *);
extern void func_PAL_L02_003D28F0(void *);
extern void func_PAL_L02_003D2E28(void *);
extern void turret_clamp_aim_yaw_pitch(void *);
extern void func_PAL_L02_003D31A0(void *);
extern int flag_set_second_pending(void *);
extern int flag_set_first_pending(void *);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern int FastDecTimer(void *);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int func_PAL_L02_003D2898(void *, void *, int);
extern int moby_count_group_side_from_object(void *, int, int);
extern int func_PAL_002AF6C0(void *, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastVecDot(void *, void *);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void moby_set_state(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void path_clamp_move_to_area(void *, void *, void *, int, float);
extern int moby_start_effect_from_entry(void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern int coll_test_hit_at_bone(void *, int, int, int, int, int, float, float, float);
extern int moby_check_target_point_from_offset(char *, void *);
/* The integer and floating argument banks retain their independent order. */
extern int coll_sweep_from_object(void *, float, float *, int, float, float, int, int, int);

void func_PAL_L02_003D18D8(char *o)
{
    char *p = *(char **)(o + 0x68);
    float angle, speed;
    int r;
    Quad temp;

    func_PAL_L02_003D24B8(o);
    switch (U8(o, 0x95)) {
    case 0:
        if (flag_set_second_pending(o)) {
            moby_set_controller_speed_limits(o, 0.0072000003f, 0.080000006f, 0.010053098f,
                         0.5026549f);
            F(p, 0x1D0) = 0.080000006f;
            F(p, 0x124) = 0.0096f;
            F(p, 0x134) = 0.5f;
            S(p, 0x33A) = ((int)(math_random_int_range(0, 30)) * 5 + 2) / 6;
        }
        if (S(p, 0x314) == 1) {
            if (FastDecTimer(p + 0x33A)) {
                if (math_random_int_below(3))
                    moby_set_state(o, 9, 2);
                else
                    moby_set_state(o, 8, 2);
                break;
            }
        }
        if (S(p, 0x316)) {
            if (math_random_int_below(2))
                moby_set_state(o, 7, 1);
            else
                moby_set_state(o, 6, 1);
            S(p, 0x316) = 0;
            if (S(p, 0x310) < 250)
                S(p, 0x310) = ((int)(math_random_int_range(480, 600)) * 5 + 2) / 6;
        }
        break;
    case 1:
        if (flag_set_second_pending(o)) {
            moby_set_controller_speed_limits(o, 0.0072000003f, 0.080000006f, 0.025132746f,
                         1.2566373f);
            F(p, 0x1D0) = 0.080000006f;
            F(p, 0x134) = 0.05f;
        }
        if (S(p, 0x314) == 1) {
            moby_set_state(o, 9, 2);
        } else if (S(p, 0x310) == 0)
            moby_set_state(o, 1, 0);
        break;
    case 2:
        if (flag_set_second_pending(o)) {
            moby_set_controller_speed_limits(o, 0.0072000003f, 0.080000006f, 0.025132746f,
                         1.2566373f);
            F(p, 0x1D0) = 0.080000006f;
            F(p, 0x124) = 0.0096f;
            F(p, 0x134) = 0.05f;
            S(p, 0x33A) = ((int)(math_random_int_range(0, 30)) * 5 + 2) / 6;
        }
        if (S(p, 0x314) != 1 && FastDecTimer(p + 0x33A)) {
            moby_set_state(o, 3, 1);
            S(p, 0x310) = ((int)(math_random_int_range(580, 600)) * 5 + 2) / 6;
        }
        break;
    case 3: {
        unsigned int flags;
        flags = moby_dispatch_action_by_kind(o, p + 0x50);
        if (flags & 1)
            func_PAL_L02_003D2A10(o);
        else if (flags & 2) {
            if (S(p, 0x314) == 1)
                moby_set_state(o, 9, 2);
            else {
                moby_set_state(o, 3, 1);
                S(p, 0x310) = ((int)(math_random_int_range(580, 600)) * 5 + 2) / 6;
            }
        }
        break;
    }
    }
    switch (U8(o, 0x20)) {
    case 1:
        if (U8(o, 0x31)) {
            if (flag_set_first_pending(o)) {
                r = !math_random_int_below(4);
                if (U8(o, 0x43) != r)
                    func_PAL_002A7E68(o, r, 0, 8);
                S(p, 0x312) = ((int)(math_random_int_range(60, 120)) * 5 + 2) / 6;
            }
            if (U8(o, 0x43) == 1) {
                if (U8(o, 0x60) & 2)
                    func_PAL_002A7E68(o, 0, 0, 17);
            } else if (!S(p, 0x312) &&
                       (!S(p, 0x338) || FastVecDot(p + 0x300, D_0018A0E0) > 0.8f))
                moby_set_state(o, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(o)) {
            if (U8(o, 0x43) != 6)
                func_PAL_002A7E68(o, 6, 0, 17);
            angle = math_random_angle();
            speed = math_random_float_range(2, 5);
            F(p, 0x2F0) = math_fast_sin_or_cos_a(angle) * speed;
            F(p, 0x2F4) = math_fast_sin_or_cos_b(angle) * speed;
            F(p, 0x2F8) = 0;
            FastVecAdd(p + 0x2F0, p + 0x2F0, p + 0x2E0);
            if (I(p, 0x218) != -1) {
                temp = *(Quad *)(p + 0x2E0);
                path_clamp_move_to_area(&temp, p + 0x2F0, p + 0x2F0, I(p, 0x218), 1.5f);
            }
        }
        func_PAL_L02_003D2898(o, p + 0x2F0, 0);
        if (U16(o, 0x96) > 25 && (F(p, 0x1CC) <= 0.5f || U16(o, 0x96) > 150))
            moby_set_state(o, 1, -1);
        break;
    case 3:
        if (flag_set_first_pending(o) && U8(o, 0x43) != math_random_int_below(2) + 4)
            func_PAL_002A7E68(o, math_random_int_below(2) + 4, 0, 8);
        if (fast_vec_dist(o + 0x10, g_hero_position) < D_L02_001B00F8_abs)
            moby_set_state(o, 4, -1);
        else if (U8(o, 0x60) & 2) {
            switch (math_random_int_below(3)) {
            case 0:
                moby_set_state(o, 6, -1);
                break;
            case 1:
                moby_set_state(o, 7, -1);
                break;
            case 2:
                moby_set_state(o, 5, -1);
                break;
            }
        }
        break;
    case 6:
        if (flag_set_first_pending(o) && U8(o, 0x43) != math_random_int_below(2) + 2)
            func_PAL_002A7E68(o, math_random_int_below(2) + 2, 0, 8);
        moby_check_target_point_from_offset(o, p + 0x1F0);
        if (U8(o, 0x60) & 2)
            moby_set_state(o, 3, -1);
        break;
    case 7:
        if (flag_set_first_pending(o) && U8(o, 0x43) != 12)
            func_PAL_002A7E68(o, 12, 0, 8);
        moby_check_target_point_from_offset(o, p + 0x1F0);
        if (U8(o, 0x60) & 2)
            moby_set_state(o, 3, -1);
        break;
    case 4:
        if (flag_set_first_pending(o)) {
            if (U8(o, 0x43) != 6)
                func_PAL_002A7E68(o, 6, 0, 8);
            {
                float upper = D_L02_001B00F8[1];
                F(p, 0x334) = math_random_float_range(D_L02_001B00F8[0], upper) + 0.5f;
            }
        }
        if ((func_PAL_L02_003D2898(o, p + 0x2E0, 0) & 0x80) ||
            vec_distance_xy(o + 0x10, g_hero_position) > F(p, 0x334)) {
            if (math_random_int_below(2))
                moby_set_state(o, 6, -1);
            else
                moby_set_state(o, 7, -1);
        }
        break;
    case 5:
        if (flag_set_first_pending(o)) {
            if (U8(o, 0x43) != 6)
                func_PAL_002A7E68(o, 6, 0, 17);
            angle = math_random_angle();
            speed = math_random_float_range(2, 5);
            F(p, 0x2F0) = math_fast_sin_or_cos_a(angle) * speed;
            F(p, 0x2F4) = math_fast_sin_or_cos_b(angle) * speed;
            F(p, 0x2F8) = 0;
            FastVecAdd(p + 0x2F0, p + 0x2F0, p + 0x2E0);
            if (I(p, 0x218) != -1) {
                temp = *(Quad *)(p + 0x2E0);
                path_clamp_move_to_area(&temp, p + 0x2F0, p + 0x2F0, I(p, 0x218), 1.5f);
            }
        }
        func_PAL_L02_003D2898(o, p + 0x2F0, 0);
        if (U16(o, 0x96) > 25 && (F(p, 0x1CC) <= 0.5f || U16(o, 0x96) > 150))
            moby_set_state(o, 3, -1);
        break;
    case 8:
        if (flag_set_first_pending(o) && U8(o, 0x43) != math_random_int_below(2) + 2)
            func_PAL_002A7E68(o, math_random_int_below(2) + 2, 0, 8);
        if (U8(o, 0x60) & 2)
            moby_set_state(o, 9, -1);
        break;
    case 9:
        if (flag_set_first_pending(o) && U8(o, 0x43) != 6)
            func_PAL_002A7E68(o, 6, 0, 4);
        if (!(U16(o, 0x96) & 3))
            F(p, 0x31C) = moby_count_group_side_from_object(o, g_hero_moby, -1) * 0.087266475f;
        func_PAL_L02_003D2898(o, p + 0x1F0, 1);
        turret_clamp_aim_yaw_pitch(o);
        if (F(p, 0x1CC) <= 1.25f)
            moby_set_state(o, 10, -1);
        break;
    case 10:
        if (flag_set_first_pending(o)) {
            F(p, 0x320) = mat_fast_helper_a(F(p, 0x1F0) - F(o, 0x10),
                                       F(p, 0x1F4) - F(o, 0x14));
            if (U8(o, 0x43) != 8)
                func_PAL_002A7E68(o, 8, 2, 8);
        }
        moby_start_effect_from_entry(o, F(p, 0x320));
        if (func_PAL_002AF6C0(o, 13))
            coll_test_hit_at_bone(o, 1, 0x4000001, 0, 1, 0, 0.75f, U8(p, 0x34), 1);
        if (U8(o, 0x60) & 2)
            moby_set_state(o, 9, -1);
        break;
    case 14:
        if (flag_set_first_pending(o)) {
            if (U8(o, 0x43) != 10)
                func_PAL_002A7E68(o, 10, 0, 5);
            I(p, 0x1BC) = g_frame_l02_counter;
        }
        vec_scale_to_length(&temp, p + 0x1A0, 1);
        func_PAL_L02_003D2898(o, &temp, 0);
        func_PAL_L02_003D31A0(o);
        coll_sweep_from_object(o, 0.6f, (float *)(o + 0x10), 0x4000000, 1, 1, 0, 1, 0);
        if (F(p, 0x190) >= F(o, 0x18)) {
            if (S(p, 0x314) == 1)
                moby_set_state(o, 8, 2);
            else
                moby_set_state(o, 2, 0);
            I(p, 0x138) &= -18;
        }
        break;
    case 12:
        func_PAL_L02_003D2A10(o);
        break;
    }
    func_PAL_L02_003D28F0(o);
    if (U8(o, 0x31))
        func_PAL_L02_003D2E28(o);
}
