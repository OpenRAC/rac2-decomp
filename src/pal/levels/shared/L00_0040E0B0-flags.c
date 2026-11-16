#include "include_asm.h"

#include "common.h"
extern void cam_compute_view_direction(char *, void *, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);
extern float g_camera_l00_position[4];
typedef struct SoundSlotA4A8 { char pad[0x74]; unsigned char active; char pad75[0x13]; void *object; } SoundSlotA4A8;
typedef struct PlayerLinkA4A8 { char pad[0x2290]; void *object; } PlayerLinkA4A8;
typedef struct CollisionResultA4A8 { char pad[0x18]; void *object; int surface; float position[4]; char pad30[0x10]; float normal[4]; } CollisionResultA4A8;
typedef struct TuningA4A8 { char pad[0x70]; float damage; char tail[0x6c]; } TuningA4A8;
extern char g_sound_state[], g_hero_position[];
extern PlayerLinkA4A8 g_hero_state;
extern unsigned char g_item_slot_to_record[];
extern TuningA4A8 g_weapon_l00_table[];
extern char g_shot_history_points[];
extern unsigned short g_homing_moby_index_list[] MACRO_ADDR;
extern CollisionResultA4A8 g_collision_result;
extern void *g_active_tether_object MACRO_ADDR;
extern float *moby_get_private_value_0(void *);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecLength(void *);
extern float math_fast_sin_or_cos_b(float);
extern float math_fabs(float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern float FastAddRotations(float, float);
extern void part_steer_effect_direction(int, void *, int);
extern void table_clear_entry_flag(int);
extern void vec_transform_or_copy(void *, void *);
extern void RemoveMobyFromIndexList(void *, void *);
extern void moby_get_offset_point(void *, void *);
extern void moby_start_animation_from_table(void *);
extern void ref_L00_0040A4A8_00(void (*)(void *), void *);
extern void line_particles_spawn_pal(void *, void *);
extern int CollLine(void *, void *, int, void *, void *);
extern int math_random_int_below(int);
extern float coll_probe_ground_height_below(void *, int, float);
extern void *parented_explosion_spawn_pal(void *, float, int, int, int, int, int, int, int, int, int, int, void *);
extern void shot_draw_impact_beam(void *, void *, void *);
extern void moby_mark_spawned(void *);
extern int FastDecTimer(void *);
extern float vec_distance_xy(void *, void *);
typedef struct ProjectileCollisionA4A8 {
    float direction[3];
    float marker;
    void *object;
    int flags;
    unsigned char kind, enabled;
    unsigned short class_id;
    float damage;
    int active;
} ProjectileCollisionA4A8;
typedef struct ProjectileStateA4A8 {
    float last_target[3];
    void *owner;
    struct ProjectileObjectA4A8 *target;
    float height, speed, yaw, spin_speed;
    short life;
    unsigned char homing, age;
    float spin;
    int history_index;
    float forward[4], target_offset[4];
    int sound, handle;
} ProjectileStateA4A8;
typedef struct ProjectileObjectA4A8 {
    char pad00[0x10];
    float position[4];
    signed char status;
    char pad21[0x47];
    ProjectileStateA4A8 *state;
    char pad6c[0x3e];
    unsigned short class_id;
    char padac[0x10];
    unsigned char hit;
    char padbd[3];
    float forward[4], right[4], up[4];
} ProjectileObjectA4A8;

/* Per-frame update for a homing shot (moby class 3799). It steers toward its target, leaves a trail, and blows up when it hits something, leaves the map or runs out of time. (PAL: 50 Hz timings) */
void homing_l00_shot_update_3_pal(ProjectileObjectA4A8 *object)
{
    float old[4] __attribute__((aligned(16)));
    float up[4] __attribute__((aligned(16)));
    float target_position[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float desired[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    union { ProjectileCollisionA4A8 record; float v[3][4]; } scratch __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    void *hit_object = 0;
    ProjectileStateA4A8 *state = object->state;
    ProjectileObjectA4A8 *target = state->target;
    float *health;
    float length, distance, angle, turn;
    int target_status;
    char *history;
    int i, explode;

    qcopy(old, object->position);
    cam_compute_view_direction((char *)object->position, up, 1);
    {
        SoundSlotA4A8 *sound = (SoundSlotA4A8 *)(g_sound_state + state->sound * 0x70);
        if (sound->object != object || sound->active == 0)
            state->sound = PlayMobySound(1, 4, object);
    }
    {
        if (target != 0) {
            health = moby_get_private_value_0(target);
            target_status = (unsigned char)target->status;
            if (target_status == 0xfe) goto target_lost;
            if (target_status == 0xfd) goto target_lost;
            if (health != 0 && *health <= 0.0f) {
            target_lost:
                state->target = 0;
                target = 0;
            } else {
                qcopy(target_position, target->position);
                FastVecScale(step, up, state->height);
                FastVecAdd(target_position, target_position, step);
            }
        }
        if (target != 0 && state->life < 296 && target->status >= 0 && state->homing != 0) {
            step[0] = state->last_target[0];
            step[1] = state->last_target[1];
            step[2] = state->last_target[2];
            step[3] = 0.0f;
            FastVecSub(delta, target_position, step);
            length = FastVecLength(delta);
            FastVecAdd(desired, target_position, state->target_offset);
            FastVecSub(direction, object->position, desired);
            distance = FastVecLength(direction);
            if (distance != 0.0f) {
                angle = FastVecDot(direction, delta) / distance;
                angle = 1.5707963705f - math_fast_angle_helper(angle);
                FastVecCross(scratch.v[0], delta, direction);
                FastVecCross(scratch.v[1], delta, scratch.v[0]);
                if (FastVecDot(direction, scratch.v[1]) < 0.0f)
                    angle = -angle;
                turn = length / state->speed;
                turn *= math_fast_sin_or_cos_b(angle);
                while (turn > 1.0f) turn -= 1.0f;
                while (turn < -1.0f) turn += 1.0f;
                angle = math_fast_angle_helper(turn);
                FastVecScale(direction, direction, -1.0f);
                vec_scale_to_length(direction, direction, 1.0f);
                if (math_fabs(angle) > 0.00001f) {
                    vec_scale_to_length(scratch.v[2], scratch.v[0], 1.0f);
                    math_build_axis_angle_quat(scratch.v[2], scratch.v[2], angle);
                    vec_rotate_by_quaternion(object->forward, direction, scratch.v[2]);
                    FastVecCross(object->right, object->forward, up);
                    vec_scale_to_length(object->right, object->right, 1.0f);
                    FastVecCross(object->up, object->right, object->forward);
                    qcopy(state->forward, object->forward);
                }
            }
        } else {
            part_steer_effect_direction(state->handle, state->forward, 0);
            qcopy(object->forward, state->forward);
            FastVecCross(object->right, object->forward, up);
            vec_scale_to_length(object->right, object->right, 1.0f);
            FastVecCross(object->up, object->right, object->forward);
        }
        if (target != 0) {
            state->last_target[0] = target_position[0];
            state->last_target[1] = target_position[1];
            state->last_target[2] = target_position[2];
        }
        if (math_fabs(state->yaw) > 0.0021f) {
            qcopy(step, object->forward);
            math_build_axis_angle_quat(delta, object->right, state->yaw * 0.017453294f);
            vec_rotate_by_quaternion(object->forward, object->forward, delta);
            vec_rotate_by_quaternion(object->up, object->up, delta);
            math_build_axis_angle_quat(delta, step, state->spin);
            vec_rotate_by_quaternion(object->forward, object->forward, delta);
            vec_rotate_by_quaternion(object->right, object->right, delta);
            vec_rotate_by_quaternion(object->up, object->up, delta);
            math_build_axis_angle_quat(delta, object->forward, state->spin);
            vec_rotate_by_quaternion(object->right, object->right, delta);
            vec_rotate_by_quaternion(object->up, object->up, delta);
            state->spin = FastAddRotations(state->spin, state->spin_speed * 0.017453294f);
        }
        object->forward[3] = object->right[3] = object->up[3] = 0.0f;
        FastVecScale(step, object->forward, state->speed);
        FastVecAdd(object->position, object->position, step);
        vec_transform_or_copy(object->position, object->position);
        if (object->position[0] < 2.0f || object->position[0] > 1021.0f ||
            object->position[1] < 2.0f || object->position[1] > 1021.0f ||
            object->position[2] < 2.0f || object->position[2] > 1021.0f) {
            RemoveMobyFromIndexList(object, g_homing_moby_index_list);
            moby_mark_spawned(object);
        } else {
            moby_get_offset_point(object, delta);
            history = g_shot_history_points + state->history_index * 0x40;
            for (i = 3; i > 0; i--) qcopy(history + i * 16, history + (i - 1) * 16);
            qcopy(history, delta);
            if (++state->age >= 4)
                ref_L00_0040A4A8_00(moby_start_animation_from_table, object);
            line_particles_spawn_pal(object, old);
            qcopy(desired, object->position);
            FastVecScale(direction, up, -0.3f);
            FastVecAdd(direction, object->position, direction);
            if (CollLine(desired, direction, 2, 0, 0)) {
                FastVecScale(desired, up, 0.3f);
                FastVecAdd(object->position, g_collision_result.position, desired);
            }
            {
                int settings_index = g_item_slot_to_record[0x2c];
                TuningA4A8 *settings = &g_weapon_l00_table[settings_index];
                scratch.record.damage = settings->damage;
            }
            scratch.record.flags = 0x830000;
            scratch.record.object = object;
            scratch.record.active = 1;
            qcopy(scratch.record.direction, step);
            vec_scale_to_length(scratch.record.direction, scratch.record.direction, 1.0f);
            scratch.record.marker = 5627.925f;
            scratch.record.kind = 3;
            scratch.record.enabled = 1;
            scratch.record.class_id = object->class_id;
            if (CollLine(old, object->position, 0, g_hero_state.object, &scratch.record)) {
                if (g_collision_result.object != 0) {
                    if (g_collision_result.object != g_hero_state.object &&
                        g_collision_result.object != state->owner) {
                        object->hit = 2;
                        qcopy(object->position, g_collision_result.position);
                        hit_object = object;
                    }
                } else if (g_collision_result.surface > 0) {
                    object->hit = 1;
                    qcopy(object->position, g_collision_result.position);
                }
            }
            if (object->hit != 0) {
                {
                    int sound_index = state->sound;
                    if (sound_index != -1) {
                        SoundSlotA4A8 *sound = (SoundSlotA4A8 *)(g_sound_state + sound_index * 0x70);
                        if (sound->object == object && sound->active != 0) snd_stop_voice(sound_index);
                    }
                }
                state->sound = -1;
                PlayMobySound(0, 0, object);
                qcopy(object->position, g_collision_result.position);
                cam_compute_view_direction((char *)object->position, axis, 1);
                explode = 1;
                if (g_collision_result.object != 0 && g_collision_result.surface <= 0) {
                    FastVecSub(normal, g_camera_l00_position, object->position);
                    vec_scale_to_length(normal, normal, 1.0f);
                } else {
                    vec_scale_to_length(normal, g_collision_result.normal, 1.0f);
                    if (math_fabs(FastVecDot(normal, axis)) >= 0.1f) explode = 0;
                }
                if (explode) coll_probe_ground_height_below(object->position, 0, 0.5f);
                {
                    int draw_effect = math_random_int_below(5) == 0;
                    parented_explosion_spawn_pal(object->position, 0.5f, 1, 15, 0, 0, 8, 15, 0, 1, 0, draw_effect, g_active_tether_object);
                }
                shot_draw_impact_beam(object, axis, hit_object);
                RemoveMobyFromIndexList(object, g_homing_moby_index_list);
                table_clear_entry_flag(state->handle);
                moby_mark_spawned(object);
            } else if (FastDecTimer(&state->life) || vec_distance_xy(object->position, g_hero_position) > 60.0f) {
                {
                    int sound_index = state->sound;
                    if (sound_index != -1) {
                        SoundSlotA4A8 *sound = (SoundSlotA4A8 *)(g_sound_state + sound_index * 0x70);
                        if (sound->object == object && sound->active != 0) snd_stop_voice(sound_index);
                    }
                }
                state->sound = -1;
                RemoveMobyFromIndexList(object, g_homing_moby_index_list);
                table_clear_entry_flag(state->handle);
                moby_mark_spawned(object);
            }
        }
    }
}
