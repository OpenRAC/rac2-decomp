#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;
typedef struct TetherState TetherState;
typedef struct {
    u8 pad00[0x10];
    Vector position;
    u8 pad20[4];
    struct { u8 pad00[0x46]; s16 kind; } *owner;
    u8 pad28[0xC];
    u16 flags;
    u8 pad36[0x32];
    TetherState *state;
    u8 pad6C[0x3E];
    s16 object_class;
    u8 padAC[0x10];
    u8 hit;
    u8 padBD[3];
    Vector right, up, forward;
    float pitch, yaw, roll;
} Moby;
struct TetherState {
    int unknown00;
    float speed;
    int unknown08[2];
    int timer;
    Moby *attached;
    float input_x, input_y;
    int unknown20;
    Moby *left_fin, *right_fin;
    int sound;
    int unknown30[5];
    float hover;
    float target_speed;
    int camera;
};
typedef struct {
    Vector direction;
    Moby *owner;
    u32 flags;
    u8 kind, response;
    u16 object_class;
    float power;
    int mode;
} DamageRecord;
typedef struct {
    int unknown00[6];
    Moby *hit;
    int mesh;
    Vector position, unknown30, normal, edgeStart, edgeEnd, tail;
} CollisionResult;
typedef struct { u8 pad00[0x70]; float power; u8 pad74[0x6C]; } LevelClass;
extern u32 g_pad_state[];
extern u8 g_hero_state[], g_sound_state[], g_item_slot_to_record[];
extern int g_visibomb_phase_flag, g_cinematic_phase_flag, g_active_tether_object, g_hero_locked_flag;
extern int g_visibomb_missile_active __attribute__((sda)), g_pad_device_idle_flag __attribute__((sda));
extern float g_visibomb_pitch_scale __attribute__((sda)), g_visibomb_min_speed __attribute__((sda)), g_visibomb_max_speed __attribute__((sda));
extern float g_visibomb_target_speed_blend __attribute__((sda)), g_visibomb_speed_blend __attribute__((sda));
extern CollisionResult g_collision_result;
extern Vector g_cam_follow_matrix;
extern LevelClass g_weapon_l00_table[];
extern int g_area_hit_targets[];
extern void level_start_timed_object_once(void);
extern int ForceClaimNotice(int, void *, int);
extern void tether_release(Moby *, TetherState *), level_restore_lighting(Moby *, int), tether_attach_to_parent(Moby *, TetherState *);
extern int cam_follow_update_target_us2(Moby *, Moby *);
extern int FloatToInt(float), snd_set_voice_pitch_bend(int, int);
extern float math_fabs(float), fast_subtract_rotations(float, float), coll_probe_ground_height_below(void *, int, float), ApproachValue(float *, float, float), mat_fast_helper_a(float, float);
extern void math_build_axis_angle_quat(void *, void *, float), vec_rotate_by_quaternion(void *, void *, void *), part_steer_effect_direction(int, void *, void *), part_queue_ground_shadow(Moby *, float);
extern void FastVecScale(void *, void *, float), vec_build_spherical_offset(float *, float, float, float), FastVecAdd(void *, void *, void *), vec_transform_or_copy(void *, void *);
extern void build_axis_rotation_quaternion(void *, int, float), vec_fast_normalize_helper(void *, void *, float);
extern int moby_find_accepting_table_object(Vector *), CollLine(void *, void *, int, Moby *, DamageRecord *);
extern void FastVecSub(void *, void *, void *), vec_scale_to_length(void *, void *, float), vec_fast_normalize(void *, void *, void *), snd_stop_voice(int);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern int coll_process_hit(float, void *, int, Moby *, int);
extern void moby_queue_knockback_for_nodes(void *, Vector *, int *, int, int, int, int, int, float, float, float);
extern void vec_add_random_offset(float *, float), tether_spawn_impact_effects(Moby *, int), cam_compute_view_direction(Vector *, Vector *, int), FastVecCross(void *, void *, void *);
extern float ref_US2_L00_00392CE0_01;

/* Moves the Visibomb missile each frame (US2 copy of visibomb_missile_update): steers it from the stick, sweeps for hits, bursts on impact and drives the attached fins. */
void visibomb_missile_update_us2(Moby *missile) {
    Vector prev_position, blast, blast_normal, velocity, contact_edge, temp;
    DamageRecord damage;
    TetherState *state = missile->state;
    Moby *mount, *ignore;
    u8 *sound;
    float desired_speed, angle, turn, height, roll, yaw;
    Vector *fin;
    int timer, player_hit = 0, i, hits;
    blast.quad = 0; blast_normal.quad = 0;
    blast.f[2] = 0.13333334f; blast_normal.f[2] = 1;
    g_visibomb_phase_flag = 1; g_visibomb_missile_active = 1;
    level_start_timed_object_once(); g_cinematic_phase_flag = 1; ForceClaimNotice(6, 0, 1);
    timer = --state->timer;
    if (timer < -99 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x16 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x39 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x6F ||
        ((Hero *)g_hero_state)->i[0x229C / 4] == 2 || ((Hero *)g_hero_state)->i[0x229C / 4] == 4 || ((Hero *)g_hero_state)->i[0x229C / 4] == 3 || ((Hero *)g_hero_state)->i[0x229C / 4] > 12 ||
        ((Hero *)g_hero_state)->i[0x229C / 4] == 7 || ((Hero *)g_hero_state)->i[0x229C / 4] == 10 || ((Hero *)g_hero_state)->i[0x229C / 4] == 16 || ((Hero *)g_hero_state)->i[0x229C / 4] == 5 ||
        ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x62 || ref_US2_L00_00392CE0_01 > 0.0f || !((Hero *)g_hero_state)->i[0x340 / 4] ||
        ((mount = ((Hero *)g_hero_state)->ptr[0x33C / 4]) && (mount->object_class == 0x13E || mount->object_class == 0x46F)) || g_pad_device_idle_flag) {
        tether_release(missile, state); return;
    }
    if (timer < 0) {
        if (g_active_tether_object) { tether_release(missile, state); ((Hero *)g_hero_state)->h[0x1E0 / 2] = 12; return; }
        if (state->attached) cam_follow_update_target_us2(state->attached, missile);
        level_restore_lighting(missile, 0); tether_attach_to_parent(missile, state); return;
    }
    desired_speed = g_visibomb_min_speed * 0.016666668f;
    if (g_pad_state[0x1A0 / 4] & 0x40) desired_speed = g_visibomb_max_speed * 0.016666668f;
    state->target_speed += (desired_speed - state->target_speed) * g_visibomb_target_speed_blend;
    state->speed += (state->target_speed - state->speed) * g_visibomb_speed_blend;
    if (state->speed > g_visibomb_max_speed * 0.016666668f) state->speed = g_visibomb_max_speed * 0.016666668f;
    snd_set_voice_pitch_bend(state->sound, FloatToInt((state->target_speed - (g_visibomb_min_speed * 0.016666668f) /
                      (g_visibomb_max_speed * 0.016666668f - g_visibomb_min_speed * 0.016666668f)) * g_visibomb_pitch_scale));
    if ((u32)(state->timer - 1) < 0xBB2) {
        float stick_x = ((Hero *)g_hero_state)->f[0x1FB0 / 4], stick_y = ((Hero *)g_hero_state)->f[0x1FB4 / 4];
        state->input_x += (stick_x - state->input_x) * 0.1f;
        state->input_y += (stick_y - state->input_y) * 0.1f;
        if (g_hero_locked_flag) {
            missile->pitch = (state->input_x - missile->pitch) * 0.06f;
            missile->yaw = state->input_y * 0.012271847f;
            missile->roll = state->input_x * 0.012271847f;
            if (math_fabs(missile->roll) > 0.00001f) {
                math_build_axis_angle_quat(&temp, &missile->forward, -missile->roll);
                vec_rotate_by_quaternion(&missile->right, &missile->right, &temp); vec_rotate_by_quaternion(&missile->up, &missile->up, &temp);
            }
            if (math_fabs(missile->yaw) > 0.00001f) {
                math_build_axis_angle_quat(&temp, &missile->up, -missile->yaw);
                vec_rotate_by_quaternion(&missile->right, &missile->right, &temp); vec_rotate_by_quaternion(&missile->forward, &missile->forward, &temp);
            }
            if (math_fabs(missile->pitch) > 0.00001f) {
                math_build_axis_angle_quat(&temp, &missile->right, missile->pitch);
                vec_rotate_by_quaternion(&missile->up, &missile->up, &temp); vec_rotate_by_quaternion(&missile->forward, &missile->forward, &temp);
            }
            part_steer_effect_direction(state->camera, &missile->right, 0);
        } else {
            missile->pitch += (state->input_x - missile->pitch) * 0.06f;
            angle = fast_subtract_rotations(missile->yaw, state->input_y * 0.012271847f);
            missile->yaw = angle;
            if (angle >= 1.5707964f) missile->yaw = 1.5697963f;
            else if (angle <= -1.5707964f) missile->yaw = -1.5697963f;
            missile->roll = fast_subtract_rotations(missile->roll, state->input_x * 0.012271847f);
            part_queue_ground_shadow(missile, 0.2f);
        }
    }
    if (g_hero_locked_flag) FastVecScale(&velocity, &missile->right, state->speed);
    else vec_build_spherical_offset(velocity.f, state->speed, missile->roll, -missile->yaw);
    qcopy(&prev_position, &missile->position);
    FastVecAdd(&missile->position, &missile->position, velocity.f); vec_transform_or_copy(&missile->position, &missile->position);
    if (state->timer >= 0xB7D) {
        height = coll_probe_ground_height_below(&missile->position, 0, 0.5f) + state->hover;
        if (missile->position.f[2] < height && (!g_collision_result.hit ||
            (g_collision_result.hit->owner && g_collision_result.hit->owner->kind == 5))) {
            turn = mat_fast_helper_a(state->speed, ApproachValue(&missile->position.f[2], height, 0.10000001f));
            if (turn > 0.026179943f) turn = 0.026179943f;
            missile->yaw -= turn;
        }
    }
    if (missile->position.f[0] < 4.5f || missile->position.f[0] > 1018.5f || missile->position.f[1] < 4.5f ||
        missile->position.f[1] > 1018.5f || missile->position.f[2] < 4.5f || missile->position.f[2] > 1018.5f) {
        tether_release(missile, state); return;
    }
    tether_attach_to_parent(missile, state);
    build_axis_rotation_quaternion(&state->left_fin->position, 1,
                  -(state->input_y * 0.5f + math_fabs(state->input_x * 0.33333334f) + (state->input_x - missile->pitch) * 1.1f) * 0.7f);
    fin = &state->right_fin->position;
    roll = (state->input_y * 0.5f + math_fabs(state->input_x * 0.33333334f));
    build_axis_rotation_quaternion(fin, 1, ((state->input_x - missile->pitch) * 1.1f - roll) * 0.7f);
    damage.flags = 0x830000; damage.direction.quad = velocity.quad; damage.owner = missile;
    damage.mode = 1; damage.power = (g_weapon_l00_table + g_item_slot_to_record[0xE])->power;
    vec_fast_normalize_helper(&damage.direction, &damage.direction, 1);
    damage.kind = 3; damage.direction.f[3] = 5627.925f;
    damage.object_class = missile->object_class; damage.direction.f[2] = 1; damage.response = 2;
    ignore = missile;
    if (state->timer > 0xB90) ignore = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
    if (moby_find_accepting_table_object(&missile->position)) {
        missile->hit = 2;
        qcopy(&contact_edge, &g_cam_follow_matrix);
        temp.quad = 0; temp.f[2] = 1; temp.f[3] = 1;
        vec_fast_normalize(&blast, &velocity, &temp); vec_scale_to_length(&blast, &blast, 0.033333335f);
        vec_scale_to_length(&blast_normal, &temp, 1);
        if (state->sound != -1) {
            sound = g_sound_state + state->sound * 0x70;
            if (*(Moby **)(sound + 0x88) == missile && sound[0x74]) snd_stop_voice(state->sound);
        }
        state->sound = -1;
    } else if (CollLine(&prev_position, &missile->position, 0, ignore, &damage)) {
        CollisionResult *col = &g_collision_result;
        Moby *hit = col->hit;
        if (hit) {
            if (hit == ((Hero *)g_hero_state)->ptr[0x2290 / 4]) player_hit = 1;
            missile->hit = 2;
            qcopy(&missile->position, &col->position);
            FastVecSub(&contact_edge, &col->edgeStart, &col->edgeEnd);
            vec_scale_to_length(&contact_edge, &contact_edge, 1);
            vec_fast_normalize(&blast, &velocity, &col->normal); vec_scale_to_length(&blast, &blast, 0.033333335f);
            vec_scale_to_length(&blast_normal, &col->normal, 1);
            if (state->sound != -1) {
                sound = g_sound_state + state->sound * 0x70;
                if (*(Moby **)(sound + 0x88) == missile && sound[0x74]) snd_stop_voice(state->sound);
            }
            state->sound = -1;
        } else if (col->mesh > 0) {
            missile->hit = 1; qcopy(&missile->position, &col->position);
            FastVecSub(&contact_edge, &col->edgeStart, &col->edgeEnd);
            vec_scale_to_length(&contact_edge, &contact_edge, 1);
            vec_fast_normalize(&blast, &velocity, &col->normal); vec_scale_to_length(&blast, &blast, 0.033333335f);
            vec_scale_to_length(&blast_normal, &col->normal, 1);
            if (state->sound != -1) {
                sound = g_sound_state + state->sound * 0x70;
                if (*(Moby **)(sound + 0x88) == missile && sound[0x74]) snd_stop_voice(state->sound);
            }
            state->sound = -1;
        }
    } else if (!state->timer) { tether_release(missile, state); return; }
after_rebound:
    if (state->timer < 0xB7C && (g_pad_state[0x1A4 / 4] & 0x20)) {
        missile->hit = 1;
        if (state->sound != -1) {
            sound = g_sound_state + state->sound * 0x70;
            if (*(Moby **)(sound + 0x88) == missile && sound[0x74]) snd_stop_voice(state->sound);
        }
        state->sound = -1;
    }
    if (missile->hit) {
        if (!player_hit) {
            SpawnExplosionEffects(missile, &blast, 0, 0, 0, 10, 3, 16, 4, 2, 0, 1, 1, 20, 1, 1, -1, 0, 0x810001);
            hits = coll_process_hit(4, &missile->position, 16, missile, 0);
            temp.quad = missile->position.quad;
            moby_queue_knockback_for_nodes(missile, &temp, g_area_hit_targets, hits, 0, 0x830000, 3, 2,
                          (g_weapon_l00_table + g_item_slot_to_record[0xE])->power, 1, 1);
        }
        missile->flags |= 1; state->speed = 0.02f;
        state->input_x *= 0.01f;
        if (state->timer >= 0xB9B) state->timer = -100;
        else state->timer = -1;
        qcopy(&temp, &missile->position);
        for (i = 4; i >= 0; --i) {
            qcopy(&missile->position, &temp); vec_add_random_offset(missile->position.f, 1.5f); tether_spawn_impact_effects(missile, 1);
            qcopy(&missile->position, &temp);
        }
        velocity.f[0] = 0; missile->hit = 0;
    }
    if (state->attached) cam_follow_update_target_us2(state->attached, missile);
    if (!g_hero_locked_flag) return;
    cam_compute_view_direction(&missile->position, &missile->forward, 1);
    FastVecCross(&temp, &missile->right, &missile->forward); vec_scale_to_length(&missile->up, &temp, 1);
    FastVecCross(&missile->forward, &missile->up, &missile->right);
    missile->right.f[3] = missile->up.f[3] = missile->forward.f[3] = 0;
}
