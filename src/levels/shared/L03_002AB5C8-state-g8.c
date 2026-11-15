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
extern int subtitle_request_voice_line(int, int);
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
extern int math_is_value_within_step(char *, float);
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
#define SF(o) (*(float *)(state + (o)))
#define SI(o) (*(int *)(state + (o)))
#define SP(o) (*(u8 **)(state + (o)))
#define OF(o) (*(float *)(object + (o)))
#define ANIM_FRAMES(off) (*(u8 *)(*(u8 **)(*(u8 **)(object + 0x24) + (off)) + 0x10))


/* Per-frame update for the robot enemies: sets speeds by kind, then runs its state machine (walk, turn, hunt, jump, fall). */
void bot_update(u8 *object)
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
            SF(0x144) = 0.0f; SF(0x134) = 0.0055555557f;
        }
        break;
    case 3:
        if (flag_set_second_pending(object)) {
            moby_set_controller_speed_limits(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                          0.006981317885220051f, 0.20943954586982727f);
            SF(0x134) = 0.0055555557f; SF(0x144) = 0.1f;
        }
        break;
    case 4:
        moby_set_controller_speed_limits(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                      0.0034906589426100254f, 0.10471977293491364f);
        SF(0x134) = 0.0016666667f; SF(0x144) = 0.4f;
        break;
    case 5:
        moby_set_controller_speed_limits(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                      0.0034906589426100254f, 0.10471977293491364f);
        SF(0x134) = 0.0016666667f; SF(0x144) = 0.05f;
        break;
    case 6:
        moby_set_controller_speed_limits(object, D_L03_001AFEF0 * 0.00027777778f, D_L03_001AFEF4 * 0.016666668f,
                      0.006981317885220051f, 0.20943954586982727f);
        SF(0x134) = 0.005f; SF(0x144) = 0.05f;
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
            if (flag_is_third_pending_set(SP(0x354))) {
                type = *(s16 *)(object + 0xAA);
                switch (type) {
                case 0x940 /* Bridgebot */:
                    if (D_0018CB20[0] == 0) subtitle_request_voice_line(0x9CF, 0x26);
                    break;
                case 0x93C /* moby class 2364 */:
                    if (D_0018CB38[0] == 0) subtitle_request_voice_line(0x9D1, 0x28);
                    break;
                case 0xA59 /* moby class 2649 */:
                    if (D_0018CDCC[0] == 0) subtitle_request_voice_line(0xA08, 0x5F);
                    break;
                case 0x964 /* Gadgebot */:
                default:
                    if (D_0018CB4C[0] >= 0) subtitle_request_voice_line(0x9D2, 0x29);
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
                if (object[0x43]) anim_start_blended(object, 0, math_random_int_below(ANIM_FRAMES(0x48)), 15);
                SI(0x380) = 2; qzero(state + 0x1B0);
            }
            if (((Hero *)g_hero_state)->ptr[0x270 / 4] == object || ((Hero *)g_hero_state)->ptr[0x26C / 4] == object)
                moby_push_toward_target(object, &((Hero *)g_hero_state)->b[0x80]);
            moby_turn_toward_move_direction(object);
            distance = vec_distance_xy(object + 0x10, g_hero_state + 0x80);
            if (D_L03_001AFEE4 < distance && route_check_points((u32)SI(0x220), object + 0x10, g_hero_state + 0x80)) {
                moby_set_state(object, 3, -1);
                if (object[0x43] != 2) anim_start_blended(object, 2, math_random_int_below(ANIM_FRAMES(0x50)), 10);
            } else {
                if (object[0x31] && object[0x42] != 1) {
                    if (SI(0x380) < 5) moby_aim_body_toward_point(object, D_00189F00);
                    else bot_update_head_tilt(object);
                }
            }
            if ((object[0x60] & 2) && object[0x42] == object[0x43]) {
                if (object[0x42] == 1)
                    anim_start_blended(object, 0, math_random_int_below(ANIM_FRAMES(0x48)), 15);
                else if (!math_random_int_below(SI(0x380))) {
                    math_step_int_toward_target((int *)(state + 0x380), 10, 1);
                    if (object[0x43] != 1) anim_start_blended(object, 1, 0, 15);
                }
            }
            break;
        case 3:
            if (!bot_move_toward_waypoint(object, (int)g_hero_position, 1) || SF(0x1DC) < D_L03_001AFEE0 ||
                (SI(0x190) > 60 && SF(0x1DC) < D_L03_001AFEE4)) {
                moby_set_state(object, 4, -1);
                if (object[0x43]) anim_start_blended(object, 0, math_random_int_below(ANIM_FRAMES(0x48)), 10);
            }
            if ((g_frame_l03_counter & 15) == (((int)object >> 8) & 15))
                SI(0x360) = moby_count_teammates_by_side(object, g_hero_position);
            break;
        case 5:
            if (flag_set_first_pending(object)) {
                if (object[0x43] != 2) anim_start_blended(object, 2, math_random_int_below(ANIM_FRAMES(0x50)), 20);
                SF(0x144) = 0.1f;
            }
            point.f[0] = math_fast_sin_or_cos_a(SF(0x374)); point.f[1] = math_fast_sin_or_cos_b(SF(0x374)); point.f[2] = 0;
            FastVecAdd(&point, &point, object + 0x10);
            bot_move_toward_waypoint(object, (int)&point, 1);
            if (*(u16 *)(object + 0x96) >= 61) {
                SF(0x144) = D_L03_001AFEE0;
                moby_set_state(object, 4, 1);
                if (object[0x43]) anim_start_blended(object, 0, math_random_int_below(ANIM_FRAMES(0x48)), 10);
            }
            break;
        case 6:
        case 8:
            if (flag_set_first_pending(object)) {
                if (object[0x20] == 8) { if (object[0x43] != 7) anim_start_blended(object, 7, 0, 20); }
                else if (object[0x43] != 3) anim_start_blended(object, 3, 0, 20);
            }
            moby_start_effect_from_entry((int)object, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - OF(0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - OF(0x14)));
            if (object[0x60] & 2) moby_set_state(object, 4, -1);
            break;

        case 7:
            if (flag_set_first_pending(object)) SF(0x144) = 0.1f;
            if (vec_distance_xy(object + 0x10, state + 0x340) > SF(0x144)) {
                bot_move_toward_waypoint(object, (int)(state + 0x340), 0);
                if (object[0x43] != 2) anim_start_blended(object, 2, math_random_int_below(ANIM_FRAMES(0x50)), 20);
            } else if (object[0x43]) anim_start_blended(object, 0, math_random_int_below(ANIM_FRAMES(0x48)), 20);
            if (math_fast_float_d(state + 0x37C)) moby_set_state(object, 4, -1);
            break;
        case 12:
            bot_move_toward_waypoint(object, (int)(state + 0x340), 0);
            if ((g_frame_l03_counter & 3) == (((int)object >> 8) & 3))
                SF(0x110) = group_is_nearest_to_target(object, state + 0x340) ? 0.11f : 0.15f;
            if (!moby_get_count_in_state_two(SP(0x358))) {
                moby_set_state(object, 4, 1);
                if (object[0x43]) anim_start_blended(object, 0, math_random_int_below(ANIM_FRAMES(0x48)), 10);
            } else if (SF(0x1DC) < SF(0x144)) moby_set_state(object, 13, -1);
            break;
        case 13:
            if (flag_set_first_pending(object)) {
                moby_decrement_count_and_finish(SP(0x358), (u32)object); SF(0x140) = 0.174532949924469f;
                vec_transform_by_object_or_given((char *)SP(0x358), (char *)(state + 0x1B0), (char *)(state + 0x1B0), 0);
                SF(0x1B4) = 0;
                matrix_mul_vec3(state + 0x1B0, state + 0x1B0, SP(0x358) + 0xC0); SF(0x110) = 0;
            }
            bot_move_toward_waypoint(object, (int)(SP(0x358) + 0x10), 0);
            if (vec_distance_xy(object + 0x10, SP(0x358) + 0x10) < 0.1f) { moby_mark_spawned(object); return; }
            break;
        case 9:
            if ((g_frame_l03_counter & 7) == (((int)object >> 8) & 7)) SP(0x358) = moby_find_nearest_tilt_target(object);
            parent = SP(0x194);
            if (parent) {
                if (SP(0x198) && *(s16 *)(SP(0x198) + 0xAA) == 0x97A /* moby class 2426 */) heading = OF(0xF8);
                else {
                    heading = mat_fast_helper_a(*(float *)(parent + 0x10) - OF(0x10), *(float *)(parent + 0x14) - OF(0x14));
                    turn = fast_subtract_rotations(heading, OF(0xF8));
                    heading = FastAddRotations(turn < 0.0f ? -1.5707963705062866f : 1.5707963705062866f, OF(0xF8));
                }
                entity_stun_in_front(object, heading);
            }
            target = SP(0x358);
            if (!target) {
                moby_set_state(object, 11, -1);
                if (object[0x43]) anim_start_blended(object, 0, math_random_int_below(ANIM_FRAMES(0x48)), 20);
                break;
            }
            bot_move_toward_waypoint(object, (int)(target + 0x10), 0);
            if ((g_frame_l03_counter & 3) == (((int)object >> 8) & 3)) {
                qcopy(&point, object + 0x10); point.f[2] += 0.2f;
                vec_scale_to_length(&other, object + 0xC0, 0.3330000042915344f);
                FastVecAdd(&other, &other, object + 0x10); other.f[2] += 0.2f;
                if (CollLine(&point, &other, 0, object, 0) && D_L03_001BFDD8[0] == SP(0x358)) {
                    moby_set_state(object, 10, -1);
                    if (object[0x43] != 4) anim_start_blended(object, 4, 0, 10);
                }
            }
            break;
        case 10:
            if (math_is_value_within_step((char *)object, 14.0f))
                coll_test_hit_at_bone(0.3330000042915344f, 4.0f, 1.0f, object, 1, 0x10000, 0, 1, 0);
            else if (object[0x60] & 2) {
                SP(0x358) = moby_find_nearest_tilt_target(object);
                if (SP(0x358)) {
                    moby_set_state(object, 9, -1);
                    if (object[0x43] != 3) anim_start_blended(object, 3, math_random_int_below(ANIM_FRAMES(0x54)), 10);
                } else {
                    moby_set_state(object, 11, -1);
                    if (object[0x43]) anim_start_blended(object, 0, math_random_int_below(ANIM_FRAMES(0x48)), 10);
                }
            }
            break;
        case 11:
            if ((g_frame_l03_counter & 7) == (((int)object >> 8) & 7)) SP(0x358) = moby_find_nearest_tilt_target(object);
            bot_update_head_tilt(object);
            if (SP(0x358)) {
                moby_set_state(object, 9, -1);
                if (object[0x43] != 3) anim_start_blended(object, 3, math_random_int_below(ANIM_FRAMES(0x54)), 20);
            } else if (*(u16 *)(object + 0x96) >= 301) {
                moby_set_state(object, 4, 1);
                if (object[0x43]) anim_start_blended(object, 0, math_random_int_below(ANIM_FRAMES(0x48)), 20);
            }
            break;
        case 14:
            bot_move_toward_waypoint(object, (int)(state + 0x340), 0);
            if (flag_set_first_pending(object)) D_0018CB2C[0] = -1;
            if (SP(0x194)) entity_stun_in_front(object, FastAddRotations(OF(0xF8), 3.141592741012573f));
            if (SI(0x1A4) & 0x80) moby_set_state(object, 15, -1);
            break;
        case 15:
            if (flag_set_first_pending(object)) {
                if (object[0x43] != 4) anim_start_blended(object, 4, 0, 10);
                *(int *)(object + 0x98) = 0;
                FastVecSub(state + 0x340, state + 0x340, SP(0x358) + 0x10);
                vec_transform_by_object_or_given((char *)SP(0x358), (char *)(state + 0x340), (char *)(state + 0x340), 0);
                SF(0x344) = 0;
                if (SF(0x340) < SF(0x344)) SF(0x340) = -3.8f;
                else SF(0x340) = 3.8f;
                matrix_mul_vec3(state + 0x340, state + 0x340, SP(0x358) + 0xC0);
                FastVecAdd(state + 0x340, state + 0x340, SP(0x358) + 0x10);
            }
            heading = mat_fast_helper_a(*(float *)(SP(0x358) + 0x10) - OF(0x10), *(float *)(SP(0x358) + 0x14) - OF(0x14));
            moby_start_effect_from_entry((int)object, heading);
            if (moby_get_anim_value((char *)object) > 11.0f) vec_step_toward_target_limited(object + 0x10, state + 0x340, 0.13333334f);
            if (object[0x60] & 2) {
                route_set_node_enabled_flag(SI(0x220), SP(0x358) + 0x10, 1);
                moby_set_state(object, 16, -1);
                if (object[0x43] != 5) anim_start_blended(object, 5, 0, 5);
                moby_set_flag_bit(SP(0x358), 1);
            }
            break;
        case 16:
            if (flag_set_first_pending(object)) SP(0x198) = 0;
            if (vec_distance_xy(g_hero_position, SP(0x358) + 0x10) > 12.0f &&
                !group_is_state_word_matching(object) && !moby_check_against_stored_value(SP(0x358), g_hero_position))
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
            if (SP(0x194)) entity_stun_in_front(object, FastAddRotations(OF(0xF8), 3.141592741012573f));
            if (SI(0x1A4) & 0x80) {
                moby_set_state(object, 19, -1);
                moby_set_flag_bit(SP(0x358), 1);
            }
            break;
        case 19:
            if (flag_set_first_pending(object) && object[0x43] != 4) anim_start_blended(object, 4, 0, 10);
            moby_start_effect_from_entry((int)object, mat_fast_helper_a(*(float *)(SP(0x358) + 0x10) - OF(0x10), *(float *)(SP(0x358) + 0x14) - OF(0x14)));
            if (object[0x42] == object[0x43]) {
                if (moby_get_anim_value((char *)object) >= 10.0f) {
                    moby_transform_joint_to_world((char *)object, 3, (char *)&point);
                    moby_set_height_offset(SP(0x358), point.f[2] - OF(0x18));
                }
                if (object[0x60] & 2) {
                    moby_set_state(object, 6, 1); moby_set_flag_bit(SP(0x358), 0);
                }
            }
            D_0018CF58[0] = -1;
            break;
        case 20:
            bot_move_toward_waypoint(object, (int)(state + 0x340), 0);
            if (SP(0x194)) entity_stun_in_front(object, FastAddRotations(OF(0xF8), 3.141592741012573f));
            if (SI(0x1A4) & 0x80) moby_set_state(object, 21, -1);
            break;
        case 21:
            if (flag_set_first_pending(object)) {
                if (object[0x43] != 5) anim_start_blended(object, 5, 0, 10);
                D_0018CDE4[0] = -1;
            }
            moby_start_effect_from_entry((int)object, mat_fast_helper_a(*(float *)(SP(0x358) + 0x10) - OF(0x10), *(float *)(SP(0x358) + 0x14) - OF(0x14)));
            if (object[0x60] & 2) moby_set_state(object, 6, 1);
            else if (math_is_value_within_step((char *)object, 20.0f)) moby_set_flag_bit(SP(0x358), 1);
            break;
        case 22: {
            MotionVector *offset;
            FastVecAdd(object + 0x10, object + 0x10, state + 0x1B0);
            qzero_nc(&point); qzero_nc(&other);
            type = *(s16 *)(object + 0xAA);
            height = 0.8f;
            switch (type) {
            case 0x964 /* Gadgebot */:
                height = 0.3f;
            case 0x940 /* Bridgebot */:
            case 0x93C /* moby class 2364 */:
            default:
                do {
                    point.f[2] = height;
                } while (0);
                other.f[2] = height;
                break;
            }
            offset = &other;
            matrix_mul_vec3(&point, &point, object + 0xC0);
            if (SF(0x1B8) < 0.0f) {
                SF(0x1B8) -= SF(0x398);
                if (OF(0xF4) > 0.0f) math_step_value_toward_target(object + 0xF4, state + 0x39C, 0, 0.006981317885220051f, 0.006981317885220051f, 0.41887909173965454f);
                else OF(0xF4) = fast_subtract_rotations(OF(0xF4), 0.41887909173965454f);
                if (OF(0x18) < SF(0x3A0)) {
                    floor = coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
                    if (OF(0x18) <= floor) {
                        OF(0x18) = floor; moby_set_state(object, 4, 1);
                        for (member = D_L03_001B2A1C; member <= D_L03_001B2A20; member += 256) {
                            if (*(s16 *)(member + 0xAA) == 0xF2D /* moby class 3885 */ && route_check_object_points(member, object + 0x10, object + 0x10)) {
                                SI(0x220) = ((int)member - (int)D_L03_001B2A1C) >> 8;
                                SI(0x368) = -1; SI(0x36C) = -1;
                            }
                        }
                    }
                }
            } else {
                SF(0x1B8) -= SF(0x394); OF(0xF4) = fast_subtract_rotations(OF(0xF4), 0.41887909173965454f);
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
    if (code != 22 && code != 1 && code != 15 && code != 16 && (SF(0x1A0) < OF(0x18) - 0.05f || SP(0x198))) {
        float zero = 0.0f;
        OF(0xF0) = zero; OF(0xF4) = zero; moby_step_at_own_position((char *)object);
    }
    bot_update_timers_and_path(object);
    func_002A677C(object);
}
