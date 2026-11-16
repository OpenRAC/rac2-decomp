#include "include_asm.h"

#include "common.h"
typedef int ActorQuadword __attribute__((mode(TI)));
typedef struct ActorObject ActorObject;
typedef struct {
    char pad00[0x34];
    u8 melee_damage;
    u8 contact_damage;
    char pad36[0x50 - 0x36];
    char contact[0x10];
    char pad60[0x124 - 0x60];
    float step;
    char pad128[0x230 - 0x128];
    float goal[4];
    ActorObject *target;
    s32 group;
    float turn_rate;
    s32 unk_24C;
    ActorObject *aim_target;
    s16 unk_254;
    s16 attached;
    s16 idle_delay;
} ActorState;
struct ActorObject {
    char pad00[0x10];
    float pos[4];
    u8 state;
    char pad21[0x42 - 0x21];
    u8 animation;
    u8 next_animation;
    char pad44[4];
    float speed;
    char pad4C[0x60 - 0x4C];
    u8 animation_flags;
    char pad61[7];
    ActorState *data;
    char pad6C[0x95 - 0x6C];
    u8 secondary_state;
    u16 timer;
    char pad98[0xAA - 0x98];
    s16 class_id;
    char padAC[0xB8 - 0xAC];
    char *controller;
    u8 idle_stage;
    char padBD[0xF8 - 0xBD];
    float heading;
    char padFC[4];
};
typedef struct {
    char pad00[0x80];
    float position[4];
    char pad90[0x249C - 0x90];
    ActorObject *attack_target;
} ActorPlayerBlock;
extern ActorPlayerBlock g_hero_state;
extern s32 g_arena_progress_level[] __attribute__((sda));
extern ActorObject *g_moby_l11_table[] __attribute__((sda));
extern s32 g_tribe_group_limit[] __attribute__((sda));
extern u16 *g_group_id_lists[];
extern float g_fighter_action_distance SDATA(D_L11_001B1D60);
extern s32 g_fighter_state_timeout SDATA(D_L11_001B1D64);
extern float g_fighter_damage_radius SDATA(D_L11_001B1D6C);
extern float g_fighter_damage_param_a SDATA(D_L11_001B1D70);
extern float g_fighter_damage_param_b SDATA(D_L11_001B1D74);
extern float g_fighter_hit_param_a SDATA(D_L11_001B1D78);
extern float g_fighter_hit_param_b SDATA(D_L11_001B1D7C);
extern float g_fighter_hit_param_c SDATA(D_L11_001B1D80);
extern float g_fighter_hit_param_d SDATA(D_L11_001B1D84);
extern float g_fighter_hit_param_e SDATA(D_L11_001B1D88);
extern float g_fighter_hit_param_f SDATA(D_L11_001B1D8C);
extern void moby_set_state(void *, int, int);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(void *, void *);
extern float vec_distance_squared_xy(void *, void *);
extern float math_random_float_range(float, float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void anim_start_blended_pal(void *, int, int, int);
extern float moby_get_anim_value(void *);
extern float FastDiffRots(float, float);
extern int flag_set_second_pending(void *);
extern int flag_set_first_pending(void *);
extern char *arena_get_center_point(void *);
extern int arena_is_point_in_polygon(void *, void *);
extern int arena_get_group_index(void *);
extern int math_random_int_below(int);
extern void fighter_pick_goal_near_target(void *, void *);
extern int moby_l01_turn_toward_target_pal(void *, void *);
extern int moby_dispatch_action_by_kind(void *, void *);
extern void moby_set_anim_type_three_pal(void *, int, int);
extern void part_queue_moby_for_glow(void *, int, void (*)(char *));
extern void fighter_choose_action(void *);
extern void fighter_reset_to_idle(char *);
extern void fighter_update_contacts_pal(void *);
extern void fighter_count_frame_check_contact(void *);
extern int joba_turn_toward_group_entity_pal(void *);
extern void joba_fighter_walk_dust_pal(void *, void *);
extern float MobySpringTurn(void *, float, float, float, float *, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void joba_damage_objects_in_radius(void *, int, float, float, float, float, float, float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern int coll_test_hit_at_bone(void *, float, float, int, int, float, int, int, int);

/* Per-frame update of a Joba arena fighter: it walks to a spot, picks fights, turns toward and chases the player, and swings at them (PAL version). */
/* Per-frame update of a Joba arena fighter: it walks to a spot, picks fights, turns toward and chases the player, and swings at them (PAL version). */
void joba_combat_actor_update_pal(ActorObject *fighter)
{
    ActorState *vars = fighter->data;
    float target[4];
    float scratch[4];
    float hit_pos[4];
    float distance, heading, delta, anim_frame;
    int action_flags, secondary_state;
    u16 *ids;
    ActorObject *entity;

    if (fighter->state == 1) return;
    fighter_update_contacts_pal(fighter);
    if (fighter->state == 1) return;
    if (vars->attached == 0) {
        vars->target = 0;
        if (fighter->secondary_state == 3) moby_set_state(fighter, 4, 2);
    }
    anim_frame = moby_get_anim_value(fighter);
    if (vars->target) {
        *(ActorQuadword *)target = *(ActorQuadword *)(vars->target->pos);
        heading = mat_fast_helper_a(vars->target->pos[0] - fighter->pos[0],
                                vars->target->pos[1] - fighter->pos[1]);
    } else {
        *(ActorQuadword *)target = *(ActorQuadword *)g_hero_state.position;
        heading = mat_fast_helper_a(g_hero_state.position[0] - fighter->pos[0],
                                g_hero_state.position[1] - fighter->pos[1]);
    }
    delta = FastDiffRots(fighter->heading, heading);
    distance = vec_distance_xy(fighter->pos, target);
    /* The entry substate also selects the initial walking animation. */
    secondary_state = fighter->secondary_state;
    switch (secondary_state) {
    case 2:
        if (flag_set_second_pending(fighter)) {
            fighter->speed = math_random_float_range(0.5f, 1.25f);
            moby_set_controller_speed_limits(fighter, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
            if (fighter->next_animation != secondary_state) anim_start_blended_pal(fighter, 2, 0, 8);
            fighter->idle_stage = 0;
            fighter_pick_goal_near_target(fighter, arena_get_center_point(fighter->controller));
            fighter->timer = 10000;
        }
        if (fighter->idle_stage == 1 && fighter->timer >= 251) {
            if (fighter->next_animation) anim_start_blended_pal(fighter, 0, 0, 8);
            fighter->timer = math_random_int_below(83);
        }
        if (vars->attached) {
            fighter->speed = 1.0f;
            moby_set_state(fighter, 5, 3);
        }
        if (fighter->idle_stage == 0 && vec_distance_xy(fighter->pos, vars->goal) < 0.5f)
            fighter->idle_stage = 1;
        else moby_l01_turn_toward_target_pal(fighter, vars->goal);
        break;
    case 3:
        break;
    case 4:
        action_flags = moby_dispatch_action_by_kind(fighter, vars->contact);
        if (action_flags & 1) {
            moby_set_anim_type_three_pal(fighter, 0, -1);
            part_queue_moby_for_glow(fighter, 0, fighter_reset_to_idle);
        } else if (action_flags & 2) fighter_choose_action(fighter);
        break;
    }
    switch (fighter->state) {
    case 3:
        if (flag_set_first_pending(fighter)) {
            fighter->idle_stage = 0;
            if (fighter->next_animation != 0) anim_start_blended_pal(fighter, 0, 0, 0);
            fighter->timer = 0;
        }
        if (fighter->idle_stage == 0 && vars->idle_delay < fighter->timer) {
            if (fighter->next_animation != 3) anim_start_blended_pal(fighter, 3, 0, 8);
            fighter->idle_stage = 1;
        } else if (fighter->idle_stage == 1) {
            if (arena_is_point_in_polygon(fighter->controller, fighter->pos))
                moby_set_state(fighter, 4, 2);
            moby_l01_turn_toward_target_pal(fighter, arena_get_center_point(fighter->controller));
        }
        break;
    case 5:
        if (flag_set_first_pending(fighter)) {
            if (fighter->next_animation != math_random_int_below(2) + 1)
                anim_start_blended_pal(fighter, math_random_int_below(2) + 1, 0, 8);
        }
        MobySpringTurn(fighter, heading, 0.001f, 0.01f, &vars->turn_rate, 0.1f);
        if (fighter->animation_flags & 2) fighter_choose_action(fighter);
        break;
    case 6:
        if (flag_set_first_pending(fighter)) {
            moby_set_controller_speed_limits(fighter, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
            if (fighter->next_animation != 2) anim_start_blended_pal(fighter, 2, 0, 8);
        }
        moby_l01_turn_toward_target_pal(fighter, target);
        if (g_fighter_action_distance < distance) fighter_choose_action(fighter);
        else if (distance < 2.7f) fighter_choose_action(fighter);
        break;
    case 7:
        if (flag_set_first_pending(fighter)) {
            moby_set_controller_speed_limits(fighter, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
            if (fighter->next_animation != 3) anim_start_blended_pal(fighter, 3, 0, 8);
            fighter->timer = 0;
        }
        if (vars->aim_target == 0 && (g_arena_progress_level[0] & 0x3F) == (((s32)fighter >> 8) & 0x3F)) {
            for (ids = g_group_id_lists[arena_get_group_index(fighter->controller)];
                 (arena_get_group_index(fighter->controller) & 0xFF) != 0xFF &&
                 arena_get_group_index(fighter->controller) <= g_tribe_group_limit[0] && ids != 0 &&
                 ((s16)ids[-1] >= 0 || ids == g_group_id_lists[arena_get_group_index(fighter->controller)]); ids++) {
                entity = g_moby_l11_table[0] + (*ids & 0x7FFF);
                if (entity == 0) break;
                if (entity->class_id == 0xDF9) continue;
                if (FastDiffRots(fighter->heading, mat_fast_helper_a(entity->pos[0] - fighter->pos[0],
                                                        entity->pos[1] - fighter->pos[1])) < 0.52359885f &&
                    vec_distance_squared_xy(fighter->pos, entity->pos) < 20.0f) {
                    vars->aim_target = entity;
                    break;
                }
            }
        } else if (vars->aim_target == 0 || (vars->aim_target->state == 0xFE || (vars->aim_target->state == 0xFD || vars->aim_target->state < 2))) {
            vars->aim_target = 0;
        }
        if (!joba_turn_toward_group_entity_pal(fighter)) {
            if (vars->aim_target) joba_fighter_walk_dust_pal(fighter, vars->aim_target->pos);
            else joba_fighter_walk_dust_pal(fighter, target);
        }
        moby_transform_joint_to_world(fighter, 1, scratch);
        joba_damage_objects_in_radius(fighter, (int)scratch, g_fighter_damage_radius, 0.0f, 100.0f, g_fighter_damage_param_a,
                          g_fighter_hit_param_a, g_fighter_hit_param_c, g_fighter_hit_param_e);
        if (distance < 2.7f && delta < 0.3490659f) moby_set_state(fighter, 11, -1);
        if (fighter->timer > ((s32)(g_fighter_state_timeout) * 5 + 2) / 6) moby_set_state(fighter, 6, -1);
        break;
    case 9:
        if (flag_set_first_pending(fighter)) {
            if (fighter->next_animation != 4) anim_start_blended_pal(fighter, 4, 0, 8);
            vars->step = 0.010000001f;
            moby_set_controller_speed_limits(fighter, 0.0096f, 0.24000001f, 0.00031415932f, 0.00767945f);
        }
        if (vars->aim_target == 0 && (g_arena_progress_level[0] & 0x3F) == (((s32)fighter >> 8) & 0x3F)) {
            for (ids = g_group_id_lists[arena_get_group_index(fighter->controller)];
                 (arena_get_group_index(fighter->controller) & 0xFF) != 0xFF &&
                 arena_get_group_index(fighter->controller) <= g_tribe_group_limit[0] && ids != 0 &&
                 ((s16)ids[-1] >= 0 || ids == g_group_id_lists[arena_get_group_index(fighter->controller)]); ids++) {
                entity = g_moby_l11_table[0] + (*ids & 0x7FFF);
                if (entity == 0) break;
                if (entity->class_id == 0xDF9) continue;
                if (FastDiffRots(fighter->heading, mat_fast_helper_a(entity->pos[0] - fighter->pos[0],
                                                        entity->pos[1] - fighter->pos[1])) < 0.52359885f &&
                    vec_distance_squared_xy(fighter->pos, entity->pos) < 20.0f) {
                    vars->aim_target = entity;
                    break;
                }
            }
        } else if (vars->aim_target == 0 || (vars->aim_target->state == 0xFE || (vars->aim_target->state == 0xFD || vars->aim_target->state < 2))) {
            vars->aim_target = 0;
        }
        if (vars->aim_target) {
            moby_l01_turn_toward_target_pal(fighter, vars->aim_target->pos);
            MobySpringTurn(fighter,
                          mat_fast_helper_a(vars->aim_target->pos[0] - fighter->pos[0],
                                        vars->aim_target->pos[1] - fighter->pos[1]),
                          0.001f, 0.01f, &vars->turn_rate, 0.1f);
        } else {
            moby_l01_turn_toward_target_pal(fighter, target);
            MobySpringTurn(fighter, heading, 0.001f, 0.01f, &vars->turn_rate, 0.1f);
        }
        moby_transform_joint_to_world(fighter, 1, scratch);
        joba_damage_objects_in_radius(fighter, (int)scratch, g_fighter_damage_radius, (float)vars->contact_damage, 100.0f, g_fighter_damage_param_b,
                          g_fighter_hit_param_b, g_fighter_hit_param_c, g_fighter_hit_param_e);
        if (g_hero_state.attack_target == fighter) moby_set_state(fighter, 10, -1);
        if (0.38397247f < delta) moby_set_state(fighter, 8, -1);
        break;
    case 10:
        if (flag_set_first_pending(fighter)) {
            if (fighter->next_animation != 5) anim_start_blended_pal(fighter, 5, 0, 2);
            moby_set_controller_speed_limits(fighter, 0.006f, 0.040000003f, 0.00062831864f, 0.015707966f);
        }
        scratch[0] = 4.0f * math_fast_sin_or_cos_a(fighter->heading);
        scratch[1] = 4.0f * math_fast_sin_or_cos_b(fighter->heading);
        scratch[2] = 0.0f;
        FastVecAdd(scratch, fighter->pos, scratch);
        moby_l01_turn_toward_target_pal(fighter, scratch);
        moby_transform_joint_to_world(fighter, 1, hit_pos);
        joba_damage_objects_in_radius(fighter, (int)hit_pos, g_fighter_damage_radius, (float)vars->contact_damage, 100.0f, g_fighter_damage_param_b,
                          g_fighter_hit_param_b, g_fighter_hit_param_d, g_fighter_hit_param_f);
        if (fighter->animation_flags & 2) moby_set_state(fighter, 8, -1);
        break;
    case 8:
        if (flag_set_first_pending(fighter)) {
            if (fighter->next_animation != 4) anim_start_blended_pal(fighter, 4, 0, 8);
        }
        scratch[0] = 4.0f * math_fast_sin_or_cos_a(fighter->heading);
        scratch[1] = 4.0f * math_fast_sin_or_cos_b(fighter->heading);
        scratch[2] = 0.0f;
        FastVecAdd(scratch, fighter->pos, scratch);
        moby_l01_turn_toward_target_pal(fighter, scratch);
        MobySpringTurn(fighter, heading, 0.001f, 0.01f, &vars->turn_rate, 0.1f);
        moby_transform_joint_to_world(fighter, 1, hit_pos);
        joba_damage_objects_in_radius(fighter, (int)hit_pos, g_fighter_damage_radius, 0.0f, 100.0f, g_fighter_damage_param_a,
                          g_fighter_hit_param_a, g_fighter_hit_param_c, g_fighter_hit_param_e);
        if (fighter->animation_flags & 2) fighter_choose_action(fighter);
        break;
    case 11:
        if (flag_set_first_pending(fighter)) {
            if (fighter->next_animation != 6) anim_start_blended_pal(fighter, 6, 0, 4);
        }
        if (fighter->animation == 6 && anim_frame >= 10.0f && anim_frame <= 15.0f)
            coll_test_hit_at_bone(fighter, 1.0f, (float)vars->melee_damage, 1, 1, 1.0f, 0, 1, 0);
        if (fighter->animation_flags & 2) {
            if (distance < 2.7f && delta < 0.3490659f) moby_set_state(fighter, 11, -1);
            else fighter_choose_action(fighter);
        }
        break;
    case 12:
        if (fighter->animation_flags & 2) fighter_choose_action(fighter);
        break;
    }
    fighter_count_frame_check_contact(fighter);
}
