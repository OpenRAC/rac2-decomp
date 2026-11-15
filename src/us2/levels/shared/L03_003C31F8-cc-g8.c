#include "names.h"
/* func_US2_L03_003C31F8, the USA v2.00 copy of func_L03_003C1BF0: the same C, where rename func_00288E18 becomes func_US2_00289840; rename func_002AEB60 becomes func_US2_002AF9C8. */
/* Per-frame state machine for the L03/L14 moby with class switch 0x940/0x964 (states 1..22).
   Own unit: -G8 globals, the hazard-nop branch label and -malign-loops=2 for the store group. */
#include "common.h"
typedef struct {
    u8 reserved00[0x134]; float acceleration;
    u8 reserved138[12]; float max_speed;
} MotionInit;
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } MotionVector;
typedef struct {
    u8 reserved00[0x18]; u8 enabled, count, kind; u8 reserved1B[0x65]; u8 payload[1];
} DispatchContext;
extern float g_hero_position[], D_00189F00[];
extern u8 g_hero_state[];
typedef union { u8 b[0x2600]; u8 *ptr[0x980]; float f[0x980]; } Hero;
extern u16 D_0018CB20[], D_0018CB38[], D_0018CDCC[];
extern u16 D_0018CB2C[], D_0018CF58[], D_0018CDE4[];
extern int D_0018CB4C[];
extern int g_frame_l03_counter MACRO_ADDR;
extern u8 *D_L03_001B2A1C MACRO_ADDR;
extern u8 *D_L03_001B2A20 MACRO_ADDR;
extern u8 *D_L03_001BFDD8[];
extern float D_L03_001AFEE0 __attribute__((sda));
extern float D_L03_001AFEE4 __attribute__((sda));
extern float D_L03_001AFEE8 __attribute__((sda));
extern float D_L03_001AFEEC __attribute__((sda));
extern float D_L03_001AFEF0 __attribute__((sda));
extern float D_L03_001AFEF4 __attribute__((sda));
extern void UpdateCommandedMoby(u8 *);
extern int flag_set_second_pending(u8 *);
extern int flag_set_first_pending(u8 *);
extern int flag_is_third_pending_set(u8 *);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern u32 moby_dispatch_action_by_kind(void *, DispatchContext *);
extern void moby_set_state(u8 *, s32, s32);
extern int func_US2_00289840(int, int);
extern int math_random_int_below(int);
extern void anim_start_blended(u8 *, int, int, int);
extern void moby_push_toward_target(u8 *, void *);
extern void moby_turn_toward_move_direction(u8 *);
extern void bot_update_head_tilt(u8 *);
extern void moby_aim_body_toward_point(u8 *, void *);
extern float vec_distance_xy(void *, void *);
extern int route_check_points(u32, void *, void *);
extern float math_step_int_toward_target(int *, int, int);
extern int bot_move_toward_waypoint(u8 *, int, int);
extern int moby_count_teammates_by_side(u8 *, float *);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float), mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float), fast_subtract_rotations(float, float);
extern void FastVecAdd(void *, void *, void *), FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float), matrix_mul_vec3(void *, void *, void *);
extern int moby_start_effect_from_entry(int, float);
extern int math_fast_float_d(void *);
extern int group_is_nearest_to_target(u8 *, u8 *);
extern u32 moby_get_count_in_state_two(u8 *);
extern void moby_decrement_count_and_finish(u8 *, u32);
extern void vec_transform_by_object_or_given(char *, char *, char *, char *);
extern void moby_mark_spawned(void *);
extern u8 *moby_find_nearest_tilt_target(u8 *);
extern void entity_stun_in_front(u8 *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern int func_US2_002AF9C8(char *, float);
extern int coll_test_hit_at_bone(float, float, float, void *, int, int, int, int, int);
extern float moby_get_anim_value(char *);
extern float vec_step_toward_target_limited(void *, void *, float);
extern void route_set_node_enabled_flag(u32, u8 *, s32);
extern int group_is_state_word_matching(u8 *);
extern u32 moby_check_against_stored_value(u8 *, u8 *);
extern void moby_place_held_object(void *);
extern void vec_clamp_length(float *, float);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void moby_set_height_offset(u8 *, float), moby_set_flag_bit(u8 *, int);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern float coll_probe_ground_height_below(u8 *, int, float);
extern int route_check_object_points(void *, void *, void *);
extern void euler_rotation_basis(void *, void *);
extern void moby_step_at_own_position(char *), bot_update_timers_and_path(u8 *), func_002A677C(u8 *);

void func_US2_L03_003C31F8(u8 *object)
{
    MotionVector point, other, delta;
    u8 *state = *(u8 **)(object + 0x68);
    u8 *target, *parent, *member, *pos, *mtx, *rot;
    u32 dispatch;
    int type, code, i, entered;
    float heading, turn, distance, floor, height;
    UpdateCommandedMoby(object);
    switch (object[0x95]) {
    case 0:
        break;
    case 1:
        if (flag_set_second_pending(object)) {
            moby_set_controller_speed_limits(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                          0.0034906589426100254f, 0.10471977293491364f);
            ((MotionInit *)state)->acceleration = 0.0016666667f;
            ((MotionInit *)state)->max_speed = D_L03_001AFEE0;
        }
        break;
    case 2:
        if (flag_set_second_pending(object)) {
            moby_set_controller_speed_limits(object, D_L03_001AFEE8 * 0.00027777778f, D_L03_001AFEEC * 0.016666668f,
                          0.006981317885220051f, 0.20943954586982727f);
            (*(float *)(state + 0x144)) = 0.0f; (*(float *)(state + 0x134)) = 0.0055555557f;
        }
        break;
    case 3:
        if (flag_set_second_pending(object)) {
            moby_set_controller_speed_limits(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                          0.006981317885220051f, 0.20943954586982727f);
            (*(float *)(state + 0x134)) = 0.0055555557f; (*(float *)(state + 0x144)) = 0.1f;
        }
        break;
    case 4:
        moby_set_controller_speed_limits(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                      0.0034906589426100254f, 0.10471977293491364f);
        (*(float *)(state + 0x134)) = 0.0016666667f; (*(float *)(state + 0x144)) = 0.4f;
        break;
    case 5:
        moby_set_controller_speed_limits(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                      0.0034906589426100254f, 0.10471977293491364f);
        (*(float *)(state + 0x134)) = 0.0016666667f; (*(float *)(state + 0x144)) = 0.05f;
        break;
    case 6:
        moby_set_controller_speed_limits(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                      0.006981317885220051f, 0.20943954586982727f);
        (*(float *)(state + 0x134)) = 0.005f; (*(float *)(state + 0x144)) = 0.05f;
        break;
    case 8:
        dispatch = moby_dispatch_action_by_kind(object, (DispatchContext *)(state + 0x60));
        if (dispatch & 1) { moby_mark_spawned(object); return; }
        if (dispatch & 2) moby_set_state(object, 2, 0);
        break;
    }
    {
        switch (object[0x20]) {
        case 1:
            if (flag_is_third_pending_set((*(u8 **)(state + 0x354)))) {
                type = *(s16 *)(object + 0xAA);
                switch (type) {
                case 0x940:
                    if (D_0018CB20[0] == 0) func_US2_00289840(0x9CF, 0x26);
                    break;
                case 0x93C:
                    if (D_0018CB38[0] == 0) func_US2_00289840(0x9D1, 0x28);
                    break;
                case 0xA59:
                    if (D_0018CDCC[0] == 0) func_US2_00289840(0xA08, 0x5F);
                    break;
                case 0x964:
                default:
                    if (D_0018CB4C[0] >= 0) func_US2_00289840(0x9D2, 0x29);
                    break;
                }
                moby_set_state(object, 4, 1);
            }
            break;
        case 2:
            if (((Hero *)g_hero_state)->ptr[0x270 / 4] == object || ((Hero *)g_hero_state)->ptr[0x26C / 4] == object)
                moby_push_toward_target(object, &((Hero *)g_hero_state)->b[0x80]);
            moby_turn_toward_move_direction(object);
            if (object[0x31]) bot_update_head_tilt(object);
            break;
        case 4:
            if (flag_set_first_pending(object)) {
                if (object[0x43]) anim_start_blended(object, 0, math_random_int_below((*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + 0x48) + 0x10))), 15);
                (*(int *)(state + 0x380)) = 2; qzero(state + 0x1B0);
            }
            if (((Hero *)g_hero_state)->ptr[0x270 / 4] == object || ((Hero *)g_hero_state)->ptr[0x26C / 4] == object)
                moby_push_toward_target(object, &((Hero *)g_hero_state)->b[0x80]);
            moby_turn_toward_move_direction(object);
            distance = vec_distance_xy(object + 0x10, g_hero_state + 0x80);
            if (D_L03_001AFEE4 < distance && route_check_points((u32)(*(int *)(state + 0x220)), object + 0x10, g_hero_state + 0x80)) {
                moby_set_state(object, 3, -1);
                if (object[0x43] != 2) anim_start_blended(object, 2, math_random_int_below((*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + 0x50) + 0x10))), 10);
            } else {
                if (object[0x31] && object[0x42] != 1) {
                    if ((*(int *)(state + 0x380)) < 5) moby_aim_body_toward_point(object, D_00189F00);
                    else bot_update_head_tilt(object);
                }
            }
            if ((object[0x60] & 2) && object[0x42] == object[0x43]) {
                if (object[0x42] == 1)
                    anim_start_blended(object, 0, math_random_int_below((*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + 0x48) + 0x10))), 15);
                else if (!math_random_int_below((*(int *)(state + 0x380)))) {
                    math_step_int_toward_target((int *)(state + 0x380), 10, 1);
                    if (object[0x43] != 1) anim_start_blended(object, 1, 0, 15);
                }
            }
            break;
        case 3:
            if (!bot_move_toward_waypoint(object, (int)g_hero_position, 1) || (*(float *)(state + 0x1DC)) < D_L03_001AFEE0 ||
                ((*(int *)(state + 0x190)) > 60 && (*(float *)(state + 0x1DC)) < D_L03_001AFEE4)) {
                moby_set_state(object, 4, -1);
                if (object[0x43]) anim_start_blended(object, 0, math_random_int_below((*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + 0x48) + 0x10))), 10);
            }
            if ((g_frame_l03_counter & 15) == (((int)object >> 8) & 15))
                (*(int *)(state + 0x360)) = moby_count_teammates_by_side(object, g_hero_position);
            break;
        case 5:
            if (flag_set_first_pending(object)) {
                if (object[0x43] != 2) anim_start_blended(object, 2, math_random_int_below((*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + 0x50) + 0x10))), 20);
                (*(float *)(state + 0x144)) = 0.1f;
            }
            point.f[0] = math_fast_sin_or_cos_a((*(float *)(state + 0x374))); point.f[1] = math_fast_sin_or_cos_b((*(float *)(state + 0x374))); point.f[2] = 0;
            FastVecAdd(&point, &point, object + 0x10);
            bot_move_toward_waypoint(object, (int)&point, 1);
            if (*(u16 *)(object + 0x96) >= 61) {
                (*(float *)(state + 0x144)) = D_L03_001AFEE0;
                moby_set_state(object, 4, 1);
                if (object[0x43]) anim_start_blended(object, 0, math_random_int_below((*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + 0x48) + 0x10))), 10);
            }
            break;
        case 6:
        case 8:
            if (flag_set_first_pending(object)) {
                if (object[0x20] == 8) { if (object[0x43] != 7) anim_start_blended(object, 7, 0, 20); }
                else if (object[0x43] != 3) anim_start_blended(object, 3, 0, 20);
            }
            moby_start_effect_from_entry((int)object, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - (*(float *)(object + 0x10)), ((Hero *)g_hero_state)->f[0x84 / 4] - (*(float *)(object + 0x14))));
            if (object[0x60] & 2) moby_set_state(object, 4, -1);
            break;

        case 7:
            if (flag_set_first_pending(object)) (*(float *)(state + 0x144)) = 0.1f;
            if (vec_distance_xy(object + 0x10, state + 0x340) > (*(float *)(state + 0x144))) {
                bot_move_toward_waypoint(object, (int)(state + 0x340), 0);
                if (object[0x43] != 2) anim_start_blended(object, 2, math_random_int_below((*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + 0x50) + 0x10))), 20);
            } else if (object[0x43]) anim_start_blended(object, 0, math_random_int_below((*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + 0x48) + 0x10))), 20);
            if (math_fast_float_d(state + 0x37C)) moby_set_state(object, 4, -1);
            break;
        case 12:
            bot_move_toward_waypoint(object, (int)(state + 0x340), 0);
            if ((g_frame_l03_counter & 3) == (((int)object >> 8) & 3))
                (*(float *)(state + 0x110)) = group_is_nearest_to_target(object, state + 0x340) ? 0.11f : 0.15f;
            if (!moby_get_count_in_state_two((*(u8 **)(state + 0x358)))) {
                moby_set_state(object, 4, 1);
                if (object[0x43]) anim_start_blended(object, 0, math_random_int_below((*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + 0x48) + 0x10))), 10);
            } else if ((*(float *)(state + 0x1DC)) < (*(float *)(state + 0x144))) moby_set_state(object, 13, -1);
            break;
        case 13:
            if (flag_set_first_pending(object)) {
                moby_decrement_count_and_finish((*(u8 **)(state + 0x358)), (u32)object); (*(float *)(state + 0x140)) = 0.174532949924469f;
                vec_transform_by_object_or_given((char *)(*(u8 **)(state + 0x358)), (char *)(state + 0x1B0), (char *)(state + 0x1B0), 0);
                (*(float *)(state + 0x1B4)) = 0;
                matrix_mul_vec3(state + 0x1B0, state + 0x1B0, (*(u8 **)(state + 0x358)) + 0xC0); (*(float *)(state + 0x110)) = 0;
            }
            bot_move_toward_waypoint(object, (int)((*(u8 **)(state + 0x358)) + 0x10), 0);
            if (vec_distance_xy(object + 0x10, (*(u8 **)(state + 0x358)) + 0x10) < 0.1f) { moby_mark_spawned(object); return; }
            break;
        case 9:
            if ((g_frame_l03_counter & 7) == (((int)object >> 8) & 7)) (*(u8 **)(state + 0x358)) = moby_find_nearest_tilt_target(object);
            parent = (*(u8 **)(state + 0x194));
            if (parent) {
                if ((*(u8 **)(state + 0x198)) && *(s16 *)((*(u8 **)(state + 0x198)) + 0xAA) == 0x97A) heading = (*(float *)(object + 0xF8));
                else {
                    heading = mat_fast_helper_a(*(float *)(parent + 0x10) - (*(float *)(object + 0x10)), *(float *)(parent + 0x14) - (*(float *)(object + 0x14)));
                    turn = fast_subtract_rotations(heading, (*(float *)(object + 0xF8)));
                    heading = FastAddRotations(turn < 0.0f ? -1.5707963705062866f : 1.5707963705062866f, (*(float *)(object + 0xF8)));
                }
                entity_stun_in_front(object, heading);
            }
            target = (*(u8 **)(state + 0x358));
            if (!target) {
                moby_set_state(object, 11, -1);
                if (object[0x43]) anim_start_blended(object, 0, math_random_int_below((*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + 0x48) + 0x10))), 20);
                break;
            }
            bot_move_toward_waypoint(object, (int)(target + 0x10), 0);
            if ((g_frame_l03_counter & 3) == (((int)object >> 8) & 3)) {
                qcopy(&point, object + 0x10); point.f[2] += 0.2f;
                vec_scale_to_length(&other, object + 0xC0, 0.3330000042915344f);
                FastVecAdd(&other, &other, object + 0x10); other.f[2] += 0.2f;
                if (CollLine(&point, &other, 0, object, 0) && D_L03_001BFDD8[0] == (*(u8 **)(state + 0x358))) {
                    moby_set_state(object, 10, -1);
                    if (object[0x43] != 4) anim_start_blended(object, 4, 0, 10);
                }
            }
            break;
        case 10:
            if (func_US2_002AF9C8((char *)object, 14.0f))
                coll_test_hit_at_bone(0.3330000042915344f, 4.0f, 1.0f, object, 1, 0x10000, 0, 1, 0);
            else if (object[0x60] & 2) {
                (*(u8 **)(state + 0x358)) = moby_find_nearest_tilt_target(object);
                if ((*(u8 **)(state + 0x358))) {
                    moby_set_state(object, 9, -1);
                    if (object[0x43] != 3) anim_start_blended(object, 3, math_random_int_below((*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + 0x54) + 0x10))), 10);
                } else {
                    moby_set_state(object, 11, -1);
                    if (object[0x43]) anim_start_blended(object, 0, math_random_int_below((*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + 0x48) + 0x10))), 10);
                }
            }
            break;
        case 11:
            if ((g_frame_l03_counter & 7) == (((int)object >> 8) & 7)) (*(u8 **)(state + 0x358)) = moby_find_nearest_tilt_target(object);
            bot_update_head_tilt(object);
            if ((*(u8 **)(state + 0x358))) {
                moby_set_state(object, 9, -1);
                if (object[0x43] != 3) anim_start_blended(object, 3, math_random_int_below((*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + 0x54) + 0x10))), 20);
            } else if (*(u16 *)(object + 0x96) >= 301) {
                moby_set_state(object, 4, 1);
                if (object[0x43]) anim_start_blended(object, 0, math_random_int_below((*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + 0x48) + 0x10))), 20);
            }
            break;
        case 14:
            bot_move_toward_waypoint(object, (int)(state + 0x340), 0);
            if (flag_set_first_pending(object)) D_0018CB2C[0] = -1;
            if ((*(u8 **)(state + 0x194))) entity_stun_in_front(object, FastAddRotations((*(float *)(object + 0xF8)), 3.141592741012573f));
            if ((*(int *)(state + 0x1A4)) & 0x80) moby_set_state(object, 15, -1);
            break;
        case 15:
            if (flag_set_first_pending(object)) {
                if (object[0x43] != 4) anim_start_blended(object, 4, 0, 10);
                *(int *)(object + 0x98) = 0;
                FastVecSub(state + 0x340, state + 0x340, (*(u8 **)(state + 0x358)) + 0x10);
                vec_transform_by_object_or_given((char *)(*(u8 **)(state + 0x358)), (char *)(state + 0x340), (char *)(state + 0x340), 0);
                (*(float *)(state + 0x344)) = 0;
                if ((*(float *)(state + 0x340)) < (*(float *)(state + 0x344))) (*(float *)(state + 0x340)) = -3.8f;
                else (*(float *)(state + 0x340)) = 3.8f;
                matrix_mul_vec3(state + 0x340, state + 0x340, (*(u8 **)(state + 0x358)) + 0xC0);
                FastVecAdd(state + 0x340, state + 0x340, (*(u8 **)(state + 0x358)) + 0x10);
            }
            heading = mat_fast_helper_a(*(float *)((*(u8 **)(state + 0x358)) + 0x10) - (*(float *)(object + 0x10)), *(float *)((*(u8 **)(state + 0x358)) + 0x14) - (*(float *)(object + 0x14)));
            moby_start_effect_from_entry((int)object, heading);
            if (moby_get_anim_value((char *)object) > 11.0f) vec_step_toward_target_limited(object + 0x10, state + 0x340, 0.13333334f);
            if (object[0x60] & 2) {
                route_set_node_enabled_flag((*(int *)(state + 0x220)), (*(u8 **)(state + 0x358)) + 0x10, 1);
                moby_set_state(object, 16, -1);
                if (object[0x43] != 5) anim_start_blended(object, 5, 0, 5);
                moby_set_flag_bit((*(u8 **)(state + 0x358)), 1);
            }
            break;
        case 16:
            if (flag_set_first_pending(object)) (*(u8 **)(state + 0x198)) = 0;
            if (vec_distance_xy(g_hero_position, (*(u8 **)(state + 0x358)) + 0x10) > 12.0f &&
                !group_is_state_word_matching(object) && !moby_check_against_stored_value((*(u8 **)(state + 0x358)), g_hero_position))
                moby_place_held_object(object);
            break;
        case 17:
            FastVecSub(&point, state + 0x340, object + 0x10);
            vec_clamp_length(point.f, 0.4166666865348816f);
            FastVecAdd(object + 0x10, object + 0x10, &point);
            if (object[0x42] == object[0x43]) {
                qcopy(object + 0x10, state + 0x340);
                moby_set_state(object, 6, 1);
            }
            break;
        case 18:
            bot_move_toward_waypoint(object, (int)(state + 0x340), 0);
            if ((*(u8 **)(state + 0x194))) entity_stun_in_front(object, FastAddRotations((*(float *)(object + 0xF8)), 3.141592741012573f));
            if ((*(int *)(state + 0x1A4)) & 0x80) {
                moby_set_state(object, 19, -1);
                moby_set_flag_bit((*(u8 **)(state + 0x358)), 1);
            }
            break;
        case 19:
            if (flag_set_first_pending(object) && object[0x43] != 4) anim_start_blended(object, 4, 0, 10);
            moby_start_effect_from_entry((int)object, mat_fast_helper_a(*(float *)((*(u8 **)(state + 0x358)) + 0x10) - (*(float *)(object + 0x10)), *(float *)((*(u8 **)(state + 0x358)) + 0x14) - (*(float *)(object + 0x14))));
            if (object[0x42] == object[0x43]) {
                if (moby_get_anim_value((char *)object) >= 10.0f) {
                    moby_transform_joint_to_world((char *)object, 3, (char *)&point);
                    moby_set_height_offset((*(u8 **)(state + 0x358)), point.f[2] - (*(float *)(object + 0x18)));
                }
                if (object[0x60] & 2) {
                    moby_set_state(object, 6, 1); moby_set_flag_bit((*(u8 **)(state + 0x358)), 0);
                }
            }
            D_0018CF58[0] = -1;
            break;
        case 20:
            bot_move_toward_waypoint(object, (int)(state + 0x340), 0);
            if ((*(u8 **)(state + 0x194))) entity_stun_in_front(object, FastAddRotations((*(float *)(object + 0xF8)), 3.141592741012573f));
            if ((*(int *)(state + 0x1A4)) & 0x80) moby_set_state(object, 21, -1);
            break;
        case 21:
            if (flag_set_first_pending(object)) {
                if (object[0x43] != 5) anim_start_blended(object, 5, 0, 10);
                D_0018CDE4[0] = -1;
            }
            moby_start_effect_from_entry((int)object, mat_fast_helper_a(*(float *)((*(u8 **)(state + 0x358)) + 0x10) - (*(float *)(object + 0x10)), *(float *)((*(u8 **)(state + 0x358)) + 0x14) - (*(float *)(object + 0x14))));
            if (object[0x60] & 2) moby_set_state(object, 6, 1);
            else if (func_US2_002AF9C8((char *)object, 20.0f)) moby_set_flag_bit((*(u8 **)(state + 0x358)), 1);
            break;
        case 22: {
            MotionVector *offset;
            FastVecAdd(object + 0x10, object + 0x10, state + 0x1B0);
            qzero_nc(&point); qzero_nc(&other);
            type = *(s16 *)(object + 0xAA);
            height = 0.8f;
            switch (type) {
            case 0x964:
                height = 0.3f;
            case 0x940:
            case 0x93C:
            default:
                do {
                    point.f[2] = height;
                } while (0);
                other.f[2] = height;
                break;
            }
            offset = &other;
            matrix_mul_vec3(&point, &point, object + 0xC0);
            if ((*(float *)(state + 0x1B8)) < 0.0f) {
                (*(float *)(state + 0x1B8)) -= (*(float *)(state + 0x398));
                if ((*(float *)(object + 0xF4)) > 0.0f) math_step_value_toward_target(object + 0xF4, state + 0x39C, 0, 0.006981317885220051f, 0.006981317885220051f, 0.41887909173965454f);
                else (*(float *)(object + 0xF4)) = fast_subtract_rotations((*(float *)(object + 0xF4)), 0.41887909173965454f);
                if ((*(float *)(object + 0x18)) < (*(float *)(state + 0x3A0))) {
                    floor = coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
                    if ((*(float *)(object + 0x18)) <= floor) {
                        (*(float *)(object + 0x18)) = floor; moby_set_state(object, 4, 1);
                        for (member = D_L03_001B2A1C; member <= D_L03_001B2A20; member += 256) {
                            if (*(s16 *)(member + 0xAA) == 0xF2D && route_check_object_points(member, object + 0x10, object + 0x10)) {
                                (*(int *)(state + 0x220)) = ((int)member - (int)D_L03_001B2A1C) >> 8;
                                (*(int *)(state + 0x368)) = -1; (*(int *)(state + 0x36C)) = -1;
                            }
                        }
                    }
                }
            } else {
                (*(float *)(state + 0x1B8)) -= (*(float *)(state + 0x394)); (*(float *)(object + 0xF4)) = fast_subtract_rotations((*(float *)(object + 0xF4)), 0.41887909173965454f);
            }
            euler_rotation_basis(object + 0xC0, object + 0xF0);
            matrix_mul_vec3(offset, offset, object + 0xC0);
            FastVecSub(&delta, &point, offset);
            FastVecAdd(object + 0x10, object + 0x10, &delta);
            break;
        }
        }
    }
    code = object[0x20];
    if (code != 22 && code != 1 && code != 15 && code != 16 && ((*(float *)(state + 0x1A0)) < (*(float *)(object + 0x18)) - 0.05f || (*(u8 **)(state + 0x198)))) {
        float zero = 0.0f;
        (*(float *)(object + 0xF0)) = zero; (*(float *)(object + 0xF4)) = zero; moby_step_at_own_position((char *)object);
    }
    bot_update_timers_and_path(object);
    func_002A677C(object);
}
