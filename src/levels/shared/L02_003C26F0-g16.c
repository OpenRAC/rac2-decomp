#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad bits; float f[4]; } Vector;
typedef struct { Vector row[4]; } Matrix;
typedef void (*DrawCallback)(void *);

typedef struct {
    int record, unknown04, delayFrames, unknown0C;
    int linked[2], disabled, restoreMode;
    char *gates[20];
    char *platforms[20];
    char *rotators[20];
    int gateCount, platformCount, rotatorCount, completed;
    u8 *decoration;
    int unknown124;
    float angles[2];
    int retryTimer;
    float savedBrightness, savedAlpha;
    int savedCamera, selector, selectorMode, previousSelector;
} ChallengeState;

typedef struct {
    u8 unknown00[0x80];
    Vector position;
    float unknown90[2], heading;
    u8 unknown9C[0x100 - 0x9C];
    Vector velocity;
    u8 unknown110[0x222 - 0x110];
    u16 controlMode;
    u8 unknown224[0xC28 - 0x224];
    u32 flags;
    u8 unknownC2C[0x1248 - 0xC2C];
    int camera;
    u8 unknown124C[0x2290 - 0x124C];
    u8 *object;
    u8 unknown2294[0x22C8 - 0x2294];
    int cameraRequest;
} PlayerView;

typedef struct {
    u8 unknown00[0x1A0];
    union { u64 all; struct { u32 low, high; } word; } buttons;
} InputView;

extern PlayerView g_hero_state;
extern InputView g_pad_state;
extern u8 D_0019B4A8[];
extern int g_current_map_index;
extern u8 D_001A7B1E;
extern s16 g_music_state[];
extern u8 g_item_slot_to_record[];
typedef struct { u8 unknown00[0x14]; int sound; u8 unknown18[0xE0 - 0x18]; } SlotInfo;
extern SlotInfo D_L02_00264A70[];
typedef struct { u8 unknown[0x464]; u8 completed[0]; } ChallengeProgress;
extern ChallengeProgress D_L02_0021F4F0;
extern int D_L02_002004A4 __attribute__((nosda));
extern int D_L02_001A8F00;
extern char *g_moby_l02_pool;
extern char *D_L02_001B368C;
extern u16 *g_entity_group_lists[];
extern Vector D_L02_001AFD20 __attribute__((sda));
extern Vector D_L02_001AFD30 __attribute__((sda));
extern float D_L02_001AFD40 __attribute__((sda));
extern float D_L02_001C0968 __attribute__((nosda));
typedef struct { u8 unknown00[0x380]; Matrix transform; } ChallengeGlobals;
extern ChallengeGlobals D_L02_001C8280;
typedef struct { Vector from, to; u8 unknown20[0x30]; char *view; } CameraPath;
extern CameraPath g_camera_l02_position;
extern float D_L02_001B308C, D_L02_001B3090;
extern char D_L02_002A4ED0[], D_L02_002A4F20[], D_L02_002A4F70[];
extern char D_L02_001AFD48[], D_L02_001AFD80[], D_L02_001AFDB8[], D_L02_001AFDF0[];

extern void STUB_printf(const char *, ...);
extern int CollLine(void *, void *, int, void *, int);
extern float math_fabs(float);
extern void FastVecAdd(void *, const void *, const void *);
extern void FastVecSub(void *, const void *, const void *);
extern float fast_vec_dist(const void *, const void *);
extern void transform_vector(void *, const void *, const void *);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern void euler_rotation_basis(void *, const void *);
extern float FastAddRotations(float, float), FastDiffRots(float, float);
extern int load_is_class_cached(int);
extern char *CreateMoby(int);
extern void moby_mark_spawned(void *);
extern void moby_transform_joint_point(char *, int, char *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void moby_mark_table_entry_flagged(unsigned int);
extern void gfx_pack_render_command_fields(u64 *, int, int, int, int);
extern void moby_set_state(u8 *, int, int);
extern float math_random_angle(void);
extern int moby_count_group_not_in_state(int, int);
extern void StepAngleTowardTarget(float *, int, float, float);
extern void vec_clamp_length(float *, float);
extern int request_begin_slot(int, int, int, int, u8 *);
extern int request_end_slot(int, int);
extern char *part_spawn_drifting(void *, int, u32, float, float);
extern int PlayMobySound(int, int, char *);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int,
                         float, float, int, int, int, void *);
extern void cam_set_mode_state(int);
extern int hero_get_target_state_kind(void);
extern void gfx_add_draw_callback_first(DrawCallback, void *);
extern void moby_set_flag_bit(u8 *, int);
extern int PadPressedWithin(int, int, int *);
extern void cam_reset_entry(int);
extern void hero_set_move_state_by_speed(void);
extern int moby_is_hero_inside_trigger_boxes(char *);
extern int gate_move_along_path(char *);
extern void moby_show_angles_debug(char *);
extern void moby_flip_element_turn_directions(void *);


extern void LoadClassIntoFreeCacheSlot(int);
extern int ForceClaimNotice(int, int, int);
extern void object_copy_vector_to_selected(const void *), cam_set_state_rotation(const void *);
extern void SetCamera5Pose(const void *, const void *, int, int, int);
extern int hero_l00_set_action(int, int);
extern void set_hero_animation(int, int, float);
extern void script_queue_keyed_request(int, int);
extern void AdvancePathFollower(char *, int);
extern void menu_draw_challenge(void *);
extern void puzzle_reset_linked_part_group(char *);
extern void part_l02_spawn_spinning_pairs(void *, int);
extern void part_update_pulsing_glow_tint(char *), spark_emitter_update(char *);
extern void PulseGroupMobyColors(char *, u32, u32);
extern void SpawnOpposedParticles(void *, int, u32, int, u32);

/* Update for the moby class 2198 challenge controller. It finds the gates, platforms and rotators of its group, runs the camera flyover and the player challenge, then rewards the player when all gates are done. */
void challenge_controller_update(u8 *object)
{
    ChallengeState *state = *(ChallengeState **)(object + 0x68);
    Vector position, target, rotation;
    Matrix transform;
    u32 status;
    char *record;

    switch ((u8)object[0x20]) {
    case 0: {
        char *actor;
        char *records;
        u16 *list;
        u16 id;
        int i;
        int status;
        object[0x30] = 0x40;
        if (state->disabled != 0) {
            *(int *)(object + 0x98) = 0;
            *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xEFFF;
        } else {
            for (i = 0; i < 2; i++)
                state->angles[i] = math_random_angle();
            moby_transform_joint_to_world(object, 1, (char *)&position);
            qcopy(&target, &position);
            target.f[2] += 1.0f;
            qcopy(&rotation, &position);
            rotation.f[2] -= 1.0f;
            if (CollLine(&target, &rotation, 2, object, 0))
                *(float *)(object + 0x18) += (D_L02_001C0968 - position.f[2]) + D_L02_001AFD40;
        }
        state->retryTimer = 60;
        state->gateCount = 0;
        state->platformCount = 0;
        state->rotatorCount = 0;
        state->completed = 0;
        state->decoration = 0;
        records = D_L02_001B368C;
        *(float *)(records + state->record * 0x80 + 0x38) += 2.0f;
        qcopy(&D_L02_001C8280.transform.row[1], records + state->record * 0x80 + 0x30);
        qcopy(&D_L02_001C8280.transform.row[0], &D_L02_001AFD20);
        qzero_nc(&D_L02_001C8280.transform.row[3]);
        qzero_nc(&D_L02_001C8280.transform.row[2]);
        D_L02_001C8280.transform.row[1].f[3] = 0.0f;
        if (moby_count_group_not_in_state((u8)object[0x21], -1) >= 2) {
            list = g_entity_group_lists[(u8)object[0x21]];
            do {
                actor = g_moby_l02_pool + (*list & 0x7FFF) * 0x100;
                if (*(short *)(actor + 0xAA) != 0x896 /* moby class 2198 */)
                    gfx_pack_render_command_fields((u64 *)actor, 0x505010, 14, 14, 14);
                if (*(short *)(actor + 0xAA) == 0xA24 /* moby class 2596 */ && state->gateCount < 20) {
                    state->gates[state->gateCount] = actor;
                    *(float *)(*(char **)(actor + 0x68) + 0x10) = (float)state->delayFrames * 0.016666668f;
                    *(u16 *)(actor + 0x34) |= 0x41;
                    state->gateCount++;
                }
                if (*(short *)(actor + 0xAA) == 0xA55 /* moby class 2645 */ && state->platformCount < 20) {
                    state->platforms[state->platformCount] = actor;
                    *(float *)(*(char **)(actor + 0x68) + 4) = (float)state->delayFrames * 0.016666668f;
                    *(u16 *)(actor + 0x34) |= 0x41;
                    state->platformCount++;
                }
                if (*(short *)(actor + 0xAA) == 0x873 /* moby class 2163 */ && state->rotatorCount < 20) {
                    state->rotators[state->rotatorCount] = actor;
                    state->rotatorCount++;
                }
            } while (*(short *)list++ >= 0);
        }
        if (state->gateCount >= 20)
            STUB_printf(D_L02_002A4ED0, *(short *)(object + 0xB2));
        if (state->platformCount >= 20)
            STUB_printf(D_L02_002A4F20, *(short *)(object + 0xB2));
        if (state->rotatorCount >= 20)
            STUB_printf(D_L02_002A4F70, *(short *)(object + 0xB2));
        if (state->rotatorCount == 0)
            STUB_printf(D_L02_001AFD48, *(short *)(object + 0xB2));
        if (state->gateCount == 0)
            STUB_printf(D_L02_001AFD80, *(short *)(object + 0xB2));
        if (state->platformCount == 0)
            STUB_printf(D_L02_001AFDB8, *(short *)(object + 0xB2));
        id = *(u16 *)(object + 0xB2);
        if (D_L02_0021F4F0.completed[(short)id] != 0
            || (status = D_0019B4A8[((short)id >> 1) + g_current_map_index * 0x400],
                (id & 1) ? ((status >> 4) & 7) != 0 : (status & 7) != 0)) {
                moby_set_flag_bit((u8 *)object, 1);
            for (i = 0; i < 2; i++) {
                if (state->linked[i] != -1)
                    moby_set_flag_bit((u8 *)(g_moby_l02_pool + state->linked[i] * 0x100), 1);
            }
            moby_set_state((u8 *)object, 5, -1);
        } else {
            moby_set_state((u8 *)object, 1, -1);
        }
        object[0x30] = 0xFF;
        break;

    }
    case 1: {
        u8 *ids;
        SlotInfo *slots;
        int nearby = moby_is_hero_inside_trigger_boxes(object);
        int mode = D_L02_001A8F00;

        if (nearby && D_001A7B1E) {
            ForceClaimNotice(12, 0x27BD, 1);
            ids = g_item_slot_to_record;
            slots = D_L02_00264A70;
            if (load_is_class_cached(slots[ids[0x26]].sound) == 0) {
                LoadClassIntoFreeCacheSlot(slots[ids[0x26]].sound);
            } else if (g_pad_state.buttons.word.high & 0x10) {
                state->savedCamera = g_hero_state.camera;
                g_hero_state.cameraRequest = 0x26;
                moby_show_angles_debug(object);
                moby_set_state((u8 *)object, 4, -1);
            }
            mode = D_L02_001A8F00;
        }
        if (mode != 2)
            spark_emitter_update(object);
        break;

    }
    case 4: {
        int status;
        ForceClaimNotice(1, 0, 1);
        g_hero_state.controlMode = 3;
        status = hero_get_target_state_kind();
        if (status == 2 && g_hero_state.object[0x42] == g_hero_state.object[0x43]) {
            hero_l00_set_action(0x6F, 0);
            set_hero_animation(0x54, 0, 7.0f);
            position.f[0] = math_fast_sin_or_cos_a(*(float *)(object + 0xF8)) * 3.0f;
            position.f[1] = math_fast_sin_or_cos_b(*(float *)(object + 0xF8)) * 3.0f;
            position.f[2] = 0.0f;
            moby_transform_joint_to_world(object, 0, (char *)&target);
            FastVecAdd(&position, &target, &position);
            qcopy(&rotation, object + 0xF0);
            rotation.f[2] = FastAddRotations(*(float *)(object + 0xF8), 3.141593f);
            SetCamera5Pose(&g_camera_l02_position.from, &g_camera_l02_position.to, 3, 300, 0);
            object_copy_vector_to_selected(&position);
            cam_set_state_rotation(&rotation);
            PlayMobySound(0, 0, object);
            object[0x30] = 0xFF;
            moby_set_state((u8 *)object, 2, -1);
        } else {
            if (status != 0) {
                unsigned int timer = *(u16 *)(object + 0x96);
                unsigned int previous = timer++;
                *(u16 *)(object + 0x96) = timer;
                if (previous < 241)
                    break;
            }
            hero_set_move_state_by_speed();
            moby_set_state((u8 *)object, 1, -1);
        }
        break;

    }
    case 2: {
        float angle;
        ForceClaimNotice(1, 0, 1);
        moby_transform_joint_point(object, 1, (char *)&transform);
        transform_vector(&rotation, &D_L02_001AFD30, &transform);
        FastVecSub(&g_hero_state.velocity, &rotation, &g_hero_state.position);
        g_hero_state.velocity.f[2] = 0.0f;
        vec_clamp_length(g_hero_state.velocity.f, 0.025000002f);
        angle = FastAddRotations(*(float *)(object + 0xF8), 3.1415927f);
        StepAngleTowardTarget(&g_hero_state.heading, 0, angle, 0.017453296f);
        if (g_hero_state.flags & 2)
            set_hero_animation(0x55, 0, 7.0f);
        position.f[0] = math_fast_sin_or_cos_a(*(float *)(object + 0xF8)) * 3.0f;
        position.f[1] = math_fast_sin_or_cos_b(*(float *)(object + 0xF8)) * 3.0f;
        position.f[2] = 0.0f;
        moby_transform_joint_to_world(object, 0, (char *)&target);
        FastVecAdd(&position, &target, &position);
        g_hero_state.controlMode = 3;
        if (fast_vec_dist(&g_camera_l02_position.from, &position) <= 0.05f) {
            SetCamera5Pose(&g_camera_l02_position.from, &g_camera_l02_position.to, 2, 300, 0);
            object_copy_vector_to_selected(&target);
            cam_set_state_rotation(&g_camera_l02_position.to);
            PlayMobySound(0, 0, object);
            object[0x30] = 0xFF;
            moby_set_state((u8 *)object, 3, -1);
        }
        break;

    }
    case 3: {
        u8 *decoration;
        s16 *selectors;
        int status;
        ForceClaimNotice(1, 0, 1);
        g_hero_state.controlMode = 3;
        if (g_hero_state.flags & 2)
            set_hero_animation(0x55, 0, 0.0f);
        moby_transform_joint_to_world(object, 0, (char *)&position);
        if (fast_vec_dist(&g_camera_l02_position.from, &position) <= 0.5f) {
            record = D_L02_001B368C + state->record * 0x80;
            qcopy(&target, record + 0x30);
            qcopy(&rotation, record + 0x70);
            qcopy(&transform.row[0], &target);
            transform.row[0].f[2] += 30.0f;
            SetCamera5Pose(&transform, &rotation, 2, 480, 0);
            *(int *)(*(char **)(g_camera_l02_position.view + 0x70) + 0xE0) = 0x1C2;
            object_copy_vector_to_selected(&target);
            cam_set_state_rotation(&rotation);
            state->decoration = (u8 *)CreateMoby(0xB12 /* moby class 2834 */);
            if (state->decoration != 0) {
                state->decoration[0x30] = 0x80;
                *(u16 *)(state->decoration + 0x32) = 0x80;
                *(u16 *)(state->decoration + 0x34) &= 0xFFBE;
                decoration = state->decoration;
                qcopy(decoration + 0x10, record + 0x30);
                *(float *)(decoration + 0x18) += 15.0f;
                *(u16 *)(state->decoration + 0x34) &= 0xFF7F;
            } else {
                STUB_printf(D_L02_001AFDF0);
            }
            state->savedBrightness = D_L02_001B308C;
            state->savedAlpha = D_L02_001B3090;
            D_L02_001B308C = 100.0f;
            D_L02_001B3090 = 255.0f;
            state->previousSelector = g_music_state[0x1E] != -1 ? g_music_state[0x1E] : g_music_state[0x24];
            script_queue_keyed_request(state->selector, state->selectorMode);
            moby_set_state((u8 *)object, 9, -1);
        }
        break;

    }
    case 9: {
        char *actor;
        char *actors;
        u16 *list;
        ForceClaimNotice(1, 0, 1);
        hero_l00_set_action(0x6F, 1);
        record = D_L02_001B368C + state->record * 0x80;
        if (fast_vec_dist(&g_camera_l02_position.from, record + 0x30) <= 1.0f) {
            if (D_L02_001A8F00 == 7) {
                *(u16 *)(object + 0x34) &= 0xFF7F;
                if (moby_count_group_not_in_state((u8)object[0x21], -1) >= 2) {
                    list = g_entity_group_lists[(u8)object[0x21]];
                    actors = g_moby_l02_pool;
                    do {
                        actor = actors + (*list & 0x7FFF) * 0x100;
                        *(u16 *)(actor + 0x34) &= 0xFF7F;
                        if (*(short *)(actor + 0xAA) == 0x873 /* moby class 2163 */) {
                            *(u16 *)(*(char **)(*(char **)(actor + 0x68) + 0x1C) + 0x34) &= 0xFF7F;
                        }
                    } while (*(short *)list++ >= 0);
                }
                moby_set_state((u8 *)object, 6, -1);
            } else {
                if (request_begin_slot(7, 1, (int)object, 1, 0) == 0)
                    break;
                cam_set_mode_state(3);
                g_hero_state.cameraRequest = state->savedCamera;
                hero_l00_set_action(0, 1);
                g_hero_state.cameraRequest = state->savedCamera;
                if (state->restoreMode != -1)
                    cam_reset_entry(state->restoreMode);
                moby_set_state((u8 *)object, 1, -1);
            }
        }
        break;

    }
    case 6: {
        char *other;
        char *data;
        char *actor;
        char *vars;
        int i, j, k, m;
        int status;
        if (D_L02_001A8F00 == 7) {
            gfx_add_draw_callback_first(menu_draw_challenge, object);
            if (g_pad_state.buttons.all & 0xE000000000ULL) {
                moby_flip_element_turn_directions(object);
            } else if (g_pad_state.buttons.word.high & 0x10) {
                g_hero_state.cameraRequest = state->savedCamera;
                cam_set_mode_state(3);
                g_hero_state.cameraRequest = state->savedCamera;
                hero_l00_set_action(0, 1);
                object[0x30] = 0x40;
                if (state->decoration) {
                    moby_mark_spawned(state->decoration);
                    state->decoration = 0;
                }
                puzzle_reset_linked_part_group(object);
                for (i = 0; i < state->rotatorCount; i++) {
                    *(float *)(state->rotators[i] + 0xF8) = *(float *)(*(char **)(state->rotators[i] + 0x68) + 0x10);
                    euler_rotation_basis(state->rotators[i] + 0xC0, state->rotators[i] + 0xF0);
                }
                D_L02_001B308C = state->savedBrightness;
                D_L02_001B3090 = state->savedAlpha;
                request_end_slot(0, 0);
                if (state->restoreMode != -1)
                    cam_reset_entry(state->restoreMode);
                script_queue_keyed_request(state->previousSelector, state->selectorMode);
                moby_set_state((u8 *)object, 1, -1);
            } else if (D_L02_002004A4 && PadPressedWithin(1, 60, 0)) {
                if (PadPressedWithin(2, 60, 0)) {
                    if (state->platformCount > 0)
                        snd_play_from_class_bank(5, 0, state->platforms[0], 0x896 /* moby class 2198 */);
                    moby_set_state((u8 *)object, 8, -1);
                }
            }
            for (j = 0; j < state->platformCount; j++) {
                AdvancePathFollower(state->platforms[j], 0);
                position.bits = *(Quad *)(state->platforms[j] + 0x10);
                SpawnOpposedParticles(&position, 6, 0x88802020, 4, 0x7F6F6FFF);
            }
            for (k = 0; k < state->gateCount; k++) {
                status = gate_move_along_path(state->gates[k]);
                switch (status) {
                case 0:
                    position.bits = *(Quad *)(state->gates[k] + 0x10);
                    SpawnOpposedParticles(&position, 6, 0x88802020, 4, 0x7F6F6FFF);
                    break;
                case 2:
                    data = *(char **)(state->gates[k] + 0x68);
                    other = g_moby_l02_pool + *(int *)data * 0x100;
                    state->completed++;
                    qcopy(&position, other + 0x10);
                    part_l02_spawn_spinning_pairs(&position, 50);
                    part_l02_spawn_spinning_pairs(&position, 50);
                    position.f[2] += 1.0f;
                    SpawnOpposedParticles(&position, 6, 0x88FF1010, 4, 0x7F6F6FFF);
                    break;
                case 3:
                    vars = *(char **)(state->gates[k] + 0x68);
                    actor = g_moby_l02_pool + *(int *)vars * 0x100;
                    if (*(int *)(*(char **)(vars + 8) + 8) != 0) {
                        qcopy(&position, actor + 0x10);
                        position.f[2] += 1.0f;
                        SpawnOpposedParticles(&position, 6, 0x88FF1010, 4, 0x7F6F6FFF);
                        --*(int *)(*(char **)(vars + 8) + 8);
                    }
                    break;
                case 1:
                    moby_set_state((u8 *)object, 7, -1);
                    break;
                }
            }
            if (state->completed == state->gateCount) {
                if (state->platformCount > 0)
                    snd_play_from_class_bank(5, 0, state->platforms[0], 0x896 /* moby class 2198 */);
                moby_set_state((u8 *)object, 8, -1);
            }
        } else {
            if (*(u16 *)(object + 0x96) < 6)
                break;
            cam_set_mode_state(3);
            g_hero_state.cameraRequest = state->savedCamera;
            hero_l00_set_action(0, 1);
            object[0x30] = 0x40;
            if (state->decoration) {
                moby_mark_spawned(state->decoration);
                state->decoration = 0;
            }
            puzzle_reset_linked_part_group(object);
            for (m = 0; m < state->rotatorCount; m++) {
                *(float *)(state->rotators[m] + 0xF8) = *(float *)(*(char **)(state->rotators[m] + 0x68) + 0x10);
                euler_rotation_basis(state->rotators[m] + 0xC0, state->rotators[m] + 0xF0);
            }
            D_L02_001B308C = state->savedBrightness;
            D_L02_001B3090 = state->savedAlpha;
            script_queue_keyed_request(state->previousSelector, state->selectorMode);
            moby_set_state((u8 *)object, 1, -1);
        }
        break;

    }
    case 8: {
        u16 id;
        int i, j, k;
        if (D_L02_001A8F00 == 7) {
            gfx_add_draw_callback_first(menu_draw_challenge, object);
            for (i = 0; i < state->platformCount; i++) {
                AdvancePathFollower(state->platforms[i], 1);
                position.bits = *(Quad *)(state->platforms[i] + 0x10);
                SpawnOpposedParticles(&position, 60, 0x8800FF00, 4, 0x7F6F6FFF);
            }
            if (!(g_pad_state.buttons.word.high & 0x10) && *(u16 *)(object + 0x96) < 241)
                break;
            id = *(u16 *)(object + 0xB2);
            if (id & 1) {
                if (((D_0019B4A8[((short)id >> 1) + g_current_map_index * 0x400] >> 4) & 7) != 7)
                    D_0019B4A8[((short)id >> 1) + g_current_map_index * 0x400] += 16;
            } else {
                if ((D_0019B4A8[((short)id >> 1) + g_current_map_index * 0x400] & 7) != 7)
                    D_0019B4A8[((short)id >> 1) + g_current_map_index * 0x400] += 1;
            }
            moby_mark_table_entry_flagged((u8)object[0xB0]);
            moby_set_flag_bit((u8 *)object, 1);
            for (j = 0; j < 2; j++) {
                if (state->linked[j] != -1)
                    moby_set_flag_bit((u8 *)(g_moby_l02_pool + state->linked[j] * 0x100), 1);
            }
            cam_set_mode_state(3);
            g_hero_state.cameraRequest = state->savedCamera;
            hero_l00_set_action(0, 1);
            object[0x30] = 0x40;
            if (state->decoration) {
                moby_mark_spawned(state->decoration);
                state->decoration = 0;
            }
            D_L02_001B308C = state->savedBrightness;
            D_L02_001B3090 = state->savedAlpha;
            request_end_slot(0, 0);
            if (state->restoreMode != -1)
                cam_reset_entry(state->restoreMode);
            script_queue_keyed_request(state->previousSelector, state->selectorMode);
            moby_set_state((u8 *)object, 5, -1);
        } else {
            if (*(u16 *)(object + 0x96) < 6)
                break;
            id = *(u16 *)(object + 0xB2);
            if (id & 1) {
                if (((D_0019B4A8[((short)id >> 1) + g_current_map_index * 0x400] >> 4) & 7) != 7)
                    D_0019B4A8[((short)id >> 1) + g_current_map_index * 0x400] += 16;
            } else {
                if ((D_0019B4A8[((short)id >> 1) + g_current_map_index * 0x400] & 7) != 7)
                    D_0019B4A8[((short)id >> 1) + g_current_map_index * 0x400] += 1;
            }
            moby_mark_table_entry_flagged((u8)object[0xB0]);
            moby_set_flag_bit((u8 *)object, 1);
            for (k = 0; k < 2; k++) {
                if (state->linked[k] != -1)
                    moby_set_flag_bit((u8 *)(g_moby_l02_pool + state->linked[k] * 0x100), 1);
            }
            cam_set_mode_state(3);
            g_hero_state.cameraRequest = state->savedCamera;
            hero_l00_set_action(0, 1);
            object[0x30] = 0x40;
            if (state->decoration) {
                moby_mark_spawned(state->decoration);
                state->decoration = 0;
            }
            D_L02_001B308C = state->savedBrightness;
            D_L02_001B3090 = state->savedAlpha;
            script_queue_keyed_request(state->previousSelector, state->selectorMode);
            moby_set_state((u8 *)object, 5, -1);
        }
        break;

    }
    case 7: {
        char *actor;
        char *vars;
        int i;
        if (D_L02_001A8F00 == 7) {
            gfx_add_draw_callback_first(menu_draw_challenge, object);
            if (state->retryTimer != 0) {
                state->retryTimer--;
            } else if (g_pad_state.buttons.word.high & 0x10) {
                cam_set_mode_state(3);
                g_hero_state.cameraRequest = state->savedCamera;
                hero_l00_set_action(0, 1);
                object[0x30] = 0x40;
                if (state->decoration) {
                    moby_mark_spawned(state->decoration);
                    state->decoration = 0;
                }
                puzzle_reset_linked_part_group(object);
                for (i = 0; i < state->rotatorCount; i++) {
                    *(float *)(state->rotators[i] + 0xF8) = *(float *)(*(char **)(state->rotators[i] + 0x68) + 0x10);
                    euler_rotation_basis(state->rotators[i] + 0xC0, state->rotators[i] + 0xF0);
                }
                D_L02_001B308C = state->savedBrightness;
                D_L02_001B3090 = state->savedAlpha;
                script_queue_keyed_request(state->previousSelector, state->selectorMode);
                request_end_slot(0, 0);
                moby_set_state((u8 *)object, 1, -1);
            } else if (g_pad_state.buttons.all & 0xE000000000ULL) {
                puzzle_reset_linked_part_group(object);
                moby_set_state((u8 *)object, 10, -1);
            }
            for (i = 0; i < state->gateCount; i++) {
                actor = state->gates[i];
                vars = *(char **)(actor + 0x68);
                if (*(int *)(*(char **)(vars + 8) + 4) != 1) {
                    if (*(int *)(vars + 0x14) >= **(int **)(vars + 0x18) - 1) {
                        position.bits = *(Quad *)(actor + 0x10);
                        SpawnOpposedParticles(&position, 6, 0x5026A883, 4, 0x7F6F6FFF);
                        if (*(u16 *)(object + 0x96) < 2) {
                            SpawnExplosion(state->gates[i] + 0x10, 0, 0, 0, 0, 0, 0, 1,
                                         1.0f, 20.0f, 0, 0, 0, 0);
                            part_spawn_drifting(state->gates[i] + 0x10, 0, 0x5026A883, 2.0f, 10500.0f);
                        }
                    } else {
                        position.bits = *(Quad *)(actor + 0x10);
                        SpawnOpposedParticles(&position, 6, 0x88802020, 4, 0x7F6F6FFF);
                    }
                }
            }
            for (i = 0; i < state->platformCount; i++) {
                position.bits = *(Quad *)(state->platforms[i] + 0x10);
                SpawnOpposedParticles(&position, 6, 0x88802020, 4, 0x7F6F6FFF);
            }
        } else {
            if (*(u16 *)(object + 0x96) < 6)
                break;
            cam_set_mode_state(3);
            g_hero_state.cameraRequest = state->savedCamera;
            hero_l00_set_action(0, 1);
            object[0x30] = 0x40;
            if (state->decoration) {
                moby_mark_spawned(state->decoration);
                state->decoration = 0;
            }
            puzzle_reset_linked_part_group(object);
            for (i = 0; i < state->rotatorCount; i++) {
                *(float *)(state->rotators[i] + 0xF8) = *(float *)(*(char **)(state->rotators[i] + 0x68) + 0x10);
                euler_rotation_basis(state->rotators[i] + 0xC0, state->rotators[i] + 0xF0);
            }
            D_L02_001B308C = state->savedBrightness;
            D_L02_001B3090 = state->savedAlpha;
            script_queue_keyed_request(state->previousSelector, state->selectorMode);
            moby_set_state((u8 *)object, 1, -1);
        }
        break;

    }
    case 10: {
        char *actor;
        char *vars;
        int i, j;
        int completed;
        float angle;
        gfx_add_draw_callback_first(menu_draw_challenge, object);
        completed = 0;
        for (i = 0; i < state->rotatorCount; i++) {
            vars = *(char **)(state->rotators[i] + 0x68);
            angle = FastDiffRots(*(float *)(vars + 0x10), *(float *)(state->rotators[i] + 0xF8));
            if (math_fabs(angle) >= 0.08f) {
                *(float *)(state->rotators[i] + 0xF8) = FastAddRotations(*(float *)(state->rotators[i] + 0xF8), 0.05235988274f);
                euler_rotation_basis(state->rotators[i] + 0xC0, state->rotators[i] + 0xF0);
            } else {
                completed++;
            }
        }
        if (completed == state->rotatorCount) {
            for (j = 0; j < state->rotatorCount; j++) {
                vars = *(char **)(state->rotators[j] + 0x68);
                *(float *)(state->rotators[j] + 0xF8) = *(float *)(vars + 0x10);
                euler_rotation_basis(state->rotators[j] + 0xC0, state->rotators[j] + 0xF0);
            }
            moby_set_state((u8 *)object, 6, -1);
        }
        break;
    }
    case 5:
        break;
    }

    status = (u8)object[0x20];
    if (status >= 6) {
        if (status == 8)
            PulseGroupMobyColors(object, 0xDD107010, 0xDD105010);
        else if (status == 7)
            PulseGroupMobyColors(object, 0xFF0000DD, 0xFF000090);
        else
            PulseGroupMobyColors(object, 0xFF000070, 0xFF000050);
    }
    if (object[0x31] != 0)
        part_update_pulsing_glow_tint(object);
    ++*(short *)(object + 0x96);
}
