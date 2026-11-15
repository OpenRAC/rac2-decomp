#include "common.h"

/* Separate unit for GP-relative tuning and the state-machine jump table.
 * Unsplit GCSE edges share the goal pointer; disabling CSE jump following retains
 * the nullable target checks on frames when the group search is skipped.
 */

typedef int ActorQuadword __attribute__((mode(TI)));

typedef struct ActorObject ActorObject;
typedef struct {
    char pad00[0x34];
    u8 meleeDamage;
    u8 contactDamage;
    char pad36[0x50 - 0x36];
    char contact[0x10];
    char pad60[0x124 - 0x60];
    float step;
    char pad128[0x230 - 0x128];
    float goal[4];
    ActorObject *target;
    s32 group;
    float turnRate;
    s32 field24C;
    ActorObject *aimTarget;
    s16 field254;
    s16 attached;
    s16 idleDelay;
} ActorState;
struct ActorObject {
    char pad00[0x10];
    float pos[4];
    u8 state;
    char pad21[0x42 - 0x21];
    u8 animation;
    u8 nextAnimation;
    char pad44[4];
    float speed;
    char pad4C[0x60 - 0x4C];
    u8 animationFlags;
    char pad61[7];
    ActorState *data;
    char pad6C[0x95 - 0x6C];
    u8 secondaryState;
    u16 timer;
    char pad98[0xAA - 0x98];
    s16 classId;
    char padAC[0xB8 - 0xAC];
    char *controller;
    u8 idleStage;
    char padBD[0xF8 - 0xBD];
    float heading;
    char padFC[4];
};

typedef struct {
    char pad00[0x80];
    float position[4];
    char pad90[0x249C - 0x90];
    ActorObject *attackTarget;
} ActorPlayerBlock;
extern ActorPlayerBlock g_hero_state;
extern s32 D_L11_001B30C8[] __attribute__((sda));
extern ActorObject *g_moby_l11_table[] __attribute__((sda));
extern s32 D_L11_001B35B8[] __attribute__((sda));
extern u16 *g_group_id_lists[];
extern float D_L11_001B1D60 SDATA(D_L11_001B1D60);
extern s32 D_L11_001B1D64 SDATA(D_L11_001B1D64);
extern float D_L11_001B1D6C SDATA(D_L11_001B1D6C);
extern float D_L11_001B1D70 SDATA(D_L11_001B1D70);
extern float D_L11_001B1D74 SDATA(D_L11_001B1D74);
extern float D_L11_001B1D78 SDATA(D_L11_001B1D78);
extern float D_L11_001B1D7C SDATA(D_L11_001B1D7C);
extern float D_L11_001B1D80 SDATA(D_L11_001B1D80);
extern float D_L11_001B1D84 SDATA(D_L11_001B1D84);
extern float D_L11_001B1D88 SDATA(D_L11_001B1D88);
extern float D_L11_001B1D8C SDATA(D_L11_001B1D8C);
extern void moby_set_state(void *, int, int);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(void *, void *);
extern float vec_distance_squared_xy(void *, void *);
extern float math_random_float_range(float, float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void anim_start_blended(void *, int, int, int);
extern float moby_get_anim_value(void *);
extern float FastDiffRots(float, float);
extern int flag_set_second_pending(void *);
extern int flag_set_first_pending(void *);
extern char *arena_get_center_point(void *);
extern int arena_is_point_in_polygon(void *, void *);
extern int arena_get_group_index(void *);
extern int math_random_int_below(int);
extern void fighter_pick_goal_near_target(void *, void *);
extern int moby_l01_turn_toward_target(void *, void *);
extern int moby_dispatch_action_by_kind(void *, void *);
extern void moby_set_anim_type_three(void *, int, int);
extern void part_queue_moby_for_glow(void *, int, void (*)(char *));
extern void fighter_choose_action(void *);
extern void fighter_reset_to_idle(char *);
extern void fighter_update_contacts(void *);
extern void fighter_count_frame_check_contact(void *);
extern int joba_turn_toward_group_entity(void *);
extern void joba_fighter_walk_dust(void *, void *);
extern void MobySpringTurn(void *, float, float, float, float *, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void joba_damage_objects_in_radius(void *, int, float, float, float, float, float, float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern int coll_test_hit_at_bone(void *, float, float, int, int, float, int, int, int);

/* Per-frame update of the Joba fighter (moby class 3577): it walks toward its goal or the player, charges, and swings at close range. */
void UpdateJobaCombatActor(ActorObject *actor)
{
    ActorState *data = actor->data;
    float target[4];
    float scratch[4];
    float hit[4];
    float distance, heading, delta, animationFrame;
    int flags, secondaryState;
    u16 *ids;
    ActorObject *entity;

    if (actor->state == 1) return;
    fighter_update_contacts(actor);
    if (actor->state == 1) return;
    if (data->attached == 0) {
        data->target = 0;
        if (actor->secondaryState == 3) moby_set_state(actor, 4, 2);
    }
    animationFrame = moby_get_anim_value(actor);
    if (data->target) {
        *(ActorQuadword *)target = *(ActorQuadword *)(data->target->pos);
        heading = mat_fast_helper_a(data->target->pos[0] - actor->pos[0],
                                data->target->pos[1] - actor->pos[1]);
    } else {
        *(ActorQuadword *)target = *(ActorQuadword *)g_hero_state.position;
        heading = mat_fast_helper_a(g_hero_state.position[0] - actor->pos[0],
                                g_hero_state.position[1] - actor->pos[1]);
    }
    delta = FastDiffRots(actor->heading, heading);
    distance = vec_distance_xy(actor->pos, target);
    /* The entry substate also selects the initial walking animation. */
    secondaryState = actor->secondaryState;
    switch (secondaryState) {
    case 2:
        if (flag_set_second_pending(actor)) {
            actor->speed = math_random_float_range(0.5f, 1.25f);
            moby_set_controller_speed_limits(actor, 0.00222222228f, 0.0666666701f, 0.00116355298f, 0.104719773f);
            if (actor->nextAnimation != secondaryState) anim_start_blended(actor, 2, 0, 10);
            actor->idleStage = 0;
            fighter_pick_goal_near_target(actor, arena_get_center_point(actor->controller));
            actor->timer = 10000;
        }
        if (actor->idleStage == 1 && actor->timer >= 301) {
            if (actor->nextAnimation) anim_start_blended(actor, 0, 0, 10);
            actor->timer = math_random_int_below(100);
        }
        if (data->attached) {
            actor->speed = 1.0f;
            moby_set_state(actor, 5, 3);
        }
        if (actor->idleStage == 0 && vec_distance_xy(actor->pos, data->goal) < 0.5f)
            actor->idleStage = 1;
        else moby_l01_turn_toward_target(actor, data->goal);
        break;
    case 3:
        break;
    case 4:
        flags = moby_dispatch_action_by_kind(actor, data->contact);
        if (flags & 1) {
            moby_set_anim_type_three(actor, 0, -1);
            part_queue_moby_for_glow(actor, 0, fighter_reset_to_idle);
        } else if (flags & 2) fighter_choose_action(actor);
        break;
    }
    switch (actor->state) {
    case 3:
        if (flag_set_first_pending(actor)) {
            actor->idleStage = 0;
            if (actor->nextAnimation != 0) anim_start_blended(actor, 0, 0, 0);
            actor->timer = 0;
        }
        if (actor->idleStage == 0 && data->idleDelay < actor->timer) {
            if (actor->nextAnimation != 3) anim_start_blended(actor, 3, 0, 10);
            actor->idleStage = 1;
        } else if (actor->idleStage == 1) {
            if (arena_is_point_in_polygon(actor->controller, actor->pos))
                moby_set_state(actor, 4, 2);
            moby_l01_turn_toward_target(actor, arena_get_center_point(actor->controller));
        }
        break;
    case 5:
        if (flag_set_first_pending(actor)) {
            if (actor->nextAnimation != math_random_int_below(2) + 1)
                anim_start_blended(actor, math_random_int_below(2) + 1, 0, 10);
        }
        MobySpringTurn(actor, heading, 0.001f, 0.01f, &data->turnRate, 0.1f);
        if (actor->animationFlags & 2) fighter_choose_action(actor);
        break;
    case 6:
        if (flag_set_first_pending(actor)) {
            moby_set_controller_speed_limits(actor, 0.00222222228f, 0.0666666701f, 0.00116355298f, 0.104719773f);
            if (actor->nextAnimation != 2) anim_start_blended(actor, 2, 0, 10);
        }
        moby_l01_turn_toward_target(actor, target);
        if (D_L11_001B1D60 < distance) fighter_choose_action(actor);
        else if (distance < 2.7f) fighter_choose_action(actor);
        break;
    case 7:
        if (flag_set_first_pending(actor)) {
            moby_set_controller_speed_limits(actor, 0.00333333341f, 0.100000009f, 0.00116355298f, 0.104719773f);
            if (actor->nextAnimation != 3) anim_start_blended(actor, 3, 0, 10);
            actor->timer = 0;
        }
        if (data->aimTarget == 0 && (D_L11_001B30C8[0] & 0x3F) == (((s32)actor >> 8) & 0x3F)) {
            for (ids = g_group_id_lists[arena_get_group_index(actor->controller)];
                 (arena_get_group_index(actor->controller) & 0xFF) != 0xFF &&
                 arena_get_group_index(actor->controller) <= D_L11_001B35B8[0] && ids != 0 &&
                 ((s16)ids[-1] >= 0 || ids == g_group_id_lists[arena_get_group_index(actor->controller)]); ids++) {
                entity = g_moby_l11_table[0] + (*ids & 0x7FFF);
                if (entity == 0) break;
                if (entity->classId == 0xDF9) continue;
                if (FastDiffRots(actor->heading, mat_fast_helper_a(entity->pos[0] - actor->pos[0],
                                                        entity->pos[1] - actor->pos[1])) < 0.52359885f &&
                    vec_distance_squared_xy(actor->pos, entity->pos) < 20.0f) {
                    data->aimTarget = entity;
                    break;
                }
            }
        } else if (data->aimTarget == 0 || (data->aimTarget->state == 0xFE || (data->aimTarget->state == 0xFD || data->aimTarget->state < 2))) {
            data->aimTarget = 0;
        }
        if (!joba_turn_toward_group_entity(actor)) {
            if (data->aimTarget) joba_fighter_walk_dust(actor, data->aimTarget->pos);
            else joba_fighter_walk_dust(actor, target);
        }
        moby_transform_joint_to_world(actor, 1, scratch);
        joba_damage_objects_in_radius(actor, (int)scratch, D_L11_001B1D6C, 0.0f, 100.0f, D_L11_001B1D70,
                          D_L11_001B1D78, D_L11_001B1D80, D_L11_001B1D88);
        if (distance < 2.7f && delta < 0.3490659f) moby_set_state(actor, 11, -1);
        if (D_L11_001B1D64 < actor->timer) moby_set_state(actor, 6, -1);
        break;
    case 9:
        if (flag_set_first_pending(actor)) {
            if (actor->nextAnimation != 4) anim_start_blended(actor, 4, 0, 10);
            data->step = 0.0069444445f;
            moby_set_controller_speed_limits(actor, 0.00666666683f, 0.200000018f, 0.000218166184f, 0.00639954163f);
        }
        if (data->aimTarget == 0 && (D_L11_001B30C8[0] & 0x3F) == (((s32)actor >> 8) & 0x3F)) {
            for (ids = g_group_id_lists[arena_get_group_index(actor->controller)];
                 (arena_get_group_index(actor->controller) & 0xFF) != 0xFF &&
                 arena_get_group_index(actor->controller) <= D_L11_001B35B8[0] && ids != 0 &&
                 ((s16)ids[-1] >= 0 || ids == g_group_id_lists[arena_get_group_index(actor->controller)]); ids++) {
                entity = g_moby_l11_table[0] + (*ids & 0x7FFF);
                if (entity == 0) break;
                if (entity->classId == 0xDF9) continue;
                if (FastDiffRots(actor->heading, mat_fast_helper_a(entity->pos[0] - actor->pos[0],
                                                        entity->pos[1] - actor->pos[1])) < 0.52359885f &&
                    vec_distance_squared_xy(actor->pos, entity->pos) < 20.0f) {
                    data->aimTarget = entity;
                    break;
                }
            }
        } else if (data->aimTarget == 0 || (data->aimTarget->state == 0xFE || (data->aimTarget->state == 0xFD || data->aimTarget->state < 2))) {
            data->aimTarget = 0;
        }
        if (data->aimTarget) {
            moby_l01_turn_toward_target(actor, data->aimTarget->pos);
            MobySpringTurn(actor,
                          mat_fast_helper_a(data->aimTarget->pos[0] - actor->pos[0],
                                        data->aimTarget->pos[1] - actor->pos[1]),
                          0.001f, 0.01f, &data->turnRate, 0.1f);
        } else {
            moby_l01_turn_toward_target(actor, target);
            MobySpringTurn(actor, heading, 0.001f, 0.01f, &data->turnRate, 0.1f);
        }
        moby_transform_joint_to_world(actor, 1, scratch);
        joba_damage_objects_in_radius(actor, (int)scratch, D_L11_001B1D6C, (float)data->contactDamage, 100.0f, D_L11_001B1D74,
                          D_L11_001B1D7C, D_L11_001B1D80, D_L11_001B1D88);
        if (g_hero_state.attackTarget == actor) moby_set_state(actor, 10, -1);
        if (0.38397247f < delta) moby_set_state(actor, 8, -1);
        break;
    case 10:
        if (flag_set_first_pending(actor)) {
            if (actor->nextAnimation != 5) anim_start_blended(actor, 5, 0, 3);
            moby_set_controller_speed_limits(actor, 0.00416666688f, 0.0333333351f, 0.000436332368f, 0.0130899716f);
        }
        scratch[0] = 4.0f * math_fast_sin_or_cos_a(actor->heading);
        scratch[1] = 4.0f * math_fast_sin_or_cos_b(actor->heading);
        scratch[2] = 0.0f;
        FastVecAdd(scratch, actor->pos, scratch);
        moby_l01_turn_toward_target(actor, scratch);
        moby_transform_joint_to_world(actor, 1, hit);
        joba_damage_objects_in_radius(actor, (int)hit, D_L11_001B1D6C, (float)data->contactDamage, 100.0f, D_L11_001B1D74,
                          D_L11_001B1D7C, D_L11_001B1D84, D_L11_001B1D8C);
        if (actor->animationFlags & 2) moby_set_state(actor, 8, -1);
        break;
    case 8:
        if (flag_set_first_pending(actor)) {
            if (actor->nextAnimation != 4) anim_start_blended(actor, 4, 0, 10);
        }
        scratch[0] = 4.0f * math_fast_sin_or_cos_a(actor->heading);
        scratch[1] = 4.0f * math_fast_sin_or_cos_b(actor->heading);
        scratch[2] = 0.0f;
        FastVecAdd(scratch, actor->pos, scratch);
        moby_l01_turn_toward_target(actor, scratch);
        MobySpringTurn(actor, heading, 0.001f, 0.01f, &data->turnRate, 0.1f);
        moby_transform_joint_to_world(actor, 1, hit);
        joba_damage_objects_in_radius(actor, (int)hit, D_L11_001B1D6C, 0.0f, 100.0f, D_L11_001B1D70,
                          D_L11_001B1D78, D_L11_001B1D80, D_L11_001B1D88);
        if (actor->animationFlags & 2) fighter_choose_action(actor);
        break;
    case 11:
        if (flag_set_first_pending(actor)) {
            if (actor->nextAnimation != 6) anim_start_blended(actor, 6, 0, 5);
        }
        if (actor->animation == 6 && animationFrame >= 10.0f && animationFrame <= 15.0f)
            coll_test_hit_at_bone(actor, 1.0f, (float)data->meleeDamage, 1, 1, 1.0f, 0, 1, 0);
        if (actor->animationFlags & 2) {
            if (distance < 2.7f && delta < 0.3490659f) moby_set_state(actor, 11, -1);
            else fighter_choose_action(actor);
        }
        break;
    case 12:
        if (actor->animationFlags & 2) fighter_choose_action(actor);
        break;
    }
    fighter_count_frame_check_contact(actor);
}
