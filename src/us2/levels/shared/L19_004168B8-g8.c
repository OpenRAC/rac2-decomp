#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern u8 *g_moby_l19_array __attribute__((sda));
extern u8 *g_linked_object_table;
extern int g_current_map_index[] MACRO_ADDR;
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern u8 g_moby_group_flags[], g_moby_nibble_table[];
typedef struct { u8 pad[0x464]; u8 slot[0]; } SlotTable;
extern SlotTable g_trigger_active_table;
#define D_L19_0021EE94 D_L19_0021EA30.slot
extern int g_hero_l19_attached_flag NOT_SDA;
typedef struct {
    u8 pad00[0x80]; Vector position, rotation;
    u8 padA0[0x60]; Vector relative;
    u8 pad110[0x22c]; u8 *platform;
    u8 pad340[0xe]; short platformMode;
    u8 pad350[0x228]; int alternateActive;
    u8 pad57C[0xc]; u8 *alternatePlatform;
    u8 pad58C[0x68c]; u8 *actor;
    u8 padC1C[0x1674]; u8 *currentActor;
    u8 pad2294[0x20]; u8 cameraMode;
} PlatformPlayer;
extern PlatformPlayer g_hero_state;
#define D_0018C0B0 D_00189E20.currentActor
#define D_0018C0D4 D_00189E20.cameraMode
#define D_0018AA38 D_00189E20.actor
#define D_0018A16E D_00189E20.platformMode
#define D_0018A15C D_00189E20.platform
#define D_0018A398 D_00189E20.alternateActive
#define D_0018A3A8 D_00189E20.alternatePlatform
#define D_00189EA0 D_00189E20.position
#define D_00189EB0 D_00189E20.rotation
#define D_00189F20 D_00189E20.relative
#define D_00189F28 D_00189E20.relative.f[2]
extern float g_platform_sound_gain __attribute__((sda));
extern float g_platform_vec_a_x __attribute__((sda));
extern float g_platform_vec_a_y __attribute__((sda));
extern float g_platform_vec_a_z __attribute__((sda));
extern float g_platform_vec_b_x __attribute__((sda));
extern float g_platform_vec_b_y __attribute__((sda));
extern float g_platform_vec_b_z __attribute__((sda));
extern float math_random_angle(void);
extern void moby_set_state(void *, u8, int);
extern int flag_is_third_pending_set(void *);
extern void moby_mark_table_entry_flagged(unsigned int);
extern void *part_find_owned_effect_slot(void *, u32, int);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern float math_move_angle_toward_target(float, float, float);
extern float math_approach_with_velocity(float *, float *, int, float, float, float, float);
extern void moby_scale_owner_words_by_angles(float *, float *, float *, float, float, float);
extern void mat_transform_offset_two_matrices(void *, void *, void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void hero_detach_from_object_us2(int);
extern void level_capture_checkpoint_state(void *, void *);
extern void part_spawn_masked_debris(char *, int, void *, float, float, float, float, u8);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int,
    float, float, float, float, int, float, int, int, int, u8, int);
#define F(p, o) (*(float *)((u8 *)(p) + (o)))
#define ADVANCE_GATE() { \
    unsigned int gate_id = actor->packedGate; \
    if (gate_id & 1) { \
        u8 *gate = D_0019B4A8 + (((int)(gate_id << 16) >> 17) + D_001A79F0_gp * 0x400); \
        if (((*gate >> 4) & 7) != 7) *gate += 0x10; \
    } else { \
        u8 *gate = D_0019B4A8 + (((int)(gate_id << 16) >> 17) + D_001A79F0_gp * 0x400); \
        if ((*gate & 7) != 7) ++*gate; \
    } \
}
typedef struct {
    u8 pad00[0x20], transformDelta[0x3c];
    int flags;
    Vector startPosition, startRotation, tilt, tiltVelocity;
    int destination;
    float duration, progress;
    int trigger;
    u8 playerOnly, noExplosion, carryingPlayer, gate;
    int linkedActor;
    float velocity, height, yaw, yawVelocity, phase;
    u8 padCC[4];
    int notify;
} PlatformState;
typedef struct {
    u8 pad00[0x10]; Vector position;
    u8 state, pad21[0x10], draw, pad32[2];
    unsigned short flags;
    u8 pad36[0x32]; PlatformState *vars;
    u8 pad6C[0x2c]; int attached;
    u8 pad9C[0xc], distance, padA9[7], gateId, padB1;
    unsigned short packedGate;
    u8 padB4[8], triggered, padBD[3];
    Vector forward, right, up, rotation;
} PlatformActor;

void UpdateTriggeredTiltingPlatform_us2(PlatformActor *actor)
{
    PlatformState *state = actor->vars;
    Vector old_position, old_rotation, temp, origin, point, camera_out;
    u8 *saved_player;
    unsigned int saved_mode;
    unsigned int id;
    int index;
    float progress, blend, height, forward_dot, target_x, old_z, gain, right_dot, target_y;
    qcopy(&old_position, &actor->position);
    qcopy(&old_rotation, &actor->rotation);
    switch (actor->state) {
    case 0:
        qcopy(&state->tilt, &actor->rotation);
        qzero_nc(&state->tiltVelocity);
        state->phase = math_random_angle();
        if (state->destination == -1) {
            actor->flags |= 2;
            return;
        }
        state->progress = 0.0f;
        state->flags |= 1;
        qcopy(&state->startPosition, &actor->position);
        qcopy(&state->startRotation, &actor->rotation);
        if (state->notify && actor->gateId != 0xff &&
                (g_moby_group_flags[actor->gateId + D_001A79F0_gp * 16] & 0x80))
            goto active;
        if (D_L19_0021EE94[state->trigger])
            goto active;
        if (!state->gate) goto inactive_actor;
        id = actor->packedGate;
        if (D_L19_0021EE94[(short)id]) goto active;
        index = g_moby_nibble_table[((int)(id << 16) >> 17) + g_current_map_index[0] * 0x400];
        if (id & 1) {
            if ((index >> 4) & 7) goto active;
            goto inactive_actor;
        } else if (!(index & 7)) goto inactive_actor;
active:
        if (actor->gateId != 0xff && state->gate)
            ADVANCE_GATE();
        qcopy_nc(&actor->position, g_linked_object_table + state->destination * 0x80 + 0x30);
        qcopy_nc(&actor->rotation, g_linked_object_table + state->destination * 0x80 + 0x70);
        moby_set_state(actor, 4, -1);
        goto initialized;
inactive_actor:
        moby_set_state(actor, 1, -1);
initialized:
        {
            float initial_height = actor->position.f[2];
            state->velocity = 0.0f;
            state->height = initial_height;
        }
        break;
    case 1:
        if (actor->triggered || flag_is_third_pending_set(actor) || state->trigger == -1 ||
                (g_moby_l19_array[state->trigger * 0x100 + 0x20] == 0xfe) ||
                (g_moby_l19_array[state->trigger * 0x100 + 0x20] == 0xfd)) {
            if (state->linkedActor != -1)
                g_moby_l19_array[state->linkedActor * 0x100 + 0xbc] = 1;
            if (actor->gateId != 0xff && state->gate) {
                ADVANCE_GATE();
                if (state->notify) moby_mark_table_entry_flagged(actor->gateId);
            }
            moby_set_state(actor, 2, -1);
        }
        if (!state->noExplosion && part_find_owned_effect_slot(actor, 0x40000, 0)) {
            if (state->linkedActor != -1)
                g_moby_l19_array[state->linkedActor * 0x100 + 0xbc] = 1;
            FastVecAdd(&temp, &actor->right, &actor->up);
            vec_scale_to_length(&temp, &temp, 1.0f / 12.0f);
            FastVecAdd(&origin, &actor->position, &actor->up);
            SpawnExplosionEffects(actor, &temp, &origin, 0.0f, 0.0f, 10, 3, 16,
                4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
            part_spawn_masked_debris((char *)actor, 31, &temp, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            {
                unsigned int event_id = actor->gateId;
                actor->draw = 0;
                actor->flags |= 1;
                actor->attached = 0;
                if (event_id != 0xff && state->gate) {
                    ADVANCE_GATE();
                    if (state->notify) moby_mark_table_entry_flagged(actor->gateId);
                }
            }
            moby_set_state(actor, 2, -1);
        }
        actor->distance = 0xff;
        break;
    case 2:
        progress = state->progress + 1.0f / state->duration;
        state->progress = progress;
        if (progress > 1.0f)
            state->progress = 1.0f;
        blend = (1.0f - math_fast_sin_or_cos_a(state->progress * 3.1415927f)) * 0.5f;
        FastVecSub(&temp, g_linked_object_table + state->destination * 0x80 + 0x30, &state->startPosition);
        FastVecScale(&temp, &temp, blend);
        old_z = actor->position.f[2];
        FastVecAdd(&actor->position, &state->startPosition, &temp);
        state->height = actor->position.f[2];
        actor->position.f[2] = old_z;
        actor->rotation.f[2] = math_move_angle_toward_target(state->startRotation.f[2], F(g_linked_object_table + state->destination * 0x80, 0x78), blend);
        actor->rotation.f[1] = math_move_angle_toward_target(state->startRotation.f[1], F(g_linked_object_table + state->destination * 0x80, 0x74), blend);
        actor->rotation.f[0] = math_move_angle_toward_target(state->startRotation.f[0], F(g_linked_object_table + state->destination * 0x80, 0x70), blend);
        if (state->progress >= 1.0f) {
            moby_set_state(actor, 3, -1);
            goto finish_transition;
        }
        break;
    case 3:
finish_transition:
        if (state->linkedActor == -1 || !g_moby_l19_array[state->linkedActor * 0x100 + 0xbc]) {
            if (state->playerOnly) {
                g_hero_l19_attached_flag = 0;
                hero_detach_from_object_us2(0);
            }
            if (state->notify) {
                if (g_screen_mode_flag) {
                    saved_mode = g_screen_mode_flag;
                    saved_player = g_hero_moby;
                    g_screen_mode_flag = 0;
                    g_hero_moby = g_platform_hero_actor;
                    level_capture_checkpoint_state(g_platform_hero_actor + 0x10, g_platform_hero_actor + 0xf0);
                    g_screen_mode_flag = saved_mode;
                    g_hero_moby = saved_player;
                } else
                    level_capture_checkpoint_state(&g_hero_position, &g_hero_turn_rotation);
            }
            moby_set_state(actor, 4, -1);
        }
        break;
    }
    height = state->height;
    if (actor->state != 2) {
        height += math_fast_sin_or_cos_b(state->phase) * 0.1f;
        state->phase = FastAddRotations(state->phase, 0.01745329611003399f);
    }
    if (state->carryingPlayer)
        height -= 0.2f;
    state->velocity = (state->velocity + (height - actor->position.f[2]) * 0.005f) * 0.98f;
    actor->position.f[2] += state->velocity;
    if (actor->state) {
        if ((!g_platform_mode && g_platform_actor_ref == (u8 *)actor) || (g_alternate_active && g_alternate_platform == (u8 *)actor)) {
            if (!state->carryingPlayer)
                state->velocity -= 1.0f / 60.0f;
            state->carryingPlayer = 1;
            FastVecSub(&temp, &g_hero_position, &actor->position);
            forward_dot = FastVecDot(&temp, &actor->forward);
            right_dot = FastVecDot(&temp, &actor->right);
            gain = g_platform_sound_gain;
            origin.q = state->tilt.q;
            point.q = actor->position.q;
            target_y = gain * forward_dot;
            target_x = -gain;
            target_x *= right_dot;
            math_approach_with_velocity((float *)(&state->tilt), (float *)(&state->tiltVelocity), 0, target_x,
                g_platform_vec_a_x, g_platform_vec_a_y, g_platform_vec_a_z);
            math_approach_with_velocity((float *)(&state->tilt.f[1]), (float *)(&state->tiltVelocity.f[1]), 0, target_y,
                g_platform_vec_a_x, g_platform_vec_a_y, g_platform_vec_a_z);
            mat_transform_offset_two_matrices(&g_hero_position, &camera_out, &actor->position, &origin, &state->tilt);
            FastVecSub(&g_hero_vector_block, &camera_out, &g_hero_position);
            g_platform_relative_z += actor->position.f[2] - point.f[2];
        } else {
            state->carryingPlayer = 0;
            math_approach_with_velocity((float *)(&state->tilt), (float *)(&state->tiltVelocity), 0, 0.0f,
                g_platform_vec_b_x, g_platform_vec_b_y, g_platform_vec_b_z);
            math_approach_with_velocity((float *)(&state->tilt.f[1]), (float *)(&state->tiltVelocity.f[1]), 0, 0.0f,
                g_platform_vec_b_x, g_platform_vec_b_y, g_platform_vec_b_z);
        }
        moby_scale_owner_words_by_angles((float *)actor, (float *)(&state->yaw), (float *)(&state->yawVelocity),
            0.02007128857076168f, 0.007272206246852875f, 0.009017535485327244f);
        actor->rotation.f[0] = FastAddRotations(state->tilt.f[0], actor->rotation.f[0]);
        actor->rotation.f[1] = FastAddRotations(state->tilt.f[1], actor->rotation.f[1]);
    }
    FastVecSub(&temp, &actor->position, &old_position);
    mat_combine_and_store(&state->transformDelta, &temp, &old_rotation, &actor->rotation);
}
