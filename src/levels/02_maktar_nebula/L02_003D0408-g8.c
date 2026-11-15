#include "common.h"
/* The animation flag byte belongs to the incoming actor. All six measured
 * reads use this one field view, including the two snapshots taken before the
 * distance comparison even on its abandon path. This is a partial view, never
 * an owning allocation. */
typedef struct {
    unsigned char reserved[0x60];
    volatile unsigned char animation_flags;
} ActorAnimationFlags;

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct { float x, y, z, w; } Position;
typedef struct { char pad[0x10]; Position position; } ActorPosition;
typedef struct { char pad[0x80]; Vector position; } PlayerPosition;
extern char g_hero_state[] NOT_SDA;
extern int D_L02_001B0148 __attribute__((sda));
extern void armed_enemy_update(char *), armed_enemy_return_to_idle(char *), moby_start_anim_fast(char *), moby_start_anim_slow(char *), armed_enemy_finish_frame(char *), armed_enemy_update_attack_variant(char *);
extern void armed_enemy_pick_point_near_target(char *, float *), armed_enemy_release_held_object(char *, Quad *), enemy_release_effect_record(char *), moby_set_anim_type_three(void *, int, int);
extern int AimAtGroupEntityInConeL02(char *), armed_enemy_try_close_attack(char *), flag_set_first_pending(u8 *), flag_set_second_pending(u8 *), math_random_int_below(int), arena_get_state_word(char *), coll_point_inside_record_volume(void *, int), cam_hook_return_minus_one(char *);
extern char *arena_get_camera_point(char *);
extern float mat_fast_helper_a(float, float), vec_distance_xy(void *, void *), FastDiffRots(float, float), moby_get_anim_value(char *);
/* Retail forwards the final dot product in F0. */
extern float vec_normalized_direction_dot(char *, char *);
extern void moby_set_state(u8 *, int, int), anim_start_blended(char *, int, int, int);
extern int moby_l01_turn_toward_target(char *, char *);
extern int moby_step_controller(void *, void *, float);
extern int moby_turn_toward_target_and_step(char *, float *, float);
extern void moby_step_at_own_position(char *), moby_step_at_own_position_factor(u8 *, float), AttachManipulator(u8 *, u32, u8 *), mem_clear(char *, int, int), vec_random_direction(float *, float, float);
extern unsigned long moby_dispatch_action_by_kind(void *, void *);
/* This interleaving preserves the four integer and four FP argument banks. */
extern void part_spawn_masked_debris(char *, int, float *, float, float, float, float, u8);
extern void part_queue_moby_for_glow(char *, int, void (*)(char *));
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
/* Runs the armed enemy's target selection and combat animation state machines. */
void armed_enemy_update_combat(char *self) {
    Vector target, scratch;
    char *state, *owner, *point;
    char *targetObject;
    float heading, distance, turn, time, saved, targetX, targetY, selfX, selfY;
    unsigned long flags;
    long previous;
    int animationFlags;
    int stateByte = (u8)self[0x20];
    if (stateByte == 1 || !self || stateByte == 0xFE || stateByte == 0xFD) return;
    state = *(char **)(self + 0x68);
    armed_enemy_update(self);
    flags = 0;
    stateByte = (u8)self[0x20];
    if (stateByte == 1 || stateByte == 0xFE || stateByte == 0xFD) return;
    if (!*(short *)(state + 0x2F6)) {
        *(char **)(state + 0x2E0) = 0;
        if ((u8)self[0x95] != 2 && (u8)self[0x95] != 7 && (u8)self[0x95] != 1) armed_enemy_return_to_idle(self);
    }
    targetObject = *(char **)(state + 0x2E0);
    if (targetObject) {
        target.quad = *(Quad *)(targetObject + 0x10);
        selfX = ((ActorPosition *)self)->position.x;
        selfY = ((ActorPosition *)self)->position.y;
        targetX = ((ActorPosition *)*(char **)(state + 0x2E0))->position.x;
        targetY = ((ActorPosition *)*(char **)(state + 0x2E0))->position.y;
        targetX -= selfX;
        targetY -= selfY;
        heading = mat_fast_helper_a(targetX, targetY);
    } else {
        target.quad = *(Quad *)(g_hero_state + 0x80);
        selfX = ((ActorPosition *)self)->position.x;
        selfY = ((ActorPosition *)self)->position.y;
        targetX = ((PlayerPosition *)g_hero_state)->position.f[0];
        targetY = ((PlayerPosition *)g_hero_state)->position.f[1];
        targetX -= selfX;
        targetY -= selfY;
        heading = mat_fast_helper_a(targetX, targetY);
    }
    distance = vec_distance_xy(self + 0x10, &target);
    switch ((u8)self[0x95]) {
    case 2:
        if (flag_set_second_pending((u8 *)self)) {
            owner = *(char **)(self + 0xB8); point = arena_get_camera_point(owner);
            if ((u8)self[0x43] != 3) anim_start_blended(self, 3, 0, 10);
            self[0xBC] = 0; armed_enemy_pick_point_near_target(self, (float *)point); *(u16 *)(self + 0x96) = 10000;
        }
        if ((u8)self[0xBC] == 1 && *(u16 *)(self + 0x96) > 300) {
            switch (math_random_int_below(2)) {
            case 0: if ((u8)self[0x43] != 1) anim_start_blended(self, 1, 0, 10); break;
            case 1: if (*(u8 *)(self + 0x43)) anim_start_blended(self, 0, 0, 10); break;
            }
            *(u16 *)(self + 0x96) = math_random_int_below(100);
        }
        if (*(short *)(state + 0x2F6)) moby_start_anim_fast(self);
        point = state + 0x2D0;
        if (!*(u8 *)(self + 0xBC)) {
            if (vec_distance_xy(self + 0x10, point) < 0.5f) { self[0xBC] = 1; break; }
        }
        moby_step_controller(self, point, heading);
        break;
    case 5:
        if (((ActorAnimationFlags *)self)->animation_flags & 2) moby_start_anim_slow(self);
        break;
    case 3:
        if (!AimAtGroupEntityInConeL02(self)) {
            switch ((u8)self[0x42]) {
            case 2: moby_l01_turn_toward_target(self, (char *)&target); break;
            case 3: moby_turn_toward_target_and_step(self, target.f, *(float *)(state + 0x2E8)); break;
            }
        }
        break;
    case 4:
        if (distance > 14) moby_start_anim_fast(self);
        else if (!armed_enemy_try_close_attack(self)) {
            if (distance < 4) {
                turn = FastDiffRots(*(float *)(self + 0xF8), heading);
                if (turn < 0.26179942f) { moby_set_state((u8 *)self, 11, -1); break; }
            }
            if ((u8)self[0x20] == 11 && distance > 5) moby_set_state((u8 *)self, 10, -1);
        }
        break;
    case 6: moby_step_at_own_position_factor((u8 *)self, heading); break;
    case 7:
        flags = moby_dispatch_action_by_kind(self, state + 0x50);
        if (*(float *)(state + 0x20) <= 1 && *(char **)(state + 0x2E4)) {
            scratch.quad = *(Quad *)(*(char **)(state + 0x2E4) + 0x10); armed_enemy_release_held_object(self, &scratch.quad);
        }
        if (*(float *)(state + 0x20) <= 0 && !*(u8 *)(state + 0x291)) {
            mem_clear(state + 0x290, 0, 64); AttachManipulator((u8 *)self, 3, (u8 *)(state + 0x290));
            *(float *)(state + 0x2B8) = 0.0001f; *(float *)(state + 0x2B4) = 0.0001f; *(float *)(state + 0x2B0) = 0.0001f; state[0x292] = 1;
            vec_random_direction(scratch.f, 0.016666668f, 0.050000004f);
            part_spawn_masked_debris(self, 0x20, scratch.f, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        }
        if (!(flags & 1UL)) {
            if (!(*(float *)(state + 0x20) <= 0 && *(u16 *)(self + 0x96) > 60)) break;
        }
        *(int *)(self + 0x98) = 0; moby_set_anim_type_three(self, 0, -1); part_queue_moby_for_glow(self, 0, enemy_release_effect_record);
        break;
    }
    switch ((u8)self[0x20]) {
    case 3:
        if (flag_set_first_pending((u8 *)self)) {
            self[0xBC] = 0; if (*(u8 *)(self + 0x43)) anim_start_blended(self, 0, 0, 0); *(int *)(state + 0x13C) = -1;
        }
        if (!*(u8 *)(self + 0xBC) && (int)*(u16 *)(self + 0x96) > (int)*(short *)(state + 0x2FC)) {
            if ((u8)self[0x43] != 3) anim_start_blended(self, 3, 0, 10); self[0xBC] = 1;
        } else if ((u8)self[0xBC] == 1) {
            owner = *(char **)(self + 0xB8);
            if (coll_point_inside_record_volume(self + 0x10, arena_get_state_word(owner))) {
                moby_set_state((u8 *)self, 4, 2); *(int *)(state + 0x13C) = cam_hook_return_minus_one(*(char **)(self + 0xB8));
            }
            point = arena_get_camera_point(*(char **)(self + 0xB8)); moby_l01_turn_toward_target(self, point);
        }
        break;
    case 7:
        if (distance < 4 || *(u16 *)(self + 0x96) > 450 || *(int *)(state + 0x180) > 30) moby_start_anim_fast(self);
        break;
    case 6:
        if (distance > 14) {
            moby_set_controller_speed_limits((u8 *)self, 0.0055555556900799274f, 0.10333333909511566f, 0.0034906589426100254f, 0.41887909173965454f);
            moby_set_state((u8 *)self, 7, 3); if ((u8)self[0x43] != 3) anim_start_blended(self, 3, 0, 10);
        } else if (distance < 4 || *(int *)(state + 0x180) > 30) moby_start_anim_slow(self);
        break;
    case 10:
        time = moby_get_anim_value(self); turn = vec_normalized_direction_dot(self, (char *)&target);
        if (turn > 0.01f) { moby_set_state((u8 *)self, 9, -1); if ((u8)self[0x43] != 5) anim_start_blended(self, 5, 0, 10); }
        else if (turn < -0.01f) { moby_set_state((u8 *)self, 8, -1); if ((u8)self[0x43] != 4) anim_start_blended(self, 4, 0, 10); moby_step_at_own_position_factor((u8 *)self, heading); break; }
        else if (distance < 4) moby_set_state((u8 *)self, 11, -1);
        else {
            if (time < 2) moby_set_controller_speed_limits((u8 *)self, 0.0055555556900799274f, 0.033333335f, 0.0034906589426100254f, 0.41887909173965454f);
            else if ((time > 10 && moby_get_anim_value(self) < 17) || !(time < 20)) goto face_target;
            moby_l01_turn_toward_target(self, (char *)&target); break;
        }
face_target:
        moby_step_at_own_position_factor((u8 *)self, heading); break;
    case 8:
        if (vec_normalized_direction_dot(self, (char *)&target) > -0.01f) {
            moby_set_state((u8 *)self, 10, -1); if ((u8)self[0x43] != 6) anim_start_blended(self, 6, 0, 10); moby_step_at_own_position(self);
        } else if (moby_get_anim_value(self) > 5) {
            saved = *(float *)(state + 0x130); *(float *)(state + 0x130) = 0.01745329424738884f;
            moby_step_at_own_position_factor((u8 *)self, heading); *(float *)(state + 0x130) = saved;
        }
        break;
    case 9:
        if (vec_normalized_direction_dot(self, (char *)&target) < 0.01f) {
            moby_set_state((u8 *)self, 10, -1); if ((u8)self[0x43] != 6) anim_start_blended(self, 6, 0, 10); moby_step_at_own_position(self);
        } else if (moby_get_anim_value(self) > 5) {
            saved = *(float *)(state + 0x130); *(float *)(state + 0x130) = 0.01745329424738884f;
            moby_step_at_own_position_factor((u8 *)self, heading); *(float *)(state + 0x130) = saved;
        }
        break;
    case 11:
        if (flag_set_first_pending((u8 *)self) && (u8)self[0x43] != 1) anim_start_blended(self, 1, 0, 10);
        moby_step_at_own_position_factor((u8 *)self, heading);
        /* fall through */
    case 19: case 20:
        if (flags & 2UL) armed_enemy_return_to_idle(self);
        break;
    case 13:
        if (((ActorAnimationFlags *)self)->animation_flags & 2) { *(float *)(self + 0x48) = 0.5f; moby_set_state((u8 *)self, 14, -1); if ((u8)self[0x43] != 9) anim_start_blended(self, 9, 0, 10); }
        break;
    case 14:
        if (distance < 4) {
            D_L02_001B0148 = 0; *(float *)(self + 0x48) = 1; moby_set_state((u8 *)self, 15, -1);
            if ((u8)self[0x43] != 10) anim_start_blended(self, 10, 10, 10);
        } else {
            animationFlags = ((ActorAnimationFlags *)self)->animation_flags; previous = animationFlags;
            if (distance > 4) goto abandon_attack;
            if (!(previous & 2)) break;
            previous = D_L02_001B0148++;
            if (previous < 3) break;
            D_L02_001B0148 = 0; *(float *)(self + 0x48) = 1;
            armed_enemy_return_to_idle(self);
        }
        break;
    case 15: case 18:
        if (((ActorAnimationFlags *)self)->animation_flags & 2) {
            *(short *)(state + 0x2F8) = 0;
            if (*(char **)(g_hero_state + 0x249C) == self) {
                moby_set_state((u8 *)self, 12, 5); if ((u8)self[0x43] != 7) anim_start_blended(self, 7, 0, 10);
            } else armed_enemy_return_to_idle(self);
        }
        armed_enemy_update_attack_variant(self); break;
    case 16:
        if (((ActorAnimationFlags *)self)->animation_flags & 2) { *(float *)(self + 0x48) = 0.5f; moby_set_state((u8 *)self, 17, -1); if ((u8)self[0x43] != 12) anim_start_blended(self, 12, 0, 10); }
        break;
    case 17:
        if (distance < 4) {
            D_L02_001B0148 = 0; *(float *)(self + 0x48) = 1; moby_set_state((u8 *)self, 18, -1);
            if ((u8)self[0x43] != 13) anim_start_blended(self, 13, 10, 10);
        } else {
            animationFlags = ((ActorAnimationFlags *)self)->animation_flags; previous = animationFlags;
            if (distance > 4) {
abandon_attack:
                *(float *)(self + 0x48) = 1; armed_enemy_return_to_idle(self);
            } else if (previous & 2) {
                previous = D_L02_001B0148++;
                if (previous > 2) { D_L02_001B0148 = 0; *(float *)(self + 0x48) = 1; armed_enemy_return_to_idle(self); }
            }
        }
        break;
    }
    armed_enemy_finish_frame(self);
}
