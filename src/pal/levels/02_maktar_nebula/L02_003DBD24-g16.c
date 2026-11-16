/* func_PAL_L02_003DBD24, the PAL copy of func_L02_003D7C20: the same C at 50 Hz. Most animation
 * blend times are rescaled (10 to 8, 15 to 12), the attack timer takes ((s32)(x) * 5 + 2) / 6, and
 * the rates and launch arguments have their PAL values. Animation numbers do not change.
 * PROXY is pointer arithmetic on an array of 0x100-byte actors: a field access expands with
 * the shift first in the addu, a direct argument keeps the global first.
 * D_L02_001A8F20 goes through the assembler's address macro (MACRO_ADDR). Its unsplit la is
 * one insn shorter in flow, so the launch-vector pseudo outranks state for $s2 in global-alloc.
 * func_PAL_L00_003FB330 and func_PAL_002B15D8 use integer/FP interleavings: each register bank, stack
 * argument and return contract is that of their definitions, and the declared order sets the
 * argument setup order (see AGENTS.md).
 */
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
    short saved_mode;
    short saved_anim;
    u8 saved_phase;
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
    u8 previous_anim;
    u8 anim;
    u8 pad44[4];
    float x48;
    u8 pad4C[0x14];
    u8 x60;
    u8 pad61[7];
    SentryState *state;
    u8 pad6C[0x2A];
    unsigned short state_time;
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
extern u8 g_hero_effect_state[];
extern int g_one_shot_flag;
typedef struct { u8 prefix[0x229C]; int motion; u8 reserved22A0[0x1FC]; Actor *damage; } ResidentView;
extern u8 g_hero_state[];
extern u8 g_item_enabled_flags[] MACRO_ADDR;
extern Actor *g_moby_l02_pool;
extern float g_brawler_target_position[4] __attribute__((sda));
extern float g_brawler_home_position[4] __attribute__((sda));
extern float g_zero_l02_vector[4] MACRO_ADDR;
extern u8 g_sound_state[];
extern float vec_distance_xy(void *, void *);
extern float fast_vec_dist(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float moby_get_anim_value(Actor *);
extern int flag_set_first_pending(Actor *);
extern void anim_start_blended_pal(Actor *, int, int, int);
extern void moby_set_state(Actor *, int, int);
extern float math_random_float_range(float, float);
extern void arena_set_current_boss(Actor *, Actor *);
extern float FastDiffRots(float, float);
extern void moby_set_anim_type_three_pal(void *, int, int);
extern int snd_play_from_global_bank(int, int, void *);
extern void value_set_entry_by_index_pal(int, int);
extern int FastDecTimer(short *);
extern void vec_clear_128(Quadword *);
extern void walker_boss_update_damage_pal(Actor *);
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
extern void boss_spawn_joint_sparks_pal(Actor *);
extern float IntToFloat(int);
extern char *part_spawn_flying_fragment_pal(Actor *, int, void *, void *, int, int, void *, void *, void *, float);
extern void part_spawn_green_glitter_pal(Actor *, void *);
extern void moby_mark_spawned(Actor *);
extern int snd_play_from_class_bank(int, int, Actor *, int);
extern void *SpawnExplosion_pal(void *, int, int, float, int, int, int, int, int, float, int, int, int, void *);
extern void moby_transform_joint_to_world(Actor *, int, void *);
extern void vec_random_direction(float *, float, float);
extern void part_spawn_masked_debris_pal(Actor *, int, float *, float, float, float, float, unsigned char);
extern void brawler_switch_off_actor(Actor *);
extern void turret_update_linked_object(Actor *);

/* Drive this actor's emergence, movement, attacks and destruction. */
void brawler_legs_update_pal(Actor *self)
{
    SentryState *state;
    char *slot;
    Actor *child;
    float target[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float burst_velocity[4] __attribute__((aligned(16)));
    float distance, yaw, frame, facing, value;
    short damage_kind;
    int sound;

    walker_boss_update_damage_pal(self);
    state = self->state;
    *(Quadword *)target = 0;
    if (state->target) {
        qcopy(target, state->target->position);
    }
    distance = vec_distance_xy(self->position, target);
    yaw = mat_fast_helper_a(target[0] - self->position[0], target[1] - self->position[1]);
    frame = moby_get_anim_value(self);
    damage_kind = 0;
    if (((ResidentView *)g_hero_state)->damage) {
        damage_kind = *(short *)((char *)((ResidentView *)g_hero_state)->damage + 0xAA);
    }
    if (((ResidentView *)g_hero_state)->motion == 7 || ((ResidentView *)g_hero_state)->damage == self || damage_kind == 0xD08) {
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
            self->state_time = 0;
            anim_start_blended_pal(self, 0, 0, 3);
            if ((g_moby_l02_pool + self->state->proxy)->anim) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 0, 0, 8);
                break;
            }
            break;
        }
        if (self->phase == 0 && self->state_time > 50) {
            self->phase = 1;
            if (self->anim != 3) {
                anim_start_blended_pal(self, 3, 0, 8);
            }
            if ((g_moby_l02_pool + self->state->proxy)->anim != 6) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 6, 0, 8);
            }
            self->position[2] = coll_probe_ground_height_below(self->position, 0, 10.0f);
            FastVecSub(direction, arena_get_camera_point(self->parent), self->position);
            direction[2] = 0.0f;
            vec_scale_to_length(direction, direction, 30.0f);
            FastVecAdd(direction, direction, self->position);
            direction[2] = arena_get_camera_point(self->parent)[2];
            moby_aim_move_record_at_target(self, direction, 0.40000004f, state->x7C);
            break;
        }
        else if (self->phase == 1 && (self->x60 & 2)) {
            self->phase = 2;
            if (self->anim != 4) {
                anim_start_blended_pal(self, 4, 0, 6);
            }
            if ((g_moby_l02_pool + self->state->proxy)->anim != 7) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 7, 0, 8);
                break;
            }
            break;
        }
        else if (self->phase == 2 && self->position[2] < arena_get_camera_point(self->parent)[2] + 0.05f) {
            vec_clear_128(&state->xF0);
            self->phase = 3;
            state->x292 = 0;
            if (self->anim != 5) {
                anim_start_blended_pal(self, 5, 3, 2);
            }
            if ((g_moby_l02_pool + self->state->proxy)->anim != 8) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 8, 0, 8);
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
                ((EffectTuning *)g_hero_effect_state)->amount = 0.35f;
                ((EffectTuning *)g_hero_effect_state)->kind = 21;
                ((EffectTuning *)g_hero_effect_state)->detail = 0;
                vec_clear_128(&state->xF0);
                if (self->anim) {
                    anim_start_blended_pal(self, 0, 0, 0);
                }
                if ((g_moby_l02_pool + self->state->proxy)->anim) {
                    anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 0, 0, 0);
                }
                moby_set_state(self, 5, 1);
                state->timer = (((int)(FloatToInt(math_random_float_range(600.0f, 1200.0f))) * 5 + 2) / 6);
            }
        }
        break;
    case 3:
        if (flag_set_first_pending(self)) {
            self->phase = 0;
            qcopy(state->home, g_brawler_home_position);
            if (self->anim != 1) {
                anim_start_blended_pal(self, 1, 0, 8);
            }
            brawler_clear_damage_stage_latch(self);
            chainblade_advance_health_phase(state->child);
            arena_set_current_boss(self->parent, state->child);
            vec_clear_128(&state->xF0);
            self->state_time = 0;
            break;
        }
        if (self->phase == 0) {
            value = vec_distance_xy(self->position, state->home);
            if (value < 0.01f) {
                self->phase = 1;
                if (self->anim != 3) {
                    anim_start_blended_pal(self, 3, 0, 8);
                }
                if ((g_moby_l02_pool + self->state->proxy)->anim != 6) {
                    anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 6, 0, 8);
                }
                vec_clear_128(&state->xF0);
                moby_aim_move_record_at_target(self, g_brawler_target_position, 0.40000004f, state->x7C);
                break;
            }
        }
        if (self->phase == 1 && (self->x60 & 2)) {
            self->phase = 2;
            self->state_time = 0;
            if (self->anim != 4) {
                anim_start_blended_pal(self, 4, 0, 8);
            }
            if ((g_moby_l02_pool + self->state->proxy)->anim != 7) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 7, 0, 8);
                break;
            }
        } else if (self->phase == 2) {
            value = fast_vec_dist(self->position, g_brawler_target_position);
            if (!(value < 1.0f) && self->state_time < 251) {
                break;
            }
            self->phase = 3;
            if (self->anim != 5) {
                anim_start_blended_pal(self, 5, 0, 8);
            }
            if ((g_moby_l02_pool + self->state->proxy)->anim != 8) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 8, 0, 8);
                break;
            }
        } else if (self->phase == 3 && (self->x60 & 2)) {
            moby_set_state(self, 4, -1);
        }
        break;
    case 4:
        if (flag_set_first_pending(self)) {
            if (self->anim) {
                anim_start_blended_pal(self, 0, 0, 8);
            }
            if ((g_moby_l02_pool + self->state->proxy)->anim) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 0, 0, 8);
            }
        }
        vec_step_toward_target_limited(self->position, g_brawler_target_position, 0.20000002f);
        if (state->x280 == 1 && vec_distance_xy(self->position, g_brawler_target_position) < 0.001f) {
            moby_set_state(self, 2, 1);
        }
        break;
    case 5:
        if (flag_set_first_pending(self)) {
            if (self->anim != 1) {
                anim_start_blended_pal(self, 1, 0, 12);
            }
            if ((g_moby_l02_pool + self->state->proxy)->anim != 1) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 1, 0, 8);
            }
            self->phase = 1;
        }
        facing = FastDiffRots(yaw, self->rot[2]);
        if (self->phase == 1 && facing > 0.78539824f) {
            self->phase = 2;
            if (self->anim != 2) {
                anim_start_blended_pal(self, 2, 0, 12);
            }
            if ((g_moby_l02_pool + self->state->proxy)->anim != 3) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 3, 0, 8);
            }
        }
        if (self->phase == 2 && facing < 0.17453295f) {
            self->phase = 1;
            if (self->anim != 1) {
                anim_start_blended_pal(self, 1, 0, 12);
            }
            if ((g_moby_l02_pool + self->state->proxy)->anim != 1) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 1, 0, 8);
            }
        }
        if (self->phase == 1 && distance < 10.0f) {
            self->phase = 0;
            if (self->anim) {
                anim_start_blended_pal(self, 0, 0, 12);
            }
        }
        if (self->phase == 0 && distance > 20.0f) {
            self->phase = 1;
            if (self->anim != 1) {
                anim_start_blended_pal(self, 1, 0, 8);
            }
        }
        if (((ResidentView *)g_hero_state)->damage) {
            moby_switch_to_state_seven(self);
        }
        if (FastDecTimer(&state->timer)) {
            state->timer = (((int)(FloatToInt(math_random_float_range(600.0f, 1200.0f))) * 5 + 2) / 6);
            moby_set_state(self, 6, -1);
        }
        if (brawler_is_health_below_stage(self)) {
            moby_set_state(self, 3, 0);
        }
        break;
    case 6:
        if (flag_set_first_pending(self)) {
            if (self->previous_anim == 7) {
                self->phase = 1;
                if ((g_moby_l02_pool + self->state->proxy)->anim != 10) {
                    anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 10, 0, 8);
                }
            } else if (self->previous_anim == 6) {
                self->phase = 0;
                self->flags &= 0xEFFF;
            } else {
                if (self->anim != 6) {
                    anim_start_blended_pal(self, 6, 0, 0);
                }
                if ((g_moby_l02_pool + self->state->proxy)->anim != 9) {
                    anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 9, 0, 8);
                }
                self->phase = 0;
                self->flags &= 0xEFFF;
            }
        } else if (self->phase == 0 && frame > 28.0f) {
            if (self->anim != 7) {
                anim_start_blended_pal(self, 7, 0, 0);
            }
            if ((g_moby_l02_pool + self->state->proxy)->anim != 10) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 10, 0, 8);
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
                    anim_start_blended_pal(self, 8, 0, 0);
                }
                if ((g_moby_l02_pool + self->state->proxy)->anim != 11) {
                    anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 11, 0, 8);
                }
                self->phase = 2;
                self->flags &= 0xEFFF;
            }
        }
        if (self->phase == 1 && ((ResidentView *)g_hero_state)->damage) {
            moby_switch_to_state_seven(self);
            break;
        }
        if (self->phase == 2 && frame > 45.0f) {
            state->x30 = 11.0f;
            self->x9C = 0;
            self->flags |= 0x1000;
            state->timer = (((int)(FloatToInt(math_random_float_range(600.0f, 1200.0f))) * 5 + 2) / 6);
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
            if ((g_moby_l02_pool + self->state->proxy)->anim != 7) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 7, 0, 12);
            }
            state->x24C += 0.27925274f;
            self->state_time = 0;
        } else if (self->state_time >= 181) {
            moby_set_state(self, 6, -1);
        }
        break;
    case 8:
        if (flag_set_first_pending(self)) {
            if (self->anim != 8) {
                anim_start_blended_pal(self, 8, 0, 17);
            }
            if ((g_moby_l02_pool + self->state->proxy)->anim != 9) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 9, 0, 12);
            }
            state->x24C += 0.27925274f;
        } else if (frame > 45.0f) {
            moby_set_state(self, state->saved_mode, -1);
        }
        break;
    case 9:
        if (flag_set_first_pending(self)) {
            if ((g_moby_l02_pool + self->state->proxy)->anim != 12) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 12, 0, 12);
            }
        }
        boss_spawn_joint_sparks_pal(self);
        if (!((g_moby_l02_pool + self->state->proxy)->x60 & 2)) {
            break;
        }
        self->mode = state->saved_mode;
        self->phase = state->saved_phase;
        if ((g_moby_l02_pool + self->state->proxy)->anim != state->saved_anim) {
            anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), state->saved_anim, 0, 12);
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
            if (self->previous_anim == 7) {
                self->phase = 1;
                if ((g_moby_l02_pool + self->state->proxy)->anim != 13) {
                    anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 13, 0, 12);
                }
                break;
            }
            else {
                self->phase = 0;
                if (self->previous_anim != 6 && self->anim != 9) {
                    anim_start_blended_pal(self, 9, 0, 12);
                }
            }
            if ((g_moby_l02_pool + self->state->proxy)->anim != 13) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 13, 0, 12);
            }
            break;
        }
        if (self->phase == 0 && (self->x60 & 2)) {
            self->phase = 1;
            if ((g_moby_l02_pool + self->state->proxy)->anim != 13) {
                anim_start_blended_pal((g_moby_l02_pool + self->state->proxy), 13, 0, 12);
            }
            if (self->anim != 7) {
                anim_start_blended_pal(self, 7, 0, 8);
                break;
            }
        } else if (self->phase == 1 && ((g_moby_l02_pool + self->state->proxy)->x60 & 2)) {
            moby_set_state(self, 11, -1);
        }
        break;
    case 11:
        if (flag_set_first_pending(self)) {
            if (!state->forced && !g_item_enabled_flags[0x13]) {
                g_item_enabled_flags[0x13] = 1;
                snd_play_from_global_bank(1, 0, 0);
                value_set_entry_by_index_pal(0x1233, -1);
                g_one_shot_flag = 1;
            }
            self->x48 = 0.0f;
            (g_moby_l02_pool + self->state->proxy)->x48 = 0.0f;
            self->state_time = 0;
            FastVecSub(direction, g_camera_l02_position, (g_moby_l02_pool + self->state->proxy)->position);
            vec_scale_to_length(direction, direction, math_random_float_range(0.10000001f, 0.14000002f));
            direction[2] += 0.080000006f;
            if (self->state->launcher) {
                part_spawn_flying_fragment_pal(self->state->launcher, 0xA4C, self->state->launcher->position, self->state->launcher->rot, 250, 0, direction,
                        g_zero_l02_vector, g_zero_l02_vector, 0.002f);
                part_spawn_green_glitter_pal(self, g_zero_l02_vector);
                moby_mark_spawned(self->state->launcher);
                self->state->launcher = 0;
                snd_play_from_class_bank(5, 0, self, 0xA44);
            }
            moby_set_anim_type_three_pal(self, 0, -1);
            state->x1F2 = 1;
            state->scale[0] = state->scale[1] = state->scale[2] = 2.0f;
            self->flags &= 0xEFFF;
        }
        value = IntToFloat(self->state_time) * -0.013333267f + 2.0f;
        if (value < 0.0f) {
            value = 0.0f;
        }
        state->scale[0] = state->scale[1] = state->scale[2] = value;
        if (self->state_time > 150) {
            self->x48 = 1.0f;
            (g_moby_l02_pool + self->state->proxy)->x48 = 1.0f;
            SpawnExplosion_pal(self->position, 1, 25, 2.0f, 20, 30, 40, 45, 1, 20.0f, 0, 1, 0, 0);
            moby_transform_joint_to_world(self, 2, direction);
            SpawnExplosion_pal(self->position, 0, 10, 0.7f, 5, 10, 5, 20, 1, 20.0f, 0, 0, 0, 0);
            moby_transform_joint_to_world(self, 6, direction);
            SpawnExplosion_pal(self->position, 0, 0, 0.7f, 10, 20, 15, 45, 1, 20.0f, 0, 0, 0, 0);
            moby_transform_joint_to_world(self, 4, direction);
            SpawnExplosion_pal(self->position, 0, 20, 0.7f, 0, 15, 10, 30, 1, 20.0f, 0, 0, 0, 0);
            moby_transform_joint_to_world(self, 8, direction);
            SpawnExplosion_pal(self->position, 0, 5, 0.7f, 15, 5, 25, 25, 1, 20.0f, 0, 0, 0, 0);
            vec_random_direction(burst_velocity, 0.120000005f, 0.24000001f);
            part_spawn_masked_debris_pal(self, 0xFFF, burst_velocity, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            vec_random_direction(burst_velocity, 0.16000001f, 0.32000002f);
            part_spawn_masked_debris_pal((g_moby_l02_pool + self->state->proxy), 0x1F, burst_velocity, 3.0f, 6.0f, 3.0f, 6.0f, 255);
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
