#include "names.h"
/* func_L04_0044DB18: the Barlow beast state machine (10,064 bytes, US and US2;
 * absent from PAL). Both switches are written in retail case-body order. Callee
 * prototypes follow their matched callers: argument registers are loaded in
 * parameter order, so func_002A7EA0 takes its int after the four floats and
 * func_002A8C28 its three floats before the three ints, and func_002B60B0
 * returns nothing (an unused return value moves local-alloc choices).
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } BeastVector;
typedef struct {
    u8 reserved00[0x18]; u8 enabled, count, kind; u8 reserved1B[0x65]; u8 payload[1];
} DispatchContext;
extern u8 g_tribesman_flag[];
extern u8 *g_route_path_table[];
extern u16 *g_moby_l04_group_lists[];
extern u8 *g_moby_l04_pool __attribute__((sda));
extern int g_tribesman_group_limit __attribute__((sda));
extern int tribesman_update_common(u8 *);
extern int flag_set_second_pending(u8 *);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern float math_fabs(float);
extern int math_fast_float_d(void *);
extern void anim_start_blended(u8 *, int, int, int);
extern int math_random_int_range(int, int), math_random_int_below(int);
extern void moby_set_state(u8 *, u8, int);
extern float vec_distance_xy(void *, void *), mat_fast_helper_a(float, float);
extern int path_set_follower_nodes(void *, void *, int, int);
extern int moby_step_controller(void *, void *, float);
extern u32 moby_dispatch_action_by_kind(void *, DispatchContext *);
extern void moby_copy_joint_transform_to_object(void *, void *, int, int);
extern void part_spawn_explosion_with_sparks(void *, void *, int, float, float);
extern void moby_mark_spawned(void *);
extern int linked_part_consume_timer(char *);
extern u8 *CreateMoby(int);
extern void func_002A0F48(void *), euler_rotation_basis(void *, void *);
extern float moby_get_anim_value(char *), coll_probe_ground_height_below(void *, int, float);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern void SetDeathBits(void *, int, int);
extern void part_queue_moby_for_glow(void *, unsigned int, void (*)(void *));
extern int moby_move_over_ground(void *, void *, void *, float, float, float, float, int);
extern float ApproachValue(float *, float, float);
extern void enemy_update_wander_heading(void *, void *, void *);
extern float fast_subtract_rotations(float, float), FastDiffRots(float, float);
extern int flag_is_third_pending_set(u8 *), path_follow_nodes(char *, char *), moby_count_group_not_in_state(int, int);
extern u8 *moby_find_linked_object(u8 *);
struct family_27f9_object;
extern float moby_turn_toward_position(struct family_27f9_object *, float *, float *, float, float, float);
extern int moby_l01_turn_toward_target(char *, char *);
extern int enemy_walk_toward_target(u8 *, void *, float, float, float, float);
extern int moby_turn_toward_target_and_step(char *, float *, float);
extern void moby_transform_joint_to_world(char *, int, char *);
extern int coll_sweep_from_object(void *, void *, int, float, float, float, int, int, int);
extern void enemy_tick_timers_blend(char *);
#define I(o) (*(s32 *)(state + (o)))
#define U(o) (*(u32 *)(state + (o)))
#define F(o) (*(float *)(state + (o)))
#define S(o) (*(s16 *)(state + (o)))
#define US(o) (*(u16 *)(state + (o)))
#define P(o) (*(u8 **)(state + (o)))
#define OF(o) (*(float *)(object + (o)))

/* Updates the beast's rider mode, route following and close-range action states. */
/* Per-frame update for the Tribesman (moby class 4088). */
void tribesman_l04_update(u8 *object)
{
    BeastVector offset, target, lateral;
    u8 *state;
    u8 *other, *route, *entity, *linked;
    u16 *ids;
    float oldHeight = OF(0x18);
    float distance, angle, turn, nearest, firstDistance, lastDistance;
    int i, selected, random, animation;
    u32 dispatch;
    state = *(u8 **)(object + 0x68);
    if (tribesman_update_common(object)) { moby_mark_spawned(object); return; }
    switch (object[0x95]) {
    case 0:
        if (flag_set_second_pending(object))
            moby_set_controller_speed_limits(object, 0.0016666667f, 0.05000000447034836f, 0.0011635529808700085f, 0.10471977f);
        if ((I(0x258) == 1 || (I(0x560) != 0 && S(0x274) == 2)) &&
            math_fabs(*(float *)(P(0x240) + 0x18) - OF(0x18)) < 2.0f) {
            if (math_fast_float_d(state + 0x2B0)) {
                g_tribesman_flag[0] = 1;
                if (I(0x29C) != -1) {
                    if (object[0x43] != 12) anim_start_blended(object, 12, 0, 10);
                    moby_set_state(object, 22, 2);
                } else if (I(0x2A4) == 1) {
                    if (object[0x43] != 31) anim_start_blended(object, 31, 0, math_random_int_range(10, 20));
                    moby_set_state(object, 17, 2);
                } else {
                    I(0x2A0) = 1;
                    if (math_random_int_below(3) == 1) {
                        if (object[0x43] != 11) anim_start_blended(object, 11, 0, 10);
                        moby_set_state(object, 17, 3);
                    } else {
                        if (object[0x43] != 12) anim_start_blended(object, 12, 0, 10);
                        moby_set_state(object, 19, 3);
                    }
                }
                goto mode_complete;
            }
        }
        if (S(0x276) != 0) {
            if (I(0x570) != -1 && I(0x574) == 1) {
                if (object[0x43] != 24) anim_start_blended(object, 24, 0, math_random_int_range(5, 15));
                moby_set_state(object, 6, -1);
            } else if (I(0x570) != -1 && I(0x574) > 1) {
                if (object[0x43] != 12) anim_start_blended(object, 12, 0, math_random_int_range(5, 15));
                moby_set_state(object, 7, -1);
                moby_set_controller_speed_limits(object, 0.003888888983055949f, 0.11666667461395264f, 0.003393696155399084f, 0.2617994248867035f);
            } else {
                object[0x95] = 1;
                if (object[0x43] != 24) anim_start_blended(object, 24, 0, 20);
            }
            if ((u32)(US(0x274) - 1) < 2 && math_fabs(*(float *)(P(0x240) + 0x18) - OF(0x18)) < 2.0f) {
                if (I(0x29C) != -1) {
                    if (object[0x43] != 12) anim_start_blended(object, 12, 0, 10);
                    moby_set_state(object, 22, 2);
                } else if (I(0x2A4) == 1) {
                    if (object[0x43] != 31) anim_start_blended(object, 31, 0, math_random_int_range(10, 20));
                    moby_set_state(object, 17, 2);
                } else {
                    I(0x2A0) = 1;
                    if (object[0x43] != 11) anim_start_blended(object, 11, 0, 10);
                    moby_set_state(object, 17, 3);
                }
            }
            S(0x276) = 0;
        }
        break;
    case 1:
        if (flag_set_second_pending(object)) {
            moby_set_controller_speed_limits(object, 0.003888888983055949f, 0.11666667461395264f, 0.0011635529808700085f, 0.10471977f);
            F(0x12C) = 6.0f; F(0x298) = 6.0f;
        }
        if (I(0x258) != 1 && I(0x25C) != 1) break;
        I(0x178) &= ~0x10;
        if (I(0x29C) != -1) {
            if (object[0x43] != 12) anim_start_blended(object, 12, 0, 10);
            moby_set_state(object, 22, 2);
            selected = 0; nearest = 100.0f;
            for (i = 0; i < *(int *)g_route_path_table[I(0x29C)]; i++) {
                float d = vec_distance_xy(object + 0x10, g_route_path_table[I(0x29C)] + 0x10 + i * 16);
                if (d < nearest) { nearest = d; selected = i; }
            }
            path_set_follower_nodes(object, g_route_path_table[I(0x29C)], -1, selected);
        } else if (I(0x2A4) == 1) {
            if (object[0x43] != 12) anim_start_blended(object, 12, 0, 10);
            moby_set_state(object, 21, 2);
        } else {
            I(0x2A0) = 1;
            if (object[0x43] != 11) anim_start_blended(object, 11, 0, 10);
            moby_set_state(object, 17, 3);
        }
        break;
    case 2:
        if (flag_set_second_pending(object))
            moby_set_controller_speed_limits(object, 0.003888888983055949f, 0.11666667461395264f, 0.0011635529808700085f, 0.10471977293491364f);
        if (I(0x258) == 1 || I(0x25C) == 1 || I(0x560) != 0) break;
        random = math_random_int_below(4);
        if (random == 0) {
            if (object[0x43] != 25) anim_start_blended(object, 25, 0, math_random_int_range(10, 20));
        } else if (random == 1) {
            if (object[0x43] != 17) anim_start_blended(object, 17, 0, math_random_int_range(20, 30));
        } else if (random == 2) {
            if (object[0x43] != 30) anim_start_blended(object, 30, 0, math_random_int_range(20, 30));
        } else if (object[0x43] != 24) anim_start_blended(object, 24, 0, math_random_int_range(20, 30));
        moby_set_state(object, 12, 1);
        break;
    case 4:
        if (F(0x20) > 0.0f) {
            u8 *position = object + 0x10;
            angle = mat_fast_helper_a(*(float *)(P(0x240) + 0x10) - OF(0x10), *(float *)(P(0x240) + 0x14) - OF(0x14));
            moby_step_controller(object, position, angle);
        }
        dispatch = moby_dispatch_action_by_kind(object, (DispatchContext *)(state + 0x60));
        if (dispatch & 1) { SetDeathBits(object, 0, 3); part_queue_moby_for_glow(object, 0, 0); return; }
        if (dispatch & 2) {
            S(0x26) = 0;
            if ((I(0x258) == 1 || I(0x25C) == 1) && math_fabs(*(float *)(P(0x240) + 0x18) - OF(0x18)) < 2.0f) {
                if (object[0x43] != 12) anim_start_blended(object, 12, 0, 10);
                moby_set_state(object, 21, 2);
                if (state[0x37] != 10) break;
                if (object[0x43] != 14) anim_start_blended(object, 14, 9, 4);
                moby_set_controller_speed_limits(object, 0.003888888983055949f, 0.11666667461395264f, 0.0011635529808700085f, 0.10471977f);
                moby_set_state(object, 23, 2);
            } else if (I(0x570) != -1) {
                if (object[0x43] != 12) anim_start_blended(object, 12, 0, math_random_int_range(5, 15));
                moby_set_state(object, 7, 0);
                moby_set_controller_speed_limits(object, 0.003888888983055949f, 0.11666667461395264f, 0.003393696155399084f, 0.2617994248867035f);
            } else {
                if (object[0x43] != 10) anim_start_blended(object, 10, 0, 10);
                moby_set_state(object, 12, 1);
                S(0x270) = math_random_int_range(580, 600);
            }
        }
        break;
    case 3:
        if (flag_set_second_pending(object))
            moby_set_controller_speed_limits(object, 0.003888888983055949f, 0.11666667461395264f, 0.0011635529808700085f, 0.10471977293491364f);
        if (I(0x2A4) == 1) {
            if (object[0x43] != 12) anim_start_blended(object, 12, 0, 10);
            moby_set_state(object, 21, 2);
        }
        if (I(0x258) == 1 || I(0x25C) == 1) break;
        random = math_random_int_below(4);
        if (random == 0) {
            if (object[0x43] != 11) anim_start_blended(object, 11, 0, 10);
        } else if (random == 1) {
            if (object[0x43] != 17) anim_start_blended(object, 17, 0, 20);
        } else if (random == 2) {
            if (object[0x43] != 30) anim_start_blended(object, 30, 0, 20);
        } else if (object[0x43] != 24) anim_start_blended(object, 24, 0, 20);
        moby_set_state(object, 12, 1);
        break;
    case 5:
        if (P(0x288)) moby_copy_joint_transform_to_object(object, P(0x288), 1, 0);
        linked = P(0x284);
        *(Quad *)(object + 0x10) = *(Quad *)(linked + 0x10);
        *(Quad *)(object + 0xF0) = *(Quad *)(linked + 0xF0);
        {
            u8 *rider = P(0x290);
            *(Quad *)(rider + 0x10) = *(Quad *)(object + 0x10);
            *(Quad *)(rider + 0xF0) = *(Quad *)(object + 0xF0);
            *(Quad *)(rider + 0x10) = *(Quad *)(object + 0x10);
            *(float *)(rider + 0x18) += 0.65f;
        }
        if (I(0x27C) == 0) {
            part_spawn_explosion_with_sparks(object, P(0x288) + 0x10, -1, 0.5f, 3.0f);
            if (P(0x288)) { moby_mark_spawned(P(0x288)); P(0x288) = 0; }
            moby_mark_spawned(P(0x290));
            *(u8 **)(*(u8 **)(P(0x284) + 0x68) + 0x2AC) = 0;
            moby_set_state(object, 2, 6);
        } else if (linked_part_consume_timer((char *)object)) {
            part_spawn_explosion_with_sparks(object, P(0x288) + 0x10, -1, 0.5f, 3.0f);
            if (P(0x288)) { moby_mark_spawned(P(0x288)); P(0x288) = 0; }
            moby_mark_spawned(P(0x290));
            *(u8 **)(*(u8 **)(P(0x284) + 0x68) + 0x2AC) = 0;
            if (object[0x43] != 9) anim_start_blended(object, 9, 0, 0);
            moby_set_state(object, 3, 6);
        }
        break;
    case 6:
        if (flag_set_second_pending(object)) {
            P(0x2AC) = CreateMoby(0x9AC /* moby class 2476 */);
            if (!P(0x2AC)) { moby_mark_spawned(object); return; }
            P(0x2AC)[0x30] = object[0x30]; *(u16 *)(P(0x2AC) + 0x32) = *(u16 *)(object + 0x32);
            P(0x2AC)[0x31] = 1; *(unsigned long *)(P(0x2AC) + 0x38) = *(unsigned long *)(object + 0x38);
            func_002A0F48(P(0x2AC)); *(int *)(P(0x2AC) + 0x98) = 0;
            moby_copy_joint_transform_to_object(object, P(0x2AC), 3, 0);
            I(0x2A0) = 1; OF(0xF0) = 0; OF(0xF4) = 0;
            euler_rotation_basis(object + 0xC0, object + 0xF0);
        }
        break;
    }
    mode_complete:
    switch (object[0x20]) {
    case 1:
        break;
    case 2:
        if (object[0x60] & 2) {
            if (F(0x20) > 0.0f) {
                I(0x178) &= ~0x10; *(u16 *)(object + 0x34) |= 0x5000;
                *(u32 *)(object + 0x98) = *(u32 *)(*(u8 **)(object + 0x24) + 0x10);
                moby_set_state(object, 12, 1);
                if (S(0x270) < 300) S(0x270) = math_random_int_range(480, 600);
                if (object[0x43] != 11) anim_start_blended(object, 11, 0, 10);
            } else {
                SetDeathBits(object, 0, 3); part_queue_moby_for_glow(object, 0, 0); return;
            }
        }
        {
            float dist = moby_get_anim_value((char *)object);
            if (dist >= 10.0f) OF(0x18) = coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
            if (dist >= 1.5f && dist <= 17.0f) {
                u8 *pos = object + 0x10;
                U(0x178) |= 0x10;
                offset.f[0] = math_fast_sin_or_cos_a(OF(0xF8) + 3.1415929794311523f) * 0.15f;
                offset.f[1] = math_fast_sin_or_cos_b(OF(0xF8) + 3.1415929794311523f) * 0.15f;
                offset.f[2] = 0;
                FastVecAdd(&target, pos, &offset);
                lateral.f[0] = math_fast_sin_or_cos_a(OF(0xF8) + 1.5707964897155762f) * 0.05f;
                lateral.f[1] = math_fast_sin_or_cos_b(OF(0xF8) + 1.5707964897155762f) * 0.05f;
                lateral.f[2] = 0;
                FastVecAdd(&target, pos, &lateral);
                moby_move_over_ground(object, pos, &target, 0.5f, 0.55f, 0.5f, 0.523598849773407f, 0);
            }
        }
        break;
    case 3:
        if (object[0x60] & 2) {
            if (F(0x20) > 0.0f) {
                I(0x178) &= ~0x10; *(u16 *)(object + 0x34) |= 0x5000;
                *(u32 *)(object + 0x98) = *(u32 *)(*(u8 **)(object + 0x24) + 0x10);
                moby_set_state(object, 12, 1);
                if (S(0x270) < 300) S(0x270) = math_random_int_range(480, 600);
                if (object[0x43] != 11) anim_start_blended(object, 11, 0, 10);
            } else {
                SetDeathBits(object, 0, 3); part_queue_moby_for_glow(object, 0, 0); return;
            }
        }
        {
            float dist = moby_get_anim_value((char *)object);
            if (dist >= 10.0f) OF(0x18) = coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
            if (dist >= 1.5f && dist <= 17.0f) {
                u8 *pos = object + 0x10;
                U(0x178) |= 0x10;
                offset.f[0] = math_fast_sin_or_cos_a(OF(0xF8) + 3.1415929794311523f) * 0.15f;
                offset.f[1] = math_fast_sin_or_cos_b(OF(0xF8) + 3.1415929794311523f) * 0.15f;
                offset.f[2] = 0;
                target.f[0] = math_fast_sin_or_cos_a(OF(0xF8) + 1.5707964897155762f) * 0.05f;
                target.f[1] = math_fast_sin_or_cos_b(OF(0xF8) + 1.5707964897155762f) * 0.05f;
                target.f[2] = 0; lateral.q = *(Quad *)(pos);
                FastVecAdd(&lateral, pos, &target);
                FastVecAdd(&lateral, pos, &offset);
                moby_move_over_ground(object, pos, &lateral, 0.5f, 0.55f, 0.5f, 0.523598849773407f, 0);
            }
        }
        break;
    case 4:
        if (F(0x298) > 0.2f) {
            math_fast_float_d(state + 0x294);
            animation = object[0x43];
            if ((animation != 13 && animation != 10) || (animation == 10 && I(0x294) != 0)) {
                if (object[0x43] != 13) anim_start_blended(object, 13, 0, 14);
            }
            if (I(0x294) > 20)
                ApproachValue((float *)(state + 0x124), 0.05000000447034836f, 0.0008333333535119891f);
            else
                ApproachValue((float *)(state + 0x124), 0.0f, 0.0008333333535119891f);
            if (object[0x43] == 13) {
                if (I(0x294) == 0) anim_start_blended(object, 10, 0, 12);
                enemy_update_wander_heading(object, state + 0x110, state + 0x140);
            } else if (object[0x43] == 10 && (object[0x60] & 2)) {
                I(0x294) = math_random_int_range(120, 700);
                if (object[0x43] != 13) anim_start_blended(object, 13, 0, 12);
            }
        }
        break;
    case 5:
        if (I(0x564) == 3) {
            float limit = 1.5707964897155762f;
            angle = mat_fast_helper_a(*(float *)(P(0x56C) + 0x10) - OF(0x10), *(float *)(P(0x56C) + 0x14) - OF(0x14));
            turn = fast_subtract_rotations(angle, OF(0xF8));
            if (flag_is_third_pending_set(object)) turn = -turn;
            if (turn > limit) turn = limit;
            else if (turn < -limit) turn = -limit;
            F(0x328) = turn;
        }
        if (I(0x564) == 1 && object[0x42] == 28 && math_random_int_below(200) == 1) {
            if (object[0x43] != 27) anim_start_blended(object, 27, 0, 30);
            if (math_random_int_below(3) == 1 && object[0x43] != 26) anim_start_blended(object, 26, 0, 30);
        }
        if ((u32)(object[0x42] - 26) < 2 && (object[0x60] & 2)) {
            if (object[0x43] != 29) anim_start_blended(object, 29, 0, 30);
            if (*(s16 *)(P(0x56C) + 0xAA) == MOBY_CLASS_TRIBESMAN) {
                *(int *)(*(u8 **)(P(0x56C) + 0x68) + 0x564) = 1; I(0x564) = 2;
            }
        }
        if (object[0x42] == 29 && (object[0x60] & 2)) {
            if (object[0x43] != 30) anim_start_blended(object, 30, 0, 30);
            if (I(0x564) == 1 && object[0x43] != 28) anim_start_blended(object, 28, 0, 30);
            if (I(0x564) == 3) {
                ids = g_moby_l04_group_lists[object[0x21]];
                for (;;) {
                    entity = g_moby_l04_pool + ((*ids & 0x7FFF) << 8);
                    if (*(s8 *)(entity + 0x20) >= 0 && *(s16 *)(entity + 0xAA) == MOBY_CLASS_TRIBESMAN &&
                        *(int *)(*(u8 **)((g_moby_l04_pool + ((*ids & 0x7FFF) << 8)) + 0x68) + 0x564) == 1) {
                        P(0x56C) = g_moby_l04_pool + ((*ids & 0x7FFF) << 8);
                        break;
                    }
                    if ((s16)*ids++ < 0) break;
                }
            }
        }
        if (I(0x564) == 1 && object[0x42] == 30 && object[0x43] != 29) anim_start_blended(object, 29, 0, 20);
        if (I(0x564) == 3 && P(0x56C)[0x42] == 29 && object[0x43] != 29) anim_start_blended(object, 29, 0, 35);
        break;
    case 6:
        I(0x2A0) = 1;
        if (object[0x60] & 2) {
            moby_set_state(object, 7, -1);
            if (object[0x43] != 13) anim_start_blended(object, 13, 0, 30);
            I(0x2A0) = 0;
        }
        break;
    case 7:
        if (path_follow_nodes((char *)object, (char *)g_route_path_table[I(0x570)])) {
            moby_set_state(object, 9, -1);
            if (object[0x43] != 24) anim_start_blended(object, 24, 0, 20);
        }
        break;
    case 9:
        if (object[0x60] & 2) {
            moby_set_controller_speed_limits(object, 0.0016666667f, 0.05000000447034836f, 0.0011635529808700085f, 0.10471977f);
            if (moby_count_group_not_in_state(object[0x21], -1) > 1) {
                P(0x56C) = (u8 *)moby_find_linked_object(object);
                moby_set_state(object, 11, -1);
                if (object[0x43] != 28) anim_start_blended(object, 28, 0, 30);
                I(0x564) = 1;
                if (P(0x56C)[0x42] == 28) {
                    if (object[0x43] != 30) anim_start_blended(object, 30, 0, 30);
                    I(0x564) = 2;
                }
            }
        }
        break;
    case 11: {
        u8 *position = object + 0x10;
        angle = mat_fast_helper_a(*(float *)(P(0x56C) + 0x10) - OF(0x10), *(float *)(P(0x56C) + 0x14) - OF(0x14));
        moby_step_controller(object, position, angle);
        angle = mat_fast_helper_a(*(float *)(P(0x56C) + 0x10) - OF(0x10), *(float *)(P(0x56C) + 0x14) - OF(0x14));
        if (FastDiffRots(OF(0xF8), angle) < 0.087266475f) moby_set_state(object, 5, -1);
        break;
    }
    case 12:
        if (F(0x298) > 0.2f) {
            moby_turn_toward_position((struct family_27f9_object *)object, (float *)P(0x240), (float *)(state + 0x28C), 0.001f, 0.01f, 0.1f);
            if (object[0x60] & 2) {
                if (object[0x43] != 22) anim_start_blended(object, 22, 0, 20);
                moby_set_state(object, 13, -1); U(0x178) |= 0x10;
                if (I(0x578) != -1) *(Quad *)(state + 0x110) = *(Quad *)(g_route_path_table[I(0x578)] + 0x10);
            }
        }
        break;
    case 13:
        moby_turn_toward_position((struct family_27f9_object *)object, (float *)P(0x240), (float *)(state + 0x28C), 0.001f, 0.01f, 0.1f);
        moby_set_controller_speed_limits(object, 0.0005555555690079927f, 0.016666668f, 0.0011635529808700085f, 0.10471977f);
        moby_l01_turn_toward_target((char *)object, (char *)(state + 0x110));
        if (vec_distance_xy(object + 0x10, state + 0x110) < 2.0f) {
            I(0x178) &= ~0x10; moby_set_state(object, 14, -1);
            if (object[0x43] != 24) anim_start_blended(object, 24, 0, 20);
            if (I(0x578) != -1) moby_set_state(object, 16, -1);
        }
        break;
    case 15:
        moby_set_controller_speed_limits(object, 0.0016666667f, 0.05000000447034836f, 0.0037815470714122057f, 0.29670602083206177f);
        if (path_follow_nodes((char *)object, (char *)g_route_path_table[I(0x578)])) {
            moby_set_state(object, 16, -1);
            if (object[0x43] != 24) anim_start_blended(object, 24, 0, 20);
        }
        break;
    case 16:
        if (object[0x60] & 2) {
            route = g_route_path_table[I(0x578)];
            firstDistance = vec_distance_xy(object + 0x10, route + 0x10);
            lastDistance = vec_distance_xy(object + 0x10, route + *(int *)route * 16);
            if (lastDistance < firstDistance) path_set_follower_nodes(object, g_route_path_table[I(0x578)], 0, *(int *)route - 1);
            else path_set_follower_nodes(object, g_route_path_table[I(0x578)], *(int *)route - 1, 0);
            moby_set_state(object, 15, -1);
            if (object[0x43] != 13) anim_start_blended(object, 13, 0, 20);
        }
        break;
    case 21:
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 5.0f && F(0x20) > 1.0f) {
            I(0x2A0) = 1;
            moby_set_controller_speed_limits(object, 0.0005555555690079927f, 0.016666668f, 0.0011635529808700085f, 0.10471977f);
            moby_set_state(object, 20, -1);
            if (object[0x43] != 22) anim_start_blended(object, 22, 0, 10);
            break;
        }
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 2.5f) {
            angle = mat_fast_helper_a(F(0x230) - OF(0x10), F(0x234) - OF(0x14));
            if (FastDiffRots(OF(0xF8), angle) < 0.3490659f) {
                if (object[0x43] != 14) anim_start_blended(object, 14, 0, 10);
                moby_set_controller_speed_limits(object, 0.003888888983055949f, 0.11666667461395264f, 0.0011635529808700085f, 0.10471977f);
                moby_set_state(object, 23, 2);
                break;
            }
        }
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 2.5f) {
            angle = mat_fast_helper_a(*(float *)(P(0x240) + 0x10) - OF(0x10), *(float *)(P(0x240) + 0x14) - OF(0x14));
            moby_step_controller(object, object + 0x10, angle);
            break;
        }
        if (I(0x548) != 0) {
            if (enemy_walk_toward_target(object, state + 0x230, OF(0xF8), 7.0f, 0.25f, F(0x2A8)) &&
                object[0x21] <= g_tribesman_group_limit && moby_count_group_not_in_state(object[0x21], -1) > 1) {
                u16 *list = g_moby_l04_group_lists[object[0x21]];
                do {
                    other = *(u8 **)(g_moby_l04_pool + ((*list & 0x7FFF) << 8) + 0x68);
                    if (*(int *)(other + 0x2A4) == 0) {
                        firstDistance = vec_distance_xy(object + 0x10, P(0x240) + 0x10);
                        lastDistance = vec_distance_xy(object + 0x10, P(0x240) + 0x10);
                        if (firstDistance < lastDistance && *(float *)(other + 0x20) > 0.0f) {
                            *(int *)(other + 0x2A4) = 1; I(0x2A4) = 0;
                            if (object[0x43] != 11) anim_start_blended(object, 11, 0, 10);
                            moby_set_state(object, 17, 3);
                        }
                        break;
                    }
                } while ((s16)*list++ >= 0);
            }
        } else moby_turn_toward_target_and_step((char *)object, (float *)(state + 0x230), F(0x2A8));
        break;
    case 17:
        I(0x2A0) = 0;
        angle = mat_fast_helper_a(*(float *)(P(0x240) + 0x10) - OF(0x10), *(float *)(P(0x240) + 0x14) - OF(0x14));
        moby_step_controller(object, object + 0x10, angle);
        if (object[0x60] & 2) {
            distance = vec_distance_xy(object + 0x10, P(0x240) + 0x10);
            if (distance < 12.0f) {
                I(0x2A0) = 1;
                if (object[0x43] != 20) anim_start_blended(object, 20, 0, 10);
                moby_set_state(object, 18, -1);
            } else {
                I(0x2A0) = 1;
                if (object[0x43] != 12) anim_start_blended(object, 12, 0, 10);
                moby_set_state(object, 19, 3);
            }
            if (I(0x2A4) != 0) {
                if (object[0x43] != 12) anim_start_blended(object, 12, 0, 10);
                moby_set_state(object, 21, 2);
            }
        }
        break;
    case 18:
        moby_turn_toward_position((struct family_27f9_object *)object, (float *)P(0x240), (float *)(state + 0x28C), 0.001f, 0.01f, 0.1f);
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) > 12.0f && math_random_int_below(10) == 1) {
            if (object[0x43] != 12) anim_start_blended(object, 12, 0, 10);
            moby_set_state(object, 19, -1);
        }
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 2.5f) {
            if (object[0x43] != 14) anim_start_blended(object, 14, 0, 10);
            moby_set_state(object, 23, -1);
        }
        if (math_random_int_below(3) == 1 && (object[0x60] & 2)) {
            if (object[0x43] != 25) anim_start_blended(object, 25, 0, 10);
            if (math_random_int_below(3) == 1 && object[0x43] != 24) anim_start_blended(object, 24, 0, 10);
            moby_set_state(object, 17, 3);
        }
        break;
    case 19:
        if (I(0x548) != 0) {
            if (enemy_walk_toward_target(object, state + 0x230, OF(0xF8), 7.0f, 0.25f, F(0x2A8))) {
                if (object[0x43] != 20) anim_start_blended(object, 20, 0, 10);
                moby_set_state(object, 18, -1);
            }
        } else {
            moby_turn_toward_target_and_step((char *)object, (float *)(state + 0x230), F(0x2A8));
        }
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 8.0f) {
            if (object[0x43] != 20) anim_start_blended(object, 20, 0, 10);
            moby_set_state(object, 18, -1);
        }
        break;
    case 20:
        distance = vec_distance_xy(object + 0x10, P(0x240) + 0x10);
        if (distance < 2.5f) {
            angle = mat_fast_helper_a(F(0x230) - OF(0x10), F(0x234) - OF(0x14));
            if (FastDiffRots(OF(0xF8), angle) < 0.3490659f) {
                if (object[0x43] != 14) anim_start_blended(object, 14, 0, 6);
                moby_set_controller_speed_limits(object, 0.003888888983055949f, 0.11666667461395264f, 0.0011635529808700085f, 0.10471977f);
                moby_set_state(object, 23, 2);
                break;
            }
        }
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 2.5f) {
            angle = mat_fast_helper_a(*(float *)(P(0x240) + 0x10) - OF(0x10), *(float *)(P(0x240) + 0x14) - OF(0x14));
            moby_step_controller(object, object + 0x10, angle);
            break;
        }
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) > 9.0f && math_random_int_below(4) == 1) {
            moby_set_controller_speed_limits(object, 0.003888888983055949f, 0.11666667461395264f, 0.0011635529808700085f, 0.10471977f);
            goto return_to_follow;
        } else {
            moby_set_controller_speed_limits(object, 0.0005555555690079927f, 0.016666668f, 0.0011635529808700085f, 0.10471977f);
            moby_turn_toward_target_and_step((char *)object, (float *)(state + 0x230), F(0x2A8));
        }
        break;
    case 22:
        F(0x174) = 1.5f;
        if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 2.5f) {
            if (object[0x43] != 14) anim_start_blended(object, 14, 0, 2);
            moby_set_state(object, 23, -1); I(0x29C) = -1; F(0x164) = 0.0008333333535119891f;
        } else {
            F(0x164) = 0.004166666883975267f;
            if (path_follow_nodes((char *)object, (char *)g_route_path_table[I(0x29C)])) {
                if (I(0x2A4) == 1) {
                    if (object[0x43] != 12) anim_start_blended(object, 12, 0, 10);
                    moby_set_state(object, 21, 2);
                } else {
                    I(0x2A0) = 1;
                    if (math_random_int_below(3) == 1) {
                        if (object[0x43] != 11) anim_start_blended(object, 11, 0, 10);
                        moby_set_state(object, 17, 3);
                    } else {
                        if (object[0x43] != 12) anim_start_blended(object, 12, 0, 10);
                        moby_set_state(object, 19, 3);
                    }
                }
                I(0x29C) = -1;
            }
        }
        break;
    case 23:
        I(0x2A0) = 0;
        distance = moby_get_anim_value((char *)object);
        if (object[0x42] == 14) {
            if (distance >= 10.0f && distance <= 15.0f) {
                moby_transform_joint_to_world((char *)object, 2, (char *)&offset);
                target.f[0] = math_fast_sin_or_cos_a(OF(0xF8)) * 0.5f;
                target.f[1] = math_fast_sin_or_cos_b(OF(0xF8)) * 0.5f; target.f[2] = 0;
                FastVecAdd(&offset, &offset, &target);
                coll_sweep_from_object(object, &offset, 0x04000001, 0.4f, F(0x2BC), 1.0f, 0, 1, 0);
                target.f[0] = math_fast_sin_or_cos_a(OF(0xF8)); target.f[1] = math_fast_sin_or_cos_b(OF(0xF8)); target.f[2] = 0;
                FastVecAdd(&offset, &offset, &target);
                coll_sweep_from_object(object, &offset, 0x04000001, 0.4f, F(0x2BC), 1.0f, 0, 1, 0);
            }
            if (object[0x42] == 14 && distance < 10.0f) OF(0x48) = 0.65f;
            else OF(0x48) = 1.0f;
        } else OF(0x48) = 1.0f;
        if (object[0x60] & 2) {
            if (F(0x20) > 1.0f) {
                if (object[0x43] != 31) anim_start_blended(object, 31, 0, 10);
                moby_set_state(object, 24, -1);
            } else {
                if (object[0x43] != 31) anim_start_blended(object, 31, 0, 10);
                moby_set_state(object, 24, -1);
            }
            if (object[0x95] != 2) {
                moby_set_state(object, 18, -1);
                if (object[0x43] != 20) anim_start_blended(object, 20, 0, 10);
            }
        }
        break;
    case 24:
        if (object[0x60] & 2) {
            if (vec_distance_xy(object + 0x10, P(0x240) + 0x10) < 2.5f) {
            return_to_follow:
                if (object[0x43] != 12) anim_start_blended(object, 12, 0, 10);
                moby_set_state(object, 21, -1);
            } else {
                if (object[0x43] != 12) anim_start_blended(object, 12, 0, 10);
                moby_set_state(object, 21, -1);
            }
        }
        break;
    }
    enemy_tick_timers_blend((char *)object);
    if (math_fabs(OF(0x18) - oldHeight) < 0.005f) OF(0x18) = oldHeight;
    return;
}
