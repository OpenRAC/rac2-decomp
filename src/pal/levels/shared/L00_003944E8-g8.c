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
    s16 objectClass;
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
    float inputX, inputY;
    int unknown20;
    Moby *leftFin, *rightFin;
    int sound;
    int unknown30[5];
    float hover;
    float targetSpeed;
    int camera;
};
typedef struct {
    Vector direction;
    Moby *owner;
    u32 flags;
    u8 kind, response;
    u16 objectClass;
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
extern void level_start_timed_object_once_pal(void);
extern int ForceClaimNotice(int, void *, int);
extern void tether_release(Moby *, TetherState *), level_restore_lighting(Moby *, int), func_PAL_L00_003944E8(Moby *, TetherState *);
extern int func_PAL_L00_0042D540(Moby *, Moby *);
extern int FloatToInt(float), snd_set_voice_pitch_bend(int, int);
extern float math_fabs(float), fast_subtract_rotations(float, float), coll_probe_ground_height_below(void *, int, float), ApproachValue(float *, float, float), mat_fast_helper_a(float, float);
extern void math_build_axis_angle_quat(void *, void *, float), vec_rotate_by_quaternion(void *, void *, void *), part_steer_effect_direction(int, void *, void *), part_queue_ground_shadow(Moby *, float);
extern void FastVecScale(void *, void *, float), vec_build_spherical_offset(float *, float, float, float), FastVecAdd(void *, void *, void *), vec_transform_or_copy(void *, void *);
extern void build_axis_rotation_quaternion(void *, int, float), vec_fast_normalize_helper(void *, void *, float);
extern int moby_find_accepting_table_object(Vector *), CollLine(void *, void *, int, Moby *, DamageRecord *);
extern void FastVecSub(void *, void *, void *), vec_scale_to_length(void *, void *, float), vec_fast_normalize(void *, void *, void *), snd_stop_voice(int);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern int coll_process_hit(float, void *, int, Moby *, int);
extern void moby_queue_knockback_for_nodes(void *, Vector *, int *, int, int, int, int, int, float, float, float);
extern void vec_add_random_offset(float *, float), func_PAL_L00_00394630(Moby *, int), cam_compute_view_direction(Vector *, Vector *, int), FastVecCross(void *, void *, void *);
extern float PH_DF3;

/* Updates the flying tether's steering, sweep collision, impact burst and attached pieces. */
void func_PAL_L00_00394A18(Moby *actor) {
    Vector previous, blast, blastNormal, velocity, contactEdge, scratch;
    DamageRecord damage;
    TetherState *state = actor->state;
    Moby *mount, *ignore;
    u8 *sound;
    float desiredSpeed, angle, turn, height, roll, yaw;
    Vector *fin;
    int timer, playerHit = 0, i, hits;
    blast.quad = 0; blastNormal.quad = 0;
    blast.f[2] = 0.16000001f; blastNormal.f[2] = 1;
    g_visibomb_phase_flag = 1; g_visibomb_missile_active = 1;
    level_start_timed_object_once_pal(); g_cinematic_phase_flag = 1; ForceClaimNotice(6, 0, 1);
    timer = --state->timer;
    if (timer < -82 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x16 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x39 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x6F ||
        ((Hero *)g_hero_state)->i[0x229C / 4] == 2 || ((Hero *)g_hero_state)->i[0x229C / 4] == 4 || ((Hero *)g_hero_state)->i[0x229C / 4] == 3 || ((Hero *)g_hero_state)->i[0x229C / 4] > 12 ||
        ((Hero *)g_hero_state)->i[0x229C / 4] == 7 || ((Hero *)g_hero_state)->i[0x229C / 4] == 10 || ((Hero *)g_hero_state)->i[0x229C / 4] == 16 || ((Hero *)g_hero_state)->i[0x229C / 4] == 5 ||
        ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x62 || !((Hero *)g_hero_state)->i[0x340 / 4] ||
        ((mount = ((Hero *)g_hero_state)->ptr[0x33C / 4]) && (mount->objectClass == 0x13E || mount->objectClass == 0x46F)) || g_pad_device_idle_flag) {
        tether_release(actor, state); return;
    }
    if (timer < 0) {
        if (g_active_tether_object) { tether_release(actor, state); ((Hero *)g_hero_state)->h[0x1E0 / 2] = 10; return; }
        if (state->attached) func_PAL_L00_0042D540(state->attached, actor);
        level_restore_lighting(actor, 0); func_PAL_L00_003944E8(actor, state); return;
    }
    desiredSpeed = g_visibomb_min_speed * 0.020000001f;
    if (g_pad_state[0x1A0 / 4] & 0x40) desiredSpeed = g_visibomb_max_speed * 0.020000001f;
    state->targetSpeed += (desiredSpeed - state->targetSpeed) * g_visibomb_target_speed_blend;
    state->speed += (state->targetSpeed - state->speed) * g_visibomb_speed_blend;
    if (state->speed > g_visibomb_max_speed * 0.020000001f) state->speed = g_visibomb_max_speed * 0.020000001f;
    snd_set_voice_pitch_bend(state->sound, FloatToInt((state->targetSpeed - (g_visibomb_min_speed * 0.020000001f) /
                      (g_visibomb_max_speed * 0.020000001f - g_visibomb_min_speed * 0.020000001f)) * g_visibomb_pitch_scale));
    if ((u32)(state->timer - 1) < 0x9BF) {
        float stickX = ((Hero *)g_hero_state)->f[0x1FB0 / 4], stickY = ((Hero *)g_hero_state)->f[0x1FB4 / 4];
        state->inputX += (stickX - state->inputX) * 0.120000005f;
        state->inputY += (stickY - state->inputY) * 0.120000005f;
        if (g_hero_locked_flag) {
            actor->pitch = (state->inputX - actor->pitch) * 0.072000004f;
            actor->yaw = state->inputY * 0.014726217f;
            actor->roll = state->inputX * 0.014726217f;
            if (math_fabs(actor->roll) > 0.00001f) {
                math_build_axis_angle_quat(&scratch, &actor->forward, -actor->roll);
                vec_rotate_by_quaternion(&actor->right, &actor->right, &scratch); vec_rotate_by_quaternion(&actor->up, &actor->up, &scratch);
            }
            if (math_fabs(actor->yaw) > 0.00001f) {
                math_build_axis_angle_quat(&scratch, &actor->up, -actor->yaw);
                vec_rotate_by_quaternion(&actor->right, &actor->right, &scratch); vec_rotate_by_quaternion(&actor->forward, &actor->forward, &scratch);
            }
            if (math_fabs(actor->pitch) > 0.00001f) {
                math_build_axis_angle_quat(&scratch, &actor->right, actor->pitch);
                vec_rotate_by_quaternion(&actor->up, &actor->up, &scratch); vec_rotate_by_quaternion(&actor->forward, &actor->forward, &scratch);
            }
            part_steer_effect_direction(state->camera, &actor->right, 0);
        } else {
            actor->pitch += (state->inputX - actor->pitch) * 0.072000004f;
            angle = fast_subtract_rotations(actor->yaw, state->inputY * 0.014726217f);
            actor->yaw = angle;
            if (angle >= 1.5707964f) actor->yaw = 1.5697963f;
            else if (angle <= -1.5707964f) actor->yaw = -1.5697963f;
            actor->roll = fast_subtract_rotations(actor->roll, state->inputX * 0.014726217f);
            part_queue_ground_shadow(actor, 0.2f);
        }
    }
    if (g_hero_locked_flag) FastVecScale(&velocity, &actor->right, state->speed);
    else vec_build_spherical_offset(velocity.f, state->speed, actor->roll, -actor->yaw);
    qcopy(&previous, &actor->position);
    FastVecAdd(&actor->position, &actor->position, velocity.f); vec_transform_or_copy(&actor->position, &actor->position);
    if (state->timer >= 0x993) {
        height = coll_probe_ground_height_below(&actor->position, 0, 0.5f) + state->hover;
        if (actor->position.f[2] < height && (!g_collision_result.hit ||
            (g_collision_result.hit->owner && g_collision_result.hit->owner->kind == 5))) {
            turn = mat_fast_helper_a(state->speed, ApproachValue(&actor->position.f[2], height, 0.120000005f));
            if (turn > 0.031415932f) turn = 0.031415932f;
            actor->yaw -= turn;
        }
    }
    if (actor->position.f[0] < 4.5f || actor->position.f[0] > 1018.5f || actor->position.f[1] < 4.5f ||
        actor->position.f[1] > 1018.5f || actor->position.f[2] < 4.5f || actor->position.f[2] > 1018.5f) {
        tether_release(actor, state); return;
    }
    func_PAL_L00_003944E8(actor, state);
    build_axis_rotation_quaternion(&state->leftFin->position, 1,
                  -(state->inputY * 0.5f + math_fabs(state->inputX * 0.33333334f) + (state->inputX - actor->pitch) * 1.1f) * 0.7f);
    fin = &state->rightFin->position;
    roll = (state->inputY * 0.5f + math_fabs(state->inputX * 0.33333334f));
    build_axis_rotation_quaternion(fin, 1, ((state->inputX - actor->pitch) * 1.1f - roll) * 0.7f);
    damage.flags = 0x830000; damage.direction.quad = velocity.quad; damage.owner = actor;
    damage.mode = 1; damage.power = (g_weapon_l00_table + g_item_slot_to_record[0xE])->power;
    vec_fast_normalize_helper(&damage.direction, &damage.direction, 1);
    damage.kind = 3; damage.direction.f[3] = 5627.925f;
    damage.objectClass = actor->objectClass; damage.direction.f[2] = 1; damage.response = 2;
    ignore = actor;
    if (state->timer > 0x99C) ignore = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
    if (moby_find_accepting_table_object(&actor->position)) {
        actor->hit = 2;
        qcopy(&contactEdge, &g_cam_follow_matrix);
        scratch.quad = 0; scratch.f[2] = 1; scratch.f[3] = 1;
        vec_fast_normalize(&blast, &velocity, &scratch); vec_scale_to_length(&blast, &blast, 0.040000003f);
        vec_scale_to_length(&blastNormal, &scratch, 1);
        if (state->sound != -1) {
            sound = g_sound_state + state->sound * 0x70;
            if (*(Moby **)(sound + 0x88) == actor && sound[0x74]) snd_stop_voice(state->sound);
        }
        state->sound = -1;
    } else if (CollLine(&previous, &actor->position, 0, ignore, &damage)) {
        CollisionResult *col = &g_collision_result;
        Moby *hit = col->hit;
        if (hit) {
            if (hit == ((Hero *)g_hero_state)->ptr[0x2290 / 4]) playerHit = 1;
            actor->hit = 2;
            qcopy(&actor->position, &col->position);
            FastVecSub(&contactEdge, &col->edgeStart, &col->edgeEnd);
            vec_scale_to_length(&contactEdge, &contactEdge, 1);
            vec_fast_normalize(&blast, &velocity, &col->normal); vec_scale_to_length(&blast, &blast, 0.040000003f);
            vec_scale_to_length(&blastNormal, &col->normal, 1);
            if (state->sound != -1) {
                sound = g_sound_state + state->sound * 0x70;
                if (*(Moby **)(sound + 0x88) == actor && sound[0x74]) snd_stop_voice(state->sound);
            }
            state->sound = -1;
        } else if (col->mesh > 0) {
            actor->hit = 1; qcopy(&actor->position, &col->position);
            FastVecSub(&contactEdge, &col->edgeStart, &col->edgeEnd);
            vec_scale_to_length(&contactEdge, &contactEdge, 1);
            vec_fast_normalize(&blast, &velocity, &col->normal); vec_scale_to_length(&blast, &blast, 0.040000003f);
            vec_scale_to_length(&blastNormal, &col->normal, 1);
            if (state->sound != -1) {
                sound = g_sound_state + state->sound * 0x70;
                if (*(Moby **)(sound + 0x88) == actor && sound[0x74]) snd_stop_voice(state->sound);
            }
            state->sound = -1;
        }
    } else if (!state->timer) { tether_release(actor, state); return; }
after_rebound:
    if (state->timer < 0x992 && (g_pad_state[0x1A4 / 4] & 0x20)) {
        actor->hit = 1;
        if (state->sound != -1) {
            sound = g_sound_state + state->sound * 0x70;
            if (*(Moby **)(sound + 0x88) == actor && sound[0x74]) snd_stop_voice(state->sound);
        }
        state->sound = -1;
    }
    if (actor->hit) {
        if (!playerHit) {
            SpawnExplosionEffects_pal(actor, &blast, 0, 0, 0, 10, 3, 16, 4, 2, 0, 1, 1, 20, 1, 1, -1, 0, 0x810001);
            hits = coll_process_hit(4, &actor->position, 16, actor, 0);
            scratch.quad = actor->position.quad;
            moby_queue_knockback_for_nodes(actor, &scratch, g_area_hit_targets, hits, 0, 0x830000, 3, 2,
                          (g_weapon_l00_table + g_item_slot_to_record[0xE])->power, 1, 1);
        }
        actor->flags |= 1; state->speed = 0.024f;
        state->inputX *= 0.01f;
        if (state->timer >= 0x9AC) state->timer = -83;
        else state->timer = -1;
        qcopy(&scratch, &actor->position);
        for (i = 4; i >= 0; --i) {
            qcopy(&actor->position, &scratch); vec_add_random_offset(actor->position.f, 1.5f); func_PAL_L00_00394630(actor, 1);
            qcopy(&actor->position, &scratch);
        }
        velocity.f[0] = 0; actor->hit = 0;
    }
    if (state->attached) func_PAL_L00_0042D540(state->attached, actor);
    if (!g_hero_locked_flag) return;
    cam_compute_view_direction(&actor->position, &actor->forward, 1);
    FastVecCross(&scratch, &actor->right, &actor->forward); vec_scale_to_length(&actor->up, &scratch, 1);
    FastVecCross(&actor->forward, &actor->up, &actor->right);
    actor->right.f[3] = actor->up.f[3] = actor->forward.f[3] = 0;
}
