#include "include_asm.h"

#include "common.h"
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
extern void func_PAL_002A7E68(void *, int, int, int);
extern float moby_get_anim_value(void *);
extern float FastDiffRots(float, float);
extern int flag_set_second_pending(void *);
extern int flag_set_first_pending(void *);
extern char *arena_get_center_point(void *);
extern int arena_is_point_in_polygon(void *, void *);
extern int arena_get_group_index(void *);
extern int math_random_int_below(int);
extern void fighter_pick_goal_near_target(void *, void *);
extern int func_PAL_L01_00323068(void *, void *);
extern int moby_dispatch_action_by_kind(void *, void *);
extern void func_PAL_L02_004009A0(void *, int, int);
extern void part_queue_moby_for_glow(void *, int, void (*)(char *));
extern void fighter_choose_action(void *);
extern void fighter_reset_to_idle(char *);
extern void func_PAL_L11_0045B9E8(void *);
extern void fighter_count_frame_check_contact(void *);
extern int func_PAL_L11_0045C2B0(void *);
extern void func_PAL_L11_0045BC60(void *, void *);
extern void MobySpringTurn(void *, float, float, float, float *, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void joba_damage_objects_in_radius(void *, int, float, float, float, float, float, float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern int coll_test_hit_at_bone(void *, float, float, int, int, float, int, int, int);

void func_PAL_L11_0045AAE4(ActorObject *p)
{
    ActorState *q = p->data;
    float target[4];
    float scratch[4];
    float hit[4];
    float distance, heading, delta, animationFrame;
    int flags, secondaryState;
    u16 *ids;
    ActorObject *entity;

    if (p->state == 1) return;
    func_PAL_L11_0045B9E8(p);
    if (p->state == 1) return;
    if (q->attached == 0) {
        q->target = 0;
        if (p->secondaryState == 3) moby_set_state(p, 4, 2);
    }
    animationFrame = moby_get_anim_value(p);
    if (q->target) {
        *(ActorQuadword *)target = *(ActorQuadword *)(q->target->pos);
        heading = mat_fast_helper_a(q->target->pos[0] - p->pos[0],
                                q->target->pos[1] - p->pos[1]);
    } else {
        *(ActorQuadword *)target = *(ActorQuadword *)g_hero_state.position;
        heading = mat_fast_helper_a(g_hero_state.position[0] - p->pos[0],
                                g_hero_state.position[1] - p->pos[1]);
    }
    delta = FastDiffRots(p->heading, heading);
    distance = vec_distance_xy(p->pos, target);
    /* The entry substate also selects the initial walking animation. */
    secondaryState = p->secondaryState;
    switch (secondaryState) {
    case 2:
        if (flag_set_second_pending(p)) {
            p->speed = math_random_float_range(0.5f, 1.25f);
            moby_set_controller_speed_limits(p, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
            if (p->nextAnimation != secondaryState) func_PAL_002A7E68(p, 2, 0, 8);
            p->idleStage = 0;
            fighter_pick_goal_near_target(p, arena_get_center_point(p->controller));
            p->timer = 10000;
        }
        if (p->idleStage == 1 && p->timer >= 251) {
            if (p->nextAnimation) func_PAL_002A7E68(p, 0, 0, 8);
            p->timer = math_random_int_below(83);
        }
        if (q->attached) {
            p->speed = 1.0f;
            moby_set_state(p, 5, 3);
        }
        if (p->idleStage == 0 && vec_distance_xy(p->pos, q->goal) < 0.5f)
            p->idleStage = 1;
        else func_PAL_L01_00323068(p, q->goal);
        break;
    case 3:
        break;
    case 4:
        flags = moby_dispatch_action_by_kind(p, q->contact);
        if (flags & 1) {
            func_PAL_L02_004009A0(p, 0, -1);
            part_queue_moby_for_glow(p, 0, fighter_reset_to_idle);
        } else if (flags & 2) fighter_choose_action(p);
        break;
    }
    switch (p->state) {
    case 3:
        if (flag_set_first_pending(p)) {
            p->idleStage = 0;
            if (p->nextAnimation != 0) func_PAL_002A7E68(p, 0, 0, 0);
            p->timer = 0;
        }
        if (p->idleStage == 0 && q->idleDelay < p->timer) {
            if (p->nextAnimation != 3) func_PAL_002A7E68(p, 3, 0, 8);
            p->idleStage = 1;
        } else if (p->idleStage == 1) {
            if (arena_is_point_in_polygon(p->controller, p->pos))
                moby_set_state(p, 4, 2);
            func_PAL_L01_00323068(p, arena_get_center_point(p->controller));
        }
        break;
    case 5:
        if (flag_set_first_pending(p)) {
            if (p->nextAnimation != math_random_int_below(2) + 1)
                func_PAL_002A7E68(p, math_random_int_below(2) + 1, 0, 8);
        }
        MobySpringTurn(p, heading, 0.001f, 0.01f, &q->turnRate, 0.1f);
        if (p->animationFlags & 2) fighter_choose_action(p);
        break;
    case 6:
        if (flag_set_first_pending(p)) {
            moby_set_controller_speed_limits(p, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
            if (p->nextAnimation != 2) func_PAL_002A7E68(p, 2, 0, 8);
        }
        func_PAL_L01_00323068(p, target);
        if (D_L11_001B1D60 < distance) fighter_choose_action(p);
        else if (distance < 2.7f) fighter_choose_action(p);
        break;
    case 7:
        if (flag_set_first_pending(p)) {
            moby_set_controller_speed_limits(p, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
            if (p->nextAnimation != 3) func_PAL_002A7E68(p, 3, 0, 8);
            p->timer = 0;
        }
        if (q->aimTarget == 0 && (D_L11_001B30C8[0] & 0x3F) == (((s32)p >> 8) & 0x3F)) {
            for (ids = g_group_id_lists[arena_get_group_index(p->controller)];
                 (arena_get_group_index(p->controller) & 0xFF) != 0xFF &&
                 arena_get_group_index(p->controller) <= D_L11_001B35B8[0] && ids != 0 &&
                 ((s16)ids[-1] >= 0 || ids == g_group_id_lists[arena_get_group_index(p->controller)]); ids++) {
                entity = g_moby_l11_table[0] + (*ids & 0x7FFF);
                if (entity == 0) break;
                if (entity->classId == 0xDF9) continue;
                if (FastDiffRots(p->heading, mat_fast_helper_a(entity->pos[0] - p->pos[0],
                                                        entity->pos[1] - p->pos[1])) < 0.52359885f &&
                    vec_distance_squared_xy(p->pos, entity->pos) < 20.0f) {
                    q->aimTarget = entity;
                    break;
                }
            }
        } else if (q->aimTarget == 0 || (q->aimTarget->state == 0xFE || (q->aimTarget->state == 0xFD || q->aimTarget->state < 2))) {
            q->aimTarget = 0;
        }
        if (!func_PAL_L11_0045C2B0(p)) {
            if (q->aimTarget) func_PAL_L11_0045BC60(p, q->aimTarget->pos);
            else func_PAL_L11_0045BC60(p, target);
        }
        moby_transform_joint_to_world(p, 1, scratch);
        joba_damage_objects_in_radius(p, (int)scratch, D_L11_001B1D6C, 0.0f, 100.0f, D_L11_001B1D70,
                          D_L11_001B1D78, D_L11_001B1D80, D_L11_001B1D88);
        if (distance < 2.7f && delta < 0.3490659f) moby_set_state(p, 11, -1);
        if (p->timer > ((s32)(D_L11_001B1D64) * 5 + 2) / 6) moby_set_state(p, 6, -1);
        break;
    case 9:
        if (flag_set_first_pending(p)) {
            if (p->nextAnimation != 4) func_PAL_002A7E68(p, 4, 0, 8);
            q->step = 0.010000001f;
            moby_set_controller_speed_limits(p, 0.0096f, 0.24000001f, 0.00031415932f, 0.00767945f);
        }
        if (q->aimTarget == 0 && (D_L11_001B30C8[0] & 0x3F) == (((s32)p >> 8) & 0x3F)) {
            for (ids = g_group_id_lists[arena_get_group_index(p->controller)];
                 (arena_get_group_index(p->controller) & 0xFF) != 0xFF &&
                 arena_get_group_index(p->controller) <= D_L11_001B35B8[0] && ids != 0 &&
                 ((s16)ids[-1] >= 0 || ids == g_group_id_lists[arena_get_group_index(p->controller)]); ids++) {
                entity = g_moby_l11_table[0] + (*ids & 0x7FFF);
                if (entity == 0) break;
                if (entity->classId == 0xDF9) continue;
                if (FastDiffRots(p->heading, mat_fast_helper_a(entity->pos[0] - p->pos[0],
                                                        entity->pos[1] - p->pos[1])) < 0.52359885f &&
                    vec_distance_squared_xy(p->pos, entity->pos) < 20.0f) {
                    q->aimTarget = entity;
                    break;
                }
            }
        } else if (q->aimTarget == 0 || (q->aimTarget->state == 0xFE || (q->aimTarget->state == 0xFD || q->aimTarget->state < 2))) {
            q->aimTarget = 0;
        }
        if (q->aimTarget) {
            func_PAL_L01_00323068(p, q->aimTarget->pos);
            MobySpringTurn(p,
                          mat_fast_helper_a(q->aimTarget->pos[0] - p->pos[0],
                                        q->aimTarget->pos[1] - p->pos[1]),
                          0.001f, 0.01f, &q->turnRate, 0.1f);
        } else {
            func_PAL_L01_00323068(p, target);
            MobySpringTurn(p, heading, 0.001f, 0.01f, &q->turnRate, 0.1f);
        }
        moby_transform_joint_to_world(p, 1, scratch);
        joba_damage_objects_in_radius(p, (int)scratch, D_L11_001B1D6C, (float)q->contactDamage, 100.0f, D_L11_001B1D74,
                          D_L11_001B1D7C, D_L11_001B1D80, D_L11_001B1D88);
        if (g_hero_state.attackTarget == p) moby_set_state(p, 10, -1);
        if (0.38397247f < delta) moby_set_state(p, 8, -1);
        break;
    case 10:
        if (flag_set_first_pending(p)) {
            if (p->nextAnimation != 5) func_PAL_002A7E68(p, 5, 0, 2);
            moby_set_controller_speed_limits(p, 0.006f, 0.040000003f, 0.00062831864f, 0.015707966f);
        }
        scratch[0] = 4.0f * math_fast_sin_or_cos_a(p->heading);
        scratch[1] = 4.0f * math_fast_sin_or_cos_b(p->heading);
        scratch[2] = 0.0f;
        FastVecAdd(scratch, p->pos, scratch);
        func_PAL_L01_00323068(p, scratch);
        moby_transform_joint_to_world(p, 1, hit);
        joba_damage_objects_in_radius(p, (int)hit, D_L11_001B1D6C, (float)q->contactDamage, 100.0f, D_L11_001B1D74,
                          D_L11_001B1D7C, D_L11_001B1D84, D_L11_001B1D8C);
        if (p->animationFlags & 2) moby_set_state(p, 8, -1);
        break;
    case 8:
        if (flag_set_first_pending(p)) {
            if (p->nextAnimation != 4) func_PAL_002A7E68(p, 4, 0, 8);
        }
        scratch[0] = 4.0f * math_fast_sin_or_cos_a(p->heading);
        scratch[1] = 4.0f * math_fast_sin_or_cos_b(p->heading);
        scratch[2] = 0.0f;
        FastVecAdd(scratch, p->pos, scratch);
        func_PAL_L01_00323068(p, scratch);
        MobySpringTurn(p, heading, 0.001f, 0.01f, &q->turnRate, 0.1f);
        moby_transform_joint_to_world(p, 1, hit);
        joba_damage_objects_in_radius(p, (int)hit, D_L11_001B1D6C, 0.0f, 100.0f, D_L11_001B1D70,
                          D_L11_001B1D78, D_L11_001B1D80, D_L11_001B1D88);
        if (p->animationFlags & 2) fighter_choose_action(p);
        break;
    case 11:
        if (flag_set_first_pending(p)) {
            if (p->nextAnimation != 6) func_PAL_002A7E68(p, 6, 0, 4);
        }
        if (p->animation == 6 && animationFrame >= 10.0f && animationFrame <= 15.0f)
            coll_test_hit_at_bone(p, 1.0f, (float)q->meleeDamage, 1, 1, 1.0f, 0, 1, 0);
        if (p->animationFlags & 2) {
            if (distance < 2.7f && delta < 0.3490659f) moby_set_state(p, 11, -1);
            else fighter_choose_action(p);
        }
        break;
    case 12:
        if (p->animationFlags & 2) fighter_choose_action(p);
        break;
    }
    fighter_count_frame_check_contact(p);
}
