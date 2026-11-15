#include "names.h"
/* func_L02_003F0798: the combat actor update (animation, steering and attack states).
   Its own unit for -frac2-hazard-labels: two branches target the mtc1 hazard nop. */
#include "common.h"
extern void moby_set_state(u8 *, int, int);
extern int math_random_int_below(int);
extern void anim_start_blended(char *, int, int, int);
extern float mat_fast_helper_a(float, float);
extern s32 flag_set_first_pending(u8 *);
typedef int ActorVectorQuad __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; ActorVectorQuad q[0x260]; } Hero;
extern char g_hero_state[];
extern char *g_active_attacker_robot;
extern void swaying_actor_update(char *);
extern void actor_update_hit_timer(char *);
extern void actor_record_position_history(char *);
extern void actor_tear_down(char *);
extern void actor_pick_approach_point(char *, char *);
extern void actor_save_state_and_switch(char *);
extern int moby_turn_toward_nearby_enemy(char *);
extern char *arena_get_camera_point(char *);
extern s32 arena_get_state_word(char *);
extern void moby_set_anim_type_three(char *, int, int);
extern int coll_point_inside_record_volume(void *, int);
extern int cam_hook_return_minus_one(char *);
extern int moby_l01_turn_toward_target(char *, char *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void widget_submit_effects(char *);
extern float vec_distance_xy(void *, void *);
extern float FastDiffRots(float, float);
extern int flag_set_second_pending(u8 *);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern int moby_step_at_own_position_factor(u8 *, float);
extern int moby_turn_toward_target_and_step(char *, float *, float);
extern int moby_step_controller(void *, void *, float);
extern float moby_get_anim_value(char *);
extern int coll_test_hit_at_bone(void *, int, float, float, int, float, int, int, int);

extern int moby_dispatch_action_by_kind(void *, void *);

/* Update the combat actor's animation, steering and attack-state transitions. */
void combat_actor_update(char *object) {
    float target[4] __attribute__((aligned(16)));
    char *state;
    char *target_object;
    int flags;
    float heading;
    float distance;
    float angle;
    float animation_frame;
    unsigned char phase;

    phase = *(u8 *)(object + 0x20);
    if (phase == 1) return;
    if (object == 0) return;
    if (phase == 0xFE) return;
    if (phase == 0xFD) return;
    state = *(char **)(object + 0x68);
    swaying_actor_update(object);
    phase = *(u8 *)(object + 0x20);
    if (phase == 1 || phase == 0xFE || phase == 0xFD) return;
    if (*(s16 *)(state + 0x4EA) == 0) {
        *(char **)(state + 0x4B0) = 0;
        if (*(u8 *)(object + 0x95) == 4) {
            moby_set_state((u8 *)object, 4, 2);
            if (math_random_int_below(2)) {
                if (*(u8 *)(object + 0x43) != 2) anim_start_blended(object, 2, 0, 10);
            } else if (*(u8 *)(object + 0x43) != 3) anim_start_blended(object, 3, 0, 10);
        }
    }
    if (*(char **)(state + 0x4B0) != 0) {
        *(ActorVectorQuad *)target = *(ActorVectorQuad *)(*(char **)(state + 0x4B0) + 0x10);
        target_object = *(char **)(state + 0x4B0);
        heading = mat_fast_helper_a(*(float *)(target_object + 0x10) - *(float *)(object + 0x10),
                                *(float *)(target_object + 0x14) - *(float *)(object + 0x14));
    } else {
        *(ActorVectorQuad *)target = *(ActorVectorQuad *)(g_hero_state + 0x80);
        heading = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(float *)(object + 0x10),
                                ((Hero *)g_hero_state)->f[0x84 / 4] - *(float *)(object + 0x14));
    }
    distance = vec_distance_xy(object + 0x10, target);
    switch (*(u8 *)(object + 0x95)) {
    case 2:
        if (flag_set_second_pending((u8 *)object)) {
            if (*(u8 *)(object + 0x43) != 11) anim_start_blended(object, 11, 0, 10);
            *(u8 *)(object + 0xBC) = 0;
            moby_set_controller_speed_limits((u8 *)object, 0.002222222276031971f, 0.06666667014360428f,
                         0.0011635529808700085f, 0.10471977293491364f);
            actor_pick_approach_point(object, arena_get_camera_point(*(char **)(object + 0xB8)));
            *(u16 *)(object + 0x96) = 10000;
        }
        if (*(u8 *)(object + 0xBC) == 1 && *(u16 *)(object + 0x96) > 300) {
            switch (math_random_int_below(5)) {
            case 0: if (*(u8 *)(object + 0x43) != 2) anim_start_blended(object, 2, 0, 10); break;
            case 1: if (*(u8 *)(object + 0x43) != 3) anim_start_blended(object, 3, 0, 10); break;
            case 2: if (*(u8 *)(object + 0x43) != 4) anim_start_blended(object, 4, 0, 10); break;
            case 3: if (*(u8 *)(object + 0x43) != 6) anim_start_blended(object, 6, 0, 10); break;
            case 4: if (*(u8 *)(object + 0x43) != 7) anim_start_blended(object, 7, 0, 10); break;
            }
            *(u16 *)(object + 0x96) = math_random_int_below(100);
        }
        if (*(s16 *)(state + 0x4EA) != 0) {
            moby_set_state((u8 *)object, 5, 4);
            if (math_random_int_below(2)) {
                if (*(u8 *)(object + 0x43) != 1) anim_start_blended(object, 1, 0, 10);
            } else if (*(u8 *)(object + 0x43) != 5) anim_start_blended(object, 5, 0, 10);
        }
        angle = mat_fast_helper_a(target[0] - *(float *)(object + 0x10),
                             target[1] - *(float *)(object + 0x14));
        angle = FastDiffRots(*(float *)(object + 0xF8), angle);
        if (angle > 2.7925272f) actor_save_state_and_switch(object);
        if (*(u8 *)(object + 0xBC) == 0 && vec_distance_xy(object + 0x10, state + 0x4A0) < 0.5f)
            *(u8 *)(object + 0xBC) = 1;
        else
            moby_l01_turn_toward_target(object, state + 0x4A0);
        break;
    case 5:
        flags = moby_dispatch_action_by_kind(object, state + 0x60);
        if ((*(u8 *)(object + 0x42) == 16 && math_random_int_below(30) == 0) || (flags & 1)) {
            moby_set_anim_type_three(object, 0, -1);
            actor_tear_down(object);
        } else if (flags & 2)
            moby_set_state((u8 *)object, 7, 4);
        break;
    }
    switch (*(u8 *)(object + 0x20)) {
    case 3:
        if (flag_set_first_pending((u8 *)object)) {
            *(u8 *)(object + 0xBC) = 0;
            if (*(u8 *)(object + 0x43) != 2) anim_start_blended(object, 2, 0, 0);
            *(int *)(state + 0x14C) = -1;
        }
        if (*(u8 *)(object + 0xBC) == 0 &&
            *(u16 *)(object + 0x96) > *(s16 *)(state + 0x4F0)) {
            if (*(u8 *)(object + 0x43) != 11) anim_start_blended(object, 11, 0, 10);
            *(u8 *)(object + 0xBC) = 1;
        } else if (*(u8 *)(object + 0xBC) == 1) {
            if (coll_point_inside_record_volume(object + 0x10, arena_get_state_word(*(char **)(object + 0xB8)))) {
                moby_set_state((u8 *)object, 4, 2);
                *(int *)(state + 0x14C) = cam_hook_return_minus_one(*(char **)(object + 0xB8));
            }
            moby_l01_turn_toward_target(object, arena_get_camera_point(*(char **)(object + 0xB8)));
        }
        break;
    case 5:
        if (*(u8 *)(object + 0x60) & 2) moby_set_state((u8 *)object, 7, -1);
        break;
    case 6:
        if (flag_set_first_pending((u8 *)object)) {
            if (*(u8 *)(object + 0x43) != 10) anim_start_blended(object, 10, 0, 10);
            moby_set_controller_speed_limits((u8 *)object, 0.004444444552063942f, 0.13333334028720856f,
                         0.006981317885220051f, 0.8377581834793091f);
        }
        moby_step_at_own_position_factor((u8 *)object, heading);
        if (*(u8 *)(object + 0x60) & 2)
            moby_set_state((u8 *)object, *(s16 *)(state + 0x4EC), *(s16 *)(state + 0x4EE));
        break;
    case 7:
        if (flag_set_first_pending((u8 *)object) && *(u8 *)(object + 0x43) != 11)
            anim_start_blended(object, 11, 0, 15);
        if (*(u8 *)(object + 0x42) == 8 && distance > 15.0f) {
            if (*(u8 *)(object + 0x43) != 11) anim_start_blended(object, 11, 0, 4);
            moby_set_controller_speed_limits((u8 *)object, 0.004444444552063942f, 0.13333334028720856f,
                         0.0011635529808700085f, 0.10471977293491364f);
        } else if (*(u8 *)(object + 0x42) == 11 && distance < 7.0f) {
            if (*(u8 *)(object + 0x43) != 8) anim_start_blended(object, 8, 0, 4);
            moby_set_controller_speed_limits((u8 *)object, 0.004444444552063942f, 0.03333333507180214f,
                         0.0011635529808700085f, 0.10471977293491364f);
        }
        if (distance < 2.8f &&
            FastDiffRots(*(float *)(object + 0xF8),
                          mat_fast_helper_a(target[0] - *(float *)(object + 0x10),
                                        target[1] - *(float *)(object + 0x14))) < 0.38397247f) {
            moby_set_state((u8 *)object, 8, -1);
            if (*(u8 *)(object + 0x43) != 12) anim_start_blended(object, 12, 4, 3);
            *(int *)(state + 0x4D0) = 0;
        } else if (distance > 2.8f) {
            if (!moby_turn_toward_nearby_enemy(object))
                moby_turn_toward_target_and_step(object, target, *(float *)(state + 0x4B4));
        } else
            moby_step_controller(object, object + 0x10, heading);
        angle = mat_fast_helper_a(target[0] - *(float *)(object + 0x10),
                             target[1] - *(float *)(object + 0x14));
        angle = FastDiffRots(*(float *)(object + 0xF8), angle);
        if (angle > 2.7925272f) actor_save_state_and_switch(object);
        break;
    case 8:
        if (*(u8 *)(object + 0x60) & 2) {
            *(float *)(state + 0x4CC) = 8.0f;
            if (g_active_attacker_robot == object) {
                moby_set_state((u8 *)object, 9, -1);
                if (*(u8 *)(object + 0x43) != 13) anim_start_blended(object, 13, 0, 7);
            } else moby_set_state((u8 *)object, 7, -1);
        }
        animation_frame = moby_get_anim_value(object);
        if (*(u8 *)(object + 0x42) == 12) {
            if (animation_frame >= 19.0f && animation_frame <= 25.0f) {
                coll_test_hit_at_bone(object, 0, 0.35f, (float)*(u8 *)(state + 0x34), 0x10001, 1.0f, 0, 1, 0);
                coll_test_hit_at_bone(object, 1, 0.15f, (float)*(u8 *)(state + 0x34), 0x10001, 1.0f, 0, 1, 0);
                coll_test_hit_at_bone(object, 2, 0.15f, (float)*(u8 *)(state + 0x34), 0x10001, 1.0f, 0, 1, 0);
            }
            if (*(u8 *)(object + 0x42) == 12 && animation_frame >= 17.0f && animation_frame <= 25.0f) {
                gfx_add_draw_callback_first((void (*)(void *))widget_submit_effects, object);
                actor_record_position_history(object);
                *(float *)(state + 0x4CC) = 25.0f;
            }
        }
        moby_step_controller(object, object + 0x10, heading);
        break;
    case 9:
        if (*(u8 *)(object + 0x60) & 2) moby_set_state((u8 *)object, 7, -1);
        break;
    }
    actor_update_hit_timer(object);
}
