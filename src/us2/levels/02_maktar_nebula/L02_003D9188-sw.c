#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef struct Actor Actor;
typedef struct {
    u8 pad000[0x30];
    float x30;
    u8 pad034[0x48];
    float x7C;
    u8 pad080[0x70];
    Quadword xF0;
    u8 pad100[0xF2];
    u8 x1F2;
    u8 pad1F3[0x1D];
    float scale[3];
    u8 pad21C[0x14];
    float home[4];
    Actor *target;
    int proxy;
    u8 pad248[4];
    float x24C;
    u8 pad250[0x10];
    Actor *launcher;
    Actor *child;
    u8 pad268[4];
    int sound;
    u8 pad270[0x10];
    short x280;
    u8 pad282[6];
    short timer;
    short savedMode;
    short savedAnim;
    u8 savedPhase;
    u8 pad28F;
    short forced;
    short x292;
} SentryState;
struct Actor {
    u8 pad00[0x10];
    float position[4];
    u8 mode;
    u8 pad21[0x13];
    unsigned short flags;
    u8 pad36[0xC];
    u8 previousAnim;
    u8 anim;
    u8 pad44[4];
    float x48;
    u8 pad4C[0x14];
    u8 x60;
    u8 pad61[7];
    SentryState *state;
    u8 pad6C[0x2A];
    unsigned short stateTime;
    u8 pad98[4];
    int x9C;
    u8 padA0[0x18];
    Actor *parent;
    u8 phase;
    u8 padBD[0x33];
    float rot[4];
    u8 pad100[0];
};
typedef struct { u8 prefix[0x160]; float amount; int reserved164; int kind; int detail; } EffectTuning;
extern u8 g_camera_l02_position[];
extern u8 D_L02_001BA3C0[];
#define EFFECT ((EffectTuning *)D_L02_001BA3C0)
extern int D_L02_001A903C;
typedef struct { u8 prefix[0x229C]; int motion; u8 reserved22A0[0x1FC]; Actor *damage; } ResidentView;
extern u8 g_hero_state[];
#define RESIDENT ((ResidentView *)D_00189E20)
extern u8 D_001A7A60[] MACRO_ADDR;
extern Actor *g_moby_l02_pool;
extern float D_L02_001B03F0[4] __attribute__((sda));
extern float D_L02_001B0400[4] __attribute__((sda));
extern float D_L02_001A8F20[4] MACRO_ADDR;
extern u8 g_sound_state[];
extern float vec_distance_xy(void *, void *);
extern float fast_vec_dist(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float moby_get_anim_value(Actor *);
extern int flag_set_first_pending(Actor *);
extern void anim_start_blended(Actor *, int, int, int);
extern void moby_set_state(Actor *, int, int);
extern float math_random_float_range(float, float);
extern void arena_set_current_boss(Actor *, Actor *);
extern float FastDiffRots(float, float);
extern void moby_set_anim_type_three(void *, int, int);
extern int snd_play_from_global_bank(int, int, void *);
extern void func_US2_002B1880(int, int);
extern int FastDecTimer(short *);
extern void vec_clear_128(Quadword *);
extern void walker_boss_update_damage(Actor *);
extern float coll_probe_ground_height_below(void *, int, float);
extern float *arena_get_camera_point(Actor *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int moby_aim_move_record_at_target(Actor *, void *, float, float);
extern void boss_rebuild_joint_widgets(Actor *);
extern int PlayMobySound(int, int, Actor *);
extern void brawler_clear_damage_stage_latch(Actor *);
extern void chainblade_advance_health_phase(Actor *);
extern float vec_step_toward_target_limited(void *, void *, float);
extern void moby_switch_to_state_seven(Actor *);
extern int FloatToInt(float);
extern int brawler_is_health_below_stage(Actor *);
extern int snd_is_voice_playing_for_owner(Actor *, int);
extern void snd_stop_voice(int);
extern void boss_spawn_joint_sparks(Actor *);
extern float IntToFloat(int);
extern char *part_spawn_flying_fragment(Actor *, int, void *, void *, int, int, void *, void *, void *, float);
extern void part_spawn_green_glitter(Actor *, void *);
extern void moby_mark_spawned(Actor *);
extern int snd_play_from_class_bank(int, int, Actor *, int);
extern void *SpawnExplosion(void *, int, int, float, int, int, int, int, int, float, int, int, int, void *);
extern void moby_transform_joint_to_world(Actor *, int, void *);
extern void vec_random_direction(float *, float, float);
extern void part_spawn_masked_debris(Actor *, int, float *, float, float, float, float, unsigned char);
extern void brawler_switch_off_actor(Actor *);
extern void turret_update_linked_object(Actor *);
#define PROXY (D_L02_001B359C + self->state->proxy)

/* Drive this actor's emergence, movement, attacks and destruction. */
void func_US2_L02_003D9188(Actor *self)
{
    SentryState *state;
    char *slot;
    Actor *child;
    float target[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float curve[4] __attribute__((aligned(16)));
    float distance, yaw, frame, facing, value;
    short damageKind;
    int sound;

    walker_boss_update_damage(self);
    state = self->state;
    *(Quadword *)target = 0;
    if (state->target) {
        qcopy(target, state->target->position);
    }
    distance = vec_distance_xy(self->position, target);
    yaw = mat_fast_helper_a(target[0] - self->position[0], target[1] - self->position[1]);
    frame = moby_get_anim_value(self);
    damageKind = 0;
    if (RESIDENT->damage) {
        damageKind = *(short *)((char *)RESIDENT->damage + 0xAA);
    }
    if (RESIDENT->motion == 7 || RESIDENT->damage == self || damageKind == 0xD08) {
        state->forced = 1;
    }
    switch (self->mode) {
    case 0:
    case 1:
        break;
    case 2:
        state->forced = 0;
        if (flag_set_first_pending(self)) {
            self->phase = 0;
            self->stateTime = 0;
            anim_start_blended(self, 0, 0, 3);
            if (PROXY->anim) {
                anim_start_blended(PROXY, 0, 0, 10);
                break;
            }
            break;
        }
        if (self->phase == 0 && self->stateTime > 60) {
            self->phase = 1;
            if (self->anim != 3) {
                anim_start_blended(self, 3, 0, 10);
            }
            if (PROXY->anim != 6) {
                anim_start_blended(PROXY, 6, 0, 10);
            }
            self->position[2] = coll_probe_ground_height_below(self->position, 0, 10.0f);
            FastVecSub(direction, arena_get_camera_point(self->parent), self->position);
            direction[2] = 0.0f;
            vec_scale_to_length(direction, direction, 30.0f);
            FastVecAdd(direction, direction, self->position);
            direction[2] = arena_get_camera_point(self->parent)[2];
            moby_aim_move_record_at_target(self, direction, 0.33333334f, state->x7C);
            break;
        }
        else if (self->phase == 1 && (self->x60 & 2)) {
            self->phase = 2;
            if (self->anim != 4) {
                anim_start_blended(self, 4, 0, 7);
            }
            if (PROXY->anim != 7) {
                anim_start_blended(PROXY, 7, 0, 10);
                break;
            }
            break;
        }
        else if (self->phase == 2 && self->position[2] < arena_get_camera_point(self->parent)[2] + 0.05f) {
            vec_clear_128(&state->xF0);
            self->phase = 3;
            state->x292 = 0;
            if (self->anim != 5) {
                anim_start_blended(self, 5, 3, 2);
            }
            if (PROXY->anim != 8) {
                anim_start_blended(PROXY, 8, 0, 10);
            }
            boss_rebuild_joint_widgets(self);
            break;
        }
        else if (self->phase == 3) {
            value = moby_get_anim_value(self);
            if (value > 2.0f && !state->x292) {
                state->x292 = 1;
                PlayMobySound(0, 0, self);
            }
            if (self->x60 & 2) {
                EFFECT->amount = 0.35f;
                EFFECT->kind = 25;
                EFFECT->detail = 0;
                vec_clear_128(&state->xF0);
                if (self->anim) {
                    anim_start_blended(self, 0, 0, 0);
                }
                if (PROXY->anim) {
                    anim_start_blended(PROXY, 0, 0, 0);
                }
                moby_set_state(self, 5, 1);
                state->timer = FloatToInt(math_random_float_range(600.0f, 1200.0f));
            }
        }
        break;
    case 3:
        if (flag_set_first_pending(self)) {
            self->phase = 0;
            qcopy(state->home, D_L02_001B0400);
            if (self->anim != 1) {
                anim_start_blended(self, 1, 0, 10);
            }
            brawler_clear_damage_stage_latch(self);
            chainblade_advance_health_phase(state->child);
            arena_set_current_boss(self->parent, state->child);
            vec_clear_128(&state->xF0);
            self->stateTime = 0;
            break;
        }
        if (self->phase == 0) {
            value = vec_distance_xy(self->position, state->home);
            if (value < 0.01f) {
                self->phase = 1;
                if (self->anim != 3) {
                    anim_start_blended(self, 3, 0, 10);
                }
                if (PROXY->anim != 6) {
                    anim_start_blended(PROXY, 6, 0, 10);
                }
                vec_clear_128(&state->xF0);
                moby_aim_move_record_at_target(self, D_L02_001B03F0, 0.33333334f, state->x7C);
                break;
            }
        }
        if (self->phase == 1 && (self->x60 & 2)) {
            self->phase = 2;
            self->stateTime = 0;
            if (self->anim != 4) {
                anim_start_blended(self, 4, 0, 10);
            }
            if (PROXY->anim != 7) {
                anim_start_blended(PROXY, 7, 0, 10);
                break;
            }
        } else if (self->phase == 2) {
            value = fast_vec_dist(self->position, D_L02_001B03F0);
            if (!(value < 1.0f) && self->stateTime < 301) {
                break;
            }
            self->phase = 3;
            if (self->anim != 5) {
                anim_start_blended(self, 5, 0, 10);
            }
            if (PROXY->anim != 8) {
                anim_start_blended(PROXY, 8, 0, 10);
                break;
            }
        } else if (self->phase == 3 && (self->x60 & 2)) {
            moby_set_state(self, 4, -1);
        }
        break;
    case 4:
        if (flag_set_first_pending(self)) {
            if (self->anim) {
                anim_start_blended(self, 0, 0, 10);
            }
            if (PROXY->anim) {
                anim_start_blended(PROXY, 0, 0, 10);
            }
        }
        vec_step_toward_target_limited(self->position, D_L02_001B03F0, 0.16666667f);
        if (state->x280 == 1 && vec_distance_xy(self->position, D_L02_001B03F0) < 0.001f) {
            moby_set_state(self, 2, 1);
        }
        break;
    case 5:
        if (flag_set_first_pending(self)) {
            if (self->anim != 1) {
                anim_start_blended(self, 1, 0, 15);
            }
            if (PROXY->anim != 1) {
                anim_start_blended(PROXY, 1, 0, 10);
            }
            self->phase = 1;
        }
        facing = FastDiffRots(yaw, self->rot[2]);
        if (self->phase == 1 && facing > 0.78539824f) {
            self->phase = 2;
            if (self->anim != 2) {
                anim_start_blended(self, 2, 0, 15);
            }
            if (PROXY->anim != 3) {
                anim_start_blended(PROXY, 3, 0, 10);
            }
        }
        if (self->phase == 2 && facing < 0.17453295f) {
            self->phase = 1;
            if (self->anim != 1) {
                anim_start_blended(self, 1, 0, 15);
            }
            if (PROXY->anim != 1) {
                anim_start_blended(PROXY, 1, 0, 10);
            }
        }
        if (self->phase == 1 && distance < 10.0f) {
            self->phase = 0;
            if (self->anim) {
                anim_start_blended(self, 0, 0, 15);
            }
        }
        if (self->phase == 0 && distance > 20.0f) {
            self->phase = 1;
            if (self->anim != 1) {
                anim_start_blended(self, 1, 0, 10);
            }
        }
        if (RESIDENT->damage) {
            moby_switch_to_state_seven(self);
        }
        if (FastDecTimer(&state->timer)) {
            state->timer = FloatToInt(math_random_float_range(600.0f, 1200.0f));
            moby_set_state(self, 6, -1);
        }
        if (brawler_is_health_below_stage(self)) {
            moby_set_state(self, 3, 0);
        }
        break;
    case 6:
        if (flag_set_first_pending(self)) {
            if (self->previousAnim == 7) {
                self->phase = 1;
                if (PROXY->anim != 10) {
                    anim_start_blended(PROXY, 10, 0, 10);
                }
            } else if (self->previousAnim == 6) {
                self->phase = 0;
                self->flags &= 0xEFFF;
            } else {
                if (self->anim != 6) {
                    anim_start_blended(self, 6, 0, 0);
                }
                if (PROXY->anim != 9) {
                    anim_start_blended(PROXY, 9, 0, 10);
                }
                self->phase = 0;
                self->flags &= 0xEFFF;
            }
        } else if (self->phase == 0 && frame > 28.0f) {
            if (self->anim != 7) {
                anim_start_blended(self, 7, 0, 0);
            }
            if (PROXY->anim != 10) {
                anim_start_blended(PROXY, 10, 0, 10);
            }
            self->phase = 1;
            state->x30 = 1.5f;
            self->flags |= 0x1000;
            if (!snd_is_voice_playing_for_owner(self, state->sound)) {
                state->sound = PlayMobySound(6, 4, self);
            }
        } else if (self->phase == 1) {
            self->x9C = 1;
            if (FastDecTimer(&state->timer) || brawler_is_health_below_stage(self)) {
                if (self->anim != 8) {
                    anim_start_blended(self, 8, 0, 0);
                }
                if (PROXY->anim != 11) {
                    anim_start_blended(PROXY, 11, 0, 10);
                }
                self->phase = 2;
                self->flags &= 0xEFFF;
            }
        }
        if (self->phase == 1 && RESIDENT->damage) {
            moby_switch_to_state_seven(self);
            break;
        }
        if (self->phase == 2 && frame > 45.0f) {
            state->x30 = 11.0f;
            self->x9C = 0;
            self->flags |= 0x1000;
            state->timer = FloatToInt(math_random_float_range(600.0f, 1200.0f));
            moby_set_state(self, 5, -1);
            sound = state->sound;
            if (sound != -1) {
                slot = (char *)g_sound_state + sound * 0x70;
                if (*(Actor **)(slot + 0x88) == self && *(u8 *)(slot + 0x74)) {
                    snd_stop_voice(sound);
                }
            }
            state->sound = -1;
        }
        break;
    case 7:
        if (flag_set_first_pending(self)) {
            if (PROXY->anim != 7) {
                anim_start_blended(PROXY, 7, 0, 15);
            }
            state->x24C += 0.1939255f;
            self->stateTime = 0;
        } else if (self->stateTime >= 181) {
            moby_set_state(self, 6, -1);
        }
        break;
    case 8:
        if (flag_set_first_pending(self)) {
            if (self->anim != 8) {
                anim_start_blended(self, 8, 0, 20);
            }
            if (PROXY->anim != 9) {
                anim_start_blended(PROXY, 9, 0, 15);
            }
            state->x24C += 0.1939255f;
        } else if (frame > 45.0f) {
            moby_set_state(self, state->savedMode, -1);
        }
        break;
    case 9:
        if (flag_set_first_pending(self)) {
            if (PROXY->anim != 12) {
                anim_start_blended(PROXY, 12, 0, 15);
            }
        }
        boss_spawn_joint_sparks(self);
        if (!(PROXY->x60 & 2)) {
            break;
        }
        self->mode = state->savedMode;
        self->phase = state->savedPhase;
        if (PROXY->anim != state->savedAnim) {
            anim_start_blended(PROXY, state->savedAnim, 0, 15);
        }
        break;
    case 10:
        if (flag_set_first_pending(self)) {
            sound = state->sound;
            if (sound != -1) {
                slot = (char *)g_sound_state + sound * 0x70;
                if (*(Actor **)(slot + 0x88) == self && *(u8 *)(slot + 0x74)) {
                    snd_stop_voice(sound);
                }
            }
            state->sound = -1;
            if (self->previousAnim == 7) {
                self->phase = 1;
                if (PROXY->anim != 13) {
                    anim_start_blended(PROXY, 13, 0, 15);
                }
                break;
            }
            else {
                self->phase = 0;
                if (self->previousAnim != 6 && self->anim != 9) {
                    anim_start_blended(self, 9, 0, 15);
                }
            }
            if (PROXY->anim != 13) {
                anim_start_blended(PROXY, 13, 0, 15);
            }
            break;
        }
        if (self->phase == 0 && (self->x60 & 2)) {
            self->phase = 1;
            if (PROXY->anim != 13) {
                anim_start_blended(PROXY, 13, 0, 15);
            }
            if (self->anim != 7) {
                anim_start_blended(self, 7, 0, 10);
                break;
            }
        } else if (self->phase == 1 && (PROXY->x60 & 2)) {
            moby_set_state(self, 11, -1);
        }
        break;
    case 11:
        if (flag_set_first_pending(self)) {
            if (!state->forced && !D_001A7A60[0x13]) {
                D_001A7A60[0x13] = 1;
                snd_play_from_global_bank(1, 0, 0);
                func_US2_002B1880(0x1233, -1);
                D_L02_001A903C = 1;
            }
            self->x48 = 0.0f;
            PROXY->x48 = 0.0f;
            self->stateTime = 0;
            FastVecSub(direction, g_camera_l02_position, PROXY->position);
            vec_scale_to_length(direction, direction, math_random_float_range(0.083333336f, 0.116666675f));
            direction[2] += 0.06666667f;
            if (self->state->launcher) {
                part_spawn_flying_fragment(self->state->launcher, 0xA4C, self->state->launcher->position, self->state->launcher->rot, 300, 0, direction,
                        D_L02_001A8F20, D_L02_001A8F20, 0.0013888889f);
                part_spawn_green_glitter(self, D_L02_001A8F20);
                moby_mark_spawned(self->state->launcher);
                self->state->launcher = 0;
                snd_play_from_class_bank(5, 0, self, 0xA44);
            }
            moby_set_anim_type_three(self, 0, -1);
            state->x1F2 = 1;
            state->scale[0] = state->scale[1] = state->scale[2] = 2.0f;
            self->flags &= 0xEFFF;
        }
        value = IntToFloat(self->stateTime) * -0.0111110555f + 2.0f;
        if (value < 0.0f) {
            value = 0.0f;
        }
        state->scale[0] = state->scale[1] = state->scale[2] = value;
        if (self->stateTime > 180) {
            self->x48 = 1.0f;
            PROXY->x48 = 1.0f;
            SpawnExplosion(self->position, 1, 25, 2.0f, 20, 30, 40, 45, 1, 20.0f, 0, 1, 0, 0);
            moby_transform_joint_to_world(self, 2, direction);
            SpawnExplosion(self->position, 0, 10, 0.7f, 5, 10, 5, 20, 1, 20.0f, 0, 0, 0, 0);
            moby_transform_joint_to_world(self, 6, direction);
            SpawnExplosion(self->position, 0, 0, 0.7f, 10, 20, 15, 45, 1, 20.0f, 0, 0, 0, 0);
            moby_transform_joint_to_world(self, 4, direction);
            SpawnExplosion(self->position, 0, 20, 0.7f, 0, 15, 10, 30, 1, 20.0f, 0, 0, 0, 0);
            moby_transform_joint_to_world(self, 8, direction);
            SpawnExplosion(self->position, 0, 5, 0.7f, 15, 5, 25, 25, 1, 20.0f, 0, 0, 0, 0);
            vec_random_direction(curve, 0.10000001f, 0.20000002f);
            part_spawn_masked_debris(self, 0xFFF, curve, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            vec_random_direction(curve, 0.13333334f, 0.26666668f);
            part_spawn_masked_debris(PROXY, 0x1F, curve, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            snd_play_from_class_bank(5, 0, self, 0xA44);
            brawler_switch_off_actor(self);
            state->scale[0] = state->scale[1] = state->scale[2] = 1.0f;
            state->x1F2 = 0;
            child = state->child;
            if (child && child->mode != 254 && child->mode != 253 && child->mode > 2) {
                chainblade_advance_health_phase(child);
                arena_set_current_boss(self->parent, state->child);
            }
        }
        break;
    }
    turret_update_linked_object(self);
}
